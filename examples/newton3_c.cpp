// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      newton3_c.cpp
 @author    Mitch Richling <http://www.mitchr.me>
 @brief     Draw a Newton Fractical -- color by root and max modulus.@EOL
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"
#include <math.h>
#include <complex>
#include <iostream>

#define pi 3.14159265359

using namespace mjr;

int main(void) {
  int   MaxCount = 155;
  int   MultCol  = 100;
  float Tol      = .0001;
  std::complex<double> r1( 1.0, 0);
  std::complex<double> r2(-0.5,  sin(2*pi/3));
  std::complex<double> r3(-0.5, -sin(2*pi/3));
  std::complex<double> r4(-1.0, 0);
  std::complex<double> r5(0.5,  sin(2*pi/3));
  std::complex<double> r6(0.5, -sin(2*pi/3));

  ramCanvas4c8b theRamCanvas = ramCanvas4c8b(4096, 4096, -2.0, 2.0, -2.0, 2.0);

  for(int y=0;y<theRamCanvas.get_numYpix();y++) {
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      std::complex<double> z(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));
      int  count = 0;
      double maxMod = 0.0;
      while((count < MaxCount) && 
            (abs(z-r1) >= Tol) && (abs(z-r2) >= Tol) && (abs(z-r3) >= Tol) &&
            (abs(z-r4) >= Tol) && (abs(z-r5) >= Tol) && (abs(z-r6) >= Tol)) {
        if(abs(z) > 0) {
          z = z-(z*z*z*z*z*z-1.0)/(6.0*z*z*z*z*z);
        }
        if(abs(z)>maxMod)
          maxMod=abs(z);
        count++;
      }

      if(abs(z-r1) <= Tol)
        theRamCanvas.drawPoint(x, y, color4c8b(int(255-maxMod*MultCol), 0,                       0));
      if(abs(z-r2) <= Tol)
        theRamCanvas.drawPoint(x, y, color4c8b(0,                       int(255-maxMod*MultCol), 0));
      if(abs(z-r3) <= Tol)
        theRamCanvas.drawPoint(x, y, color4c8b(0,                       0,                       int(255-maxMod*MultCol)));
      if(abs(z-r4) <= Tol)
        theRamCanvas.drawPoint(x, y, color4c8b(int(255-maxMod*MultCol), int(255-maxMod*MultCol), 0));
      if(abs(z-r5) <= Tol)
        theRamCanvas.drawPoint(x, y, color4c8b(0,                       int(255-maxMod*MultCol), int(255-maxMod*MultCol)));
      if(abs(z-r6) <= Tol)
        theRamCanvas.drawPoint(x, y, color4c8b(int(255-maxMod*MultCol), 0,                       int(255-maxMod*MultCol)));
    }
  }
  // The biggest reason homogeneous transforms are in the library is to support color scale correction.  Instead of getting the scale 100% correct, just
  // transform the results to get something workable.
  theRamCanvas.applyHomoPixTfrm(&color4c8b::tfrmLinearGreyLevelScale, 255.0/155, 0.0);
  theRamCanvas.writeTGAfile("newton3_c.tga");
}
