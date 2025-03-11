// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      tricorn_orbits.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Tricorn orbits.@EOL
 @std       C++20
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
 @filedetails
  @verbatim
    magick \( tricorn_orbits_ohst.tiff -evaluate Pow 0.4 -despeckle \) ../docs/pics/cs/color_lut_docs_csCCwicB_50.png -clut -rotate 90 tricorn_orbits_csCCwicB.png; nomacs tricorn_orbits_csCCwicB.png &

    magick \( tricorn_orbits_ohst.tiff -evaluate Pow 0.3 -despeckle \) ../docs/pics/cs/color_lut_docs_csPLYinferno_50.png -clut -rotate 90 tricorn_orbits_csPLYinferno.png; nomacs tricorn_orbits_csPLYinferno.png &

    magick \( tricorn_orbits_ohst.tiff -evaluate Pow 0.3 \) \( tricorn_orbits_ihst.tiff -evaluate Pow 0.8 \) \( tricorn_orbits_oirt.tiff -evaluate Pow 0.7 -despeckle -blur 10 \) -combine -rotate 90 tricorn_orbits_composite.png; nomacs tricorn_orbits_composite.png &
  @endverbatim
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathCPLX.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas1c16b rcct;
typedef mjr::ramCanvas3c8b  rcrt;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int                       csize     =  7680/8;
  const int                       maxitr    =  256*4;
  const double                    escRad    =  5.0;
  const double                    z0r       =  0.0;
  const double                    z0i       =  0.0;
  const int                       resMul    =  8;
  const double                    sweepXmin = -2.0;
  const double                    sweepXmax =  2.0;
  const int                       sweepXres =  csize*resMul;
  const double                    sweepXdel =  (sweepXmax-sweepXmin)/sweepXres;;
  const int                       sweepYres =  csize*resMul;
  const double                    sweepYmin = -2.0;
  const double                    sweepYmax =  2.0;
  const double                    sweepYdel =  (sweepYmax-sweepYmin)/sweepYres;
  const double                    drawXmin  = -1.8;
  const double                    drawXmax  =  1.2;
  const double                    drawYmin  = -1.5;
  const double                    drawYmax  =  1.5;

  rcct ihstRamCanvas(csize, csize, drawXmin, drawXmax, drawYmin, drawYmax); // Interior points histogram
  rcct imagRamCanvas(csize, csize, drawXmin, drawXmax, drawYmin, drawYmax); // Interior points minimum distance to origin
  rcct ohstRamCanvas(csize, csize, drawXmin, drawXmax, drawYmin, drawYmax); // Exterior points histogram
  rcct oirtRamCanvas(csize, csize, drawXmin, drawXmax, drawYmin, drawYmax); // Exterior points max iteration for point
  rcct ojmpRamCanvas(csize, csize, drawXmin, drawXmax, drawYmin, drawYmax); // Exterior points max jump to point
  std::complex<double>* theOrbit = new std::complex<rcct::coordFltType>[maxitr+1];

  for(int y=0;y<sweepYres;y++) {
    if((y%(sweepYres/16))==0)
      std::cout << "LINE: " << y << "/" << sweepYres << std::endl;
    for(int x=0;x<sweepXres;x++) {
      std::complex<rcct::coordFltType> c(x * sweepXdel + sweepXmin, y * sweepYdel + sweepYmin);
      std::complex<rcct::coordFltType> z(z0r, z0i);
      for(rcct::colorChanType count=0; ; count++) {
        z = std::pow(std::conj(z), 2) + c ;
        if(std::abs(z)>escRad) {
          for(rcct::colorChanType i=10; i<=count; i++) {
            ohstRamCanvas.incPxChan(theOrbit[i]);
            oirtRamCanvas.tformPixel(theOrbit[i], [i](auto& c) { c.tfrmMax(i); });
            rcct::colorChanType dst = static_cast<rcct::colorChanType>(std::abs(theOrbit[i]-theOrbit[i-1]) / escRad * rcct::colorType::maxChanVal);
            ojmpRamCanvas.tformPixel(theOrbit[i], [dst](auto& c) { c.tfrmMax(dst); });
          }
          break;
        } else if(count>=(maxitr-1)) {
          for(rcct::colorChanType i=10; i<=count; i++) {
            rcct::colorChanType dst = static_cast<rcct::colorChanType>(std::abs(theOrbit[i]) / escRad * rcct::colorType::maxChanVal);
            imagRamCanvas.tformPixel(theOrbit[i], [dst](auto& c) { if(c.isBlack()) c.setC0(dst); else c.tfrmMin(dst); });
            ihstRamCanvas.incPxChan(theOrbit[i]);
          }
          break;        
        }
        theOrbit[count] = z;
      }
    }
  }

  // Dump out our "data" images
  oirtRamCanvas.autoHistStrech();
  oirtRamCanvas.writeTIFFfile("tricorn_orbits_oirt.tiff");
  ohstRamCanvas.autoHistStrech();
  ohstRamCanvas.writeTIFFfile("tricorn_orbits_ohst.tiff");
  ihstRamCanvas.autoHistStrech();
  ihstRamCanvas.writeTIFFfile("tricorn_orbits_ihst.tiff");
  ojmpRamCanvas.autoHistStrech();
  ojmpRamCanvas.writeTIFFfile("tricorn_orbits_ojmp.tiff");
  imagRamCanvas.autoHistStrech();
  imagRamCanvas.writeTIFFfile("tricorn_orbits_imag.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
