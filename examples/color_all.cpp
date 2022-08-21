// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      color_all.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw every possible color in 24-bit.@EOL
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

  This is a very simple program that plots a point of EVERY possible 24-bit color.  This program illustrates how to count by bytes, set colors in byte order,
  how to avoid all the work and do it with simple integers via setRGBAfromLogPackIntABGR, how to count via Grey code order, and how to reduce to 216 web safe
  color.

********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long igray(unsigned long n);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b theRamCanvas_iii(4096, 4096);
  mjr::ramCanvas3c8b theRamCanvas_int(4096, 4096);
  mjr::ramCanvas3c8b theRamCanvas_gry(4096, 4096);
  mjr::ramCanvas3c8b theRamCanvas_rgb(4096, 4096);
  mjr::ramCanvas3c8b theRamCanvas_web(4096, 4096);

  mjr::ramCanvasRGB8b::colorChanType red=0, blue=0, green=0;
  uint32_t count=0;
  mjr::ramCanvas3c8b::colorType aColor;
  for(int y=0;y<theRamCanvas_int.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas_int.getNumPixX();x++) {
      aColor.setRGBfromLogPackIntGen(count, 0, 1, 2);
      theRamCanvas_iii.drawPoint(x, y, aColor);
      aColor.setRGBfromLogPackIntABGR(count);
      theRamCanvas_int.drawPoint(x, y, aColor);
      aColor.setRGBfromLogPackIntABGR(igray(count));
      theRamCanvas_gry.drawPoint(x, y, aColor);
      aColor.setChansRGB(red, green, blue);
      theRamCanvas_rgb.drawPoint(x, y, aColor);
      aColor.tfrmWebSafeRGB();
      theRamCanvas_web.drawPoint(x, y, aColor);
      count++;
      if(red < 255) {
        red++;
      } else {
        red = 0;
        if (green < 255) {
          green++;
        } else {
          green = 0;
          blue++;
        }
      }

    }
  }
  theRamCanvas_int.writeTIFFfile("color_all_int.tiff");
  theRamCanvas_iii.writeTIFFfile("color_all_iii.tiff");
  theRamCanvas_gry.writeTIFFfile("color_all_gry.tiff");
  theRamCanvas_rgb.writeTIFFfile("color_all_rgb.tiff");
  theRamCanvas_web.writeTIFFfile("color_all_web.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
unsigned long igray(unsigned long n) {
  unsigned long ans = n;
  unsigned long idiv;
  int ish = 1;
  ans=n;
  for(;;) {
    ans ^= (idiv=ans>>ish);
    if(idiv <=1 || ish == 16)
      return ans;
    ish <<=1;
  }
}
/** @endcond */
