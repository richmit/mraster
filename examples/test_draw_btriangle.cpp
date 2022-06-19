// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      test_draw_btriangle.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Illustrate and test barycentric interpolation.@EOL
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

int main(void) {
  const int s = 1; // Set to 10 for high res image (test smoothness), set to 1 for low resolution (test pixel level detail)
  const int c = 11 - s;
  static_assert(s<11 && s>0, "ERROR: s must be in [1, 10].");

  mjr::ramCanvas3c8b theRamCanvas(s*170, s*100);
  mjr::ramCanvas3c8b::coordIntType x = 0, y = 0;
  x = 0;
  theRamCanvas.drawFillTriangle(90*s+x, 40*s+y, 10*s+x, 10*s+y, 60*s+x, 90*s+y, "green", "red",   "blue");
  theRamCanvas.drawTriangle    (90*s+x, 40*s+y, 10*s+x, 10*s+y, 60*s+x, 90*s+y, "white");
  x += 70*s;
  theRamCanvas.drawFillTriangle(10*s+x, 10*s+y, 90*s+x, 40*s+y, 60*s+x, 90*s+y, "red",   "green", "blue");
  theRamCanvas.drawTriangle    (10*s+x, 10*s+y, 90*s+x, 40*s+y, 60*s+x, 90*s+y, "white");
  theRamCanvas.scaleUpProximal(c);
  theRamCanvas.writeTIFFfile("test_draw_btriangle.tiff");
}
