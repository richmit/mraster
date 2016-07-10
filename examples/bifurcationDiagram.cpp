// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      bifurcationDiagram.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draws a mandelbrot set using the C++ complex type.@EOL
 @std       C++14
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
#include <complex>

using namespace mjr;

int main(void) {
  ramCanvas1c16b theRamCanvas(7680, 7680, 2.5, 4, -0.1, 1.1);
  for(ramCanvas1c16b::rcCordFlt r=theRamCanvas.get_minRealX(); r<theRamCanvas.get_maxRealX(); r+=theRamCanvas.get_xPixWid()/20) {
    ramCanvas1c16b::rcCordFlt f = 0.5;
    ramCanvas1c16b::rcCordInt x  = theRamCanvas.real2intX(r);
    for(int i=0; i<5000 && std::abs(f)<100; i++) {
      f = r*f*(1-f);
      if(i>1000) {
        ramCanvas1c16b::rcCordInt y = theRamCanvas.real2intY(f);
        theRamCanvas.drawPoint(x, y, theRamCanvas.getPxColor(x, y).tfrmAddClp(color1c16b(600)));
      }
    }
  }
  theRamCanvas.writeTGAfile("bifurcationDiagram.tga");
}
