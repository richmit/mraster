// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_rgb_ColorSpace.cpp
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
TEST(c_set_rgb_ColorSpace, unsigned8) {

  mjr::colorRGB8b  aColor, bColor;
  mjr::colorRGBA8b cColor, dColor;

  ////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::RGB, 0, 0.5, 1);
  EXPECT_EQ(aColor.getRed(),    mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getGreen(),  mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(aColor.getBlue(),   mjr::colorRGB8b::maxChanVal);

  cColor.setToWhite();
  cColor.setRGBfromColorSpace(mjr::colorRGBA8b::colorSpaceEnum::RGB, 0, 0.5, 1);
  EXPECT_EQ(cColor.getRed(),    mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getGreen(),  mjr::colorRGBA8b::meanChanVal);
  EXPECT_EQ(cColor.getBlue(),   mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getAlpha(),  0xFF); // Not set

  cColor.setToBlack();
  cColor.setRGBfromColorSpace(mjr::colorRGBA8b::colorSpaceEnum::RGB, 0, 0.5, 1);
  EXPECT_EQ(cColor.getRed(),    mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getGreen(),  mjr::colorRGBA8b::meanChanVal);
  EXPECT_EQ(cColor.getBlue(),   mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getAlpha(),  0x00); // Not set

  for(double r=0; r<1.0; r=r+0.1)
    for(double g=0; g<1.0; g=g+0.1)
      for(double b=0; b<1.0; b=b+0.1) // TEST x 1000
        EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::RGB, r, g, b).isEqualRGB(bColor.setChansRGB_dbl(r, g, b)));

  ////////////////////////////////////////////////////////////////////////////////

  // HSL & HSV are pretty well tested elseware.

  ////////////////////////////////////////////////////////////////////////////////
  //   0-100 reals   reals
  //   0.0,    0.0,    0.0               0.00000000000000,   0.00000000000000,   0.00000000000000
  //   0.0, -100.0,    0.0               0.00000000000000,  42.50011693400831,   0.00000000000000
  //   0.0,  100.0,    0.0              96.73833014676526,   0.00000000000000,   6.73101465756404
  //   0.0,    0.0, -100.0               0.00000000000000,  28.17831280013103, 148.60141206787873
  //   0.0,    0.0,  100.0              52.41394321977139,   0.00000000000000,   0.00000000000000
  // 100.0,    0.0,    0.0             255.00000000000000, 255.00000000000000, 254.98144635564927
  //  50.0,   50.0,   50.0             206.61345904246030,  75.47718797538901,  33.52976908891374
  //  50.0,  -50.0,   50.0              35.14702068347071, 137.45770493758675,  16.12671766273848
  //  50.0,  -50.0,  -50.0               0.00000000000000, 143.15667349842120, 203.43118280505934
  //  50.0,   50.0,  -50.0             157.75797959913612,  86.69682271747450, 204.99202043092524

  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(  0,   0,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0, -100.0,    0.0).isEqualRGB(bColor.setChansRGB(  0,  42,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,  100.0,    0.0).isEqualRGB(bColor.setChansRGB( 96,   0,   6)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,    0.0, -100.0).isEqualRGB(bColor.setChansRGB(  0,  28, 148)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,    0.0,  100.0).isEqualRGB(bColor.setChansRGB( 52,   0,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB, 100.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(255, 255, 254)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,   50.0,   50.0).isEqualRGB(bColor.setChansRGB(206,  75,  33)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,  -50.0,   50.0).isEqualRGB(bColor.setChansRGB( 35, 137,  16)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,  -50.0,  -50.0).isEqualRGB(bColor.setChansRGB(  0, 143, 203)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,   50.0,  -50.0).isEqualRGB(bColor.setChansRGB(157,  86, 204)));

  ////////////////////////////////////////////////////////////////////////////////
  //   0-1     0-1     0-1
  //   0.0,    0.0,    0.0            0.00000000000000,   0.00000000000000,   0.00000000000000
  //   1.0,    0.0,    0.0           50.42455181463890,   0.00000000000000,   1.83509220000000
  //   0.0,    1.0,    0.0            0.00000000000000,  37.29504496314512,   0.00000000000000
  //   0.0,    0.0,    1.0            0.00000000000000,   1.36725900000000,  26.38515827433519
  //   1.0,    1.0,    0.0           35.27435545247001,  23.88691519243730,   0.00000000000000
  //   1.0,    0.0,    1.0           46.09063114907088,   0.00000000000000,  27.25916547197178
  //   0.0,    1.0,    1.0            0.00000000000000,  37.76511040594671,  22.93126475355600

  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB( 0,   0,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   1.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(50,   0,   1)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    1.0,    0.0).isEqualRGB(bColor.setChansRGB( 0,  37,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    0.0,    1.0).isEqualRGB(bColor.setChansRGB( 0,   1,  26)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   1.0,    1.0,    0.0).isEqualRGB(bColor.setChansRGB(35,  23,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   1.0,    0.0,    1.0).isEqualRGB(bColor.setChansRGB(46,   0,  27)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    1.0,    1.0).isEqualRGB(bColor.setChansRGB( 0,  37,  22)));

  ////////////////////////////////////////////////////////////////////////////////
  //   0-100 0-100   0-360
  //   0.0,    0.0,    0.0             0.00000000000000,   0.00000000000000,   0.00000000000000
  //   0.0,  100.0,    0.0            96.73833014676526,   0.00000000000000,   6.73101465756404
  //   0.0,   50.0,    0.0            57.41225747257089,   0.00000000000000,   2.34936006058456
  //   0.0,    0.0,  180.0             0.00000000000000,   0.00000000000000,   0.00000000000000
  //   0.0,   50.0,  180.0             0.00000000000000,  28.32099136175329,   0.00000000000000
  //  50.0,   50.0,  180.0             0.00000000000000, 139.16169169667540, 117.60474230139480
  // 100.0,  100.0,  360.0           255.00000000000000, 155.40224018978810, 255.00000000000000
  // 100.0,  100.0,  180.0             0.00000000000000, 255.00000000000000, 252.06306109593692
  // 100.0,  100.0,   60.0           255.00000000000000, 211.98994181103800,  78.02765922273178

  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(  0,   0,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,  100.0,    0.0).isEqualRGB(bColor.setChansRGB( 96,   0,   6)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,   50.0,    0.0).isEqualRGB(bColor.setChansRGB( 57,   0,   2)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,    0.0,  180.0).isEqualRGB(bColor.setChansRGB(  0,   0,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,   50.0,  180.0).isEqualRGB(bColor.setChansRGB(  0,  28,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,  50.0,   50.0,  180.0).isEqualRGB(bColor.setChansRGB(  0, 139, 117)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH, 100.0,  100.0,  360.0).isEqualRGB(bColor.setChansRGB(255, 155, 255)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH, 100.0,  100.0,  180.0).isEqualRGB(bColor.setChansRGB(  0, 255, 252)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH, 100.0,  100.0,   60.0).isEqualRGB(bColor.setChansRGB(255, 211,  78)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_rgb_ColorSpace, unsigned16) {

  mjr::colorRGB16b gColor, hColor;

  ////////////////////////////////////////////////////////////////////////////////
  gColor.setRGBfromColorSpace(mjr::colorRGB16b::colorSpaceEnum::RGB, 0, 0.5, 1);
  EXPECT_EQ(gColor.getRed(),    mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(gColor.getGreen(),  mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(gColor.getBlue(),   mjr::colorRGB16b::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_rgb_ColorSpace, float32) {

  mjr::colorRGB32F eColor, fColor;

  ////////////////////////////////////////////////////////////////////////////////

  eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::RGB, 0, 0.5, 1);
  EXPECT_EQ(eColor.getRed(),    mjr::colorRGB32F::minChanVal);
  EXPECT_EQ(eColor.getGreen(),  mjr::colorRGB32F::meanChanVal);
  EXPECT_EQ(eColor.getBlue(),   mjr::colorRGB32F::maxChanVal);

  for(double r=0; r<1.0; r=r+0.1)
    for(double g=0; g<1.0; g=g+0.1)
      for(double b=0; b<1.0; b=b+0.1) // TEST x 1000

  ////////////////////////////////////////////////////////////////////////////////

  // HSL & HSV are pretty well tested elseware.

  ////////////////////////////////////////////////////////////////////////////////
  //   0-100 reals   reals
  //   0.0,    0.0,    0.0               0.00000000000000,   0.00000000000000,   0.00000000000000
  //   0.0, -100.0,    0.0               0.00000000000000,  42.50011693400831,   0.00000000000000
  //   0.0,  100.0,    0.0              96.73833014676526,   0.00000000000000,   6.73101465756404
  //   0.0,    0.0, -100.0               0.00000000000000,  28.17831280013103, 148.60141206787873
  //   0.0,    0.0,  100.0              52.41394321977139,   0.00000000000000,   0.00000000000000
  // 100.0,    0.0,    0.0             255.00000000000000, 255.00000000000000, 254.98144635564927
  //  50.0,   50.0,   50.0             206.61345904246030,  75.47718797538901,  33.52976908891374
  //  50.0,  -50.0,   50.0              35.14702068347071, 137.45770493758675,  16.12671766273848
  //  50.0,  -50.0,  -50.0               0.00000000000000, 143.15667349842120, 203.43118280505934
  //  50.0,   50.0,  -50.0             157.75797959913612,  86.69682271747450, 204.99202043092524

  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0, -100.0,    0.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,  42.50011693400831F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,  100.0,    0.0).isCloseRGB(fColor.setChansRGB( 96.73833014676526F/255.0F,   0.00000000000000F/255.0F,   6.73101465756404F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,    0.0, -100.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,  28.17831280013103F/255.0F, 148.60141206787873F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,    0.0,  100.0).isCloseRGB(fColor.setChansRGB( 52.41394321977139F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB, 100.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(255.00000000000000F/255.0F, 255.00000000000000F/255.0F, 254.98144635564927F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,   50.0,   50.0).isCloseRGB(fColor.setChansRGB(206.61345904246030F/255.0F,  75.47718797538901F/255.0F,  33.52976908891374F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,  -50.0,   50.0).isCloseRGB(fColor.setChansRGB( 35.14702068347071F/255.0F, 137.45770493758675F/255.0F,  16.12671766273848F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,  -50.0,  -50.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F, 143.15667349842120F/255.0F, 203.43118280505934F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,   50.0,  -50.0).isCloseRGB(fColor.setChansRGB(157.75797959913612F/255.0F,  86.69682271747450F/255.0F, 204.99202043092524F/255.0F), 0.00001F));

  ////////////////////////////////////////////////////////////////////////////////
  //   0-1     0-1     0-1
  //   0.0,    0.0,    0.0            0.00000000000000,   0.00000000000000,   0.00000000000000
  //   1.0,    0.0,    0.0           50.42455181463890,   0.00000000000000,   1.83509220000000
  //   0.0,    1.0,    0.0            0.00000000000000,  37.29504496314512,   0.00000000000000
  //   0.0,    0.0,    1.0            0.00000000000000,   1.36725900000000,  26.38515827433519
  //   1.0,    1.0,    0.0           35.27435545247001,  23.88691519243730,   0.00000000000000
  //   1.0,    0.0,    1.0           46.09063114907088,   0.00000000000000,  27.25916547197178
  //   0.0,    1.0,    1.0            0.00000000000000,  37.76511040594671,  22.93126475355600

  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 1.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(50.42455181463890F/255.0F,   0.00000000000000F/255.0F,   1.83509220000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    1.0,    0.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,  37.29504496314512F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    0.0,    1.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,   1.36725900000000F/255.0F,  26.38515827433519F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 1.0,    1.0,    0.0).isCloseRGB(fColor.setChansRGB(35.27435545247001F/255.0F,  23.88691519243730F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 1.0,    0.0,    1.0).isCloseRGB(fColor.setChansRGB(46.09063114907088F/255.0F,   0.00000000000000F/255.0F,  27.25916547197178F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    1.0,    1.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,  37.76511040594671F/255.0F,  22.93126475355600F/255.0F), 0.00001F));

  ////////////////////////////////////////////////////////////////////////////////
  //   0-100 0-100   0-360
  //   0.0,    0.0,    0.0             0.00000000000000,   0.00000000000000,   0.00000000000000
  //   0.0,  100.0,    0.0            96.73833014676526,   0.00000000000000,   6.73101465756404
  //   0.0,   50.0,    0.0            57.41225747257089,   0.00000000000000,   2.34936006058456
  //   0.0,    0.0,  180.0             0.00000000000000,   0.00000000000000,   0.00000000000000
  //   0.0,   50.0,  180.0             0.00000000000000,  28.32099136175329,   0.00000000000000
  //  50.0,   50.0,  180.0             0.00000000000000, 139.16169169667540, 117.60474230139480
  // 100.0,  100.0,  360.0           255.00000000000000, 155.40224018978810, 255.00000000000000
  // 100.0,  100.0,  180.0             0.00000000000000, 255.00000000000000, 252.06306109593692
  // 100.0,  100.0,   60.0           255.00000000000000, 211.98994181103800,  78.02765922273178

  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,  100.0,    0.0).isCloseRGB(fColor.setChansRGB( 96.73833014676526F/255.0F,   0.00000000000000F/255.0F,   6.73101465756404F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,   50.0,    0.0).isCloseRGB(fColor.setChansRGB( 57.41225747257089F/255.0F,   0.00000000000000F/255.0F,   2.34936006058456F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,    0.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,   50.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,  28.32099136175329F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,  50.0,   50.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F, 139.16169169667540F/255.0F, 117.60474230139480F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH, 100.0,  100.0,  360.0).isCloseRGB(fColor.setChansRGB(255.00000000000000F/255.0F, 155.40224018978810F/255.0F, 255.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH, 100.0,  100.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F, 255.00000000000000F/255.0F, 252.06306109593692F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH, 100.0,  100.0,   60.0).isCloseRGB(fColor.setChansRGB(255.00000000000000F/255.0F, 211.98994181103800F/255.0F,  78.02765922273178F/255.0F), 0.00001F));
}
