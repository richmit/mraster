// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      simone_attractor_search.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Find parameters for simone attractor that light up lots of pixels.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/sic/index.html
 @copyright
  @parblock
  Copyright (c) 1988-2015,2025, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int BSIZ = 2048;

  std::random_device rd;
  std::mt19937 rEng(rd());
  std::uniform_real_distribution<double> uniform_dist_double(-2.0, 2.0);
  std::uniform_int_distribution<int>     uniform_dist_int(3, 7);

  mjr::ramCanvas1c16b theRamCanvas(BSIZ, BSIZ, -1, 1, -1, 1); // Just used for coordinate conversion. ;)

  uint64_t maxCnt = 0;
  for(int j=0; j<100000; j++) {
    std::map<uint64_t, uint64_t> ptcnt;
    double a      = uniform_dist_double(rEng);
    double b      = uniform_dist_double(rEng);
    double xn     = 0;
    double yn     = 0;
    std::complex<double> z(0.01,0.01);
    for(uint64_t i=0;i<1000;i++) {
      double tmp = std::sin(xn*xn-yn*yn+a);
      yn = std::cos(2*xn*yn+b);
      xn = tmp;
      ptcnt[((uint64_t)theRamCanvas.real2intX(xn))<<32 | ((uint64_t)theRamCanvas.real2intY(yn))] = 1;
    }
    if(ptcnt.size() >= maxCnt) {
      maxCnt = ptcnt.size();
      std::cout << " { " << a << ", " <<  b << ", 0.0, 0.0, 10000000},  // " << maxCnt << std::endl;
    }
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */
