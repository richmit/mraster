// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <random>                                                        /* C++ random numbers      C++11    */

int main(int argc, char *argv[]) {
  std::random_device rd;
  std::minstd_rand0 rEng(rd());
  auto timestamp_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  mjr::ramCanvas3c8b theRamCanvas(7680/2, 4320/2, -2.2, 2.2, -2.2, 2.2);
  theRamCanvas.clrCanvas(mjr::color3c8b(255, 0, 0));
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
      xC = rEng() % theRamCanvas.get_numXpix();
      yC = rEng() % theRamCanvas.get_numYpix();

      mjr::color3c8b aColor = theRamCanvas.getPxColor(xC, yC);
      double lumC = aColor.colorLuminance();

      if((lumC > 0) && (lumC < tgtLum)) {
        double maxLum = -1;
        int    maxDir = -1;
        int    lum0ct = 0;
        for(int curDir=0; curDir<8; curDir++) {
          mjr::ramCanvas3c8b::coordIntType xN, yN;
          xN = xC+stenX[curDir];
          yN = yC+stenY[curDir];
          if(xN>=0 && yN>=0 && xN<theRamCanvas.get_numXpix() && yN<theRamCanvas.get_numYpix()) {
            double lumN = theRamCanvas.getPxColor(xN, yN).colorLuminance();
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
          if(xN>=0 && yN>=0 && xN<theRamCanvas.get_numXpix() && yN<theRamCanvas.get_numYpix()) {
            maxDir = curDir;
          }
        }

        if(maxDir > -1) {
          mjr::ramCanvas3c8b::coordIntType xN, yN;
          xN = xC+stenX[maxDir];
          yN = yC+stenY[maxDir];

          theRamCanvas.getPxColorRefNC(xN, yN).tfrmAdd(aColor);
          theRamCanvas.drawPoint(xC, yC, mjr::color3c8b(0, 0, 0));
        }
      }
    }

    std::ostringstream stringStream;
    stringStream << argv[2] << std::setfill('0') << std::setw(3) << tgtLumPct << ".tiff";
    theRamCanvas.writeTIFFfile(stringStream.str());
    std::cout << "Write: " << stringStream.str() << std::endl;
  }


  return 1;

  std::cout << "Runtime " << static_cast<double>(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) - timestamp_time_t)/(60.0) << " min" << std::endl;
}
