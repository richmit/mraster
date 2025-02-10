// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      demo_corners.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Demonstrate the ramCanvas corners API.@EOL
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
 @filedetails

  This code demonstrates one way to use an SDF function to color pixels using the "corners" API in ramCanvas.  Note that the methodology show is inefficient
  because it evaluates most coordinates four times, but the point here is to demonstrate the API...  It also demonstrates the mjr::math::esgn library which is
  part of MRMathCPP (https://github.com/richmit/MRMathCPP/).

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathESGN.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
double f(double x, double y);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();

  mjr::ramCanvas3c8b theRamCanvas(7680/2, 4320/2, -10.0, 10.0, -6.0, 6.0);
  //mjr::ramCanvas3c8b theRamCanvas(7680/2, 4320/2, -5.0, 5.0, -3.0, 3.0);

  // Run across all the pixels, and paint them according to the height of f.
  for(int yi=0;yi<theRamCanvas.getNumPixY();yi++) {
    for(int xi=0;xi<theRamCanvas.getNumPixX();xi++) {
      double fxy = f(theRamCanvas.int2realX(xi), theRamCanvas.int2realY(yi));
      theRamCanvas.drawPoint(xi, yi, mjr::ramCanvas3c8b::colorType::csPGrey3x::c(static_cast<mjr::ramCanvas3c8b::csIntType>((382*(1+fxy)))));  
      //theRamCanvas.drawPoint(xi, yi, mjr::ramCanvas3c8b::colorType::csPGrey3x::c(static_cast<mjr::ramCanvas3c8b::csIntType>((764*std::abs(fxy)))));  
    }
  }

  // Run across all the pixels, and draw the ones with a zero crossing red.
  for(int yi=0;yi<theRamCanvas.getNumPixY();yi++) {
    for(int xi=0;xi<theRamCanvas.getNumPixX();xi++) {
      std::vector<mjr::math::esgn::signT> signs(4);
      for(int c=0;c<4;c++) {
        auto fpt = theRamCanvas.int2realCorner(xi, yi, c);
        signs[c] = mjr::math::esgn::sgn(f(fpt.x, fpt.y));
      }
      if (mjr::math::esgn::zero_or_change(signs))
        theRamCanvas.drawPoint(xi, yi, mjr::ramCanvas3c8b::colorType::cornerColorEnum::RED);
    }
  }

  theRamCanvas.writeTIFFfile("demo_corners.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
double f(double x, double y) {
  double z = y+2*std::exp(-x*x/4);
  double d = std::sqrt(x*x+y*y);
  double a = std::atan2(std::abs(x), std::abs(z)+0.1);
  return std::sin(d*d)*std::sin(9*a*d+0*int(d+1));
}

/** @endcond */
