// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      tippets.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw the John Tippetts variant of the Mandelbrot set.@EOL
 @std       C++14
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

#define __USE_MINGW_ANSI_STUDIO 0

#include "ramCanvas.hpp"

#include <complex>                                                       /* STL algorithm           C++11    */

double ranges[6][4] = { {  -2.700,  2.100, -2.100,  2.100 },
                        {  -2.100, -1.700, -0.300,  0.300 },
                        {  -1.540, -1.330, -0.175,  0.175 },
                        {   0.250,  0.700, -1.000,  1.000 },
                        {   0.250,  0.600,  0.700,  1.000 },
                        {  -0.720, -0.695,  0.385,  0.410 } };

int main(void) {
  const int NUMITR = 2000;
  const int CSIZE  = 3840;

  int count;
  float a, b, zx, zy;
  mjr::ramCanvas3c8b theRamCanvas(CSIZE, CSIZE);
  for(int i=0; i<6; i++) {    
    theRamCanvas.newRealCoords(ranges[i][0], ranges[i][1], ranges[i][2], ranges[i][3]);  
    theRamCanvas.clrCanvasToBlack();
    for(int y=0;y<theRamCanvas.get_numYpix();y++) {
      if((y%(CSIZE/10))==0)
        std::cout << "    CASE: " << i << " LINE: " << y << "/" << CSIZE << std::endl;
      for(int x=0;x<theRamCanvas.get_numXpix();x++) {
        for(a=theRamCanvas.int2realX(x),b=theRamCanvas.int2realY(y),zx=zy=0.0,count=0;
            (zx*zx+zy*zy<100000)&&(count<=NUMITR);
            count++,zx=zx*zx-zy*zy+a,zy=2*zx*zy+b) ;
        if(count < NUMITR)
          theRamCanvas.drawPoint(x, y, mjr::color3c8b().cmpFireRamp(mjr::intWrap(count*20, 767)));
      }
    }
    theRamCanvas.writeTIFFfile("tippets" + std::to_string(i) + ".tiff");
  }
}
