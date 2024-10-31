// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      brownianDiffusion.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Read a TIFF image and simulate brownian diffusion.@EOL
 @keywords  dla fractal brownian motion brown
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
int main(int argc, char *argv[]) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  std::random_device rd;
  std::minstd_rand0 rEng(rd());
  mjr::ramCanvas3c8b theRamCanvas(7680/2, 4320/2, -2.2, 2.2, -2.2, 2.2);
  theRamCanvas.clrCanvas(mjr::ramCanvas3c8b::colorType(255, 0, 0));
  int MAXCOUNT = 524288; // Number of times to try and find a point

  int stenX[8] = {1, -1, 0,  0, 1,  1, -1, -1};
  int stenY[8] = {0,  0, 1, -1, 1, -1,  1, -1};


  if((argc < 3) || (argc > 4)) {
    std::cout << "ERROR: Useage: dlaBrownian inFile.tiff outFile_without_extension [ITERATIONS]" << std::endl;
  }

  if(theRamCanvas.readTIFFfile(argv[1])) {
    std::cout << "ERROR: Problem with file: " << argv[2] << std::endl;
    return 1;
  }

  if(argc > 3)
    MAXCOUNT = std::stoi(argv[3]);

  for(int tgtLumPct=1;tgtLumPct<=100;tgtLumPct+=10) {
    double tgtLum=tgtLumPct / 100.0;

    for(int numItr=1;numItr<MAXCOUNT;numItr++) {
      mjr::ramCanvas3c8b::coordIntType xC, yC;
      xC = static_cast<int>(rEng() % theRamCanvas.getNumPixX());
      yC = static_cast<int>(rEng() % theRamCanvas.getNumPixY());

      mjr::ramCanvas3c8b::colorType aColor = theRamCanvas.getPxColor(xC, yC);
      double lumC = aColor.luminanceRGB();

      if((lumC > 0) && (lumC < tgtLum)) {
        double maxLum = -1;
        int    maxDir = -1;
        int    lum0ct = 0;
        for(int curDir=0; curDir<8; curDir++) {
          mjr::ramCanvas3c8b::coordIntType xN, yN;
          xN = xC+stenX[curDir];
          yN = yC+stenY[curDir];
          if(xN>=0 && yN>=0 && xN<theRamCanvas.getNumPixX() && yN<theRamCanvas.getNumPixY()) {
            double lumN = theRamCanvas.getPxColor(xN, yN).luminanceRGB();
            if(lumN <= 0) {
              lum0ct++;
            } else {
              if((lumN > lumC) && (maxLum < lumN)) {
                maxLum  = lumN;
                maxDir  = curDir;
              }
            }
          }
        }

        // If sourounted by zeros, then random move
        if(lum0ct==8) {
          int curDir = rEng() % 8;
          mjr::ramCanvas3c8b::coordIntType xN, yN;
          xN = xC+stenX[curDir];
          yN = yC+stenY[curDir];
          if(xN>=0 && yN>=0 && xN<theRamCanvas.getNumPixX() && yN<theRamCanvas.getNumPixY()) {
            maxDir = curDir;
          }
        }

        if(maxDir > -1) {
          mjr::ramCanvas3c8b::coordIntType xN, yN;
          xN = xC+stenX[maxDir];
          yN = yC+stenY[maxDir];

          theRamCanvas.getPxColorRefNC(xN, yN).tfrmAdd(aColor);
          theRamCanvas.drawPoint(xC, yC, mjr::ramCanvas3c8b::colorType(0, 0, 0));
        }
      }
    }

    theRamCanvas.writeTIFFfile(argv[2] + mjr::math::str::fmt_int(tgtLumPct, 3, '0') + ".tiff");
    std::cout << "Write: " << tgtLumPct << std::endl;
  }

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;

  return 1;
}
/** @endcond */
