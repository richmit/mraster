// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      r_adjoin.cpp
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
TEST(r_adjoin, comprehensive) {

  mjr::ramCanvas1c8b aRamCanvas(8, 8);
  aRamCanvas.drawRectangle(0, 0, 7, 7, "white");
  aRamCanvas.drawLine(0, 7, 7, 0, "white");

  mjr::ramCanvas1c8b bRamCanvas(8, 8);
  bRamCanvas.drawRectangle(0, 0, 7, 7, "white");
  bRamCanvas.drawLine(0, 0, 7, 7, "white");

  mjr::ramCanvas1c8b cRamCanvas(aRamCanvas);  mjr::ramCanvas1c8b RcRamCanvas(8, 8);
  cRamCanvas.adjoinCanvasRight(bRamCanvas);
  EXPECT_EQ(RcRamCanvas.readRAWfile("../data/utest/ut-adjoin-c.mrw"), 0);
  EXPECT_TRUE(RcRamCanvas.isEqual(cRamCanvas));

  mjr::ramCanvas1c8b dRamCanvas(aRamCanvas);  mjr::ramCanvas1c8b RdRamCanvas(8, 8);
  dRamCanvas.adjoinCanvasLeft(bRamCanvas);
  EXPECT_EQ(RdRamCanvas.readRAWfile("../data/utest/ut-adjoin-d.mrw"), 0);
  EXPECT_TRUE(RdRamCanvas.isEqual(dRamCanvas));

  mjr::ramCanvas1c8b eRamCanvas(aRamCanvas);  mjr::ramCanvas1c8b ReRamCanvas(8, 8);
  eRamCanvas.adjoinCanvasBottom(bRamCanvas);
  EXPECT_EQ(ReRamCanvas.readRAWfile("../data/utest/ut-adjoin-e.mrw"), 0);
  EXPECT_TRUE(ReRamCanvas.isEqual(eRamCanvas));

  mjr::ramCanvas1c8b fRamCanvas(aRamCanvas);  mjr::ramCanvas1c8b RfRamCanvas(8, 8);
  fRamCanvas.adjoinCanvasTop(bRamCanvas);
  EXPECT_EQ(RfRamCanvas.readRAWfile("../data/utest/ut-adjoin-f.mrw"), 0);
  EXPECT_TRUE(RfRamCanvas.isEqual(fRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.writeRAWfile("ut-adjoin-a.mrw");
  aRamCanvas.scaleUpProximal(32);
  aRamCanvas.writeTIFFfile("ut-adjoin-a.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  bRamCanvas.writeRAWfile("ut-adjoin-b.mrw");
  bRamCanvas.scaleUpProximal(32);
  bRamCanvas.writeTIFFfile("ut-adjoin-b.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  cRamCanvas.writeRAWfile("ut-adjoin-c.mrw");  
  cRamCanvas.scaleUpProximal(32);
  cRamCanvas.writeTIFFfile("ut-adjoin-c.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  dRamCanvas.writeRAWfile("ut-adjoin-d.mrw");  
  dRamCanvas.scaleUpProximal(32);
  dRamCanvas.writeTIFFfile("ut-adjoin-d.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  eRamCanvas.writeRAWfile("ut-adjoin-e.mrw");  
  eRamCanvas.scaleUpProximal(32);
  eRamCanvas.writeTIFFfile("ut-adjoin-e.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  fRamCanvas.writeRAWfile("ut-adjoin-f.mrw");
  fRamCanvas.scaleUpProximal(32);
  fRamCanvas.writeTIFFfile("ut-adjoin-f.tiff");
}
