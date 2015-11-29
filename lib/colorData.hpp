// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
   @file      colorData.hpp
   @author    Mitch Richling <http://www.mitchr.me>
   @brief     Header for the colorData array declaration@EOL 
   @copyright 
   @parblock
   Copyright (c) 1988-2015, Mitchell Jay Richling <http://www.mitchr.me> All rights reserved.

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
***************************************************************************************************************************************************************/

#ifndef MJR_INCLUDE_colorData

// Put everything in the mjr namespace
namespace mjr {

/** Color Matching Functions as tabulated in table 3 from Stockman and Sharpe (2000).  I beleive they are taken from Stiles and Burch 10-degree (1959)*/
    extern const float colMatchPoints[89][4];

/** An enumeration of all the web safe colors as well as transformations of the web safe colors into various formas as seen by color blind people.  The first
    and last elements of the arrays are black and white -- so the array is 218 elemnets long. */
    extern const char *webSafeColorData[218][7];

/** Color scheme known as icp_uO_BrBu_10 (Brown to Blue, 10 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BrBu_10[13];

/** Color scheme known as icp_uO_BrBu_12 (Brown to Blue, 12 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BrBu_12[15];

/** Color scheme known as icp_uO_BuDOr_12 (Blue to Dark Orange, 12 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BuDOr_12[15];

/** Color scheme known as icp_uO_BuDOr_18 (Blue to Dark Orange, 18 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BuDOr_18[21];

/** Color scheme known as icp_uO_BuDRd_12 (Dark Red to Blue, 12 steps, based on ColorBrewer RdYlBu_11) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BuDRd_12[15];

/** Color scheme known as icp_uO_BuDRd_18 (Dark Red to Blue, 18 steps, based on ColorBrewer RdYlBu_11) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BuDRd_18[21];

/** Color scheme known as icp_uO_BuGr_14 (Blue-Green) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BuGr_14[17];

/** Color scheme known as icp_uO_BuGy_8 (Blue to Gray, 8 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BuGy_8[11];

/** Color scheme known as icp_uO_BuOrR_14 (Blue to Orange Red, 14 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BuOrR_14[17];

/** Color scheme known as icp_uO_BuOr_12 (Blue to Orange, 12 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BuOr_12[15];

/** Color scheme known as icp_uO_BuOr_8 (Blue to Orange, 8 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_BuOr_8[11];

/** Color scheme known as icp_uO_Bu_10 (Light blue to dark blue, 10 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_Bu_10[13];

/** Color scheme known as icp_uO_Bu_7 (Light Blue to Dark Blue, 7 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_Bu_7[10];

/** Color scheme known as icp_uO_Cat_12 (Categorical 12-step scheme, after ColorBrewer 11-step Paired Scheme) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_Cat_12[15];

/** Color scheme known as icp_uO_GrMg_16 (Green to Magenta, 16 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_GrMg_16[19];

/** Color scheme known as icp_uO_RdYlBu_11b (RdYlBu_11b (Hue fixed for protans, after ColorBrewer RdYlBu)) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_RdYlBu_11b[14];

/** Color scheme known as icp_uO_StepSeq_25 (Stepped sequential scheme, 5 steps) from U of Oregon (Dept of geography) */
    extern const char *icp_uO_StepSeq_25[28];

/** Color scheme known as icp_CB_Accent_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Accent_03[6];

/** Color scheme known as icp_CB_Accent_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Accent_04[7];

/** Color scheme known as icp_CB_Accent_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Accent_05[8];

/** Color scheme known as icp_CB_Accent_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Accent_06[9];

/** Color scheme known as icp_CB_Accent_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Accent_07[10];

/** Color scheme known as icp_CB_Accent_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Accent_08[11];

/** Color scheme known as icp_CB_Blues_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Blues_03[6];

/** Color scheme known as icp_CB_Blues_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Blues_04[7];

/** Color scheme known as icp_CB_Blues_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Blues_05[8];

/** Color scheme known as icp_CB_Blues_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Blues_06[9];

/** Color scheme known as icp_CB_Blues_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Blues_07[10];

/** Color scheme known as icp_CB_Blues_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Blues_08[11];

/** Color scheme known as icp_CB_Blues_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Blues_09[12];

/** Color scheme known as icp_CB_BrBG_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_BrBG_03[6];

/** Color scheme known as icp_CB_BrBG_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_BrBG_04[7];

/** Color scheme known as icp_CB_BrBG_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_BrBG_05[8];

/** Color scheme known as icp_CB_BrBG_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_BrBG_06[9];

/** Color scheme known as icp_CB_BrBG_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_BrBG_07[10];

/** Color scheme known as icp_CB_BrBG_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_BrBG_08[11];

/** Color scheme known as icp_CB_BrBG_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_BrBG_09[12];

/** Color scheme known as icp_CB_BrBG_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_BrBG_10[13];

/** Color scheme known as icp_CB_BrBG_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_BrBG_11[14];

/** Color scheme known as icp_CB_BuGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuGn_03[6];

/** Color scheme known as icp_CB_BuGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuGn_04[7];

/** Color scheme known as icp_CB_BuGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuGn_05[8];

/** Color scheme known as icp_CB_BuGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuGn_06[9];

/** Color scheme known as icp_CB_BuGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuGn_07[10];

/** Color scheme known as icp_CB_BuGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuGn_08[11];

/** Color scheme known as icp_CB_BuGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuGn_09[12];

/** Color scheme known as icp_CB_BuPu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuPu_03[6];

/** Color scheme known as icp_CB_BuPu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuPu_04[7];

/** Color scheme known as icp_CB_BuPu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuPu_05[8];

/** Color scheme known as icp_CB_BuPu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuPu_06[9];

/** Color scheme known as icp_CB_BuPu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuPu_07[10];

/** Color scheme known as icp_CB_BuPu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuPu_08[11];

/** Color scheme known as icp_CB_BuPu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_BuPu_09[12];

/** Color scheme known as icp_CB_Dark2_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Dark2_03[6];

/** Color scheme known as icp_CB_Dark2_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Dark2_04[7];

/** Color scheme known as icp_CB_Dark2_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Dark2_05[8];

/** Color scheme known as icp_CB_Dark2_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Dark2_06[9];

/** Color scheme known as icp_CB_Dark2_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Dark2_07[10];

/** Color scheme known as icp_CB_Dark2_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Dark2_08[11];

/** Color scheme known as icp_CB_GnBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_GnBu_03[6];

/** Color scheme known as icp_CB_GnBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_GnBu_04[7];

/** Color scheme known as icp_CB_GnBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_GnBu_05[8];

/** Color scheme known as icp_CB_GnBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_GnBu_06[9];

/** Color scheme known as icp_CB_GnBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_GnBu_07[10];

/** Color scheme known as icp_CB_GnBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_GnBu_08[11];

/** Color scheme known as icp_CB_GnBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_GnBu_09[12];

/** Color scheme known as icp_CB_Greens_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greens_03[6];

/** Color scheme known as icp_CB_Greens_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greens_04[7];

/** Color scheme known as icp_CB_Greens_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greens_05[8];

/** Color scheme known as icp_CB_Greens_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greens_06[9];

/** Color scheme known as icp_CB_Greens_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greens_07[10];

/** Color scheme known as icp_CB_Greens_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greens_08[11];

/** Color scheme known as icp_CB_Greens_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greens_09[12];

/** Color scheme known as icp_CB_Greys_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greys_03[6];

/** Color scheme known as icp_CB_Greys_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greys_04[7];

/** Color scheme known as icp_CB_Greys_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greys_05[8];

/** Color scheme known as icp_CB_Greys_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greys_06[9];

/** Color scheme known as icp_CB_Greys_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greys_07[10];

/** Color scheme known as icp_CB_Greys_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greys_08[11];

/** Color scheme known as icp_CB_Greys_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Greys_09[12];

/** Color scheme known as icp_CB_OrRd_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_OrRd_03[6];

/** Color scheme known as icp_CB_OrRd_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_OrRd_04[7];

/** Color scheme known as icp_CB_OrRd_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_OrRd_05[8];

/** Color scheme known as icp_CB_OrRd_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_OrRd_06[9];

/** Color scheme known as icp_CB_OrRd_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_OrRd_07[10];

/** Color scheme known as icp_CB_OrRd_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_OrRd_08[11];

/** Color scheme known as icp_CB_OrRd_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_OrRd_09[12];

/** Color scheme known as icp_CB_Oranges_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Oranges_03[6];

/** Color scheme known as icp_CB_Oranges_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Oranges_04[7];

/** Color scheme known as icp_CB_Oranges_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Oranges_05[8];

/** Color scheme known as icp_CB_Oranges_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Oranges_06[9];

/** Color scheme known as icp_CB_Oranges_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Oranges_07[10];

/** Color scheme known as icp_CB_Oranges_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Oranges_08[11];

/** Color scheme known as icp_CB_Oranges_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Oranges_09[12];

/** Color scheme known as icp_CB_PRGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PRGn_03[6];

/** Color scheme known as icp_CB_PRGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PRGn_04[7];

/** Color scheme known as icp_CB_PRGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PRGn_05[8];

/** Color scheme known as icp_CB_PRGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PRGn_06[9];

/** Color scheme known as icp_CB_PRGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PRGn_07[10];

/** Color scheme known as icp_CB_PRGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PRGn_08[11];

/** Color scheme known as icp_CB_PRGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PRGn_09[12];

/** Color scheme known as icp_CB_PRGn_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PRGn_10[13];

/** Color scheme known as icp_CB_PRGn_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PRGn_11[14];

/** Color scheme known as icp_CB_Paired_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Paired_03[6];

/** Color scheme known as icp_CB_Paired_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Paired_04[7];

/** Color scheme known as icp_CB_Paired_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Paired_05[8];

/** Color scheme known as icp_CB_Paired_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Paired_06[9];

/** Color scheme known as icp_CB_Paired_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Paired_07[10];

/** Color scheme known as icp_CB_Paired_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Paired_08[11];

/** Color scheme known as icp_CB_Paired_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Paired_09[12];

/** Color scheme known as icp_CB_Paired_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Paired_10[13];

/** Color scheme known as icp_CB_Paired_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Paired_11[14];

/** Color scheme known as icp_CB_Paired_12 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Paired_12[15];

/** Color scheme known as icp_CB_Pastel1_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel1_03[6];

/** Color scheme known as icp_CB_Pastel1_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel1_04[7];

/** Color scheme known as icp_CB_Pastel1_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel1_05[8];

/** Color scheme known as icp_CB_Pastel1_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel1_06[9];

/** Color scheme known as icp_CB_Pastel1_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel1_07[10];

/** Color scheme known as icp_CB_Pastel1_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel1_08[11];

/** Color scheme known as icp_CB_Pastel1_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel1_09[12];

/** Color scheme known as icp_CB_Pastel2_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel2_03[6];

/** Color scheme known as icp_CB_Pastel2_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel2_04[7];

/** Color scheme known as icp_CB_Pastel2_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel2_05[8];

/** Color scheme known as icp_CB_Pastel2_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel2_06[9];

/** Color scheme known as icp_CB_Pastel2_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel2_07[10];

/** Color scheme known as icp_CB_Pastel2_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Pastel2_08[11];

/** Color scheme known as icp_CB_PiYG_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PiYG_03[6];

/** Color scheme known as icp_CB_PiYG_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PiYG_04[7];

/** Color scheme known as icp_CB_PiYG_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PiYG_05[8];

/** Color scheme known as icp_CB_PiYG_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PiYG_06[9];

/** Color scheme known as icp_CB_PiYG_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PiYG_07[10];

/** Color scheme known as icp_CB_PiYG_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PiYG_08[11];

/** Color scheme known as icp_CB_PiYG_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PiYG_09[12];

/** Color scheme known as icp_CB_PiYG_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PiYG_10[13];

/** Color scheme known as icp_CB_PiYG_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PiYG_11[14];

/** Color scheme known as icp_CB_PuBuGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBuGn_03[6];

/** Color scheme known as icp_CB_PuBuGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBuGn_04[7];

/** Color scheme known as icp_CB_PuBuGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBuGn_05[8];

/** Color scheme known as icp_CB_PuBuGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBuGn_06[9];

/** Color scheme known as icp_CB_PuBuGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBuGn_07[10];

/** Color scheme known as icp_CB_PuBuGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBuGn_08[11];

/** Color scheme known as icp_CB_PuBuGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBuGn_09[12];

/** Color scheme known as icp_CB_PuBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBu_03[6];

/** Color scheme known as icp_CB_PuBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBu_04[7];

/** Color scheme known as icp_CB_PuBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBu_05[8];

/** Color scheme known as icp_CB_PuBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBu_06[9];

/** Color scheme known as icp_CB_PuBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBu_07[10];

/** Color scheme known as icp_CB_PuBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBu_08[11];

/** Color scheme known as icp_CB_PuBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuBu_09[12];

/** Color scheme known as icp_CB_PuOr_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PuOr_03[6];

/** Color scheme known as icp_CB_PuOr_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PuOr_04[7];

/** Color scheme known as icp_CB_PuOr_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PuOr_05[8];

/** Color scheme known as icp_CB_PuOr_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PuOr_06[9];

/** Color scheme known as icp_CB_PuOr_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PuOr_07[10];

/** Color scheme known as icp_CB_PuOr_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PuOr_08[11];

/** Color scheme known as icp_CB_PuOr_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PuOr_09[12];

/** Color scheme known as icp_CB_PuOr_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PuOr_10[13];

/** Color scheme known as icp_CB_PuOr_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_PuOr_11[14];

/** Color scheme known as icp_CB_PuRd_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuRd_03[6];

/** Color scheme known as icp_CB_PuRd_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuRd_04[7];

/** Color scheme known as icp_CB_PuRd_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuRd_05[8];

/** Color scheme known as icp_CB_PuRd_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuRd_06[9];

/** Color scheme known as icp_CB_PuRd_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuRd_07[10];

/** Color scheme known as icp_CB_PuRd_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuRd_08[11];

/** Color scheme known as icp_CB_PuRd_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_PuRd_09[12];

/** Color scheme known as icp_CB_Purples_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Purples_03[6];

/** Color scheme known as icp_CB_Purples_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Purples_04[7];

/** Color scheme known as icp_CB_Purples_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Purples_05[8];

/** Color scheme known as icp_CB_Purples_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Purples_06[9];

/** Color scheme known as icp_CB_Purples_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Purples_07[10];

/** Color scheme known as icp_CB_Purples_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Purples_08[11];

/** Color scheme known as icp_CB_Purples_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Purples_09[12];

/** Color scheme known as icp_CB_RdBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdBu_03[6];

/** Color scheme known as icp_CB_RdBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdBu_04[7];

/** Color scheme known as icp_CB_RdBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdBu_05[8];

/** Color scheme known as icp_CB_RdBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdBu_06[9];

/** Color scheme known as icp_CB_RdBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdBu_07[10];

/** Color scheme known as icp_CB_RdBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdBu_08[11];

/** Color scheme known as icp_CB_RdBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdBu_09[12];

/** Color scheme known as icp_CB_RdBu_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdBu_10[13];

/** Color scheme known as icp_CB_RdBu_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdBu_11[14];

/** Color scheme known as icp_CB_RdGy_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdGy_03[6];

/** Color scheme known as icp_CB_RdGy_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdGy_04[7];

/** Color scheme known as icp_CB_RdGy_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdGy_05[8];

/** Color scheme known as icp_CB_RdGy_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdGy_06[9];

/** Color scheme known as icp_CB_RdGy_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdGy_07[10];

/** Color scheme known as icp_CB_RdGy_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdGy_08[11];

/** Color scheme known as icp_CB_RdGy_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdGy_09[12];

/** Color scheme known as icp_CB_RdGy_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdGy_10[13];

/** Color scheme known as icp_CB_RdGy_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdGy_11[14];

/** Color scheme known as icp_CB_RdPu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_RdPu_03[6];

/** Color scheme known as icp_CB_RdPu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_RdPu_04[7];

/** Color scheme known as icp_CB_RdPu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_RdPu_05[8];

/** Color scheme known as icp_CB_RdPu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_RdPu_06[9];

/** Color scheme known as icp_CB_RdPu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_RdPu_07[10];

/** Color scheme known as icp_CB_RdPu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_RdPu_08[11];

/** Color scheme known as icp_CB_RdPu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_RdPu_09[12];

/** Color scheme known as icp_CB_RdYlBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlBu_03[6];

/** Color scheme known as icp_CB_RdYlBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlBu_04[7];

/** Color scheme known as icp_CB_RdYlBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlBu_05[8];

/** Color scheme known as icp_CB_RdYlBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlBu_06[9];

/** Color scheme known as icp_CB_RdYlBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlBu_07[10];

/** Color scheme known as icp_CB_RdYlBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlBu_08[11];

/** Color scheme known as icp_CB_RdYlBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlBu_09[12];

/** Color scheme known as icp_CB_RdYlBu_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlBu_10[13];

/** Color scheme known as icp_CB_RdYlBu_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlBu_11[14];

/** Color scheme known as icp_CB_RdYlGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlGn_03[6];

/** Color scheme known as icp_CB_RdYlGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlGn_04[7];

/** Color scheme known as icp_CB_RdYlGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlGn_05[8];

/** Color scheme known as icp_CB_RdYlGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlGn_06[9];

/** Color scheme known as icp_CB_RdYlGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlGn_07[10];

/** Color scheme known as icp_CB_RdYlGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlGn_08[11];

/** Color scheme known as icp_CB_RdYlGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlGn_09[12];

/** Color scheme known as icp_CB_RdYlGn_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlGn_10[13];

/** Color scheme known as icp_CB_RdYlGn_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_RdYlGn_11[14];

/** Color scheme known as icp_CB_Reds_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Reds_03[6];

/** Color scheme known as icp_CB_Reds_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Reds_04[7];

/** Color scheme known as icp_CB_Reds_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Reds_05[8];

/** Color scheme known as icp_CB_Reds_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Reds_06[9];

/** Color scheme known as icp_CB_Reds_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Reds_07[10];

/** Color scheme known as icp_CB_Reds_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Reds_08[11];

/** Color scheme known as icp_CB_Reds_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_Reds_09[12];

/** Color scheme known as icp_CB_Set1_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set1_03[6];

/** Color scheme known as icp_CB_Set1_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set1_04[7];

/** Color scheme known as icp_CB_Set1_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set1_05[8];

/** Color scheme known as icp_CB_Set1_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set1_06[9];

/** Color scheme known as icp_CB_Set1_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set1_07[10];

/** Color scheme known as icp_CB_Set1_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set1_08[11];

/** Color scheme known as icp_CB_Set1_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set1_09[12];

/** Color scheme known as icp_CB_Set2_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set2_03[6];

/** Color scheme known as icp_CB_Set2_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set2_04[7];

/** Color scheme known as icp_CB_Set2_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set2_05[8];

/** Color scheme known as icp_CB_Set2_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set2_06[9];

/** Color scheme known as icp_CB_Set2_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set2_07[10];

/** Color scheme known as icp_CB_Set2_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set2_08[11];

/** Color scheme known as icp_CB_Set3_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set3_03[6];

/** Color scheme known as icp_CB_Set3_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set3_04[7];

/** Color scheme known as icp_CB_Set3_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set3_05[8];

/** Color scheme known as icp_CB_Set3_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set3_06[9];

/** Color scheme known as icp_CB_Set3_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set3_07[10];

/** Color scheme known as icp_CB_Set3_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set3_08[11];

/** Color scheme known as icp_CB_Set3_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set3_09[12];

/** Color scheme known as icp_CB_Set3_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set3_10[13];

/** Color scheme known as icp_CB_Set3_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set3_11[14];

/** Color scheme known as icp_CB_Set3_12 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
    extern const char *icp_CB_Set3_12[15];

/** Color scheme known as icp_CB_Spectral_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_Spectral_03[6];

/** Color scheme known as icp_CB_Spectral_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_Spectral_04[7];

/** Color scheme known as icp_CB_Spectral_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_Spectral_05[8];

/** Color scheme known as icp_CB_Spectral_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_Spectral_06[9];

/** Color scheme known as icp_CB_Spectral_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_Spectral_07[10];

/** Color scheme known as icp_CB_Spectral_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_Spectral_08[11];

/** Color scheme known as icp_CB_Spectral_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_Spectral_09[12];

/** Color scheme known as icp_CB_Spectral_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_Spectral_10[13];

/** Color scheme known as icp_CB_Spectral_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
    extern const char *icp_CB_Spectral_11[14];

/** Color scheme known as icp_CB_YlGnBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGnBu_03[6];

/** Color scheme known as icp_CB_YlGnBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGnBu_04[7];

/** Color scheme known as icp_CB_YlGnBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGnBu_05[8];

/** Color scheme known as icp_CB_YlGnBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGnBu_06[9];

/** Color scheme known as icp_CB_YlGnBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGnBu_07[10];

/** Color scheme known as icp_CB_YlGnBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGnBu_08[11];

/** Color scheme known as icp_CB_YlGnBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGnBu_09[12];

/** Color scheme known as icp_CB_YlGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGn_03[6];

/** Color scheme known as icp_CB_YlGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGn_04[7];

/** Color scheme known as icp_CB_YlGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGn_05[8];

/** Color scheme known as icp_CB_YlGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGn_06[9];

/** Color scheme known as icp_CB_YlGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGn_07[10];

/** Color scheme known as icp_CB_YlGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGn_08[11];

/** Color scheme known as icp_CB_YlGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlGn_09[12];

/** Color scheme known as icp_CB_YlOrBr_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrBr_03[6];

/** Color scheme known as icp_CB_YlOrBr_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrBr_04[7];

/** Color scheme known as icp_CB_YlOrBr_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrBr_05[8];

/** Color scheme known as icp_CB_YlOrBr_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrBr_06[9];

/** Color scheme known as icp_CB_YlOrBr_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrBr_07[10];

/** Color scheme known as icp_CB_YlOrBr_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrBr_08[11];

/** Color scheme known as icp_CB_YlOrBr_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrBr_09[12];

/** Color scheme known as icp_CB_YlOrRd_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrRd_03[6];

/** Color scheme known as icp_CB_YlOrRd_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrRd_04[7];

/** Color scheme known as icp_CB_YlOrRd_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrRd_05[8];

/** Color scheme known as icp_CB_YlOrRd_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrRd_06[9];

/** Color scheme known as icp_CB_YlOrRd_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrRd_07[10];

/** Color scheme known as icp_CB_YlOrRd_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrRd_08[11];

/** Color scheme known as icp_CB_YlOrRd_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
    extern const char *icp_CB_YlOrRd_09[12];

} // end namespace mjr

#define MJR_INCLUDE_colorData
#endif
