// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      test_color.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark program for pixel draw rates with ramCanvas.@EOL
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

  We instantiate every member function in colorTpl so that we can check for compile time errors and do some basic functionality testing.

********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  std::tuple<mjr::colorRGBA8b::channelType, mjr::colorRGBA8b::channelType, mjr::colorRGBA8b::channelType> tc3 {128, 255, 128};
  std::tuple<mjr::colorRGBA8b::channelType, mjr::colorRGBA8b::channelType, mjr::colorRGBA8b::channelType, mjr::colorRGBA8b::channelType> tc4 {255, 128, 255, 128};
  std::vector<mjr::colorRGBA8b::channelType> vc2B {128, 255};
  std::vector<mjr::colorRGBA32F::channelType> vc2F {0.5, 1.0};

  mjr::colorRGBA8b  aColor(255, 200, 100);
  mjr::colorRGBA8b  bColor(255, 200, 100, 20);
  mjr::colorRGBA8b  cColor(255, 200, 100, 100);
  mjr::colorRGBA8b  dColor(255);
  mjr::colorRGBA8b  eColor(mjr::colorRGBA8b::cornerColorEnum::RED);
  mjr::colorRGBA8b  fColor("red");
  mjr::colorRGBA8b  gColor(std::string("red"));
  mjr::colorRGBA16b hColor("W");
  mjr::colorRGBA32b iColor('0'); // Note this calls setChans with a value of 48 (the ascii value for '0')

  mjr::colorRGBA32F jColor(1.0F);
  mjr::colorRGBA32F kColor(1.0F, 0.5F, 0.24F);
  mjr::colorRGBA32F lColor(1.0F, 0.5F, 0.54F);

  std::cout << "a: " << aColor << std::endl;
  std::cout << "b: " << bColor << std::endl;
  std::cout << "c: " << cColor << std::endl;
  std::cout << "d: " << dColor << std::endl;
  std::cout << "e: " << eColor << std::endl;
  std::cout << "f: " << fColor << std::endl;
  std::cout << "g: " << gColor << std::endl;
  std::cout << "h: " << hColor << std::endl;
  std::cout << "i: " << iColor << std::endl;

  std::cout << "j: " << jColor << std::endl;
  std::cout << "k: " << kColor << std::endl;
  std::cout << "l: " << kColor << std::endl;

  std::cout << "a red 8b: " << (int)aColor.getC1_byte() << std::endl;
  std::cout << "a red F:  " << (double)aColor.getC1_dbl() << std::endl;

  std::cout << "a MaxC:   " << (int)aColor.getMaxC()    << std::endl;
  std::cout << "a MinC:   " << (int)aColor.getMinC()    << std::endl;
  std::cout << "a MaxRGB: " << (int)aColor.getMaxRGB()  << std::endl;
  std::cout << "a MinRGB: " << (int)aColor.getMinRGB()  << std::endl;

  aColor.setChan(0, 0);                                            std::cout << "aColor.setChan(0, 0);                          " << aColor << std::endl;
  aColor.setC0(0);                                                 std::cout << "aColor.setC0(0);                               " << aColor << std::endl;
  aColor.setC1(0);                                                 std::cout << "aColor.setC1(0);                               " << aColor << std::endl;
  aColor.setC3(0);                                                 std::cout << "aColor.setC3(0);                               " << aColor << std::endl;
  aColor.setChans(2);                                              std::cout << "aColor.setChans(2);                            " << aColor << std::endl;
  aColor.setChans(vc2B);                                           std::cout << "aColor.setChans(vc2B);                         " << aColor << std::endl;

  aColor.setChan_dbl(0, 0.0);                                      std::cout << "aColor.setChan_dbl(0, 0.0);                    " << aColor << std::endl;
  aColor.setC0_dbl(0.0);                                           std::cout << "aColor.setC0_dbl(0.0);                         " << aColor << std::endl;
  aColor.setC1_dbl(0.0);                                           std::cout << "aColor.setC1_dbl(0.0);                         " << aColor << std::endl;
  aColor.setC3_dbl(0.0);                                           std::cout << "aColor.setC3_dbl(0.0);                         " << aColor << std::endl;
  aColor.setChans_dbl(0.8);                                        std::cout << "aColor.setChans_dbl(0.8);                      " << aColor << std::endl;

  aColor.setChan_byte(0, 0);                                       std::cout << "aColor.setChan_byte(0, 0);                     " << aColor << std::endl;
  aColor.setC0_byte(50);                                           std::cout << "aColor.setC0_byte(50);                         " << aColor << std::endl;
  aColor.setC1_byte(200);                                          std::cout << "aColor.setC1_byte(200);                        " << aColor << std::endl;
  aColor.setC3_byte(0);                                            std::cout << "aColor.setC3_byte(0);                          " << aColor << std::endl;
  aColor.setChans_byte(123);                                       std::cout << "aColor.setChans_byte(123);                     " << aColor << std::endl;

  aColor.tfrmSignDiff(bColor);                                    std::cout << "aColor.tfrmSignDiff(bColor);                  " << aColor << std::endl;
  aColor.tfrmOr(bColor);                                           std::cout << "aColor.tfrmOr(bColor);                         " << aColor << std::endl;
  aColor.tfrmNor(bColor);                                          std::cout << "aColor.tfrmNor(bColor);                        " << aColor << std::endl;
  aColor.tfrmCopy(bColor);                                         std::cout << "aColor.tfrmCopy(bColor);                       " << aColor << std::endl;
  aColor.tfrmAnd(bColor);                                          std::cout << "aColor.tfrmAnd(bColor);                        " << aColor << std::endl;
  aColor.tfrmNand(bColor);                                         std::cout << "aColor.tfrmNand(bColor);                       " << aColor << std::endl;
  aColor.tfrmXor(bColor);                                          std::cout << "aColor.tfrmXor(bColor);                        " << aColor << std::endl;
  aColor.tfrmNxor(bColor);                                         std::cout << "aColor.tfrmNxor(bColor);                       " << aColor << std::endl;
  aColor.tfrmNot();                                                std::cout << "aColor.tfrmNot();                              " << aColor << std::endl;
  aColor.tfrmMultClamp(bColor);                                      std::cout << "aColor.tfrmMultClamp(bColor);                    " << aColor << std::endl;
  aColor.tfrmAddClamp(bColor);                                       std::cout << "aColor.tfrmAddClamp(bColor);                     " << aColor << std::endl;
  aColor.tfrmAddDivClamp(bColor, cColor);                            std::cout << "aColor.tfrmAddDivClamp(bColor, cColor);          " << aColor << std::endl;
  aColor.tfrmDiffClamp(bColor);                                      std::cout << "aColor.tfrmDiffClamp(bColor);                    " << aColor << std::endl;
  aColor.tfrmNegDiffClamp(bColor);                                   std::cout << "aColor.tfrmNegDiffClamp(bColor);                 " << aColor << std::endl;
  aColor.tfrmAbsDiff(bColor);                                      std::cout << "aColor.tfrmAbsDiff(bColor);                    " << aColor << std::endl;
  aColor.tfrmSqDiff(bColor);                                       std::cout << "aColor.tfrmSqDiff(bColor);                     " << aColor << std::endl;
  aColor.tfrmMax(bColor);                                          std::cout << "aColor.tfrmMax(bColor);                        " << aColor << std::endl;
  aColor.tfrmMin(bColor);                                          std::cout << "aColor.tfrmMin(bColor);                        " << aColor << std::endl;
  aColor.tfrmAdd(bColor);                                          std::cout << "aColor.tfrmAdd(bColor);                        " << aColor << std::endl;
  aColor.tfrmDiv(bColor);                                          std::cout << "aColor.tfrmDiv(bColor);                        " << aColor << std::endl;
  aColor.tfrmMult(bColor);                                         std::cout << "aColor.tfrmMult(bColor);                       " << aColor << std::endl;
  aColor.tfrmMean(bColor);                                         std::cout << "aColor.tfrmMean(bColor);                       " << aColor << std::endl;
  aColor.tfrmDiff(bColor);                                         std::cout << "aColor.tfrmDiff(bColor);                       " << aColor << std::endl;
  aColor.tfrmMod(bColor);                                          std::cout << "aColor.tfrmMod(bColor);                        " << aColor << std::endl;
  aColor.tfrmMaxI(bColor);                                         std::cout << "aColor.tfrmMaxI(bColor);                       " << aColor << std::endl;
  aColor.tfrmMinI(bColor);                                         std::cout << "aColor.tfrmMinI(bColor);                       " << aColor << std::endl;

  aColor.setChansRGB(100, 200, 210);                               std::cout << "aColor.setChansRGB(100, 200, 210);             " << aColor << std::endl;
  aColor.setChansRGBA(100, 200, 210, 0);                           std::cout << "aColor.setChansRGBA(100, 200, 210, 0);         " << aColor << std::endl;
  bColor.setChansRGBA(1, 2, 3, 4);                                 std::cout << "bColor.setChansRGBA(1, 2, 3, 4);               " << bColor << std::endl;
  bColor.setChans(tc3);                                            std::cout << "bColor.setChans(tc3);                          " << bColor << std::endl;
  bColor.setChans(tc4);                                            std::cout << "bColor.setChans(tc4);                          " << bColor << std::endl;

  aColor.copy(bColor);                                             std::cout << "aColor.copy(bColor);                           " << aColor << std::endl;

  aColor.setChans("#010203");                                      std::cout << "aColor.setChans(#010203);                      " << aColor << std::endl;
  hColor.setChans("#1122");                                        std::cout << "hColor.setChans(#1122);                        " << hColor << std::endl;
  hColor.setChans("#1z22");                                        std::cout << "hColor.setChans(#1z22);                        " << hColor << std::endl;
  aColor.setChans("#010203");                                      std::cout << "aColor.setChans(#010203);                      " << aColor << std::endl;
  aColor.setToCorner("red");                                       std::cout << "aColor.setToCorner(red);                       " << aColor << std::endl;
  aColor.setToCorner("b");                                         std::cout << "aColor.setToCorner(b);                         " << aColor << std::endl;
  aColor.setToCorner("black");                                     std::cout << "aColor.setToCorner(black);                     " << aColor << std::endl;
  aColor.setToCorner("W");                                         std::cout << "aColor.setToCorner(W);                         " << aColor << std::endl;
  aColor.setToCorner("0");                                         std::cout << "aColor.setToCorner(0);                         " << aColor << std::endl;
  aColor.setChansRGBA_byte(100, 200, 210, 20);                     std::cout << "aColor.setChans_byte(100, 200, 210, 20);       " << aColor << std::endl;
  aColor.setChansRGB_byte(100, 200, 210);                          std::cout << "aColor.setChans_byte(100, 200, 210);           " << aColor << std::endl;
  aColor.setChansRGBA_dbl(0.5, 0.5, 0.5, 0.5);                     std::cout << "aColor.setChans_dbl(0.5, 0.5, 0.5, 0.5);       " << aColor << std::endl;
  aColor.setChansRGB_dbl(0.5, 0.5, 0.5);                           std::cout << "aColor.setChans_dbl(0.5, 0.5, 0.5);            " << aColor << std::endl;
  aColor.setRGBAfromLogPackIntABGR(123);                           std::cout << "aColor.setRGBAfromLogPackIntABGR(123);         " << aColor << std::endl;

  aColor.tfrmLinearGreyLevelScale(0.5, 0.1);                       std::cout << "aColor.tfrmLinearGreyLevelScale(0.5, 0.1);     " << aColor << std::endl;

  aColor.setRGBAfromLogPackIntARGB(0x01020304u);                   std::cout << "aColor.setRGBAfromLogPackIntARGB(0x01020304);  " << aColor << std::endl;

  aColor.setToBlack();                                             std::cout << "aColor.setToBlack();                           " << aColor << std::endl;
  aColor.setToWhite();                                             std::cout << "aColor.setToWhite();                           " << aColor << std::endl;
  aColor.setToRed();                                               std::cout << "aColor.setToRed();                             " << aColor << std::endl;
  aColor.setToGreen();                                             std::cout << "aColor.setToGreen();                           " << aColor << std::endl;
  aColor.setToBlue();                                              std::cout << "aColor.setToBlue();                            " << aColor << std::endl;
  aColor.setToCyan();                                              std::cout << "aColor.setToCyan();                            " << aColor << std::endl;
  aColor.setToYellow();                                            std::cout << "aColor.setToYellow();                          " << aColor << std::endl;
  aColor.setToMagenta();                                           std::cout << "aColor.setToMagenta();                         " << aColor << std::endl;
  aColor.setToCorner(mjr::colorRGBA8b::cornerColorEnum::BLACK);    std::cout << "aColor.setToCorner(::BLACK);                   " << aColor << std::endl;

  aColor.setRGBcmpGreyTGA16bit(1);                                 std::cout << "aColor.setRGBcmpGreyTGA16bit(1);               " << aColor << std::endl;

  jColor.setChan(0, 0);                                            std::cout << "jColor.setChan(0, 0);                          " << jColor << std::endl;
  jColor.setC0(0);                                                 std::cout << "jColor.setC0(!0);                              " << jColor << std::endl;
  jColor.setC1(0);                                                 std::cout << "jColor.setC1(0);                               " << jColor << std::endl;
  jColor.setC3(0);                                                 std::cout << "jColor.setC3(0);                               " << jColor << std::endl;
  jColor.setChans(2);                                              std::cout << "jColor.setChans(2);                            " << jColor << std::endl;
  jColor.setChans(vc2F);                                           std::cout << "jColor.setChans(vc2F);                         " << jColor << std::endl;

  jColor.setChan_dbl(0, 0.0);                                      std::cout << "jColor.setChan_dbl(0, 0.0);                    " << jColor << std::endl;
  jColor.setC0_dbl(0.0);                                           std::cout << "jColor.setC0_dbl(0.0);                         " << jColor << std::endl;
  jColor.setC1_dbl(0.0);                                           std::cout << "jColor.setC1_dbl(0.0);                         " << jColor << std::endl;
  jColor.setC3_dbl(0.0);                                           std::cout << "jColor.setC3_dbl(0.0);                         " << jColor << std::endl;
  jColor.setChans_dbl(0.8);                                        std::cout << "jColor.setChans_dbl(0.8);                      " << jColor << std::endl;

  jColor.setChan_byte(0, 0);                                       std::cout << "jColor.setChan_byte(0, 0);                     " << jColor << std::endl;
  jColor.setC0_byte(50);                                           std::cout << "jColor.setC0_byte(50);                         " << jColor << std::endl;
  jColor.setC1_byte(200);                                          std::cout << "jColor.setC1_byte(200);                        " << jColor << std::endl;
  jColor.setC3_byte(0);                                            std::cout << "jColor.setC3_byte(0);                          " << jColor << std::endl;
  jColor.setChans_byte(123);                                       std::cout << "jColor.setChans_byte(123);                     " << jColor << std::endl;

  jColor.tfrmSignDiff(kColor);                                    std::cout << "jColor.tfrmSignDiff(kColor);                  " << jColor << std::endl;
  jColor.tfrmOr(kColor);                                           std::cout << "jColor.tfrmOr(kColor);                         " << jColor << std::endl;
  jColor.tfrmNor(kColor);                                          std::cout << "jColor.tfrmNor(kColor);                        " << jColor << std::endl;
  jColor.tfrmCopy(kColor);                                         std::cout << "jColor.tfrmCopy(kColor);                       " << jColor << std::endl;
  jColor.tfrmAnd(kColor);                                          std::cout << "jColor.tfrmAnd(kColor);                        " << jColor << std::endl;
  jColor.tfrmNand(kColor);                                         std::cout << "jColor.tfrmNand(kColor);                       " << jColor << std::endl;
  jColor.tfrmXor(kColor);                                          std::cout << "jColor.tfrmXor(kColor);                        " << jColor << std::endl;
  jColor.tfrmNxor(kColor);                                         std::cout << "jColor.tfrmNxor(kColor);                       " << jColor << std::endl;
  jColor.tfrmNot();                                                std::cout << "jColor.tfrmNot();                              " << jColor << std::endl;
  jColor.tfrmMultClamp(kColor);                                      std::cout << "jColor.tfrmMultClamp(kColor);                    " << jColor << std::endl;
  jColor.tfrmAddClamp(kColor);                                       std::cout << "jColor.tfrmAddClamp(kColor);                     " << jColor << std::endl;
  jColor.tfrmAddDivClamp(kColor, lColor);                            std::cout << "jColor.tfrmAddDivClamp(kColor, lColor);          " << jColor << std::endl;
  jColor.tfrmDiffClamp(kColor);                                      std::cout << "jColor.tfrmDiffClamp(kColor);                    " << jColor << std::endl;
  jColor.tfrmNegDiffClamp(kColor);                                   std::cout << "jColor.tfrmNegDiffClamp(kColor);                 " << jColor << std::endl;
  jColor.tfrmAbsDiff(kColor);                                      std::cout << "jColor.tfrmAbsDiff(kColor);                    " << jColor << std::endl;
  jColor.tfrmSqDiff(kColor);                                       std::cout << "jColor.tfrmSqDiff(kColor);                     " << jColor << std::endl;
  jColor.tfrmMax(kColor);                                          std::cout << "jColor.tfrmMax(kColor);                        " << jColor << std::endl;
  jColor.tfrmMin(kColor);                                          std::cout << "jColor.tfrmMin(kColor);                        " << jColor << std::endl;
  jColor.tfrmAdd(kColor);                                          std::cout << "jColor.tfrmAdd(kColor);                        " << jColor << std::endl;
  jColor.tfrmDiv(kColor);                                          std::cout << "jColor.tfrmDiv(kColor);                        " << jColor << std::endl;
  jColor.tfrmMult(kColor);                                         std::cout << "jColor.tfrmMult(kColor);                       " << jColor << std::endl;
  jColor.tfrmGmean(kColor);                                        std::cout << "jColor.tfrmGmean(kColor);                      " << jColor << std::endl;
  jColor.tfrmMean(kColor);                                         std::cout << "jColor.tfrmMean(kColor);                       " << jColor << std::endl;
  jColor.tfrmDiff(kColor);                                         std::cout << "jColor.tfrmDiff(kColor);                       " << jColor << std::endl;
  jColor.tfrmMod(kColor);                                          std::cout << "jColor.tfrmMod(kColor);                        " << jColor << std::endl;
  jColor.tfrmMaxI(kColor);                                         std::cout << "jColor.tfrmMaxI(kColor);                       " << jColor << std::endl;
  jColor.tfrmMinI(kColor);                                         std::cout << "jColor.tfrmMinI(kColor);                       " << jColor << std::endl;

  jColor.setChansRGB(100, 200, 210);                               std::cout << "jColor.setChansRGB(100, 200, 210);             " << jColor << std::endl;
  jColor.setChansRGBA(100, 200, 210, 0);                           std::cout << "jColor.setChansRGBA(100, 200, 210, 0);         " << jColor << std::endl;
  kColor.setChansRGBA(1, 2, 3, 4);                                 std::cout << "kColor.setChansRGBA(1, 2, 3, 4);               " << kColor << std::endl;
  kColor.setChans(tc3);                                            std::cout << "kColor.setChans(tc3);                          " << kColor << std::endl;
  kColor.setChans(tc4);                                            std::cout << "kColor.setChans(tc4);                          " << kColor << std::endl;

  jColor.copy(kColor);                                             std::cout << "jColor.copy(kColor);                           " << jColor << std::endl;

  jColor.setChans("#010203");                                      std::cout << "jColor.setChans(#010203);                      " << jColor << std::endl;
  hColor.setChans("#1122");                                        std::cout << "hColor.setChans(#1122);                        " << hColor << std::endl;
  hColor.setChans("#1z22");                                        std::cout << "hColor.setChans(#1z22);                        " << hColor << std::endl;
  jColor.setChans("#010203");                                      std::cout << "jColor.setChans(#010203);                      " << jColor << std::endl;
  jColor.setToCorner("red");                                       std::cout << "jColor.setToCorner(red);                       " << jColor << std::endl;
  jColor.setToCorner("b");                                         std::cout << "jColor.setToCorner(b);                         " << jColor << std::endl;
  jColor.setToCorner("black");                                     std::cout << "jColor.setToCorner(black);                     " << jColor << std::endl;
  jColor.setToCorner("W");                                         std::cout << "jColor.setToCorner(W);                         " << jColor << std::endl;
  jColor.setToCorner("0");                                         std::cout << "jColor.setToCorner(0);                         " << jColor << std::endl;
  jColor.setChansRGBA_byte(100, 200, 210, 20);                     std::cout << "jColor.setChansRGBA_byte(100, 200, 210, 20);   " << jColor << std::endl;
  jColor.setChansRGB_byte(100, 200, 210);                          std::cout << "jColor.setChansRGB_byte(100, 200, 210);        " << jColor << std::endl;
  jColor.setChansRGBA_dbl(0.5, 0.5, 0.5, 0.5);                     std::cout << "jColor.setChansRGBA_dbl(0.5, 0.5, 0.5, 0.5);   " << jColor << std::endl;
  jColor.setChansRGB_dbl(0.5, 0.5, 0.5);                           std::cout << "jColor.setChansRGB_dbl(0.5, 0.5, 0.5);         " << jColor << std::endl;
  jColor.setRGBAfromLogPackIntABGR(123);                           std::cout << "jColor.setRGBAfromLogPackIntABGR(123);         " << jColor << std::endl;

  jColor.tfrmLinearGreyLevelScale(0.5, 0.1);                       std::cout << "jColor.tfrmLinearGreyLevelScale(0.5, 0.1);     " << jColor << std::endl;

  jColor.setRGBAfromLogPackIntARGB(0x01020304u);                   std::cout << "jColor.setRGBAfromLogPackIntARGB(0x01020304);  " << jColor << std::endl;

  jColor.setToBlack();                                             std::cout << "jColor.setToBlack();                           " << jColor << std::endl;
  jColor.setToWhite();                                             std::cout << "jColor.setToWhite();                           " << jColor << std::endl;
  jColor.setToRed();                                               std::cout << "jColor.setToRed();                             " << jColor << std::endl;
  jColor.setToGreen();                                             std::cout << "jColor.setToGreen();                           " << jColor << std::endl;
  jColor.setToBlue();                                              std::cout << "jColor.setToBlue();                            " << jColor << std::endl;
  jColor.setToCyan();                                              std::cout << "jColor.setToCyan();                            " << jColor << std::endl;
  jColor.setToYellow();                                            std::cout << "jColor.setToYellow();                          " << jColor << std::endl;
  jColor.setToMagenta();                                           std::cout << "jColor.setToMagenta();                         " << jColor << std::endl;
  jColor.setToCorner(mjr::colorRGBA32F::cornerColorEnum::BLACK);   std::cout << "jColor.setToCorner(::BLACK);                   " << jColor << std::endl;

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
