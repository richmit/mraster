// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      newton_roter.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Simplified code for Newton's Fractical.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/newton/index.html
 @copyright
  @parblock
  Copyright (c) 1988-2022, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

  Newton's method on (z^6-1)/(a^6*z^6+b).  The bottom specifies a set of 6 poles on a circle of radius b and centered at the origin.  The a variable is
  a modulus one complex number used to spin the poles around the circle like they orbit the origin.

     time convert -delay 1 -loop 0 -dispose previous newton_roter_???.tiff newton_roter.gif

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b rcT;    // The Ram Canvas type we will use

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int                  MAXITR = 255;
  const int                  CCLMAG = 130;
  const int                  DCLMAG = 30;
  const int                  NUMFRM = 4*8;
  const double               ZMAGMX = 1e10;
  const double               RELSIZ = 7.0;
  const double               XCENTR = 0.0;
  const double               YCENTR = 0.0;
  const double               ZROEPS = .0001;
  const int                  IMGSIZ = 7680/16;
  const std::complex<double> r1( 1.0,                             0.0);
  const std::complex<double> r2(-0.5,  std::sin(2*std::numbers::pi/3));
  const std::complex<double> r3(-0.5, -std::sin(2*std::numbers::pi/3));

# pragma omp parallel for schedule(static,1)
  for(int frame=0; frame<NUMFRM; frame++) {
#   pragma omp critical
    std::cout << "frame " << (frame+1) << " of " << NUMFRM << std::endl;
    rcT theRamCanvas(IMGSIZ, IMGSIZ, XCENTR-RELSIZ, XCENTR+RELSIZ, YCENTR-RELSIZ, YCENTR+RELSIZ);
    double angle = 2.0*std::numbers::pi/6.0/NUMFRM*frame;
    std::complex<double> a(std::cos(angle), std::sin(angle));
    double b = 1e-2;
    for(int y=0;y<theRamCanvas.getNumPixY();y++) {
      for(int x=0;x<theRamCanvas.getNumPixX();x++) {
        std::complex<double> z  = theRamCanvas.int2real(x, y);
        std::complex<double> zL = z + 100.0;
        for(int count=0; count<MAXITR; count++) {
          if(std::abs(z-zL) <= ZROEPS) {
            theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0R::c(count*CCLMAG)); break;
          } else if(std::abs(z) <= ZROEPS) {
            break;
          } else if(std::abs(z) > ZMAGMX) {
            theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0W::c(count*DCLMAG)); break;
            break;
          }
          zL = z;
          if (b<1e11)
            z = (-pow(a, 6.0) * pow(z, 12.0) + (7.0 * pow(a, 6.0) + (5.0 * b)) * pow(z, 6.0) + b) / 
                pow(z, 5.0) / (pow(a, 6.0) + b) / 6.0;
          else
            z = (5.0 * pow(z, 6.0) + 1.0) / pow(z, 5.0) / 6.0;
        }
      }
    }
    theRamCanvas.writeTIFFfile("newton_roter_" + mjr::fmtInt(frame, 3, '0') + ".tiff");
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
