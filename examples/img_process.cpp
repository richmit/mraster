// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      img_process.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Demo some image processing.@EOL
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

/**************************************************************************************************************************************************************/
int main(int argc, char *argv[]) {

  //mjr::ramCanvas3c8b *aRamCanvasPtr;
  //mjr::ramCanvas3c8b aRamCanvas;
  //mjr::ramCanvas3c8b listOcanv[16];
  //mjr::ramCanvas4c8b listOcanv[16];
  mjr::ramCanvas1c16b listOcanv[16];
  //mjr::ramCanvas1c8b listOcanv[16];
  mjr::color3c8b aColor;
  int rRet;

  int numFiles=argc-1;
  for(int i=1;i<argc;i++) {
    std::cerr << "LOADING: " << argv[i] << std::endl;
    if((rRet=listOcanv[i-1].readTIFFfile(argv[i]))) {
      fprintf(stderr, "ERROR(%d) reading file %s\n", rRet, argv[i]);
      exit(1);
    }
  }

  if(numFiles==0) {
    std::cout << "No images provided on command line.  Generateing test images" << std::endl;
    listOcanv[0].resizeCanvas(512, 512);
    listOcanv[0].drawFillRectangle(  0, 0, 105, 512, "white");
    listOcanv[0].drawFillRectangle(106, 0, 205, 512, "red");
    listOcanv[0].drawFillRectangle(206, 0, 305, 512, "green");
    listOcanv[0].drawFillRectangle(306, 0, 405, 512, "blue");
    listOcanv[0].drawFillRectangle(406, 0, 511, 512, "black");
    listOcanv[0].writeTIFFfile("testImage1.tiff");
    listOcanv[0].flipTranspose();
    listOcanv[0].writeTIFFfile("testImage2.tiff");
    return 0;
  }

  // if(numFiles==0) {
  //   std::cout << "No images provided on command line.  Generateing test images" << std::endl;
  //   listOcanv[0].resizeCanvas(3, 3);
  //   listOcanv[0].drawPoint(0, 0, (uint16_t)0xffff);
  //   listOcanv[0].drawPoint(1, 0, (uint16_t)0x0fff);
  //   listOcanv[0].drawPoint(2, 0, (uint16_t)0xffff);
  //   listOcanv[0].drawPoint(0, 1, (uint16_t)0x0000);
  //   listOcanv[0].drawPoint(1, 1, (uint16_t)0x0000);
  //   listOcanv[0].drawPoint(2, 1, (uint16_t)0x0000);
  //   listOcanv[0].drawPoint(0, 2, (uint16_t)0x0fff);
  //   listOcanv[0].drawPoint(1, 2, (uint16_t)0xffff);
  //   listOcanv[0].drawPoint(2, 2, (uint16_t)0x0fff);
  //   listOcanv[0].writeTIFFfile("testImage1.tiff");
  //   return 0;
  // }

   listOcanv[0].writeTIFFfile("in1.tiff");
   listOcanv[1].writeTIFFfile("in2.tiff");
  
  // for(auto& pix : listOcanv[0])
  //   //pix.setToRed();
  //   pix.tfrmNot();

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Hide the second image in the first.  Outputs the given images as in1.tiff and in2.tiff.  Outputs the combined image as cmb.tiff.                                     */
  /* **************************************************************************************************************************************************************** */
  // listOcanv[0].writeTIFFfile("in1.tiff");
  // listOcanv[1].writeTIFFfile("in2.tiff");
  // listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmAnd, color3c8b(0xF0, 0xF0, 0xF0)); 
  // listOcanv[1].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmShiftR, color3c8b(4, 4, 4));
  // listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmOr, listOcanv[1]);
  // listOcanv[0].writeTIFFfile("cmb.tiff");
  
  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Extract two images that have been combined.                                                      */
  /* **************************************************************************************************************************************************************** */
  // listOcanv[1].reallocCanvas(listOcanv[0].get_numXpix(), listOcanv[0].get_numYpix());
  // listOcanv[1].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmCopy, listOcanv[0]);
  // listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmAnd, color3c8b(0xF0, 0xF0, 0xF0));
  // listOcanv[1].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmShiftL, color3c8b(4, 4, 4));
  // listOcanv[0].writeTIFFfile("out1.tiff");
  // listOcanv[1].writeTIFFfile("out2.tiff");

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Various homogenious transformations                                                              */
  /* **************************************************************************************************************************************************************** */
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmStep, color3c8b(150, 150, 150), color3c8b(200, 200, 200));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmSaw, color3c8b(150, 150, 150), color3c8b(200, 200, 200));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmShiftL, color3c8b(4, 4, 4));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmShiftR, color3c8b(4, 4, 4));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmAnd, color3c8b(0x00, 0xFF, 0x00));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmOr, color3c8b(0xFF, 0x00, 0x00));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmXor, color3c8b(0xF0, 0x0F, 0x0F));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmInvert);
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmNot);
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmStdPow, 0.7);
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmStdPow, 0.9, 0.8, 0.7);
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmLinearGreyLevelScale, 2.0, 150.0);  
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmLinearGreyLevelScale, 2, 150, 0, 0, 1, 0); // no workie
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmDirac, color3c8b(0xF0, 0x0F, 0x0F));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmFuzzyDirac, color3c8b(0xF0, 0x0F, 0x0F), color3c8b(0x0F, 0x0F, 0x0F));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::rcColor::tfrmDiracTot, color3c8b(0xF0, 0x0F, 0x0F));
  //listOcanv[0].writeTIFFfile("img_process.tiff");

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Various canvas combination functions                                                             */
  /* **************************************************************************************************************************************************************** */
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmXor,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmAnd,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmOr,       listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmCopy,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmAbsDiff,  listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmSqDiff,   listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmSum,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmSumClp,   listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmDiv,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMult,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMultClp,  listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMean,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMean,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmGmean,    listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmGmeanClp, listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmDiff,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmDiffClp,  listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMod,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMaxL,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMinL,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMax,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMin,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMean,     listOcanv[1], 10, 20);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMean,     listOcanv[1], 20, 10, 50, 40);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMean,     listOcanv[1], 10, 20, 50, 60, 100, 100);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::rcColor::tfrmMean,     listOcanv[1], 400, 450, 150, 60, 100, 100);
  //listOcanv[0].writeTIFFfile("img_process.tiff");

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Multi-image statstical combinations.                                                             */
  /* **************************************************************************************************************************************************************** */
  //aRamCanvas = ramCanvas3c8b(listOcanv[0].get_numXpix(), listOcanv[0].get_numYpix());
  //aRamCanvas.combineRamCanvasMean(listOcanv, numFiles);
  //aRamCanvas.writeTIFFfile("img_process.tiff");

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Rotate, Scale, Reflect                                                                           */
  /* **************************************************************************************************************************************************************** */
  //listOcanv[0].flipHorz();
  //listOcanv[0].flipVert();
  //listOcanv[0].flipTranspose();
  //listOcanv[0].rotate90CW();
  //listOcanv[0].rotate90CCW();
  //listOcanv[0].rotate180();
  //listOcanv[0].scaleUpProximal(2);
  //listOcanv[0].scaleDown1pt(2);
  //listOcanv[0].scaleDownMax(2);
  //listOcanv[0].scaleDownMean(2);
  //listOcanv[0].writeTIFFfile("img_process.tiff");
  //listOcanv[0].cropCanvas(10, 10, 200, 200);
  //listOcanv[0].resizeCanvas(400, 300, 30, 5);
  //listOcanv[0].writeTIFFfile("img_process.tiff");

  return 0;
}

