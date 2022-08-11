// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      geomTfrm_LensDistortion.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Read an image, correct it for radial lens discortion, and write out the corrected image.@EOL
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
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

// mjr::point2d<double> funny(double x, double y) {
//   return mjr::point2d<double>(x+100*std::sin(y/100), y);
// }


// mjr::point2d<double> funny(double x, double y) {
//   double d = 25; //std::hypot(x, y) / 2056;
//   return mjr::point2d<double>(std::cos(d)*x+std::sin(d)*y, -std::sin(d)*x+std::cos(d)*y);
// }

// mjr::point2d<double> funny(double x, double y) {
// x = x - 2000;
// y = y - 1500;
//   double d = std::hypot(x, y) / 1056;
//   return mjr::point2d<double>(std::cos(d)*x+std::sin(d)*y+2000, -std::sin(d)*x+std::cos(d)*y+1500);
// }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b dRamCanvas;

  if (argc < 2) {
    fprintf(stderr, "ERROR argument required!\n");
    exit(1);
  }

  int rRet;
  if((rRet=dRamCanvas.readTIFFfile(argv[1]))) {
    fprintf(stderr, "ERROR(%d) reading file %s\n", rRet, argv[1]);
    exit(1);
  }

  double A       =  0.0000;
  double B       = -0.0160;
  double C       =  0.0000;
  double D       = 1.0 - A - B - C;

  double Xo      =  0.0;
  double Yo      =  0.0;
  std::vector<double> poly {A, B, C, D};
std::cout << poly[1] << std::endl;

  mjr::ramCanvas3c8b uRamCanvas = dRamCanvas.geomTfrmRevRPoly(poly, Xo, Yo);

   // mjr::ramCanvas3c8b uRamCanvas = dRamCanvas.genGeomTfrmArb(funny);

  // ramCanvasTpl<colorT, intCrdT, fltCrdT>::genGeomTfrmArb(pointFltType (*f)(double, double)) {
  //   ramCanvasTpl<colorT, intCrdT, fltCrdT> newRamCanvas(numXpix, numYpix);

  uRamCanvas.writeTIFFfile("geomTfrm_LensDistortion.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;

  return 0;
}
/** @endcond */
