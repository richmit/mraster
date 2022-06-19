// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      test_draw_glyph.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draws all supported ASCII characters with all five Hershey fonts.@EOL
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

int main(void) {

  mjr::ramCanvas3c8b theRamCanvasNN(511, 511);
  theRamCanvasNN.set_xIntAxisOrientation(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  theRamCanvasNN.set_yIntAxisOrientation(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  theRamCanvasNN.drawLine(0, 255, 511, 255, "blue");
  theRamCanvasNN.drawLine(255, 0, 255, 511, "blue");
  theRamCanvasNN.drawHersheyGlyph(518, 255, 255,  1,  1, "red");
  theRamCanvasNN.drawHersheyGlyph(518, 255, 255,  2,  2, "red");
  theRamCanvasNN.drawHersheyGlyph(518, 255, 255,  4,  4, "red");
  theRamCanvasNN.drawHersheyGlyph(518, 255, 255,  8,  8, "red");
  theRamCanvasNN.drawHersheyGlyph(518, 255, 255, 16, 16, "red");
  theRamCanvasNN.writeTIFFfile("test_draw_glyph_NN.tiff");

  mjr::ramCanvas3c8b theRamCanvasIN(511, 511);
  theRamCanvasIN.set_xIntAxisOrientation(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  theRamCanvasIN.set_yIntAxisOrientation(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  theRamCanvasIN.drawLine(0, 255, 511, 255, "blue");
  theRamCanvasIN.drawLine(255, 0, 255, 511, "blue");
  theRamCanvasIN.drawHersheyGlyph(518, 255, 255,  1,  1, "red");
  theRamCanvasIN.drawHersheyGlyph(518, 255, 255,  2,  2, "red");
  theRamCanvasIN.drawHersheyGlyph(518, 255, 255,  4,  4, "red");
  theRamCanvasIN.drawHersheyGlyph(518, 255, 255,  8,  8, "red");
  theRamCanvasIN.drawHersheyGlyph(518, 255, 255, 16, 16, "red");
  theRamCanvasIN.writeTIFFfile("test_draw_glyph_NI.tiff");

  mjr::ramCanvas3c8b theRamCanvasNI(511, 511);
  theRamCanvasNI.set_xIntAxisOrientation(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  theRamCanvasNI.set_yIntAxisOrientation(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  theRamCanvasNI.drawLine(0, 255, 511, 255, "blue");
  theRamCanvasNI.drawLine(255, 0, 255, 511, "blue");
  theRamCanvasNI.drawHersheyGlyph(518, 255, 255,  1,  1, "red");
  theRamCanvasNI.drawHersheyGlyph(518, 255, 255,  2,  2, "red");
  theRamCanvasNI.drawHersheyGlyph(518, 255, 255,  4,  4, "red");
  theRamCanvasNI.drawHersheyGlyph(518, 255, 255,  8,  8, "red");
  theRamCanvasNI.drawHersheyGlyph(518, 255, 255, 16, 16, "red");
  theRamCanvasNI.writeTIFFfile("test_draw_glyph_IN.tiff");

  mjr::ramCanvas3c8b theRamCanvasII(511, 511);
  theRamCanvasII.set_xIntAxisOrientation(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  theRamCanvasII.set_yIntAxisOrientation(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  theRamCanvasII.drawLine(0, 255, 511, 255, "blue");
  theRamCanvasII.drawLine(255, 0, 255, 511, "blue");
  theRamCanvasII.drawHersheyGlyph(518, 255, 255,  1,  1, "red");
  theRamCanvasII.drawHersheyGlyph(518, 255, 255,  2,  2, "red");
  theRamCanvasII.drawHersheyGlyph(518, 255, 255,  4,  4, "red");
  theRamCanvasII.drawHersheyGlyph(518, 255, 255,  8,  8, "red");
  theRamCanvasII.drawHersheyGlyph(518, 255, 255, 16, 16, "red");
  theRamCanvasII.writeTIFFfile("test_draw_glyph_II.tiff");
}
