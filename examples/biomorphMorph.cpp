// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      biomorphMorph.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw the classic biomorphMorph fractal.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/biomorphMorph/index.html
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
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathSTR.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b::colorType ct;
typedef ct::csIntType cit;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    NUMITR = 7;
  const int    NUMFRM = 24*4;
  const int    IMXSIZ = 7680/4;
  const int    IMYSIZ = 7680/4;
  const int    LIM    = 10;

  mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -2.75, 2.75, -2.75, 2.75);
  for(int frame=0; frame<NUMFRM; frame++) {
    std::cout << "Frame: " << frame << std::endl;
    double angle = frame*std::numbers::pi*2/NUMFRM;    
    theRamCanvas.clrCanvasToBlack();
    for(int y=0;y<theRamCanvas.getNumPixY();y++) {
      for(int x=0;x<theRamCanvas.getNumPixX();x++) {
        std::complex<double> c(std::cos(angle), std::sin(angle));
        std::complex<double> z = theRamCanvas.int2real(x, y);
        std::complex<double> zL(0.0, 0.0);
        int count = 0; 
        while( ((std::abs(std::real(z))<LIM) || (std::abs(std::imag(z))<LIM)) && (count<NUMITR) ) {
          zL = z;
          z=std::sin(z) + std::pow(z, 2) + c;
          count++;
        }
        if(count < NUMITR) {
          if(std::abs(std::real(zL)) < LIM)
            theRamCanvas.drawPoint(x, y, ct::csCCu0W::c(std::abs(std::real(zL))/LIM));
          else if(std::abs(std::imag(zL)) < LIM)
            theRamCanvas.drawPoint(x, y, ct::csCCu0W::c(1.0-std::abs(std::imag(zL))/LIM));
        } else {
          if(std::abs(std::real(zL)) < LIM)
            theRamCanvas.drawPoint(x, y, ct::csCCu0Y::c(std::abs(std::real(zL))/LIM));
          else if(std::abs(std::imag(zL)) < LIM)
            theRamCanvas.drawPoint(x, y, ct::csCCu0Y::c(1.0-std::abs(std::imag(zL))/LIM));
        }
      }
    }
    theRamCanvas.writeTIFFfile("biomorphMorph_" + mjr::math::str::fmt_int(frame, 3, '0') + ".tiff");
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
