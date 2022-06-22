// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      color_lut_ramp_misc.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Demonstrate the cmpColorRamp (general color ramp) function
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvasRGB8b theRamCanvas(1024, 1024);
  mjr::colorRGB8b aColor(0,0,0);

//  mjr::ramCanvas3c8b::colorType corners[7] = { mjr::ramCanvas3c8b::colorType("red"),   mjr::ramCanvas3c8b::colorType("yellow"),
//                           mjr::ramCanvas3c8b::colorType("green"), mjr::ramCanvas3c8b::colorType("cyan"),
//                           mjr::ramCanvas3c8b::colorType("blue"),  mjr::ramCanvas3c8b::colorType("magenta"),
//                           mjr::ramCanvas3c8b::colorType("red")};
//
//  mjr::ramCanvas3c8b::colorType corners2[7] = { mjr::ramCanvas3c8b::colorType(mjr::ramCanvas3c8b::colorType::cornerColors::RED),   mjr::ramCanvas3c8b::colorType(mjr::ramCanvas3c8b::colorType::cornerColors::YELLOW),
//                            mjr::ramCanvas3c8b::colorType(mjr::ramCanvas3c8b::colorType::cornerColors::GREEN), mjr::ramCanvas3c8b::colorType(mjr::ramCanvas3c8b::colorType::cornerColors::CYAN),
//                            mjr::ramCanvas3c8b::colorType(mjr::ramCanvas3c8b::colorType::cornerColors::BLUE),  mjr::ramCanvas3c8b::colorType(mjr::ramCanvas3c8b::colorType::cornerColors::MAGENTA),
//                            mjr::ramCanvas3c8b::colorType(mjr::ramCanvas3c8b::colorType::cornerColors::RED)};
//
//  double anchors[7] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
//  for(int i=0; i<7; i++)
//    anchors[i] = anchors[i]/6.0;

  double anchors[8] = {390, 425, 445, 495, 540, 600, 685, 830};

  mjr::colorRGB8b corners[8];

  corners[0].setColorFromF(  4.735895e-04, -3.803366e-04,  6.188242e-03);
  corners[1].setColorFromF(  2.408992e-02, -3.213844e-02,  6.140333e-01);
  corners[2].setColorFromF( -1.389196e-03,  2.282020e-03,  1.000000e+00);
  corners[3].setColorFromF( -1.405614e-01,  5.221071e-01,  1.304521e-01);
  corners[4].setColorFromF(  1.692925e-01,  1.000000e+00, -8.184450e-03);
  corners[5].setColorFromF(  1.000000e+00,  2.463630e-01, -2.764747e-03);
  corners[6].setColorFromF(  2.693146e-02, -6.494247e-04,  7.366005e-06);
  corners[7].setColorFromF(  1.436555e-06, -2.633831e-09,  4.411618e-11);

  for(int x=0;x<theRamCanvas.get_numXpix();x++)
    for(int y=0;y<theRamCanvas.get_numYpix();y++)
      theRamCanvas.drawPoint(x, y, aColor.cmpColorRamp(x, 8, anchors, corners));

  theRamCanvas.writeTIFFfile("color_lut_ramp_misc.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
