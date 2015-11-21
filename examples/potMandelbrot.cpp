// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      potMandelbrot.cpp
 @author    Mitch Richling <http://www.mitchr.me>
 @brief     This program draws a mandelbrot set using the "potential"@EOL
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

  This generates a Povray color scheme to generate a height field of the "potential" of the mandelbrot set.

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"
#include "math.h"

using namespace mjr;

#define MAXITR 656
//#define BALLSIZE 2.0
#define BALLSIZE 100000.0

// This is out here so that it will get allocated on the heap
// I'm too lazy to use malloc just this moment.
double theValues[2000][2000];

int main(void) {
  int x, y, count;
  double xr, yr, zx, zy, tempx;
  double pot, maxPot=0, minPot=0;
  color4c8b aColor;
  ramCanvas4c8b theRamCanvas = ramCanvas4c8b(512, 512,
//                                     -2, 2, -2, 2
//                                     -0.1773439, -0.052343905, -0.9173759, -0.7923759
//                                     -0.08673248, -0.07110748, -0.83358735, -0.81796235
//                                     0.03534691, 0.5353469, 0.11538452, 0.6153845
                                             -2.0, 1.0, -1.5, 1.5
//                                     0.3260546, 0.2560546+0.1225859, 0.25996086, 0.25996086+0.12649214
                                     );
  
  /* Compute the min and max */
  for(x=0;x<theRamCanvas.get_numXpix();x++) {
    for(y=0;y<theRamCanvas.get_numYpix();y++) {
      for(xr=theRamCanvas.int2realX(x),yr=theRamCanvas.int2realY(y),zx=zy=0.0,count=0;
          (zx*zx+zy*zy<BALLSIZE)&&(count<MAXITR);
          count++,tempx=zx*zx-zy*zy+xr,zy=2*zx*zy+yr,zx=tempx) ;
      if(count < MAXITR) {
        pot=0.5*log(zx*zx+zy*zy)/pow(2.0,count);
        if(pot < 0.0) pot = 0.0;
        theValues[x][y]=pot;
        if(x == 0 && y == 0) {
          minPot = pot;
          maxPot = pot;
        } else {
          if(maxPot < pot) { maxPot = pot; }
          if(minPot > pot) { minPot = pot; }
        }
      } else {
        theValues[x][y] = -1;
      }
    }
  }

  fprintf(stderr, "MIN: %10.5f  MAX: %10.5f\n", (float)minPot, (float)maxPot);

  for(x=0;x<theRamCanvas.get_numXpix();x++) {
    for(y=0;y<theRamCanvas.get_numYpix();y++) {
      pot=theValues[x][y];
      if(pot >=  0) {
        pot = pot - minPot;
        pot=(0xffff-1)-pot*(0xffff-2)/(maxPot-minPot);
		aColor.cmpGreyTGA16bit((int)pot);
      } else {
		aColor.setToBlack();
      }
	  theRamCanvas.drawPoint(x, y, aColor);
    }
  }
  theRamCanvas.writeTGAfile("potMandelbrot_1.tga");

  /* Draw */
  for(x=0;x<theRamCanvas.get_numXpix();x++) {
    for(y=0;y<theRamCanvas.get_numYpix();y++) {
      for(xr=theRamCanvas.int2realX(x),yr=theRamCanvas.int2realY(y),zx=zy=0.0,count=0;
          (zx*zx+zy*zy<BALLSIZE)&&(count<MAXITR);
          count++,tempx=zx*zx-zy*zy+xr,zy=2*zx*zy+yr,zx=tempx) ;
      if(count < MAXITR) {
        pot=0.5*log(zx*zx+zy*zy)/pow(2.0,count);
        if(pot < 0.0) pot = 0;
        pot = pot - minPot;
        if(pot < 0.0) pot = 0;
        pot=(0xffff-1)-pot*(0xffff-2)/(maxPot-minPot);
        aColor.cmpGreyTGA16bit((int)pot);
      } else {
		aColor.cmpGreyTGA16bit(0xffff-1);
      }
	  theRamCanvas.drawPoint(x, y, aColor);
    }
  }
  theRamCanvas.writeTGAfile("potMandelbrot_2.tga");
  
}
