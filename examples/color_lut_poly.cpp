// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      color_lut_poly.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a few cubehelix color schemes.@EOL
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
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define BMP i++; y1 = rampWidth + i * rampWidth; y2 = rampWidth + i * rampWidth + rampWidth - rampGap; yt = (y1+y2)/2;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::color3c8b              ct;
typedef mjr::hershey::font          hft;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  int numRamps = 10, rampGap = 5, rampWidth = 50, textWide = 400, maxColors = 1024;
  int i=0, y1=0, y2=0, yt=0, xt=maxColors+2*rampGap;;
  mjr::ramCanvas3c8b theRC(maxColors+2*rampGap+textWide, (2+numRamps)*rampWidth+rampGap);
  mjr::ramCanvas3c8b::colorType aColor(255, 255, 255);

  i=-1;
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csPLYgrey::c(mjr::math::linm::gen_map(x, 0, 1024, 0.0, 1.0)));    theRC.drawString("  csPLYgrey    ", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csPLYquad::c(mjr::math::linm::gen_map(x, 0, 1024, 0.0, 1.0)));    theRC.drawString("  csPLYquad    ", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csPLYturbo::c(mjr::math::linm::gen_map(x, 0, 1024, 0.0, 1.0)));   theRC.drawString("  csPLYturbo   ", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csPLYparula::c(mjr::math::linm::gen_map(x, 0, 1024, 0.0, 1.0)));  theRC.drawString("  csPLYparula  ", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csPLYmagma::c(mjr::math::linm::gen_map(x, 0, 1024, 0.0, 1.0)));   theRC.drawString("  csPLYmagma   ", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csPLYinferno::c(mjr::math::linm::gen_map(x, 0, 1024, 0.0, 1.0))); theRC.drawString("  csPLYinferno ", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csPLYplasma::c(mjr::math::linm::gen_map(x, 0, 1024, 0.0, 1.0)));  theRC.drawString("  csPLYplasma  ", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csPLYviridis::c(mjr::math::linm::gen_map(x, 0, 1024, 0.0, 1.0))); theRC.drawString("  csPLYviridis ", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csPLYcividis::c(mjr::math::linm::gen_map(x, 0, 1024, 0.0, 1.0))); theRC.drawString("  csPLYcividis ", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csPLYhsvRB::c(mjr::math::linm::gen_map(x, 0, 1024, 0.0, 1.0)));   theRC.drawString("  csPLYhsvRB   ", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 

  theRC.writeTIFFfile("color_lut_poly.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
