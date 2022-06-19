// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      color_web_triangle.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Plot the full range of RGB colors along with various reduced color spaces.@EOL
 @std       C++11
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

  This is a very simple program that plots a point of EVERY possible color for a 24-bit display.  It also produces versions for various types of color blind
  vision and the 216 color web safe version.

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

int main(void) {
  int x, y;
  int redX=512, redY=512, blueX=1024, blueY=512, greenX=768, greenY=956;
  double sLength = 512;
  mjr::ramCanvas3c8b::colorType color;
  mjr::ramCanvas3c8b theRamCanvas_tru(1536, 1536);
  mjr::ramCanvas3c8b theRamCanvas_web(1536, 1536);
  mjr::ramCanvas3c8b theRamCanvas_Pro(1536, 1536);
  mjr::ramCanvas3c8b theRamCanvas_Deu(1536, 1536);
  mjr::ramCanvas3c8b theRamCanvas_Tri(1536, 1536);

  for(y=0;y<theRamCanvas_web.get_numYpix();y++) {
    for(x=0;x<theRamCanvas_web.get_numXpix();x++) {
      if( (sqrt(double((x-redX)  *(x-redX)  +(y-redY)  *(y-redY)))    < sLength) ||
          (sqrt(double((x-blueX) *(x-blueX) +(y-blueY) *(y-blueY)))   < sLength) ||
          (sqrt(double((x-greenX)*(x-greenX)+(y-greenY)*(y-greenY)))) < sLength) {
        color.setColorRGB((mjr::colChan8)(255-sqrt(double((x-redX)  *(x-redX)   +(y-redY) *(y-redY))  /sLength*255)),
                          (mjr::colChan8)(255-sqrt(double((x-blueX) *(x-blueX)  +(y-blueY)*(y-blueY)) /sLength*255)),
                          (mjr::colChan8)(255-sqrt(double((x-greenX)*(x-greenX)+(y-greenY)*(y-greenY))/sLength*255)));
        mjr::ramCanvas3c8b::colorType tmpColor;
        tmpColor = color;
        theRamCanvas_tru.drawPoint(x, y, tmpColor);
        tmpColor = color;
        theRamCanvas_web.drawPoint(x, y, tmpColor.tfrmWebSafe216());
        tmpColor = color;
        theRamCanvas_Pro.drawPoint(x, y, tmpColor.tfrmWebSafePro216());
        tmpColor = color;
        theRamCanvas_Deu.drawPoint(x, y, tmpColor.tfrmWebSafeDeu216());
        tmpColor = color;
        theRamCanvas_Tri.drawPoint(x, y, tmpColor.tfrmWebSafeTri216());
      }
    }
  }
  theRamCanvas_tru.writeTIFFfile("color_web_triangle_tru.tiff");
  theRamCanvas_web.writeTIFFfile("color_web_triangle_web.tiff");
  theRamCanvas_Pro.writeTIFFfile("color_web_triangle_Pro.tiff");
  theRamCanvas_Deu.writeTIFFfile("color_web_triangle_Deu.tiff");
  theRamCanvas_Tri.writeTIFFfile("color_web_triangle_Tri.tiff");
}
