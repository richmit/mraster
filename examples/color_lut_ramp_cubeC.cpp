// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      color_lut_ramp_cubeC.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw several examples of cube color ramps.@EOL
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
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define BMP i++; y1 = rampWidth + i * rampWidth; y2 = rampWidth + i * rampWidth + rampWidth - rampGap; yt = (y1+y2)/2;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::color3c8b              ct;
typedef mjr::color3c8b::csIntType   csIt;
typedef mjr::color3c8b::csNatType   csNt;
typedef mjr::color3c8b::csFltType   csFt;
typedef mjr::hershey::font          hft;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  int numRamps = 30, rampGap = 5, rampWidth = 50, textWide = 600, maxColors = 1600;
  csFt maxColorsF = static_cast<csFt>(maxColors);
  int i=0, y1=0, y2=0, yt=0, xt=maxColors+2*rampGap;;
  mjr::ramCanvas3c8b theRC(maxColors+2*rampGap+textWide, (2+numRamps)*rampWidth+rampGap);
  mjr::ramCanvas3c8b::colorType aColor(255, 255, 255);

   for(int x=0; x<maxColors+rampGap;x=x+256)
     theRC.drawLine(x, 0, x, theRC.getNumPixY()-1, aColor);
   i=-1;

  BMP;  for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCdiag01::c(x/maxColorsF));              theRC.drawString("  csCCdiag01",              hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; 
  BMP; 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCsumRGB::c(x/maxColorsF));              theRC.drawString("  csCCsumRGB",              hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCsumBGR::c(x/maxColorsF));              theRC.drawString("  csCCsumBGR",              hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCsumGRB::c(x/maxColorsF));              theRC.drawString("  csCCsumGRB",              hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCsumBRG::c(x/maxColorsF));              theRC.drawString("  csCCsumBRG",              hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCsumGBR::c(x/maxColorsF));              theRC.drawString("  csCCsumGBR",              hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCsumRBG::c(x/maxColorsF));              theRC.drawString("  csCCsumRBG",              hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCudRg::c(x/maxColorsF));                theRC.drawString("  csCCudRg",                hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCudRb::c(x/maxColorsF));                theRC.drawString("  csCCudRb",                hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCudGr::c(x/maxColorsF));                theRC.drawString("  csCCudGr",                hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCudGb::c(x/maxColorsF));                theRC.drawString("  csCCudGb",                hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCudBr::c(x/maxColorsF));                theRC.drawString("  csCCudBr",                hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCudBg::c(x/maxColorsF));                theRC.drawString("  csCCudBg",                hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20);                                                                                                        
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCColdeRainbow::c(x/maxColorsF));         theRC.drawString("  csCColdeRainbow",         hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20);                                                                                                        
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCColdeIceToWaterToHot::c(x/maxColorsF)); theRC.drawString("  csCColdeIceToWaterToHot", hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20);                                                                                                                                                         
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCColdeColdToHot::c(x/maxColorsF));       theRC.drawString("  csCColdeColdToHot",       hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCColdeFireRamp::c(x/maxColorsF));        theRC.drawString("  csCColdeFireRamp",        hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCconsTwo::c(x/maxColorsF));             theRC.drawString("  csCCconsTwo",             hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCconsOne::c(x/maxColorsF));             theRC.drawString("  csCCconsOne",             hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20);                                                                                                        
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCdiagCR::c(x/maxColorsF));              theRC.drawString("  csCCdiagCR",              hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCdiagMG::c(x/maxColorsF));              theRC.drawString("  csCCdiagMG",              hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; for(int x=0;x<maxColors;x++) theRC.drawLine(x, y1, x, y2, ct::csCCdiagYB::c(x/maxColorsF));              theRC.drawString("  csCCdiagYB",              hft::ROMAN_SL_SANSERIF, xt, yt, "red",  1, 20); 
  BMP; 
  BMP; 
  BMP; 
  BMP; 
  BMP; 
  BMP; 
    
  theRC.writeTIFFfile("color_lut_ramp_cubeC.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
