// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/

/**
 @file      mandelbrot_binary.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     This program draws a Mandelbrot the binary method.@EOL
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

  We use the "binary" method with a twist.  

   * bin: The traditional binary method
   * gray: Shaded by the argument
   * quad: Like the traditional method, but different colors for each quadrant

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

const double pi     = 3.141592653589793238462643383279502884;
const int    CSIZE  = 2048;
const int    MAXITR = 2048;
const double BALL   = 100;

/* This is out here so that it will get allocated on the heap. I'm too lazy to use malloc just this moment. */
double theValues[CSIZE][CSIZE];

double ranges[3][4] = { { -2.0,        1.0,       -1.5,        1.5       },
                        { -0.12,      -0.03,      -0.92, -0.81 },
                        {  0.0353469,  0.5353469,  0.1153845,  0.6153845 }
};

enum class whyStopMB {OUTSET, MAXCOUNT, INSET};

int main(void)
{
  mjr::ramCanvas3c8b   binRamCanvas(CSIZE, CSIZE), grayRamCanvas(CSIZE, CSIZE), quadRamCanvas(CSIZE, CSIZE);
  mjr::color3c8b       theColor;
  whyStopMB               why;           

  for(int i=0; i<3; i++) {
    //for(int i : { 0 } ) {
    binRamCanvas.newRealCoords(ranges[i][0], ranges[i][1], ranges[i][2], ranges[i][3]);
    binRamCanvas.clrCanvasToBlack();
    std::complex<double> z;
    for(int y=0;y<binRamCanvas.get_numYpix();y++) {
      if((y%(CSIZE/10))==0)
        std::cout << "    CASE: " << i << " LINE: " << y << "/" << CSIZE << std::endl;
      for(int x=0;x<binRamCanvas.get_numXpix();x++) {
        int count;
        double cr = binRamCanvas.int2realX(x);
        double ci = binRamCanvas.int2realY(y);
        std::complex<double> c(cr, ci);
        double p = std::abs(c-0.25);
        if((cr >= p-2.0*p*p+0.25) && std::abs(c+1.0) >= 0.25) {
          z=c;
          for(count=0; ; count++) {
            if(count>=MAXITR) {
              why = whyStopMB::MAXCOUNT;
              break;
            }
            if(std::abs(z)>BALL) {
              why = whyStopMB::OUTSET;
              break;
            }
            z = z * z + c;    
          }
        } else {
          why = whyStopMB::INSET;
        }

        if(why == whyStopMB::OUTSET) {
          double zAbs = std::abs(z);
          if(zAbs > 0.001) {
            int ns = ( std::imag(z) > 0 ? 0 : 255 );
            int ew = ( std::real(z) > 0 ? 0 : 255 );
            grayRamCanvas.drawPoint(x, y, theColor.cmpGrey(mjr::unitTooIntLinMap((std::real(z) / zAbs + 1.0) / 2.0, 255)));
            binRamCanvas.drawPoint(x, y,  mjr::color3c8b( ns, ns, ns));
            quadRamCanvas.drawPoint(x, y, mjr::color3c8b(ns, 255-(ns+ew)/2, ew));
          }
        } else {
          grayRamCanvas.drawPoint(x, y, "red");
          binRamCanvas.drawPoint(x, y,  "red");
          quadRamCanvas.drawPoint(x, y, "red");
        }
      }
    }
    
    binRamCanvas.writeTIFFfile("mandelbrot_binary_bin_"    + std::to_string(i) + ".tiff");
    grayRamCanvas.writeTIFFfile("mandelbrot_binary_gray_"  + std::to_string(i) + ".tiff");
    quadRamCanvas.writeTIFFfile("mandelbrot_binary_quad_"  + std::to_string(i) + ".tiff");
  }  
}
