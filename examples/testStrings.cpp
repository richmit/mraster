// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      testStrings.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Test string rendering both with a box and without.@EOL
 @std       C++11
 @copyright 
  @parblock
  Copyright (c) 2015, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

using namespace mjr;

int main(void) {
  int y;

  ramCanvas4c8b theRamCanvas1 = ramCanvas4c8b(700, 240);
  theRamCanvas1.set_yIntAxisOrientation(ramCanvas4c8b::axisOrientation::INVERTED);
  theRamCanvas1.drawLine(100, 0,  100, 512, "blue");
  y = 50;
  theRamCanvas1.drawLine(0, y,   1024, y, "blue");  
  theRamCanvas1.drawString("Hello, World!", hersheyFont::ROMAN_SL_SANSERIF, 100, y, "red",  1, 16);
  y+=50;
  theRamCanvas1.drawLine(0, y,   1024, y, "blue");  
  theRamCanvas1.drawString("Hello, World!", hersheyFont::ROMAN_SL_SANSERIF, 100, y, "red",  2, 15);
  y+=75;
  theRamCanvas1.drawLine(0, y,   1024, y, "blue");  
  theRamCanvas1.drawString("Hello, World!", hersheyFont::ROMAN_SL_SANSERIF, 100, y, "red",  3, 15);
  theRamCanvas1.writeTGAfile("testStrings_1.tga");

  ramCanvas4c8b theRamCanvas2 = ramCanvas4c8b(740, 420);
  theRamCanvas2.set_yIntAxisOrientation(ramCanvas4c8b::axisOrientation::INVERTED);
  y = 50;
  theRamCanvas2.drawStringBox("Hello, World!", hersheyFont::ROMAN_SL_SANSERIF, 100, y, "red", "green",  1, 16);
  theRamCanvas2.drawLine(0, y,   1024, y, "blue");  
  y+=100;
  theRamCanvas2.drawStringBox("Hello, World!", hersheyFont::ROMAN_SL_SANSERIF, 100, y, "red", "green",  2, 15);
  theRamCanvas2.drawLine(0, y,   1024, y, "blue");  
  y+=160;
  theRamCanvas2.drawStringBox("Hello, World!", hersheyFont::ROMAN_SL_SANSERIF, 100, y, "red", "green",  3, 15);
  theRamCanvas2.drawLine(0, y,   2024, y, "blue");  
  theRamCanvas2.drawLine(100, 0,  100, 512, "blue");
  theRamCanvas2.writeTGAfile("testStrings_2.tga");

}
