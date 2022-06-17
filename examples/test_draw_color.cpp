// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      test_draw_color.cpp
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

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

int main(void) {
  mjr::colorRGBA8b aColor(255, 200, 100);
  mjr::colorRGBA8b bColor(255, 200, 100, 20);
  mjr::colorRGBA8b cColor(255, 200, 100, 100);

  std::cout << aColor << std::endl;
  std::cout << "red 8b: " << (int)aColor.getRed8bit() << std::endl;
  std::cout << "red F:  " << (double)aColor.getRedF() << std::endl;

  std::cout << "MaxC:   " << (int)aColor.getMaxC()    << std::endl;  
  std::cout << "MinC:   " << (int)aColor.getMinC()    << std::endl;  
  std::cout << "MaxRGB: " << (int)aColor.getMaxRGB()  << std::endl;  
  std::cout << "MinRGB: " << (int)aColor.getMinRGB()  << std::endl;  

  aColor.setChan(0, 0);                                            std::cout << "aColor.setChan(0, 0);                        " << aColor << std::endl;
  aColor.setRed(0);                                                std::cout << "aColor.setRed(0);                            " << aColor << std::endl;
  aColor.setGreen(0);                                              std::cout << "aColor.setGreen(0);                          " << aColor << std::endl;
  aColor.setAlpha(0);                                              std::cout << "aColor.setAlpha(0);                          " << aColor << std::endl;
  aColor.setAll(2);                                                std::cout << "aColor.setAll(2);                            " << aColor << std::endl;
                                                                                                                              
  aColor.setChanF(0, 0.0);                                         std::cout << "aColor.setChanF(0, 0.0);                     " << aColor << std::endl;
  aColor.setRedF(0.0);                                             std::cout << "aColor.setRedF(0.0);                         " << aColor << std::endl;
  aColor.setGreenF(0.0);                                           std::cout << "aColor.setGreenF(0.0);                       " << aColor << std::endl;
  aColor.setAlphaF(0.0);                                           std::cout << "aColor.setAlphaF(0.0);                       " << aColor << std::endl;
  aColor.setAllF(0.8F);                                            std::cout << "aColor.setAllF(0.8F);                        " << aColor << std::endl;
                                                                                                                              
  aColor.setChan64bit(0, 255, 255);                                std::cout << "aColor.setChan64bit(0, 255, 255);            " << aColor << std::endl;
  aColor.setRed64bit(255, 255);                                    std::cout << "aColor.setRed64bit(255, 255);                " << aColor << std::endl;
  aColor.setGreen64bit(255, 255);                                  std::cout << "aColor.setGreen64bit(255, 255);              " << aColor << std::endl;
  aColor.setAlpha64bit(255, 255);                                  std::cout << "aColor.setAlpha64bit(255, 255);              " << aColor << std::endl;
  aColor.setAll64bit(255, 255);                                    std::cout << "aColor.setAll64bit(255, 255);                " << aColor << std::endl;
                                                                                                                              
  aColor.setChan8bit(0, 0);                                        std::cout << "aColor.setChan8bit(0, 0);                    " << aColor << std::endl;
  aColor.setRed8bit(50);                                           std::cout << "aColor.setRed8bit(50);                       " << aColor << std::endl;
  aColor.setGreen8bit(200);                                        std::cout << "aColor.setGreen8bit(200);                    " << aColor << std::endl;
  aColor.setAlpha8bit(0);                                          std::cout << "aColor.setAlpha8bit(0);                      " << aColor << std::endl;
  aColor.setAll8bit(123);                                          std::cout << "aColor.setAll8bit(123);                      " << aColor << std::endl;
                                                                                                                              
  aColor.ScaleSignDiff(bColor);                                    std::cout << "aColor.ScaleSignDiff(bColor);                " << aColor << std::endl;
  aColor.tfrmOr(bColor);                                           std::cout << "aColor.tfrmOr(bColor);                       " << aColor << std::endl;
  aColor.tfrmNor(bColor);                                          std::cout << "aColor.tfrmNor(bColor);                      " << aColor << std::endl;
  aColor.tfrmCopy(bColor);                                         std::cout << "aColor.tfrmCopy(bColor);                     " << aColor << std::endl;
  aColor.tfrmAnd(bColor);                                          std::cout << "aColor.tfrmAnd(bColor);                      " << aColor << std::endl;
  aColor.tfrmNand(bColor);                                         std::cout << "aColor.tfrmNand(bColor);                     " << aColor << std::endl;
  aColor.tfrmXor(bColor);                                          std::cout << "aColor.tfrmXor(bColor);                      " << aColor << std::endl;
  aColor.tfrmNxor(bColor);                                         std::cout << "aColor.tfrmNxor(bColor);                     " << aColor << std::endl;
  aColor.tfrmNot();                                                std::cout << "aColor.tfrmNot();                            " << aColor << std::endl;
  aColor.tfrmMultClp(bColor);                                      std::cout << "aColor.tfrmMultClp(bColor);                  " << aColor << std::endl;
  aColor.tfrmGmeanClp(bColor);                                     std::cout << "aColor.tfrmGmeanClp(bColor);                 " << aColor << std::endl;
  aColor.tfrmAddClp(bColor);                                       std::cout << "aColor.tfrmAddClp(bColor);                   " << aColor << std::endl;
  aColor.tfrmAddDivClp(bColor, cColor);                            std::cout << "aColor.tfrmAddDivClp(bColor, cColor);        " << aColor << std::endl;
  aColor.tfrmDiffClp(bColor);                                      std::cout << "aColor.tfrmDiffClp(bColor);                  " << aColor << std::endl;
  aColor.tfrmNegDiffClp(bColor);                                   std::cout << "aColor.tfrmNegDiffClp(bColor);               " << aColor << std::endl;
  aColor.tfrmAbsDiff(bColor);                                      std::cout << "aColor.tfrmAbsDiff(bColor);                  " << aColor << std::endl;
  aColor.tfrmSqDiff(bColor);                                       std::cout << "aColor.tfrmSqDiff(bColor);                   " << aColor << std::endl;
  aColor.tfrmMax(bColor);                                          std::cout << "aColor.tfrmMax(bColor);                      " << aColor << std::endl;
  aColor.tfrmMin(bColor);                                          std::cout << "aColor.tfrmMin(bColor);                      " << aColor << std::endl;
  aColor.tfrmAdd(bColor);                                          std::cout << "aColor.tfrmAdd(bColor);                      " << aColor << std::endl;
  aColor.tfrmDiv(bColor);                                          std::cout << "aColor.tfrmDiv(bColor);                      " << aColor << std::endl;
  aColor.tfrmMult(bColor);                                         std::cout << "aColor.tfrmMult(bColor);                     " << aColor << std::endl;
  aColor.tfrmGmean(bColor);                                        std::cout << "aColor.tfrmGmean(bColor);                    " << aColor << std::endl;
  aColor.tfrmMean(bColor);                                         std::cout << "aColor.tfrmMean(bColor);                     " << aColor << std::endl;
  aColor.tfrmDiff(bColor);                                         std::cout << "aColor.tfrmDiff(bColor);                     " << aColor << std::endl;
  aColor.tfrmMod(bColor);                                          std::cout << "aColor.tfrmMod(bColor);                      " << aColor << std::endl;
  aColor.tfrmMaxI(bColor);                                         std::cout << "aColor.tfrmMaxI(bColor);                     " << aColor << std::endl;
  aColor.tfrmMinI(bColor);                                         std::cout << "aColor.tfrmMinI(bColor);                     " << aColor << std::endl;
                                                                                                                              
  aColor.setColorRGB(100, 200, 210);                               std::cout << "aColor.setColorRGB(100, 200, 210);           " << aColor << std::endl; 
  aColor.setColorRGBA(100, 200, 210, 0);                           std::cout << "aColor.setColorRGBA(100, 200, 210, 0);       " << aColor << std::endl;
  bColor.setColorRGBA(0, 0, 0, 0);                                 std::cout << "bColor.setColorRGBA(0, 0, 0, 0);             " << bColor << std::endl;
  aColor.setColorFromColor(bColor);                                std::cout << "aColor.setColorFromColor(bColor);            " << aColor << std::endl;
  aColor.setColorFromString("#010203");                            std::cout << "aColor.setColorFromString(#010203);          " << aColor << std::endl;
  aColor.setColorFromString("red");                                std::cout << "aColor.setColorFromString(red);              " << aColor << std::endl;
  aColor.setColorFrom8bit(100, 200, 210, 20);                      std::cout << "aColor.setColorFrom8bit(100, 200, 210, 20);  " << aColor << std::endl;
  aColor.setColorFrom8bit(100, 200, 210);                          std::cout << "aColor.setColorFrom8bit(100, 200, 210);      " << aColor << std::endl;
  aColor.setColorFromF(0.5, 0.5, 0.5, 0.5);                        std::cout << "aColor.setColorFromF(0.5, 0.5, 0.5, 0.5);    " << aColor << std::endl;
  aColor.setColorFromF(0.5, 0.5, 0.5);                             std::cout << "aColor.setColorFromF(0.5, 0.5, 0.5);         " << aColor << std::endl;
  aColor.setColorFromPackedIntABGR(123);                           std::cout << "aColor.setColorFromPackedIntABGR(123);       " << aColor << std::endl;
  
  aColor.tfrmLinearGreyLevelScale(0.5F, 0.1F);                     std::cout << "aColor.tfrmLinearGreyLevelScale(0.5F, 0.1F); " << aColor << std::endl;

  aColor.setChanToMin();                                           std::cout << "aColor.setChanToMin();                       " << aColor << std::endl;
  aColor.setChanToMax();                                           std::cout << "aColor.setChanToMax();                       " << aColor << std::endl;
  aColor.setToBlack();                                             std::cout << "aColor.setToBlack();                         " << aColor << std::endl;
  aColor.setToWhite();                                             std::cout << "aColor.setToWhite();                         " << aColor << std::endl;
  aColor.setToRed();                                               std::cout << "aColor.setToRed();                           " << aColor << std::endl;
  aColor.setToGreen();                                             std::cout << "aColor.setToGreen();                         " << aColor << std::endl;
  aColor.setToBlue();                                              std::cout << "aColor.setToBlue();                          " << aColor << std::endl;
  aColor.setToCyan();                                              std::cout << "aColor.setToCyan();                          " << aColor << std::endl;
  aColor.setToYellow();                                            std::cout << "aColor.setToYellow();                        " << aColor << std::endl;
  aColor.setToMagenta();                                           std::cout << "aColor.setToMagenta();                       " << aColor << std::endl;
                                                                                                                              
  aColor.setColorFromCorner(mjr::colorRGBA8b::cornerColor::BLACK); std::cout << "aColor.setColorFromCorner(::BLACK);          " << aColor << std::endl;
  aColor.cmpGreyTGA16bit(1);                                       std::cout << "aColor.cmpGreyTGA16bit(1);                   " << aColor << std::endl;
}
