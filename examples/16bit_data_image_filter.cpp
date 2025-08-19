// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      16bit_data_image_filter.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Demonstrate "data images" and mjr::ramCanvasPixelFilter.@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 1988-2015, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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
 @filedetails

  This example reads a 16bit greyscale image, and colorizes it several diffrent ways.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathIVL.hpp"

// We use the hpf_t filter type to transform our data into pseudo-color images without modifying the original data.
typedef mjr::color3c8b oc_t;
typedef mjr::ramCanvas1c16b drc_t;
typedef mjr::ramCanvasPixelFilter::FuncHomoTransform<drc_t, oc_t> hpf_t;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  drc_t datRC;
  int rRet;

  if (argc != 2) {
    fprintf(stderr, "ERROR: A single filename must be provided as a command line argument!\n");
    exit(1);
  }

  if((rRet=datRC.readRAWfile(argv[1]))) {
    fprintf(stderr, "ERROR(%d) reading file %s\n", rRet, argv[1]);
    exit(1);
  }

  //  For our first attempt, we simply use the values in datRC as the three components of a 24-bit RGB image.
  datRC.writeTIFFfile("16bit_data_image_filter_01.tiff", hpf_t(datRC,[](auto inColor) { return oc_t(static_cast<oc_t::channelType>(inColor.getC0())); }));

  // Next we use the integers stored in datRC to index a color scheme (Note that csCColdeFireRamp has more than 256 colors).
  datRC.writeTIFFfile("16bit_data_image_filter_02.tiff", hpf_t(datRC,[](auto inColor) { return oc_t::csCColdeFireRamp::c(inColor.getC0()*oc_t::csCColdeFireRamp::numC/255); }));

  // Like the previous line, but with a 30x multiplayer so the colors wrap around.  This is a pretty typical way to draw an escape function.
  datRC.writeTIFFfile("16bit_data_image_filter_03.tiff", hpf_t(datRC,[](auto inColor) { return oc_t::csCColdeFireRamp::c(30*inColor.getC0()); }));

  // This will perfectly apply the color scheme so that the max color scheme index is used for pixels with the max possible channel value.  
  datRC.writeTIFFfile("16bit_data_image_filter_04.tiff", mjr::ramCanvasPixelFilter::ColorSchemeOnChan<drc_t, oc_t, oc_t::csCCfractal0RYBCW>(datRC));

  // We apply the same color scheme, but use the color value as the index into the color scheme
  datRC.writeTIFFfile("16bit_data_image_filter_05.tiff", hpf_t(datRC,[](auto inColor) { return oc_t::csCCfractal0RYBCW::c(inColor.getC0()); }));

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
