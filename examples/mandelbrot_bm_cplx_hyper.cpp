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

int main(void) {
  mjr::color3c8b aColor;

  const int NUMITR   = 16*16*4*4;
  const int CSIZE    = 7680/2;
  //mjr::ramCanvas3c8b theRamCanvas(CSIZE, CSIZE, -2.2, 0.8, -1.5, 1.5);
  
  // double xCenter = -0.761574;
  // double yCenter = -0.0847596;
  // double radius  = 1.0e-3;

  double xCenter = -0.71;
  double yCenter = 0.0;
  double radius  = 1.3;

  mjr::ramCanvas3c8b theRamCanvas(CSIZE, CSIZE, xCenter-radius, xCenter+radius, yCenter-radius, yCenter+radius);

  theRamCanvas.clrCanvasToBlack();

  long int countPERIOD1  = 0;
  long int countPERIOD2  = 0;
  long int countMAXCOUNT = 0;
  long int countOUTSET   = 0;
  long int countCYCORLIM = 0;
  long int countREFLCT   = 0;

  for(int y=0;y<theRamCanvas.get_numYpix();y++) { 
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      int count;
      double cr = theRamCanvas.int2realX(x);
      double ci = theRamCanvas.int2realY(y);
      std::complex<double> c(cr, ci), z(0, 0);
      std::vector<std::complex<double>> lastZs(NUMITR+5);
      double p = std::abs(c-0.25);
      if((cr <= p-2.0*p*p+0.25)) {
        theRamCanvas.drawPoint(x, y, "blue");
        countPERIOD1++;
      } else {
        if((std::abs(c+1.0) <= 0.25)) {
          theRamCanvas.drawPoint(x, y, "green");
          countPERIOD2++;
        } else {
          if((theRamCanvas.getPxColor(std::conj(c)).colorSumIntensity()>0)) {
            theRamCanvas.drawPoint(x, y, theRamCanvas.getPxColor(std::conj(c)));
            countREFLCT++;
          } else {
            for(count=0; ; count++) {
              z = z * z + c;
              lastZs[count] = z;
              if(count>=NUMITR) {
                theRamCanvas.drawPoint(x, y, "white");               
                countMAXCOUNT++;
                break;
              }
              if(std::norm(z)>4.0) {
                //theRamCanvas.drawPoint(x, y, "red");
                theRamCanvas.drawPoint(x, y, mjr::color3c8b((5*count+50)%256, 0, 0));
                countOUTSET++;
                break;
              }
              if(count>1 && std::any_of(lastZs.begin(), std::next(lastZs.begin(), count-1), [&z](std::complex<double> zl){return std::abs(zl-z)<0.0001;}) ) {
                //theRamCanvas.drawPoint(x, y, "yellow");
                theRamCanvas.drawPoint(x, y, mjr::color3c8b((5*count+50)%256, (count+50)%256, 0));
                countCYCORLIM++;
                break;
              }
            }
          }
        }
      }      
    }

    if( ((y%(CSIZE/32))==0) || (y==(CSIZE-1)) ) {
      std::cout << "LINE: " << y << "/" << CSIZE << std::endl;
      std::cout << "  countPERIOD1:  " << countPERIOD1  << std::endl;
      std::cout << "  countPERIOD2:  " << countPERIOD2  << std::endl;
      std::cout << "  countMAXCOUNT: " << countMAXCOUNT << std::endl;
      std::cout << "  countOUTSET:   " << countOUTSET   << std::endl;
      std::cout << "  countCYCORLIM: " << countCYCORLIM << std::endl;
      std::cout << "  countREFLCT:   " << countREFLCT   << std::endl;
    }

  }
  theRamCanvas.writeTIFFfile("mandelbrot_bm_cplx_hyper.tiff");
}



// *  period 1 cardioid boundry: r = (1 - cos(theta))/2, x = r*cos(theta)+0.25, y = r*sin(theta)
// *  period 2 disk boundry:     r = 0.25, x = r*cos(theta)-1, y = r*sin(theta)
