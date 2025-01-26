// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_cs_csCBSpectral.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2025-01-25
 @brief     Unit tests for basic color methods.@EOL
 @keywords  boost
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
TEST(c_set_cs_csCBSpectral, int_in_unsigned8_out) {

  mjr::colorRGBA8b  aColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0,  3).isEqualRGB(aColor.setChansRGB(252, 141,  89))); // smallest
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1,  3).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2,  3).isEqualRGB(aColor.setChansRGB(153, 213, 148)));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0, 11).isEqualRGB(aColor.setChansRGB(158,   1,  66))); // biggest
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1, 11).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2, 11).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3, 11).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4, 11).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5, 11).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6, 11).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7, 11).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8, 11).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9, 11).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10, 11).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3,  3).isEqualRGB(aColor.setChansRGB(252, 141,  89))); // wrap index
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4,  3).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5,  3).isEqualRGB(aColor.setChansRGB(153, 213, 148)));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(11, 11).isEqualRGB(aColor.setChansRGB(158,   1,  66))); // wrap index
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(12, 11).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(13, 11).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(14, 11).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(15, 11).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(16, 11).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(17, 11).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(18, 11).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(19, 11).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(20, 11).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(21, 11).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0    ).isEqualRGB(aColor.setChansRGB(158,   1,  66)));  // missing -> 11
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1    ).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2    ).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3    ).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4    ).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5    ).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6    ).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7    ).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8    ).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9    ).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10    ).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0,  1).isEqualRGB(aColor.setChansRGB(252, 141,  89)));  // too small -> 3
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1,  1).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2,  1).isEqualRGB(aColor.setChansRGB(153, 213, 148)));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0, 50).isEqualRGB(aColor.setChansRGB(158,   1,  66)));  // too big -> 11
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1, 50).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2, 50).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3, 50).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4, 50).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5, 50).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6, 50).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7, 50).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8, 50).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9, 50).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10, 50).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0, 3);
  EXPECT_EQ(aColor.getRed(),    252);
  EXPECT_EQ(aColor.getGreen(),  141);
  EXPECT_EQ(aColor.getBlue(),    89);
  EXPECT_EQ(aColor.getAlpha(),    mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0, 3);
  EXPECT_EQ(aColor.getRed(),     252);
  EXPECT_EQ(aColor.getGreen(),   141);
  EXPECT_EQ(aColor.getBlue(),     89);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal); // Not set!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_cs_csCBSpectral, int_in_float32_out) {

  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0,  3).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F)); // smallest
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2,  3).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0, 11).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F)); // biggest
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10, 11).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3,  3).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F)); // wrap index
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5,  3).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(11, 11).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F)); // wrap index
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(12, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(13, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(14, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(15, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(16, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(17, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(18, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(19, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(20, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(21, 11).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0    ).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // missing -> 11
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1    ).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2    ).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3    ).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4    ).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5    ).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6    ).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7    ).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8    ).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9    ).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10    ).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0,  1).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F));  // too small -> 3
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1,  1).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2,  1).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0, 50).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // too big -> 11
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1, 50).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2, 50).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3, 50).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4, 50).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5, 50).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6, 50).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7, 50).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8, 50).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9, 50).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10, 50).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0, 3);
  EXPECT_EQ(bColor.getAlpha(),    mjr::colorRGBA32F::minChanVal); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0, 3);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA32F::maxChanVal); // Not set!

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_cs_csCBSpectral, float_in_unsigned8_out) {

  mjr::colorRGBA8b  aColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  0/2.0F,  3).isCloseRGB(aColor.setChansRGB(252, 141,  89), 2)); // smallest
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  1/2.0F,  3).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  2/2.0F,  3).isCloseRGB(aColor.setChansRGB(153, 213, 148), 2));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0/10.0F, 11).isCloseRGB(aColor.setChansRGB(158,   1,  66), 2)); // biggest
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1/10.0F, 11).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2/10.0F, 11).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3/10.0F, 11).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4/10.0F, 11).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5/10.0F, 11).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6/10.0F, 11).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7/10.0F, 11).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8/10.0F, 11).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9/10.0F, 11).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10/10.0F, 11).isCloseRGB(aColor.setChansRGB( 94,  79, 162), 2));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  3/2.0F,  3).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2)); // wrap index

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 1/10.0F, 11).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2)); // wrap index
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 2/10.0F, 11).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 3/10.0F, 11).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 4/10.0F, 11).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 5/10.0F, 11).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 6/10.0F, 11).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 7/10.0F, 11).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 8/10.0F, 11).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 9/10.0F, 11).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0/10.0F    ).isCloseRGB(aColor.setChansRGB(158,   1,  66), 2));  // missing -> 11
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1/10.0F    ).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2/10.0F    ).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3/10.0F    ).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4/10.0F    ).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5/10.0F    ).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6/10.0F    ).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7/10.0F    ).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8/10.0F    ).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9/10.0F    ).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10/10.0F    ).isCloseRGB(aColor.setChansRGB( 94,  79, 162), 2));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  0/2.0F,  1).isCloseRGB(aColor.setChansRGB(252, 141,  89), 2));  // too small -> 3
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  1/2.0F,  1).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  2/2.0F,  1).isCloseRGB(aColor.setChansRGB(153, 213, 148), 2));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0/10.0F, 50).isCloseRGB(aColor.setChansRGB(158,   1,  66), 2));  // too big -> 11
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1/10.0F, 50).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2/10.0F, 50).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3/10.0F, 50).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4/10.0F, 50).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5/10.0F, 50).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6/10.0F, 50).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7/10.0F, 50).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8/10.0F, 50).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9/10.0F, 50).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10/10.0F, 50).isCloseRGB(aColor.setChansRGB( 94,  79, 162), 2));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0/2.0F, 3);
  EXPECT_EQ(aColor.getAlpha(),    mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0/2.0F, 3);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal); // Not set!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_cs_csCBSpectral, float_in_float32_out) {

  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0/2.0F,  3).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F)); // smallest
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1/2.0F,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2/2.0F,  3).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0/10.0F, 11).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F)); // biggest
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1/10.0F, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2/10.0F, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3/10.0F, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4/10.0F, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5/10.0F, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6/10.0F, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7/10.0F, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8/10.0F, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9/10.0F, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10/10.0F, 11).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3/2.0F,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+1/10.0F, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+2/10.0F, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+3/10.0F, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+4/10.0F, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+5/10.0F, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+6/10.0F, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+7/10.0F, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+8/10.0F, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+9/10.0F, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));

// ////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0/10.0F    ).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // missing -> 11
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1/10.0F    ).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2/10.0F    ).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3/10.0F    ).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4/10.0F    ).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5/10.0F    ).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6/10.0F    ).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7/10.0F    ).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8/10.0F    ).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9/10.0F    ).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10/10.0F    ).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0/2.0F,  1).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F));  // too small -> 3
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1/2.0F,  1).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2/2.0F,  1).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0/10.0F, 50).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // too big -> 11
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1/10.0F, 50).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2/10.0F, 50).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3/10.0F, 50).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4/10.0F, 50).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5/10.0F, 50).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6/10.0F, 50).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7/10.0F, 50).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8/10.0F, 50).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9/10.0F, 50).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10/10.0F, 50).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0/2.0F, 3);
  EXPECT_EQ(bColor.getAlpha(),    mjr::colorRGBA32F::minChanVal); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0/2.0F, 3);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA32F::maxChanVal); // Not set!
}
