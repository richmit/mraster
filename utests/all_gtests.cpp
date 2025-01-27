// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      all_gtests.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-08-24
 @brief     Combine all GTest programs into one binary.@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 2025, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.

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

// for f in *.cpp(:x/all_gtests/) { echo "#include \"$f\"" } > /dev/clip

#include "c_bool_isBlack.cpp"
#include "c_bool_isClose.cpp"
#include "c_bool_isEqual.cpp"
#include "c_comp_MinMax.cpp"
#include "c_comp_bestChan.cpp"
#include "c_comp_distDeltaE1976.cpp"
#include "c_comp_distX.cpp"
#include "c_comp_dotProd.cpp"
#include "c_comp_linearInterpolate.cpp"
#include "c_comp_luminance.cpp"
#include "c_comp_rgb2colorSpace.cpp"
#include "c_comp_wMean.cpp"
#include "c_constructor.cpp"
#include "c_int128_test.cpp"
#include "c_set_chan_argb.cpp"
#include "c_set_chan_byte.cpp"
#include "c_set_chan_const.cpp"
#include "c_set_chan_dbl.cpp"
#include "c_set_chan_gen.cpp"
#include "c_set_chan_hex.cpp"
#include "c_set_cs_csBin.cpp"
#include "c_set_cs_csCBSpectral.cpp"
#include "c_set_cs_csCColdeRainbow.cpp"
#include "c_set_cs_csCubeHelix.cpp"
#include "c_set_cs_csFPcircular12.cpp"
#include "c_set_cs_csHSLhX.cpp"
#include "c_set_cs_csPLY.cpp"
#include "c_set_rgb_ColorSpace.cpp"
#include "c_set_rgb_constant.cpp"
#include "c_set_rgb_tga.cpp"
#include "c_set_rgb_unitHSx.cpp"
#include "c_set_rgb_wavelengthCM.cpp"
#include "c_set_rgb_wavelengthLA.cpp"
#include "c_set_rgba_pack.cpp"
#include "c_tfrm_GryLevScl.cpp"
#include "c_tfrm_PowPow.cpp"
#include "c_tfrm_arith.cpp"
#include "c_tfrm_logic.cpp"
#include "c_tfrm_misc.cpp"
#include "c_tfrm_websafe.cpp"
#include "r_adjoin.cpp"
#include "r_draw_circles.cpp"
#include "r_draw_glyph.cpp"
#include "r_draw_lines.cpp"
#include "r_draw_point.cpp"
#include "r_draw_primatives.cpp"
#include "r_draw_rectangles.cpp"
#include "r_draw_rectangles_filled.cpp"
#include "r_draw_string.cpp"
#include "r_draw_triangles.cpp"
#include "r_draw_triangles_filled.cpp"
#include "r_p_scale.cpp"
#include "r_save_file.cpp"
#include "r_tfrm_geom.cpp"

/** @endcond */
