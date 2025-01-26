// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      r_draw_circles.cpp
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
TEST(r_draw_circles, comprehensive) {

  mjr::color1c8b aColor(mjr::color1c8b::cornerColorEnum::WHITE);
  mjr::color1c8b bColor(mjr::color1c8b::cornerColorEnum::BLACK);

  mjr::ramCanvas1c8b aRamCanvas(63, 63);  mjr::ramCanvas1c8b RaRamCanvas(63, 63);
  for(int i=2; i<32; i+=2)
    aRamCanvas.drawCircle(31, 31, i, aColor);
  EXPECT_EQ(RaRamCanvas.readRAWfile("../data/utest/ut-circles-a.mrw"), 0);
  EXPECT_TRUE(RaRamCanvas.isEqual(aRamCanvas));

  mjr::ramCanvas1c8b bRamCanvas(63, 63);  mjr::ramCanvas1c8b RbRamCanvas(63, 63);
  bRamCanvas.drawFillCircle(31, 31, 30, aColor);
  EXPECT_EQ(RbRamCanvas.readRAWfile("../data/utest/ut-circles-b.mrw"), 0);
  EXPECT_TRUE(RbRamCanvas.isEqual(bRamCanvas));

  mjr::ramCanvas1c8b cRamCanvas(32, 32);  mjr::ramCanvas1c8b RcRamCanvas(32, 32);
  cRamCanvas.drawCircle(31, 31, 16, aColor);
  cRamCanvas.drawCircle(16, -5, 15, aColor);
  cRamCanvas.drawCircle(5,  20, 8, aColor);
  EXPECT_EQ(RcRamCanvas.readRAWfile("../data/utest/ut-circles-c.mrw"), 0);
  EXPECT_TRUE(RcRamCanvas.isEqual(cRamCanvas));

  mjr::ramCanvas1c8b dRamCanvas(32, 32);  mjr::ramCanvas1c8b RdRamCanvas(32, 32);
  dRamCanvas.drawFillCircle(31, 31, 16, aColor);
  dRamCanvas.drawFillCircle(16, -5, 15, aColor);
  dRamCanvas.drawFillCircle(5,  20, 8, aColor);
  EXPECT_EQ(RdRamCanvas.readRAWfile("../data/utest/ut-circles-d.mrw"), 0);
  EXPECT_TRUE(RdRamCanvas.isEqual(dRamCanvas));

  mjr::ramCanvas1c8b eRamCanvas(32, 32);  mjr::ramCanvas1c8b ReRamCanvas(32, 32);
  eRamCanvas.drawFillCircle(16, 16, 17, aColor);
  EXPECT_EQ(ReRamCanvas.readRAWfile("../data/utest/ut-circles-e.mrw"), 0);
  EXPECT_TRUE(ReRamCanvas.isEqual(eRamCanvas));

  mjr::ramCanvas1c8b fRamCanvas(32, 32);  mjr::ramCanvas1c8b RfRamCanvas(32, 32);
  fRamCanvas.drawFillCircle(16, 16, 50, aColor);
  EXPECT_EQ(RfRamCanvas.readRAWfile("../data/utest/ut-circles-f.mrw"), 0);
  EXPECT_TRUE(RfRamCanvas.isEqual(fRamCanvas));

  aRamCanvas.writeRAWfile("ut-circles-a.mrw");
  aRamCanvas.scaleUpProximal(8);
  aRamCanvas.writeTIFFfile("ut-circles-a.tiff");

  bRamCanvas.writeRAWfile("ut-circles-b.mrw");
  bRamCanvas.scaleUpProximal(8);
  bRamCanvas.writeTIFFfile("ut-circles-b.tiff");

  cRamCanvas.writeRAWfile("ut-circles-c.mrw");
  cRamCanvas.scaleUpProximal(20);
  cRamCanvas.writeTIFFfile("ut-circles-c.tiff");

  dRamCanvas.writeRAWfile("ut-circles-d.mrw");
  dRamCanvas.scaleUpProximal(20);
  dRamCanvas.writeTIFFfile("ut-circles-d.tiff");

  eRamCanvas.writeRAWfile("ut-circles-e.mrw");
  eRamCanvas.scaleUpProximal(20);
  eRamCanvas.writeTIFFfile("ut-circles-e.tiff");

  fRamCanvas.writeRAWfile("ut-circles-f.mrw");
  fRamCanvas.scaleUpProximal(20);
  fRamCanvas.writeTIFFfile("ut-circles-f.tiff");
}
