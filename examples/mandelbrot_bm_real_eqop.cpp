// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      mandelbrot_bm_real_eqop.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark drawing a mandelbrot set using floating point types and arithmetic only.@EOL
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

  Basic benchmark.  Uses only real numbers.  Reduces operation count by rearranging the equations a bit.
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

int main(void) {
  const int NUMITR = 1024;
  mjr::ramCanvas3c8b theRamCanvas(7680, 7680, -2.2, 0.8, -1.5, 1.5);

  for(int y=0;y<theRamCanvas.get_numYpix();y++) {
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
        mjr::ramCanvas3c8b::rcCordFlt xr = theRamCanvas.int2realX(x);
        mjr::ramCanvas3c8b::rcCordFlt yr = theRamCanvas.int2realY(y);
        mjr::ramCanvas3c8b::rcCordFlt zx = 0.0;
        mjr::ramCanvas3c8b::rcCordFlt zy = 0.0;
        mjr::ramCanvas3c8b::rcCordFlt zx2, zy2, tmp;
        int count = 0;
        do {
          zx2 = zx * zx;
          zy2 = zy * zy;
          tmp = zx2-zy2+xr;
          zy = 2*zx*zy+yr;
          zx = tmp;
          count++;
        } while( (zx2+zy2<4) && (count<NUMITR) );
        if(count < NUMITR)
          theRamCanvas.drawPoint(x, y, mjr::color3c8b().cmpFireRamp(mjr::intWrap(count*20, 767)));
    }
  }
  theRamCanvas.writeTIFFfile("mandelbrot_bm_real_eqop.tiff");
}


