// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      phoenixD.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw Phoenix Julia set fractals with distance estimator.@EOL
 @std       C++20
 @see       Writeup with images: https://www.mitchr.me/SS/phoenix/
 @see       MRaster repository: https://github.com/richmit/mraster/
 @see       Doxygen documentation: https://www.mitchr.me/SS/mraster/doc-examples/autodocs/html/
 @see       Related example: https://github.com/richmit/mraster/blob/master/examples/phoenix.cpp
 @copyright
  @parblock
  Copyright (c) 2024, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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
#include "MRMathSTR.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b::colorType ct;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<std::array<double, 9>> params {
  /*       cr,       ci,       pr,       pi,     k, x-min, x-max, y-min, y-max */
  {  0.566700,  0.00000, -0.50000,  0.00000, 100.0, -1.35,  1.35, -1.35,  1.35}, //  0 
  {  0.544992,  0.00000, -0.47000,  0.00000, 100.0, -1.35,  1.35, -1.35,  1.35}, //  1
  {  0.269000,  0.00000,  0.00000,  0.01000, 100.0, -1.10,  1.10, -1.00,  1.00}, //  2
  { -0.400000,  0.10000,  0.29550,  0.00000, 100.0, -1.10,  1.10, -1.50,  1.50}, //  3
  {  0.400000,  0.00000, -0.25000,  0.00000, 100.0, -1.30,  1.20, -1.00,  1.00}, //  4
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    WIDTH  = 1920*1;
  const int    HEIGHT = 1920*1;
  const int    NUMITR = 500;
  const double MAXZ   = 4.0;

# pragma omp parallel for schedule(static,1)
  for(decltype(params.size()) j=0; j<params.size(); ++j) {
    const std::complex<double> c(params[j][0], params[j][1]);
    const std::complex<double> p(params[j][2], params[j][3]);
    mjr::ramCanvas3c8b theRamCanvas(WIDTH, HEIGHT, params[j][5], params[j][6], params[j][7], params[j][8]);
    for(int y=0;y<theRamCanvas.getNumPixY();y++) {
      for(int x=0;x<theRamCanvas.getNumPixX();x++) {
        std::complex<double> d1(1.0, 0.0);
        std::complex<double> d2(0.0, 0.0);

        std::complex<double> z1(theRamCanvas.int2realY(y), theRamCanvas.int2realX(x));
        std::complex<double> z2(0.0, 0.0);
        int count = 0;
        while((std::norm(z1)<MAXZ) && (count<=NUMITR)) {
          std::complex<double> z = z1*z1+c+p*z2;
          std::complex<double> d = 2.0*d1*z1+p*d2;
          z2 = z1;
          z1 = z;
          d2 = d1;
          d1 = d;
          count++;
        }
        if(count < NUMITR)
          theRamCanvas.drawPoint(x, y, ct::csCCfractal0RYBCW::c(static_cast<ct::csIntType>(std::log(std::abs(d1)+1)*params[j][4])));
      }
    }
    theRamCanvas.writeTIFFfile("phoenixD_" + mjr::math::str::fmt_int(j, 2, '0') + ".tiff");
    std::cout << "ITER(" << j <<  "): " << "DONE " << std::endl;
  }

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
