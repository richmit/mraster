// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      sic_search.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Find parameters for SIC fractals that light up lots of pixels.@EOL
 @keywords  
 @std       C++11
 @see       sic.cpp
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

#include "ramCanvas.hpp"

#include <map>                                                           /* STL map                 C++11    */
#include <random>                                                        /* C++ random numbers      C++11    */

int main(void) {
  const int BSIZ = 2048;

  std::random_device rd;
  std::mt19937 rEng(rd());
  std::uniform_real_distribution<double> uniform_dist_float(-2.0, 2.0);
  std::uniform_int_distribution<int>     uniform_dist_int(3, 7);

  mjr::ramCanvas1c16b theRamCanvas(BSIZ, BSIZ, -2, 2, -2, 2); // Just used for coordinate conversion. ;)

  uint64_t maxCnt = 0;
  for(int j=0; j<100000; j++) {
    std::map<uint64_t, uint64_t> ptcnt;
    float lambda = uniform_dist_float(rEng);
    float alpha  = uniform_dist_float(rEng);
    float beta   = uniform_dist_float(rEng);
    float gamma  = uniform_dist_float(rEng);
    float w      = uniform_dist_float(rEng);
    int n        = uniform_dist_int(rEng);
    std::complex<float> z(.01,.01);
    for(uint64_t i=0;i<1000;i++) { 
      z = (lambda + alpha*z*std::conj(z)+beta*std::pow(z, n).real() + w*std::complex<float>(0,1))*z+gamma*std::pow(std::conj(z), n-1);
      ptcnt[((uint64_t)theRamCanvas.real2intX(z.real()))<<32 | ((uint64_t)theRamCanvas.real2intY(z.imag()))] = 1;
    }
    if(ptcnt.size() > maxCnt) {
      maxCnt = ptcnt.size();
      std::cout << j << " " << maxCnt << " " << lambda << "," <<  alpha << "," <<  beta << "," <<  gamma << "," <<  w << "," << n << std::endl;
    }
  }
  return 0;
}
