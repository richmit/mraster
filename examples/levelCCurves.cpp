// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      levelCCurves.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     draw graphics tga library color 24-bit@EOL
 @keywords  
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
#include <math.h>

using namespace mjr;

float f(float x, float y);  
void drawLevelCurves(int numBand, float bandWidth, float zMin, float zMax, float minRealX, float maxRealX, float minRealY, float maxRealY, const char *file);

int main(void) {
  drawLevelCurves(10, 0.0, 0, 0, -20, 20, -20, 20, "levelCCurves_l.tga");
  drawLevelCurves( 0, 0.0, 0, 0, -20, 20, -20, 20, "levelCCurves_c.tga");
}

float f(float x, float y) {
  return sin(x)+cos(y)+sqrt(x*x+y*y)*.05;
}

void drawLevelCurves(int numBand, float bandWidth, float zMin, float zMax, float minRealX, float maxRealX, float minRealY, float maxRealY, const char *file) {
  int x, y, clr, foundBand;
  float fxy, bandGap, band, minDist, minBand;

  ramCanvas4c8b theRamCanvas = ramCanvas4c8b(1024, 1024, minRealX, maxRealX, minRealY, maxRealY);

  // Compute zMin and zMax if we need to.
  if( (zMax == 0) && (zMin == 0) ) {
    fprintf(stderr, "Compute zMax and zMin\n");
    zMax = zMin = f(theRamCanvas.int2realX(0), theRamCanvas.int2realY(0));
    for(y=0;y<theRamCanvas.get_numYpix();y++)  {
      for(x=0;x<theRamCanvas.get_numXpix();x++) {
        fxy = f(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));
        if(fxy > zMax) zMax=fxy;
        if(fxy < zMin) zMin=fxy;
      }
    }
  }

  bandGap = 1.0*(zMax-zMin)/numBand;
  fprintf(stderr, "Compute curves\n");
  for(y=0;y<theRamCanvas.get_numYpix();y++)  {
    for(x=0;x<theRamCanvas.get_numXpix();x++) {
      fxy = f(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));
      if(fxy < zMin) {
        theRamCanvas.setDfltColor(color4c8b(255, 0, 0));
      } else {
        if(fxy > zMax) {
        theRamCanvas.setDfltColor(color4c8b(0, 255, 0));
        } else {
          if(numBand == 0) {
            clr = (int)((zMax-fxy)/(zMax-zMin)*250);
            theRamCanvas.setDfltColor(color4c8b().cmpGrey(clr));
          } else {
            if(bandWidth == 0) {
              theRamCanvas.setDfltColor(color4c8b(0, 0, 255));
              foundBand=0;
              minDist = (zMax-zMin+1);
              minBand = 0.0;
              for(band=zMax; band>zMin; band=band-bandGap) {
                if(fabs(band-fxy) < minDist) {
                  minDist = fabs(band-fxy);
                  minBand = band;
                  foundBand = 1;
                }
              }
              if(foundBand) {
                clr = (int)((zMax-minBand)/(zMax-zMin)*250);
                theRamCanvas.setDfltColor(color4c8b().cmpGrey(clr));
              }
            } else {
              theRamCanvas.setDfltColor(color4c8b(0, 0, 255));
              foundBand=0;
              for(band=zMax; band>zMin; band=band-bandGap) {
                if(fabs(band-fxy) < bandWidth) {
                  clr = (int)((zMax-fxy)/(zMax-zMin)*250);
                  theRamCanvas.setDfltColor(color4c8b(255, 255, 255));
                  foundBand = 1;
                  break;
                }
              }
            }
          }
        }
      }
      theRamCanvas.drawPoint(x, y);
    }
  }

  theRamCanvas.writeTGAfile(file);
}


