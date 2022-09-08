// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
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

********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#define DO_POINT      0
#define DO_POINT_NC   0
#define DO_RAMP       0
#define DO_RAMP_INT   0
#define DO_RAMP_CON   0
#define DO_INVERT     0
#define DO_COL_SET    0
#define DO_COL_SETC   0
#define DO_UNPACK     0
#define DO_MINI       0
#define DO_CLR_BLK    0
#define DO_CLR        0
#define DO_FFBTRI     0
#define DO_FFTRI      0
#define DO_FGBTRI     0
#define DO_FGTRI      0
#define DO_CIRCLE     1
#define DO_RECT       0
#define DO_LINE       0
#define DO_CLIP_LINE  0
#define DO_HLINE_NC   0
#define DO_HLINE      0
#define DO_VLINE_NC   0
#define DO_VLINE      0
#define DO_45LINE     0
#define DO_TRIVLN     0
#define DO_INTRP_AVG9 0
#define DO_INTRP_BILN 0
#define DO_CONV       0
#define DO_CS_CONV    0

#define DO_OUT_TIF   1
#define DO_OUT_RAW   0

#define REPS  1

#define BSIZE 4048 
//#define BSIZE 10

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// typedef mjr::ramCanvas1c8b  canvasType;
// typedef mjr::ramCanvas1c16b canvasType;
// typedef mjr::ramCanvas1c32b canvasType;
// typedef mjr::ramCanvas1c64b canvasType;
// typedef mjr::ramCanvas1c128b canvasType;

 typedef mjr::ramCanvas3c8b  canvasType;
// typedef mjr::ramCanvas3c16b canvasType;
// typedef mjr::ramCanvas3c32b canvasType;

// typedef mjr::ramCanvas3c32F canvasType;
// typedef mjr::ramCanvas3c64F canvasType;

// typedef mjr::ramCanvas8c8b  canvasType;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  canvasType theRamCanvas(BSIZE, BSIZE);
  int xMax = theRamCanvas.getNumPixX()-1;
  int yMax = theRamCanvas.getNumPixY()-1;
  canvasType::colorType aColor("red");
  canvasType::colorType bColor("cyan");
  canvasType::colorType cColor("black");
  canvasType::colorType dColor("green");
  std::chrono::time_point<std::chrono::system_clock> bmStartTime, bmEndTime;
  std::chrono::duration<double> bmTime;

  std::cout << "bpp: " << canvasType::colorType::bitsPerPixel << std::endl;
  std::cout << "chn: " << canvasType::colorType::channelCount << std::endl;
  std::cout << "int: " << canvasType::colorType::chanIsInt    << std::endl;

#if DO_POINT
  std::cout << "Starting DO_POINT" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*256;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++)
        if((x*y)%2)
          theRamCanvas.drawPoint(x, y, aColor);
        else
          theRamCanvas.drawPoint(x, y, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_POINT Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_RAMP_INT
  std::cout << "Starting DO_RAMP_INT" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*32;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++)
        theRamCanvas.drawPoint(x, y, cColor.cmpRGBcornerDGradiant(x+y, "0BCGYWMR0"));
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_RAMP_INT Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_RAMP_CON
  std::cout << "Starting DO_RAMP_CON" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*32;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++)  
        theRamCanvas.drawPoint(x, y, cColor.cmpRGBcornerCGradiant(1.0*(x+y)/(yMax+yMax), "0BCGYWMR0"));
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_RAMP_CON Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_RAMP
  std::cout << "Starting DO_RAMP" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*16;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++)
          theRamCanvas.drawPoint(x, y, cColor.linearInterpolate(x/(double)xMax, aColor, bColor));
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_RAMP Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_POINT_NC
  std::cout << "Starting DO_POINT_NC" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*512;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++) 
        if((x*y)%2) 
          theRamCanvas.drawPointNC(x, y, aColor);
        else 
          theRamCanvas.drawPointNC(x, y, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_POINT_NC Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_INVERT
  std::cout << "Starting DO_INVERT" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*128+1;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++) 
          theRamCanvas.getPxColorRefNC(x, y).tfrmInvert();
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_INVERT Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_COL_SETC
  std::cout << "Starting DO_COL_SETC" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*32;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++) {
        if((i+x*y)%2) 
          cColor.setChans_byte(static_cast<uint8_t>((i+x)%256));
        else
          cColor.setChans_byte(static_cast<uint8_t>((i+y)%256));
        theRamCanvas.drawPointNC(x, y, cColor);
      }
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_COL_SETC Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_COL_SET
  std::cout << "Starting DO_COL_SET" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*32;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++) {
        cColor.setChansRGB_byte(static_cast<uint8_t>(x%256), 
                                static_cast<uint8_t>(y%256),
                                static_cast<uint8_t>((i*8)%256));
        theRamCanvas.drawPointNC(x, y, cColor);
      }
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_COL_SET Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_UNPACK
  std::cout << "Starting DO_UNPACK" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*64;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++)
        theRamCanvas.getPxColorRefNC(x, y).setRGBfromLogPackIntARGB(0xFFFFFF-i*x*x*y);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_UNPACK Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_MINI
  std::cout << "Starting DO_MINI" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*128;i++)
    for(int y=0;y<=xMax;y++)
      for(int x=0;x<=yMax;x++)
        if((x*y)%2) 
          theRamCanvas.getPxColorRefNC(x, y).tfrmMinI(bColor);
        else
          theRamCanvas.getPxColorRefNC(x, y).tfrmMinI(bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_MINI Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_CLR_BLK
  std::cout << "Starting DO_CLR_BLK" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  theRamCanvas.setDfltColor(aColor);
  for(int i=0;i<REPS*256;i++) {
    if(i%2) 
      theRamCanvas.clrCanvasToWhite();
    else
      theRamCanvas.clrCanvasToBlack();
  }
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_CLR_BLK Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_CLR
  std::cout << "Starting DO_CLR" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*256;i++) {
    if(i%2) 
      theRamCanvas.clrCanvas(aColor);
    else
      theRamCanvas.clrCanvas(bColor);
  }
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_CLR Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_CLIP_LINE
  std::cout << "Starting DO_CLIP_LINE" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*8;i++)
    for(int j=0; j<BSIZE*4; j++) {
      double a = static_cast<double>(j) * 6.2831 / (BSIZE * 2.0);
      int  x1 = static_cast<int>(BSIZE * std::cos(a));
      int  y1 = static_cast<int>(BSIZE * std::sin(a));
      if(j%2)
        theRamCanvas.drawLine(-x1+xMax/2, -y1+yMax/2, x1+xMax/2, y1+yMax/2, aColor);
      else
        theRamCanvas.drawLine(-x1+xMax/2, -y1+yMax/2, x1+xMax/2, y1+yMax/2, bColor);
    }
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_CLIP_LINE Runtime " << bmTime.count() << " sec" << std::endl;
#endif

