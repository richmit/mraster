// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      newton_max_back.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Newton Fractical -- color by orbit distance from roots.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/newton/index.html#max_back
 @copyright
  @parblock
  Copyright (c) 1988-2015, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software
     without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
  @endparblock
 @filedetails   

  We do the standard Newton iterations, but we keep track iterations that make a step AWAY from the root to which the orbit eventually converges.  Then
  we color according to the largest such back-step.  Near the origin, some backsteps are quite large.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b rcT;      // The Ram Canvas type we will use
typedef rcT::colorChanType rcccT;    // Color Channel Type

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  constexpr int        MAXITR = 255;
  constexpr double     ZROEPS = .0001;
  constexpr int        IMGSIZ = 7680;
  std::complex<double> r1( 1.0,                        0.0);
  std::complex<double> r2(-0.5,  sin(2*std::numbers::pi/3));
  std::complex<double> r3(-0.5, -sin(2*std::numbers::pi/3));
  rcT                  theRamCanvas(IMGSIZ, IMGSIZ, -2.15, 1.85, -2.0, 2.0);

# pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> z = theRamCanvas.int2real(x, y);
      std::complex<double> zL = z;
      double maxStepBack1 = 0.0;
      double maxStepBack2 = 0.0;
      double maxStepBack3 = 0.0;
      double curRootMod1 = 1.0;
      double curRootMod2 = 1.0;
      double curRootMod3 = 1.0;
      for(int count=0; count<MAXITR; count++) {
        double modz = std::abs(z);
        if (modz<ZROEPS)
          break;
        z = z-(z*z*z-1.0)/(z*z*3.0);
        curRootMod1 = std::abs(z-r1);
        curRootMod2 = std::abs(z-r2);
        curRootMod3 = std::abs(z-r3);
        double curStepBack1 = curRootMod1 - std::abs(zL-r1);
        double curStepBack2 = curRootMod2 - std::abs(zL-r2);
        double curStepBack3 = curRootMod3 - std::abs(zL-r3);
        if(curStepBack1 > maxStepBack1) maxStepBack1 = curStepBack1;
        if(curStepBack2 > maxStepBack2) maxStepBack2 = curStepBack2;
        if(curStepBack3 > maxStepBack3) maxStepBack3 = curStepBack3;
        if ((modz<ZROEPS) || (curRootMod1<ZROEPS) || (curRootMod2<ZROEPS) || (curRootMod3<ZROEPS))
          break;
      }

      rcccT r = static_cast<rcccT>(( ((curRootMod1 < 2*ZROEPS) && (maxStepBack1 > 0)) ? std::log(1+maxStepBack1)*18 : 0));
      rcccT g = static_cast<rcccT>(( ((curRootMod2 < 2*ZROEPS) && (maxStepBack2 > 0)) ? std::log(1+maxStepBack2)*18 : 0));
      rcccT b = static_cast<rcccT>(( ((curRootMod3 < 2*ZROEPS) && (maxStepBack3 > 0)) ? std::log(1+maxStepBack3)*18 : 0));
      theRamCanvas.drawPoint(x, y, rcT::colorType(r, g, b));
    }
  }
  theRamCanvas.autoMaxHistStrechRGB();
  theRamCanvas.applyHomoPixTfrm(&rcT::colorType::tfrmPow, 0.4);
  theRamCanvas.writeTIFFfile("newton_max_back.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
