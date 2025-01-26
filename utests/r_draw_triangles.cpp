// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      r_triangles.cpp
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
TEST(r_draw_triangles, comprehensive) {

  // Try to hit many of the special cases for triangle rendering. For filled triangles, that includes the cases cA-cS in ramCanvasTpl::drawFillTriangleUtl.
  // It also means trying to get some good coverage of the special cases in ramCanvasTpl::triangleEdger as well.  One critical care about is that the edges of
  // triangles (open, solid, and shaded) are *identical*.  Another is that the results should be invariant under permutations of the points in the function
  // call.

  std::vector<std::vector<int>> tri {{ 0,  0, 16,  0,  8,  8}, // flat bot, ctr,  45
                                     { 0,  0, 16,  0,  8, 16}, // flat bot, ctr, <45
                                     { 0,  0, 16,  0,  8,  4}, // flat bot, ctr, >45
                                     { 0,  0,  8,  0,  0,  8}, // flat bot, lft,  45
                                     { 0,  0,  8,  0,  0, 16}, // flat bot, lft, <45
                                     { 0,  0,  8,  0,  0,  4}, // flat bot, lft, >45
                                     { 0,  0,  8,  0,  8,  8}, // flat bot, rgt,  45
                                     { 0,  0,  8,  0,  8, 16}, // flat bot, rgt, <45
                                     { 0,  0,  8,  0,  8,  4}, // flat bot, rgt, >45
                                     { 0, 16, 16, 16,  8,  8}, // flat top, ctr,  45
                                     { 0, 16, 16, 16,  8,  0}, // flat top, ctr, <45
                                     { 0, 16, 16, 16,  8, 12}, // flat top, ctr, >45
                                     { 0, 16,  8, 16,  0,  8}, // flat top, lft,  45
                                     { 0, 16,  8, 16,  0,  0}, // flat top, lft, <45
                                     { 0, 16,  8, 16,  0, 12}, // flat top, lft, >45
                                     { 0, 16,  8, 16,  8,  8}, // flat top, rgt,  45
                                     { 0, 16,  8, 16,  8,  0}, // flat top, rgt, <45
                                     { 0, 16,  8, 16,  8, 12}, // flat top, rgt, >45
                                     { 0,  0,  0, 16,  8,  8}, // flat lft, ctr,  45
                                     { 0,  0,  0, 16, 16,  8}, // flat lft, ctr, <45
                                     { 0,  0,  0, 16,  4,  8}, // flat lft, ctr, >45
                                     { 0,  0,  0,  8,  8,  0}, // flat lft, bot,  45
                                     { 0,  0,  0,  8, 16,  0}, // flat lft, bot, <45
                                     { 0,  0,  0,  8,  4,  0}, // flat lft, bot, >45
                                     { 0,  0,  0,  8,  8,  8}, // flat lft, top,  45
                                     { 0,  0,  0,  8, 16,  8}, // flat lft, top, <45
                                     { 0,  0,  0,  8,  4,  8}, // flat lft, top, >45
                                     {16,  0, 16, 16,  8,  8}, // flat rgt, ctr,  45
                                     {16,  0, 16, 16,  0,  8}, // flat rgt, ctr, <45
                                     {16,  0, 16, 16, 12,  8}, // flat rgt, ctr, >45
                                     {16,  0, 16,  8,  8,  0}, // flat rgt, bot,  45
                                     {16,  0, 16,  8,  0,  0}, // flat rgt, bot, <45
                                     {16,  0, 16,  8, 12,  0}, // flat rgt, bot, >45
                                     {16,  0, 16,  8,  8,  8}, // flat rgt, lft,  45
                                     {16,  0, 16,  8,  0,  8}, // flat rgt, lft, <45
                                     {16,  0, 16,  8, 12,  8}, // flat rgt, lft, >45
                                     { 0,  0, 16,  0,  8,  0}, // flat hoz, ctr
                                     { 0,  0, 16,  0,  0,  0}, // flat hoz, lft
                                     { 0,  0, 16,  0, 16,  0}, // flat hoz, rgt
                                     { 0,  0,  0, 16,  0,  8}, // flat vrt, ctr
                                     { 0,  0,  0, 16,  0,  0}, // flat vrt, bot
                                     { 0,  0,  0, 16,  0, 16}, // flat vrt, top
                                     { 8,  8,  8,  8,  8,  8}, // one point
                                     { 0,  0,  0,  0, 16, 16}, // line 45
                                     { 0, 16,  0, 16, 16,  0}, // line -45
                                     { 0,  0,  0,  0, 16,  4}, // line small slope
                                     { 0,  0,  0,  0, 16,  8}, // line small slope
                                     { 0, 16,  0, 16, 16,  8}, // line small -slope
                                     { 0, 16,  0, 16, 16, 12}, // line small -slope
                                     { 0,  0,  0,  0,  4, 16}, // line big slope
                                     { 0,  0,  0,  0,  8, 16}, // line big slope
                                     { 0, 16,  0, 16, 12,  0}, // line big -slope
                                     { 0, 16,  0, 16,  8,  0}, // line big -slope
                                     { 0,  0,  8,  8, 16, 16}, // 45 1-3 pt in ctr
                                     { 0,  0,  4,  8, 16, 16}, // 45 1-3 pt above
                                     { 0,  0, 12,  8, 16, 16}, // 45 1-3 pt below
                                     //{ 4,  0,  8,  8, 12, 16}, // >45 1-3 pt in ctr
                                     { 4,  0,  6,  8, 12, 16}, // >45 1-3 pt off -2
                                     { 4,  0,  4,  8, 12, 16}, // >45 1-3 pt off -4
                                     { 4,  0,  0,  8, 12, 16}, // >45 1-3 pt off -8
                                     { 4,  0, 10,  8, 12, 16}, // >45 1-3 pt off +2
                                     { 4,  0, 12,  8, 12, 16}, // >45 1-3 pt off +4
                                     { 4,  0, 16,  8, 12, 16}, // >45 1-3 pt off +8
                                     //{ 4, 16,  8,  8, 12,  0}, // >-45 1-3 pt in ctr
                                     { 4, 16,  6,  8, 12,  0}, // >-45 1-3 pt off -2
                                     { 4, 16,  4,  8, 12,  0}, // >-45 1-3 pt off -4
                                     { 4, 16,  0,  8, 12,  0}, // >-45 1-3 pt off -8
                                     { 4, 16, 10,  8, 12,  0}, // >-45 1-3 pt off +2
                                     { 4, 16, 12,  8, 12,  0}, // >-45 1-3 pt off +4
                                     { 4, 16, 16,  8, 12,  0}, // >-45 1-3 pt off +8
                                     //{ 0,  4,  8,  8, 16, 12}, // <45 1-3 pt in ctr
                                     { 0,  4,  8,  6, 16, 12}, // <45 1-3 pt off -2
                                     { 0,  4,  8,  4, 16, 12}, // <45 1-3 pt off -4
                                     { 0,  4,  8,  0, 16, 12}, // <45 1-3 pt off -8
                                     { 0,  4,  8, 10, 16, 12}, // <45 1-3 pt off +2
                                     { 0,  4,  8, 12, 16, 12}, // <45 1-3 pt off +4
                                     { 0,  4,  8, 16, 16, 12}, // <45 1-3 pt off +8
                                     {16, 4,   8,  6,  0, 12}, // >-45 1-3 pt off -2
                                     {16, 4,   8,  4,  0, 12}, // >-45 1-3 pt off -4
                                     {16, 4,   8,  0,  0, 12}, // >-45 1-3 pt off -8
                                     {16, 4,   8, 10,  0, 12}, // >-45 1-3 pt off +2
                                     {16, 4,   8, 12,  0, 12}, // >-45 1-3 pt off +4
                                     {16, 4,   8, 16,  0, 12}, // >-45 1-3 pt off +8
                                     {16, 4,   8,  8,  0, 12}  // >-45 1-3 pt in ctr
                                    };

  mjr::ramCanvas1c8b::colorType aColor(mjr::ramCanvas1c8b::colorType::cornerColorEnum::WHITE);
  mjr::ramCanvas3c8b::colorType bColor(mjr::ramCanvas3c8b::colorType::cornerColorEnum::BLUE);
  mjr::ramCanvas3c8b::colorType cColor(mjr::ramCanvas3c8b::colorType::cornerColorEnum::GREEN);
  mjr::ramCanvas3c8b::colorType dColor(mjr::ramCanvas3c8b::colorType::cornerColorEnum::RED);

  mjr::ramCanvas1c8b aRamCanvas(163, 163);  mjr::ramCanvas1c8b RaRamCanvas(163, 163);
  mjr::ramCanvas1c8b bRamCanvas(163, 163);
  mjr::ramCanvas1c8b cRamCanvas(163, 163);
  mjr::ramCanvas1c8b dRamCanvas(163, 163);
  mjr::ramCanvas1c8b eRamCanvas(163, 163);
  mjr::ramCanvas1c8b fRamCanvas(163, 163);

  mjr::ramCanvas1c8b gRamCanvas(163, 163);  mjr::ramCanvas1c8b RgRamCanvas(163, 163);
  mjr::ramCanvas1c8b hRamCanvas(163, 163);
  mjr::ramCanvas1c8b iRamCanvas(163, 163);
  mjr::ramCanvas1c8b jRamCanvas(163, 163);
  mjr::ramCanvas1c8b kRamCanvas(163, 163);
  mjr::ramCanvas1c8b lRamCanvas(163, 163);

  mjr::ramCanvas3c8b mRamCanvas(163, 163);  mjr::ramCanvas3c8b RmRamCanvas(163, 163);
  mjr::ramCanvas3c8b nRamCanvas(163, 163);
  mjr::ramCanvas3c8b oRamCanvas(163, 163);
  mjr::ramCanvas3c8b pRamCanvas(163, 163);
  mjr::ramCanvas3c8b qRamCanvas(163, 163);
  mjr::ramCanvas3c8b rRamCanvas(163, 163);

  for(int i=0; i<9; i++) {
    for(int j=0; j<9; j++) {
      unsigned k = i + j * 9;
      if (k < tri.size()) {
        auto pts = tri[k];;
        int xo = 1+18*i;
        int yo = 1+18*j;
        aRamCanvas.drawTriangle(xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], aColor);
        bRamCanvas.drawTriangle(xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], aColor);
        cRamCanvas.drawTriangle(xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], aColor);
        dRamCanvas.drawTriangle(xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], aColor);
        eRamCanvas.drawTriangle(xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], aColor);
        fRamCanvas.drawTriangle(xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], aColor);

        gRamCanvas.drawFillTriangle(xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], aColor);
        hRamCanvas.drawFillTriangle(xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], aColor);
        iRamCanvas.drawFillTriangle(xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], aColor);
        jRamCanvas.drawFillTriangle(xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], aColor);
        kRamCanvas.drawFillTriangle(xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], aColor);
        lRamCanvas.drawFillTriangle(xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], aColor);


        mRamCanvas.drawFillTriangle(xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], bColor, cColor, dColor);
        nRamCanvas.drawFillTriangle(xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], cColor, dColor, bColor);
        oRamCanvas.drawFillTriangle(xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], dColor, bColor, cColor);
        pRamCanvas.drawFillTriangle(xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], dColor, cColor, bColor);
        qRamCanvas.drawFillTriangle(xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], cColor, bColor, dColor);
        rRamCanvas.drawFillTriangle(xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], bColor, dColor, cColor);
      }
    }
  }

  EXPECT_TRUE(aRamCanvas.isEqual(bRamCanvas));
  EXPECT_TRUE(aRamCanvas.isEqual(cRamCanvas));
  EXPECT_TRUE(aRamCanvas.isEqual(dRamCanvas));
  EXPECT_TRUE(aRamCanvas.isEqual(eRamCanvas));
  EXPECT_TRUE(aRamCanvas.isEqual(fRamCanvas));

  EXPECT_EQ(RaRamCanvas.readRAWfile("../data/utest/ut-triangles-a.mrw"), 0);
  EXPECT_TRUE(RaRamCanvas.isEqual(aRamCanvas));

  EXPECT_TRUE(gRamCanvas.isEqual(hRamCanvas));
  EXPECT_TRUE(gRamCanvas.isEqual(iRamCanvas));
  EXPECT_TRUE(gRamCanvas.isEqual(jRamCanvas));
  EXPECT_TRUE(gRamCanvas.isEqual(kRamCanvas));
  EXPECT_TRUE(gRamCanvas.isEqual(lRamCanvas));

  EXPECT_EQ(RgRamCanvas.readRAWfile("../data/utest/ut-triangles-g.mrw"), 0);
  EXPECT_TRUE(RgRamCanvas.isEqual(gRamCanvas));

  EXPECT_TRUE(mRamCanvas.isEqual(nRamCanvas));
  EXPECT_TRUE(mRamCanvas.isEqual(oRamCanvas));
  EXPECT_TRUE(mRamCanvas.isEqual(pRamCanvas));
  EXPECT_TRUE(mRamCanvas.isEqual(qRamCanvas));
  EXPECT_TRUE(mRamCanvas.isEqual(rRamCanvas));

  EXPECT_EQ(RmRamCanvas.readRAWfile("../data/utest/ut-triangles-m.mrw"), 0);
  EXPECT_TRUE(RmRamCanvas.isEqual(mRamCanvas));

  aRamCanvas.writeRAWfile("ut-triangles-a.mrw");
  bRamCanvas.writeRAWfile("ut-triangles-b.mrw");
  cRamCanvas.writeRAWfile("ut-triangles-c.mrw");
  dRamCanvas.writeRAWfile("ut-triangles-d.mrw");
  eRamCanvas.writeRAWfile("ut-triangles-e.mrw");
  fRamCanvas.writeRAWfile("ut-triangles-f.mrw");

  aRamCanvas.scaleUpProximal(8);
  bRamCanvas.scaleUpProximal(8);
  cRamCanvas.scaleUpProximal(8);
  dRamCanvas.scaleUpProximal(8);
  eRamCanvas.scaleUpProximal(8);
  fRamCanvas.scaleUpProximal(8);

  aRamCanvas.writeTIFFfile("ut-triangles-a.tiff");
  bRamCanvas.writeTIFFfile("ut-triangles-b.tiff");
  cRamCanvas.writeTIFFfile("ut-triangles-c.tiff");
  dRamCanvas.writeTIFFfile("ut-triangles-d.tiff");
  eRamCanvas.writeTIFFfile("ut-triangles-e.tiff");
  fRamCanvas.writeTIFFfile("ut-triangles-f.tiff");

  gRamCanvas.writeRAWfile("ut-triangles-g.mrw");
  hRamCanvas.writeRAWfile("ut-triangles-h.mrw");
  iRamCanvas.writeRAWfile("ut-triangles-i.mrw");
  jRamCanvas.writeRAWfile("ut-triangles-j.mrw");
  kRamCanvas.writeRAWfile("ut-triangles-k.mrw");
  lRamCanvas.writeRAWfile("ut-triangles-l.mrw");

  gRamCanvas.scaleUpProximal(8);
  hRamCanvas.scaleUpProximal(8);
  iRamCanvas.scaleUpProximal(8);
  jRamCanvas.scaleUpProximal(8);
  kRamCanvas.scaleUpProximal(8);
  lRamCanvas.scaleUpProximal(8);

  gRamCanvas.writeTIFFfile("ut-triangles-g.tiff");
  hRamCanvas.writeTIFFfile("ut-triangles-h.tiff");
  iRamCanvas.writeTIFFfile("ut-triangles-i.tiff");
  jRamCanvas.writeTIFFfile("ut-triangles-j.tiff");
  kRamCanvas.writeTIFFfile("ut-triangles-k.tiff");
  lRamCanvas.writeTIFFfile("ut-triangles-l.tiff");

  mRamCanvas.writeRAWfile("ut-triangles-m.mrw");
  nRamCanvas.writeRAWfile("ut-triangles-n.mrw");
  oRamCanvas.writeRAWfile("ut-triangles-o.mrw");
  pRamCanvas.writeRAWfile("ut-triangles-p.mrw");
  qRamCanvas.writeRAWfile("ut-triangles-q.mrw");
  rRamCanvas.writeRAWfile("ut-triangles-r.mrw");

  mRamCanvas.scaleUpProximal(8);
  nRamCanvas.scaleUpProximal(8);
  oRamCanvas.scaleUpProximal(8);
  pRamCanvas.scaleUpProximal(8);
  qRamCanvas.scaleUpProximal(8);
  rRamCanvas.scaleUpProximal(8);

  mRamCanvas.writeTIFFfile("ut-triangles-m.tiff");
  nRamCanvas.writeTIFFfile("ut-triangles-n.tiff");
  oRamCanvas.writeTIFFfile("ut-triangles-o.tiff");
  pRamCanvas.writeTIFFfile("ut-triangles-p.tiff");
  qRamCanvas.writeTIFFfile("ut-triangles-q.tiff");
  rRamCanvas.writeTIFFfile("ut-triangles-r.tiff");
}
