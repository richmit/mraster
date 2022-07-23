// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_bm_cplx_hyper.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark drawing a mandelbrot set using the C++ complex type and excluding hypocycloids.@EOL
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

  Basic benchmark.  Uses complex numbers.  Has several algorithmic optimizations.

  Depending upon what region is being drawn, the distribution of points satisfying the various optimization conditions will change.  Each optimization has a
  cost in execution, and if that cost is higher than the benefits on the region then it should be avoided -- this is especially true with CYCORLIM.  For this
  reason the set of boolean variables determining what optimizations to use should be tuned for the region.  In addition, CYCORLIM cost is dominated by
  LASTMAX.  For large, zoomed out images this optimization breaks even at about LASTMAX=4.  For zoomed in images with a significant space covered by a period
  N bulb, setting LASTMAX to something larger than N can provide a significant speedup.

           | doBOUND | doPERIOD1 | doPERIOD2 | doREFLCT | doCYCORLIM | LASTMAX | Speed Up |
           |---------+-----------+-----------+----------+------------+---------+----------|
           | true    | -         | -         | -        | -          | -       | N/A      |
           | true    | true      | -         | -        | -          | -       | 3.0x     |
           | true    | true      | true      | -        | -          | -       | 4.6x     |
           | true    | true      | true      | true     | -          | -       | 5.6x     |
           | true    | true      | true      | true     | true       | 4       | 5.8x     |

 Note doREFLCT should be implemented differently for cases where symmetry is known in advance.  In these cases we can simply avoid iterating over
 the symmetric points at all instead of testing to see if we are on a symmetric point.
********************************************************************************************************************************************************.H.E.**/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int NUMITR   = 1024;
  const int CSIZE    = 7680;
  const int LASTMAX  = 4;
  mjr::ramCanvas3c8b theRamCanvas(CSIZE, CSIZE, -2.2, 0.8, -1.5, 1.5);
  theRamCanvas.clrCanvasToBlack();

  long int countPERIOD1  = 0;
  long int countPERIOD2  = 0;
  long int countMAXCOUNT = 0;
  long int countBOUND    = 0;
  long int countCYCORLIM = 0;
  long int countREFLCT   = 0;

  bool doPERIOD1  = true;
  bool doPERIOD2  = true;
  bool doBOUND    = true;
  bool doCYCORLIM = true;
  bool doREFLCT   = true;

  bool doStatusPrint = false;

  std::vector<std::complex<double>> lastZs(LASTMAX);
  for(int y=0;y<theRamCanvas.get_numYpix();y++) {
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      int count;
      double cr = theRamCanvas.int2realX(x);
      double ci = theRamCanvas.int2realY(y);
      std::complex<double> c(cr, ci), z(0, 0);
      double p = std::abs(c-0.25);
      if(doPERIOD1 && (cr <= p-2.0*p*p+0.25)) {
        theRamCanvas.drawPoint(x, y, "blue");
        countPERIOD1++;
      } else {
        if(doPERIOD2 && (std::abs(c+1.0) <= 0.25)) {
          theRamCanvas.drawPoint(x, y, "green");
          countPERIOD2++;
        } else {
          if(doREFLCT && (!(theRamCanvas.getPxColor(std::conj(c)).isBlack()))) {
            //theRamCanvas.drawPoint(x, y, "magenta");
            theRamCanvas.drawPoint(x, y, theRamCanvas.getPxColor(std::conj(c)));
            countREFLCT++;
          } else {
            for(count=0; ; count++) {
              z = z * z + c;

              if(count>=NUMITR) {
                theRamCanvas.drawPoint(x, y, "white");
                countMAXCOUNT++;
                break;
              }
              if(doBOUND && (std::norm(z)>4.0)) {
                //theRamCanvas.drawPoint(x, y, "red");
                theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(static_cast<mjr::ramCanvas3c8b::colorChanType>((5*count+50)%256), 0, 0));
                countBOUND++;
                break;
              }
              if(doCYCORLIM && (count>LASTMAX) && std::any_of(lastZs.begin(), lastZs.end(), [&z](std::complex<double> zl){return std::abs(zl-z)<0.0001;}) ) {
                theRamCanvas.drawPoint(x, y, "yellow");
                //theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType((5*count+50)%256, (count+50)%256, 0));
                countCYCORLIM++;
                break;
              }
              lastZs[count%LASTMAX] = z;
            }
          }
        }
      }
    }

    if( doStatusPrint && (((y%(CSIZE/32))==0) || (y==(CSIZE-1))) ) {
      std::cout << "LINE: " << y << "/" << CSIZE << std::endl;
      std::cout << "  countPERIOD1:  " << countPERIOD1  << std::endl;
      std::cout << "  countPERIOD2:  " << countPERIOD2  << std::endl;
      std::cout << "  countMAXCOUNT: " << countMAXCOUNT << std::endl;
      std::cout << "  countBOUND:    " << countBOUND   << std::endl;
      std::cout << "  countCYCORLIM: " << countCYCORLIM << std::endl;
      std::cout << "  countREFLCT:   " << countREFLCT   << std::endl;
    }
  }
  theRamCanvas.writeTIFFfile("mandelbrot_bm_cplx_hyper.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
