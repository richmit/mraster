// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      r_draw_glyph.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2025-01-25
 @brief     Unit tests ramCanvas.@EOL
 @keywords  GTest
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 2022-2025, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.

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
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

#include <gtest/gtest.h>
#include "ramCanvas.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(r_draw_glyph, comprehensive) {

  // Make sure glyphs render right side up and forward.  The images in RAM will differ, but the *FILES* should be identical.

  mjr::ramCanvas3c8b aRamCanvas(127, 127); mjr::ramCanvas3c8b R1aRamCanvas(127, 127); mjr::ramCanvas3c8b R2aRamCanvas(127, 127);
  aRamCanvas.drawLine(0, 63, 127, 63, "blue");
  aRamCanvas.drawLine(63, 0, 63, 127, "blue");
  aRamCanvas.setIntAxOrientationX(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  aRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  aRamCanvas.drawHersheyGlyph(505, 63, 63,  1,  1, "red");
  aRamCanvas.drawHersheyGlyph(505, 63, 63,  2,  2, "red");
  aRamCanvas.drawHersheyGlyph(505, 63, 63,  4,  4, "red");

  aRamCanvas.writeRAWfile("ut-glyph_axis-a.mrw");
  aRamCanvas.scaleUpProximal(4);
  aRamCanvas.writeTIFFfile("ut-glyph_axis-a.tiff");

  mjr::ramCanvas3c8b bRamCanvas(127, 127); mjr::ramCanvas3c8b R1bRamCanvas(127, 127); mjr::ramCanvas3c8b R2bRamCanvas(127, 127);
  bRamCanvas.drawLine(0, 63, 127, 63, "blue");
  bRamCanvas.drawLine(63, 0, 63, 127, "blue");
  bRamCanvas.setIntAxOrientationX(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  bRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  bRamCanvas.drawHersheyGlyph(505, 63, 63,  1,  1, "red");
  bRamCanvas.drawHersheyGlyph(505, 63, 63,  2,  2, "red");
  bRamCanvas.drawHersheyGlyph(505, 63, 63,  4,  4, "red");
  
  bRamCanvas.writeRAWfile("ut-glyph_axis-b.mrw");
  bRamCanvas.scaleUpProximal(4);
  bRamCanvas.writeTIFFfile("ut-glyph_axis-b.tiff");

  mjr::ramCanvas3c8b cRamCanvas(127, 127); mjr::ramCanvas3c8b R1cRamCanvas(127, 127); mjr::ramCanvas3c8b R2cRamCanvas(127, 127);
  cRamCanvas.drawLine(0, 63, 127, 63, "blue");
  cRamCanvas.drawLine(63, 0, 63, 127, "blue");
  cRamCanvas.setIntAxOrientationX(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  cRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  cRamCanvas.drawHersheyGlyph(505, 63, 63,  1,  1, "red");
  cRamCanvas.drawHersheyGlyph(505, 63, 63,  2,  2, "red");
  cRamCanvas.drawHersheyGlyph(505, 63, 63,  4,  4, "red");

  cRamCanvas.writeRAWfile("ut-glyph_axis-c.mrw");
  cRamCanvas.scaleUpProximal(4);
  cRamCanvas.writeTIFFfile("ut-glyph_axis-c.tiff");

  mjr::ramCanvas3c8b dRamCanvas(127, 127); mjr::ramCanvas3c8b R1dRamCanvas(127, 127); mjr::ramCanvas3c8b R2dRamCanvas(127, 127);
  dRamCanvas.drawLine(0, 63, 127, 63, "blue");
  dRamCanvas.drawLine(63, 0, 63, 127, "blue");
  dRamCanvas.setIntAxOrientationX(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  dRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  dRamCanvas.drawHersheyGlyph(505, 63, 63,  1,  1, "red");
  dRamCanvas.drawHersheyGlyph(505, 63, 63,  2,  2, "red");
  dRamCanvas.drawHersheyGlyph(505, 63, 63,  4,  4, "red");

  dRamCanvas.writeRAWfile("ut-glyph_axis-d.mrw");
  dRamCanvas.scaleUpProximal(4);
  dRamCanvas.writeTIFFfile("ut-glyph_axis-d.tiff");
  
  // All of them should come out with the E right side up and drawn correctly.

  EXPECT_EQ(R1aRamCanvas.readRAWfile("../data/utest/ut-glyph_axis-a.mrw"), 0);
  EXPECT_EQ(R2aRamCanvas.readRAWfile("ut-glyph_axis-a.mrw"), 0);
  EXPECT_TRUE(R1aRamCanvas.isEqual(R2aRamCanvas));

  EXPECT_EQ(R1bRamCanvas.readRAWfile("../data/utest/ut-glyph_axis-a.mrw"), 0);
  EXPECT_EQ(R2bRamCanvas.readRAWfile("ut-glyph_axis-b.mrw"), 0);
  EXPECT_TRUE(R1bRamCanvas.isEqual(R2bRamCanvas));

  EXPECT_EQ(R1cRamCanvas.readRAWfile("../data/utest/ut-glyph_axis-a.mrw"), 0);
  EXPECT_EQ(R2cRamCanvas.readRAWfile("ut-glyph_axis-c.mrw"), 0);
  EXPECT_TRUE(R1cRamCanvas.isEqual(R2cRamCanvas));

  EXPECT_EQ(R1dRamCanvas.readRAWfile("../data/utest/ut-glyph_axis-a.mrw"), 0);
  EXPECT_EQ(R2dRamCanvas.readRAWfile("ut-glyph_axis-d.mrw"), 0);
  EXPECT_TRUE(R1dRamCanvas.isEqual(R2dRamCanvas));
}
