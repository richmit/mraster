// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
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

#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

#define DO_LINE       0
#define DO_CLIP_LINE  0
#define DO_POINT      0
#define DO_CLR        0
#define DO_FFTRI      0
#define DO_FGTRI      0
#define DO_RECT       0
#define DO_HLINE_NC   0
#define DO_HLINE      0
#define DO_VLINE_NC   0
#define DO_VLINE      0
#define DO_45LINE     0
#define DO_TRIVLN     0
#define DO_INTRP_AVG9 1

#define DO_OUT_TIF   0
#define DO_OUT_RAW   0

#define REPS  128

#define BSIZE 2024*2

int main(void) {
  auto startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  mjr::ramCanvasRGB8b theRamCanvas(BSIZE, BSIZE);
  int xMax = theRamCanvas.get_numXpix()-1;
  int yMax = theRamCanvas.get_numYpix()-1;
  mjr::colorRGB8b aColor(255,   0, 0);
  mjr::colorRGB8b bColor(  0, 255, 0);

#if DO_POINT
  std::cout << "Starting DO_POINT" << std::endl;
  for(int i=0;i<REPS;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++)
        if((x*y)%2)
          theRamCanvas.drawPoint(x, y, aColor);
        else
          theRamCanvas.drawPoint(x, y, bColor);
#endif

#if DO_CLR
  std::cout << "Starting DO_CLR" << std::endl;
  theRamCanvas.setDfltColor(aColor);
  for(int i=0;i<REPS*4;i++) {
    theRamCanvas.clrCanvasToBlack();
  }
#endif

#if DO_CLIP_LINE
  std::cout << "Starting DO_CLIP_LINE" << std::endl;
  for(int i=0;i<REPS/16;i++)
    for(int j=0; j<BSIZE*2; j++) {
      double a = static_cast<double>(j) * 6.2831 / (BSIZE * 2.0);
      int  x1 = static_cast<int>(BSIZE * std::cos(a));
      int  y1 = static_cast<int>(BSIZE * std::sin(a));
      if(j%2)
        theRamCanvas.drawLine(-x1+xMax/2, -y1+yMax/2, x1+xMax/2, y1+yMax/2, aColor);
      else
        theRamCanvas.drawLine(-x1+xMax/2, -y1+yMax/2, x1+xMax/2, y1+yMax/2, bColor);
    }
#endif

//  MJR TODO NOTE <2022-06-18T14:01:26-0500> main: Add a test case for lines that are completely out of the drawing area.

#if DO_LINE
  std::cout << "Starting DO_LINE" << std::endl;
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
  std::cout << "Starting DO_FFTRI" << std::endl;
  for(int i=0;i<REPS/16;i++)
    for(int x1=xMax,j=0;x1>=0;x1-=BSIZE/128,j++)
      if(j%2)
        theRamCanvas.drawFillTriangle(x1, x1, x1+BSIZE/2, x1, x1, x1+yMax/2, aColor);
      else
        theRamCanvas.drawFillTriangle(x1, x1, x1+BSIZE/2, x1, x1, x1+yMax/2, bColor);
#endif

#if DO_FGTRI
  std::cout << "Starting DO_FGTRI" << std::endl;
  for(int i=0;i<REPS/128;i++)
    for(int x1=xMax,j=0;x1>=0;x1-=BSIZE/128,j++)
      if(j%2)
        theRamCanvas.drawFillTriangle(x1, yMax/2, x1+BSIZE/2, yMax/2+x1, x1+BSIZE/2, yMax/2-x1, aColor);
      else
        theRamCanvas.drawFillTriangle(x1, yMax/2, x1+BSIZE/2, yMax/2+x1, x1+BSIZE/2, yMax/2-x1, bColor);
#endif

#if DO_RECT
  std::cout << "Starting DO_RECT" << std::endl;
  for(int i=0;i<REPS/32;i++)
    for(int xy=0, j=0;xy<yMax && xy<=xMax;xy+=BSIZE/128, j++)
      if(j%2)
        theRamCanvas.drawFillRectangle(xy, xy, xMax-xy, yMax-xy, aColor);
      else
        theRamCanvas.drawFillRectangle(xy, xy, xMax-xy, yMax-xy, bColor);
#endif

#if DO_HLINE_NC
  std::cout << "Starting DO_HLINE_NC" << std::endl;
  for(int i=0;i<REPS*4;i++)
    for(int y=0;y<=yMax;y+=1)
      if(y%2)
        theRamCanvas.drawHorzLineNC(0, xMax, y, aColor);
      else
        theRamCanvas.drawHorzLineNC(0, xMax, y, bColor);
#endif

#if DO_HLINE
  std::cout << "Starting DO_HLINE" << std::endl;
  for(int i=0;i<REPS;i++)
    for(int y=0;y<=yMax;y++)
      if(y%2)
        theRamCanvas.drawLine(0, y, xMax, y, aColor);
      else
        theRamCanvas.drawLine(0, y, xMax, y, bColor);
#endif

#if DO_VLINE
  std::cout << "Starting DO_VLINE" << std::endl;
  for(int i=0;i<REPS/2;i++)
    for(int x=0;x<=xMax;x++)
      if(x%2)
        theRamCanvas.drawLine(x, 0, x, yMax, aColor);
      else
        theRamCanvas.drawLine(x, 0, x, yMax, bColor);
#endif

#if DO_VLINE_NC
  std::cout << "Starting DO_VLINE_NC" << std::endl;
  for(int i=0;i<REPS/2;i++)
    for(int x=0;x<=xMax;x++)
      if(x%2)
        theRamCanvas.drawVertLineNC(0, yMax, x, aColor);
      else
        theRamCanvas.drawVertLineNC(0, yMax, x, bColor);
#endif

#if DO_45LINE
  std::cout << "Starting DO_45LINE" << std::endl;
  for(int i=0;i<REPS;i++)
    for(int y=0;y<=yMax;y++)
      if(y%2)
        theRamCanvas.drawLine(0, y, xMax, xMax+y, aColor);
      else
        theRamCanvas.drawLine(0, y, xMax, xMax+y, bColor);
#endif

#if DO_TRIVLN
  std::cout << "Starting DO_TRIVLN" << std::endl;
  theRamCanvas.drawLine(     0,      0, xMax/2, yMax/2, aColor);
  theRamCanvas.drawLine(xMax/2, yMax/2,   xMax,   yMax, bColor);
  theRamCanvas.autoHistStrech();
#endif

#if DO_INTRP_AVG9
  std::cout << "Starting DO_INTRP_AVG9" << std::endl;
  for(int i=0;i<REPS/16;i++)
    for(int y=0;y<=yMax;y+=1)
      for(int x=0;x<=xMax;x+=1)
        theRamCanvas.drawPoint(x, y, theRamCanvas.getPxColorInterpAvg9(x, y));
#endif

#if DO_OUT_TIF
  std::cout << "Starting DO_OUT_TIF" << std::endl;
  theRamCanvas.writeTIFFfile("bmark.tiff");
#endif

#if DO_OUT_RAW
  std::cout << "Starting DO_OUT_RAW" << std::endl;
  theRamCanvas.writeRAWfile("bmark.mrw");
#endif

  std::cout << "Print Complete" << std::endl;
  std::cout << "Center Red:   " << static_cast<int>(theRamCanvas.getPxColor(BSIZE/2, BSIZE/2).getRed()) << std::endl;
  std::cout << "Center Green: " << static_cast<int>(theRamCanvas.getPxColor(BSIZE/2, BSIZE/2).getGreen()) << std::endl;
  std::cout << "Runtime " << static_cast<double>(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) - startTime)/(60.0) << " min" << std::endl;
}
