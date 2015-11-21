// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      imgProExample.cpp
 @author    Mitch Richling <http://www.mitchr.me>
 @brief     Demo some image processing.@EOL
 @copyright 
  @parblock
  Copyright (c) 1988-2015, Mitchell Jay Richling <http://www.mitchr.me> All rights reserved.

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

#include <unistd.h> 

using namespace mjr;

int main(int argc, char *argv[]) {
  //ramCanvas4c8b *aRamCanvasPtr;
  //ramCanvas4c8b aRamCanvas;
  ramCanvas4c8b listOcanv[16];
  //color4n1<int, short, long> aColor;
  color4c8b aColor;
  int rRet;

  int numFiles=0;
  for(int i=1;i<16;i++, numFiles++) {
    if(argc >= (i+1)) {
      if((rRet = listOcanv[i-1].readColorTGAfile(argv[i]))) {
        fprintf(stderr, "ERROR(%d) reading file %s\n", rRet, argv[i]);
        exit(1);
      }
    }
  }

  listOcanv[0].writeTGAfile("y.tga");

  /* ************************************************************************************************ */
  /* ************************************************************************************************ */
  /* Hide the second image in the first.  Outputs the given images as in1.tga and in2.tga.  Outputs the combined image as cmb.tga.                                     */
  /* ************************************************************************************************ */
  //listOcanv[0].writeTGAfile("in1.tga");
  //listOcanv[1].writeTGAfile("in2.tga");
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmAnd, color4c8b(0xF0, 0xF0, 0xF0));
  //listOcanv[1].applyHomoPixTfrm(&color4c8b::tfrmShiftR, color4c8b(4, 4, 4));
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::nboOr, listOcanv[1]);
  //listOcanv[0].writeTGAfile("cmb.tga");

  /* ************************************************************************************************ */
  /* ************************************************************************************************ */
  /* Extract two images that have been combined.                                                      */
  /* ************************************************************************************************ */
  //listOcanv[1].reallocCanvas(listOcanv[0].get_numXpix(), listOcanv[0].get_numYpix());
  //listOcanv[1].combineRamCanvasBinOp(&color4c8b::nboCopy, listOcanv[0]);
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmAnd, color4c8b(0xF0, 0xF0, 0xF0));
  //listOcanv[1].applyHomoPixTfrm(&color4c8b::tfrmShiftL, color4c8b(4, 4, 4));
  //listOcanv[0].writeTGAfile("out1.tga");
  //listOcanv[1].writeTGAfile("out2.tga");

  /* ************************************************************************************************ */
  /* ************************************************************************************************ */
  /* Various homogenious transformations                                                              */
  /* ************************************************************************************************ */
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmStep, color4c8b(150, 150, 150), color4c8b(200, 200, 200));
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmSaw, color4c8b(150, 150, 150), color4c8b(200, 200, 200));
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmShiftL, color4c8b(4, 4, 4));
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmShiftR, color4c8b(4, 4, 4));
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmAnd, color4c8b(0x00, 0xFF, 0x00));
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmOr, color4c8b(0xFF, 0x00, 0x00));
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmXor, color4c8b(0xF0, 0x0F, 0x0F));
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmInvert);
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmNot);
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmStdPow, 0.7);
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmStdPow, 0.9, 0.8, 0.7);
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmLinearGreyLevelScale, 2.0, 150.0);  
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmLinearGreyLevelScale, 2, 150, 0, 0, 1, 0); // no workie
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmDirac, color4c8b(0xF0, 0x0F, 0x0F));
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmFuzzyDirac, color4c8b(0xF0, 0x0F, 0x0F), color4c8b(0x0F, 0x0F, 0x0F));
  //listOcanv[0].applyHomoPixTfrm(&color4c8b::tfrmDiracTot, color4c8b(0xF0, 0x0F, 0x0F));

  //listOcanv[0].writeTGAfile("imgProExample.tga");

  /* ************************************************************************************************ */
  /* ************************************************************************************************ */
  /* Various canvas combination functions                                                             */
  /* ************************************************************************************************ */
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmXor,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmAnd,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmOr,       listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmCopy,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmAbsDiff,  listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmSqDiff,   listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmSum,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmSumClp,   listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmDiv,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMult,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMultClp,  listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMean,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMean,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmGmean,    listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmGmeanClp, listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmDiff,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmDiffClp,  listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMod,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMaxL,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMinL,     listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMax,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMin,      listOcanv[1]);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMean,     listOcanv[1], 10, 20);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMean,     listOcanv[1], 20, 10, 50, 40);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMean,     listOcanv[1], 10, 20, 50, 60, 100, 100);
  //listOcanv[0].combineRamCanvasBinOp(&color4c8b::tfrmMean,     listOcanv[1], 400, 450, 150, 60, 100, 100);
  //listOcanv[0].writeTGAfile("imgProExample.tga");

  /* ************************************************************************************************ */
  /* ************************************************************************************************ */
  /* Multi-image statstical combinations.                                                             */
  /* ************************************************************************************************ */
  //aRamCanvas = ramCanvas4c8b(listOcanv[0].get_numXpix(), listOcanv[0].get_numYpix());
  //aRamCanvas.combineRamCanvasMean(listOcanv, numFiles);
  //aRamCanvas.writeTGAfile("imgProExample.tga");

  /* ************************************************************************************************ */
  /* ************************************************************************************************ */
  /* Calculus based spatial transformations                                                           */
  /* ************************************************************************************************ */
  //listOcanv[0].delC2E();
  //listOcanv[0].delC2N();
  //listOcanv[0].delW2E();
  //listOcanv[0].delS2N();
  //listOcanv[0].aGrad1();
  //listOcanv[0].absDirDel(1,1);
  //listOcanv[0].posDirDel(1,1);
  //listOcanv[0].negDirDel(1,1);
  //listOcanv[0].writeTGAfile("imgProExample.tga");

  /* ************************************************************************************************ */
  /* ************************************************************************************************ */
  /* Various spatial transformations                                                                  */
  /* ************************************************************************************************ */
  //listOcanv[0].sqrMax(3);
  //listOcanv[0].sqrMean(3);
  //listOcanv[0].sqrAutoHistStr(5);
  //listOcanv[0].sqrEdgeMean(5);
  //listOcanv[0].writeTGAfile("imgProExample.tga");

  /* ************************************************************************************************ */
  /* ************************************************************************************************ */
  /* Rotate, Scale, Reflect                                                                           */
  /* ************************************************************************************************ */
  //listOcanv[0].flipHorz();
  //listOcanv[0].flipVert();
  //listOcanv[0].flipTranspose();
  //listOcanv[0].rotate90CW();
  //listOcanv[0].rotate90CCW();
  //listOcanv[0].rotate180();
  //listOcanv[0].rotateCCW1pt(0.785398163); // 0.785398163 rad == 45 deg
  //listOcanv[0].rotateCCW1pt(0.785398163, listOcanv[0].get_numXpix()/2, listOcanv[0].get_numYpix()/2);
  //listOcanv[0].linearTfrm1pt(1.2, 0.3, 0.4, 1.5);
  //listOcanv[0].affineTfrm1pt(1.5, 0.2, 0.4, 0.5, 100, 100);
  //listOcanv[0].affineTfrm3pt(1.5, 0.2, 0.4, 0.5, 100, 100);
  //listOcanv[0].affineTfrmXact(1.5, 0.2, 0.4, 0.5, 100, 100, 10, 10);
  //listOcanv[0].scaleUp(5);
  //listOcanv[0].scaleDown1pt(3);  
  //listOcanv[0].scaleDownAllPoint(3);  
  //listOcanv[0].scaleDownNpointBoot(2, 2);
  //listOcanv[0].scaleDownMax(3);  
  //listOcanv[0].writeTGAfile("imgProExample.tga");

  //listOcanv[0].cropCanvas(10, 10, 200, 200);
  //listOcanv[0].resizeCanvas(400, 300, 30, 5);
  //listOcanv[0].writeTGAfile("imgProExample.tga");

  //aRamCanvasPtr = listOcanv[0].getSubCanvas(10, 10, 200, 200);
  //aRamCanvasPtr->writeTGAfile("imgProExample.tga");

  /* ************************************************************************************************ */
  /* ************************************************************************************************ */
  /* Digital Harris Filter.                                                                           */
  /* ************************************************************************************************ */
  //fprintf(stderr, "LOAD DONE.  Harris Filter Start\n");
  //  for(int y=0;y<listOcanv[0].get_numYpix();y++) {
  //for(int x=0;x<listOcanv[0].get_numXpix();x++) {
  //    listOcanv[0].getPxColorRefNC(x, y).setGreen(listOcanv[1].getPxColor(x, y).getGreen());
  //    listOcanv[0].getPxColorRefNC(x, y).setBlue(listOcanv[2].getPxColor(x, y).getBlue());
  //  }
  //}
  //fprintf(stderr, "Harris Filter Done.  Hist streach Start...\n");
  ////listOcanv[0].autoHistStrech();
  ////listOcanv[0].autoMaxHistStrech();
  ////listOcanv[0].sqrAutoHistStreach(5);
  //fprintf(stderr, "Hist streach Done.  Write Start..\n");
  //listOcanv[0].writeTGAfile("imgProExample.tga");

}
