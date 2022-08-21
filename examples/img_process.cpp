// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
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
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  //mjr::ramCanvas3c8b *aRamCanvasPtr;
  //mjr::ramCanvas3c8b aRamCanvas;
  mjr::ramCanvas3c8b listOcanv[16];
  //mjr::ramCanvas4c8b listOcanv[16];
  //mjr::ramCanvas1c16b listOcanv[16];
  //mjr::ramCanvas1c8b listOcanv[16];
  mjr::ramCanvas3c8b::colorType aColor;
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
    char const *colors[5] = { "white", "red", "green", "blue", "black" };
    for(int i=0; i<(512/32); i++)
      listOcanv[0].drawLine(0,  i*32, 512,  i*32, colors[i%5]);
    listOcanv[0].writeTIFFfile("testImage1.tiff");
    listOcanv[0].flipTranspose();
    listOcanv[0].writeTIFFfile("testImage2.tiff");
    return 0;
  }

   // listOcanv[0].writeTIFFfile("in1.tiff");
   // listOcanv[1].writeTIFFfile("in2.tiff");

  // for(auto& pix : listOcanv[0])
  //   //pix.setToRed();
  //   pix.tfrmNot();

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Convolution.  Output image as conv.tiff.                                                                                                                         */
  /* **************************************************************************************************************************************************************** */

  // To use convolving, we need a kernel
  // double edgeDetect1_3[9]  = { 1,  0, -1,  0,  0,  0, -1,  0,  1};
  // double edgeDetect2_3[9]  = { 0,  1,  0,  1, -4,  1,  0,  1,  0};
  // double edgeDetect3_3[9]  = {-1, -1, -1, -1,  8, -1, -1, -1, -1};
  // double sharpen_3[9]      = { 0, -1,  0, -1,  5, -1,  0, -1,  0};
  // double boxBlur_3[9]      = { 1,  1,  1,  1,  1,  1,  1,  1,  1}; // (d=9)
  // double gaussianBlur_3[9] = { 1,  2,  1,  2,  4,  2,  1,  2,  1}; // (d=16)
  // double gaussianBlur_5[25]    = {1, 4, 6, 4, 1, 4, 16, 24, 16, 4, 6, 24,   36, 24, 6, 4, 16, 24, 16, 4, 1, 4, 6, 4, 1}; // (d=256)
  // double unsharpMmasking_5[25] = {1, 4, 6, 4, 1, 4, 16, 24, 16, 4, 6, 24, -476, 24, 6, 4, 16, 24, 16, 4, 1, 4, 6, 4, 1}; // (d=-256)

  double kernel[51*51];
  listOcanv[0].computeConvolutionMatrixGausian(kernel, 9, 10);
  //listOcanv[0].computeConvolutionMatrixBox(kernel, 9);

  std::cerr << "CONVOLUTION STARTING" << std::endl;
  listOcanv[0].convolution(kernel, 9, 9, 1.0);
  //listOcanv[0].convolution(edgeDetect2_3, 3, 3, 1.0);
  //listOcanv[0].convolution(gaussianBlur_5, 5, 5, 256);
  listOcanv[0].writeTIFFfile("testImage1_c.tiff");

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Hide the second image in the first.  Outputs the given images as in1.tiff and in2.tiff.  Outputs the combined image as cmb.tiff.                                     */
  /* **************************************************************************************************************************************************************** */
  // listOcanv[0].writeTIFFfile("in1.tiff");
  // listOcanv[1].writeTIFFfile("in2.tiff");
  // listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmAnd, mjr::ramCanvas3c8b::colorType(0xF0, 0xF0, 0xF0));
  // listOcanv[1].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmShiftR, mjr::ramCanvas3c8b::colorType(4, 4, 4));
  // listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmOr, listOcanv[1]);
  // listOcanv[0].writeTIFFfile("cmb.tiff");

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Extract two images that have been combined.                                                      */
  /* **************************************************************************************************************************************************************** */
  // listOcanv[1].reallocCanvas(listOcanv[0].getNumPixX(), listOcanv[0].getNumPixY());
  // listOcanv[1].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmCopy, listOcanv[0]);
  // listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmAnd, mjr::ramCanvas3c8b::colorType(0xF0, 0xF0, 0xF0));
  // listOcanv[1].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmShiftL, mjr::ramCanvas3c8b::colorType(4, 4, 4));
  // listOcanv[0].writeTIFFfile("out1.tiff");
  // listOcanv[1].writeTIFFfile("out2.tiff");

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Various homogenious transformations                                                              */
  /* **************************************************************************************************************************************************************** */
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmStep, mjr::ramCanvas3c8b::colorType(150, 150, 150), mjr::ramCanvas3c8b::colorType(200, 200, 200));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmSaw, mjr::ramCanvas3c8b::colorType(150, 150, 150), mjr::ramCanvas3c8b::colorType(200, 200, 200));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmShiftL, mjr::ramCanvas3c8b::colorType(4, 4, 4));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmShiftR, mjr::ramCanvas3c8b::colorType(4, 4, 4));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmAnd, mjr::ramCanvas3c8b::colorType(0x00, 0xFF, 0x00));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmOr, mjr::ramCanvas3c8b::colorType(0xFF, 0x00, 0x00));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmXor, mjr::ramCanvas3c8b::colorType(0xF0, 0x0F, 0x0F));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmInvert);
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmNot);
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmStdPow, 0.7);
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmStdPow, 0.9, 0.8, 0.7);
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmLinearGreyLevelScale, 2.0, 150.0);
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmLinearGreyLevelScale, 2, 150, 0, 0, 1, 0); // no workie
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmDirac, mjr::ramCanvas3c8b::colorType(0xF0, 0x0F, 0x0F));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmFuzzyDirac, mjr::ramCanvas3c8b::colorType(0xF0, 0x0F, 0x0F), mjr::ramCanvas3c8b::colorType(0x0F, 0x0F, 0x0F));
  //listOcanv[0].applyHomoPixTfrm(&mjr::ramCanvas3c8b::colorType::tfrmDiracTot, mjr::ramCanvas3c8b::colorType(0xF0, 0x0F, 0x0F));
  //listOcanv[0].writeTIFFfile("img_process.tiff");

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Various canvas combination functions                                                             */
  /* **************************************************************************************************************************************************************** */
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmXor,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmAnd,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmOr,       listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmCopy,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmAbsDiff,  listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmSqDiff,   listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmSum,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmSumClp,   listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmDiv,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMult,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMultClp,  listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMean,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMean,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmGmean,    listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmGmeanClp, listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmDiff,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmDiffClp,  listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMod,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMaxL,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMinL,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMax,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMin,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMean,     listOcanv[1], 10, 20);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMean,     listOcanv[1], 20, 10, 50, 40);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMean,     listOcanv[1], 10, 20, 50, 60, 100, 100);
  //listOcanv[0].combineRamCanvasBinOp(&mjr::ramCanvas3c8b::colorType::tfrmMean,     listOcanv[1], 400, 450, 150, 60, 100, 100);
  //listOcanv[0].writeTIFFfile("img_process.tiff");

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Multi-image statstical combinations.                                                             */
  /* **************************************************************************************************************************************************************** */
  //aRamCanvas = ramCanvas3c8b(listOcanv[0].getNumPixX(), listOcanv[0].getNumPixY());
  //aRamCanvas.combineRamCanvasMean(listOcanv, numFiles);
  //aRamCanvas.writeTIFFfile("img_process.tiff");

  /* **************************************************************************************************************************************************************** */
  /* **************************************************************************************************************************************************************** */
  /* Rotate, Scale, Reflect                                                                                                                                           */
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

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;

  return 0;
}
/** @endcond */