//  MJR TODO NOTE <2022-06-18> main: Add a test case for lines that are completely out of the drawing area.

#if DO_LINE
  std::cout << "Starting DO_LINE" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*16;i++) {
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
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_LINE Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_FFBTRI
  std::cout << "Starting DO_FFBTRI" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS;i++)
    for(int y=0;y<=yMax;y+=50)
      if(y%2)
        theRamCanvas.drawFillTriangle(xMax/2, 0, 0, y, xMax, yMax-y, aColor, bColor, dColor);
      else
        theRamCanvas.drawFillTriangle(xMax/2, 0, 0, y, xMax, yMax-y, bColor, cColor, aColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_FFBTRI Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_FFTRI
  std::cout << "Starting DO_FFTRI" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*2;i++)
    for(int y=0;y<=yMax;y+=25)
      if(y%2)
        theRamCanvas.drawFillTriangle(xMax/2, 0, 0, y, xMax, yMax-y, aColor);
      else
        theRamCanvas.drawFillTriangle(xMax/2, 0, 0, y, xMax, yMax-y, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_FFTRI Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_FGBTRI
  std::cout << "Starting DO_FGBTRI" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*2;i++)
    for(int x1=xMax,j=0;x1>=0;x1-=BSIZE/64,j++)
      if(j%2)
        theRamCanvas.drawFillTriangle(x1, yMax/2, x1+BSIZE/2, yMax/2+x1, x1+BSIZE/2, yMax/2-x1, aColor, bColor, dColor);
      else
        theRamCanvas.drawFillTriangle(x1, yMax/2, x1+BSIZE/2, yMax/2+x1, x1+BSIZE/2, yMax/2-x1, bColor, cColor, aColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_FGBTRI Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_FGTRI
  std::cout << "Starting DO_FGTRI" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*16;i++)
    for(int x1=xMax,j=0;x1>=0;x1-=BSIZE/128,j++)
      if(j%2)
        theRamCanvas.drawFillTriangle(x1, yMax/2, x1+BSIZE/2, yMax/2+x1, x1+BSIZE/2, yMax/2-x1, aColor);
      else
        theRamCanvas.drawFillTriangle(x1, yMax/2, x1+BSIZE/2, yMax/2+x1, x1+BSIZE/2, yMax/2-x1, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_FGTRI Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_CIRCLE
  std::cout << "Starting DO_CIRCLE" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*16;i++)
    for(int xy=100, j=0;xy<yMax && xy<=xMax;xy+=1, j++)
      if(j%2)
        theRamCanvas.drawCircle(xy, xy, xMax-xy, aColor);
      else
        theRamCanvas.drawCircle(xy, xy, xMax-xy, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_CIRCLE Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_RECT
  std::cout << "Starting DO_RECT" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*16;i++)
    for(int xy=0, j=0;xy<yMax && xy<=xMax;xy+=BSIZE/128, j++)
      if(j%2)
        theRamCanvas.drawFillRectangle(xy, xy, xMax-xy, yMax-xy, aColor);
      else
        theRamCanvas.drawFillRectangle(xy, xy, xMax-xy, yMax-xy, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_RECT Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_HLINE_NC
  std::cout << "Starting DO_HLINE_NC" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*512;i++)
    for(int y=0;y<=yMax;y+=1)
      if(y%2)
        theRamCanvas.drawHorzLineNC(0, xMax, y, aColor);
      else
        theRamCanvas.drawHorzLineNC(0, xMax, y, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_HLINE_NC Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_HLINE
  std::cout << "Starting DO_HLINE" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*128;i++)
    for(int y=0;y<=yMax;y++)
      if(y%2)
        theRamCanvas.drawLine(0, y, xMax, y, aColor);
      else
        theRamCanvas.drawLine(0, y, xMax, y, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_HLINE Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_VLINE
  std::cout << "Starting DO_VLINE" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*32;i++)
    for(int x=0;x<=xMax;x++)
      if(x%2)
        theRamCanvas.drawLine(x, 0, x, yMax, aColor);
      else
        theRamCanvas.drawLine(x, 0, x, yMax, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_VLINE Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_VLINE_NC
  std::cout << "Starting DO_VLINE_NC" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*32;i++)
    for(int x=0;x<=xMax;x++)
      if(x%2)
        theRamCanvas.drawVertLineNC(0, yMax, x, aColor);
      else
        theRamCanvas.drawVertLineNC(0, yMax, x, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_VLINE_NC Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_45LINE
  std::cout << "Starting DO_45LINE" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*128;i++)
    for(int y=0;y<=yMax;y++)
      if(y%2)
        theRamCanvas.drawLine(0, y, xMax, xMax+y, aColor);
      else
        theRamCanvas.drawLine(0, y, xMax, xMax+y, bColor);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_45LINE Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_TRIVLN
  std::cout << "Starting DO_TRIVLN" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  theRamCanvas.drawLine(     0,      0, xMax/2, yMax/2, aColor);
  theRamCanvas.drawLine(xMax/2, yMax/2,   xMax,   yMax, bColor);
  theRamCanvas.autoHistStrech();
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_TRIVLN Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_INTRP_AVG9
  std::cout << "Starting DO_INTRP_AVG9" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*8;i++)
    for(int y=0;y<=yMax;y+=1)
      for(int x=0;x<=xMax;x+=1)
        theRamCanvas.drawPoint(x, y, theRamCanvas.getPxColorInterpAvg9(x, y));
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_INTRP_AVG9 Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_INTRP_BILN
  std::cout << "Starting DO_INTRP_BILN" << std::endl;
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*1;i++)
    for(double y=0;y<=yMax;y+=0.3)
      for(double x=0;x<=xMax;x+=0.7)
        theRamCanvas.drawPointNC((int)x, (int)y, theRamCanvas.getPxColorInterpBLin(x, y));
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_INTRP_BILN Runtime " << bmTime.count() << " sec" << std::endl;
#endif

