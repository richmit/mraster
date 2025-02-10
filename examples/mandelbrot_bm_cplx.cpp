// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_bm_cplx.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark drawing a mandelbrot set using the C++ complex type.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/mandelbrot/index.html
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

  Basic benchmark.  Uses complex numbers.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathIVL.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef std::complex<mjr::ramCanvas3c8b::coordFltType> cplx;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  int count;
  const int NUMITR = 1024;
  cplx c, z, zero(0.0, 0.0);
  mjr::ramCanvas3c8b theRamCanvas(7680, 7680, -2.2, 0.8, -1.5, 1.5);

  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      for(c=cplx(theRamCanvas.int2realX(x),theRamCanvas.int2realY(y)),z=zero,count=0; 
          (std::norm(z)<4)&&(count<=NUMITR); 
          count++,z=z*z+c)
        ;
      if(count < NUMITR)
        theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType::csCColdeFireRamp::c(mjr::math::ivl::wrapCC(static_cast<mjr::ramCanvas3c8b::csIntType>(count*20), 767)));
    }
  }
  theRamCanvas.writeTIFFfile("mandelbrot_bm_cplx.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
