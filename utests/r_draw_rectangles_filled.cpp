// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      r_draw_rectangles_filled.cpp
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
TEST(r_draw_rectangles_filled, comprehensive) {

  // The drawFillRectangle method is pretty simple, but has several edge cases around clipping.  It is also weird about how it uses it's arguments.

  mjr::ramCanvas1c8b::colorType aColor(mjr::ramCanvas1c8b::colorType::cornerColorEnum::WHITE);

  // open: The args are used not points (x1, y1) & (x2, y2), but rather as x and y ranges.
  mjr::ramCanvas1c8b aRamCanvas(9, 9);  mjr::ramCanvas1c8b RaRamCanvas(9, 9);
  aRamCanvas.drawFillRectangle(1, 1, 7, 7, aColor);
  EXPECT_EQ(RaRamCanvas.readRAWfile("../data/utest/ut-rectanglesF-a.mrw"), 0);
  EXPECT_TRUE(RaRamCanvas.isEqual(aRamCanvas));

  mjr::ramCanvas1c8b bRamCanvas(9, 9);
  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawFillRectangle(1, 1, 7, 7, aColor);
  EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawFillRectangle(7, 1, 1, 7, aColor);
  EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawFillRectangle(1, 7, 7, 1, aColor);
  EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawFillRectangle(7, 7, 1, 1, aColor);
  EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));

  // open: clip ALL corner (canvas inside rectangle)
  mjr::ramCanvas1c8b cRamCanvas(9, 9);  mjr::ramCanvas1c8b RcRamCanvas(9, 9);
  cRamCanvas.drawFillRectangle(-4, -2, 25,  12, aColor);
  EXPECT_EQ(RcRamCanvas.readRAWfile("../data/utest/ut-rectanglesF-c.mrw"), 0);
  EXPECT_TRUE(RcRamCanvas.isEqual(cRamCanvas));

  // open: clip ALL corner (canvas inside rectangle)
  mjr::ramCanvas1c8b dRamCanvas(9, 9);  mjr::ramCanvas1c8b RdRamCanvas(9, 9);
  dRamCanvas.drawFillRectangle(-9,  2, -4,   7, aColor); // to left
  dRamCanvas.drawFillRectangle(16,  2, 24,   7, aColor); // to right
  dRamCanvas.drawFillRectangle( 2,  12, 7,  17, aColor); // to top
  dRamCanvas.drawFillRectangle( 2, -17, 7, -10, aColor); // to bot
  dRamCanvas.drawFillRectangle(-9, -15, -4, -7, aColor); // to left below
  dRamCanvas.drawFillRectangle(10,  15, 14, 17, aColor); // to right up
  EXPECT_EQ(RdRamCanvas.readRAWfile("../data/utest/ut-rectanglesF-d.mrw"), 0);
  EXPECT_TRUE(RdRamCanvas.isEqual(dRamCanvas));

  // open: clip one corner
  mjr::ramCanvas1c8b eRamCanvas(9, 9);  mjr::ramCanvas1c8b ReRamCanvas(9, 9);
  eRamCanvas.drawFillRectangle( 6,  6, 12,  12, aColor);
  eRamCanvas.drawFillRectangle( 6,  2, 12, -12, aColor);
  eRamCanvas.drawFillRectangle(-6,  6,  2,  16, aColor);
  eRamCanvas.drawFillRectangle(-6, -6,  2,   2, aColor);
  EXPECT_EQ(ReRamCanvas.readRAWfile("../data/utest/ut-rectanglesF-e.mrw"), 0);
  EXPECT_TRUE(ReRamCanvas.isEqual(eRamCanvas));

  // open: clip one side
  mjr::ramCanvas1c8b fRamCanvas(9, 9);  mjr::ramCanvas1c8b RfRamCanvas(9, 9);
  fRamCanvas.drawFillRectangle( 2,   7,  6, 12, aColor); // top
  fRamCanvas.drawFillRectangle( 7,   2, 20,  6, aColor); // right
  fRamCanvas.drawFillRectangle(-6,   2,  1,  6, aColor);  // left
  fRamCanvas.drawFillRectangle( 2, -27,  6,  1, aColor); // bot
  EXPECT_EQ(RfRamCanvas.readRAWfile("../data/utest/ut-rectanglesF-f.mrw"), 0);
  EXPECT_TRUE(RfRamCanvas.isEqual(fRamCanvas));

  // open: clip one side (T/B)
  mjr::ramCanvas1c8b gRamCanvas(9, 9);  mjr::ramCanvas1c8b RgRamCanvas(9, 9);
  gRamCanvas.drawFillRectangle(-3,   7, 26, 12, aColor); // top
  gRamCanvas.drawFillRectangle(-4, -27, 30,  1, aColor); // bot
  EXPECT_EQ(RgRamCanvas.readRAWfile("../data/utest/ut-rectanglesF-g.mrw"), 0);
  EXPECT_TRUE(RgRamCanvas.isEqual(gRamCanvas));

  // open: clip one side (L/R)
  mjr::ramCanvas1c8b hRamCanvas(9, 9);  mjr::ramCanvas1c8b RhRamCanvas(9, 9);
  hRamCanvas.drawFillRectangle( 7,  -2, 20, 36, aColor); // right
  hRamCanvas.drawFillRectangle(-6,  -5,  1, 16, aColor);  // left
  EXPECT_EQ(RhRamCanvas.readRAWfile("../data/utest/ut-rectanglesF-h.mrw"), 0);
  EXPECT_TRUE(RhRamCanvas.isEqual(hRamCanvas));

  aRamCanvas.writeRAWfile("ut-rectanglesF-a.mrw");
  aRamCanvas.scaleUpProximal(20);
  aRamCanvas.writeTIFFfile("ut-rectanglesF-a.tiff");

  cRamCanvas.writeRAWfile("ut-rectanglesF-c.mrw");
  cRamCanvas.scaleUpProximal(20);
  cRamCanvas.writeTIFFfile("ut-rectanglesF-c.tiff");

  dRamCanvas.writeRAWfile("ut-rectanglesF-d.mrw");
  dRamCanvas.scaleUpProximal(20);
  dRamCanvas.writeTIFFfile("ut-rectanglesF-d.tiff");

  eRamCanvas.writeRAWfile("ut-rectanglesF-e.mrw");
  eRamCanvas.scaleUpProximal(20);
  eRamCanvas.writeTIFFfile("ut-rectanglesF-e.tiff");

  fRamCanvas.writeRAWfile("ut-rectanglesF-f.mrw");
  fRamCanvas.scaleUpProximal(20);
  fRamCanvas.writeTIFFfile("ut-rectanglesF-f.tiff");

  gRamCanvas.writeRAWfile("ut-rectanglesF-g.mrw");
  gRamCanvas.scaleUpProximal(20);
  gRamCanvas.writeTIFFfile("ut-rectanglesF-g.tiff");

  hRamCanvas.writeRAWfile("ut-rectanglesF-h.mrw");
  hRamCanvas.scaleUpProximal(20);
  hRamCanvas.writeTIFFfile("ut-rectanglesF-h.tiff");
}
