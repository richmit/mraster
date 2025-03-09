// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandeldragon.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Simple rendering of the mandeldragon fractal.@EOL
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

  The mandeldragon fractal is drawn using the same basic algorithm as the mandelbrot fractal, but using a different formula to iterate:

  @f[ z_{n+1} = (c + 1) \cdot z_n \cdot (1 - z_n) @f]

  With 

  @f[ z_0 = \frac{1}{2}  @f]

  The mandeldragon lives in a ball of radius 5 centered at the origin, so we can use this as a test for set inclusion.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();

  const int    maxitr = 1024;
  const double maxzsq = 10.0; 
  const int    width  = 7680/2;
  const int    height = 4320/2;
  const double ar     = static_cast<double>(width) / static_cast<double>(height);
  mjr::ramCanvas3c8b theRamCanvas(width, height, -3.3, 3.3, -3.3/ar, 3.3/ar);

#pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> c = theRamCanvas.int2real(x, y);
      std::complex<double> z(0.5, 0.0);
      int count = 0; 
      while((std::norm(z)<maxzsq) && (count<=maxitr)) {
        z = (c + 1.0) * z * (1.0 - z);
        count++;
      }
      if(count < maxitr)
        theRamCanvas.drawPoint(x, y, decltype(theRamCanvas)::colorType::csCColdeFireRamp::c(static_cast<decltype(theRamCanvas)::csIntType>(count*10)));
    }
  }

  theRamCanvas.writeTIFFfile("mandeldragon.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
