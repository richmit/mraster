// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      potMandelbrot.cpp
 @author    Mitch Richling <http://www.mitchr.me>
 @brief     This program draws a Mandelbrot set using the "potential"@EOL
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

  This example program computes the potential function of the Mandelbrot set over various regions of the complex plane.  For each region it produces three
  images -- two POV-Ray height fields and a 16-bit greyscale images.

  One can create a BOV-type data file like so:

     dd if=potMandelbrot_2.mrw skip=100 iflag=skip_bytes of=potMandelbrot_2.mrd

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"
#include "math.h"

using namespace mjr;

#define CSIZE 5000
//#define CSIZE 512
#define MAXITR 6000
#define BALLSIZE 10000000.0

/* This is out here so that it will get allocated on the heap. I'm too lazy to use malloc just this moment. */
double theValues[CSIZE][CSIZE];

double ranges[3][4] = { { -2.0,        1.0,       -1.5,        1.5       },
                        { -0.12,      -0.03,      -0.92, -0.81 },
                        {  0.0353469,  0.5353469,  0.1153845,  0.6153845 } };

int main(void) {
  int x, y, count;
  double xr, yr, zx, zy, tempx, pot, maxPot=0, minPot=0;
  color4c8b aColor;
  ramCanvas4c8b theRamCanvas(CSIZE, CSIZE);

  for(int i=0; i<3; i++) {
  //for(int i : { 0 } ) {
    theRamCanvas.newRealCoords(ranges[i][0], ranges[i][1], ranges[i][2], ranges[i][3]);
    theRamCanvas.clrCanvasToBlack();
    /* Compute the potential function on our grid.  We use the ramCanvas as a nice way to convert from integer to real coordinates on this grid, but we store
       the data in a floating point array.  We store -1 if the point appears to be in the Mandelbrot set, and the potential otherwise.  We do this so that we
       can color the set differently allowing us to render a canyon-like plot instead of a plateau-like plot.  We also compute the min and max potential so
       that we maximize the resulting image's color histogram. */
    for(y=0;y<theRamCanvas.get_numYpix();y++) {
      if((y%(CSIZE/10))==0)
        std::cout << "    CASE: " << i << " LINE: " << y << "/" << CSIZE << std::endl;
      for(x=0;x<theRamCanvas.get_numXpix();x++) {
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

    std::cout << "MIN: " << minPot << " MAX:" << maxPot << std::endl;

    /* Draw a POV-Ray height field from the potential data.  This one will have the Mandelbrot set itself set to zero height (black).  This allows us to
       render canyon-like images.  Rendering this data in 3D will tend to emphasize the edge of the set (the walls of the canyon), so a high maximum iteration
       count will yield better results. */
    std::cout << "TGA_1" << std::endl;
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
    theRamCanvas.writeTGAfile("potMandelbrot_a_" + std::to_string(i) + ".tga");

    /* Draw a POV-Ray height field from the potential data.  This one will have the Mandelbrot set itself set the maximum height.  This allows us to render
       plateau-like images. */
    std::cout << "TGA_2" << std::endl;
    for(x=0;x<theRamCanvas.get_numXpix();x++) 
      for(y=0;y<theRamCanvas.get_numYpix();y++) 
        if(theValues[x][y] <  0)
          theRamCanvas.drawPoint(x, y, aColor.cmpGreyTGA16bit(0xffff-1));
    theRamCanvas.writeTGAfile("potMandelbrot_b_" + std::to_string(i) + ".tga");

    /* We dump out 16-bit unsigned integers less than 2^15 so that they may be interpreted as signed integers by tools like VisIT which might read the data
       via the BOV file. */
    std::cout << "RAW_2" << std::endl;
    ramCanvas1c16b theRamCanvasG(CSIZE, CSIZE);
    for(x=0;x<theRamCanvasG.get_numXpix();x++) {
      for(y=0;y<theRamCanvasG.get_numYpix();y++) {
        pot=theValues[x][y];
        if(pot >=  0) {
          pot = pot - minPot;
          pot=(0x8000-1)-pot*(0x8000-2)/(maxPot-minPot);
          theRamCanvasG.drawPoint(x, y, pot);
        } else {
          theRamCanvasG.drawPoint(x, y, 0x8000-1);
        }
      }
    }
    theRamCanvasG.writeRAWfile("potMandelbrot_b_" + std::to_string(i) + ".mrw");
    theRamCanvasG.applyHomoPixTfrm(&color1c16b::tfrmStdPow, 6);
    theRamCanvasG.autoHistStrech();
    theRamCanvasG.writeTGAfile("potMandelbrot_bg_" + std::to_string(i) + ".tga");
  }  
}
