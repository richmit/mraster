// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      mandelbrot_bm_real.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark drawing a mandelbrot set using doubleing point types and arithmetic only.@EOL
 @std       C++98
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

  Basic benchmark.  Uses only real numbers.
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

int main(void) {
  auto startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  int count;
  const int NUMITR = 1024;
  mjr::ramCanvas3c8b::coordFltType xr, yr, zx, zy, tempx;
  mjr::ramCanvas3c8b theRamCanvas(7680, 7680, -2.2, 0.8, -1.5, 1.5);

  for(int x=0;x<theRamCanvas.get_numXpix();x++) {
    for(int y=0;y<theRamCanvas.get_numYpix();y++) {
      for(xr=theRamCanvas.int2realX(x),yr=theRamCanvas.int2realY(y),zx=zy=0.0,count=0; (zx*zx+zy*zy<4)&&(count<=NUMITR); count++,tempx=zx*zx-zy*zy+xr,zy=2*zx*zy+yr,zx=tempx)
        ;
      if(count < NUMITR)
        theRamCanvas.drawPoint(x, y, mjr::color3c8b().cmpFireRamp(mjr::intWrap(count*20, 767)));
    }
  }
  theRamCanvas.writeTIFFfile("mandelbrot_bm_real.tiff");
  std::cout << "Runtime " << static_cast<double>(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) - startTime)/(60.0) << " min" << std::endl;
}
