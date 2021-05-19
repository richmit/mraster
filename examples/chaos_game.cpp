// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      chaos_game.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Play the chaos Game.@EOL
 @keywords  fractal ifs
 @std       C++14
 @copyright 
  @parblock
  Copyright (c) 1988-2015,2017, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

  See: https://en.wikipedia.org/wiki/Chaos_game

***************************************************************************************************************************************************************/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <random>                                                        /* C++ random numbers      C++11    */
#include <vector>                                                        /* STL vector              C++11    */ 
#include <list>                                                          /* STL list                C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
struct ifs {
    long itrMax;
    long itrToss;
    int numPts;
    int lastAvoidForward;
    int lastAvoidBackward;
    int lastAvoidLast;
    double factor;
    double radius;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<ifs> ifsList {
  { 10000000, 1000,  3, -1, -1,  -1, 2.0, 1.10},
  {100000000, 1000,  4, -1,  1,  -1, 2.0, 1.10},
  {100000000, 1000,  4, -1,  2,  -1, 2.0, 1.10},
  {100000000, 1000,  4, -1, -1,   1, 2.0, 1.10},
  {100000000, 1000,  4, -1, -1,  -1, 2.0, 1.10},
  {100000000, 1000,  4, -1, -1,  -1, 2.3, 1.10},
  {100000000, 1000,  5,  1,  1,  -1, 2.0, 1.10},
  {100000000, 1000,  5,  2,  2,  -1, 2.0, 1.10},
  {100000000, 1000,  5, -1,  1,   1, 2.0, 0.75},
  {100000000, 1000,  5, -1,  1,  -1, 2.0, 1.10},
  {100000000, 1000,  5, -1,  2,  -1, 2.0, 1.10},
  {100000000, 1000,  5, -1, -1,   1, 2.0, 0.84},
  {100000000, 1000,  5, -1, -1,   1, 2.0, 1.10},
  {100000000, 1000,  5, -1, -1,   1, 2.3, 0.70},
  {100000000, 1000,  5, -1, -1,  -1, 2.0, 1.10},
  {100000000, 1000,  5, -1, -1,  -1, 2.3, 1.10},
  {100000000, 1000,  6,  2,  2,  -1, 2.0, 1.10},
  {100000000, 1000,  6,  3,  1,  -1, 2.0, 1.10},
  {100000000, 1000,  7,  1, -1,   1, 2.5, 0.65},
  {100000000, 1000,  7,  2, -1,   1, 2.5, 0.65},
  {100000000, 1000,  7,  3,  3,   1, 2.5, 0.65},
  {100000000, 1000,  7,  3, -1,   1, 2.5, 0.65},
  {100000000, 1000,  7,  5,  5,   1, 2.5, 0.65},
  {100000000, 1000,  7,  5, -1,   1, 2.5, 0.65},
  {100000000, 1000,  8,  1,  1,   1, 2.0, 0.75},
  {100000000, 1000,  8,  1,  1,  -1, 2.0, 1.01},
  {100000000, 1000,  8,  2,  2,   1, 2.0, 0.94},
  {100000000, 1000,  8,  3,  3,   1, 2.0, 0.94},
  {100000000, 1000,  8,  5,  1,   1, 2.0, 0.94},
  {100000000, 1000,  8,  5,  2,   1, 2.0, 0.94},
  {100000000, 1000,  8,  5,  5,   1, 2.0, 0.94},
  {100000000, 1000, 10,  1,  1,   1, 2.5, 0.57},
  {100000000, 1000, 10,  1,  9,   1, 2.5, 0.65},
  {100000000, 1000, 10,  2,  2,   1, 2.5, 0.65},
  {100000000, 1000, 10,  3,  3,   1, 2.5, 0.65},
  {100000000, 1000, 10,  4,  4,   1, 2.5, 0.65},
  {100000000, 1000, 10,  5,  5,   1, 2.5, 0.65},
  {100000000, 1000, 10,  6,  1,   1, 2.5, 0.65},
  {100000000, 1000, 10,  6,  6,   1, 2.5, 0.65},
  {100000000, 1000, 10,  7,  7,   1, 2.5, 0.65},
  {100000000, 1000, 10,  8,  8,   1, 2.1, 0.87},
  {100000000, 1000, 10,  8,  8,   1, 2.3, 0.74},
  {100000000, 1000, 10,  8,  8,   1, 2.5, 0.65},
  {100000000, 1000, 15,  5,  5,   1, 3.8, 0.36}
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {

  mjr::ramCanvas3c8b theRamCanvas(2160, 2160);
  theRamCanvas.set_drawMode(mjr::ramCanvas3c8b::drawModeType::ADDCLIP);
  std::vector<mjr::color3c8b> aColor{ mjr::color3c8b(1, 1, 1)};
  int numCol = aColor.size();

  std::random_device rd;
  std::minstd_rand0 rEng(rd());

  for(auto &theIFS :ifsList) {
    theRamCanvas.newRealCoords(-theIFS.radius, theIFS.radius, -theIFS.radius, theIFS.radius);
    theRamCanvas.clrCanvasToBlack();

    std::vector<std::complex<double>> points;
    const double pi = 3.141592654;
    double curAngle = pi/2;
    for(int i=0; i<theIFS.numPts; i++) {
      points.push_back(std::complex<double>{cos(curAngle), sin(curAngle)});
      curAngle += 2*pi/theIFS.numPts;
    }
  
    std::complex<double> z{0.1, 0.2};
    int lastPoint = -1;
    double maxMag = 0;
    for(int n=0;n<theIFS.itrMax;n++) {
      int rn = rEng();
      int rpi = rn%theIFS.numPts;
      while(((lastPoint !=-1) && (theIFS.lastAvoidLast    !=-1) && rpi==lastPoint) ||
            ((lastPoint !=-1) && (theIFS.lastAvoidBackward!=-1) && (rpi==(lastPoint+theIFS.lastAvoidBackward)%theIFS.numPts)) ||
            ((lastPoint !=-1) && (theIFS.lastAvoidForward !=-1) && ((rpi+theIFS.lastAvoidForward)%theIFS.numPts==lastPoint))) {
        rn = rEng();
        rpi = rn%theIFS.numPts;
      }
      lastPoint = rpi;
      z = (z+points[rpi])/theIFS.factor;
      if(n > theIFS.itrToss)
        theRamCanvas.drawPoint(z, aColor[rn%numCol]);
      double curMag = std::abs(z);
      if(maxMag < curMag)
        maxMag = curMag;
    }
    std::cout << "max mag: " << maxMag << std::endl;

    theRamCanvas.applyHomoPixTfrm(&mjr::color3c8b::tfrmStdPow, 1/5.0);
  
    std::ostringstream stringStream;
    stringStream << "chaos_game";
    stringStream << "," << theIFS.numPts;
    stringStream << "," << theIFS.lastAvoidForward;
    stringStream << "," << theIFS.lastAvoidBackward;
    stringStream << "," << theIFS.lastAvoidLast;
    stringStream << "," << theIFS.factor;
    stringStream << ".tiff";
    theRamCanvas.writeTIFFfile(stringStream.str());
  }

  return 0;
}
