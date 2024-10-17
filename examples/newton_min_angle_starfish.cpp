// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      newton_min_angle_starfish.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Newton Fractical@EOL
 @std       C++20
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

  We do the standard Newton iterations, but we keep track of the minimum phase angle difference between the three bisectors between the roots. The distances
  are used to set the r, g, b channels (i.e. distance to root 1/2 bisector is r, root 1/3 bisector is g, and root 2/3 bisector is b).

  The standard Newton fractal is generated from @f$f=z^2-1@f$.  This function is continuous on the entire complex plain.  What do we get if we add poles
  in imaginary axis mirror locations of the roots?  i.e. for each root @f$x+iy@f$ of @f$f@f$, we add a pole at @f$-x+iy@f$?  The corresponding function is:
         @f[f=\frac{z^3-1}{z^3+1}@f]
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
  constexpr double     ang1   = 0.0;
  constexpr double     ang2   = 2*std::numbers::pi/3;
  constexpr double     ang3   = -2*std::numbers::pi/3;
  constexpr double     ang12  = (ang1+ang2)/2.0;
  constexpr double     ang13  = (ang1+ang3)/2.0;
  constexpr double     ang23  = std::numbers::pi;
  const double         normer = std::log(2*std::numbers::pi/3);
  const double         r      = 0.010;
  std::complex<double> r1( 1.0,  sin(ang1));
  std::complex<double> r2(-0.5,  sin(ang2));
  std::complex<double> r3(-0.5,  sin(ang3));
  rcT                  theRamCanvas(IMGSIZ, IMGSIZ, -2.15/10.0, 1.85/10.0, -1.88/10.0, 1.89/10.0);

# pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    if ((y%100)==0)
#     pragma omp critical
      std::cout << "line " << y << " of " << IMGSIZ << std::endl;
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> z = theRamCanvas.int2real(x, y);
      double minAngleDelta1 = std::numbers::pi;
      double minAngleDelta2 = std::numbers::pi;
      double minAngleDelta3 = std::numbers::pi;
      for(int count=0; count<MAXITR; count++) {
        double modz = std::abs(z);
        if (modz<ZROEPS)
          break;
        z = (-pow(z, 0.6e1) + (0.2e1 * r + 0.4e1) * pow(z, 0.3e1) + r) * pow(z, -0.2e1) / (r + 0.1e1) / 0.3e1;
        double curAngle = std::arg(z);
        double curAngleDelta1 = std::abs(ang12-curAngle);
        double curAngleDelta2 = std::abs(ang13-curAngle);
        double curAngleDelta3 = std::min(std::abs(curAngle-ang23), std::abs(curAngle+ang23));
        if(curAngleDelta1 < minAngleDelta1) minAngleDelta1 = curAngleDelta1;
        if(curAngleDelta2 < minAngleDelta2) minAngleDelta2 = curAngleDelta2;
        if(curAngleDelta3 < minAngleDelta3) minAngleDelta3 = curAngleDelta3;
        if ((modz<ZROEPS) || (std::abs(z-r1)<ZROEPS) || (std::abs(z-r2)<ZROEPS) || (std::abs(z-r3)<ZROEPS))
          break;
      }
      rcccT r = static_cast<rcccT>(50.0*std::log(minAngleDelta1)/normer);
      rcccT g = static_cast<rcccT>(50.0*std::log(minAngleDelta2)/normer);
      rcccT b = static_cast<rcccT>(50.0*std::log(minAngleDelta3)/normer);
      theRamCanvas.drawPoint(x, y, rcT::colorType(r, g, b));
    }
  }

  theRamCanvas.applyHomoPixTfrm(&rcT::colorType::tfrmPow, 0.4);
  theRamCanvas.writeTIFFfile("newton_min_angle_starfish.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
