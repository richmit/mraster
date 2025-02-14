// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_emboss.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     This program draws a Mandelbrot set using the "potential"@EOL
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

  This example program computes some "surfaces" related to the Mandelbrot set, and a pseudo-3D rendering of same.

   * pot: Potential surface
   * dist: Distance surface (Using the Milnor and Thurston distance estimator)

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathLINM.hpp"
#include "MRMathIVL.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
const int    CSIZE  = 2048;
const int    MAXITR = 2048;
const double BALL   = 100;

/* This is out here so that it will get allocated on the heap. I'm too lazy to use malloc just this moment. */
double theValues[CSIZE][CSIZE];

double ranges[5][4] = { { -2.0,        1.0,       -1.5,        1.5       },
                        { -0.12,      -0.03,      -0.92, -0.81 },
                        {  0.0353469,  0.5353469,  0.1153845,  0.6153845 },
                        {  -1.5,       -1.0,        -0.5,       0.0        },
                        {  0.0353469,  0.5353469,  0.1153845,  0.6153845 }
                      };

/** Reasons iteration may stop */
enum class whyStop { OUTSET,   //!< Not in set (|z|>BALL)
                     MAXCOUNT, //!< Maximum iteration reached
                     INSET     //!< In set (known region)
                   };

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b   potRamCanvas(CSIZE, CSIZE), distRamCanvas(CSIZE, CSIZE);
  mjr::ramCanvas3c8b::colorType       theColor;
  double               lightHeight = 1.125;
  double               lightAngle = std::numbers::pi/4;
  std::complex<double> lightDirection = exp(lightAngle*std::complex<double>(0,1));
  whyStop              why;

  for(int i=0; i<3; i++) {
    //for(int i : { 0 } ) {
    potRamCanvas.newRealCoords(ranges[i][0], ranges[i][1], ranges[i][2], ranges[i][3]);
    potRamCanvas.clrCanvasToBlack();
    /* Compute the potential function on our grid.  For off-set points we store the potential in an array, for in-set points we store a -1.  */
    std::complex<double> z;
    for(int y=0;y<potRamCanvas.getNumPixY();y++) {
      if((y%(CSIZE/10))==0)
        std::cout << "    CASE: " << i << " LINE: " << y << "/" << CSIZE << std::endl;
      for(int x=0;x<potRamCanvas.getNumPixX();x++) {
        int count;
        double cr = potRamCanvas.int2realX(x);
        double ci = potRamCanvas.int2realY(y);
        std::complex<double> c(cr, ci);
        std::complex<double> dc = 1.0;
        std::complex<double> pder = dc;
        std::complex<double> dder1 = 1.0;
        std::complex<double> dder2 = 0.0;
        double p = std::abs(c-0.25);
        if((cr >= p-2.0*p*p+0.25) && std::abs(c+1.0) >= 0.25) {
          z=c;
          for(count=0; ; count++) {
            if(count>=MAXITR) {
              why = whyStop::MAXCOUNT;
              break;
            }
            if(std::abs(z)>BALL) {
              why = whyStop::OUTSET;
              break;
            }
            dder2 = 2.0 * (dder2 * z + dder1 * dder1);
            dder1 = 2.0 * dder1 * z + 1.0;
            pder = pder * 2.0 * z + dc;
            z   = z * z + c;
          }
        } else {
          why = whyStop::INSET;
        }

        if(why == whyStop::OUTSET) {
          if(std::abs(pder) < 0.00001) { // Should never happen...
            potRamCanvas.drawPoint(x, y, "blue");
          } else {
            if(std::abs(z) < 0.00001) { // This can't happen...
              potRamCanvas.drawPoint(x, y, "green");
            } else {
              std::complex<double> potNormal = z/pder;
              potNormal = potNormal/std::abs(potNormal);  // normalize potNormal
              double potShade = std::real(potNormal * std::conj(lightDirection)) + lightHeight;  // dot product with the incoming light
              potShade = mjr::math::ivl::unit_clamp(potShade/(1+lightHeight));  // rescale so <=1, and then clamp to keep >=0
              potRamCanvas.drawPoint(x, y, mjr::ramCanvas3c8b::colorType(static_cast<mjr::ramCanvas3c8b::colorChanType>(mjr::math::linm::scl_real_to_int(potShade, 255)),
                                                          static_cast<mjr::ramCanvas3c8b::colorChanType>(mjr::math::linm::scl_real_to_int(potShade, 255)),
                                                          static_cast<mjr::ramCanvas3c8b::colorChanType>(mjr::math::linm::scl_real_to_int(potShade, 255))));
            }
          }
        } else {
          potRamCanvas.drawPoint(x, y, "red");
        }

        if(why == whyStop::OUTSET) {
          double zLogMod = 0.5*std::log(std::norm(z));
          std::complex<double> distNormal = z*dder1*((1.0+zLogMod)*std::conj(dder1*dder1)-zLogMod*std::conj(z*dder2));
          double distNormalAbs = std::abs(distNormal);
          if(distNormalAbs < 0.00001) { // Should never happen...
            distRamCanvas.drawPoint(x, y, "blue");
          } else {
            distNormal = distNormal/distNormalAbs;  // normalize distNormal
            double distShade = std::real(distNormal * std::conj(lightDirection)) + lightHeight;  // dot product with the incoming light
            distShade = mjr::math::ivl::unit_clamp(distShade/(1+lightHeight));  // rescale so <=1, and then clamp to keep >=0
            distRamCanvas.drawPoint(x, y, mjr::color3c8b::csCCdiag01::c(static_cast<mjr::ramCanvas3c8b::csIntType>(mjr::math::linm::scl_real_to_int(distShade, 255))));
          }
        } else {
          distRamCanvas.drawPoint(x, y, "red");
        }
      }
    }

    potRamCanvas.writeTIFFfile("mandelbrot_emboss_pot_"   + std::to_string(i) + ".tiff");
    distRamCanvas.writeTIFFfile("mandelbrot_emboss_dist_" + std::to_string(i) + ".tiff");
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
