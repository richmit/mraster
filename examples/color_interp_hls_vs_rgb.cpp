// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      color_interp_hls_vs_rgb.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Illistrate the diffrence in interpolion in HLS vs RGB spaec.@EOL
 @std       C++98
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

  In some cases, interpolating in HLS spaces can lead to an entirely different result from interpolating in RGB space.  This program illustrates on such
  example.  Note that in many of the most important cases, interpolating leads to the same results in both color spaces.

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

int main(void) {
  mjr::ramCanvas3c8b theRamCanvas(512, 512, -2.0, 2, -2, 2);
  mjr::ramCanvas3c8b::colorType aColor;

  for(int x=0; x<512; x++) {
    theRamCanvas.drawLine(x,   0, x, 250, aColor.interplColors(   x/512.0, mjr::ramCanvas3c8b::colorType("R"), mjr::ramCanvas3c8b::colorType("C")));
    theRamCanvas.drawLine(x, 260, x, 512, aColor.interplColorsHLS(x/512.0, mjr::ramCanvas3c8b::colorType("R"), mjr::ramCanvas3c8b::colorType("C")));
  }
  theRamCanvas.writeTIFFfile("color_interp_hls_vs_rgb.tiff");
}
