// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandeldragon_orbits.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Mandeldragon orbits.@EOL
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

  Explores the orbits of the iteration

   - mandeldragon_orbits_XRANGE_omax.tiff         Maximum iteration count for all orbits that hit the pixel
   - mandeldragon_orbits_XRANGE_ohst.tiff         Point histogram of exterior point orbits
   - mandeldragon_orbits_XRANGE_ihst.tiff         Point histogram of interior point orbits
   - mandeldragon_orbits_XRANGE_color_METHOD.tiff Colorized using a combination of the above images
   - mandeldragon_orbits_XRANGE_ohst_METHOD.tiff  Colorized version of ohst

The color images may be created on the command line from the monochrome, data images.  For example, we can combine
images like this:

                magick \( mandeldragon_orbits_omax.tiff -evaluate Pow 0.8 \) \( mandeldragon_orbits_ohst.tiff -evaluate Pow 0.3 \) \( mandeldragon_orbits_ihst.tiff -evaluate Pow 0.8 \) -combine mandeldragon_orbits_838.png

We can colorize a single monochrome image with a color scheme like this:

                magick \( mandeldragon_orbits_ohst.tiff -evaluate Pow 0.5 \) ../docs/pics/cs/color_lut_docs_csPLYinferno_50.png -clut mandeldragon_orbits_csPLYinferno.png

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas1c16b rcct;
typedef mjr::ramCanvas3c8b  rcrt;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int                       csize     = 7680/6;
  const int                       maxitr    = 256*4;
  const int                       resMul    = 16;
  const int                       sweepYres = csize*resMul;
  const double                    sweepYmin = -4.0;
  const double                    sweepYmax =  4.0;
  const double                    sweepYdel = (sweepYmax-sweepYmin)/sweepYres;
  const std::vector<double>       sweepXminL {  -4.0,  -4.0,  -4.0};
  const std::vector<double>       sweepXmaxL {   0.0,   4.0,   4.0};
  const std::vector<int>          sweepXresL {     1,     2,     1};
  const std::vector<std::string>  caseNamesL { "neg", "all", "pos"};
  
  for(int side=0; side<3; side++) {
    int    sweepXres = csize*resMul*sweepXresL[side];
    double sweepXmin = sweepXminL[side];
    double sweepXmax = sweepXmaxL[side];
    double sweepXdel = (sweepXmax-sweepXmin)/sweepXres;;
 
    rcct ihstRamCanvas(csize, csize,  -0.6, 1.0, -0.9, 0.9);
    rcct ohstRamCanvas(csize, csize,  -0.6, 1.0, -0.9, 0.9);
    rcct omaxRamCanvas(csize, csize,  -0.6, 1.0, -0.9, 0.9);
    std::complex<double>* theOrbit = new std::complex<rcct::coordFltType>[maxitr+1];

    for(int y=0;y<sweepYres;y++) {
      if((y%(sweepYres/16))==0)
        std::cout << "LINE: " << y << "/" << sweepYres << std::endl;
      for(int x=0;x<sweepXres;x++) {
        std::complex<rcct::coordFltType> c(x * sweepXdel + sweepXmin, y * sweepYdel + sweepYmin);
        std::complex<rcct::coordFltType> z(0.5, 0.0);
        for(rcct::colorChanType count=0; ; count++) {
          z = (c + 1.0) * z * (1.0 - z);
          theOrbit[count] = z;
          if(std::abs(z)>5.0) {
            for(rcct::colorChanType i=10; i<=count; i++) {
              ohstRamCanvas.incPxChan(theOrbit[i]);
              omaxRamCanvas.tformPixel(theOrbit[i], [i](auto& c) { c.tfrmMax(i); });
            }
            break;
          } else if(count>=(maxitr-1)) {
            for(rcct::colorChanType i=10; i<=count; i++) {
              ihstRamCanvas.incPxChan(theOrbit[i]);
            }
            break;
          }
        }
      }
    }

    // Dump out our "data" images
    omaxRamCanvas.autoHistStrech();
    omaxRamCanvas.rotate90CCW();
    omaxRamCanvas.writeTIFFfile("mandeldragon_orbits_" + caseNamesL[side] + "_omax.tiff");
    ohstRamCanvas.autoHistStrech();
    ohstRamCanvas.rotate90CCW();
    ohstRamCanvas.writeTIFFfile("mandeldragon_orbits_" + caseNamesL[side] + "_ohst.tiff");
    ihstRamCanvas.autoHistStrech();
    ihstRamCanvas.rotate90CCW();
    ihstRamCanvas.writeTIFFfile("mandeldragon_orbits_" + caseNamesL[side] + "_ihst.tiff");

    // Construct 8-bit RGB images
    rcrt theRamCanvas(omaxRamCanvas.getNumPixX(), omaxRamCanvas.getNumPixY());

    theRamCanvas.colorizeIntCanvas([&omaxRamCanvas, &ohstRamCanvas, &ihstRamCanvas](auto x, auto y) { return rcrt::colorType(static_cast<rcrt::colorChanType>(omaxRamCanvas.getPxColor(x, y).tfrmPow(0.8).getChan(0)/256), 
                                                                                                                             static_cast<rcrt::colorChanType>(ohstRamCanvas.getPxColor(x, y).tfrmPow(0.3).getChan(0)/256), 
                                                                                                                             static_cast<rcrt::colorChanType>(ihstRamCanvas.getPxColor(x, y).tfrmPow(0.8).getChan(0)/256)); });
    theRamCanvas.writeTIFFfile("mandeldragon_orbits_" + caseNamesL[side] + "_color_838.tiff");

    theRamCanvas.colorizeIntCanvas([&omaxRamCanvas, &ohstRamCanvas, &ihstRamCanvas](auto x, auto y) { return rcrt::colorType(static_cast<rcrt::colorChanType>(0), 
                                                                                                                             static_cast<rcrt::colorChanType>(ohstRamCanvas.getPxColor(x, y).tfrmPow(0.3).getChan(0)/256), 
                                                                                                                             static_cast<rcrt::colorChanType>(ihstRamCanvas.getPxColor(x, y).tfrmPow(0.8).getChan(0)/256)); });
    theRamCanvas.writeTIFFfile("mandeldragon_orbits_" + caseNamesL[side] + "_color__Z38.tiff");

    theRamCanvas.colorizeIntCanvas([&ohstRamCanvas](auto x, auto y) { return rcrt::colorType::csCCfractal0RYBCW::c(ohstRamCanvas.getPxColor(x, y).tfrmPow(0.3).getChan_dbl(0)); });
    theRamCanvas.writeTIFFfile("mandeldragon_orbits_" + caseNamesL[side] + "_ohst_3csCCfractal0RYBCW.tiff");

    theRamCanvas.colorizeIntCanvas([&ohstRamCanvas](auto x, auto y) { return rcrt::colorType::csCCdivBWR::c(ohstRamCanvas.getPxColor(x, y).tfrmPow(0.3).getChan_dbl(0)); });
    theRamCanvas.writeTIFFfile("mandeldragon_orbits_" + caseNamesL[side] + "_ohst_3csCCdivBWR.tiff");

    theRamCanvas.colorizeIntCanvas([&ohstRamCanvas](auto x, auto y) { return rcrt::colorType::csCCdivBWR::c(ohstRamCanvas.getPxColor(x, y).tfrmPow(0.5).getChan_dbl(0)); });
    theRamCanvas.writeTIFFfile("mandeldragon_orbits_" + caseNamesL[side] + "_ohst_5csCCdivBWR.tiff");

    theRamCanvas.colorizeIntCanvas([&ohstRamCanvas](auto x, auto y) { return rcrt::colorType::csPLYinferno::c(ohstRamCanvas.getPxColor(x, y).tfrmPow(0.5).getChan_dbl(0)); });
    theRamCanvas.writeTIFFfile("mandeldragon_orbits_" + caseNamesL[side] + "_ohst_csPLYinferno.tiff");
  }

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
