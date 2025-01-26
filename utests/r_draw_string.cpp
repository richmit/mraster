// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      r_draw_string.cpp
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
TEST(r_draw_string, comprehensive) {

  mjr::ramCanvas3c8b aRamCanvas(450, 100);  mjr::ramCanvas3c8b RaRamCanvas(450, 100);
  int y;
  aRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  RaRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  aRamCanvas.drawLine(50, 0,  50, 512, "blue");
  y = 18;
  aRamCanvas.drawLine(0, y,   1024, y, "blue");
  aRamCanvas.drawString("Hello, World!", mjr::hershey::font::ROMAN_SL_SANSERIF, 50, y, "red",  1, 16);
  y+=50;
  aRamCanvas.drawLine(0, y,   1024, y, "blue");
  aRamCanvas.drawString("Hello, World!", mjr::hershey::font::ROMAN_SL_SANSERIF, 50, y, "red",  2, 15);

  EXPECT_EQ(RaRamCanvas.readRAWfile("../data/utest/ut-strings-a.mrw"), 0);
  EXPECT_TRUE(RaRamCanvas.isEqual(aRamCanvas));

  mjr::ramCanvas3c8b bRamCanvas(450, 100);  mjr::ramCanvas3c8b RbRamCanvas(450, 100);
  bRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  RbRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  y =18;
  bRamCanvas.drawStringBox("Hello, World!", mjr::hershey::font::ROMAN_SL_SANSERIF, 50, y, "red", "green",  1, 16);
  bRamCanvas.drawLine(0, y,   1024, y, "blue");
  y+=50;
  bRamCanvas.drawStringBox("Hello, World!", mjr::hershey::font::ROMAN_SL_SANSERIF, 50, y, "red", "green",  2, 15);
  bRamCanvas.drawLine(0, y,   1024, y, "blue");
  bRamCanvas.drawLine(50, 0,  50, 512, "blue");
  
  EXPECT_EQ(RbRamCanvas.readRAWfile("../data/utest/ut-strings-b.mrw"), 0);
  EXPECT_TRUE(RbRamCanvas.isEqual(bRamCanvas));

  aRamCanvas.writeRAWfile("ut-strings-a.mrw");
  aRamCanvas.scaleUpProximal(4);
  aRamCanvas.writeTIFFfile("ut-strings-a.tiff");

  bRamCanvas.writeRAWfile("ut-strings-b.mrw");
  bRamCanvas.scaleUpProximal(4);
  bRamCanvas.writeTIFFfile("ut-strings-b.tiff");
}
