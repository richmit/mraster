// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      testFonts.cpp
 @author    Mitch Richling <http://www.mitchr.me>
 @brief     Draws all supported ASCII characters with all five Hershey fonts.@EOL
 @std       C++11
 @copyright 
  @parblock
  Copyright (c) 2015, Mitchell Jay Richling <http://www.mitchr.me> All rights reserved.

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

  const char *str1 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNO";
  const char *str2 = " PQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
  ramCanvas4c8b theRamCanvas = ramCanvas4c8b(1600, 540);
  theRamCanvas.set_yIntAxisOrientation(ramCanvas4c8b::axisOrientation::INVERTED);
  int y = 50;
  theRamCanvas.drawFillRectangle(0, 0, 2500, 600, "cyan");
  theRamCanvas.drawStringBox("GREEK_SL_SANSERIF", hersheyFont::ROMAN_SL_SANSERIF,  50, y, "red", "green", 1, 20);
  theRamCanvas.drawString(str1, hersheyFont::GREEK_SL_SANSERIF,  400, y, "red", 1, 20);  y+=50;
  theRamCanvas.drawString(str2, hersheyFont::GREEK_SL_SANSERIF,  400, y, "red", 1, 20);  y+=50;
  theRamCanvas.drawStringBox("GREEK_DL_SERIF",    hersheyFont::ROMAN_SL_SANSERIF,  50, y, "red", "green", 1, 20);
  theRamCanvas.drawString(str1, hersheyFont::GREEK_DL_SERIF,     400, y, "red", 1, 23); y+=50;
  theRamCanvas.drawString(str2, hersheyFont::GREEK_DL_SERIF,     400, y, "red", 1, 23); y+=50;
  theRamCanvas.drawStringBox("ROMAN_SL_SANSERIF", hersheyFont::ROMAN_SL_SANSERIF,  50, y, "red", "green", 1, 20);
  theRamCanvas.drawString(str1, hersheyFont::ROMAN_SL_SANSERIF,  400, y, "red", 1, 20); y+=50;
  theRamCanvas.drawString(str2, hersheyFont::ROMAN_SL_SANSERIF,  400, y, "red", 1, 20); y+=50;
  theRamCanvas.drawStringBox("ROMAN_DL_SERIF",    hersheyFont::ROMAN_SL_SANSERIF,  50, y, "red", "green", 1, 20);
  theRamCanvas.drawString(str1, hersheyFont::ROMAN_DL_SERIF,     400, y, "red", 1, 23); y+=50;
  theRamCanvas.drawString(str2, hersheyFont::ROMAN_DL_SERIF,     400, y, "red", 1, 23); y+=50;
  theRamCanvas.drawStringBox("ROMAN_TL_SERIF",    hersheyFont::ROMAN_SL_SANSERIF,  50, y, "red", "green", 1, 20);
  theRamCanvas.drawString(str1, hersheyFont::ROMAN_TL_SERIF,     400, y, "red", 1, 25); y+=50;
  theRamCanvas.drawString(str2, hersheyFont::ROMAN_TL_SERIF,     400, y, "red", 1, 25); y+=50;
  theRamCanvas.writeTGAfile("testFonts.tga");

}
