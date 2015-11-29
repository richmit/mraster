// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      colorAll.cpp
 @author    Mitch Richling <http://www.mitchr.me>
 @brief     Draw every possible color in 24-bit.@EOL
 @std       C++98
 @copyright 
  @parblock
  Copyright (c) 1988-2015, Mitchell Jay Richling <http://www.mitchr.me> All rights reserved.

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
  how to avoid all the work and do it with simple integers via setColorFromPackedIntRGBA, how to count via Grey code order, and how to reduce to 216 web safe
  color.

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

using namespace mjr;

unsigned long igray(unsigned long n);

int main(void) {
  ramCanvas4c8b theRamCanvas_iii = ramCanvas4c8b(4096, 4096);
  ramCanvas4c8b theRamCanvas_int = ramCanvas4c8b(4096, 4096);
  ramCanvas4c8b theRamCanvas_gry = ramCanvas4c8b(4096, 4096);
  ramCanvas4c8b theRamCanvas_rgb = ramCanvas4c8b(4096, 4096);
  ramCanvas4c8b theRamCanvas_web = ramCanvas4c8b(4096, 4096);

  int red=0, blue=0, green=0, count=0;
  for(int y=0;y<theRamCanvas_int.get_numYpix();y++) {
    for(int x=0;x<theRamCanvas_int.get_numXpix();x++) {
      red++;
      if(red>=256) {
        red=0;
        green++;
        if(green>=256) {
          green=0;
          blue++;
        }
      }
      color4c8b aColor;
      aColor.setColorFromPackedIntRGBA(count, 0, 1, 2, 3);
      theRamCanvas_iii.drawPoint(x, y, aColor);
      aColor.setColorFromPackedIntRGBA(count);    
      theRamCanvas_int.drawPoint(x, y, aColor);
      aColor.setColorFromPackedIntRGBA(igray(count));
      theRamCanvas_gry.drawPoint(x, y, aColor);
      aColor.setColorRGB(red, green, blue);
      theRamCanvas_rgb.drawPoint(x, y, aColor);
      aColor.tfrmWebSafe216();
      theRamCanvas_web.drawPoint(x, y, aColor);
      count++;
    }
  }
  theRamCanvas_int.writeTGAfile("colorAll_int.tga");
  theRamCanvas_iii.writeTGAfile("colorAll_iii.tga");
  theRamCanvas_gry.writeTGAfile("colorAll_gry.tga");
  theRamCanvas_rgb.writeTGAfile("colorAll_rgb.tga");
  theRamCanvas_web.writeTGAfile("colorAll_web.tga");
}

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
