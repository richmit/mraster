// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      apomorph.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Morph a IFS from an Apollony Gasket to a cloud.@EOL
 @keywords  mistake fractal
 @std       C++20
 @see       https://www.mitchr.me/SS/AGasket/index.html
 @copyright
  @parblock
  Copyright (c) 1988-2015,2017, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

  This code started as a programming error.  I was trying to generate an Apollony Gasket via an IFS, but had a cut-n-past error -- a 1 where I should have had
  a zero.  The result was something very unlike an Apollony Gasket. So I was curious what the results would be if the parameter was swept from 0 to 1.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathSTR.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  std::cout << "apomorph start" << std::endl;
  const int   CSIZE = 2160;      // Quad HD
  const int ITRTOSS = 1000;      // Throw away first iterations
  const long NUMITR = 400000000; // Needs to be big

  mjr::ramCanvas3c8b theRamCanvas(CSIZE, CSIZE, -4.0, 4.0, -4.0, 4.0);
  theRamCanvas.setDrawMode(mjr::ramCanvas3c8b::drawModeType::ADDCLAMP);

  mjr::ramCanvas3c8b::colorType aColor[] = { mjr::ramCanvas3c8b::colorType(1, 0, 0), mjr::ramCanvas3c8b::colorType(0, 1, 0), mjr::ramCanvas3c8b::colorType(0, 0, 1) };

  std::random_device rd;
  std::minstd_rand0 rEng(rd()); // Fast is better than high quality for this application.

  const double s = 1.73205080757;
//  const std::complex<double> i(0.0, 1.0);
  const std::complex<double> si(0.0, s);
  const std::complex<double> c1 = (1.0+s)/(2.0+s);
  const std::complex<double> c2 =  0.5*(si-1.0);
  const std::complex<double> c3 = -0.5*(si+1.0);
  const std::complex<double> c4 = 1.0+s;
  for(int frame=1; frame<401; frame++) {
    theRamCanvas.clrCanvasToBlack();
    std::complex<double> c5(3.0, (frame-1)*0.0025);
    std::cout << "apomorph frame: " << frame << "  " << (frame-1)*0.0025 << std::endl;
    std::complex<double> z(0.1, 0.2);
    for (long n=0;n<NUMITR;n++) {
      std::complex<double> zNxt;
      if ((n % (NUMITR/100)) == 0) {
        if ((n % (NUMITR/10)) == 0)
          std::cout << "|" << std::flush;
        else
          std::cout << "." << std::flush;
      }
      std::complex<double> f = c5/(c4-z)-c1;
      std::minstd_rand0::result_type rn = rEng()%3;
      switch (rn) {
      case 0:
        zNxt = f;    break;
      case 1:
        zNxt = c2/f; break;
      case 2:
        zNxt = c3/f; break;
      }
      z = zNxt;
      if (n > ITRTOSS)
        theRamCanvas.drawPoint(z, aColor[rn]);
    }
    std::cout << "|" << std::endl;
    std::cout << "apomorph dump" << std::endl;
    theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmStdPow, 1/5.0);

    theRamCanvas.writeTIFFfile("apomorph_" + mjr::math::str::fmt_int(frame, 3, '0') + ".tiff");
    std::cout << "apomorph finish" << std::endl;
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */
