// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      dlaDrift.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Read a TIFF image and simulate diffusion limited aggregation with drift of blue pixels.@EOL
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
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <random>                                                        /* C++ random numbers      C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  int numHits = 1, numHitsRel = 0, numClipRel = 0, numCloseRel = 0, linesPrinted = 0;
  std::random_device rd;
  std::minstd_rand0 rEng(rd());
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b theRamCanvas(7680/2, 4320/2, -2.2, 2.2, -2.2, 2.2);
  theRamCanvas.clrCanvas(mjr::ramCanvas3c8b::colorType(255, 0, 0));
  int MAXNUMPT = 524288; // Number of random points to pick
  int MAXCOUNT = 524288; // Number of times to move each random point

  if((argc < 3) || (argc > 5)) {
    std::cout << "ERROR: Useage: dlaBrownian inFile.tiff outFile.tiff [ITERATIONS [POINTS]]" << std::endl;
  }

  if(theRamCanvas.readTIFFfile(argv[1])) {
    std::cout << "ERROR: Problem with file: " << argv[2] << std::endl;
    return 1;
  }

  if(argc > 3)
    MAXCOUNT = std::stoi(argv[3]);
  if(argc > 4)
    MAXNUMPT = std::stoi(argv[4]);

  for(int numPt=1;numPt<MAXNUMPT;numPt++) {
    // Get a random point not near the tree
    mjr::ramCanvas3c8b::coordIntType x, y;
    x = rEng() % theRamCanvas.getNumPixX();
    y = rEng() % theRamCanvas.getNumPixY();
    if(theRamCanvas.getPxColor(x+0, y+0).getC2()) {
      numCloseRel++;
    } else {
      // move arround till we go out of range, or hit the tree
      for(int count=0;count<MAXCOUNT;count++) {
        int rn = rEng() % 5;
        switch (rn) {
          case 0:
            x++; break;
          case 1:
            x--; break;
          case 2:
            y++; break;
          case 3:
            x++; y++; break;
          case 4:
            x--; y++; break;
        }
        if(x<1 || y<1 || x>(theRamCanvas.getNumPixX()-2) || y>(theRamCanvas.getNumPixY()-2)) {
          numClipRel++;
          break;
        }
        if(theRamCanvas.getPxColor(x+1, y+0).getC2() ||
           theRamCanvas.getPxColor(x-1, y+0).getC2() ||
           theRamCanvas.getPxColor(x+0, y+1).getC2() ||
           theRamCanvas.getPxColor(x+0, y-1).getC2() ||
           theRamCanvas.getPxColor(x+1, y+1).getC2() ||
           theRamCanvas.getPxColor(x+1, y-1).getC2() ||
           theRamCanvas.getPxColor(x-1, y+1).getC2() ||
           theRamCanvas.getPxColor(x-1, y-1).getC2()
          ) {
          theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(0, 0, 255));
          numHits++;
          numHitsRel++;
          break;
        }
      }
    }
    if((numPt%1024)==0) {
      if(linesPrinted == 0) {
        std::cout << std::setw(10) << "HITS/1k" << " " << std::setw(10) << "CLIPS/1k" << " "  << std::setw(10) << "CLOSE/1k";
        std::cout << "       " << std::setw(10) << "HITS" << " @ " << std::setw(10) << "POINTS" << std::endl;
      }
      linesPrinted++;
      if(linesPrinted > 20)
        linesPrinted = 0;
      std::cout << std::setw(10) << numHitsRel << " " << std::setw(10) << numClipRel << " " << std::setw(10) << numCloseRel;
      std::cout << "       " << std::setw(10) << numHits << " @ " << std::setw(10) << numPt << std::endl;
      numCloseRel = 0;
      numHitsRel  = 0;
      numClipRel  = 0;
    }
  }
  if(theRamCanvas.writeTIFFfile(argv[2])) {
    std::cout << "ERROR: Problem with file: " << argv[2] << std::endl;
    return 1;
  }

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
