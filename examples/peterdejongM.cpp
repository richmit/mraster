// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      peterdejongM.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Peter de Jong Attractor Movie.@EOL
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

int main(void) {

  const int               imageSize =  540; // 4320 2160 1080 540 270
  const unsigned long int maxIters  =  300000000ul;
  const unsigned long int itersTick =  10000000ul;
  const int               numFrames =  128; // 512 128 32 16
  const double            pi        =  3.141592653589793238462643383279502884;
  const double            a         =  1.50503;
  const double            b         = -1.44118;
  const double            c         = -1.23281;
  const double            d         =  1.78607;
  const double            e         =  1.709360; 
  const double            f         =  1.794210; 
  const double            g         =  1.893750; 
  const double            h         = -1.38227;  
  const double            p         =  2.10;     

  mjr::color1c16b aColor;
  aColor.setAll(1);

  for(int frame=0; frame<numFrames; frame++) {

    mjr::ramCanvas1c16b theRamCanvas(imageSize, imageSize, -2, 2, -2, 2);
    /* Draw the atractor on a 16-bit, greyscale canvas -- the grey level will be an integer represeting the hit count for that pixel. */
    double x       = 1.0;
    double y       = 1.0;  
    uint64_t maxII = 0;
    for(uint64_t i=0;i<maxIters;i++) {
      double xNew = sin((a + 0.09 * sin(frame * 2 * pi / numFrames))*y + e) - cos(b*x + f);
      double yNew = sin((c + 0.08 * cos(frame * 2 * pi / numFrames))*x + g) - cos(d*y + h);
      theRamCanvas.drawPoint(x, y, theRamCanvas.getPxColor(x, y).tfrmAdd(aColor));
      if(theRamCanvas.getPxColor(x, y).getRed() > maxII) {
        maxII = theRamCanvas.getPxColor(x, y).getRed();
        if(maxII > 16384) { // 1/4 of max possible intensity
          std::cout << "FRAME(" << frame <<  "): " << i << " MAXS: " << maxII << " EXIT: Maximum image intensity reached" << std::endl;
          break;
        }
      }
      if((i % itersTick) == 0)
        std::cout << "FRAME(" << frame <<  "): " << i << " MAXS: " << maxII << std::endl;
      x=xNew;
      y=yNew;
    }

    // Dump a raw image
    { std::ostringstream stringStream;
      stringStream << "peterdejongM_" << std::setfill('0') << std::setw(3) << frame << ".mrw";
      theRamCanvas.writeRAWfile(stringStream.str());
    }
    
    // Root image transform
    theRamCanvas.applyHomoPixTfrm(&mjr::color1c16b::tfrmStdPow, 1/p);
    maxII = 65535.0 * pow(maxII/65535.0, 1/p);

    /* Create a new image based on an integer color scale -- this one is 24-bit RGB color.  This isn't the most efficient technique from a RAM perspective in
       that we could pass a conversion routine to writeTIFFfile (see sic.cpp for an example of how to do just that). */
    mjr::ramCanvas3c8b anotherRamCanvas(imageSize, imageSize);
    mjr::color3c8b bColor;
    for(int yi=0;yi<theRamCanvas.get_numYpix();yi++)
      for(int xi=0;xi<theRamCanvas.get_numXpix();xi++)
        anotherRamCanvas.drawPoint(xi, yi, bColor.cmpColorRamp(theRamCanvas.getPxColor(xi, yi).getRed() * 1275 / maxII, "0RYBCW"));

    { std::ostringstream stringStream;
      stringStream << "peterdejongM_" << std::setfill('0') << std::setw(3) << frame << ".tiff";
      anotherRamCanvas.writeTIFFfile(stringStream.str());
    }
  }
  return 0;
}


// mkdir rawpng
// mkdir mrw
// mv peter*.mrw mrw
// for f in mrw/*.mrw(:r:t); do echo $f; if [ ! -e rawpng/$f.png ] ; then convert -depth 16 -size 540x540+100 gray:mrw/$f.mrw -quality 90 rawpng/$f.png; fi; done
