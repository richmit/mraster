// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      sierpinskiTriangle.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     This little program draws a S. Gasket using an iterative, random algorithm.@EOL
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

#include<stdlib.h>
#include "ramCanvas.hpp"

using namespace mjr;

typedef float PointType[2];

int main() {
  PointType cpt = {0.0, 0.0};
  color4c8b aColor[] = { color4c8b(255, 0, 0), color4c8b(0, 255, 0), color4c8b(0, 0, 255) };
  PointType pts[] = {{0,0.8}, {-0.8,-0.8}, {0.8,-0.8}};
  int NumPts = 3;
  
  ramCanvas4c8b theRamCanvas = ramCanvas4c8b(2048, 2048, -1, 1, -1, 1);
  for(int n=0;n<10000000;n++) {
    int ip = rand()%NumPts;
    cpt[0] = (pts[ip][0] + cpt[0]) / 2.0;
    cpt[1] = (pts[ip][1] + cpt[1]) / 2.0;
    if(n > 100000)
      theRamCanvas.drawPoint(cpt[0], cpt[1], aColor[ip]);
  }
  theRamCanvas.writeTGAfile("sierpinskiTriangle.tga");

  return 0;
}
