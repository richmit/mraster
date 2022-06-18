// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      newton_bm_real.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark drawing a Newton fractal using real types and arithmetic.@EOL
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
  const mjr::ramCanvas3c8b::rcCordFlt pi       = 3.14159265359;
  int                                 MaxCount = 255;
  int                                 MultCol  = 15;
  mjr::ramCanvas3c8b::rcCordFlt       Tol      = (.0001 * .0001);
  mjr::ramCanvas3c8b                  theRamCanvas(4096, 4096, -2.0, 2, -2, 2); // -0.9, -0.7, -0.1, 0.1
  for(int y=0;y<theRamCanvas.get_numYpix();y++) {
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      mjr::ramCanvas3c8b::rcCordFlt zx = theRamCanvas.int2realX(x);
      mjr::ramCanvas3c8b::rcCordFlt zy = theRamCanvas.int2realY(y);
      int count = 0;
      while(count < MaxCount                                                  &&
            ((zx-1) * (zx-1) + zy * zy >= Tol)                                &&
            ((zx+.5) * (zx+.5) + (zy-sin(2*pi/3)) * (zy-sin(2*pi/3)) >= Tol)  &&
            ((zx+.5) * (zx+.5) + (zy+sin(2*pi/3)) * (zy+sin(2*pi/3)) >= Tol)) {
        mjr::ramCanvas3c8b::rcCordFlt botx = 3*(zx * zx - zy * zy);
        mjr::ramCanvas3c8b::rcCordFlt boty = 3*(2 * zx * zy);

        mjr::ramCanvas3c8b::rcCordFlt mag = botx * botx + boty * boty;
        if (mag > 0) {
          mjr::ramCanvas3c8b::rcCordFlt topx = (zx*zx*zx+-3.0*zx*zy*zy-1)/mag;
          mjr::ramCanvas3c8b::rcCordFlt topy = (3.0*zx*zx*zy-zy*zy*zy)/mag;

          zx = zx - (topx * botx + topy * boty);
          zy = zy - (topy * botx - topx * boty);
        }
        count++;
      }
      mjr::color3c8b::channelType cCol = static_cast<mjr::color3c8b::channelType>(255-count*MultCol);

      if((zx-1) * (zx-1) + zy * zy < Tol)
        theRamCanvas.drawPoint(x, y, mjr::color3c8b(cCol, 0, 0));
      else if((zx+.5) * (zx+.5) + (zy-sin(2*pi/3)) * (zy-sin(2*pi/3)) <= Tol)
        theRamCanvas.drawPoint(x, y, mjr::color3c8b(0, cCol, 0));
      else if((zx+.5) * (zx+.5) + (zy+sin(2*pi/3)) * (zy+sin(2*pi/3)) <= Tol)
        theRamCanvas.drawPoint(x, y, mjr::color3c8b(0, 0, cCol));
    }
  }
  theRamCanvas.writeTIFFfile("newton.tiff");
}
