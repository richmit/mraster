// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      r_draw_lines.cpp
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
TEST(r_draw_lines, no_clip) {

// The line draw algorithm has many cases.  We try to hit them all.

  const int WIDE = 16+16+16+1;
  const int TALL = 18;

  mjr::ramCanvas1c8b aRamCanvas(WIDE, TALL); mjr::ramCanvas1c8b RaRamCanvas(WIDE, TALL);
  mjr::ramCanvas1c8b::colorType aColor;

  std::vector<std::vector<int>> lns {{ 1,  1,  1, 11},
                                     { 1,  1, 11, 16},
                                     { 1,  1, 11, 11},
                                     { 1,  1, 11,  6},
                                     { 1,  1, 11,  1},
                                     {13, 16, 23, 11},
                                     {13, 16, 23,  6},
                                     {13, 16, 23,  1}};

  aColor.setToWhite();
  for(auto pts : lns) {
    aRamCanvas.drawLine(   pts[2], pts[3],    pts[0], pts[1], aColor);
    aRamCanvas.drawLine(24+pts[0], pts[1], 24+pts[2], pts[3], aColor);
  }

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Compare reference with test
  EXPECT_EQ(RaRamCanvas.readRAWfile("../data/utest/ut-lines_no_clip.mrw"), 0);
  EXPECT_TRUE(RaRamCanvas.isEqual(aRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Save diagnostic images
  aRamCanvas.writeRAWfile("ut-lines_no_clip.mrw");
  aRamCanvas.scaleUpProximal(10);
  aRamCanvas.writeTIFFfile("ut-lines_no_clip.tiff");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(r_draw_lines, clip) {

  // The line draw algorithm has many cases.  We try to hit them all.

  std::vector<std::vector<int>> lns {{ -8, -16,   8,  16},
                                     {-16, -16,  16,  16},
                                     {-16,  -8,  16,   8},
                                     {-16,   0,  16,   0},
                                     {-16,   8,  16,  -8},
                                     {-16,  16,  16, -16},
                                     { -8,  16,   8, -16},
                                     {  0, -16,   0,  16}};

  mjr::ramCanvas1c8b::colorType aColor;
  aColor.setToWhite();

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // no-clip
  mjr::ramCanvas1c8b bRamCanvas(40, 40); mjr::ramCanvas1c8b RbRamCanvas(40, 40);
  mjr::ramCanvas1c8b cRamCanvas(40, 40); 

  for(auto pts : lns) {
    bRamCanvas.drawLine(19+pts[0], 19+pts[1], 19+pts[2], 19+pts[3], aColor);
    cRamCanvas.drawLine(19+pts[2], 19+pts[3], 19+pts[0], 19+pts[1], aColor);
  }

  EXPECT_TRUE(bRamCanvas.isEqual(cRamCanvas));

  // Compare reference with test
  EXPECT_EQ(RbRamCanvas.readRAWfile("../data/utest/ut-lines_clip-b.mrw"), 0);
  EXPECT_TRUE(RbRamCanvas.isEqual(bRamCanvas));

  // Save diagnostic images
  bRamCanvas.writeRAWfile("ut-lines_clip-b.mrw");
  bRamCanvas.scaleUpProximal(10);
  bRamCanvas.writeTIFFfile("ut-lines_clip-b.tiff");

  cRamCanvas.writeRAWfile("ut-lines_clip-c.mrw");
  cRamCanvas.scaleUpProximal(10);
  cRamCanvas.writeTIFFfile("ut-lines_clip-c.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // bot/left-clip
  mjr::ramCanvas1c8b dRamCanvas(25, 25); mjr::ramCanvas1c8b RdRamCanvas(25, 25);
  mjr::ramCanvas1c8b eRamCanvas(25, 25);

  for(auto pts : lns) {
    dRamCanvas.drawLine(7+pts[0], 7+pts[1], 7+pts[2], 7+pts[3], aColor);
    eRamCanvas.drawLine(7+pts[2], 7+pts[3], 7+pts[0], 7+pts[1], aColor);
  }

  EXPECT_TRUE(dRamCanvas.isEqual(eRamCanvas));

  // Compare reference with test
  EXPECT_EQ(RdRamCanvas.readRAWfile("../data/utest/ut-lines_clip-d.mrw"), 0);
  EXPECT_TRUE(RdRamCanvas.isEqual(dRamCanvas));

  // Save diagnostic images
  dRamCanvas.writeRAWfile("ut-lines_clip-d.mrw");
  dRamCanvas.scaleUpProximal(10);
  dRamCanvas.writeTIFFfile("ut-lines_clip-d.tiff");

  eRamCanvas.writeRAWfile("ut-lines_clip-e.mrw");
  eRamCanvas.scaleUpProximal(10);
  eRamCanvas.writeTIFFfile("ut-lines_clip-e.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // top/right-clip
  mjr::ramCanvas1c8b fRamCanvas(25, 25); mjr::ramCanvas1c8b RfRamCanvas(25, 25);
  mjr::ramCanvas1c8b gRamCanvas(25, 25);

  for(auto pts : lns) {
    fRamCanvas.drawLine(17+pts[0], 17+pts[1], 17+pts[2], 17+pts[3], aColor);
    gRamCanvas.drawLine(17+pts[2], 17+pts[3], 17+pts[0], 17+pts[1], aColor);
  }

  EXPECT_TRUE(fRamCanvas.isEqual(gRamCanvas));

  // Compare reference with test
  EXPECT_EQ(RfRamCanvas.readRAWfile("../data/utest/ut-lines_clip-f.mrw"), 0);
  EXPECT_TRUE(RfRamCanvas.isEqual(fRamCanvas));

  // Save diagnostic images
  fRamCanvas.writeRAWfile("ut-lines_clip-f.mrw");
  fRamCanvas.scaleUpProximal(10);
  fRamCanvas.writeTIFFfile("ut-lines_clip-f.tiff");

  gRamCanvas.writeRAWfile("ut-lines_clip-g.mrw");
  gRamCanvas.scaleUpProximal(10);
  gRamCanvas.writeTIFFfile("ut-lines_clip-g.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // all-clip
  mjr::ramCanvas1c8b hRamCanvas(15, 15); mjr::ramCanvas1c8b RhRamCanvas(15, 15);
  mjr::ramCanvas1c8b iRamCanvas(15, 15); 

  for(auto pts : lns) {
    hRamCanvas.drawLine(7+pts[0], 7+pts[1], 7+pts[2], 7+pts[3], aColor);
    iRamCanvas.drawLine(7+pts[2], 7+pts[3], 7+pts[0], 7+pts[1], aColor);
  }

  EXPECT_TRUE(hRamCanvas.isEqual(iRamCanvas));

  // Compare reference with test
  EXPECT_EQ(RhRamCanvas.readRAWfile("../data/utest/ut-lines_clip-h.mrw"), 0);
  EXPECT_TRUE(RhRamCanvas.isEqual(hRamCanvas));

  // Save diagnostic images
  hRamCanvas.writeRAWfile("ut-lines_clip-h.mrw");
  hRamCanvas.scaleUpProximal(10);
  hRamCanvas.writeTIFFfile("ut-lines_clip-h.tiff");

  iRamCanvas.writeRAWfile("ut-lines_clip-i.mrw");
  iRamCanvas.scaleUpProximal(10);
  iRamCanvas.writeTIFFfile("ut-lines_clip-i.tiff");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(r_draw_lines, swap) {

// Make sure we get the same result regardless of point order in drawLine call

  mjr::ramCanvas1c8b aRamCanvas(16, 16);
  mjr::ramCanvas1c8b bRamCanvas(16, 16);
  mjr::ramCanvas1c8b::colorType aColor(mjr::ramCanvas1c8b::colorType::cornerColorEnum::WHITE);

  int x1, y1, x2, y2;
  for(int i=0; i<16; i++) {
    y1 = i;
    x1 = 0;
    y2 = 15-y1;
    x2 = 15;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));
    y1 = 0;
    x1 = i;
    y2 = 15;
    x2 = 15-x1;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));
    // Clip on right
    y1 = i;
    x1 = 0;
    y2 = 15-y1;
    x2 = 25;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));
    // Clip on top
    y1 = 0;
    x1 = i;
    y2 = 25;
    x2 = 15-x1;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));
    // Clip on left
    y1 = i;
    x1 = -5;
    y2 = 15-y1;
    x2 = 15;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));
    // Clip on bot
    y1 = -10;
    x1 = i;
    y2 = 15;
    x2 = 15-x1;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));
  }
}
