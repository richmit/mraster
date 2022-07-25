// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      test_interp_scale.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Quick test program for getPxColorInterpBLin.@EOL
 @copyright
  @parblock
  Copyright (c) 1988-2015, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may be used to edorse or promote products derived from this software
     without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
  @endparblock
********************************************************************************************************************************************************.H.E.**/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b aRamCanvas;
  mjr::ramCanvas3c8b::colorType aColor("red");
  int rRet;

  if (argc < 2) {
    fprintf(stderr, "ERROR argument required!\n");
    exit(1);
  }

  if((rRet=aRamCanvas.readTIFFfile(argv[1]))) {
    fprintf(stderr, "ERROR(%d) reading file %s\n", rRet, argv[1]);
    exit(1);
  }

  // aRamCanvas.writeTGAfile("test_interp_scale_orig.tga");
  // aRamCanvas.writeTGAfile("test_interp_scale_orig.tiff");

  mjr::ramCanvas3c8b::coordIntType width  = aRamCanvas.get_numXpix();
  mjr::ramCanvas3c8b::coordIntType height = aRamCanvas.get_numYpix();
  double magr = 7.0;
  int magi = 7.0;

  mjr::ramCanvas3c8b bRamCanvas(width * magi, height * magi);

  for(mjr::ramCanvas3c8b::coordIntType x = 0; x < bRamCanvas.get_numXpix(); x++) {
    for(mjr::ramCanvas3c8b::coordIntType y = 0; y < bRamCanvas.get_numYpix(); y++) {
      aColor = aRamCanvas.getPxColorInterpTrunc(x/magi, y/magi);
      bRamCanvas.drawPointNC(x, y, aColor);
    }
  }
  bRamCanvas.writeTIFFfile("test_interp_scale_trunc.tiff");

  for(mjr::ramCanvas3c8b::coordIntType x = 0; x < bRamCanvas.get_numXpix(); x++) {
    for(mjr::ramCanvas3c8b::coordIntType y = 0; y < bRamCanvas.get_numYpix(); y++) {
      aColor = aRamCanvas.getPxColorInterpNear(x/magi, y/magi);
      bRamCanvas.drawPointNC(x, y, aColor);
    }
  }
  bRamCanvas.writeTIFFfile("test_interp_scale_near.tiff");

  for(mjr::ramCanvas3c8b::coordIntType x = 0; x < bRamCanvas.get_numXpix(); x++) {
    for(mjr::ramCanvas3c8b::coordIntType y = 0; y < bRamCanvas.get_numYpix(); y++) {
      aColor = aRamCanvas.getPxColorInterpBLin(x/magr, y/magr);
      bRamCanvas.drawPointNC(x, y, aColor);
    }
  }
  bRamCanvas.writeTIFFfile("test_interp_scale_bil.tiff");

  for(mjr::ramCanvas3c8b::coordIntType x = 0; x < bRamCanvas.get_numXpix(); x++) {
    for(mjr::ramCanvas3c8b::coordIntType y = 0; y < bRamCanvas.get_numYpix(); y++) {
      aColor = aRamCanvas.getPxColorInterpAvg4(x/magr, y/magr);
      bRamCanvas.drawPointNC(x, y, aColor);
    }
  }
  bRamCanvas.writeTIFFfile("test_interp_scale_avg4.tiff");

  for(mjr::ramCanvas3c8b::coordIntType x = 0; x < bRamCanvas.get_numXpix(); x++) {
    for(mjr::ramCanvas3c8b::coordIntType y = 0; y < bRamCanvas.get_numYpix(); y++) {
      aColor = aRamCanvas.getPxColorInterpAvg9(x/magr, y/magr);
      bRamCanvas.drawPointNC(x, y, aColor);
    }
  }
  bRamCanvas.writeTIFFfile("test_interp_scale_avg9.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;

  return 0;
}
