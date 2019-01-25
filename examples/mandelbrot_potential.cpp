// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      mandelbrot_potential.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     This program draws a Mandelbrot set using the "potential"@EOL
 @std       C++98
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

  This example program computes the potential function of the Mandelbrot set over various regions of the complex plane.  For each region it produces three
  images -- two POV-Ray height fields and a 16-bit greyscale images.

  One can create a BOV-type data file like so:

     dd if=mandelbrot_potential_2.mrw skip=100 iflag=skip_bytes of=mandelbrot_potential_2.mrd

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

//#define CSIZE 4096
#define CSIZE 1024
#define MAXITR 6000
#define BALL 10000000.0

enum class whyStopMPO {OUTSET, MAXCOUNT, INSET};

/* This is out here so that it will get allocated on the heap. I'm too lazy to use malloc just this moment. */
double theValues[CSIZE][CSIZE];

double ranges[3][4] = { { -2.0,        1.0,       -1.5,        1.5       },
                        { -0.12,      -0.03,      -0.92,      -0.81      },
                        {  0.0353469,  0.5353469,  0.1153845,  0.6153845 } };

int main(void) {
  double             maxPot=0;
  double             minPot=BALL;
  mjr::color3c8b     aColor;
  mjr::ramCanvas3c8b theRamCanvas(CSIZE, CSIZE);
  whyStopMPO            why;           

  for(int i=0; i<3; i++) {
    //for(int i : { 0 } ) {
    theRamCanvas.newRealCoords(ranges[i][0], ranges[i][1], ranges[i][2], ranges[i][3]);
    theRamCanvas.clrCanvasToBlack();
    /* Compute the potential function on our grid.  For off-set points we store the potential in an array, for in-set points we store a -1.  */
    std::complex<double> z;
    for(int y=0;y<theRamCanvas.get_numYpix();y++) {
      if((y%(CSIZE/10))==0)
        std::cout << "    CASE: " << i << " LINE: " << y << "/" << CSIZE << std::endl;
      for(int x=0;x<theRamCanvas.get_numXpix();x++) {
        int count;
        double cr = theRamCanvas.int2realX(x);
        double ci = theRamCanvas.int2realY(y);
        std::complex<double> c(cr, ci);
        double p = std::abs(c-0.25);
        if((cr >= p-2.0*p*p+0.25) && std::abs(c+1.0) >= 0.25) {
          z=c;
          for(count=0; ; count++) {
            if(count>=MAXITR) {
              why = whyStopMPO::MAXCOUNT;
              break;
            }
            if(std::abs(z)>BALL) {
              why = whyStopMPO::OUTSET;
              break;
            }
            z = z * z + c;    
          }
        } else {
          why = whyStopMPO::INSET;
        }
        if(why == whyStopMPO::OUTSET) {
          double pot = 0;
          if(count<1000) {
            double zn = std::norm(z);
            if(zn > 1) {
              pot = 0.5*log(zn)/pow(2.0, count);
            }
          }
          theValues[x][y]=pot;
          if(maxPot < pot) { maxPot = pot; }
          if(minPot > pot) { minPot = pot; }
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
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      for(int y=0;y<theRamCanvas.get_numYpix();y++) {
        double pot=theValues[x][y];
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
    theRamCanvas.writeTGAfile("mandelbrot_potential_a_" + std::to_string(i) + ".tga");

    /* Draw a POV-Ray height field from the potential data.  This one will have the Mandelbrot set itself set the maximum height.  This allows us to render
       plateau-like images. */
    std::cout << "TGA_2" << std::endl;
    for(int x=0;x<theRamCanvas.get_numXpix();x++) 
      for(int y=0;y<theRamCanvas.get_numYpix();y++) 
        if(theValues[x][y] <  0)
          theRamCanvas.drawPoint(x, y, aColor.cmpGreyTGA16bit(0xffff-1));
    theRamCanvas.writeTGAfile("mandelbrot_potential_b_" + std::to_string(i) + ".tga");

    /* We dump out 16-bit unsigned integers less than 2^15 so that they may be interpreted as signed integers by tools like VisIT which might read the data
       via the BOV file. */
    std::cout << "RAW_2" << std::endl;
    mjr::ramCanvas1c16b theRamCanvasG(CSIZE, CSIZE);
    for(int x=0;x<theRamCanvasG.get_numXpix();x++) {
      for(int y=0;y<theRamCanvasG.get_numYpix();y++) {
        double pot=theValues[x][y];
        if(pot >= 0) {
          pot = pot - minPot;
          pot=(0x8000-1)-pot*(0x8000-2)/(maxPot-minPot);
          theRamCanvasG.drawPoint(x, y, pot);
        } else {
          theRamCanvasG.drawPoint(x, y, 0x8000-1);
        }
      }
    }
    theRamCanvasG.writeRAWfile("mandelbrot_potential_" + std::to_string(i) + ".mrw");
    theRamCanvasG.autoHistStrech();
    theRamCanvasG.writeTIFFfile("mandelbrot_potential_" + std::to_string(i) + ".tiff");
  }  
}