#if DO_CONV
  std::cout << "Starting DO_CONV" << std::endl;
  double kernel[10*10];
  int kSize = 9;
  theRamCanvas.computeConvolutionMatrixGausian(kernel, kSize, 10);
  bmStartTime = std::chrono::system_clock::now();
  for(int i=0;i<REPS*2;i++)
    theRamCanvas.convolution(kernel, kSize);
  bmEndTime = std::chrono::system_clock::now();
  bmTime = std::chrono::system_clock::now() - bmStartTime;
  std::cout << "  DO_CONV Runtime " << bmTime.count() << " sec" << std::endl;
#endif

  std::cout << "Benchmarks Complete" << std::endl;
  std::cout << "Center Pixel: " << theRamCanvas.getPxColor(BSIZE/2, BSIZE/2) << std::endl;
  std::cout << "Center Pixel C1(8-bit): " << (int)theRamCanvas.getPxColor(BSIZE/2, BSIZE/2).getC0_byte() << std::endl;
  std::chrono::duration<double> tbmRunTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Benchmark Runtime " << tbmRunTime.count() << " sec" << std::endl;

#if DO_OUT_TIF
  std::cout << "Starting DO_OUT_TIF" << std::endl;
  theRamCanvas.writeTIFFfile("bmark.tiff");
#endif

#if DO_OUT_RAW
  std::cout << "Starting DO_OUT_RAW" << std::endl;
  theRamCanvas.writeRAWfile("bmark.mrw");
#endif

  std::cout << "I/O Complete" << std::endl; 
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
