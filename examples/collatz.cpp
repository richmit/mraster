// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      collatz.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a mandelbrot-like fractal with the collatz map.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/collatz/index.html
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
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    NUMITR = 164;
  const int    IMXSIZ = 7680/2;
  const int    IMYSIZ = 7680/2;
  
  //mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -3.75, 3.75, -3.75, 3.75);            // 56  centered 0+0i
  //mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -0.99-0.15, -0.99+0.15, -0.15, 0.15); // 28  centered near 1+i
  mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -0.99-0.03, -0.99+0.03, -0.03, 0.03);   // 28  same, zoomed in

  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> z = theRamCanvas.int2real(x, y);
      int count = 0; 
      while((std::norm(z)<1e10) && (count<=NUMITR)) {
        z = 0.25 * (2.0 + 7.0*z - (2.0 + 5.0 * z) * std::cos(z * std::numbers::pi));        
        count++;
      }
      if(count < NUMITR)
        theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType::csCCsumRGB::c(static_cast<mjr::ramCanvas3c8b::csIntType>(count*28)));
    }
  }
  theRamCanvas.writeTIFFfile("collatz.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
