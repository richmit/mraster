// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      r_save_file.cpp
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
TEST(r_save_file, Comprehensive) {

  const int WIDE = 16;
  const int TALL = 8;

  mjr::ramCanvasRGB8b  aRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB8b::colorType  aColor; typedef mjr::ramCanvasRGB8b::colorChanType  aCt; mjr::ramCanvasRGB8b  RaRamCanvas(WIDE, TALL);
  mjr::ramCanvasRGB16b bRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB16b::colorType bColor; typedef mjr::ramCanvasRGB16b::colorChanType bCt; mjr::ramCanvasRGB16b RbRamCanvas(WIDE, TALL);
  mjr::ramCanvasRGB32b cRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB32b::colorType cColor; typedef mjr::ramCanvasRGB32b::colorChanType cCt; mjr::ramCanvasRGB32b RcRamCanvas(WIDE, TALL);
  mjr::ramCanvasRGB64b dRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB64b::colorType dColor; typedef mjr::ramCanvasRGB64b::colorChanType dCt; mjr::ramCanvasRGB64b RdRamCanvas(WIDE, TALL);
  mjr::ramCanvasRGB32F eRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB32F::colorType eColor; typedef mjr::ramCanvasRGB32F::colorChanType eCt; mjr::ramCanvasRGB32F ReRamCanvas(WIDE, TALL);
  mjr::ramCanvasRGB64F fRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB64F::colorType fColor; typedef mjr::ramCanvasRGB64F::colorChanType fCt; mjr::ramCanvasRGB64F RfRamCanvas(WIDE, TALL);
  mjr::ramCanvas1c8b   gRamCanvas(WIDE, TALL);   mjr::ramCanvas1c8b::colorType   gColor; typedef mjr::ramCanvas1c8b::colorChanType   gCt; mjr::ramCanvas1c8b   RgRamCanvas(WIDE, TALL);
  mjr::ramCanvas1c16b  hRamCanvas(WIDE, TALL);   mjr::ramCanvas1c16b::colorType  hColor; typedef mjr::ramCanvas1c16b::colorChanType  hCt; mjr::ramCanvas1c16b  RhRamCanvas(WIDE, TALL);
  mjr::ramCanvas1c32b  iRamCanvas(WIDE, TALL);   mjr::ramCanvas1c32b::colorType  iColor; typedef mjr::ramCanvas1c32b::colorChanType  iCt; mjr::ramCanvas1c32b  RiRamCanvas(WIDE, TALL);
  mjr::ramCanvas1c64b  jRamCanvas(WIDE, TALL);   mjr::ramCanvas1c64b::colorType  jColor; typedef mjr::ramCanvas1c64b::colorChanType  jCt; mjr::ramCanvas1c64b  RjRamCanvas(WIDE, TALL);
  mjr::ramCanvas1c32F  kRamCanvas(WIDE, TALL);   mjr::ramCanvas1c32F::colorType  kColor; typedef mjr::ramCanvas1c32F::colorChanType  kCt; mjr::ramCanvas1c32F  RkRamCanvas(WIDE, TALL);
  mjr::ramCanvas1c64F  lRamCanvas(WIDE, TALL);   mjr::ramCanvas1c64F::colorType  lColor; typedef mjr::ramCanvas1c64F::colorChanType  lCt; mjr::ramCanvas1c64F  RlRamCanvas(WIDE, TALL);

  for(int x=0;x<aRamCanvas.getNumPixX();x++)
    for(int y=0;y<aRamCanvas.getNumPixY();y++) {
      aRamCanvas.drawPoint(x, y, aColor.setChansRGB((aCt)x, (aCt)y, (aCt)(x+y)));
      bRamCanvas.drawPoint(x, y, bColor.setChansRGB((bCt)x, (bCt)y, (bCt)(x+y)));
      cRamCanvas.drawPoint(x, y, cColor.setChansRGB((cCt)x, (cCt)y, (cCt)(x+y)));
      dRamCanvas.drawPoint(x, y, dColor.setChansRGB((dCt)x, (dCt)y, (dCt)(x+y)));
      eRamCanvas.drawPoint(x, y, eColor.setChansRGB((eCt)x, (eCt)y, (eCt)(x+y)));
      fRamCanvas.drawPoint(x, y, fColor.setChansRGB((fCt)x, (fCt)y, (fCt)(x+y)));
      gRamCanvas.drawPoint(x, y, gColor.setChans((gCt)(x+y)));
      hRamCanvas.drawPoint(x, y, hColor.setChans((hCt)(x+y)));
      iRamCanvas.drawPoint(x, y, iColor.setChans((iCt)(x+y)));
      jRamCanvas.drawPoint(x, y, jColor.setChans((jCt)(x+y)));
      kRamCanvas.drawPoint(x, y, kColor.setChans((kCt)(x+y)));
      lRamCanvas.drawPoint(x, y, lColor.setChans((lCt)(x+y)));
    }

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Write TIFF files
  aRamCanvas.writeTIFFfile("ut-save_file-a.tiff");
  bRamCanvas.writeTIFFfile("ut-save_file-b.tiff");
  cRamCanvas.writeTIFFfile("ut-save_file-c.tiff");
  dRamCanvas.writeTIFFfile("ut-save_file-d.tiff");
  eRamCanvas.writeTIFFfile("ut-save_file-e.tiff");
  fRamCanvas.writeTIFFfile("ut-save_file-f.tiff");
  gRamCanvas.writeTIFFfile("ut-save_file-g.tiff");
  hRamCanvas.writeTIFFfile("ut-save_file-h.tiff");
  iRamCanvas.writeTIFFfile("ut-save_file-i.tiff");
  jRamCanvas.writeTIFFfile("ut-save_file-j.tiff");
  kRamCanvas.writeTIFFfile("ut-save_file-k.tiff");
  lRamCanvas.writeTIFFfile("ut-save_file-l.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Write TIFF files

  aRamCanvas.writeRAWfile("ut-save_file-a.mrw");
  bRamCanvas.writeRAWfile("ut-save_file-b.mrw");
  cRamCanvas.writeRAWfile("ut-save_file-c.mrw");
  dRamCanvas.writeRAWfile("ut-save_file-d.mrw");
  eRamCanvas.writeRAWfile("ut-save_file-e.mrw");
  fRamCanvas.writeRAWfile("ut-save_file-f.mrw");
  gRamCanvas.writeRAWfile("ut-save_file-g.mrw");
  hRamCanvas.writeRAWfile("ut-save_file-h.mrw");
  iRamCanvas.writeRAWfile("ut-save_file-i.mrw");
  jRamCanvas.writeRAWfile("ut-save_file-j.mrw");
  kRamCanvas.writeRAWfile("ut-save_file-k.mrw");
  lRamCanvas.writeRAWfile("ut-save_file-l.mrw");


  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Compare reference images with images just created

  // I checked this file by hand on 2022-08-28. sha256: 94c07f28db463165acc539a88c8a31c13646890204c7548d72ec3b3bda851c9c
  // hexDump.rb -t 0 -c -w 16 -b 3 -p 100 ut-save_file-a.mrw | less -SR
  EXPECT_EQ(RaRamCanvas.readRAWfile("../data/utest/ut-save_file-a.mrw"), 0);
  EXPECT_TRUE(RaRamCanvas.isEqual(aRamCanvas));

  // I checked this file by hand on 2022-08-28. sha256: daeac55ba6fdf084ece356ce86fba5f0b501ba375b0765d3b1e0aed91bde78b5
  // hexDump.rb -t 0 -c -w 16 -b 6 -p 100 ut-save_file-b.mrw | less -RS
  EXPECT_EQ(RbRamCanvas.readRAWfile("../data/utest/ut-save_file-b.mrw"), 0);
  EXPECT_TRUE(RbRamCanvas.isEqual(bRamCanvas));

  // I checked this file qby hand on 2022-08-28. sha256: d29aa9add19842ba1f2cd98e48a5987b645e8357180984b9b88186733ee4b99f
  // hexDump.rb -t 0 -c -w 16 -b 12 -p 100 ut-save_file-c.mrw | less -RS
  EXPECT_EQ(RcRamCanvas.readRAWfile("../data/utest/ut-save_file-c.mrw"), 0);
  EXPECT_TRUE(RcRamCanvas.isEqual(cRamCanvas));

  // I checked this file qby hand on 2022-08-28. sha256: bf987ec465ba232f3339b87bb9a90b52ec282d31f91378821965c06d72cc1720
  // hexDump.rb -t -1 -c -w 16 -b 24 -p 100 ut-save_file-d.mrw | less -RS
  EXPECT_EQ(RdRamCanvas.readRAWfile("../data/utest/ut-save_file-d.mrw"), 0);
  EXPECT_TRUE(RdRamCanvas.isEqual(dRamCanvas));

  // I checked this file qby hand on 2022-08-28. sha256: eb74e602fc69f5755a276c0bcc3c7acc473def2fb7288e324b6463f45d7f8816
  // hexDump.rb -t 0 -c -w 16 -b 12 -p 100 ut-save_file-e.mrw | less -RS
  EXPECT_EQ(ReRamCanvas.readRAWfile("../data/utest/ut-save_file-e.mrw"), 0);
  EXPECT_TRUE(ReRamCanvas.isEqual(eRamCanvas));

  // I checked this file qby hand on 2022-08-28. sha256: 060b545e73ce68ea60f9413ba8611cea1ddf30c986c6ad9384d137939927465d
  // I did the conversion by hand, so I should double check it...
  // hexDump.rb -t -1 -c -w 16 -b 24 -p 100 ut-save_file-f.mrw | less -RS
  EXPECT_EQ(RfRamCanvas.readRAWfile("../data/utest/ut-save_file-f.mrw"), 0);
  EXPECT_TRUE(RfRamCanvas.isEqual(fRamCanvas));

  // I checked this file qby hand on 2022-08-28. sha256: 24c15670cd4776abbad82f9ad3fa6c83c90dca367c6931bb9dce6b7565108a97
  // hexDump.rb -t 0 -c -w 16 -b 1 -p 100 ut-save_file-g.mrw | less -RS
  EXPECT_EQ(RgRamCanvas.readRAWfile("../data/utest/ut-save_file-g.mrw"), 0);
  EXPECT_TRUE(RgRamCanvas.isEqual(gRamCanvas));

  // I checked this file qby hand on 2022-08-28. sha256: a2daf01cd91b48e850b4db7424dc06d689fe557bc777b20f7dda6954c9bd0618
  // hexDump.rb -t 0 -c -w 16 -b 2 -p 100 ut-save_file-h.mrw | less -RS
  EXPECT_EQ(RhRamCanvas.readRAWfile("../data/utest/ut-save_file-h.mrw"), 0);
  EXPECT_TRUE(RhRamCanvas.isEqual(hRamCanvas));

  // I checked this file qby hand on 2022-08-28. sha256: e54e75ae84fe412648121cf55ba39a0c05405474a0a1cd19ac6dfc92ac839be0 *ut-save_file-i.mrw
  // hexDump.rb -t 0 -c -w 16 -b 4 -p 100 ut-save_file-i.mrw | less -RS
  EXPECT_EQ(RiRamCanvas.readRAWfile("../data/utest/ut-save_file-i.mrw"), 0);
  EXPECT_TRUE(RiRamCanvas.isEqual(iRamCanvas));

  // I checked this file qby hand on 2022-08-28. sha256: 3144a77040b5a25c9c089d7cf32d6ee0f832a23b71de1f2d1b3fafab4b82408c
  // hexDump.rb -t 0 -c -w 16 -b 8 -p 100 ut-save_file-j.mrw | less -RS
  EXPECT_EQ(RjRamCanvas.readRAWfile("../data/utest/ut-save_file-j.mrw"), 0);
  EXPECT_TRUE(RjRamCanvas.isEqual(jRamCanvas));

  // I checked this file qby hand on 2022-08-28. sha256: 25ce4b85baca2aa4ea8f4635e82abb4e1aa92e55ec6a9caf9b5558a1d0574a66
  // hexDump.rb -t 0 -c -w 16 -b 4 -p 100 ut-save_file-k.mrw | less -RS
  EXPECT_EQ(RkRamCanvas.readRAWfile("../data/utest/ut-save_file-k.mrw"), 0);
  EXPECT_TRUE(RkRamCanvas.isEqual(kRamCanvas));

  // I checked this file qby hand on 2022-08-28. sha256: 007879b182639b37a54358067f742c86bccb1ec0cb85a67a9f648ebf56c44294
  // I did the conversion by hand, so I should double check it...
  // hexDump.rb -t -1 -c -w 16 -b 8 -p 100 ut-save_file-l.mrw | less -RS
  EXPECT_EQ(RlRamCanvas.readRAWfile("../data/utest/ut-save_file-l.mrw"), 0);
  EXPECT_TRUE(RlRamCanvas.isEqual(lRamCanvas));
}
