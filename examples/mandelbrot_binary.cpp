// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_binary.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     This program draws a Mandelbrot the binary method.@EOL
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

 We use the "binary" method with a twist.

  - bin: The traditional binary method
  - gray: Shaded by the argument
  - quad: Like the traditional method, but different colors for each quadrant

 This example demonstrates how to use some of the types defined in the ramCanvas object (integer coordinates, double coordinates, color, and color channel)
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
const int    MAXITR = 1024*1;

double ranges[3][4] = { { -2.0,        1.0,       -1.5,        1.5       },
                        { -0.12,      -0.03,      -0.92,      -0.81
                        {  0.0353469,  0.5353469,  0.1153845,  0.6153845 }
                      };

enum class whyStopMB {OUTSET, MAXCOUNT, INSET};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b rc;    // The Ram Canvas type we will use
typedef rc::colorType      rcc;   // The color type in our Ram Canvas type

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int              CSIZE = 1024*1;
  const rc::coordFltType BALL  = 100;
  rc                     binRamCanvas(CSIZE, CSIZE), grayRamCanvas(CSIZE, CSIZE), quadRamCanvas(CSIZE, CSIZE);
  whyStopMB              why;

  for(int i=0; i<3; i++) {
    binRamCanvas.newRealCoords(ranges[i][0], ranges[i][1], ranges[i][2], ranges[i][3]);
    binRamCanvas.clrCanvasToBlack();
    std::complex<rc::coordFltType> z;
    for(rc::coordIntType y=0;y<binRamCanvas.getNumPixY();y++) {
      if((y%(CSIZE/10))==0)
        std::cout << "    CASE: " << i << " LINE: " << y << "/" << CSIZE << std::endl;
      for(rc::coordIntType x=0;x<binRamCanvas.getNumPixX();x++) {
        int count;
        rc::coordFltType cr = binRamCanvas.int2realX(x);
        rc::coordFltType ci = binRamCanvas.int2realY(y);
        std::complex<rc::coordFltType> c(cr, ci);
        rc::coordFltType p = std::abs(c-0.25);
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
          rc::coordFltType zAbs = std::abs(z);
          if(zAbs > 0.001) {
            rcc::channelType ns = ( std::imag(z) > 0 ? 0 : 255 );
            rcc::channelType ew = ( std::real(z) > 0 ? 0 : 255 );
            grayRamCanvas.drawPoint(x, y, mjr::color3c8b::csCCdiag01::c(static_cast<mjr::ramCanvas3c8b::csIntType>(mjr::unitTooIntLinMap((std::real(z) / zAbs + 1.0) / 2.0, 255))));
            binRamCanvas.drawPoint(x, y,  rcc(ns, ns, ns));
            quadRamCanvas.drawPoint(x, y, rcc(ns, static_cast<rcc::channelType>(255-(ns+ew)/2), ew));
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

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
