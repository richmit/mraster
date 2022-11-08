// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      laguerre_3updown.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Simplified code for Newton's Fractical.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/newton/index.html#laguerre-pole
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

  Same as newton_3updown.cpp, but using Laguerre's method.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int            MAXITR = 255;
  const int            CCLMAG = 35;
  const double         ZMAGMX = 1e10;
  const double         YCENTR = 0.0;
  const double         ZROEPS = .0001;
  const int            IMGSIZ = 7680/1;
  const double         RELSIZ =  4.0; //  0.55;  14.5;  4.0;   0.15;
  const double         XCENTR =  0.5; //  -4.7;   1.5;  0.5;  -0.20;
  const double         r      =  1.0; // 100.0; 100.0;  1.0;  0.001;
  std::complex<double> r1( 1.0,                        0.0);
  std::complex<double> r2(-0.5,  sin(2*std::numbers::pi/3));
  std::complex<double> r3(-0.5, -sin(2*std::numbers::pi/3));
  mjr::ramCanvas3c8b theRamCanvas(IMGSIZ, IMGSIZ, XCENTR-RELSIZ, XCENTR+RELSIZ, YCENTR-RELSIZ, YCENTR+RELSIZ);

# pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
#   pragma omp critical
    if ((y%(IMGSIZ/100))==0)
      std::cout << "line " << y << " of " << IMGSIZ << std::endl;
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> z = theRamCanvas.int2real(x, y);
      for(int count=0; count<MAXITR; count++) {
        if(std::abs(z-r1) <= ZROEPS) {
          theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType::csCCu0R::c(count*CCLMAG)); break;
        } else if(std::abs(z-r2) <= ZROEPS) {                                                                    
          theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType::csCCu0G::c(count*CCLMAG)); break;
        } else if(std::abs(z-r3) <= ZROEPS) {                                          
          theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType::csCCu0B::c(count*CCLMAG)); break;
        } else if(std::abs(z) <= ZROEPS) {
          break;
        } else if(std::abs(z) > ZMAGMX) {
          break;
        }
        std::complex<double> G = 3.0 * z * z * (r + 1.0) / (pow(z, 3.0) - 1.0) / (pow(z, 3.0) + r);
        std::complex<double> ABR = 6.0 * sqrt((r + 1.0) * (2.0 * pow(z, 6.0) - pow(z, 3.0) + r) * z /
                                              pow(pow(z, 3.0) - 1.0, 2.0) / pow(pow(z, 3.0) + r, 2.0));
        std::complex<double> ABP = G + ABR;
        std::complex<double> ABN = G - ABR;
        std::complex<double> AB = (std::abs(ABP) > std::abs(ABN) ? ABP : ABN);
        z = z - 3.0 / AB;
      }
    }
  }
  theRamCanvas.writeTIFFfile("laguerre_3updown.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
