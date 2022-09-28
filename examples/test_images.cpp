// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      test_images.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Generate some test images.@EOL
 @copyright
  @parblock
  Copyright (c) 1988-2015, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may be used to edorse or promote products derived from this software
     without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
  @endparblock
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
  const int wide = 4096/1;
  const int tall = 2048/1;
  const int gap  = 32;
  mjr::ramCanvas3c8b cRamCanvas(wide, tall);
  mjr::ramCanvas1c8b mRamCanvas(wide, tall);

  char const numc = 7;
  char const *colors[numc] = { "white", "red", "green", "blue", "magenta", "cyan", "yellow" };

  cRamCanvas.clrCanvasToBlack();
  for(int i=1; i<wide/gap; i++)
    cRamCanvas.drawLine(i*gap, 0, i*gap, (tall-1), colors[i%numc]);
  for(int i=1; i<tall/gap; i++) 
    cRamCanvas.drawLine(0,  i*gap, (wide-1),  i*gap, colors[i%numc]);
  cRamCanvas.writeTIFFfile("test_images_ccgrid.tiff");

  for(int j=1; j<tall/gap/2+1; j++) {
    for(int i=(j-1)*4+1; i<wide/gap; i++) {
      cRamCanvas.drawFillTriangle(i*gap, j*gap, 
                                  (i+1)*gap, (j+1)*gap,
                                  (i+1)*gap, j*gap,
                                  colors[i%numc]);
    }
  }
  cRamCanvas.writeTIFFfile("test_images_ccgridt.tiff");

  mRamCanvas.clrCanvasToBlack();
  cRamCanvas.clrCanvasToBlack();
  for(int i=1; i<wide/gap; i++) {
    cRamCanvas.drawLine(i*gap, 0, i*gap, (tall-1), "white");
    mRamCanvas.drawLine(i*gap, 0, i*gap, (tall-1), "white");
  }
  for(int i=1; i<tall/gap; i++) {
    cRamCanvas.drawLine(0,  i*gap, (wide-1),  i*gap, "white");
    mRamCanvas.drawLine(0,  i*gap, (wide-1),  i*gap, "white");
  }
  cRamCanvas.writeTIFFfile("test_images_mcgrid.tiff");
  mRamCanvas.writeTIFFfile("test_images_mmgrid.tiff");

  for(int j=1; j<tall/gap/2+1; j++) {
    for(int i=(j-1)*4+1; i<wide/gap; i++) {
      cRamCanvas.drawFillTriangle(i*gap, j*gap, 
                                  (i+1)*gap, (j+1)*gap,
                                  (i+1)*gap, j*gap,
                                  "white");
      mRamCanvas.drawFillTriangle(i*gap, j*gap, 
                                  (i+1)*gap, (j+1)*gap,
                                  (i+1)*gap, j*gap,
                                  "white");
    }
  }
  cRamCanvas.writeTIFFfile("test_images_mcgridt.tiff");
  mRamCanvas.writeTIFFfile("test_images_mmgridt.tiff");

  return 0;
}
/** @endcond */
