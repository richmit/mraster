// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      tricorn.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw the classic tricorn fractal.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/mandelbrot/index.html
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
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    NUMITR = 1024;
  const int    IMXSIZ = 7680/2;
  const int    IMYSIZ = 7680/2;

  mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -2.75, 2.75, -2.75, 2.75);      // The whole thing
  //mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -2.1, -0.30, -0.25, 0.25);      // The "corn"
  //mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -1.65, -1.46, -0.07, 0.07);  // Tiny tricorns & mandelbrots
  //mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -1.48-0.0065, -1.48+0.007, -0.0035, 0.0035); // That biggest mandelbrot-like set from above

  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> c(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));
      std::complex<double> z(0.0, 0.0);
      int count = 0; 
      while((std::norm(z)<14) && (count<=NUMITR)) {
        z=std::pow(std::conj(z), 2) + c;
        count++;
      }
      if(count < NUMITR)
        theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType::csCColdeFireRamp::c(static_cast<mjr::ramCanvas3c8b::csIntType>(count*30)));
    }
  }
  theRamCanvas.writeTIFFfile("tricorn.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
