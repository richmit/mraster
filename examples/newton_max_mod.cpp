// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      newton_max_mod.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Newton Fractical -- color by root and max modulus.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/newton/index.html#maxmod
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
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b rcT;  // The Ram Canvas type we will use
typedef rcT::colorType rccT;     // The Ram Canvas color type
typedef rcT::csIntType rccsiT;   // The Ram Canvas color scheme index type

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int            MAXITR = 255;
  const int            COLMAG = 400;
  const double         ZROEPS = .0001;
  const int            IMGSIZ = 7680;
  std::complex<double> r1( 1.0,                        0.0);
  std::complex<double> r2(-0.5,  sin(2*std::numbers::pi/3));
  std::complex<double> r3(-0.5, -sin(2*std::numbers::pi/3));
  rcT                  theRamCanvas(IMGSIZ, IMGSIZ, -2.15, 1.85, -2.0, 2.0);

# pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> z = theRamCanvas.int2real(x, y);
      double maxMod = 0.0;
      for(int count=0; count<MAXITR; count++) {
        if(std::abs(z-r1) <= ZROEPS) {
          theRamCanvas.drawPoint(x, y, rccT::csCCu0R::c(static_cast<rccsiT>(255-maxMod*COLMAG))); break;
        } else if(std::abs(z-r2) <= ZROEPS) {                                                                    
          theRamCanvas.drawPoint(x, y, rccT::csCCu0G::c(static_cast<rccsiT>(255-maxMod*COLMAG))); break;
        } else if(std::abs(z-r3) <= ZROEPS) {                                          
          theRamCanvas.drawPoint(x, y, rccT::csCCu0B::c(static_cast<rccsiT>(255-maxMod*COLMAG))); break;
        } else if(std::abs(z) <= ZROEPS) {
          break;
        }
        if(abs(z)>maxMod)
          maxMod=abs(z);
        z = z-(z*z*z-1.0)/(z*z*3.0);
      }
    }
  }
  theRamCanvas.writeTIFFfile("newton_max_mod.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
