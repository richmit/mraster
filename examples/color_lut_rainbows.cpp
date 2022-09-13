// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      color_lut_rainbows.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     rainbow related colors@EOL
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
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  int numRamps = 7, rampGap = 10, rampWidth = 150, maxColors = 1536, textWide = 600;

  mjr::ramCanvas3c8b theRamCanvas(maxColors+2*rampGap+textWide, (2+numRamps)*rampWidth+rampGap);
  mjr::ramCanvas3c8b::colorType aColor(255, 255, 255);

  for(int x=0; x<(maxColors+rampGap);x=x+256)
    theRamCanvas.drawLine(x, 0, x, theRamCanvas.getNumPixY()-1, aColor);

  for(int x=0;x<(maxColors);x++)
    for(int i=0; i<numRamps; i++) {
      int y1 = rampWidth + i * rampWidth;
      int y2 = rampWidth + i * rampWidth + rampWidth - rampGap;
      int yt = (y1+y2)/2;

      mjr::ramCanvas3c8b::csIntType xi = static_cast<mjr::ramCanvas3c8b::csIntType>(x);
      mjr::ramCanvas3c8b::csIntType b  = static_cast<mjr::ramCanvas3c8b::csIntType>(maxColors);
      switch(i) {
        case 0: theRamCanvas.drawLine(x, y1, x, y2, mjr::color3c8b::csCColdeRainbow::c(xi));                                                   theRamCanvas.drawString("  setRGBcmpClrCubeRainbow    ", mjr::hershey::font::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 1: theRamCanvas.drawLine(x, y1, x, y2, mjr::color3c8b::csRainbowLA::c(xi, b));                                                    theRamCanvas.drawString("  setRGBcmpRainbowLA         ", mjr::hershey::font::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 2: theRamCanvas.drawLine(x, y1, x, y2, mjr::color3c8b::csRainbowCM::c(xi, b, mjr::ramCanvas3c8b::cmfInterpolationEnum::FLOOR));   theRamCanvas.drawString("  setRGBcmpRainbowCM  FLOOR  ", mjr::hershey::font::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 3: theRamCanvas.drawLine(x, y1, x, y2, mjr::color3c8b::csRainbowCM::c(xi, b, mjr::ramCanvas3c8b::cmfInterpolationEnum::CEILING)); theRamCanvas.drawString("  setRGBcmpRainbowCM  CEILING", mjr::hershey::font::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 4: theRamCanvas.drawLine(x, y1, x, y2, mjr::color3c8b::csRainbowCM::c(xi, b, mjr::ramCanvas3c8b::cmfInterpolationEnum::NEAREST)); theRamCanvas.drawString("  setRGBcmpRainbowCM  NEAREST", mjr::hershey::font::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 5: theRamCanvas.drawLine(x, y1, x, y2, mjr::color3c8b::csRainbowCM::c(xi, b, mjr::ramCanvas3c8b::cmfInterpolationEnum::LINEAR));  theRamCanvas.drawString("  setRGBcmpRainbowCM  LINEAR ", mjr::hershey::font::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
        case 6: theRamCanvas.drawLine(x, y1, x, y2, mjr::color3c8b::csRainbowCM::c(xi, b, mjr::ramCanvas3c8b::cmfInterpolationEnum::BUMP));    theRamCanvas.drawString("  setRGBcmpRainbowCM  BUMP   ", mjr::hershey::font::ROMAN_SL_SANSERIF, maxColors+2*rampGap, yt, "red",  1, 20); break;
      }
    }
  theRamCanvas.writeTIFFfile("color_lut_rainbows.tiff");
  theRamCanvas.writeTGAfile("color_lut_rainbows.tga");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
