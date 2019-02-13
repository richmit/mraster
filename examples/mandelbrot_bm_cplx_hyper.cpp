// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      mandelbrot_bm_cplx_hyper.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark drawing a mandelbrot set using the C++ complex type and excluding hypocycloids.@EOL
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <complex>                                                       /* STL algorithm           C++11    */

/** Reasons iteration may stop */
enum class whyStopMCH { OUTSET,   //!< Not in set (|z|>2)
                        MAXCOUNT, //!< Maximum iteration reached
                        PERIOD1,  //!< In set (known region)
                        PERIOD2,  //!< In set (known region)
                        CYCLE     //!< Found a cycle
                      };

int main(void) {
  mjr::color3c8b aColor;

  const int NUMITR = 1024;
  const int CSIZE  = 7680/4;
  //mjr::ramCanvas3c8b theRamCanvas(CSIZE, CSIZE, -2.2, 0.8, -1.5, 1.5);
  
  // double xCenter = -0.761574;
  // double yCenter = -0.0847596;
  // double radius  = 1.0e-3;

  double xCenter = -0.71;
  double yCenter = 0.0;
  double radius  = 1.3;


  mjr::ramCanvas3c8b theRamCanvas(CSIZE, CSIZE, xCenter-radius, xCenter+radius, yCenter-radius, yCenter+radius);
  
  long int countPERIOD1  = 0;
  long int countPERIOD2  = 0;
  long int countMAXCOUNT = 0;
  long int countOUTSET   = 0;
  long int countCYCLE    = 0;

  for(int y=0;y<theRamCanvas.get_numYpix();y++) { 
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      whyStopMCH why;           
      int count;
      double cr = theRamCanvas.int2realX(x);
      double ci = theRamCanvas.int2realY(y);
      std::complex<double> c(cr, ci), z(0, 0), zLast(5, 5);
      double p = std::abs(c-0.25);
      if( false && (cr <= p-2.0*p*p+0.25)) {
        why = whyStopMCH::PERIOD1;
        countPERIOD1++;
      } else {
        if( false && (std::abs(c+1.0) <= 0.25)) {
          why = whyStopMCH::PERIOD2;
          countPERIOD2++;
        } else {
          for(count=0; ; count++) {
            if(count>=NUMITR) {
              why = whyStopMCH::MAXCOUNT;
              countMAXCOUNT++;
              break;
            }
            if(std::norm(z)>4.0) {
              why = whyStopMCH::OUTSET;
              countOUTSET++;
              break;
            }
            if( false && (std::abs(z-zLast)<0.0001)) {
              why = whyStopMCH::CYCLE;
              countCYCLE++;
              break;
            }
            zLast = z;
            z = z * z + c;
          }
        }
      }      
      // switch (why) {
      //   case whyStopMCH::MAXCOUNT : theRamCanvas.drawPoint(x, y, "red");                                                 break;
      //   case whyStopMCH::OUTSET   : theRamCanvas.drawPoint(x, y, aColor.cmpGrey(mjr::intWrap(count*20, 256))); break;  // Disable to more clearly CYCLE points          
      //   case whyStopMCH::PERIOD1  : theRamCanvas.drawPoint(x, y, "blue");                                                break;
      //   case whyStopMCH::PERIOD2  : theRamCanvas.drawPoint(x, y, "green");                                               break;
      //   case whyStopMCH::CYCLE    : theRamCanvas.drawPoint(x, y, "cyan");                                                break;
      // }
      if( (why == whyStopMCH::MAXCOUNT) || (why == whyStopMCH::CYCLE) ) {
        theRamCanvas.drawPoint(std::real(z), std::imag(z), "white");
      }
    }

    if( ((y%(CSIZE/32))==0) || (y==(CSIZE-1)) ) {
      std::cout << "LINE: " << y << "/" << CSIZE << std::endl;
      std::cout << "  countPERIOD1:  " << countPERIOD1  << std::endl;
      std::cout << "  countPERIOD2:  " << countPERIOD2  << std::endl;
      std::cout << "  countMAXCOUNT: " << countMAXCOUNT << std::endl;
      std::cout << "  countOUTSET:   " << countOUTSET   << std::endl;
      std::cout << "  countCYCLE:    " << countCYCLE    << std::endl;
    }
  }
  theRamCanvas.writeTIFFfile("mandelbrot_bm_cplx_hyper.tiff");
}



// *  period 1 cardioid boundry: r = (1 - cos(theta))/2, x = r*cos(theta)+0.25, y = r*sin(theta)
// *  period 2 disk boundry:     r = 0.25, x = r*cos(theta)-1, y = r*sin(theta)
