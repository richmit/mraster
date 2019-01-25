// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      mandelbrot_grayscale.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a grayscale Mandelbrot Set.@EOL
 @std       C++14
 @copyright 
  @parblock
  Copyright (c) 1988-2015,2018 Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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
***************************************************************************************************************************************************************/

// Draw a grayscale Mandelbrot set.
// We illustrate:
//   - How to create and use a grayscale canvas
//   - An optimization to make drawing the set faster
//   - How to losslessly stretch an image histogram to the limits

#include "ramCanvas.hpp"

#include <complex>                                                       /* STL algorithm           C++11    */

int main(void) {
  mjr::ramCanvas1c16b theRamCanvas(7680, 7680, -2.2, 0.8, -1.5, 1.5);
  int count;
  const int NUMITR = mjr::ramCanvas1c16b::rcColor::maxChanVal / 32;
  float cr, ci;
  std::complex<float> c, z, zero(0.0, 0.0);  
  for(int y=0;y<theRamCanvas.get_numYpix();y++) {
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      cr = theRamCanvas.int2realX(x);
      ci = theRamCanvas.int2realY(y);
      c  = std::complex<float>(cr, ci);
      float p = abs(c-0.25f);
      if((cr >= p-2.0f*p*p+0.25f) && abs(c+1.0f) >= 0.25f) {
        for(z=zero,count=0; (std::norm(z)<4)&&(count<=NUMITR); count++,z=z*z+c)
          ;
        if(count < NUMITR)
          theRamCanvas.drawPoint(x, y, count*100);
      }
    }
  }
  theRamCanvas.autoHistStrech();
  theRamCanvas.writeTIFFfile("mandelbrot_grayscale.tiff");
}
