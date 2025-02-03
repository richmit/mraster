// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      geomTfrm_LensDistortion.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Read an image, correct it for radial lens discortion, and write out the corrected image.@EOL
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
 @filedetails   

  The geomTfrmRevRPoly() method uses a radial polynomial transform.  This method may be used to reproduce the behavior of Imagemagick's barrel distortion
  transformation.  In Imagemagick the following terminology and constraints are used:

   - (X, Y) is the image center for both T & S
   - A, B, C, & D are constants
   - A+B+C+D=1 -- if you don't provide D it will be computed

  This is all put together on the command line something like this:
  @verbatim
       -distort Barrel "A B C D X Y"
  @endverbatim

  We can demonstrate the similar behavior between Imagemagick & this example program like this:

   - Make test images
     @verbatim
     make test_images
     ./test_images.exe
     @endverbatim
  
   - Compute the new image with imagemagik
     @verbatim
     rm test_images_mcgrid_fimg.tiff
     magick test_images_mcgrid.tiff -background Green -virtual-pixel Background -interpolate Bilinear -filter point -distort barrel "0.0 -0.0160 0.0" test_images_mcgrid_fimg.tiff
     start test_images_mcgrid_fimg.tiff
     @endverbatim
  
   - Compute the new image with MRaster
     @verbatim
     make geomTfrm_LensDistortion
     ./geomTfrm_LensDistortion.exe test_images_mcgrid.tiff
     mv geomTfrm_LensDistortion.tiff test_images_mcgrid_fmr.tiff
     start test_images_mcgrid_fmr.tiff
     @endverbatim
  
   - Use compare aginst the two imgages
     @verbatim
     magick compare -metric mae test_images_mcgrid_fmr.tiff test_images_mcgrid_fimg.tiff out.tiff
     start out.tiff
     @endverbatim
  
   - Subtract the two images
     @verbatim
     magick test_images_mcgrid_fmr.tiff test_images_mcgrid_fimg.tiff -compose Mathematics -define compose:args='0,1,-1,0' -composite out.tiff
     start out.tiff
     @endverbatim

  Note the images are not identical, but they are very close.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b dRamCanvas;

  if (argc < 2) {
    fprintf(stderr, "ERROR argument required!\n");
    exit(1);
  }

  int rRet;
  if((rRet=dRamCanvas.readTIFFfile(argv[1]))) {
    fprintf(stderr, "ERROR(%d) reading file %s\n", rRet, argv[1]);
    exit(1);
  }

  double A       =  0.0000;
  double B       = -0.0160;
  double C       =  0.0000;
  double D       =  1.0000 - A - B - C;

  double Xo      = dRamCanvas.getNumPixX() / 2.0;
  double Yo      = dRamCanvas.getNumPixY() / 2.0;
  double Sr      = std::min(dRamCanvas.getNumPixX(), dRamCanvas.getNumPixY()) / 2.0;
  double Sout    = 1.0;

  std::vector<double> poly {A, B, C, D};

  mjr::ramCanvas3c8b uRamCanvas = dRamCanvas.geomTfrmRevRPoly(poly, Sr, Xo, Yo, Sout);

  uRamCanvas.writeTIFFfile("geomTfrm_LensDistortion.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;

  return 0;
}
/** @endcond */
