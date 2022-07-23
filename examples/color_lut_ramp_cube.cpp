// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      color_lut_ramp_cube.cpp
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  int numRamps = 45, rampGap = 5, rampWidth = 50, textWide = 600, maxColors = 1536;

  mjr::ramCanvas3c8b theRamCanvas(maxColors+2*rampGap+textWide, (2+numRamps)*rampWidth+rampGap);
  mjr::ramCanvas3c8b::colorType aColor(255, 255, 255);

   for(int x=0; x<maxColors+rampGap;x=x+256)
     theRamCanvas.drawLine(x, 0, x, theRamCanvas.get_numYpix()-1, aColor);

  for(int x=0;x<maxColors+rampGap;x++)
    for(int i=0; i<numRamps; i++) {
      int y1 = rampWidth + i * rampWidth;
      int y2 = rampWidth + i * rampWidth + rampWidth - rampGap;
      int yt = (y1+y2)/2;

      mjr::ramCanvas3c8b::csIdxType xi = static_cast<mjr::ramCanvas3c8b::csIdxType>(x);

      switch(i) {
        case  0: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpGrey(xi));                   theRamCanvas.drawString("  setRGBcmpGrey",              mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case  1: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpGrey3x(xi));                 theRamCanvas.drawString("  setRGBcmpGrey3x",            mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case  2: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpGrey4x(xi));                 theRamCanvas.drawString("  setRGBcmpGrey4x",            mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case  3: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpSumRampRGB(xi));             theRamCanvas.drawString("  setRGBcmpSumRampRGB",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case  4: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpSumRampBGR(xi));             theRamCanvas.drawString("  setRGBcmpSumRampBGR",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case  5: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpSumRampGRB(xi));             theRamCanvas.drawString("  setRGBcmpSumRampGRB",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case  6: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpSumRampBRG(xi));             theRamCanvas.drawString("  setRGBcmpSumRampBRG",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case  7: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpSumRampGBR(xi));             theRamCanvas.drawString("  setRGBcmpSumRampGBR",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case  8: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpSumRampRBG(xi));             theRamCanvas.drawString("  setRGBcmpSumRampRBG",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case  9: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpUpDownRampRg(xi));           theRamCanvas.drawString("  setRGBcmpUpDownRampRg",      mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 10: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpUpDownRampRb(xi));           theRamCanvas.drawString("  setRGBcmpUpDownRampRb",      mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 11: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpUpDownRampGr(xi));           theRamCanvas.drawString("  setRGBcmpUpDownRampGr",      mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 12: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpUpDownRampGb(xi));           theRamCanvas.drawString("  setRGBcmpUpDownRampGb",      mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 13: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpUpDownRampBr(xi));           theRamCanvas.drawString("  setRGBcmpUpDownRampBr",      mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 14: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpUpDownRampBg(xi));           theRamCanvas.drawString("  setRGBcmpUpDownRampBg",      mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case 15: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpRampGrey2R(xi));             theRamCanvas.drawString("  setRGBcmpRampGrey2R",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 16: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpRampGrey2G(xi));             theRamCanvas.drawString("  setRGBcmpRampGrey2G",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 17: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpRampGrey2B(xi));             theRamCanvas.drawString("  setRGBcmpRampGrey2B",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 18: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpRampGrey2C(xi));             theRamCanvas.drawString("  setRGBcmpRampGrey2C",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 19: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpRampGrey2M(xi));             theRamCanvas.drawString("  setRGBcmpRampGrey2M",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 20: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpRampGrey2Y(xi));             theRamCanvas.drawString("  setRGBcmpRampGrey2Y",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case 22: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpIceToWaterToHot(xi));        theRamCanvas.drawString("  setRGBcmpIceToWaterToHot",   mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case 21: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpClrCubeRainbow(xi));         theRamCanvas.drawString("  setRGBcmpClrCubeRainbow",    mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 23: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpColdToHot(xi));              theRamCanvas.drawString("  setRGBcmpColdToHot",         mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case 24: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpConstTwoRamp(xi));           theRamCanvas.drawString("  setRGBcmpConstTwoRamp",      mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 25: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpConstOneRamp(xi));           theRamCanvas.drawString("  setRGBcmpConstOneRamp",      mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case 26: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRGBcolorRamp(xi, "BWR"));          theRamCanvas.drawString("  cmpRGBcolorRamp",            mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 27: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRGBcolorRamp(xi, "CWM"));          theRamCanvas.drawString("  cmpRGBcolorRamp",            mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case 28: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpDiagRampCR(xi));             theRamCanvas.drawString("  setRGBcmpDiagRampCR",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 29: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpDiagRampMG(xi));             theRamCanvas.drawString("  setRGBcmpDiagRampMG",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 30: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpDiagRampYB(xi));             theRamCanvas.drawString("  setRGBcmpDiagRampYB",        mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 31: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpGreyRGB(xi));                theRamCanvas.drawString("  setRGBcmpGreyRGB",           mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case 32: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRGBcolorRamp(xi, "0RW"));          theRamCanvas.drawString("  cmpRGBcolorRamp",            mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 33: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRGBcolorRamp(xi, "0YW"));          theRamCanvas.drawString("  cmpRGBcolorRamp",            mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 34: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRGBcolorRamp(xi, "0GW"));          theRamCanvas.drawString("  cmpRGBcolorRamp",            mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 35: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRGBcolorRamp(xi, "0CW"));          theRamCanvas.drawString("  cmpRGBcolorRamp",            mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 36: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRGBcolorRamp(xi, "0BW"));          theRamCanvas.drawString("  cmpRGBcolorRamp",            mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 37: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRGBcolorRamp(xi, "0MW"));          theRamCanvas.drawString("  cmpRGBcolorRamp",            mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case 38: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpBinaryColorRampRG(xi, 128)); theRamCanvas.drawString("  setRGBcmpBinaryColorRampRG", mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 39: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpBinaryColorRampRB(xi, 128)); theRamCanvas.drawString("  setRGBcmpBinaryColorRampRB", mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 40: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpBinaryColorRampGR(xi, 128)); theRamCanvas.drawString("  setRGBcmpBinaryColorRampGR", mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 41: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpBinaryColorRampGB(xi, 128)); theRamCanvas.drawString("  setRGBcmpBinaryColorRampGB", mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 42: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpBinaryColorRampBR(xi, 128)); theRamCanvas.drawString("  setRGBcmpBinaryColorRampBR", mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 43: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpBinaryColorRampBG(xi, 128)); theRamCanvas.drawString("  setRGBcmpBinaryColorRampBG", mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
                                                                                                                                                        
        case 44: theRamCanvas.drawLine(x, y1, x, y2, aColor.setRGBcmpFireRamp(xi));               theRamCanvas.drawString("  setRGBcmpFireRamp",          mjr::hersheyFont::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;  // Same as setRGBcmpSumRampRGB
      }
    }
  theRamCanvas.writeTIFFfile("color_lut_ramp_cube.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
