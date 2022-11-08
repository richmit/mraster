// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      newton_z6.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Newton Fractical for \f$z^6\f$.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/newton/index.html#z6
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
typedef mjr::ramCanvas3c8b rcT;    // The Ram Canvas type we will use

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  constexpr  int              COLMAG = 25;
  constexpr rcT::coordIntType IMGSIZ = 7680;
  constexpr int               MAXITR = 155;
  constexpr rcT::coordFltType ZROEPS = 1.0e-5;
  constexpr rcT::cplxFltType  r1( 1.0,  0.0);
  constexpr rcT::cplxFltType  r2(-0.5,  std::sin(2.0*std::numbers::pi/3.0));
  constexpr rcT::cplxFltType  r3(-0.5, -std::sin(2.0*std::numbers::pi/3.0));
  constexpr rcT::cplxFltType  r4(-1.0,  0.0);
  constexpr rcT::cplxFltType  r5( 0.5,  std::sin(2.0*std::numbers::pi/3.0));
  constexpr rcT::cplxFltType  r6( 0.5, -std::sin(2.0*std::numbers::pi/3.0));

  rcT theRamCanvas(IMGSIZ, IMGSIZ, -1.20, 1.20, -1.20, 1.20);

# pragma omp parallel for schedule(static,1)
  for(rcT::coordIntType y=0;y<theRamCanvas.getNumPixY();y++) {
    for(rcT::coordIntType x=0;x<theRamCanvas.getNumPixX();x++) {
      rcT::cplxFltType z = theRamCanvas.int2real(x, y);
      for(int count=0; count<MAXITR; count++) {
        if(std::abs(z-r1) <= ZROEPS) {
          theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0R::c(255-count*COLMAG)); break;
        } else if(std::abs(z-r2) <= ZROEPS) {                                                                    
          theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0G::c(255-count*COLMAG)); break;
        } else if(std::abs(z-r3) <= ZROEPS) {                                          
          theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0B::c(255-count*COLMAG)); break;
        } else if(std::abs(z-r4) <= ZROEPS) {
          theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0M::c(255-count*COLMAG)); break;
        } else if(std::abs(z-r5) <= ZROEPS) {
          theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0C::c(255-count*COLMAG)); break;
        } else if(std::abs(z-r6) <= ZROEPS) {
          theRamCanvas.drawPoint(x, y, rcT::colorType::csCCu0Y::c(255-count*COLMAG)); break;
        } else if(std::abs(z) <= ZROEPS) {
          break;
        }
        rcT::cplxFltType tmp = pow(z, 5);
        z = z-(tmp*z-1.0)/(6.0*tmp);
      }
    }
  }
  /* The biggest reason homogeneous transforms are in the library is to support color scale correction.  */
  theRamCanvas.applyHomoPixTfrm(&rcT::colorType::tfrmLinearGreyLevelScale, 255.0 / 155, 0.0);
  theRamCanvas.autoHistStrech();
  theRamCanvas.writeTIFFfile("newton_z6.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
