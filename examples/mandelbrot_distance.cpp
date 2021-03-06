// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      mandelbrot_distance.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     This program draws a mandelbrot set using the "distance".@EOL
 @std       C++98
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

  We draw the boundary using the Milnor and Thurston distance estimator as presented in 'The Science of Fractal Images'.  

  Color scheme:
    - blue:  points found to be outside (iterated bigger than BALL), but very close to set.
    - yellow: points found to be outside (iterated bigger than BALL), but far from to set.
    - white: points found to be outside (iterated bigger than BALL), but for which we could not compute the distance (der==0) -- shouldn't happen.
    - green: points known to be in one of the hyperbolic components of the set
    - cyan: points assumed to be in the set because we iterated MAXCOUNT times

  Reference: Peitgen, Heinz-Otto and Saupe, Dietmar; 1988; The Science of Fractal Images; ISBN: 0-387-96608-0; pp 192-196
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

/** Reasons iteration may stop */
enum class whyStopMD { OUTSET,   //!< Not in set (|z|>BALL)
                       MAXCOUNT, //!< Maximum iteration reached
                       INSET     //!< In set (known region)
                     };

int main(void) {
  const double       DISTTH = 0.001;
  const int          MAXITR = 2048;
  const double       BALL   = 10000.0;
  double             dist;
  mjr::ramCanvas3c8b theRamCanvas(1080*2, 1080*2, -1.9, 0.5, -1.2, 1.2);
  whyStopMD            why;           

  for(int y=0; y<theRamCanvas.get_numYpix(); y++) {
    for(int x=0; x<theRamCanvas.get_numXpix(); x++) {
      int count;
      double cr = theRamCanvas.int2realX(x);
      double ci = theRamCanvas.int2realY(y);
      std::complex<double> c(cr, ci), der(0, 0), z(0, 0);
      double p = std::abs(c-0.25);
      if((cr >= p-2.0*p*p+0.25) && std::abs(c+1.0) >= 0.25) {
        for(count=0; ; count++) {            
          if(count>=MAXITR) {
            why = whyStopMD::MAXCOUNT;
            break;
          }
          if(std::abs(z)>BALL) {
            why = whyStopMD::OUTSET;
            break;
          }
          der = 2.0 * z * der + 1.0;
          z   = z * z + c;
        }
      } else {
        why = whyStopMD::INSET;
      }
      if(why == whyStopMD::OUTSET) {
        double der_mag = std::abs(der);
        if(der_mag > 0.00001) {
          dist=2.0*std::log(std::abs(z))*std::abs(z)/der_mag;
          if(dist < DISTTH) {
            theRamCanvas.drawPoint(x, y, mjr::color3c8b(0, 0, 255));
          } else {
            theRamCanvas.drawPoint(x, y, mjr::color3c8b(255, 255, 0));
          }        
        } else {
          theRamCanvas.drawPoint(x, y, mjr::color3c8b(255, 255, 255));
        }        
      } else {
        if(why == whyStopMD::INSET) {
          theRamCanvas.drawPoint(x, y, mjr::color3c8b(0, 255, 0));
        } else {
          theRamCanvas.drawPoint(x, y, mjr::color3c8b(0, 255, 255));
        }        
      }
    }      
  }

  theRamCanvas.writeTIFFfile("mandelbrot_distance.tiff");
}
