// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_minOrbit.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Simple Mandelbrot set with interior color based orbit distance from the origin.@EOL
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
 @filedetails

  Color the *inside* of the mandelbrot set using the distance from the point's orbit to the origion.

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b::colorType ct;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    IMGSIZ = 7680/4;
  const int    MAXITR = 1024;
  const double MAXZSQ = 4.0;
  mjr::ramCanvas3c8b theRamCanvas(IMGSIZ, IMGSIZ, -2.2, 0.8, -1.5, 1.5);

#pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> c = theRamCanvas.int2real(x, y);
      std::complex<double> z(0.0, 0.0);
      int count = 0; 
      double minAbs = 5.0;
      while((std::norm(z)<MAXZSQ) && (count<=MAXITR)) {
        z=std::pow(z, 2) + c;
        count++;
        if (std::norm(z) < minAbs)
          minAbs = std::norm(z);
      }
      if(count < MAXITR)
        theRamCanvas.drawPoint(x, y, decltype(theRamCanvas)::colorType::csCColdeFireRamp::c(static_cast<decltype(theRamCanvas)::csIntType>(count*30)));
      else
        theRamCanvas.drawPoint(x, y, decltype(theRamCanvas)::colorType::csCCwicC::c(static_cast<decltype(theRamCanvas)::csFltType>(minAbs*50)));
    }
  }
  theRamCanvas.writeTIFFfile("mandelbrot_minOrbit.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
