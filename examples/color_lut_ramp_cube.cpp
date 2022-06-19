// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      color_lut_ramp_cube.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw several examples of cube color ramps.@EOL
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

int main(void) {

  int numRamps = 45, rampGap = 5, rampWidth = 50;

  mjr::ramCanvas3c8b theRamCanvas(1536+rampGap, (2+numRamps)*rampWidth+rampGap);
  mjr::ramCanvas3c8b::colorType aColor(255, 255, 255);

   for(int x=0; x<theRamCanvas.get_numXpix();x=x+256)
     theRamCanvas.drawLine(x, 0, x, theRamCanvas.get_numYpix()-1, aColor);

  for(int x=0;x<theRamCanvas.get_numXpix();x++)
    for(int i=0; i<numRamps; i++) {
      int y1 = rampWidth + i * rampWidth;
      int y2 = rampWidth + i * rampWidth + rampWidth - rampGap;
      switch(i) {
        case  0: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpGrey(x));                   break;
        case  1: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpGrey3x(x));                 break;
        case  2: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpGrey4x(x));                 break;

        case  3: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpSumRampRGB(x));             break;
        case  4: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpSumRampBGR(x));             break;
        case  5: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpSumRampGRB(x));             break;
        case  6: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpSumRampBRG(x));             break;
        case  7: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpSumRampGBR(x));             break;
        case  8: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpSumRampRBG(x));             break;

        case  9: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpUpDownRampRg(x));           break;
        case 10: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpUpDownRampRb(x));           break;
        case 11: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpUpDownRampGr(x));           break;
        case 12: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpUpDownRampGb(x));           break;
        case 13: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpUpDownRampBr(x));           break;
        case 14: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpUpDownRampBg(x));           break;

        case 15: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRampGrey2R(x));             break;
        case 16: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRampGrey2G(x));             break;
        case 17: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRampGrey2B(x));             break;
        case 18: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRampGrey2C(x));             break;
        case 19: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRampGrey2M(x));             break;
        case 20: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpRampGrey2Y(x));             break;

        case 22: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpIceToWaterToHot(x));        break;

        case 21: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpClrCubeRainbow(x));         break;
        case 23: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpColdToHot(x));              break;

        case 24: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpConstTwoRamp(x));           break;
        case 25: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpConstOneRamp(x));           break;

        case 26: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpColorRamp(x, "BWR"));       break;
        case 27: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpColorRamp(x, "CWM"));       break;

        case 28: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpDiagRampCR(x));             break;
        case 29: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpDiagRampMG(x));             break;
        case 30: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpDiagRampYB(x));             break;
        case 31: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpGreyRGB(x));                break;

        case 32: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpColorRamp(x, "0RW"));       break;
        case 33: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpColorRamp(x, "0YW"));       break;
        case 34: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpColorRamp(x, "0GW"));       break;
        case 35: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpColorRamp(x, "0CW"));       break;
        case 36: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpColorRamp(x, "0BW"));       break;
        case 37: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpColorRamp(x, "0MW"));       break;

        case 38: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpBinaryColorRampRG(x, 128)); break;
        case 39: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpBinaryColorRampRB(x, 128)); break;
        case 40: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpBinaryColorRampGR(x, 128)); break;
        case 41: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpBinaryColorRampGB(x, 128)); break;
        case 42: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpBinaryColorRampBR(x, 128)); break;
        case 43: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpBinaryColorRampBG(x, 128)); break;

        case 44: theRamCanvas.drawLine(x, y1, x, y2, aColor.cmpFireRamp(x));               break;  // Same as cmpSumRampRGB

      }
    }
  theRamCanvas.writeTIFFfile("color_lut_ramp_cube.tiff");
}
