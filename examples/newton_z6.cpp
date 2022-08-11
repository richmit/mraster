// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      newton_z6.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Newton Fractical for \f$z^6\f$.@EOL
 @std       C++20
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
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  int         MaxCount = 155;
  int         MultCol  = 25;
  const double Tol      = .0001;
  std::complex<double> r1( 1.0,  0);
  std::complex<double> r2(-0.5,  sin(2*std::numbers::pi/3));
  std::complex<double> r3(-0.5, -sin(2*std::numbers::pi/3));
  std::complex<double> r4(-1.0,  0);
  std::complex<double> r5( 0.5,  sin(2*std::numbers::pi/3));
  std::complex<double> r6( 0.5, -sin(2*std::numbers::pi/3));

  mjr::ramCanvas3c8b theRamCanvas(4096, 4096, -1.20, 1.20, -1.20, 1.20);

  for(int y=0;y<theRamCanvas.get_numYpix();y++) {
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      std::complex<double> z(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));
      int  count = 0;
      while((count < MaxCount) &&
            (abs(z-r1) >= Tol) && (abs(z-r2) >= Tol) && (abs(z-r3) >= Tol) &&
            (abs(z-r4) >= Tol) && (abs(z-r5) >= Tol) && (abs(z-r6) >= Tol)) {
        if(abs(z) > 0) {
          std::complex<double> tmp = pow(z, 5);
          z = z-(tmp*z-1.0)/(6.0*tmp);
        }
        count++;
      }
      mjr::ramCanvas3c8b::colorChanType cCol = static_cast<mjr::ramCanvas3c8b::colorChanType>(255-count*MultCol);

      if(abs(z-r1) <= Tol)
        theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(cCol, 0,                       0));
      if(abs(z-r2) <= Tol)
        theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(0,                       cCol, 0));
      if(abs(z-r3) <= Tol)
        theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(0,                       0,                       cCol));
      if(abs(z-r4) <= Tol)
        theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(cCol, cCol, 0));
      if(abs(z-r5) <= Tol)
        theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(0,                       cCol, cCol));
      if(abs(z-r6) <= Tol)
        theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(cCol, 0,                       cCol));
    }
  }
  /* The biggest reason homogeneous transforms are in the library is to support color scale correction.  */
  theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmLinearGreyLevelScale, 255.0 / 155, 0.0);
  theRamCanvas.autoHistStrech();
  theRamCanvas.writeTIFFfile("newton_z6.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
