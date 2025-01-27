// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_comp_rgb2colorSpace.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2025-01-25
 @brief     Unit tests for basic color methods.@EOL
 @keywords  gtest
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
#include "MRcolor.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_comp_rgb2colorSpace, unsigned8) {

  mjr::colorRGB8b              aColor;
  mjr::colorRGB8b::colConDbl3  bColor;

  ////////////////////////////////////////////////////////////////////////////////

  aColor.setChansRGB(mjr::colorRGB8b::minChanVal, mjr::colorRGB8b::meanChanVal, mjr::colorRGB8b::maxChanVal);
  bColor = aColor.rgb2colorSpace(mjr::colorRGB8b::colorSpaceEnum::RGB);
  EXPECT_NEAR(bColor.getC0(),  0.0,    0.00001);
  EXPECT_NEAR(bColor.getC1(),  0.5,    0.01);        // Can't get much accuracy with 8-bit
  EXPECT_NEAR(bColor.getC2(),  1.0,    0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_comp_rgb2colorSpace, unsigned16) {

  mjr::colorRGB16b             eColor;
  mjr::colorRGB16b::colConDbl3 fColor;

  ////////////////////////////////////////////////////////////////////////////////

  eColor.setChansRGB(mjr::colorRGB16b::minChanVal, mjr::colorRGB16b::meanChanVal, mjr::colorRGB16b::maxChanVal);
  fColor = eColor.rgb2colorSpace(mjr::colorRGB16b::colorSpaceEnum::RGB);
  EXPECT_NEAR(fColor.getC0(),  0.0,    0.00001);
  EXPECT_NEAR(fColor.getC1(),  0.5,    0.0001);      // A bit more accuracy with 16-bit
  EXPECT_NEAR(fColor.getC2(),  1.0,    0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_comp_rgb2colorSpace, unsigned32) {

  mjr::colorRGB32b             gColor;
  mjr::colorRGB32b::colConDbl3 hColor;

  ////////////////////////////////////////////////////////////////////////////////

  gColor.setChansRGB(mjr::colorRGB32b::minChanVal, mjr::colorRGB32b::meanChanVal, mjr::colorRGB32b::maxChanVal);
  hColor = gColor.rgb2colorSpace(mjr::colorRGB32b::colorSpaceEnum::RGB);
  EXPECT_NEAR(hColor.getC0(),  0.0,    0.00001);
  EXPECT_NEAR(hColor.getC1(),  0.5,    0.00001);     // A bit more accuracy with 32-bit
  EXPECT_NEAR(hColor.getC2(),  1.0,    0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_comp_rgb2colorSpace, float32) {

  mjr::colorRGB32F             cColor;
  mjr::colorRGB32F::colConDbl3 dColor;

  ////////////////////////////////////////////////////////////////////////////////

  //   0.00000000000000   0.5000000000000000   1.00000000000000000 RGB
  // 210.11764705181122   1.0000000000000000   0.50000000000000000 HSL
  // 210.11764705181122   1.0000000000000000   1.00000000000000000 HSV
  //  54.58302990500775  19.1017817806751750 -71.14430025970830000 LAB
  //  25.704111183644635 22.5282223672892700  97.60137039454821000 XYZ
  //  54.58302990500775  73.6640314308147600 285.02909316255295000 LCH

  cColor.setChansRGB(mjr::colorRGB32F::minChanVal, mjr::colorRGB32F::meanChanVal, mjr::colorRGB32F::maxChanVal);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::RGB);
  EXPECT_NEAR(dColor.getC0(),    0.000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC1(),    0.500000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    1.000000000000000, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::HSL);
  EXPECT_NEAR(dColor.getC0(),  210.000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC1(),    1.000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    0.500000000000000, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::HSV);
  EXPECT_NEAR(dColor.getC0(),  210.000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC1(),    1.000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    1.000000000000000, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB);
  EXPECT_NEAR(dColor.getC0(),   54.583029905007749, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   19.106431157445371, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  -71.140167945193781, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ);
  EXPECT_NEAR(dColor.getC0(),   25.704111183644635, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   22.528222367289271, 0.00001);
  EXPECT_NEAR(dColor.getC2(),   97.601370394548212, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH);
  EXPECT_NEAR(dColor.getC0(),   54.583029905007749, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   73.661246302547553, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  285.033419356169360, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////

  //   0.400000000000000   0.6000000000000000   0.800000000000000 RGB
  // 209.999996870756100   0.4999999962747098   0.600000002980232 HSL
  // 209.999996870756100   0.5000000000000000   0.800000000000000 HSV
  //  61.625634479116870  -2.8148222106305076 -31.439123763222420 LAB
  //  27.769805832971585  29.9668794742762760  61.447302014049825 XYZ
  //  61.625634479116870  31.5648812302006830 264.883809161551100 LCH

  cColor.setChansRGB_dbl(0.4, 0.6, 0.8);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::RGB);
  EXPECT_NEAR(dColor.getC0(),     0.400000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC1(),    0.6000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC2(),     0.800000000000000, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::HSL);
  EXPECT_NEAR(dColor.getC0(),  209.999996870756100, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   0.4999999962747098, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    0.600000002980232, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::HSV);
  EXPECT_NEAR(dColor.getC0(),  209.999996870756100, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   0.5000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    0.800000000000000, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB);
  EXPECT_NEAR(dColor.getC0(),   61.625634479116870, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  -2.8148222106305076, 0.01);           //  MJR TODO NOTE  Why?  Need to check into the inaccuracy here.
  EXPECT_NEAR(dColor.getC2(),  -31.439123763222420, 0.01);           //  MJR TODO NOTE  Why?  Need to check into the inaccuracy here.

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ);
  EXPECT_NEAR(dColor.getC0(),    27.769805832971585, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   29.9668794742762760, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    61.447302014049825, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH);
  EXPECT_NEAR(dColor.getC0(),   61.625634479116870, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  31.5648812302006830, 0.01);           //  MJR TODO NOTE  Why?  Need to check into the inaccuracy here.
  EXPECT_NEAR(dColor.getC2(),  264.883809161551100, 0.01);           //  MJR TODO NOTE  Why?  Need to check into the inaccuracy here.
}
