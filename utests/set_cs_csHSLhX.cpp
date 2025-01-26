// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      set_cs_csHSLhX.cpp
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
TEST(set_cs_csHSLhX, Comprehensive) {

  ////////////////////////////////////////////////////////////////////////////////

  mjr::colorRGBA8b aColor;

  aColor.setToWhite();
  mjr::colorRGBA8b::csHSLhB::c(aColor, mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGB8b::maxChanVal); // unchanged

  aColor.setToBlack();
  mjr::colorRGBA8b::csHSLhB::c(aColor, mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGB8b::minChanVal); // unchanged

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::minChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::minChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::minChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);  // wrap
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::minChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::minChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::minChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);  // wrap
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::maxChanVal, 0.00001); // Note for floating point clrChanT, csHSLh_tpl gets to maxChanVal

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::maxChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::minChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::maxChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::minChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);  // wrap to zoeo -- not meanChanVal.  One of the oddities of floating pont wrap.
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);
}
