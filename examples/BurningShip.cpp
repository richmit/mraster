// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      BurningShip.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-09-08
 @brief     Burning Ship Fractal.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/BurningShip/index.html
 @copyright 
  @parblock
  Copyright (c) 2022, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.

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
typedef mjr::color3c8b::csCC_tpl<mjr::color3c8b::cornerColorEnum::BLUE, 
                                 mjr::color3c8b::cornerColorEnum::RED, 
                                 mjr::color3c8b::cornerColorEnum::YELLOW, 
                                 mjr::color3c8b::cornerColorEnum::WHITE>  csCCbs;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int NUMITR = 1024; 
  const int MAXMAG = 15; 
  const int IMGSIZ = 7680/4;
  //mjr::ramCanvas3c8b escRamCanvas(IMGSIZ, IMGSIZ, -1.5, 2.7, -1.25, 2.49);                 // Entire fractal
  //mjr::ramCanvas3c8b escRamCanvas(IMGSIZ, IMGSIZ, 1.6, 1.9, -0.089, 0.2);                  // The horizon zoom
  mjr::ramCanvas3c8b escRamCanvas(IMGSIZ, IMGSIZ, 1.715, 1.795, -0.022, 0.086);              // The classic zoom
  //mjr::ramCanvas3c8b escRamCanvas(IMGSIZ, IMGSIZ, 1.802, 1.80287, -0.002, 0.002);          // Columns to heaven
  //mjr::ramCanvas3c8b escRamCanvas(IMGSIZ, IMGSIZ, -0.3743, -0.3735, -0.0876, -0.0866);     // Deep zoom.  BATS!

  for(int y=0;y<escRamCanvas.getNumPixY();y++) {
    for(int x=0;x<escRamCanvas.getNumPixX();x++) {
      double cx = escRamCanvas.int2realX(x), cy = escRamCanvas.int2realY(y);
      double zx = 0.0, zy = 0.0;
      double t;
      int count = 0;
      while(((zx*zx+zy*zy)<MAXMAG) && (count<=NUMITR)) {
        count++;
        t  = zx*zx - zy*zy     - cx;
        zy = std::abs(2*zx*zy) - cy;
        zx = t;
      }
      if(count < NUMITR) 
        escRamCanvas.drawPoint(x, y, csCCbs::c(static_cast<mjr::ramCanvas3c8b::csIntType>(count*10)));
    }
  }
  // Escape Time Coloring
  escRamCanvas.writeTIFFfile("BurningShip.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
