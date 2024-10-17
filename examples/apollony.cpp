// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      apollony.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw the Apollony Gasket via an ifs.@EOL
 @keywords  apollony fractal gasket
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

  Pick an initial @f$z\in\mathbb{C}@f$, say @f$\frac{1}{10}+\frac{2}{10}i@f$.  Then iterate.  For each iteration let the next $z$ value be @f$f_n(z)@f$ where
  @f$n@f$ is selected at random.  If we plot the @f$z@f$ points, we obtain the classical Apollony Gasket.

  @f[\begin{array}{rcl}
    f_1(z) &=& f(z)                         \\
    f_2(z) &=& \frac{-1 + i\sqrt{3}}{2f(z)} \\
    f_3(z) &=& \frac{-1 - i\sqrt{3}}{2f(z)} \\
  \end{array}@f]

  Where

  @f[ f(z) = \frac{3}{1-z+\sqrt{3}} - \frac{1+\sqrt{3}}{2+\sqrt{3}} @f]
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  std::cout << "apollony start" << std::endl;
  const int   CSIZE = 1080*2;                            // Quad HD
  const int ITRTOSS = static_cast<int>(std::pow(2, 10)); // Throw away first iterations
  const long NUMITR = static_cast<int>(std::pow(2, 29)); // Needs to be big

  mjr::ramCanvas3c8b theRamCanvas(CSIZE, CSIZE, -4.0, 4.0, -4.0, 4.0);
  theRamCanvas.setDrawMode(mjr::ramCanvas3c8b::drawModeType::ADDCLAMP);

#if SUPPORT_DRAWING_MODE
  mjr::ramCanvas3c8b::colorType aColor[] = { mjr::ramCanvas3c8b::colorType(1, 0, 0),
                                             mjr::ramCanvas3c8b::colorType(0, 1, 0), 
                                             mjr::ramCanvas3c8b::colorType(0, 0, 1) };
#else
  mjr::ramCanvas3c8b::colorType aColor[] = { mjr::ramCanvas3c8b::colorType(255, 0, 0), 
                                             mjr::ramCanvas3c8b::colorType(0, 255, 0), 
                                             mjr::ramCanvas3c8b::colorType(0, 0, 255) };
#endif

  std::random_device rd;
  std::minstd_rand0 rEng(rd()); // Fast is better than high quality for this application.

  const double               s = 1.73205080757;
  const std::complex<double> si(0, s);
  const std::complex<double> c1 = (1+s)/(2+s);
  const std::complex<double> c2 =  0.5*(si-1.0);
  const std::complex<double> c3 = -0.5*(si+1.0);
  const std::complex<double> c4 = 1.0+s;
  const std::complex<double> c5(3.0, 0.0);
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
  std::cout << "apollony dump" << std::endl;
  theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmStdPow, 1/5.0);
  theRamCanvas.writeTIFFfile("apollony.tiff");
  std::cout << "apollony finish" << std::endl;
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */
