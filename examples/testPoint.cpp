// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      testPoint.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark program for pixel draw rates with ramCanvas.@EOL
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
 @filedetails

   One of the points of the point classes is to provide an easy way to specify points using existing data structures.

********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  const int BSIZE = 20;

  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvasRGB8b theRamCanvas(BSIZE, BSIZE, 0, BSIZE-1, 0, BSIZE-1);
  theRamCanvas.setRealAxOrientationY(mjr::ramCanvasRGB8b::realAxisOrientation::INVERTED);
  mjr::colorRGB8b aColor(mjr::colorRGB8b::cornerColorEnum::RED);
  mjr::colorRGB8b bColor(mjr::colorRGB8b::cornerColorEnum::BLUE);
  mjr::colorRGB8b cColor(mjr::colorRGB8b::cornerColorEnum::MAGENTA);
  mjr::colorRGB8b dColor(mjr::colorRGB8b::cornerColorEnum::CYAN);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType({2, 2}),                      aColor);  // Initializeer list
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(4, 2),                        bColor);  // two arg
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(std::tuple<int,int>(6, 2)),   aColor);  // tuple<int,int>
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(std::tuple<int,short>(8, 2)), bColor);  // tuple<int,short>
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(std::complex<int>(10, 2)),    aColor);  // complex<int>
#ifndef __clang__
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(std::complex<short>(12, 2)),  bColor);  // complex<short>
#endif
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(std::vector<int>({14, 2})),   aColor);  // vector<int)
  int aArI[2] = {16, 2};
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(aArI),                        bColor);  // array of int
  int aArS[2] = {18, 2};
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(aArS),                        aColor);  // array of short

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  theRamCanvas.drawPoint(std::complex<int>(2, 4),     bColor);  // complex<int>    -- complex<short>   no work
  theRamCanvas.drawPoint(std::tuple<int,int>(4, 4),   aColor);  // tuple<int,int>  -- tuple<int,short> no work
  theRamCanvas.drawPoint(std::vector<int>({6, 4}),    bColor);  // vector<int>

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType({2, 2}),                       cColor);  // Initializeer list
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(4, 2),                         dColor);  // two arg
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(std::tuple<int,int>(6, 2)),    cColor);  // tuple<int,int>
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(std::tuple<int,short>(8, 2)),  dColor);  // tuple<int,short>
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(std::complex<double>(10, 2)),   cColor);  // complex<double>
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(std::complex<double>(12, 2)),  dColor);  // complex<double>
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(std::vector<double>({14, 2})), cColor);  // vector<double>
  double aArD[2] = {16, 2};
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(aArD),                         dColor);  // array of double

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  theRamCanvas.drawPoint(std::complex<double>(2, 4),       dColor);  // complex<double>   -- complex<double> no work
  theRamCanvas.drawPoint(std::tuple<double,double>(4, 4),  cColor);  // tuple<double,double>  -- tuple<double,double> no work
  theRamCanvas.drawPoint(std::vector<double>({6, 4}),      dColor);  // vector<double>

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  theRamCanvas.scaleUpProximal(10);
  theRamCanvas.writeTIFFfile("testPoint.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
