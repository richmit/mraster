// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_precomp.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Produce several images related to the period/cycle structure of the Mandelbrot set.@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 1988-2015,2021 Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

typedef mjr::ramCanvas1c16b rcCNT;  // for counts!
typedef mjr::ramCanvas3c8b  rcC8;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  rcC8::colorType limitColor("red");
  rcC8::colorType perColor("blue");
  rcC8::colorType setColor("yellow");

  const int                  MCSIZE   = 7680;
  const int                  CSIZEF   = 1;
  const int                  CSIZE    = MCSIZE/CSIZEF;
  rcC8  theRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);
  rcCNT perRamCanvas;
  rcCNT stbRamCanvas;

  perRamCanvas.readTIFFfile("../precomp/mandelbrot_precompPER.tiff");
  stbRamCanvas.readTIFFfile("../precomp/mandelbrot_precompSTB.tiff");
#pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      auto inten = theRamCanvas.getPxColorNC(x, y).intensity();
      auto period = perRamCanvas.getPxColorNC(x, y).getC0();
      if (period > 0) {
        if (inten == 0)
          theRamCanvas.drawPoint(x, y, setColor);          
        auto itrreq = stbRamCanvas.getPxColorNC(x, y).getC0();
        std::complex<double> c(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));
        std::complex<double> z(0.0, 0.0);
        rcCNT::colorChanType count = 1;
        while (count<itrreq) {
          z=std::pow(z, 2) + c;
          count++;
        }
        count = 0;
        while (count<period) {
          z=std::pow(z, 2) + c;
          theRamCanvas.drawPoint(std::real(z), std::imag(z), limitColor);
          count++;
        }
      }
    }
    std::cout << y << std::endl;
  }

perRamCanvas.writeTIFFfile("tmp.tiff");

  theRamCanvas.writeTIFFfile("mandelbrot_precomp_p1_br.tiff");
  theRamCanvas.rotate90CCW();
  theRamCanvas.writeTIFFfile("mandelbrot_precomp_p1_ar.tiff");
  theRamCanvas.scaleDownMean(4);
  theRamCanvas.writeTIFFfile("mandelbrot_precomp_p1.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
