// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      newton_min_root.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Newton Fractical -- color by orbit distance from roots.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/newton/index.html
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

  We do the standard Newton iterations, but we keep track of the minimum distance from the roots by any iterate of the orbit.  Then we use the two largest
  minimum distances to color the pixel.  The distances are used to set the r, g, b channels (i.e. distance to root 1 is r, root 2 is g, and root 3 is b).
  Closer is a brighter color.  By using the two largest and omitting the third distance, the color represents how close the orbit got to the roots to which it
  didn't converge.
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
  int                  MAXITR = 255;
  double               ZROEPS = .0001;
  double               MAXZ   = 10;
  const int            IMGSIZ = 7680;
  std::complex<double> r1( 1.0,                        0.0);
  std::complex<double> r2(-0.5,  sin(2*std::numbers::pi/3));
  std::complex<double> r3(-0.5, -sin(2*std::numbers::pi/3));
  rcT                  theRamCanvas(IMGSIZ, IMGSIZ, -2.15, 1.85, -2.0, 2.0);

# pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> z(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));
      double minMod1 = std::abs(z-r1);
      double minMod2 = std::abs(z-r2);
      double minMod3 = std::abs(z-r3);
      for(int count=0; count<MAXITR; count++) {
        double modz = std::abs(z);
        if ((modz>MAXZ) || (modz<ZROEPS))
          break;
        z = z-(z*z*z-1.0)/(z*z*3.0);
        if(std::abs(z-r1) < minMod1) minMod1 = std::abs(z-r1);
        if(std::abs(z-r2) < minMod2) minMod2 = std::abs(z-r2);
        if(std::abs(z-r3) < minMod3) minMod3 = std::abs(z-r3);
        if ((modz<ZROEPS) || (minMod1<ZROEPS) || (minMod2<ZROEPS) || (minMod3<ZROEPS))
          break;
      }

      rcccT r = static_cast<rcccT>((minMod1 < std::min(minMod2, minMod3) ? 100.0 : 720.0*std::log(4.73-minMod1)));
      rcccT g = static_cast<rcccT>((minMod2 < std::min(minMod1, minMod3) ? 100.0 : 720.0*std::log(4.73-minMod2)));
      rcccT b = static_cast<rcccT>((minMod3 < std::min(minMod1, minMod2) ? 100.0 : 720.0*std::log(4.73-minMod3)));
      theRamCanvas.drawPoint(x, y, rcT::colorType(r, g, b));
    }
  }

  theRamCanvas.writeTIFFfile("newton_min_root.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
