// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      newton_half.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw various Newton-like Fracticals.@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 1988-2015, 2017, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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


     Maxima: f:sin(z); z-f/diff(f, z);

********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <vector>                                                        /* STL vector              C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
/** Enum identifying why iteration stopped */
enum class whyStopNH { DIVZERO,   //!< Divide by zero (zeroTol)
                       TOOBIG,    //!< Iterate got too big (> escapeMod)
                       CONVERGEU, //!< Converged in the upper half plane
                       CONVERGEL, //!< Converged in the lower half plane
                       TOOLONG    //!< Too many iterations (> MaxCount)
                     };

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const double escapeMod  = -32.0;
  const int    MaxCount   = 64;
  const double  zeroTol    = 0.0001;
  const int    numToKeep  = 5;
  whyStopNH    why;
  //mjr::ramCanvas3c8b theRamCanvas(3840/1, 2160/1, 4.0, 8.0, -2.0, 2.0);
  //mjr::ramCanvas3c8b theRamCanvas(3840/1, 2160/1, -0.16, 0.36, -0.22, 0.23);
  //mjr::ramCanvas3c8b theRamCanvas(3840/4, 2160/4, -0.42, 0.42, -0.2, 0.2);
  //mjr::ramCanvas3c8b theRamCanvas(3840/1, 2160/1, -4.72, -0.5, -1.0, 1.0);
  //mjr::ramCanvas3c8b theRamCanvas(3840/4, 2160/4, -3.0, 3.0, -3.0, 3.0);
  mjr::ramCanvas3c8b theRamCanvas(1080*4, 1080*4, 0.6, 1.1, -0.4, 0.4);

  mjr::ramCanvas3c8b::colorType aColor(255, 255, 255);

  for(int y=0;y<theRamCanvas.get_numYpix();y++) {
    std::cout << "Line: " << y << std::endl;
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      std::complex<double> z(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));

      std::vector<std::complex<double>> lastZs(numToKeep);
      mjr::ramCanvas3c8b::csIntType count = 0;
      double maxMod = 0.0;
      while(1) {
        if (count >= MaxCount) {
          why = whyStopNH::TOOLONG;
          break;
        }
        //std::complex<double> cz = ((-2.0*sin(2.0*z))-sin(z)+1.0);
        //std::complex<double> cz = (exp(z)-1.0);
        //std::complex<double> cz = sin(z);
        //std::complex<double> cz = cos(z);
        //std::complex<double> cz = ((2.0*z*cos(z)-z*z*sin(z))*cos(z*z*cos(z)));
        std::complex<double> cz = ((cos(z)-z*sin(z))*cos(z*cos(z)));
        if(abs(cz) < zeroTol) {
          why = whyStopNH::DIVZERO;
          break;
        }
        //z = z-(cos(2.0*z)+cos(z)+z)/cz;
        //z = z-(exp(z)-z)/cz;
        //z = z+cos(z)/cz;
        //z = z-(sin(z)-0.9)/cz;
        //z=z-sin(z*z*cos(z))/cz;
        z=z-sin(z*cos(z))/cz;
        double modz = abs(z);
        lastZs[count%numToKeep] = z;
        if(modz>maxMod) {
          maxMod = modz;
        }
        if(count >= numToKeep) {  // Criteria for convergeance:  Last numToKeep z values must be within zeroTol of each other.
          bool allEqual = true;
          for(int i=1; i<numToKeep; i++)
            if(abs(lastZs[0]-lastZs[i])>zeroTol) {
              allEqual = false;
              break;
            }
          if(allEqual) {
            if(z.real() > 0) {
              why = whyStopNH::CONVERGEU;
            } else {
              why = whyStopNH::CONVERGEL;
            }
            break;
          }
        }
        if((escapeMod>0) && (modz>escapeMod)) {
          why = whyStopNH::TOOBIG;
          break;
        }
        count++;
      }

      mjr::ramCanvas3c8b::csIntType ccol = (2*4*count);
      mjr::ramCanvas3c8b::csIntType mcol = ((mjr::ramCanvas3c8b::csIntType)(2*8*maxMod));
      switch(why) {
        case whyStopNH::TOOLONG   : theRamCanvas.drawPoint(x, y, aColor.cmpRGBcornerDGradiant((mcol)%(2*256),      "MWM")); break;
        case whyStopNH::CONVERGEU : theRamCanvas.drawPoint(x, y, aColor.cmpRGBcornerDGradiant((mcol+ccol)%(2*256), "BWB")); break;
        case whyStopNH::CONVERGEL : theRamCanvas.drawPoint(x, y, aColor.cmpRGBcornerDGradiant((mcol+ccol)%(2*256), "RWR")); break;
        case whyStopNH::TOOBIG    : theRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(0,        0,        0));           break;
        case whyStopNH::DIVZERO   : theRamCanvas.drawPoint(x, y, aColor.cmpRGBcornerDGradiant((mcol+ccol)%(2*256), "CWC")); break;
      }
    }
  }
  theRamCanvas.writeTIFFfile("newton_half.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
