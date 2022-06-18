// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      test_draw_misc.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Illustrate and test simple drawing functions.@EOL
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
  mjr::color3c8b aColor;
  mjr::ramCanvas3c8b theRamCanvas(1024, 1024, -1, 1, 2, 2);

  theRamCanvas.setDfltColor(mjr::color3c8b("white"));
  theRamCanvas.drawRectangle(3, 3, 23, 23);
  theRamCanvas.drawRectangle(0, 0, 20, 20);
  theRamCanvas.drawRectangle(-10, -10, 50, 50);

  theRamCanvas.setDfltColor(mjr::color3c8b("blue"));
  theRamCanvas.drawFillRectangle(60, 60, 80, 80);
  theRamCanvas.drawFillRectangle(400, 400, 600, 600);


  theRamCanvas.drawFillTriangle(10, 700, 20, 600, 50, 650, mjr::color3c8b("green"));
  theRamCanvas.drawFillTriangle(50, 750, 60, 650, 20, 700, mjr::color3c8b("green"));
  theRamCanvas.drawFillTriangle(100, 650, 150, 650, 120, 700, mjr::color3c8b("green"));
  theRamCanvas.drawFillTriangle(150, 700, 200, 700, 180, 650, mjr::color3c8b("green"));

  theRamCanvas.setDfltColor("red");
  for(int y=-75;y<75;y+=3) {
    theRamCanvas.drawLine(400, 200, 400+150, 200+y);
    theRamCanvas.drawLine(400, 200, 400-150, 200+y);
    theRamCanvas.drawLine(400, 200, 400+y,   200+150);
    theRamCanvas.drawLine(400, 200, 400+y,   200-150);
  }

  theRamCanvas.drawLine(-20, -10, 70, 60);

  for(int y=-10;y<50;y+=5) {
    theRamCanvas.drawTriangle(20, 200, y, 200+30, 30, 300);
  }

  theRamCanvas.setDfltColor(mjr::color3c8b("green"));
  for(int r=10;r<50;r+=5)
    theRamCanvas.drawCircle(200, 250, r);

  theRamCanvas.drawFillCircle(150, 150, 50);

  // Check out some of they ways to specify color (more exist)!
  theRamCanvas.drawFillCircle(70, 400, 50, "red");
  theRamCanvas.drawFillCircle(70, 400, 40, "#ff00ff");
  theRamCanvas.drawFillCircle(70, 400, 30, mjr::color3c8b::cornerColor::BLUE);
  theRamCanvas.drawFillCircle(70, 400, 10, mjr::color3c8b(0xff, 0xff, 0x00));

  theRamCanvas.writeTIFFfile("test_draw_misc.tiff");
}
