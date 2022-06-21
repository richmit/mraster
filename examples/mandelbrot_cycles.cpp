// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      mandelbrot_cycles.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark drawing a mandelbrot set using the C++ complex type and excluding hypocycloids.@EOL
 @std       C++98
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
 @filedetails

  Color points based on qualitative sequence behavior: Tends to infinity (reds), cyclic (blues), or converges (greens).  The method for detecting cycles and
  fixed points is not perfect, but makes a nice picture.  The color intensity is the length of time it took to make the behavior determination.
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <algorithm>                                                     /* STL algorithm           C++11    */
#include <chrono>                                                        /* time                    C++11    */
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <vector>                                                        /* STL vector              C++11    */

int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b::colorType aColor;

  const int NUMITR   = 16*16*4*4;
  const int CSIZE    = 7680/2;
  const int LASTSIZE = 16*16*4;
  mjr::ramCanvas3c8b theRamCanvas(CSIZE, CSIZE, -1.45, 0.5, -1.05, 1.05);

  for(int y=0;y<theRamCanvas.get_numYpix();y++) {
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      int count, lastIdx=0;
      double cr = theRamCanvas.int2realX(x);
      double ci = theRamCanvas.int2realY(y);
      std::complex<double> c(cr, ci), z(cr, ci);
      std::vector<std::complex<double>> lastZs(LASTSIZE, std::complex<double>(cr, ci));
      for(count=0; ; count++) {
        z = z * z + c;
        if(count>=NUMITR) {                                                                                            // Ran too long
          theRamCanvas.drawPoint(x, y, "white");
          break;
        }
        if(std::norm(z)>2.0) {                                                                                         // Got too big
          theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(static_cast<mjr::ramCanvas3c8b::colorChanType>((2*count+20>255 ? 255 : count+20)), 0, 0));
          break;
        }
        if(std::abs(z-lastZs[lastIdx])<0.01) {                                                                         // Converged
          theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(0, static_cast<mjr::ramCanvas3c8b::colorChanType>((count+20>255 ? 255 : count+20)), 0));
          break;
        }
        if(std::any_of(lastZs.begin(), lastZs.end(), [&z](std::complex<double> zl){return std::abs(zl-z)<0.0001;}) ) { // Cycle
          theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(0, 0, static_cast<mjr::ramCanvas3c8b::colorChanType>((count+50>255 ? 255 : count+50))));
          break;
        }
        lastIdx = (lastIdx+1)%LASTSIZE;
        lastZs[lastIdx] = z;
      }
    }
    std::cout << CSIZE << "/" << y << std::endl;
  }
  theRamCanvas.writeTIFFfile("mandelbrot_cycles.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
