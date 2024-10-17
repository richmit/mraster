// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      newton_3updown.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Simplified code for Newton's Fractical.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/newton/index.html#threeupdown
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

  The standard Newton fractal is generated from @f$f=z^2-1@f$.  This function is continuous on the entire complex plain.  What do we get if we add poles
  in imaginary axis mirror locations of the roots?  i.e. for each root @f$x+iy@f$ of @f$f@f$, we add a pole at @f$-x+iy@f$?  The corresponding function is:
         @f[f=\frac{z^3-1}{z^3+1}@f]
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
  const int            MAXITR = 255;
  const int            COLMAG = 300;
  const int            CCLMAG = 300;
  const double         ZMAGMX = 1e10;
  const double         RELSIZ = 2.1;
  const double         XCENTR = 0.35;
  const double         YCENTR = 0.0;
  const double         ZROEPS = .0001;
  const int            IMGSIZ = 7680/1;
  const  double        r      = 1.0;
  std::complex<double> r1( 1.0,                        0.0);
  std::complex<double> r2(-0.5,  sin(2*std::numbers::pi/3));
  std::complex<double> r3(-0.5, -sin(2*std::numbers::pi/3));
  rcT                  theRamCanvas(IMGSIZ, IMGSIZ, XCENTR-RELSIZ, XCENTR+RELSIZ, YCENTR-RELSIZ, YCENTR+RELSIZ);

# pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
#   pragma omp critical
    if ((y%(IMGSIZ/100))==0)
      std::cout << "line " << y << " of " << IMGSIZ << std::endl;
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> z = theRamCanvas.int2real(x, y);
      for(int count=0; count<MAXITR; count++) {
        if(std::abs(z) < 2) {
          if(std::abs(z-r1) <= ZROEPS) {
            theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0R::c(count*CCLMAG)); break;
          } else if(std::abs(z-r2) <= ZROEPS) {                                                                    
            theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0G::c(count*CCLMAG)); break;
          } else if(std::abs(z-r3) <= ZROEPS) {                                          
            theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0B::c(count*CCLMAG)); break;
          } else if(std::abs(z) <= ZROEPS) {
            break;
          }
        } else {
          if(std::abs(z) > ZMAGMX) {
            theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0W::c(count*COLMAG)); break;
            break;
          }
        }
        z = (-pow(z, 0.6e1) + (0.2e1 * r + 0.4e1) * pow(z, 0.3e1) + r) * pow(z, -0.2e1) / (r + 0.1e1) / 0.3e1;
      }
    }
  }
  theRamCanvas.writeTIFFfile("newton_3updown.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
