// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      tinkerbell_search.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Find parameters for tinkerbell fractals.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/barrymartin/index.html
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
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  const int BSIZ = 480*8;

  std::random_device rd;
  std::mt19937 rEng(rd());
  std::uniform_real_distribution<double> uniform_dist_double(-2.0, 2.0);

  mjr::ramCanvas1c16b theRamCanvas(BSIZ, BSIZ, -2, 2, -2, 2); // Just used for coordinate conversion. ;)

  for(int j=0; j<1000; j++) {
    std::map<uint64_t, uint64_t> ptcnt;
    double a = uniform_dist_double(rEng);
    double b = uniform_dist_double(rEng);
    double c = uniform_dist_double(rEng);
    double d = uniform_dist_double(rEng);
    double x  = 0.1;
    double y  = 0.1;
    double xMax     = x;     
    double yMax     = y;     
    double xMin     = x;     
    double yMin     = y;     
    uint64_t maxII  = 0;
    uint64_t inCnt  = 0;
    uint64_t itr;
    for(itr=1;itr<10000000;itr++) {
      double xNew = x*x-y*y+a*x+b*y;
      double yNew = 2*x*y+c*x+d*y;
      if (xNew > xMax) xMax = xNew;
      if (xNew < xMin) xMin = xNew;
      if (yNew > yMax) yMax = yNew;
      if (yNew < yMin) yMin = yNew;
      if ( !theRamCanvas.isCliped(x, y)) {
        inCnt++;
        theRamCanvas.incPxChan(x, y);
        if(theRamCanvas.getPxColor(x, y).getC0() > maxII) {
          maxII = theRamCanvas.getPxColor(x, y).getC0();
          if(maxII > 16384) { // 1/4 of max possible intensity
            break;
          }
        }
      }
      x=xNew;
      y=yNew;
    }
    if ( (inCnt > 1000000) && (xMin < xMax) && (yMin < yMax) ) {
      mjr::ramCanvas1c16b::coordIntType uCnt = theRamCanvas.statNumNonZeroPixels();
      if (uCnt > 500000) {
        std::cout << "    { " << a <<  ", " << b <<  ", " << c <<  ", " << d <<  ", " << 0.1 <<  ", " << 0.1 <<  ", " << "1e8, " << xMin <<  ", " << xMax <<  ", " << yMin <<  ", " << yMax <<  " }, // " << " INC: " << inCnt << " UNQ: " << uCnt << std::endl;
      }
    }
  }
  return 0;
}
/** @endcond */
