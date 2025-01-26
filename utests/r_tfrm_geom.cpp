// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      r_tfrm_geom.cpp
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
TEST(geom_tfrm, comprehensive) {

  mjr::ramCanvas1c8b aRamCanvas(8, 8); mjr::ramCanvas1c8b RaRamCanvas(8, 8);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawLine(0, 0, 3, 0, "white");
  aRamCanvas.drawLine(3, 7, 7, 7, "white");
  EXPECT_EQ(RaRamCanvas.readRAWfile("../data/utest/ut-geom_tfrm-a.mrw"), 0);
  EXPECT_TRUE(RaRamCanvas.isEqual(aRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  mjr::ramCanvas1c8b bRamCanvas(aRamCanvas);  mjr::ramCanvas1c8b RbRamCanvas(8, 8);
  bRamCanvas.flipHorz();
  EXPECT_EQ(RbRamCanvas.readRAWfile("../data/utest/ut-geom_tfrm-b.mrw"), 0);
  EXPECT_TRUE(RbRamCanvas.isEqual(bRamCanvas));
  RbRamCanvas.flipHorz();
  EXPECT_TRUE(RbRamCanvas.isEqual(aRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  mjr::ramCanvas1c8b cRamCanvas(aRamCanvas);  mjr::ramCanvas1c8b RcRamCanvas(8, 8);
  cRamCanvas.flipVert();
  EXPECT_EQ(RcRamCanvas.readRAWfile("../data/utest/ut-geom_tfrm-c.mrw"), 0);
  EXPECT_TRUE(RcRamCanvas.isEqual(cRamCanvas));
  RcRamCanvas.flipVert();
  EXPECT_TRUE(RcRamCanvas.isEqual(aRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  mjr::ramCanvas1c8b dRamCanvas(aRamCanvas);  mjr::ramCanvas1c8b RdRamCanvas(8, 8);
  dRamCanvas.flipTranspose();
  EXPECT_EQ(RdRamCanvas.readRAWfile("../data/utest/ut-geom_tfrm-d.mrw"), 0);
  EXPECT_TRUE(RdRamCanvas.isEqual(dRamCanvas));
  RdRamCanvas.flipTranspose();
  EXPECT_TRUE(RdRamCanvas.isEqual(aRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  mjr::ramCanvas1c8b eRamCanvas(aRamCanvas);  mjr::ramCanvas1c8b ReRamCanvas(8, 8);
  eRamCanvas.rotate90CW();
  EXPECT_EQ(ReRamCanvas.readRAWfile("../data/utest/ut-geom_tfrm-e.mrw"), 0);
  EXPECT_TRUE(ReRamCanvas.isEqual(eRamCanvas));
  eRamCanvas.rotate90CCW();
  EXPECT_TRUE(eRamCanvas.isEqual(aRamCanvas));
  eRamCanvas.rotate90CW();
  eRamCanvas.rotate90CW();
  eRamCanvas.rotate90CW();
  eRamCanvas.rotate90CW();
  EXPECT_TRUE(eRamCanvas.isEqual(aRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  mjr::ramCanvas1c8b fRamCanvas(aRamCanvas);  mjr::ramCanvas1c8b RfRamCanvas(8, 8);
  fRamCanvas.rotate90CCW();
  EXPECT_EQ(RfRamCanvas.readRAWfile("../data/utest/ut-geom_tfrm-f.mrw"), 0);
  EXPECT_TRUE(RfRamCanvas.isEqual(fRamCanvas));
  fRamCanvas.rotate90CW();
  EXPECT_TRUE(fRamCanvas.isEqual(aRamCanvas));
  fRamCanvas.rotate90CCW();
  fRamCanvas.rotate90CCW();
  fRamCanvas.rotate90CCW();
  fRamCanvas.rotate90CCW();
  EXPECT_TRUE(fRamCanvas.isEqual(aRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  mjr::ramCanvas1c8b gRamCanvas(aRamCanvas);  mjr::ramCanvas1c8b RgRamCanvas(8, 8);
  gRamCanvas.rotate180();
  EXPECT_EQ(RgRamCanvas.readRAWfile("../data/utest/ut-geom_tfrm-g.mrw"), 0);
  EXPECT_TRUE(RgRamCanvas.isEqual(gRamCanvas));
  gRamCanvas.rotate180();
  EXPECT_TRUE(gRamCanvas.isEqual(aRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.writeRAWfile("ut-geom_tfrm-a.mrw");
  aRamCanvas.scaleUpProximal(16);
  aRamCanvas.writeTIFFfile("ut-geom_tfrm-a.tiff");

  bRamCanvas.writeRAWfile("ut-geom_tfrm-b.mrw");
  bRamCanvas.scaleUpProximal(16);
  bRamCanvas.writeTIFFfile("ut-geom_tfrm-b.tiff");

  cRamCanvas.writeRAWfile("ut-geom_tfrm-c.mrw");
  cRamCanvas.scaleUpProximal(16);
  cRamCanvas.writeTIFFfile("ut-geom_tfrm-c.tiff");

  dRamCanvas.writeRAWfile("ut-geom_tfrm-d.mrw");
  dRamCanvas.scaleUpProximal(16);
  dRamCanvas.writeTIFFfile("ut-geom_tfrm-d.tiff");

  eRamCanvas.writeRAWfile("ut-geom_tfrm-e.mrw");
  eRamCanvas.scaleUpProximal(16);
  eRamCanvas.writeTIFFfile("ut-geom_tfrm-e.tiff");

  fRamCanvas.writeRAWfile("ut-geom_tfrm-f.mrw");
  fRamCanvas.scaleUpProximal(16);
  fRamCanvas.writeTIFFfile("ut-geom_tfrm-f.tiff");

  gRamCanvas.writeRAWfile("ut-geom_tfrm-g.mrw");
  gRamCanvas.scaleUpProximal(16);
  gRamCanvas.writeTIFFfile("ut-geom_tfrm-g.tiff");
}
