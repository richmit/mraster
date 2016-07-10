// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      bmark.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark program for pixel draw rates with ramCanvas.@EOL
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

  Simple benchmark.  Select what you want to test via the define statements.

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"
#include <cmath>

using namespace mjr;

#define DO_LINE      1
#define DO_CLIP_LINE 1
#define DO_POINT     1
#define DO_CLR       1
#define DO_FFTRI     1
#define DO_FGTRI     1
#define DO_RECT      1
#define DO_HLINE     1
#define DO_VLINE     1
#define DO_45LINE    1
#define DO_TRIVLN    0

#define DO_OUT       0

#define REPS  128

#define BSIZE 2024

int main(void) {
  ramCanvasRGB8b theRamCanvas(BSIZE, BSIZE);
  int xMax = theRamCanvas.get_numXpix()-1;
  int yMax = theRamCanvas.get_numYpix()-1;
  colorRGB8b aColor(255,   0, 0);
  colorRGB8b bColor(  0, 255, 0);

#if DO_POINT
  for(int i=0;i<REPS;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++)
        if((x*y)%2) 
          theRamCanvas.drawPoint(x, y, aColor);
        else
          theRamCanvas.drawPoint(x, y, bColor);
#endif

#if DO_CLR
  theRamCanvas.setDfltColor(aColor);
  for(int i=0;i<REPS*4;i++) {
    theRamCanvas.clrCanvasToBlack();
  }
#endif

#if DO_CLIP_LINE
  for(int i=0;i<REPS/16;i++)
    for(int j=0; j<BSIZE*2; j++) {
      float a = j*6.2831/(BSIZE*2);
      int  x1 = BSIZE * std::cos(a);
      int  y1 = BSIZE * std::sin(a);
      if(j%2)
        theRamCanvas.drawLine(-x1+xMax/2, -y1+yMax/2, x1+xMax/2, y1+yMax/2, aColor);
      else
        theRamCanvas.drawLine(-x1+xMax/2, -y1+yMax/2, x1+xMax/2, y1+yMax/2, bColor);
    }
#endif

#if DO_LINE
  for(int i=0;i<REPS/16;i++) {
    for(int y=0;y<=yMax;y+=1)
      if(y%2) 
        theRamCanvas.drawLine(0, y, xMax, yMax-y, aColor);
      else
        theRamCanvas.drawLine(0, y, xMax, yMax-y, bColor);
    for(int x=0;x<=xMax;x+=1)
      if(x%2) 
        theRamCanvas.drawLine(x, 0, xMax-x, yMax, aColor);
      else
        theRamCanvas.drawLine(x, 0, xMax-x, yMax, bColor);
  }
#endif

#if DO_FFTRI
  for(int i=0;i<REPS/16;i++)
    for(int x1=xMax,j=0;x1>=0;x1-=BSIZE/128,j++)
      if(j%2) 
        theRamCanvas.drawFillTriangle(x1, x1, x1+BSIZE/2, x1, x1, x1+yMax/2, aColor);
      else
        theRamCanvas.drawFillTriangle(x1, x1, x1+BSIZE/2, x1, x1, x1+yMax/2, bColor);
#endif

#if DO_FGTRI
  for(int i=0;i<REPS/128;i++)
    for(int x1=xMax,j=0;x1>=0;x1-=BSIZE/128,j++)
      if(j%2) 
        theRamCanvas.drawFillTriangle(x1, yMax/2, x1+BSIZE/2, yMax/2+x1, x1+BSIZE/2, yMax/2-x1, aColor);
      else
        theRamCanvas.drawFillTriangle(x1, yMax/2, x1+BSIZE/2, yMax/2+x1, x1+BSIZE/2, yMax/2-x1, bColor);
#endif

#if DO_RECT
  for(int i=0;i<REPS/32;i++)
    for(int xy=0, j=0;xy<yMax && xy<=xMax;xy+=BSIZE/128, j++)
      if(j%2) 
        theRamCanvas.drawFillRectangle(xy, xy, xMax-xy, yMax-xy, aColor);
      else
        theRamCanvas.drawFillRectangle(xy, xy, xMax-xy, yMax-xy, bColor);
#endif

#if DO_HLINE
  for(int i=0;i<REPS;i++)
    for(int y=0;y<=yMax;y++)
      if(y%2) 
        theRamCanvas.drawLine(0, y, xMax, y, aColor);
      else
        theRamCanvas.drawLine(0, y, xMax, y, bColor);
#endif

#if DO_VLINE
  for(int i=0;i<REPS;i++)
    for(int x=0;x<=xMax;x++)
      if(x%2) 
        theRamCanvas.drawLine(x, 0, x, yMax, aColor);
      else
        theRamCanvas.drawLine(x, 0, x, yMax, bColor); 
#endif

#if DO_45LINE
  for(int i=0;i<REPS;i++)
    for(int y=0;y<=yMax;y++)
      if(y%2) 
        theRamCanvas.drawLine(0, y, xMax, xMax+y, aColor);
      else
        theRamCanvas.drawLine(0, y, xMax, xMax+y, bColor);
#endif

#if DO_TRIVLN
  theRamCanvas.drawLine(     0,      0, xMax/2, yMax/2, aColor);
  theRamCanvas.drawLine(xMax/2, yMax/2,   xMax,   yMax, bColor);
  theRamCanvas.autoHistStrech();
#endif
  
#if DO_OUT
  theRamCanvas.writeTGAfile("bmark.tga");
  theRamCanvas.writeRAWfile("bmark.mrw");
#endif
  
}
