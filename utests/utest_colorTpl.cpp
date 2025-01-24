// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      utest_colorTpl.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-08-11
 @brief     Unit tests for basic color methods.@EOL
 @keywords  boost
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 2022, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.

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
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

#include <gtest/gtest.h>

#include "ramCanvas.hpp"

// |----------+--------------------------------------------------------------------------------------------------------------|
// | Coverage | Method                                                                                                       |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | colorTpl();                                                                                                  |
// | DIRECT   | colorTpl(const colorType& aColor);                                                                           |
// | DIRECT   | colorTpl(clrChanT c1, clrChanT c2, clrChanT c3, clrChanT c4);                                                |
// | DIRECT   | colorTpl(clrChanT c1, clrChanT c2, clrChanT c3);                                                             |
// | DIRECT   | colorTpl(clrChanT c1, clrChanT c2);                                                                          |
// | DIRECT   | colorTpl(clrChanT cVal);                                                                                     |
// | DIRECT   | colorTpl(cornerColorEnum cornerColor);                                                                       |
// | DIRECT   | colorTpl(std::string colorString);                                                                           |
// | DIRECT   | colorTpl(const char* colorCString);                                                                          |
// | INDIRECT | ~colorTpl();                                                                                                 |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | INDIRECT | colorTpl& copy(colorArgType aCol);                                                                           |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | getC0() const;                                                                                               |
// | DIRECT   | getC1() const;                                                                                               |
// | DIRECT   | getC2() const;                                                                                               |
// | DIRECT   | getC3() const;                                                                                               |
// | DIRECT   | getChan(int chan) const;                                                                                     |
// | DIRECT   | setC0(clrChanT cVal);                                                                                        |
// | DIRECT   | setC1(clrChanT cVal);                                                                                        |
// | DIRECT   | setC2(clrChanT cVal);                                                                                        |
// | DIRECT   | setC3(clrChanT cVal);                                                                                        |
// | DIRECT   | setChan(int chan, clrChanT cVal);                                                                            |
// | INDIRECT | setChanToMax(int chan);                                                                                      |
// | INDIRECT | setChanToMin(int chan);                                                                                      |
// | DIRECT   | setChans(clrChanT c1, clrChanT c2, clrChanT c3, clrChanT c4);                                                |
// | DIRECT   | setChans(clrChanT c1, clrChanT c2, clrChanT c3);                                                             |
// | DIRECT   | setChans(clrChanT c1, clrChanT c2);                                                                          |
// | DIRECT   | setChans(clrChanT cVal);                                                                                     |
// | INDIRECT | setChans(std::tuple<clrChanT, clrChanT, clrChanT, clrChanT> chanValues);                                     |
// | INDIRECT | setChans(std::tuple<clrChanT, clrChanT, clrChanT> chanValues);                                               |
// |          | setChans(std::vector<clrChanT>& chanValues);                                                                 |
// | DIRECT   | setChans(std::string colorHexString, bool clearUndefinedChannels = false);                                   |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | getC0_dbl() const;                                                                                           |
// | DIRECT   | getC1_dbl() const;                                                                                           |
// | DIRECT   | getC2_dbl() const;                                                                                           |
// | DIRECT   | getC3_dbl() const;                                                                                           |
// | DIRECT   | getChan_dbl(int chan) const;                                                                                 |
// | DIRECT   | setChan_dbl(int chan, double cVal);                                                                          |
// | DIRECT   | setC0_dbl(double cVal);                                                                                      |
// | DIRECT   | setC1_dbl(double cVal);                                                                                      |
// | DIRECT   | setC2_dbl(double cVal);                                                                                      |
// | DIRECT   | setC3_dbl(double cVal);                                                                                      |
// | DIRECT   | setChans_dbl(double c1, double c2, double c3, double c4);                                                    |
// | DIRECT   | setChans_dbl(double c1, double c2, double c3);                                                               |
// | DIRECT   | setChans_dbl(double c1, double c2);                                                                          |
// | DIRECT   | setChans_dbl(double cVal);                                                                                   |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | bestRedChan()                                                                                                |
// | DIRECT   | bestGreenChan()                                                                                              |
// | DIRECT   | bestBlueChan()                                                                                               |
// | DIRECT   | bestAlphaChan()                                                                                              |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | setChans_dbl(colConALLdbl dblColor)                                                                          |
// | DIRECT   | setChans_byte(colConALLbyte byteColor)                                                                       |
// | DIRECT   | setChansRGBA_dbl(colConRGBAdbl dblColor)                                                                     |
// | DIRECT   | setChansRGB_dbl(colConRGBdbl dblColor)                                                                       |
// | DIRECT   | setChansRGBA_byte(colConRGBAbyte byteColor)                                                                  |
// | DIRECT   | setChansRGB_byte(colConRGBbyte byteColor)                                                                    |
// | DIRECT   | getColCon_dbl()                                                                                              |
// | DIRECT   | getColCon_byte()                                                                                             |
// | DIRECT   | getColConRGBA_dbl()                                                                                          |
// | DIRECT   | getColConRGB_dbl()                                                                                           |
// | DIRECT   | getColConRGBA_byte()                                                                                         |
// | DIRECT   | getColConRGB_byte()                                                                                          |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | getC0_byte() const;                                                                                          |
// | DIRECT   | getC1_byte() const;                                                                                          |
// | DIRECT   | getC2_byte() const;                                                                                          |
// | DIRECT   | getC3_byte() const;                                                                                          |
// | DIRECT   | getChan_byte(int chan) const;                                                                                |
// | DIRECT   | setChan_byte(int chan, uint8_t cVal);                                                                        |
// | DIRECT   | setC0_byte(uint8_t cVal);                                                                                    |
// | DIRECT   | setC1_byte(uint8_t cVal);                                                                                    |
// | DIRECT   | setC2_byte(uint8_t cVal);                                                                                    |
// | DIRECT   | setC3_byte(uint8_t cVal);                                                                                    |
// | DIRECT   | setChans_byte(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4);                                               |
// | DIRECT   | setChans_byte(uint8_t c1, uint8_t c2, uint8_t c3);                                                           |
// | DIRECT   | setChans_byte(uint8_t c1, uint8_t c2);                                                                       |
// | DIRECT   | setChans_byte(uint8_t cVal);                                                                                 |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | setToBlack();                                                                                                |
// | DIRECT   | setToWhite();                                                                                                |
// | DIRECT   | setToRed();                                                                                                  |
// | DIRECT   | setToBlue();                                                                                                 |
// | DIRECT   | setToGreen();                                                                                                |
// | DIRECT   | setToCyan();                                                                                                 |
// | DIRECT   | setToYellow();                                                                                               |
// | DIRECT   | setToMagenta();                                                                                              |
// | DIRECT   | setToCorner(char cornerColor);                                                                               |
// | DIRECT   | setToCorner(cornerColorEnum cornerColor);                                                                    |
// | DIRECT   | setToCorner(std::string cornerColor);                                                                        |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | setRGBAfromLogPackIntABGR(packed4Cint anInt)                                                                 |
// | DIRECT   | setRGBfromLogPackIntABGR( packed4Cint anInt)                                                                 |
// | DIRECT   | setRGBAfromLogPackIntARGB(packed4Cint anInt)                                                                 |
// | DIRECT   | setRGBfromLogPackIntARGB( packed4Cint anInt)                                                                 |
// | DIRECT   | setRGBAfromLogPackIntRGBA(packed4Cint anInt)                                                                 |
// | DIRECT   | setRGBfromLogPackIntRGBA( packed4Cint anInt)                                                                 |
// | DIRECT   | setRGBAfromLogPackIntABRG(packed4Cint anInt)                                                                 |
// | DIRECT   | setRGBfromLogPackIntABRG( packed4Cint anInt)                                                                 |
// | DIRECT   | setRGBAfromLogPackIntBGRA(packed4Cint anInt)                                                                 |
// | DIRECT   | setRGBfromLogPackIntBGRA( packed4Cint anInt)                                                                 |
// | INDIRECT | setRGBAfromLogPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx);            |
// | INDIRECT | setRGBfromLogPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx);                           |
// |          | setRGBAfromPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx);               |
// |          | setRGBfromPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx);                              |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | setRGBfromUnitHSV(double H, double S, double V);                                                             |
// | DIRECT   | setRGBfromUnitHSL(double H, double S, double L);                                                             |
// | DIRECT   | setRGBfromColorSpace(colorSpaceEnum space, double inCh1, double inCh2, double inCh3);                        |
// | SIMILAR  | setRGBfromColorSpace(colorSpaceEnum space, colorTpl<double, 3> inColor);                                     |
// |          | interplColorSpace(colorSpaceEnum space, double aDouble, colorArgType col1, colorArgType col2);               |
// | DIRECT   | rgb2colorSpace(colorSpaceEnum space);                                                                        |
// |          | colorSpaceToString(colorSpaceEnum space);                                                                    |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | setRGBcmpGreyTGA16bit(uint16_t tga16val);                                                                    |
// | DIRECT   | setRGBcmpGreyTGA24bit(uint32_t tga24val);                                                                    |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | setRGBfromWavelengthCM(double wavelength, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR); |
// | DIRECT   | setRGBfromWavelengthLA(double wavelength);                                                                   |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | cmpGradiant(csFltType csX, std::vector<csFltType> const& anchors, std::vector<colorType> const& colors);     |
// |          | cmpGradiant(csFltType csX, std::vector<colorType> const& colors);                                            |
// | INDIRECT | cmpGradiant(csFltType csX, csIntType numColors, const packed4Cint* colors)                                   |
// | DIRECT   | cmpRGBcornerDGradiant(csIntType csIdx, const char *cornerColors);                                            |
// | INDIRECT | cmpRGBcornerDGradiant(csIntType csIdx, csIntType numColors, const ccT* cornerColors)                         |
// | DIRECT   | cmpRGBcornerCGradiant(csFltType csX, const char *cornerColors) {                                             |
// | INDIRECT | cmpRGBcornerCGradiant(csFltType csX, csIntType numColors, const ccT* cornerColors)                           |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | wMean( 8 args                                                                                                |
// | DIRECT   | wMean( 6 args                                                                                                |
// | DIRECT   | wMean( 4 args                                                                                                |
// | DIRECT   | uMean( 7 args                                                                                                |
// | DIRECT   | uMean( 5 args                                                                                                |
// | DIRECT   | uMean( 3 args                                                                                                |
// | DIRECT   | linearInterpolate(double aDouble, colorArgType col1, colorArgType col2);                                     |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | tfrmOr(colorArgType aCol)         No coverage for floating point clrChanT                                    |
// | DIRECT   | tfrmNor(colorArgType aCol)        No coverage for floating point clrChanT                                    |
// | DIRECT   | tfrmAnd(colorArgType aCol)        No coverage for floating point clrChanT                                    |
// | DIRECT   | tfrmNand(colorArgType aCol)       No coverage for floating point clrChanT                                    |
// | DIRECT   | tfrmXor(colorArgType aCol)        No coverage for floating point clrChanT                                    |
// | DIRECT   | tfrmNxor(colorArgType aCol)       No coverage for floating point clrChanT                                    |
// | DIRECT   | tfrmNot(void)                     No coverage for floating point clrChanT                                    |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | tfrmSqDiff(colorArgType aCol);                                                                               |
// | DIRECT   | tfrmAbsDiff(colorArgType aCol);                                                                              |
// | DIRECT   | tfrmAdd(colorArgType aCol);                                                                                  |
// | DIRECT   | tfrmDiv(colorArgType aCol);                                                                                  |
// | DIRECT   | tfrmMult(colorArgType aCol);                                                                                 |
// | DIRECT   | tfrmMultClamp(colorArgType aCol);                                                                            |
// | DIRECT   | tfrmSignDiff(colorArgType aCol);                                                                             |
// | DIRECT   | tfrmDiffClamp(colorArgType aCol);                                                                            |
// | DIRECT   | tfrmNegDiffClamp(colorArgType aCol);                                                                         |
// | DIRECT   | tfrmAddClamp(colorArgType aCol);                                                                             |
// | DIRECT   | tfrmAddDivClamp(colorArgType aCol, colorArgType dCol);                                                       |
// | DIRECT   | tfrmDiff(colorArgType aCol);                                                                                 |
// | DIRECT   | tfrmMod(colorArgType aCol)                                                                                   |
// | DIRECT   | tfrmInvert();                                                                                                |
// | DIRECT   | tfrmMix(double aDouble, colorArgType tooCol);                                                                |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | tfrmCopy(colorArgType aCol);                                                                                 |
// | DIRECT   | tfrmMaxI(colorArgType aCol);                                                                                 |
// | DIRECT   | tfrmMinI(colorArgType aCol);                                                                                 |
// | DIRECT   | tfrmMax(colorArgType aCol);                                                                                  |
// | DIRECT   | tfrmMin(colorArgType aCol);                                                                                  |
// | DIRECT   | tfrmShiftL(colorArgType aCol)                                                                                |
// | DIRECT   | tfrmShiftR(colorArgType aCol)                                                                                |
// | DIRECT   | tfrmSaw(colorArgType lowCol, colorArgType highCol);                                                          |
// | DIRECT   | tfrmStep(colorArgType lowCol, colorArgType highCol);                                                         |
// | DIRECT   | tfrmDiracTot(colorArgType aCol);                                                                             |
// | DIRECT   | tfrmDirac(colorArgType aCol);                                                                                |
// | DIRECT   | tfrmFuzzyDirac(colorArgType ctrCol, colorArgType radCol);                                                    |
// | DIRECT   | tfrmMean(colorArgType aCol);                                                                                 |
// | DIRECT   | tfrmGmean(colorArgType aCol);                                                                                |
// | DIRECT   | tfrmGmeanClamp(colorArgType aCol);                                                                           |
// | DIRECT   | tfrmGreyScaleRGB(void);                                                                                      |
// | DIRECT   | tfrmWebSafeRGB();                                                                                            |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | tfrmLinearGreyLevelScale(double c, double b);                                                                |
// | DIRECT   | tfrmLinearGreyLevelScaleRGB(double rc, double rb, double gc, double gb, double bc, double bb);               |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | tfrmStdPow(double p);                                                                                        |
// | DIRECT   | tfrmStdPowRGB(double rp, double gp, double bp);                                                              |
// | DIRECT   | tfrmStdPowSqr(void);                                                                                         |
// | DIRECT   | tfrmStdPowSqrt(void);                                                                                        |
// | DIRECT   | tfrmLn();                                                                                                    |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | rgb2GreyDotProd(channelArithSDPType redWt, channelArithSDPType greenWt, channelArithSDPType blueWt);         |
// | DIRECT   | luminanceRGB(void);                                                                                          |
// | DIRECT   | intensityRGB(void);                                                                                          |
// | DIRECT   | intensity(void);                                                                                             |
// | DIRECT   | intensityScaledRGB(void);                                                                                    |
// | DIRECT   | intensityScaled(void);                                                                                       |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | getMaxC();                                                                                                   |
// | DIRECT   | getMinC();                                                                                                   |
// | DIRECT   | getMaxRGB();                                                                                                 |
// | DIRECT   | getMinRGB();                                                                                                 |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | dotProd(colorArgType aColor);                                                                                |
// | DIRECT   | distHypot(colorArgType aColor);                                                                              |
// | DIRECT   | distSumAbs(colorArgType aColor);                                                                             |
// | DIRECT   | distMaxAbs(colorArgType aColor);                                                                             |
// | DIRECT   | distDeltaE1976(colorArgType aColor);                                                                         |
// | DIRECT   | distDeltaE1994(colorArgType aColor);                                                                         |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | isEqual(colorArgType aColor);                                                                                |
// | DIRECT   | isEqualRGB(colorArgType aColor);                                                                             |
// | DIRECT   | isClose                                                                                                      |
// | DIRECT   | isCloseRGB                                                                                                   |
// | DIRECT   | isNotEqual(colorArgType aColor);                                                                             |
// | DIRECT   | isBlack();                                                                                                   |
// | DIRECT   | isBlackRGB();                                                                                                |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | INDIRECT | clampTop(iT arithValue);                                                                                     |
// | INDIRECT | clampBot(iT arithValue);                                                                                     |
// | INDIRECT | clampAll(iT arithValue);                                                                                     |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | csBin01                                                                                                      |
// | SIMILAR  | csBinGB                                                                                                      |
// | SIMILAR  | csBinRB                                                                                                      |
// | SIMILAR  | csBinMC                                                                                                      |
// | SIMILAR  | csBinYC                                                                                                      |
// | SIMILAR  | csBinRG                                                                                                      |
// | SIMILAR  | csBinMY                                                                                                      |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | INDIRECT | csBin_tpl                                                                                                    |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | SIMILAR  | csCBAccent                                                                                                   |
// | SIMILAR  | csCBBlues                                                                                                    |
// | SIMILAR  | csCBBrBG                                                                                                     |
// | SIMILAR  | csCBBuGn                                                                                                     |
// | SIMILAR  | csCBBuPu                                                                                                     |
// | SIMILAR  | csCBDark2                                                                                                    |
// | SIMILAR  | csCBGnBu                                                                                                     |
// | SIMILAR  | csCBGreens                                                                                                   |
// | SIMILAR  | csCBGreys                                                                                                    |
// | SIMILAR  | csCBOrRd                                                                                                     |
// | SIMILAR  | csCBOranges                                                                                                  |
// | SIMILAR  | csCBPRGn                                                                                                     |
// | SIMILAR  | csCBPaired                                                                                                   |
// | SIMILAR  | csCBPastel1                                                                                                  |
// | SIMILAR  | csCBPastel2                                                                                                  |
// | SIMILAR  | csCBPiYG                                                                                                     |
// | SIMILAR  | csCBPuBu                                                                                                     |
// | SIMILAR  | csCBPuBuGn                                                                                                   |
// | SIMILAR  | csCBPuOr                                                                                                     |
// | SIMILAR  | csCBPuRd                                                                                                     |
// | SIMILAR  | csCBPurples                                                                                                  |
// | SIMILAR  | csCBRdBu                                                                                                     |
// | SIMILAR  | csCBRdGy                                                                                                     |
// | SIMILAR  | csCBRdPu                                                                                                     |
// | SIMILAR  | csCBRdYlBu                                                                                                   |
// | SIMILAR  | csCBRdYlGn                                                                                                   |
// | SIMILAR  | csCBReds                                                                                                     |
// | SIMILAR  | csCBSet1                                                                                                     |
// | SIMILAR  | csCBSet2                                                                                                     |
// | SIMILAR  | csCBSet3                                                                                                     |
// | DIRECT   | csCBSpectral                                                                                                 |
// | SIMILAR  | csCBYlGn                                                                                                     |
// | SIMILAR  | csCBYlGnBu                                                                                                   |
// | SIMILAR  | csCBYlOrBr                                                                                                   |
// | SIMILAR  | csCBYlOrRd                                                                                                   |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | INDIRECT | csCB_tpl                                                                                                     |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | INDIRECT | csCC_tpl                                                                                                     |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | SIMILAR  | csCCconsOne                                                                                                  |
// | SIMILAR  | csCCconsTwo                                                                                                  |
// | SIMILAR  | csCCdiag01                                                                                                   |
// | SIMILAR  | csCCdiagCR                                                                                                   |
// | SIMILAR  | csCCdiagMG                                                                                                   |
// | SIMILAR  | csCCdiagYB                                                                                                   |
// | SIMILAR  | csCColdeColdToHot                                                                                            |
// | SIMILAR  | csCColdeFireRamp                                                                                             |
// | SIMILAR  | csCColdeIceToWaterToHot                                                                                      |
// | DIRECT   | csCColdeRainbow                                                                                              |
// | SIMILAR  | csCCsumBGR                                                                                                   |
// | SIMILAR  | csCCsumBRG                                                                                                   |
// | SIMILAR  | csCCsumGBR                                                                                                   |
// | SIMILAR  | csCCsumGRB                                                                                                   |
// | SIMILAR  | csCCsumRBG                                                                                                   |
// | SIMILAR  | csCCsumRGB                                                                                                   |
// | SIMILAR  | csCCudBg                                                                                                     |
// | SIMILAR  | csCCudBr                                                                                                     |
// | SIMILAR  | csCCudGb                                                                                                     |
// | SIMILAR  | csCCudGr                                                                                                     |
// | SIMILAR  | csCCudRb                                                                                                     |
// | SIMILAR  | csCCudRg                                                                                                     |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | csCHblu                                                                                                      |
// | DIRECT   | csCHstd                                                                                                      |
// | DIRECT   | csCHvio                                                                                                      |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | INDIRECT | csCubeHelix_tpl                                                                                              |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | INDIRECT | csFP_tpl                                                                                                     |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | SIMILAR  | csFPblAqGrYeOrReVi200                                                                                        |
// | DIRECT   | csFPcircular12                                                                                               |
// | SIMILAR  | csFPcircular24                                                                                               |
// | SIMILAR  | csFPcmoceanAlgae                                                                                             |
// | SIMILAR  | csFPcmoceanAmp                                                                                               |
// | SIMILAR  | csFPcmoceanBalance                                                                                           |
// | SIMILAR  | csFPcmoceanCurl                                                                                              |
// | SIMILAR  | csFPcmoceanDeep                                                                                              |
// | SIMILAR  | csFPcmoceanDense                                                                                             |
// | SIMILAR  | csFPcmoceanHaline                                                                                            |
// | SIMILAR  | csFPcmoceanIce                                                                                               |
// | SIMILAR  | csFPcmoceanTempo                                                                                             |
// | SIMILAR  | csFPmplBrBG                                                                                                  |
// | SIMILAR  | csFPmplOcean                                                                                                 |
// | SIMILAR  | csFPmplOranges                                                                                               |
// | SIMILAR  | csFPneoDdivVegetationA                                                                                       |
// | SIMILAR  | csFPneoDivVegetationC                                                                                        |
// | SIMILAR  | csFPneoModisNdvi                                                                                             |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | csWS_tpl                                                                                                     |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | csWSnormalVision                                                                                             |
// |          | csWSprotanopia                                                                                               |
// |          | csWSdeutanopia                                                                                               |
// |          | csWStritanoptia                                                                                              |
// |          | csWSprotanopiaAlt                                                                                            |
// |          | csWSdeutanopiaAlt                                                                                            |
// |          | csWStritanoptiaAlt                                                                                           |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | csHSLhB                                                                                                      |
// | DIRECT   | csHSLhC                                                                                                      |
// | DIRECT   | csHSLhG                                                                                                      |
// | DIRECT   | csHSLhM                                                                                                      |
// | DIRECT   | csHSLhR                                                                                                      |
// | DIRECT   | csHSLhY                                                                                                      |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | INDIRECT | csHSLh_tpl                                                                                                   |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | csPGrey3x                                                                                                    |
// |          | csPGrey4x                                                                                                    |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | csPLY_tpl                                                                                                    |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | INDIRECT | csPLYcividis                                                                                                 |
// | DIRECT   | csPLYgrey                                                                                                    |
// | INDIRECT | csPLYhsvRB                                                                                                   |
// | INDIRECT | csPLYinferno                                                                                                 |
// | INDIRECT | csPLYmagma                                                                                                   |
// | INDIRECT | csPLYparula                                                                                                  |
// | INDIRECT | csPLYplasma                                                                                                  |
// | DIRECT   | csPLYquad                                                                                                    |
// | INDIRECT | csPLYturbo                                                                                                   |
// | INDIRECT | csPLYviridis                                                                                                 |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | csRainbowCM                                                                                                  |
// |          | csRainbowLA                                                                                                  |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | setRGBfromWavelengthCM(double wavelength, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR); |
// | DIRECT   | setRGBfromWavelengthLA(double wavelength);                                                                   |
// |----------+--------------------------------------------------------------------------------------------------------------|

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c8b, SetChanDbl) {

  mjr::color4c8b aColor;
  decltype(aColor)::channelType mxcv = 255;
  decltype(aColor)::channelType hlcv = 255/2;
  decltype(aColor)::channelType mncv =   0;
  double                        hldb = 127.0/mxcv;

  EXPECT_EQ(decltype(aColor)::maxChanVal,   mxcv);
  EXPECT_EQ(decltype(aColor)::minChanVal,   mncv);

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(1.0, 1.0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(1, 0.5);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       hlcv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0,  0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   hldb, 0.005);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0,  0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0,  0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChans_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mxcv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  255);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   1.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGBA_dbl(1.0, 0.0, 0.5, 0.5);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       hlcv);
  EXPECT_EQ(aColor.getChan(3),       hlcv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  127);
  EXPECT_EQ(aColor.getChan_byte(3),  127);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0,  0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0,  0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   hldb, 0.005);
  EXPECT_NEAR(aColor.getChan_dbl(3),   hldb, 0.005);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c16b, SetChanDbl) {
  mjr::color4c16b aColor;

  decltype(aColor)::channelType mxcv = 65535;
  decltype(aColor)::channelType hlcv = 32767; // 
  decltype(aColor)::channelType mncv =   0;
  double                        hldb = 32767.0/mxcv;

  EXPECT_EQ(decltype(aColor)::maxChanVal,   mxcv);
  EXPECT_EQ(decltype(aColor)::minChanVal,   mncv);

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(1.0, 1.0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(1, 0.5);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       hlcv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0,  0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   hldb, 0.005);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0,  0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0,  0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChans_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mxcv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  255);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   1.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGBA_dbl(1.0, 0.0, 0.5, 0.5);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       hlcv);
  EXPECT_EQ(aColor.getChan(3),       hlcv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  127);
  EXPECT_EQ(aColor.getChan_byte(3),  127);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0,  0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0,  0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   hldb, 0.005);
  EXPECT_NEAR(aColor.getChan_dbl(3),   hldb, 0.005);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c64F, SetChanDbl) {

  mjr::color4c64F aColor;

  EXPECT_NEAR(mjr::color4c64F::maxChanVal,   1.0, 0.00001);
  EXPECT_NEAR(mjr::color4c64F::minChanVal,   0.0, 0.00001);

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(0, 0.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(1.0, 1.0, 0.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(1, 0.5);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       0.5,                         0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.5, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChans_dbl(1.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::maxChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  255);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   1.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGBA_dbl(1.0, 0.0, 0.5, 0.5);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       0.5, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       0.5, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  127);
  EXPECT_EQ(aColor.getChan_byte(3),  127);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.5, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.5, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c8b, SetChanByte) {

  mjr::color4c8b aColor;

  aColor.setToBlack();
  aColor.setChan_byte(0, 11);
  aColor.setChan_byte(1, 22);
  aColor.setChan_byte(2, 33);
  aColor.setChan_byte(3, 44);

  EXPECT_EQ(aColor.getChan(0)      , 11);
  EXPECT_EQ(aColor.getChan(1)      , 22);
  EXPECT_EQ(aColor.getChan(2)      , 33);
  EXPECT_EQ(aColor.getChan(3)      , 44);

  EXPECT_EQ(aColor.getChan(0)      , aColor.getC0());
  EXPECT_EQ(aColor.getChan(1)      , aColor.getC1());
  EXPECT_EQ(aColor.getChan(2)      , aColor.getC2());
  EXPECT_EQ(aColor.getChan(3)      , aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0) , 11);
  EXPECT_EQ(aColor.getChan_byte(1) , 22);
  EXPECT_EQ(aColor.getChan_byte(2) , 33);
  EXPECT_EQ(aColor.getChan_byte(3) , 44);

  EXPECT_EQ(aColor.getChan_byte(0) , aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1) , aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2) , aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3) , aColor.getC3_byte());

  aColor.setC0_byte(55);
  aColor.setC1_byte(66);
  aColor.setC2_byte(77);
  aColor.setC3_byte(88);

  EXPECT_EQ(aColor.getChan(0)      , 55);
  EXPECT_EQ(aColor.getChan(1)      , 66);
  EXPECT_EQ(aColor.getChan(2)      , 77);
  EXPECT_EQ(aColor.getChan(3)      , 88);

  EXPECT_EQ(aColor.getChan(0)      , aColor.getC0());
  EXPECT_EQ(aColor.getChan(1)      , aColor.getC1());
  EXPECT_EQ(aColor.getChan(2)      , aColor.getC2());
  EXPECT_EQ(aColor.getChan(3)      , aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0) , 55);
  EXPECT_EQ(aColor.getChan_byte(1) , 66);
  EXPECT_EQ(aColor.getChan_byte(2) , 77);
  EXPECT_EQ(aColor.getChan_byte(3) , 88);

  EXPECT_EQ(aColor.getChan_byte(0) , aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1) , aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2) , aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3) , aColor.getC3_byte());

  aColor.setChans_byte(99);

  EXPECT_EQ(aColor.getChan(0)      , 99);
  EXPECT_EQ(aColor.getChan(1)      , 99);
  EXPECT_EQ(aColor.getChan(2)      , 99);
  EXPECT_EQ(aColor.getChan(3)      , 99);

  EXPECT_EQ(aColor.getChan(0)      , aColor.getC0());
  EXPECT_EQ(aColor.getChan(1)      , aColor.getC1());
  EXPECT_EQ(aColor.getChan(2)      , aColor.getC2());
  EXPECT_EQ(aColor.getChan(3)      , aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0) , 99);
  EXPECT_EQ(aColor.getChan_byte(1) , 99);
  EXPECT_EQ(aColor.getChan_byte(2) , 99);
  EXPECT_EQ(aColor.getChan_byte(3) , 99);

  EXPECT_EQ(aColor.getChan_byte(0) , aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1) , aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2) , aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3) , aColor.getC3_byte());

  aColor.setChansRGB_byte(33, 44, 55);

  EXPECT_EQ(aColor.getChan(0)      , 33);
  EXPECT_EQ(aColor.getChan(1)      , 44);
  EXPECT_EQ(aColor.getChan(2)      , 55);
  EXPECT_EQ(aColor.getChan(3)      , 99);

  EXPECT_EQ(aColor.getChan(0)      , aColor.getC0());
  EXPECT_EQ(aColor.getChan(1)      , aColor.getC1());
  EXPECT_EQ(aColor.getChan(2)      , aColor.getC2());
  EXPECT_EQ(aColor.getChan(3)      , aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0) , 33);
  EXPECT_EQ(aColor.getChan_byte(1) , 44);
  EXPECT_EQ(aColor.getChan_byte(2) , 55);
  EXPECT_EQ(aColor.getChan_byte(3) , 99);

  EXPECT_EQ(aColor.getChan_byte(0) , aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1) , aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2) , aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3) , aColor.getC3_byte());

  aColor.setChansRGBA_byte(11, 22, 33, 44);

  EXPECT_EQ(aColor.getChan(0)      , 11);
  EXPECT_EQ(aColor.getChan(1)      , 22);
  EXPECT_EQ(aColor.getChan(2)      , 33);
  EXPECT_EQ(aColor.getChan(3)      , 44);

  EXPECT_EQ(aColor.getChan(0)      , aColor.getC0());
  EXPECT_EQ(aColor.getChan(1)      , aColor.getC1());
  EXPECT_EQ(aColor.getChan(2)      , aColor.getC2());
  EXPECT_EQ(aColor.getChan(3)      , aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0) , 11);
  EXPECT_EQ(aColor.getChan_byte(1) , 22);
  EXPECT_EQ(aColor.getChan_byte(2) , 33);
  EXPECT_EQ(aColor.getChan_byte(3) , 44);

  EXPECT_EQ(aColor.getChan_byte(0) , aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1) , aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2) , aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3) , aColor.getC3_byte());

  // Test that max & min are hit
  aColor.setChansRGBA_byte(0, 255, 0, 255);

  EXPECT_EQ(aColor.getChan(0)      , mjr::color4c8b::minChanVal);
  EXPECT_EQ(aColor.getChan(1)      , mjr::color4c8b::maxChanVal);
  EXPECT_EQ(aColor.getChan(2)      , mjr::color4c8b::minChanVal);
  EXPECT_EQ(aColor.getChan(3)      , mjr::color4c8b::maxChanVal);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c16b, setChanByte) {

  mjr::color4c16b aColor;

  aColor.setToBlack();
  aColor.setChan_byte(0, 11);
  aColor.setChan_byte(1, 22);
  aColor.setChan_byte(2, 33);
  aColor.setChan_byte(3, 44);

  EXPECT_EQ(aColor.getChan(0),       0xB0B);
  EXPECT_EQ(aColor.getChan(1),       0x1616);
  EXPECT_EQ(aColor.getChan(2),       0x2121);
  EXPECT_EQ(aColor.getChan(3),       0x2C2C);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  11);
  EXPECT_EQ(aColor.getChan_byte(1),  22);
  EXPECT_EQ(aColor.getChan_byte(2),  33);
  EXPECT_EQ(aColor.getChan_byte(3),  44);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setC0_byte(55);
  aColor.setC1_byte(66);
  aColor.setC2_byte(77);
  aColor.setC3_byte(88);

  EXPECT_EQ(aColor.getChan(0),       14135);
  EXPECT_EQ(aColor.getChan(1),       16962);
  EXPECT_EQ(aColor.getChan(2),       19789);
  EXPECT_EQ(aColor.getChan(3),       22616);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  55);
  EXPECT_EQ(aColor.getChan_byte(1),  66);
  EXPECT_EQ(aColor.getChan_byte(2),  77);
  EXPECT_EQ(aColor.getChan_byte(3),  88);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChans_byte(99);

  EXPECT_EQ(aColor.getChan(0),       25443);
  EXPECT_EQ(aColor.getChan(1),       25443);
  EXPECT_EQ(aColor.getChan(2),       25443);
  EXPECT_EQ(aColor.getChan(3),       25443);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  99);
  EXPECT_EQ(aColor.getChan_byte(1),  99);
  EXPECT_EQ(aColor.getChan_byte(2),  99);
  EXPECT_EQ(aColor.getChan_byte(3),  99);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGB_byte(33, 44, 55);

  EXPECT_EQ(aColor.getChan(0),       8481);
  EXPECT_EQ(aColor.getChan(1),       11308);
  EXPECT_EQ(aColor.getChan(2),       14135);
  EXPECT_EQ(aColor.getChan(3),       25443);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  33);
  EXPECT_EQ(aColor.getChan_byte(1),  44);
  EXPECT_EQ(aColor.getChan_byte(2),  55);
  EXPECT_EQ(aColor.getChan_byte(3),  99);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGBA_byte(11, 22, 33, 44);

  EXPECT_EQ(aColor.getChan(0),       2827);
  EXPECT_EQ(aColor.getChan(1),       5654);
  EXPECT_EQ(aColor.getChan(2),       8481);
  EXPECT_EQ(aColor.getChan(3),       11308);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  11);
  EXPECT_EQ(aColor.getChan_byte(1),  22);
  EXPECT_EQ(aColor.getChan_byte(2),  33);
  EXPECT_EQ(aColor.getChan_byte(3),  44);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  // Test that max & min are hit
  aColor.setChansRGBA_byte(0, 255, 0, 255);

  EXPECT_EQ(aColor.getChan(0),       mjr::color4c16b::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       mjr::color4c16b::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       mjr::color4c16b::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       mjr::color4c16b::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c64F, setChanByte) {

  mjr::color4c64F aColor;

  aColor.setToBlack();
  aColor.setChan_byte(0, 11);
  aColor.setChan_byte(1, 22);
  aColor.setChan_byte(2, 34); // 33 has a rounding error :)
  aColor.setChan_byte(3, 44);

  EXPECT_NEAR(aColor.getChan(0),       0.043137254902, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       0.0862745098039, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       0.133333333333, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       0.172549019608, 0.0001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.0001);

  EXPECT_EQ(aColor.getChan_byte(0),  11);
  EXPECT_EQ(aColor.getChan_byte(1),  22);
  EXPECT_EQ(aColor.getChan_byte(2),  34);
  EXPECT_EQ(aColor.getChan_byte(3),  44);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setC0_byte(55);
  aColor.setC1_byte(65); // 66 has rounding error :)
  aColor.setC2_byte(77);
  aColor.setC3_byte(88);

  EXPECT_NEAR(aColor.getChan(0),       0.21568627450980393, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       0.254901960784, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       0.30196078431372547, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       0.34509803921568627, 0.0001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.0001);

  EXPECT_EQ(aColor.getChan_byte(0),  55);
  EXPECT_EQ(aColor.getChan_byte(1),  65);
  EXPECT_EQ(aColor.getChan_byte(2),  77);
  EXPECT_EQ(aColor.getChan_byte(3),  88);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChans_byte(99);

  EXPECT_NEAR(aColor.getChan(0),       0.38823529411764707, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       0.38823529411764707, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       0.38823529411764707, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       0.38823529411764707, 0.0001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.0001);

  EXPECT_EQ(aColor.getChan_byte(0),  99);
  EXPECT_EQ(aColor.getChan_byte(1),  99);
  EXPECT_EQ(aColor.getChan_byte(2),  99);
  EXPECT_EQ(aColor.getChan_byte(3),  99);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGB_byte(34, 44, 55);

  EXPECT_NEAR(aColor.getChan(0),       0.133333333333, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       0.17254901960784313, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       0.21568627450980393, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       0.38823529411764707, 0.0001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.0001);

  EXPECT_EQ(aColor.getChan_byte(0),  34);
  EXPECT_EQ(aColor.getChan_byte(1),  44);
  EXPECT_EQ(aColor.getChan_byte(2),  55);
  EXPECT_EQ(aColor.getChan_byte(3),  99);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGBA_byte(11, 22, 34, 44);

  EXPECT_NEAR(aColor.getChan(0),       0.043137254902, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       0.08627450980392157, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       0.133333333333, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       0.17254901960784313, 0.0001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.0001);

  EXPECT_EQ(aColor.getChan_byte(0),  11);
  EXPECT_EQ(aColor.getChan_byte(1),  22);
  EXPECT_EQ(aColor.getChan_byte(2),  34);
  EXPECT_EQ(aColor.getChan_byte(3),  44);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  // Test that max & min are hit
  aColor.setChansRGBA_byte(0, 255, 0, 255);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::minChanVal, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::maxChanVal, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::minChanVal, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::maxChanVal, 0.0001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c8b, SetChan) {

  mjr::color4c8b aColor;

  aColor.setToBlack();
  aColor.setChan(0, 11);
  aColor.setChan(1, 22);
  aColor.setChan(2, 33);
  aColor.setChan(3, 44);

  EXPECT_EQ(aColor.getChan(0),       11);
  EXPECT_EQ(aColor.getChan(1),       22);
  EXPECT_EQ(aColor.getChan(2),       33);
  EXPECT_EQ(aColor.getChan(3),       44);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  11);
  EXPECT_EQ(aColor.getChan_byte(1),  22);
  EXPECT_EQ(aColor.getChan_byte(2),  33);
  EXPECT_EQ(aColor.getChan_byte(3),  44);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setC0(55);
  aColor.setC1(66);
  aColor.setC2(77);
  aColor.setC3(88);

  EXPECT_EQ(aColor.getChan(0),       55);
  EXPECT_EQ(aColor.getChan(1),       66);
  EXPECT_EQ(aColor.getChan(2),       77);
  EXPECT_EQ(aColor.getChan(3),       88);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  55);
  EXPECT_EQ(aColor.getChan_byte(1),  66);
  EXPECT_EQ(aColor.getChan_byte(2),  77);
  EXPECT_EQ(aColor.getChan_byte(3),  88);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChans(99);

  EXPECT_EQ(aColor.getChan(0),       99);
  EXPECT_EQ(aColor.getChan(1),       99);
  EXPECT_EQ(aColor.getChan(2),       99);
  EXPECT_EQ(aColor.getChan(3),       99);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  99);
  EXPECT_EQ(aColor.getChan_byte(1),  99);
  EXPECT_EQ(aColor.getChan_byte(2),  99);
  EXPECT_EQ(aColor.getChan_byte(3),  99);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGB(33, 44, 55);

  EXPECT_EQ(aColor.getChan(0),       33);
  EXPECT_EQ(aColor.getChan(1),       44);
  EXPECT_EQ(aColor.getChan(2),       55);
  EXPECT_EQ(aColor.getChan(3),       99);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  33);
  EXPECT_EQ(aColor.getChan_byte(1),  44);
  EXPECT_EQ(aColor.getChan_byte(2),  55);
  EXPECT_EQ(aColor.getChan_byte(3),  99);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGBA(11, 22, 33, 44);

  EXPECT_EQ(aColor.getChan(0),       11);
  EXPECT_EQ(aColor.getChan(1),       22);
  EXPECT_EQ(aColor.getChan(2),       33);
  EXPECT_EQ(aColor.getChan(3),       44);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  11);
  EXPECT_EQ(aColor.getChan_byte(1),  22);
  EXPECT_EQ(aColor.getChan_byte(2),  33);
  EXPECT_EQ(aColor.getChan_byte(3),  44);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c16b, SetChan) {
  mjr::color4c16b aColor;

  aColor.setToBlack();
  aColor.setChan(0, 1024);
  aColor.setChan(1, 2048);
  aColor.setChan(2, 4096);
  aColor.setChan(3, 8192);

  EXPECT_EQ(aColor.getChan(0),       1024);
  EXPECT_EQ(aColor.getChan(1),       2048);
  EXPECT_EQ(aColor.getChan(2),       4096);
  EXPECT_EQ(aColor.getChan(3),       8192);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0x03);
  EXPECT_EQ(aColor.getChan_byte(1),  0x07);
  EXPECT_EQ(aColor.getChan_byte(2),  0x0f);
  EXPECT_EQ(aColor.getChan_byte(3),  0x1f);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setC0(8192);
  aColor.setC1(4096);
  aColor.setC2(2048);
  aColor.setC3(1024);

  EXPECT_EQ(aColor.getChan(0),       8192);
  EXPECT_EQ(aColor.getChan(1),       4096);
  EXPECT_EQ(aColor.getChan(2),       2048);
  EXPECT_EQ(aColor.getChan(3),       1024);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0x1f);
  EXPECT_EQ(aColor.getChan_byte(1),  0x0f);
  EXPECT_EQ(aColor.getChan_byte(2),  0x07);
  EXPECT_EQ(aColor.getChan_byte(3),  0x03);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

   aColor.setChans(32768);

  EXPECT_EQ(aColor.getChan(0),       32768);
  EXPECT_EQ(aColor.getChan(1),       32768);
  EXPECT_EQ(aColor.getChan(2),       32768);
  EXPECT_EQ(aColor.getChan(3),       32768);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0x7f);
  EXPECT_EQ(aColor.getChan_byte(1),  0x7f);
  EXPECT_EQ(aColor.getChan_byte(2),  0x7f);
  EXPECT_EQ(aColor.getChan_byte(3),  0x7f);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGB(4096, 8192, 16384);

  EXPECT_EQ(aColor.getChan(0),       4096);
  EXPECT_EQ(aColor.getChan(1),       8192);
  EXPECT_EQ(aColor.getChan(2),       16384);
  EXPECT_EQ(aColor.getChan(3),       32768);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0x0f);
  EXPECT_EQ(aColor.getChan_byte(1),  0x1f);
  EXPECT_EQ(aColor.getChan_byte(2),  0x3f);
  EXPECT_EQ(aColor.getChan_byte(3),  0x7f);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGBA(1024, 2048, 4096, 8192);

  EXPECT_EQ(aColor.getChan(0),       1024);
  EXPECT_EQ(aColor.getChan(1),       2048);
  EXPECT_EQ(aColor.getChan(2),       4096);
  EXPECT_EQ(aColor.getChan(3),       8192);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0x03);
  EXPECT_EQ(aColor.getChan_byte(1),  0x07);
  EXPECT_EQ(aColor.getChan_byte(2),  0x0f);
  EXPECT_EQ(aColor.getChan_byte(3),  0x1f);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  //Corners
  aColor.setChans(0);

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());

  EXPECT_EQ(aColor.getChan_dbl(0),  0.0);
  EXPECT_EQ(aColor.getChan_dbl(0),  aColor.getC0_dbl());

  aColor.setChans(65535);

  EXPECT_EQ(aColor.getChan(0),       65535);
  EXPECT_EQ(aColor.getChan(0),       aColor.getC1());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC1_byte());

  EXPECT_EQ(aColor.getChan_dbl(0),  1.0);
  EXPECT_EQ(aColor.getChan_dbl(0),  aColor.getC1_dbl());
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c64F, SetChan) {

  mjr::color4c64F aColor;

  aColor.setToBlack();
  aColor.setChan(0, 0.25);
  aColor.setChan(1, 0.50);
  aColor.setChan(2, 0.75);
  aColor.setChan(3, 1.00);

  EXPECT_NEAR(aColor.getChan(0),       0.25, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.50, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       0.75, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       1.00, 0.000001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.000001);

  EXPECT_EQ(aColor.getChan_byte(0),   63);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  191);
  EXPECT_EQ(aColor.getChan_byte(3),  255);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setC0(1.00);
  aColor.setC1(0.75);
  aColor.setC2(0.50);
  aColor.setC3(0.25);

  EXPECT_NEAR(aColor.getChan(0),       1.00, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.75, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       0.50, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       0.25, 0.000001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.000001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  191);
  EXPECT_EQ(aColor.getChan_byte(2),  127);
  EXPECT_EQ(aColor.getChan_byte(3),  63);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

   aColor.setChans(0.0);

  EXPECT_NEAR(aColor.getChan(0),       0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.000001);

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGB(0.75, 0.50, 1.0);

  EXPECT_NEAR(aColor.getChan(0),       0.75, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.50, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       1.00, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       0.00, 0.000001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.000001);

  EXPECT_EQ(aColor.getChan_byte(0),  191);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGBA(0.25, 0.50, 0.75, 1.00);

  EXPECT_NEAR(aColor.getChan(0),       0.25, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.50, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       0.75, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       1.00, 0.000001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.000001);

  EXPECT_EQ(aColor.getChan_byte(0),   63);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  191);
  EXPECT_EQ(aColor.getChan_byte(3),  255);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c64F, SetChanConst) {

  mjr::color4c64F aColor(0.25);
  EXPECT_NEAR(aColor.getChan(0),       0.25, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.25, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       0.25, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       0.25, 0.000001);

  mjr::color4c64F cColor(0.25, 0.50, 0.75);
  EXPECT_NEAR(cColor.getChan(0),       0.25, 0.000001);
  EXPECT_NEAR(cColor.getChan(1),       0.50, 0.000001);
  EXPECT_NEAR(cColor.getChan(2),       0.75, 0.000001);
  EXPECT_NEAR(cColor.getChan(3),       0.00, 0.000001);

  mjr::color4c64F dColor(1.00, 0.75, 0.50, 0.25);
  EXPECT_NEAR(dColor.getChan(0),       1.00, 0.000001);
  EXPECT_NEAR(dColor.getChan(1),       0.75, 0.000001);
  EXPECT_NEAR(dColor.getChan(2),       0.50, 0.000001);
  EXPECT_NEAR(dColor.getChan(3),       0.25, 0.000001);

  mjr::color4c64F eColor(dColor);
  EXPECT_NEAR(eColor.getChan(0),       1.00, 0.000001);
  EXPECT_NEAR(eColor.getChan(1),       0.75, 0.000001);
  EXPECT_NEAR(eColor.getChan(2),       0.50, 0.000001);
  EXPECT_NEAR(eColor.getChan(3),       0.25, 0.000001);

  mjr::color4c64F f0Color(mjr::color4c64F::cornerColorEnum::BLACK);
  mjr::color4c64F fRColor(mjr::color4c64F::cornerColorEnum::RED);
  mjr::color4c64F fGColor(mjr::color4c64F::cornerColorEnum::GREEN);
  mjr::color4c64F fBColor(mjr::color4c64F::cornerColorEnum::BLUE);
  mjr::color4c64F fYColor(mjr::color4c64F::cornerColorEnum::YELLOW);
  mjr::color4c64F fCColor(mjr::color4c64F::cornerColorEnum::CYAN);
  mjr::color4c64F fMColor(mjr::color4c64F::cornerColorEnum::MAGENTA);
  mjr::color4c64F f1Color(mjr::color4c64F::cornerColorEnum::WHITE);

  EXPECT_NEAR(f0Color.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(fRColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(fGColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(fBColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(fYColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(fCColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(fMColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(f1Color.getC0(),  1.0, 0.000001);

  EXPECT_NEAR(f0Color.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(fRColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(fGColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(fBColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(fYColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(fCColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(fMColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(f1Color.getC1(),  1.0, 0.000001);

  EXPECT_NEAR(f0Color.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(fRColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(fGColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(fBColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(fYColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(fCColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(fMColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(f1Color.getC2(),  1.0, 0.000001);

  EXPECT_NEAR(f0Color.getC3(),  0.0, 0.000001);
  EXPECT_NEAR(fRColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(fGColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(fBColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(fYColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(fCColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(fMColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(f1Color.getC3(),  1.0, 0.000001);

  // magic string -- corner with single character.

  mjr::color4c64F g0Color("0");
  mjr::color4c64F gRColor("R");
  mjr::color4c64F gGColor("G");
  mjr::color4c64F gBColor("B");
  mjr::color4c64F gYColor("Y");
  mjr::color4c64F gCColor("C");
  mjr::color4c64F gMColor("M");
  mjr::color4c64F g1Color("W");

  EXPECT_NEAR(g0Color.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(gRColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(gGColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(gBColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(gYColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(gCColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(gMColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(g1Color.getC0(),  1.0, 0.000001);

  EXPECT_NEAR(g0Color.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(gRColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(gGColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(gBColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(gYColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(gCColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(gMColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(g1Color.getC1(),  1.0, 0.000001);

  EXPECT_NEAR(g0Color.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(gRColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(gGColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(gBColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(gYColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(gCColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(gMColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(g1Color.getC2(),  1.0, 0.000001);

  EXPECT_NEAR(g0Color.getC3(),  0.0, 0.000001);
  EXPECT_NEAR(gRColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(gGColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(gBColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(gYColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(gCColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(gMColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(g1Color.getC3(),  1.0, 0.000001);

  // magic string -- corner with full name

  mjr::color4c64F h0Color("black");
  mjr::color4c64F hRColor("Red");
  mjr::color4c64F hGColor("GREEN");
  mjr::color4c64F hBColor("blue");
  mjr::color4c64F hYColor("YeLLoW");
  mjr::color4c64F hCColor("CYAN");
  mjr::color4c64F hMColor("MAGENTA");
  mjr::color4c64F h1Color("White");

  EXPECT_NEAR(h0Color.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(hRColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(hGColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(hBColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(hYColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(hCColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(hMColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(h1Color.getC0(),  1.0, 0.000001);

  EXPECT_NEAR(h0Color.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(hRColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(hGColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(hBColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(hYColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(hCColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(hMColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(h1Color.getC1(),  1.0, 0.000001);

  EXPECT_NEAR(h0Color.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(hRColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(hGColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(hBColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(hYColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(hCColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(hMColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(h1Color.getC2(),  1.0, 0.000001);

  EXPECT_NEAR(h0Color.getC3(),  0.0, 0.000001);
  EXPECT_NEAR(hRColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(hGColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(hBColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(hYColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(hCColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(hMColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(h1Color.getC3(),  1.0, 0.000001);

  mjr::color4c64F iColor("zoogo");   // unknown color => black
  EXPECT_NEAR(iColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(iColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(iColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(iColor.getC3(),  0.0, 0.000001);

  mjr::color4c64F jColor("z");   // unknown color => black
  EXPECT_NEAR(jColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(jColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(jColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(jColor.getC3(),  0.0, 0.000001);

  // magic string -- hex color string

  mjr::color4c64F kColor("#aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd");
  EXPECT_NEAR(kColor.getC0(),  0.66666666666, 0.000001);
  EXPECT_NEAR(kColor.getC1(),  0.73333333333, 0.000001);
  EXPECT_NEAR(kColor.getC2(),  0.80000000000, 0.000001);
  EXPECT_NEAR(kColor.getC3(),  0.86666666666, 0.000001);

  // Init List

  mjr::color4c64F oColor({1, 2, 3, 4});
  EXPECT_NEAR(oColor.getChan(0),  1, 0.000001);
  EXPECT_NEAR(oColor.getChan(1),  2, 0.000001);
  EXPECT_NEAR(oColor.getChan(2),  3, 0.000001);
  EXPECT_NEAR(oColor.getChan(3),  4, 0.000001);

  mjr::color4c64F pColor({1, 2, 3});              // size mismatch -> all chans to zero
  EXPECT_NEAR(pColor.getChan(0),  1, 0.000001);
  EXPECT_NEAR(pColor.getChan(1),  2, 0.000001);
  EXPECT_NEAR(pColor.getChan(2),  3, 0.000001);
  EXPECT_NEAR(pColor.getChan(3),  0, 0.000001);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c8b, SetChanConst) {

  mjr::color4c8b aColor(123);
  EXPECT_EQ(aColor.getChan(0),  123);
  EXPECT_EQ(aColor.getChan(1),  123);
  EXPECT_EQ(aColor.getChan(2),  123);
  EXPECT_EQ(aColor.getChan(3),  123);

  mjr::color4c8b cColor(33, 44, 55);
  EXPECT_EQ(cColor.getChan(0),  33);
  EXPECT_EQ(cColor.getChan(1),  44);
  EXPECT_EQ(cColor.getChan(2),  55);
  EXPECT_EQ(cColor.getChan(3),  0);

  mjr::color4c8b dColor(66, 77, 88, 99);
  EXPECT_EQ(dColor.getChan(0),  66);
  EXPECT_EQ(dColor.getChan(1),  77);
  EXPECT_EQ(dColor.getChan(2),  88);
  EXPECT_EQ(dColor.getChan(3),  99);

  mjr::color4c8b eColor(dColor);
  EXPECT_EQ(eColor.getChan(0),  66);
  EXPECT_EQ(eColor.getChan(1),  77);
  EXPECT_EQ(eColor.getChan(2),  88);
  EXPECT_EQ(eColor.getChan(3),  99);

  mjr::color4c8b f0Color(mjr::color4c8b::cornerColorEnum::BLACK);
  mjr::color4c8b fRColor(mjr::color4c8b::cornerColorEnum::RED);
  mjr::color4c8b fGColor(mjr::color4c8b::cornerColorEnum::GREEN);
  mjr::color4c8b fBColor(mjr::color4c8b::cornerColorEnum::BLUE);
  mjr::color4c8b fYColor(mjr::color4c8b::cornerColorEnum::YELLOW);
  mjr::color4c8b fCColor(mjr::color4c8b::cornerColorEnum::CYAN);
  mjr::color4c8b fMColor(mjr::color4c8b::cornerColorEnum::MAGENTA);
  mjr::color4c8b f1Color(mjr::color4c8b::cornerColorEnum::WHITE);

  EXPECT_EQ(f0Color.getC0(),    0);
  EXPECT_EQ(fRColor.getC0(),    255);
  EXPECT_EQ(fGColor.getC0(),    0);
  EXPECT_EQ(fBColor.getC0(),    0);
  EXPECT_EQ(fYColor.getC0(),    255);
  EXPECT_EQ(fCColor.getC0(),    0);
  EXPECT_EQ(fMColor.getC0(),    255);
  EXPECT_EQ(f1Color.getC0(),    255);

  EXPECT_EQ(f0Color.getC1(),    0);
  EXPECT_EQ(fRColor.getC1(),    0);
  EXPECT_EQ(fGColor.getC1(),    255);
  EXPECT_EQ(fBColor.getC1(),    0);
  EXPECT_EQ(fYColor.getC1(),    255);
  EXPECT_EQ(fCColor.getC1(),    255);
  EXPECT_EQ(fMColor.getC1(),    0);
  EXPECT_EQ(f1Color.getC1(),    255);

  EXPECT_EQ(f0Color.getC2(),    0);
  EXPECT_EQ(fRColor.getC2(),    0);
  EXPECT_EQ(fGColor.getC2(),    0);
  EXPECT_EQ(fBColor.getC2(),    255);
  EXPECT_EQ(fYColor.getC2(),    0);
  EXPECT_EQ(fCColor.getC2(),    255);
  EXPECT_EQ(fMColor.getC2(),    255);
  EXPECT_EQ(f1Color.getC2(),    255);

  EXPECT_EQ(f0Color.getC3(),    0);
  EXPECT_EQ(fRColor.getC3(),    0); // primary
  EXPECT_EQ(fGColor.getC3(),    0); // primary
  EXPECT_EQ(fBColor.getC3(),    0); // primary
  EXPECT_EQ(fYColor.getC3(),    255); // secondary
  EXPECT_EQ(fCColor.getC3(),    255); // secondary
  EXPECT_EQ(fMColor.getC3(),    255); // secondary
  EXPECT_EQ(f1Color.getC3(),    255);

  // magic string -- corner with single character.

  mjr::color4c8b g0Color("0");
  mjr::color4c8b gRColor("R");
  mjr::color4c8b gGColor("G");
  mjr::color4c8b gBColor("B");
  mjr::color4c8b gYColor("Y");
  mjr::color4c8b gCColor("C");
  mjr::color4c8b gMColor("M");
  mjr::color4c8b g1Color("W");

  EXPECT_EQ(g0Color.getC0(),    0);
  EXPECT_EQ(gRColor.getC0(),    255);
  EXPECT_EQ(gGColor.getC0(),    0);
  EXPECT_EQ(gBColor.getC0(),    0);
  EXPECT_EQ(gYColor.getC0(),    255);
  EXPECT_EQ(gCColor.getC0(),    0);
  EXPECT_EQ(gMColor.getC0(),    255);
  EXPECT_EQ(g1Color.getC0(),    255);

  EXPECT_EQ(g0Color.getC1(),    0);
  EXPECT_EQ(gRColor.getC1(),    0);
  EXPECT_EQ(gGColor.getC1(),    255);
  EXPECT_EQ(gBColor.getC1(),    0);
  EXPECT_EQ(gYColor.getC1(),    255);
  EXPECT_EQ(gCColor.getC1(),    255);
  EXPECT_EQ(gMColor.getC1(),    0);
  EXPECT_EQ(g1Color.getC1(),    255);

  EXPECT_EQ(g0Color.getC2(),    0);
  EXPECT_EQ(gRColor.getC2(),    0);
  EXPECT_EQ(gGColor.getC2(),    0);
  EXPECT_EQ(gBColor.getC2(),    255);
  EXPECT_EQ(gYColor.getC2(),    0);
  EXPECT_EQ(gCColor.getC2(),    255);
  EXPECT_EQ(gMColor.getC2(),    255);
  EXPECT_EQ(g1Color.getC2(),    255);

  EXPECT_EQ(g0Color.getC3(),    0);
  EXPECT_EQ(gRColor.getC3(),    0); // primary
  EXPECT_EQ(gGColor.getC3(),    0); // primary
  EXPECT_EQ(gBColor.getC3(),    0); // primary
  EXPECT_EQ(gYColor.getC3(),    255); // secondary
  EXPECT_EQ(gCColor.getC3(),    255); // secondary
  EXPECT_EQ(gMColor.getC3(),    255); // secondary
  EXPECT_EQ(g1Color.getC3(),    255);

  // magic string -- corner with full name

  mjr::color4c8b h0Color("black");
  mjr::color4c8b hRColor("Red");
  mjr::color4c8b hGColor("GREEN");
  mjr::color4c8b hBColor("blue");
  mjr::color4c8b hYColor("YeLLoW");
  mjr::color4c8b hCColor("CYAN");
  mjr::color4c8b hMColor("MAGENTA");
  mjr::color4c8b h1Color("White");

  EXPECT_EQ(h0Color.getC0(),    0);
  EXPECT_EQ(hRColor.getC0(),    255);
  EXPECT_EQ(hGColor.getC0(),    0);
  EXPECT_EQ(hBColor.getC0(),    0);
  EXPECT_EQ(hYColor.getC0(),    255);
  EXPECT_EQ(hCColor.getC0(),    0);
  EXPECT_EQ(hMColor.getC0(),    255);
  EXPECT_EQ(h1Color.getC0(),    255);

  EXPECT_EQ(h0Color.getC1(),    0);
  EXPECT_EQ(hRColor.getC1(),    0);
  EXPECT_EQ(hGColor.getC1(),    255);
  EXPECT_EQ(hBColor.getC1(),    0);
  EXPECT_EQ(hYColor.getC1(),    255);
  EXPECT_EQ(hCColor.getC1(),    255);
  EXPECT_EQ(hMColor.getC1(),    0);
  EXPECT_EQ(h1Color.getC1(),    255);

  EXPECT_EQ(h0Color.getC2(),    0);
  EXPECT_EQ(hRColor.getC2(),    0);
  EXPECT_EQ(hGColor.getC2(),    0);
  EXPECT_EQ(hBColor.getC2(),    255);
  EXPECT_EQ(hYColor.getC2(),    0);
  EXPECT_EQ(hCColor.getC2(),    255);
  EXPECT_EQ(hMColor.getC2(),    255);
  EXPECT_EQ(h1Color.getC2(),    255);

  EXPECT_EQ(h0Color.getC3(),    0);
  EXPECT_EQ(hRColor.getC3(),    0); // primary
  EXPECT_EQ(hGColor.getC3(),    0); // primary
  EXPECT_EQ(hBColor.getC3(),    0); // primary
  EXPECT_EQ(hYColor.getC3(),    255); // secondary
  EXPECT_EQ(hCColor.getC3(),    255); // secondary
  EXPECT_EQ(hMColor.getC3(),    255); // secondary
  EXPECT_EQ(h1Color.getC3(),    255);

  mjr::color4c8b iColor("zoogo");   // unknown color => black
  EXPECT_EQ(iColor.getC0(),     0);
  EXPECT_EQ(iColor.getC1(),     0);
  EXPECT_EQ(iColor.getC2(),     0);
  EXPECT_EQ(iColor.getC3(),     0);

  mjr::color4c8b jColor("z");   // unknown color => black
  EXPECT_EQ(jColor.getC0(),     0);
  EXPECT_EQ(jColor.getC1(),     0);
  EXPECT_EQ(jColor.getC2(),     0);
  EXPECT_EQ(jColor.getC3(),     0);

  // magic string -- hex color strings

  mjr::color4c8b kColor("#aabbccdd");
  EXPECT_EQ(kColor.getC0(),     0xAA);
  EXPECT_EQ(kColor.getC1(),     0xBB);
  EXPECT_EQ(kColor.getC2(),     0xCC);
  EXPECT_EQ(kColor.getC3(),     0xDD);

  mjr::color4c8b lColor("#bbccdd");
  EXPECT_EQ(lColor.getC0(),     0xBB);
  EXPECT_EQ(lColor.getC1(),     0xCC);
  EXPECT_EQ(lColor.getC2(),     0xDD);
  EXPECT_EQ(lColor.getC3(),     0x0);

  mjr::color4c8b mColor("#aa");
  EXPECT_EQ(mColor.getC0(),     0xAA);
  EXPECT_EQ(mColor.getC1(),     0x0);
  EXPECT_EQ(mColor.getC2(),     0x0);
  EXPECT_EQ(mColor.getC3(),     0x0);

  mjr::color4c8b nColor("#a");
  EXPECT_EQ(nColor.getC0(),     0x0);
  EXPECT_EQ(nColor.getC1(),     0x0);
  EXPECT_EQ(nColor.getC2(),     0x0);
  EXPECT_EQ(nColor.getC3(),     0x0);

  // Init List

  mjr::color4c8b oColor({1, 2, 3, 4});
  EXPECT_EQ(oColor.getChan(0),  1);
  EXPECT_EQ(oColor.getChan(1),  2);
  EXPECT_EQ(oColor.getChan(2),  3);
  EXPECT_EQ(oColor.getChan(3),  4);

  mjr::color4c8b pColor({1, 2, 3});
  EXPECT_EQ(pColor.getChan(0),  1);
  EXPECT_EQ(pColor.getChan(1),  2);
  EXPECT_EQ(pColor.getChan(2),  3);
  EXPECT_EQ(pColor.getChan(3),  0); // unsp -> zero

  mjr::color4c8b qColor({1});
  EXPECT_EQ(qColor.getChan(0),  1);
  EXPECT_EQ(qColor.getChan(1),  0); // unsp -> zero
  EXPECT_EQ(qColor.getChan(2),  0); // unsp -> zero
  EXPECT_EQ(qColor.getChan(3),  0); // unsp -> zero

  mjr::color4c8b rColor({1, 2, 3, 4, 5, 6});
  EXPECT_EQ(rColor.getChan(0),  1);
  EXPECT_EQ(rColor.getChan(1),  2);
  EXPECT_EQ(rColor.getChan(2),  3);
  EXPECT_EQ(rColor.getChan(3),  4);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c16b, SetChanConst) {

  mjr::color4c16b aColor(123);
  EXPECT_EQ(aColor.getChan(0),  123);
  EXPECT_EQ(aColor.getChan(1),  123);
  EXPECT_EQ(aColor.getChan(2),  123);
  EXPECT_EQ(aColor.getChan(3),  123);

  mjr::color4c16b cColor(33, 44, 55);
  EXPECT_EQ(cColor.getChan(0),  33);
  EXPECT_EQ(cColor.getChan(1),  44);
  EXPECT_EQ(cColor.getChan(2),  55);
  EXPECT_EQ(cColor.getChan(3),  0);

  mjr::color4c16b dColor(66, 77, 88, 99);
  EXPECT_EQ(dColor.getChan(0),  66);
  EXPECT_EQ(dColor.getChan(1),  77);
  EXPECT_EQ(dColor.getChan(2),  88);
  EXPECT_EQ(dColor.getChan(3),  99);

  mjr::color4c16b eColor(dColor);
  EXPECT_EQ(eColor.getChan(0),  66);
  EXPECT_EQ(eColor.getChan(1),  77);
  EXPECT_EQ(eColor.getChan(2),  88);
  EXPECT_EQ(eColor.getChan(3),  99);

  mjr::color4c16b f0Color(mjr::color4c16b::cornerColorEnum::BLACK);
  mjr::color4c16b fRColor(mjr::color4c16b::cornerColorEnum::RED);
  mjr::color4c16b fGColor(mjr::color4c16b::cornerColorEnum::GREEN);
  mjr::color4c16b fBColor(mjr::color4c16b::cornerColorEnum::BLUE);
  mjr::color4c16b fYColor(mjr::color4c16b::cornerColorEnum::YELLOW);
  mjr::color4c16b fCColor(mjr::color4c16b::cornerColorEnum::CYAN);
  mjr::color4c16b fMColor(mjr::color4c16b::cornerColorEnum::MAGENTA);
  mjr::color4c16b f1Color(mjr::color4c16b::cornerColorEnum::WHITE);

  EXPECT_EQ(f0Color.getC0(),    0);
  EXPECT_EQ(fRColor.getC0(),    65535);
  EXPECT_EQ(fGColor.getC0(),    0);
  EXPECT_EQ(fBColor.getC0(),    0);
  EXPECT_EQ(fYColor.getC0(),    65535);
  EXPECT_EQ(fCColor.getC0(),    0);
  EXPECT_EQ(fMColor.getC0(),    65535);
  EXPECT_EQ(f1Color.getC0(),    65535);

  EXPECT_EQ(f0Color.getC1(),    0);
  EXPECT_EQ(fRColor.getC1(),    0);
  EXPECT_EQ(fGColor.getC1(),    65535);
  EXPECT_EQ(fBColor.getC1(),    0);
  EXPECT_EQ(fYColor.getC1(),    65535);
  EXPECT_EQ(fCColor.getC1(),    65535);
  EXPECT_EQ(fMColor.getC1(),    0);
  EXPECT_EQ(f1Color.getC1(),    65535);

  EXPECT_EQ(f0Color.getC2(),    0);
  EXPECT_EQ(fRColor.getC2(),    0);
  EXPECT_EQ(fGColor.getC2(),    0);
  EXPECT_EQ(fBColor.getC2(),    65535);
  EXPECT_EQ(fYColor.getC2(),    0);
  EXPECT_EQ(fCColor.getC2(),    65535);
  EXPECT_EQ(fMColor.getC2(),    65535);
  EXPECT_EQ(f1Color.getC2(),    65535);

  EXPECT_EQ(f0Color.getC3(),    0);
  EXPECT_EQ(fRColor.getC3(),    0); // primary
  EXPECT_EQ(fGColor.getC3(),    0); // primary
  EXPECT_EQ(fBColor.getC3(),    0); // primary
  EXPECT_EQ(fYColor.getC3(),    65535); // secondary
  EXPECT_EQ(fCColor.getC3(),    65535); // secondary
  EXPECT_EQ(fMColor.getC3(),    65535); // secondary
  EXPECT_EQ(f1Color.getC3(),    65535);

  // magic string -- corner with single character.

  mjr::color4c16b g0Color("0");
  mjr::color4c16b gRColor("R");
  mjr::color4c16b gGColor("G");
  mjr::color4c16b gBColor("B");
  mjr::color4c16b gYColor("Y");
  mjr::color4c16b gCColor("C");
  mjr::color4c16b gMColor("M");
  mjr::color4c16b g1Color("W");

  EXPECT_EQ(g0Color.getC0(),    0);
  EXPECT_EQ(gRColor.getC0(),    65535);
  EXPECT_EQ(gGColor.getC0(),    0);
  EXPECT_EQ(gBColor.getC0(),    0);
  EXPECT_EQ(gYColor.getC0(),    65535);
  EXPECT_EQ(gCColor.getC0(),    0);
  EXPECT_EQ(gMColor.getC0(),    65535);
  EXPECT_EQ(g1Color.getC0(),    65535);

  EXPECT_EQ(g0Color.getC1(),    0);
  EXPECT_EQ(gRColor.getC1(),    0);
  EXPECT_EQ(gGColor.getC1(),    65535);
  EXPECT_EQ(gBColor.getC1(),    0);
  EXPECT_EQ(gYColor.getC1(),    65535);
  EXPECT_EQ(gCColor.getC1(),    65535);
  EXPECT_EQ(gMColor.getC1(),    0);
  EXPECT_EQ(g1Color.getC1(),    65535);

  EXPECT_EQ(g0Color.getC2(),    0);
  EXPECT_EQ(gRColor.getC2(),    0);
  EXPECT_EQ(gGColor.getC2(),    0);
  EXPECT_EQ(gBColor.getC2(),    65535);
  EXPECT_EQ(gYColor.getC2(),    0);
  EXPECT_EQ(gCColor.getC2(),    65535);
  EXPECT_EQ(gMColor.getC2(),    65535);
  EXPECT_EQ(g1Color.getC2(),    65535);

  EXPECT_EQ(g0Color.getC3(),    0);
  EXPECT_EQ(gRColor.getC3(),    0); // primary
  EXPECT_EQ(gGColor.getC3(),    0); // primary
  EXPECT_EQ(gBColor.getC3(),    0); // primary
  EXPECT_EQ(gYColor.getC3(),    65535); // secondary
  EXPECT_EQ(gCColor.getC3(),    65535); // secondary
  EXPECT_EQ(gMColor.getC3(),    65535); // secondary
  EXPECT_EQ(g1Color.getC3(),    65535);

  // magic string -- corner with full name

  mjr::color4c16b h0Color("black");
  mjr::color4c16b hRColor("Red");
  mjr::color4c16b hGColor("GREEN");
  mjr::color4c16b hBColor("blue");
  mjr::color4c16b hYColor("YeLLoW");
  mjr::color4c16b hCColor("CYAN");
  mjr::color4c16b hMColor("MAGENTA");
  mjr::color4c16b h1Color("White");

  EXPECT_EQ(h0Color.getC0(),    0);
  EXPECT_EQ(hRColor.getC0(),    65535);
  EXPECT_EQ(hGColor.getC0(),    0);
  EXPECT_EQ(hBColor.getC0(),    0);
  EXPECT_EQ(hYColor.getC0(),    65535);
  EXPECT_EQ(hCColor.getC0(),    0);
  EXPECT_EQ(hMColor.getC0(),    65535);
  EXPECT_EQ(h1Color.getC0(),    65535);

  EXPECT_EQ(h0Color.getC1(),    0);
  EXPECT_EQ(hRColor.getC1(),    0);
  EXPECT_EQ(hGColor.getC1(),    65535);
  EXPECT_EQ(hBColor.getC1(),    0);
  EXPECT_EQ(hYColor.getC1(),    65535);
  EXPECT_EQ(hCColor.getC1(),    65535);
  EXPECT_EQ(hMColor.getC1(),    0);
  EXPECT_EQ(h1Color.getC1(),    65535);

  EXPECT_EQ(h0Color.getC2(),    0);
  EXPECT_EQ(hRColor.getC2(),    0);
  EXPECT_EQ(hGColor.getC2(),    0);
  EXPECT_EQ(hBColor.getC2(),    65535);
  EXPECT_EQ(hYColor.getC2(),    0);
  EXPECT_EQ(hCColor.getC2(),    65535);
  EXPECT_EQ(hMColor.getC2(),    65535);
  EXPECT_EQ(h1Color.getC2(),    65535);

  EXPECT_EQ(h0Color.getC3(),    0);
  EXPECT_EQ(hRColor.getC3(),    0); // primary
  EXPECT_EQ(hGColor.getC3(),    0); // primary
  EXPECT_EQ(hBColor.getC3(),    0); // primary
  EXPECT_EQ(hYColor.getC3(),    65535); // secondary
  EXPECT_EQ(hCColor.getC3(),    65535); // secondary
  EXPECT_EQ(hMColor.getC3(),    65535); // secondary
  EXPECT_EQ(h1Color.getC3(),    65535);

  mjr::color4c16b iColor("zoogo");   // unknown color => black
  EXPECT_EQ(iColor.getC0(),     0);
  EXPECT_EQ(iColor.getC1(),     0);
  EXPECT_EQ(iColor.getC2(),     0);
  EXPECT_EQ(iColor.getC3(),     0);

  mjr::color4c16b jColor("z");   // unknown color => black
  EXPECT_EQ(jColor.getC0(),     0);
  EXPECT_EQ(jColor.getC1(),     0);
  EXPECT_EQ(jColor.getC2(),     0);
  EXPECT_EQ(jColor.getC3(),     0);

  // magic string -- hex color string

  mjr::color4c16b kColor("#aaaabbbbccccdddd");
  EXPECT_EQ(kColor.getC0(),     0xAAAA);
  EXPECT_EQ(kColor.getC1(),     0xBBBB);
  EXPECT_EQ(kColor.getC2(),     0xCCCC);
  EXPECT_EQ(kColor.getC3(),     0xDDDD);

  mjr::color4c16b lColor("#bbbbccccdddd");
  EXPECT_EQ(lColor.getC0(),     0xBBBB);
  EXPECT_EQ(lColor.getC1(),     0xCCCC);
  EXPECT_EQ(lColor.getC2(),     0xDDDD);
  EXPECT_EQ(lColor.getC3(),     0x0);

  mjr::color4c16b mColor("#aaaa");
  EXPECT_EQ(mColor.getC0(),     0xAAAA);
  EXPECT_EQ(mColor.getC1(),     0x0);
  EXPECT_EQ(mColor.getC2(),     0x0);
  EXPECT_EQ(mColor.getC3(),     0x0);

  mjr::color4c16b nColor("#aaa");
  EXPECT_EQ(nColor.getC0(),     0x0);
  EXPECT_EQ(nColor.getC1(),     0x0);
  EXPECT_EQ(nColor.getC2(),     0x0);
  EXPECT_EQ(nColor.getC3(),     0x0);

  // Init List

  mjr::color4c16b oColor({1, 2, 3, 4});
  EXPECT_EQ(oColor.getChan(0),  1);
  EXPECT_EQ(oColor.getChan(1),  2);
  EXPECT_EQ(oColor.getChan(2),  3);
  EXPECT_EQ(oColor.getChan(3),  4);

  mjr::color4c16b pColor({1, 2, 3});              // size mismatch -> all chans to zero
  EXPECT_EQ(pColor.getChan(0),  1);
  EXPECT_EQ(pColor.getChan(1),  2);
  EXPECT_EQ(pColor.getChan(2),  3);
  EXPECT_EQ(pColor.getChan(3),  0);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c16b, SetChanHex) {

  mjr::color4c8b aColor("0");
  aColor.setToWhite();
  aColor.setChans("#aabbccdd");
  EXPECT_EQ(aColor.getC0(),  0xAA);
  EXPECT_EQ(aColor.getC1(),  0xBB);
  EXPECT_EQ(aColor.getC2(),  0xCC);
  EXPECT_EQ(aColor.getC3(),  0xDD);

  // undefined chans left alown
  aColor.setToWhite();
  aColor.setChans("#bbccdd");
  EXPECT_EQ(aColor.getC0(),  0xBB);
  EXPECT_EQ(aColor.getC1(),  0xCC);
  EXPECT_EQ(aColor.getC2(),  0xDD);
  EXPECT_EQ(aColor.getC3(),  0xFF);

  aColor.setToWhite();
  aColor.setChans("#aa");
  EXPECT_EQ(aColor.getC0(),  0xAA);
  EXPECT_EQ(aColor.getC1(),  0xFF);
  EXPECT_EQ(aColor.getC2(),  0xFF);
  EXPECT_EQ(aColor.getC3(),  0xFF);

  aColor.setToWhite();
  aColor.setChans("#aaa");
  EXPECT_EQ(aColor.getC0(),  0xFF);
  EXPECT_EQ(aColor.getC1(),  0xFF);
  EXPECT_EQ(aColor.getC2(),  0xFF);
  EXPECT_EQ(aColor.getC3(),  0xFF);

  // undefined chans set to min
  aColor.setToWhite();
  aColor.setChans("#bbccdd", true);
  EXPECT_EQ(aColor.getC0(),  0xBB);
  EXPECT_EQ(aColor.getC1(),  0xCC);
  EXPECT_EQ(aColor.getC2(),  0xDD);
  EXPECT_EQ(aColor.getC3(),  0x0000);

  aColor.setToWhite();
  aColor.setChans("#aa", true);
  EXPECT_EQ(aColor.getC0(),  0xAA);
  EXPECT_EQ(aColor.getC1(),  0x0000);
  EXPECT_EQ(aColor.getC2(),  0x0000);
  EXPECT_EQ(aColor.getC3(),  0x0000);

  aColor.setToWhite();
  aColor.setChans("#a", true);
  EXPECT_EQ(aColor.getC0(),  0x0000);
  EXPECT_EQ(aColor.getC1(),  0x0000);
  EXPECT_EQ(aColor.getC2(),  0x0000);
  EXPECT_EQ(aColor.getC3(),  0x0000);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c16b, setChanHex) {

  mjr::color4c16b aColor("0");
  aColor.setToWhite();
  aColor.setChans("#aaaabbbbccccdddd");
  EXPECT_EQ(aColor.getC0(),  0xAAAA);
  EXPECT_EQ(aColor.getC1(),  0xBBBB);
  EXPECT_EQ(aColor.getC2(),  0xCCCC);
  EXPECT_EQ(aColor.getC3(),  0xDDDD);

  // undefined chans left alown
  aColor.setToWhite();
  aColor.setChans("#bbbbccccdddd");
  EXPECT_EQ(aColor.getC0(),  0xBBBB);
  EXPECT_EQ(aColor.getC1(),  0xCCCC);
  EXPECT_EQ(aColor.getC2(),  0xDDDD);
  EXPECT_EQ(aColor.getC3(),  0xFFFF);

  aColor.setToWhite();
  aColor.setChans("#aaaa");
  EXPECT_EQ(aColor.getC0(),  0xAAAA);
  EXPECT_EQ(aColor.getC1(),  0xFFFF);
  EXPECT_EQ(aColor.getC2(),  0xFFFF);
  EXPECT_EQ(aColor.getC3(),  0xFFFF);

  aColor.setToWhite();
  aColor.setChans("#aaa");
  EXPECT_EQ(aColor.getC0(),  0xFFFF);
  EXPECT_EQ(aColor.getC1(),  0xFFFF);
  EXPECT_EQ(aColor.getC2(),  0xFFFF);
  EXPECT_EQ(aColor.getC3(),  0xFFFF);

  // undefined chans set to min
  aColor.setToWhite();
  aColor.setChans("#bbbbccccdddd", true);
  EXPECT_EQ(aColor.getC0(),  0xBBBB);
  EXPECT_EQ(aColor.getC1(),  0xCCCC);
  EXPECT_EQ(aColor.getC2(),  0xDDDD);
  EXPECT_EQ(aColor.getC3(),  0x0000);

  aColor.setToWhite();
  aColor.setChans("#aaaa", true);
  EXPECT_EQ(aColor.getC0(),  0xAAAA);
  EXPECT_EQ(aColor.getC1(),  0x0000);
  EXPECT_EQ(aColor.getC2(),  0x0000);
  EXPECT_EQ(aColor.getC3(),  0x0000);

  aColor.setToWhite();
  aColor.setChans("#aaa", true);
  EXPECT_EQ(aColor.getC0(),  0x0000);
  EXPECT_EQ(aColor.getC1(),  0x0000);
  EXPECT_EQ(aColor.getC2(),  0x0000);
  EXPECT_EQ(aColor.getC3(),  0x0000);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_color4c64F, setChanHex) {

  mjr::color4c64F aColor("0");
  aColor.setToWhite();
  aColor.setChans("#aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd");
  EXPECT_NEAR(aColor.getC0(),  0.66666666666, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  0.73333333333, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  0.80000000000, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  0.86666666666, 0.00001);

  // undefined chans left alown
  aColor.setToWhite();
  aColor.setChans("#bbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd");
  EXPECT_NEAR(aColor.getC0(),  0.73333333333, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  0.80000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  0.86666666666, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  1.00000000000, 0.00001);

  aColor.setToWhite();
  aColor.setChans("#aaaaaaaaaaaaaaaa");
  EXPECT_NEAR(aColor.getC0(),  0.66666666666, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  1.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  1.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  1.00000000000, 0.00001);

  aColor.setToWhite();
  aColor.setChans("#aaa");
  EXPECT_NEAR(aColor.getC0(),  1.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  1.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  1.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  1.00000000000, 0.00001);

  // undefined chans set to min
  aColor.setToWhite();
  aColor.setChans("#bbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd", true);
  EXPECT_NEAR(aColor.getC0(),  0.73333333333, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  0.80000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  0.86666666666, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  0.00000000000, 0.00001);

  aColor.setToWhite();
  aColor.setChans("#aaaaaaaaaaaaaaaa", true);
  EXPECT_NEAR(aColor.getC0(),  0.66666666666, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  0.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  0.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  0.00000000000, 0.00001);

  aColor.setToWhite();
  aColor.setChans("#aaa", true);
  EXPECT_NEAR(aColor.getC0(),  0.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  0.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  0.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  0.00000000000, 0.00001);

 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_colorARGB8, setChan) {

  // For these tests we are mostly concerned with R, G, B, & A being
  // put in the right places.  Conversions between double/byte and
  // clrChanT are tested pretty well elsewhere.

  typedef mjr::colorTpl<mjr::colChanI8, 4, 1, 2, 3, 0> colorARGB8;
  colorARGB8 aColor;

  aColor.setToBlack();
  aColor.setRed(colorARGB8::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen(colorARGB8::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue(colorARGB8::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha(colorARGB8::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(1, 2, 3, 4);

  EXPECT_EQ(aColor.getChan(0),       4);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(1, 2, 3);

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_byte(1, 2, 3, 4);

  EXPECT_EQ(aColor.getChan(0),       4);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_byte(1, 2, 3);

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_dbl(0.25, 0.50, 0.75, 1.00);

  EXPECT_EQ(aColor.getChan(0),       0xFF);
  EXPECT_EQ(aColor.getChan(1),       0x3F);
  EXPECT_EQ(aColor.getChan(2),       0x7F);
  EXPECT_EQ(aColor.getChan(3),       0xBF);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_dbl(1.00, 0.25, 0.50);

  EXPECT_EQ(aColor.getChan(0),       0x00);
  EXPECT_EQ(aColor.getChan(1),       0xFF);
  EXPECT_EQ(aColor.getChan(2),       0x3F);
  EXPECT_EQ(aColor.getChan(3),       0x7F);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(colorARGB8::clrChanTup4(1, 2, 3, 4));

  EXPECT_EQ(aColor.getChan(0),       4);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(colorARGB8::clrChanTup3(1, 2, 3));

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TYP_colorARGB16, setChan) {

  typedef mjr::colorTpl<mjr::colChanI16, 4, 1, 2, 3, 0> colorARGB16;
  colorARGB16 aColor;

  aColor.setToBlack();
  aColor.setRed(colorARGB16::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setGreen(colorARGB16::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setBlue(colorARGB16::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha(colorARGB16::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(1, 2, 3, 4);

  EXPECT_EQ(aColor.getChan(0),       4);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(1, 2, 3);

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_byte(1, 2, 3, 4);

  EXPECT_EQ(aColor.getChan(0),       1028);
  EXPECT_EQ(aColor.getChan(1),       257);
  EXPECT_EQ(aColor.getChan(2),       514);
  EXPECT_EQ(aColor.getChan(3),       771);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_byte(1, 2, 3);

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       257);
  EXPECT_EQ(aColor.getChan(2),       514);
  EXPECT_EQ(aColor.getChan(3),       771);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_dbl(0.25, 0.50, 0.75, 1.00);

  EXPECT_EQ(aColor.getChan(0),       0xFFFF);
  EXPECT_EQ(aColor.getChan(1),       0x3FFF);
  EXPECT_EQ(aColor.getChan(2),       0x7FFF);
  EXPECT_EQ(aColor.getChan(3),       0xBFFF);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_dbl(1.00, 0.25, 0.50);

  EXPECT_EQ(aColor.getChan(0),       0x0000);
  EXPECT_EQ(aColor.getChan(1),       0xFFFF);
  EXPECT_EQ(aColor.getChan(2),       0x3FFF);
  EXPECT_EQ(aColor.getChan(3),       0x7FFF);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(colorARGB16::clrChanTup4(1, 2, 3, 4));

  EXPECT_EQ(aColor.getChan(0),       4);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(colorARGB16::clrChanTup3(1, 2, 3));

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_fromLogPackIntARGB, bit8) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  EXPECT_EQ(aColor.getRed(),    0xBB);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xDD);
  EXPECT_EQ(aColor.getAlpha(),  0xAA);

  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xDD);
  EXPECT_EQ(aColor.getC0(),     0xAA);

  aColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(aColor.getRed(),    0xDD);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xBB);
  EXPECT_EQ(aColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(aColor.getC1(),     0xDD);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xBB);
  EXPECT_EQ(aColor.getC0(),     0xAA); // From before

  eColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(eColor.getRed(),    0xDD);
  EXPECT_EQ(eColor.getGreen(),  0xCC);
  EXPECT_EQ(eColor.getBlue(),   0xBB);

  EXPECT_EQ(eColor.getC0(),     0xDD);
  EXPECT_EQ(eColor.getC1(),     0xCC);
  EXPECT_EQ(eColor.getC2(),     0xBB);

  bColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  EXPECT_EQ(bColor.getRed(),    0xBB);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xDD);
  EXPECT_EQ(bColor.getAlpha(),  0xAA);

  EXPECT_EQ(bColor.getC0(),     0xBB);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xDD);
  EXPECT_EQ(bColor.getC3(),     0xAA);

  bColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(bColor.getRed(),    0xDD);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xBB);
  EXPECT_EQ(bColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(bColor.getC0(),     0xDD);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xBB);
  EXPECT_EQ(bColor.getC3(),     0xAA); // From before

  fColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(fColor.getRed(),    0xDD);
  EXPECT_EQ(fColor.getGreen(),  0xCC);
  EXPECT_EQ(fColor.getBlue(),   0xBB);

  EXPECT_EQ(fColor.getC2(),     0xDD);
  EXPECT_EQ(fColor.getC1(),     0xCC);
  EXPECT_EQ(fColor.getC0(),     0xBB);

  cColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xDD);
  EXPECT_EQ(cColor.getAlpha(),  0xAA);

  EXPECT_EQ(cColor.getC2(),     0xBB);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xDD);
  EXPECT_EQ(cColor.getC3(),     0xAA);

  cColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(cColor.getRed(),    0xDD);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xBB);
  EXPECT_EQ(cColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(cColor.getC2(),     0xDD);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xBB);
  EXPECT_EQ(cColor.getC3(),     0xAA); // From before

  dColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  EXPECT_EQ(dColor.getRed(),    0xBB);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xDD);
  EXPECT_EQ(dColor.getAlpha(),  0xAA);

  EXPECT_EQ(dColor.getC3(),     0xBB);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xDD);
  EXPECT_EQ(dColor.getC0(),     0xAA);

  dColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(dColor.getRed(),    0xDD);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xBB);
  EXPECT_EQ(dColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(dColor.getC3(),     0xDD);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xBB);
  EXPECT_EQ(dColor.getC0(),     0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_fromLogPackIntRGBA, bit8) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  EXPECT_EQ(aColor.getRed(),    0xBB);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xDD);
  EXPECT_EQ(aColor.getAlpha(),  0xAA);

  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xDD);
  EXPECT_EQ(aColor.getC0(),     0xAA);

  aColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(aColor.getRed(),    0xDD);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xBB);
  EXPECT_EQ(aColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(aColor.getC1(),     0xDD);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xBB);
  EXPECT_EQ(aColor.getC0(),     0xAA); // From before

  eColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(eColor.getRed(),    0xDD);
  EXPECT_EQ(eColor.getGreen(),  0xCC);
  EXPECT_EQ(eColor.getBlue(),   0xBB);

  EXPECT_EQ(eColor.getC0(),     0xDD);
  EXPECT_EQ(eColor.getC1(),     0xCC);
  EXPECT_EQ(eColor.getC2(),     0xBB);

  bColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  EXPECT_EQ(bColor.getRed(),    0xBB);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xDD);
  EXPECT_EQ(bColor.getAlpha(),  0xAA);

  EXPECT_EQ(bColor.getC0(),     0xBB);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xDD);
  EXPECT_EQ(bColor.getC3(),     0xAA);

  bColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(bColor.getRed(),    0xDD);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xBB);
  EXPECT_EQ(bColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(bColor.getC0(),     0xDD);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xBB);
  EXPECT_EQ(bColor.getC3(),     0xAA); // From before

  fColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(fColor.getRed(),    0xDD);
  EXPECT_EQ(fColor.getGreen(),  0xCC);
  EXPECT_EQ(fColor.getBlue(),   0xBB);

  EXPECT_EQ(fColor.getC2(),     0xDD);
  EXPECT_EQ(fColor.getC1(),     0xCC);
  EXPECT_EQ(fColor.getC0(),     0xBB);

  cColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xDD);
  EXPECT_EQ(cColor.getAlpha(),  0xAA);

  EXPECT_EQ(cColor.getC2(),     0xBB);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xDD);
  EXPECT_EQ(cColor.getC3(),     0xAA);

  cColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(cColor.getRed(),    0xDD);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xBB);
  EXPECT_EQ(cColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(cColor.getC2(),     0xDD);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xBB);
  EXPECT_EQ(cColor.getC3(),     0xAA); // From before

  dColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  EXPECT_EQ(dColor.getRed(),    0xBB);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xDD);
  EXPECT_EQ(dColor.getAlpha(),  0xAA);

  EXPECT_EQ(dColor.getC3(),     0xBB);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xDD);
  EXPECT_EQ(dColor.getC0(),     0xAA);

  dColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(dColor.getRed(),    0xDD);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xBB);
  EXPECT_EQ(dColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(dColor.getC3(),     0xDD);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xBB);
  EXPECT_EQ(dColor.getC0(),     0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_fromLogPackIntABGR, bit8) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  EXPECT_EQ(aColor.getRed(),    0xBB);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xDD);
  EXPECT_EQ(aColor.getAlpha(),  0xAA);

  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xDD);
  EXPECT_EQ(aColor.getC0(),     0xAA);

  aColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(aColor.getRed(),    0xDD);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xBB);
  EXPECT_EQ(aColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(aColor.getC1(),     0xDD);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xBB);
  EXPECT_EQ(aColor.getC0(),     0xAA); // From before

  eColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(eColor.getRed(),    0xDD);
  EXPECT_EQ(eColor.getGreen(),  0xCC);
  EXPECT_EQ(eColor.getBlue(),   0xBB);

  EXPECT_EQ(eColor.getC0(),     0xDD);
  EXPECT_EQ(eColor.getC1(),     0xCC);
  EXPECT_EQ(eColor.getC2(),     0xBB);

  bColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  EXPECT_EQ(bColor.getRed(),    0xBB);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xDD);
  EXPECT_EQ(bColor.getAlpha(),  0xAA);

  EXPECT_EQ(bColor.getC0(),     0xBB);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xDD);
  EXPECT_EQ(bColor.getC3(),     0xAA);

  bColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(bColor.getRed(),    0xDD);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xBB);
  EXPECT_EQ(bColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(bColor.getC0(),     0xDD);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xBB);
  EXPECT_EQ(bColor.getC3(),     0xAA); // From before

  fColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(fColor.getRed(),    0xDD);
  EXPECT_EQ(fColor.getGreen(),  0xCC);
  EXPECT_EQ(fColor.getBlue(),   0xBB);

  EXPECT_EQ(fColor.getC2(),     0xDD);
  EXPECT_EQ(fColor.getC1(),     0xCC);
  EXPECT_EQ(fColor.getC0(),     0xBB);

  cColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xDD);
  EXPECT_EQ(cColor.getAlpha(),  0xAA);

  EXPECT_EQ(cColor.getC2(),     0xBB);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xDD);
  EXPECT_EQ(cColor.getC3(),     0xAA);

  cColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(cColor.getRed(),    0xDD);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xBB);
  EXPECT_EQ(cColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(cColor.getC2(),     0xDD);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xBB);
  EXPECT_EQ(cColor.getC3(),     0xAA); // From before

  dColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  EXPECT_EQ(dColor.getRed(),    0xBB);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xDD);
  EXPECT_EQ(dColor.getAlpha(),  0xAA);

  EXPECT_EQ(dColor.getC3(),     0xBB);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xDD);
  EXPECT_EQ(dColor.getC0(),     0xAA);

  dColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(dColor.getRed(),    0xDD);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xBB);
  EXPECT_EQ(dColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(dColor.getC3(),     0xDD);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xBB);
  EXPECT_EQ(dColor.getC0(),     0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_fromLogPackIntABRG, bit8) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  EXPECT_EQ(aColor.getRed(),    0xBB);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xDD);
  EXPECT_EQ(aColor.getAlpha(),  0xAA);

  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xDD);
  EXPECT_EQ(aColor.getC0(),     0xAA);

  aColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(aColor.getRed(),    0xDD);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xBB);
  EXPECT_EQ(aColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(aColor.getC1(),     0xDD);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xBB);
  EXPECT_EQ(aColor.getC0(),     0xAA); // From before

  eColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(eColor.getRed(),    0xDD);
  EXPECT_EQ(eColor.getGreen(),  0xCC);
  EXPECT_EQ(eColor.getBlue(),   0xBB);

  EXPECT_EQ(eColor.getC0(),     0xDD);
  EXPECT_EQ(eColor.getC1(),     0xCC);
  EXPECT_EQ(eColor.getC2(),     0xBB);

  bColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  EXPECT_EQ(bColor.getRed(),    0xBB);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xDD);
  EXPECT_EQ(bColor.getAlpha(),  0xAA);

  EXPECT_EQ(bColor.getC0(),     0xBB);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xDD);
  EXPECT_EQ(bColor.getC3(),     0xAA);

  bColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(bColor.getRed(),    0xDD);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xBB);
  EXPECT_EQ(bColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(bColor.getC0(),     0xDD);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xBB);
  EXPECT_EQ(bColor.getC3(),     0xAA); // From before

  fColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(fColor.getRed(),    0xDD);
  EXPECT_EQ(fColor.getGreen(),  0xCC);
  EXPECT_EQ(fColor.getBlue(),   0xBB);

  EXPECT_EQ(fColor.getC2(),     0xDD);
  EXPECT_EQ(fColor.getC1(),     0xCC);
  EXPECT_EQ(fColor.getC0(),     0xBB);

  cColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xDD);
  EXPECT_EQ(cColor.getAlpha(),  0xAA);

  EXPECT_EQ(cColor.getC2(),     0xBB);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xDD);
  EXPECT_EQ(cColor.getC3(),     0xAA);

  cColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(cColor.getRed(),    0xDD);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xBB);
  EXPECT_EQ(cColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(cColor.getC2(),     0xDD);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xBB);
  EXPECT_EQ(cColor.getC3(),     0xAA); // From before

  dColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  EXPECT_EQ(dColor.getRed(),    0xBB);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xDD);
  EXPECT_EQ(dColor.getAlpha(),  0xAA);

  EXPECT_EQ(dColor.getC3(),     0xBB);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xDD);
  EXPECT_EQ(dColor.getC0(),     0xAA);

  dColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(dColor.getRed(),    0xDD);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xBB);
  EXPECT_EQ(dColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(dColor.getC3(),     0xDD);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xBB);
  EXPECT_EQ(dColor.getC0(),     0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_fromLogPackIntBGRA, bit8) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorBGRA8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  EXPECT_EQ(aColor.getRed(),    0xBB);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xDD);
  EXPECT_EQ(aColor.getAlpha(),  0xAA);

  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xDD);
  EXPECT_EQ(aColor.getC0(),     0xAA);

  aColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(aColor.getRed(),    0xDD);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xBB);
  EXPECT_EQ(aColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(aColor.getC1(),     0xDD);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xBB);
  EXPECT_EQ(aColor.getC0(),     0xAA); // From before

  eColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(eColor.getRed(),    0xDD);
  EXPECT_EQ(eColor.getGreen(),  0xCC);
  EXPECT_EQ(eColor.getBlue(),   0xBB);

  EXPECT_EQ(eColor.getC0(),     0xDD);
  EXPECT_EQ(eColor.getC1(),     0xCC);
  EXPECT_EQ(eColor.getC2(),     0xBB);

  bColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  EXPECT_EQ(bColor.getRed(),    0xBB);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xDD);
  EXPECT_EQ(bColor.getAlpha(),  0xAA);

  EXPECT_EQ(bColor.getC0(),     0xBB);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xDD);
  EXPECT_EQ(bColor.getC3(),     0xAA);

  bColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(bColor.getRed(),    0xDD);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xBB);
  EXPECT_EQ(bColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(bColor.getC0(),     0xDD);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xBB);
  EXPECT_EQ(bColor.getC3(),     0xAA); // From before

  fColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(fColor.getRed(),    0xDD);
  EXPECT_EQ(fColor.getGreen(),  0xCC);
  EXPECT_EQ(fColor.getBlue(),   0xBB);

  EXPECT_EQ(fColor.getC2(),     0xDD);
  EXPECT_EQ(fColor.getC1(),     0xCC);
  EXPECT_EQ(fColor.getC0(),     0xBB);

  cColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xDD);
  EXPECT_EQ(cColor.getAlpha(),  0xAA);

  EXPECT_EQ(cColor.getC2(),     0xBB);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xDD);
  EXPECT_EQ(cColor.getC3(),     0xAA);

  cColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(cColor.getRed(),    0xDD);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xBB);
  EXPECT_EQ(cColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(cColor.getC2(),     0xDD);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xBB);
  EXPECT_EQ(cColor.getC3(),     0xAA); // From before

  dColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  EXPECT_EQ(dColor.getRed(),    0xBB);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xDD);
  EXPECT_EQ(dColor.getAlpha(),  0xAA);

  EXPECT_EQ(dColor.getC2(),     0xBB);
  EXPECT_EQ(dColor.getC1(),     0xCC);
  EXPECT_EQ(dColor.getC0(),     0xDD);
  EXPECT_EQ(dColor.getC3(),     0xAA);

  dColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(dColor.getRed(),    0xDD);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xBB);
  EXPECT_EQ(dColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(dColor.getC2(),     0xDD);
  EXPECT_EQ(dColor.getC1(),     0xCC);
  EXPECT_EQ(dColor.getC0(),     0xBB);
  EXPECT_EQ(dColor.getC3(),     0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_fromLogPackIntARGB, bit16) {

  // We really just need to make sure the scale works for 16bit -- i.e. that the bytes of the integer are truely inturprted by set*_byte() members.

  mjr::colorRGBA16b bColor;
  mjr::colorRGB16b  eColor;

  bColor.setRGBAfromLogPackIntARGB(0xFF00FF80);

  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getBlue(),   0x8080);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA16b::maxChanVal);

  EXPECT_EQ(bColor.getC0(),     mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(bColor.getC1(),     mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getC2(),     0x8080);
  EXPECT_EQ(bColor.getC3(),     mjr::colorRGBA16b::maxChanVal);

  bColor.setRGBfromLogPackIntARGB(0x00FF00FF);

  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(bColor.getBlue(),   mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA16b::maxChanVal); // From before

  EXPECT_EQ(bColor.getC0(),     mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getC1(),     mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(bColor.getC2(),     mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getC3(),     mjr::colorRGBA16b::maxChanVal); // From before

  eColor.setRGBfromLogPackIntARGB(0x00FF00FF);

  EXPECT_EQ(eColor.getRed(),    mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(eColor.getGreen(),  mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(eColor.getBlue(),   mjr::colorRGBA16b::maxChanVal);

  EXPECT_EQ(eColor.getC0(),     mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(eColor.getC1(),     mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(eColor.getC2(),     mjr::colorRGBA16b::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_saved_fromLogPackIntARGB, bit8) {

  // Make sure channels that should not be changed are not.

  mjr::colorRGBA8b bColor;
  mjr::color5c8b   cColor;

  bColor.setToWhite();
  bColor.setRGBfromLogPackIntARGB(0x00000000);

  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(bColor.getBlue(),   mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal);

  bColor.setToBlack();
  bColor.setRGBfromLogPackIntARGB(0xFFFFFFFF);

  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(bColor.getBlue(),   mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA8b::minChanVal);

  cColor.setToWhite();
  cColor.setRGBAfromLogPackIntARGB(0x00000000);

  EXPECT_EQ(cColor.getRed(),    mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getGreen(),  mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getBlue(),   mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getAlpha(),  mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getChan(4),  mjr::colorRGBA8b::maxChanVal);

  cColor.setToBlack();
  cColor.setRGBAfromLogPackIntARGB(0xFFFFFFFF);

  EXPECT_EQ(cColor.getRed(),    mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getGreen(),  mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getBlue(),   mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getChan(4),  mjr::colorRGBA8b::minChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_setRGBcmpGreyTGA16bit, bit8) {

  mjr::colorRGBA8b aColor;
  mjr::colorRGB8b  bColor;

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA16bit(0x0000);

  EXPECT_EQ(bColor.getRed(),    0x00);
  EXPECT_EQ(bColor.getGreen(),  0x00);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0x00);
  EXPECT_EQ(bColor.getC1(),     0x00);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA16bit(0xFFFF);

  EXPECT_EQ(bColor.getRed(),    0xFF);
  EXPECT_EQ(bColor.getGreen(),  0xFF);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0xFF);
  EXPECT_EQ(bColor.getC1(),     0xFF);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA16bit(0xAABB);

  EXPECT_EQ(bColor.getRed(),    0xAA);
  EXPECT_EQ(bColor.getGreen(),  0xBB);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0xAA);
  EXPECT_EQ(bColor.getC1(),     0xBB);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA16bit(0x0000);

  EXPECT_EQ(bColor.getRed(),    0x00);
  EXPECT_EQ(bColor.getGreen(),  0x00);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0x00);
  EXPECT_EQ(bColor.getC1(),     0x00);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA16bit(0xFFFF);

  EXPECT_EQ(bColor.getRed(),    0xFF);
  EXPECT_EQ(bColor.getGreen(),  0xFF);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0xFF);
  EXPECT_EQ(bColor.getC1(),     0xFF);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA16bit(0xAABB);

  EXPECT_EQ(bColor.getRed(),    0xAA);
  EXPECT_EQ(bColor.getGreen(),  0xBB);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0xAA);
  EXPECT_EQ(bColor.getC1(),     0xBB);
  EXPECT_EQ(bColor.getC2(),     0x00);

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA16bit(0x0000);

  EXPECT_EQ(aColor.getRed(),    0x00);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0x00);
  EXPECT_EQ(aColor.getC1(),     0x00);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA16bit(0xFFFF);

  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0xFF);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0xFF);
  EXPECT_EQ(aColor.getC1(),     0xFF);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA16bit(0xAABB);

  EXPECT_EQ(aColor.getRed(),    0xAA);
  EXPECT_EQ(aColor.getGreen(),  0xBB);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0xAA);
  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA16bit(0x0000);

  EXPECT_EQ(aColor.getRed(),    0x00);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0x00);
  EXPECT_EQ(aColor.getC1(),     0x00);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA16bit(0xFFFF);

  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0xFF);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0xFF);
  EXPECT_EQ(aColor.getC1(),     0xFF);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA16bit(0xAABB);

  EXPECT_EQ(aColor.getRed(),    0xAA);
  EXPECT_EQ(aColor.getGreen(),  0xBB);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0xAA);
  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0xFF);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_setRGBcmpGreyTGA24bit, bit8) {

  mjr::colorRGBA8b aColor;
  mjr::colorRGB8b  bColor;

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA24bit(0x00000000);

  EXPECT_EQ(bColor.getRed(),    0x00);
  EXPECT_EQ(bColor.getGreen(),  0x00);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0x00);
  EXPECT_EQ(bColor.getC1(),     0x00);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  EXPECT_EQ(bColor.getRed(),    0xFF);
  EXPECT_EQ(bColor.getGreen(),  0xFF);
  EXPECT_EQ(bColor.getBlue(),   0xFF);

  EXPECT_EQ(bColor.getC0(),     0xFF);
  EXPECT_EQ(bColor.getC1(),     0xFF);
  EXPECT_EQ(bColor.getC2(),     0xFF);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  EXPECT_EQ(bColor.getRed(),    0xAA);
  EXPECT_EQ(bColor.getGreen(),  0xBB);
  EXPECT_EQ(bColor.getBlue(),   0xCC);

  EXPECT_EQ(bColor.getC0(),     0xAA);
  EXPECT_EQ(bColor.getC1(),     0xBB);
  EXPECT_EQ(bColor.getC2(),     0xCC);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA24bit(0x00000000);

  EXPECT_EQ(bColor.getRed(),    0x00);
  EXPECT_EQ(bColor.getGreen(),  0x00);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0x00);
  EXPECT_EQ(bColor.getC1(),     0x00);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  EXPECT_EQ(bColor.getRed(),    0xFF);
  EXPECT_EQ(bColor.getGreen(),  0xFF);
  EXPECT_EQ(bColor.getBlue(),   0xFF);

  EXPECT_EQ(bColor.getC0(),     0xFF);
  EXPECT_EQ(bColor.getC1(),     0xFF);
  EXPECT_EQ(bColor.getC2(),     0xFF);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  EXPECT_EQ(bColor.getRed(),    0xAA);
  EXPECT_EQ(bColor.getGreen(),  0xBB);
  EXPECT_EQ(bColor.getBlue(),   0xCC);

  EXPECT_EQ(bColor.getC0(),     0xAA);
  EXPECT_EQ(bColor.getC1(),     0xBB);
  EXPECT_EQ(bColor.getC2(),     0xCC);

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA24bit(0x00000000);

  EXPECT_EQ(aColor.getRed(),    0x00);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0x00);
  EXPECT_EQ(aColor.getC1(),     0x00);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0xFF);
  EXPECT_EQ(aColor.getBlue(),   0xFF);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0xFF);
  EXPECT_EQ(aColor.getC1(),     0xFF);
  EXPECT_EQ(aColor.getC2(),     0xFF);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  EXPECT_EQ(aColor.getRed(),    0xAA);
  EXPECT_EQ(aColor.getGreen(),  0xBB);
  EXPECT_EQ(aColor.getBlue(),   0xCC);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0xAA);
  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA24bit(0x00000000);

  EXPECT_EQ(aColor.getRed(),    0x00);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0x00);
  EXPECT_EQ(aColor.getC1(),     0x00);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0xFF);
  EXPECT_EQ(aColor.getBlue(),   0xFF);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0xFF);
  EXPECT_EQ(aColor.getC1(),     0xFF);
  EXPECT_EQ(aColor.getC2(),     0xFF);
  EXPECT_EQ(aColor.getC3(),     0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  EXPECT_EQ(aColor.getRed(),    0xAA);
  EXPECT_EQ(aColor.getGreen(),  0xBB);
  EXPECT_EQ(aColor.getBlue(),   0xCC);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0xAA);
  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xFF);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(tfrm_logic_cover, Comprehensive) {

  mjr::colorRGBA8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorRGBA8b cColor;

  aColor.setRGBAfromLogPackIntRGBA(0xAABBCCDD);
  bColor.setRGBAfromLogPackIntRGBA(0x11223344);

  EXPECT_EQ(aColor.getRed(),    0xAA);
  EXPECT_EQ(aColor.getGreen(),  0xBB);
  EXPECT_EQ(aColor.getBlue(),   0xCC);
  EXPECT_EQ(aColor.getAlpha(),  0xDD);

  EXPECT_EQ(bColor.getRed(),    0x11);
  EXPECT_EQ(bColor.getGreen(),  0x22);
  EXPECT_EQ(bColor.getBlue(),   0x33);
  EXPECT_EQ(bColor.getAlpha(),  0x44);

  cColor = aColor;
  cColor.tfrmNot();
  EXPECT_EQ(cColor.getRed(),    0x55);
  EXPECT_EQ(cColor.getGreen(),  0x44);
  EXPECT_EQ(cColor.getBlue(),   0x33);
  EXPECT_EQ(cColor.getAlpha(),  0x22);

  cColor = aColor;
  cColor.tfrmOr(bColor);
  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xBB);
  EXPECT_EQ(cColor.getBlue(),   0xFF);
  EXPECT_EQ(cColor.getAlpha(),  0xDD);

  cColor = aColor;
  cColor.tfrmNor(bColor);
  EXPECT_EQ(cColor.getRed(),    0x44);
  EXPECT_EQ(cColor.getGreen(),  0x44);
  EXPECT_EQ(cColor.getBlue(),   0x00);
  EXPECT_EQ(cColor.getAlpha(),  0x22);

  cColor = aColor;
  cColor.tfrmAnd(bColor);
  EXPECT_EQ(cColor.getRed(),    0x00);
  EXPECT_EQ(cColor.getGreen(),  0x22);
  EXPECT_EQ(cColor.getBlue(),   0x00);
  EXPECT_EQ(cColor.getAlpha(),  0x44);

  cColor = aColor;
  cColor.tfrmNand(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0xDD);
  EXPECT_EQ(cColor.getBlue(),   0xFF);
  EXPECT_EQ(cColor.getAlpha(),  0xBB);

  cColor = aColor;
  cColor.tfrmXor(bColor);
  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0x99);
  EXPECT_EQ(cColor.getBlue(),   0xFF);
  EXPECT_EQ(cColor.getAlpha(),  0x99);

  cColor = aColor;
  cColor.tfrmNxor(bColor);
  EXPECT_EQ(cColor.getRed(),    0x44);
  EXPECT_EQ(cColor.getGreen(),  0x66);
  EXPECT_EQ(cColor.getBlue(),   0x00);
  EXPECT_EQ(cColor.getAlpha(),  0x66);

//  MJR TODO NOTE  Add tfrmShiftL & tfrmShiftR

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(tfrm_logic_noCover, Comprehensive) {

  mjr::colorRGBA64b aColor;
  mjr::colorRGBA64b bColor;
  mjr::colorRGBA64b cColor;

  aColor.setChansRGBA(0xAAAAAAAAAAAAAAAAu, 0xBBBBBBBBBBBBBBBBu, 0xCCCCCCCCCCCCCCCCu, 0xDDDDDDDDDDDDDDDDu);
  bColor.setChansRGBA(0x1111111111111111u, 0x2222222222222222u, 0x3333333333333333u, 0x4444444444444444u);

  EXPECT_EQ(aColor.getRed(),    0xAAAAAAAAAAAAAAAAu);
  EXPECT_EQ(aColor.getGreen(),  0xBBBBBBBBBBBBBBBBu);
  EXPECT_EQ(aColor.getBlue(),   0xCCCCCCCCCCCCCCCCu);
  EXPECT_EQ(aColor.getAlpha(),  0xDDDDDDDDDDDDDDDDu);

  EXPECT_EQ(bColor.getRed(),    0x1111111111111111u);
  EXPECT_EQ(bColor.getGreen(),  0x2222222222222222u);
  EXPECT_EQ(bColor.getBlue(),   0x3333333333333333u);
  EXPECT_EQ(bColor.getAlpha(),  0x4444444444444444u);

  cColor = aColor;
  cColor.tfrmNot();
  EXPECT_EQ(cColor.getRed(),    0x5555555555555555u);
  EXPECT_EQ(cColor.getGreen(),  0x4444444444444444u);
  EXPECT_EQ(cColor.getBlue(),   0x3333333333333333u);
  EXPECT_EQ(cColor.getAlpha(),  0x2222222222222222u);

  cColor = aColor;
  cColor.tfrmOr(bColor);
  EXPECT_EQ(cColor.getRed(),    0xBBBBBBBBBBBBBBBBu);
  EXPECT_EQ(cColor.getGreen(),  0xBBBBBBBBBBBBBBBBu);
  EXPECT_EQ(cColor.getBlue(),   0xFFFFFFFFFFFFFFFFu);
  EXPECT_EQ(cColor.getAlpha(),  0xDDDDDDDDDDDDDDDDu);

  cColor = aColor;
  cColor.tfrmNor(bColor);
  EXPECT_EQ(cColor.getRed(),    0x4444444444444444u);
  EXPECT_EQ(cColor.getGreen(),  0x4444444444444444u);
  EXPECT_EQ(cColor.getBlue(),   0x0000000000000000u);
  EXPECT_EQ(cColor.getAlpha(),  0x2222222222222222u);

  cColor = aColor;
  cColor.tfrmAnd(bColor);
  EXPECT_EQ(cColor.getRed(),    0x0000000000000000u);
  EXPECT_EQ(cColor.getGreen(),  0x2222222222222222u);
  EXPECT_EQ(cColor.getBlue(),   0x0000000000000000u);
  EXPECT_EQ(cColor.getAlpha(),  0x4444444444444444u);

  cColor = aColor;
  cColor.tfrmNand(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFFFFFFFFFFFFFFFFu);
  EXPECT_EQ(cColor.getGreen(),  0xDDDDDDDDDDDDDDDDu);
  EXPECT_EQ(cColor.getBlue(),   0xFFFFFFFFFFFFFFFFu);
  EXPECT_EQ(cColor.getAlpha(),  0xBBBBBBBBBBBBBBBBu);

  cColor = aColor;
  cColor.tfrmXor(bColor);
  EXPECT_EQ(cColor.getRed(),    0xBBBBBBBBBBBBBBBBu);
  EXPECT_EQ(cColor.getGreen(),  0x9999999999999999u);
  EXPECT_EQ(cColor.getBlue(),   0xFFFFFFFFFFFFFFFFu);
  EXPECT_EQ(cColor.getAlpha(),  0x9999999999999999u);

  cColor = aColor;
  cColor.tfrmNxor(bColor);
  EXPECT_EQ(cColor.getRed(),    0x4444444444444444u);
  EXPECT_EQ(cColor.getGreen(),  0x6666666666666666u);
  EXPECT_EQ(cColor.getBlue(),   0x0000000000000000u);
  EXPECT_EQ(cColor.getAlpha(),  0x6666666666666666u);


//  MJR TODO NOTE  Add tfrmShiftL & tfrmShiftR
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_tfrm_arith, bit8) {

  mjr::colorRGB8b aColor;
  mjr::colorRGB8b bColor;
  mjr::colorRGB8b dColor;
  mjr::colorRGB8b cColor;

  aColor.setRGBfromLogPackIntARGB(0xFF00FF);
  bColor.setRGBfromLogPackIntARGB(0x00FFFF);
  dColor.setRGBfromLogPackIntARGB(0x0100FF);

  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0xFF);

  EXPECT_EQ(bColor.getRed(),    0x00);
  EXPECT_EQ(bColor.getGreen(),  0xFF);
  EXPECT_EQ(bColor.getBlue(),   0xFF);

  EXPECT_EQ(dColor.getRed(),    0x01);
  EXPECT_EQ(dColor.getGreen(),  0x00);
  EXPECT_EQ(dColor.getBlue(),   0xFF);

  cColor=aColor;
  cColor.tfrmMix(0.0, bColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMix(0.5, bColor);
  EXPECT_EQ(cColor.getC0(),  0x7F);
  EXPECT_EQ(cColor.getC1(),  0x7F);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMix(1.0, bColor);
  EXPECT_EQ(cColor.getC0(),  0x00);
  EXPECT_EQ(cColor.getC1(),  0xFF);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor = aColor;
  cColor.tfrmInvert();
  EXPECT_EQ(cColor.getRed(),    0x00);
  EXPECT_EQ(cColor.getGreen(),  0xFF);
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmAdd(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0xFF);
  EXPECT_EQ(cColor.getBlue(),   0xFE); // Overflow wrap

  cColor = aColor;
  cColor.tfrmAddClamp(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0xFF);
  EXPECT_EQ(cColor.getBlue(),   0xFF); // Overflow clamp

  cColor = aColor;
  cColor.tfrmMult(bColor);
  EXPECT_EQ(cColor.getRed(),    0x00);
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0x01); // Overflow wrap

  cColor = aColor;
  cColor.tfrmMultClamp(bColor);
  EXPECT_EQ(cColor.getRed(),    0x00);
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0xFF); // Overflow clamp

  cColor = aColor;
  cColor.tfrmDiv(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF); // NOOP as bot=0
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0x01);

  cColor = aColor;
  cColor.tfrmMod(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF); // NOOP as bot=0
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmDiff(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0x01); // Underflow wrap
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmDiffClamp(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0x00); // Overflow clamp
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmAbsDiff(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0xFF);
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmSqDiff(bColor);
  EXPECT_EQ(cColor.getRed(),    0x01); // Overflow wrap
  EXPECT_EQ(cColor.getGreen(),  0x01); // Overflow wrap
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmNegDiffClamp(bColor);
  EXPECT_EQ(cColor.getRed(),    0x00); // Overflow clamp
  EXPECT_EQ(cColor.getGreen(),  0xFF);
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmAddDivClamp(bColor, dColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0x02);

  cColor = aColor;
  cColor.tfrmSignDiff(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0x7F);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_tfrm_arith, float) {

  mjr::colorRGB32F aColor;
  mjr::colorRGB32F bColor;
  mjr::colorRGB32F dColor;
  mjr::colorRGB32F cColor;

  aColor.setChansRGB(2.0, 0.0, 2.0);
  bColor.setChansRGB(0.0, 2.0, 2.0);
  dColor.setChansRGB(0.0, 2.0, 2.0);

  cColor=aColor;
  cColor.tfrmMix(0.0, bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMix(0.5, bColor);
  EXPECT_NEAR(cColor.getC0(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMix(1.0, bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor = aColor;
  cColor.tfrmInvert();
  EXPECT_NEAR(cColor.getC0(),  -1.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),   1.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  -1.0, 0.00001);

  cColor = aColor;
  cColor.tfrmAdd(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  4.0, 0.00001);

  cColor = aColor;
  cColor.tfrmAddClamp(bColor);
  EXPECT_NEAR(cColor.getC0(),  1.0, 0.00001); // clamped to maxChanVal
  EXPECT_NEAR(cColor.getC1(),  1.0, 0.00001); // clamped to maxChanVal
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001); // clamped to maxChanVal

  cColor = aColor;
  cColor.tfrmMult(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  4.0, 0.00001);

  cColor = aColor;
  cColor.tfrmMultClamp(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001); // clamped to maxChanVal

  cColor = aColor;
  cColor.tfrmDiv(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001); // NOOP as bot=0
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001);

  cColor = aColor;
  cColor.tfrmMod(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001); // NOOP as bot=0
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmDiff(bColor);
  EXPECT_NEAR(cColor.getC0(),   2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  -2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),   0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmDiffClamp(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001); // Clamp on bottom only
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001); //clamped to minChanVal
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmAbsDiff(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmSqDiff(bColor);
  EXPECT_NEAR(cColor.getC0(),  4.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  4.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmNegDiffClamp(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001); // Underflow clamp bottom
  EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmAddDivClamp(bColor, dColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001); // NOOP bot=0
  EXPECT_NEAR(cColor.getC1(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001); // Overflow clamp at top

  cColor = aColor;
  cColor.tfrmSignDiff(bColor);
  EXPECT_NEAR(cColor.getC0(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.5, 0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_isBlack_and_isBlackRGB, Comprehensive)  {

  mjr::colorRGB8b   aColor; // integer color with imperfect mask
  mjr::colorRGBA8b  bColor; // integer color with perfect mask
  mjr::colorRGB64b  cColor; // integer color without mask
  mjr::colorRGB32F  dColor; // floating point color with mask
  mjr::colorRGBA32F fColor; // floating point color with perfect mask
  mjr::colorRGB64F  gColor; // floating point color without mask

  aColor.setToBlack();
  bColor.setToBlack();
  cColor.setToBlack();
  dColor.setToBlack();
  fColor.setToBlack();
  gColor.setToBlack();

  EXPECT_TRUE(aColor.isBlackRGB());
  EXPECT_TRUE(bColor.isBlackRGB());
  EXPECT_TRUE(cColor.isBlackRGB());
  EXPECT_TRUE(dColor.isBlackRGB());
  EXPECT_TRUE(fColor.isBlackRGB());
  EXPECT_TRUE(gColor.isBlackRGB());

  EXPECT_TRUE(aColor.isBlack());
  EXPECT_TRUE(bColor.isBlack());
  EXPECT_TRUE(cColor.isBlack());
  EXPECT_TRUE(dColor.isBlack());
  EXPECT_TRUE(fColor.isBlack());
  EXPECT_TRUE(gColor.isBlack());

  aColor.setChanToMax(0);
  bColor.setChanToMax(0);
  cColor.setChanToMax(0);
  dColor.setChanToMax(0);
  fColor.setChanToMax(0);
  gColor.setChanToMax(0);

  EXPECT_FALSE(aColor.isBlackRGB());
  EXPECT_FALSE(bColor.isBlackRGB());
  EXPECT_FALSE(cColor.isBlackRGB());
  EXPECT_FALSE(dColor.isBlackRGB());
  EXPECT_FALSE(fColor.isBlackRGB());
  EXPECT_FALSE(gColor.isBlackRGB());

  EXPECT_FALSE(aColor.isBlack());
  EXPECT_FALSE(bColor.isBlack());
  EXPECT_FALSE(cColor.isBlack());
  EXPECT_FALSE(dColor.isBlack());
  EXPECT_FALSE(fColor.isBlack());
  EXPECT_FALSE(gColor.isBlack());

  aColor.setToWhite();
  bColor.setToWhite();
  cColor.setToWhite();
  dColor.setToWhite();
  fColor.setToWhite();
  gColor.setToWhite();

  EXPECT_FALSE(aColor.isBlackRGB());
  EXPECT_FALSE(bColor.isBlackRGB());
  EXPECT_FALSE(cColor.isBlackRGB());
  EXPECT_FALSE(dColor.isBlackRGB());
  EXPECT_FALSE(fColor.isBlackRGB());
  EXPECT_FALSE(gColor.isBlackRGB());

  EXPECT_FALSE(aColor.isBlack());
  EXPECT_FALSE(bColor.isBlack());
  EXPECT_FALSE(cColor.isBlack());
  EXPECT_FALSE(dColor.isBlack());
  EXPECT_FALSE(fColor.isBlack());
  EXPECT_FALSE(gColor.isBlack());

  bColor.setChansRGBA(0, 0, 0, 1);
  fColor.setChansRGBA(0, 0, 0, 1);

  EXPECT_TRUE(bColor.isBlackRGB());
  EXPECT_TRUE(fColor.isBlackRGB());

  EXPECT_FALSE(bColor.isBlack());
  EXPECT_FALSE(fColor.isBlack());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_isEqual_and_isEqualRGB_and_isNotEqual, Comprehensive) {

  mjr::colorRGB8b   aLcolor; // integer color with imperfect mask
  mjr::colorRGBA8b  bLcolor; // integer color with perfect mask
  mjr::colorRGB64b  cLcolor; // integer color without mask
  mjr::colorRGB32F  dLcolor; // floating point color with mask
  mjr::colorRGBA32F fLcolor; // floating point color with perfect mask
  mjr::colorRGB64F  gLcolor; // floating point color without mask

  mjr::colorRGB8b   aRcolor; // integer color with imperfect mask
  mjr::colorRGBA8b  bRcolor; // integer color with perfect mask
  mjr::colorRGB64b  cRcolor; // integer color without mask
  mjr::colorRGB32F  dRcolor; // floating point color with mask
  mjr::colorRGBA32F fRcolor; // floating point color with perfect mask
  mjr::colorRGB64F  gRcolor; // floating point color without mask

  aLcolor.setToBlack();
  bLcolor.setToBlack();
  cLcolor.setToBlack();
  dLcolor.setToBlack();
  fLcolor.setToBlack();
  gLcolor.setToBlack();

  aRcolor.setToBlack();
  bRcolor.setToBlack();
  cRcolor.setToBlack();
  dRcolor.setToBlack();
  fRcolor.setToBlack();
  gRcolor.setToBlack();

  EXPECT_TRUE(aLcolor.isEqual(aRcolor));
  EXPECT_TRUE(bLcolor.isEqual(bRcolor));
  EXPECT_TRUE(cLcolor.isEqual(cRcolor));
  EXPECT_TRUE(dLcolor.isEqual(dRcolor));
  EXPECT_TRUE(fLcolor.isEqual(fRcolor));
  EXPECT_TRUE(gLcolor.isEqual(gRcolor));

  EXPECT_FALSE(aLcolor.isNotEqual(aRcolor));
  EXPECT_FALSE(bLcolor.isNotEqual(bRcolor));
  EXPECT_FALSE(cLcolor.isNotEqual(cRcolor));
  EXPECT_FALSE(dLcolor.isNotEqual(dRcolor));
  EXPECT_FALSE(fLcolor.isNotEqual(fRcolor));
  EXPECT_FALSE(gLcolor.isNotEqual(gRcolor));

  EXPECT_TRUE(aLcolor.isEqualRGB(aRcolor));
  EXPECT_TRUE(bLcolor.isEqualRGB(bRcolor));
  EXPECT_TRUE(cLcolor.isEqualRGB(cRcolor));
  EXPECT_TRUE(dLcolor.isEqualRGB(dRcolor));
  EXPECT_TRUE(fLcolor.isEqualRGB(fRcolor));
  EXPECT_TRUE(gLcolor.isEqualRGB(gRcolor));

  aLcolor.setChanToMax(0);
  bLcolor.setChanToMax(0);
  cLcolor.setChanToMax(0);
  dLcolor.setChanToMax(0);
  fLcolor.setChanToMax(0);
  gLcolor.setChanToMax(0);

  EXPECT_FALSE(aLcolor.isEqual(aRcolor));
  EXPECT_FALSE(bLcolor.isEqual(bRcolor));
  EXPECT_FALSE(cLcolor.isEqual(cRcolor));
  EXPECT_FALSE(dLcolor.isEqual(dRcolor));
  EXPECT_FALSE(fLcolor.isEqual(fRcolor));
  EXPECT_FALSE(gLcolor.isEqual(gRcolor));

  EXPECT_TRUE(aLcolor.isNotEqual(aRcolor));
  EXPECT_TRUE(bLcolor.isNotEqual(bRcolor));
  EXPECT_TRUE(cLcolor.isNotEqual(cRcolor));
  EXPECT_TRUE(dLcolor.isNotEqual(dRcolor));
  EXPECT_TRUE(fLcolor.isNotEqual(fRcolor));
  EXPECT_TRUE(gLcolor.isNotEqual(gRcolor));

  EXPECT_FALSE(aLcolor.isEqualRGB(aRcolor));
  EXPECT_FALSE(bLcolor.isEqualRGB(bRcolor));
  EXPECT_FALSE(cLcolor.isEqualRGB(cRcolor));
  EXPECT_FALSE(dLcolor.isEqualRGB(dRcolor));
  EXPECT_FALSE(fLcolor.isEqualRGB(fRcolor));
  EXPECT_FALSE(gLcolor.isEqualRGB(gRcolor));

  aRcolor.setChanToMax(0);
  bRcolor.setChanToMax(0);
  cRcolor.setChanToMax(0);
  dRcolor.setChanToMax(0);
  fRcolor.setChanToMax(0);
  gRcolor.setChanToMax(0);

  EXPECT_TRUE(aLcolor.isEqual(aRcolor));
  EXPECT_TRUE(bLcolor.isEqual(bRcolor));
  EXPECT_TRUE(cLcolor.isEqual(cRcolor));
  EXPECT_TRUE(dLcolor.isEqual(dRcolor));
  EXPECT_TRUE(fLcolor.isEqual(fRcolor));
  EXPECT_TRUE(gLcolor.isEqual(gRcolor));

  EXPECT_FALSE(aLcolor.isNotEqual(aRcolor));
  EXPECT_FALSE(bLcolor.isNotEqual(bRcolor));
  EXPECT_FALSE(cLcolor.isNotEqual(cRcolor));
  EXPECT_FALSE(dLcolor.isNotEqual(dRcolor));
  EXPECT_FALSE(fLcolor.isNotEqual(fRcolor));
  EXPECT_FALSE(gLcolor.isNotEqual(gRcolor));

  EXPECT_TRUE(aLcolor.isEqualRGB(aRcolor));
  EXPECT_TRUE(bLcolor.isEqualRGB(bRcolor));
  EXPECT_TRUE(cLcolor.isEqualRGB(cRcolor));
  EXPECT_TRUE(dLcolor.isEqualRGB(dRcolor));
  EXPECT_TRUE(fLcolor.isEqualRGB(fRcolor));
  EXPECT_TRUE(gLcolor.isEqualRGB(gRcolor));

  aLcolor.setToWhite();
  bLcolor.setToWhite();
  cLcolor.setToWhite();
  dLcolor.setToWhite();
  fLcolor.setToWhite();
  gLcolor.setToWhite();

  EXPECT_FALSE(aLcolor.isEqual(aRcolor));
  EXPECT_FALSE(bLcolor.isEqual(bRcolor));
  EXPECT_FALSE(cLcolor.isEqual(cRcolor));
  EXPECT_FALSE(dLcolor.isEqual(dRcolor));
  EXPECT_FALSE(fLcolor.isEqual(fRcolor));
  EXPECT_FALSE(gLcolor.isEqual(gRcolor));

  EXPECT_TRUE(aLcolor.isNotEqual(aRcolor));
  EXPECT_TRUE(bLcolor.isNotEqual(bRcolor));
  EXPECT_TRUE(cLcolor.isNotEqual(cRcolor));
  EXPECT_TRUE(dLcolor.isNotEqual(dRcolor));
  EXPECT_TRUE(fLcolor.isNotEqual(fRcolor));
  EXPECT_TRUE(gLcolor.isNotEqual(gRcolor));

  EXPECT_FALSE(aLcolor.isEqualRGB(aRcolor));
  EXPECT_FALSE(bLcolor.isEqualRGB(bRcolor));
  EXPECT_FALSE(cLcolor.isEqualRGB(cRcolor));
  EXPECT_FALSE(dLcolor.isEqualRGB(dRcolor));
  EXPECT_FALSE(fLcolor.isEqualRGB(fRcolor));
  EXPECT_FALSE(gLcolor.isEqualRGB(gRcolor));

  bLcolor.setChansRGBA(1, 2, 3, 4);
  fLcolor.setChansRGBA(1, 2, 3, 4);

  bRcolor.setChansRGBA(1, 2, 3, 5);
  fRcolor.setChansRGBA(1, 2, 3, 5);

  EXPECT_FALSE(bLcolor.isEqual(bRcolor));
  EXPECT_FALSE(fLcolor.isEqual(fRcolor));

  EXPECT_TRUE(bLcolor.isEqualRGB(bRcolor));
  EXPECT_TRUE(fLcolor.isEqualRGB(fRcolor));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(distHypot_and_distSumAbs_and_distMaxAbs, Integer) {

  mjr::colorRGBA8b   aColor;
  mjr::colorRGBA8b   bColor;

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToBlack();

  EXPECT_NEAR(aColor.distHypot( bColor),  std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*4), 0.00001);
  EXPECT_EQ(aColor.distSumAbs(bColor),  mjr::colorRGBA8b::maxChanVal*4);
  EXPECT_EQ(aColor.distMaxAbs(bColor),  mjr::colorRGBA8b::maxChanVal);

  EXPECT_NEAR(bColor.distHypot( aColor),  std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*4), 0.00001);
  EXPECT_EQ(bColor.distSumAbs(aColor),  mjr::colorRGBA8b::maxChanVal*4);
  EXPECT_EQ(bColor.distMaxAbs(aColor),  mjr::colorRGBA8b::maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToWhite();

  EXPECT_NEAR(aColor.distHypot( bColor),  0, 0.00001);
  EXPECT_EQ(aColor.distSumAbs(bColor),  0);
  EXPECT_EQ(aColor.distMaxAbs(bColor),  0);

  EXPECT_NEAR(bColor.distHypot( aColor),  0, 0.00001);
  EXPECT_EQ(bColor.distSumAbs(aColor),  0);
  EXPECT_EQ(bColor.distMaxAbs(aColor),  0);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToCyan();
  bColor.setToBlack();

  EXPECT_NEAR(aColor.distHypot( bColor),  std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*3), 0.0001);
  EXPECT_EQ(aColor.distSumAbs(bColor),  mjr::colorRGBA8b::maxChanVal*3);
  EXPECT_EQ(aColor.distMaxAbs(bColor),  mjr::colorRGBA8b::maxChanVal);

  EXPECT_NEAR(bColor.distHypot( aColor),  std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*3), 0.0001);
  EXPECT_EQ(bColor.distSumAbs(aColor),  mjr::colorRGBA8b::maxChanVal*3);
  EXPECT_EQ(bColor.distMaxAbs(aColor),  mjr::colorRGBA8b::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(distHypot_and_distSumAbs_and_distMaxAbs, FLoat) {

  mjr::colorRGBA32F   aColor;
  mjr::colorRGBA32F   bColor;

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToBlack();

  EXPECT_NEAR(aColor.distHypot( bColor),  std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*4), 0.00001);
  EXPECT_NEAR(aColor.distSumAbs(bColor),  mjr::colorRGBA32F::maxChanVal*4, 0.00001);
  EXPECT_NEAR(aColor.distMaxAbs(bColor),  mjr::colorRGBA32F::maxChanVal, 0.00001);

  EXPECT_NEAR(bColor.distHypot( aColor),  std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*4), 0.00001);
  EXPECT_NEAR(bColor.distSumAbs(aColor),  mjr::colorRGBA32F::maxChanVal*4, 0.00001);
  EXPECT_NEAR(bColor.distMaxAbs(aColor),  mjr::colorRGBA32F::maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToWhite();

  EXPECT_NEAR(aColor.distHypot( bColor),  0, 0.00001);
  EXPECT_NEAR(aColor.distSumAbs(bColor),  0, 0.00001);
  EXPECT_NEAR(aColor.distMaxAbs(bColor),  0, 0.00001);

  EXPECT_NEAR(bColor.distHypot( aColor),  0, 0.00001);
  EXPECT_NEAR(bColor.distSumAbs(aColor),  0, 0.00001);
  EXPECT_NEAR(bColor.distMaxAbs(aColor),  0, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToCyan();
  bColor.setToBlack();

  EXPECT_NEAR(aColor.distHypot( bColor),  std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*3), 0.00001);
  EXPECT_NEAR(aColor.distSumAbs(bColor),  mjr::colorRGBA32F::maxChanVal*3, 0.00001);
  EXPECT_NEAR(aColor.distMaxAbs(bColor),  mjr::colorRGBA32F::maxChanVal, 0.00001);

  EXPECT_NEAR(bColor.distHypot( aColor),  std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*3), 0.00001);
  EXPECT_NEAR(bColor.distSumAbs(aColor),  mjr::colorRGBA32F::maxChanVal*3, 0.00001);
  EXPECT_NEAR(bColor.distMaxAbs(aColor),  mjr::colorRGBA32F::maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setChansRGBA(0.5, 0.5, 0.5, 0.5);
  bColor.setToBlack();

  EXPECT_NEAR(aColor.distHypot( bColor),  std::sqrt(0.5*0.5*4), 0.00001);
  EXPECT_NEAR(aColor.distSumAbs(bColor),  0.5*4, 0.00001);
  EXPECT_NEAR(aColor.distMaxAbs(bColor),  0.5, 0.00001);

  EXPECT_NEAR(bColor.distHypot( aColor),  std::sqrt(0.5*0.5*4), 0.00001);
  EXPECT_NEAR(bColor.distSumAbs(aColor),  0.5*4, 0.00001);
  EXPECT_NEAR(bColor.distMaxAbs(aColor),  0.5, 0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(luminanceRGB_and_intensity_and_intensityScaledRGB_and_intensityScaled_and_rgb2GreyDotProd, Comprehensive) {

  EXPECT_EQ(mjr::colorRGBA8b( 2, 5, 7, 11).rgb2GreyDotProd(13, 17, 23),           272);
  EXPECT_EQ(mjr::colorRGBA32F(2, 5, 7, 11).rgb2GreyDotProd(13, 17, 23),           272);

  EXPECT_EQ(mjr::colorRGBA8b(255, 255, 255, 255).rgb2GreyDotProd(255, 255, 255),  195075); // Too big for an arith SP type...

  EXPECT_NEAR(mjr::colorRGBA8b( 2, 5, 7, 11).luminanceRGB(),                      0.0176729411765, 0.00001);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 11).luminanceRGB(),                      4.5066,          0.00001);

  EXPECT_EQ(mjr::colorRGBA8b( 2, 5, 7, 11).intensityRGB(),                        14);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 11).intensityRGB(),                      14,              0.00001);

  EXPECT_EQ(mjr::colorRGBA8b( 2, 5, 7, 11).intensity(),                           25);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 11).intensity(),                         25,              0.00001);

  EXPECT_NEAR(mjr::colorRGBA8b( 2, 5, 7, 11).intensityScaledRGB(),                0.0183006562,    0.00001);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 11).intensityScaledRGB(),                4.66666698,      0.00001);

  EXPECT_NEAR(mjr::colorRGBA8b( 2, 5, 7, 11).intensityScaled(),                   0.0245098039216, 0.00001);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 11).intensityScaled(),                   6.25,            0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(dotProd_and_getMaxC_and_getMinC_and_getMinRGB_and_getMaxRGB, Comprehensive) {

  EXPECT_EQ(mjr::colorRGBA8b(2, 5, 7, 11).dotProd(mjr::colorRGBA8b(13, 17, 23, 27)),             569);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 11).dotProd(mjr::colorRGBA32F(13, 17, 23, 27)),         569, 0.000001);

  EXPECT_EQ(mjr::colorRGBA8b(255, 255, 255, 255).dotProd(mjr::colorRGBA8b(255, 255, 255, 255)),  260100); // Too big for an arith SP type...

  EXPECT_EQ(mjr::colorRGBA8b(2, 5, 7, 11).getMaxC(),                                             11);
  EXPECT_EQ(mjr::colorRGBA8b(2, 5, 7, 11).getMaxRGB(),                                           7);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 11).getMaxC(),                                          11, 0.000001);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 11).getMaxRGB(),                                        7, 0.000001);

  EXPECT_EQ(mjr::colorRGBA8b(2, 5, 7, 1).getMinC(),                                              1);
  EXPECT_EQ(mjr::colorRGBA8b(2, 5, 7, 1).getMinRGB(),                                            2);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 1).getMinC(),                                           1, 0.000001);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 1).getMinRGB(),                                         2, 0.000001);

  EXPECT_EQ(mjr::colorRGB8b(2, 5, 7).getMaxC(),                                                  7);
  EXPECT_EQ(mjr::colorRGB32F(2, 5, 7).getMaxC(),                                                 7);

  EXPECT_EQ(mjr::colorRGB8b(2, 5, 7).getMinC(),                                                  2);
  EXPECT_EQ(mjr::colorRGB32F(2, 5, 7).getMinC(),                                                 2);

  mjr::color2c8b aColor; aColor.setC0(5); aColor.setC1(2);
  mjr::color2c8b bColor; bColor.setC0(5); bColor.setC1(2);

  EXPECT_EQ(aColor.getMaxC(),                                                                    5);
  EXPECT_EQ(bColor.getMaxC(),                                                                    5);

  EXPECT_EQ(aColor.getMinC(),                                                                    2);
  EXPECT_EQ(bColor.getMinC(),                                                                    2);

  EXPECT_EQ(mjr::colorRGBA8b(2).getMaxC(),                                                       2);
  EXPECT_NEAR(mjr::colorRGBA32F(2).getMaxC(),                                                    2, 0.000001);

  EXPECT_EQ(mjr::colorRGBA8b(2).getMinC(),                                                       2);
  EXPECT_NEAR(mjr::colorRGBA32F(2).getMinC(),                                                    2, 0.000001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_WavelengthCM, Integer) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA8b  bColor;

  aColor.setToBlack();
  aColor.setRGBfromWavelengthCM(570);
  EXPECT_EQ(aColor.getRed(),    173);
  EXPECT_EQ(aColor.getGreen(),  189);
  EXPECT_EQ(aColor.getBlue(),   2);
  EXPECT_EQ(aColor.getAlpha(),  aColor.minChanVal);

  aColor.setToWhite();
  aColor.setRGBfromWavelengthCM(570);
  EXPECT_EQ(aColor.getRed(),    173);
  EXPECT_EQ(aColor.getGreen(),  189);
  EXPECT_EQ(aColor.getBlue(),   2);
  EXPECT_EQ(aColor.getAlpha(),  aColor.maxChanVal);

  aColor.setRGBfromWavelengthCM(571, mjr::colorRGBA8b::cmfInterpolationEnum::FLOOR);
  bColor.setRGBfromWavelengthCM(570);
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromWavelengthCM(571, mjr::colorRGBA8b::cmfInterpolationEnum::CEILING);
  bColor.setRGBfromWavelengthCM(575);
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromWavelengthCM(571, mjr::colorRGBA8b::cmfInterpolationEnum::NEAREST);
  bColor.setRGBfromWavelengthCM(570);
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromWavelengthCM(574, mjr::colorRGBA8b::cmfInterpolationEnum::NEAREST);
  bColor.setRGBfromWavelengthCM(575);
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromWavelengthCM(572, mjr::colorRGBA8b::cmfInterpolationEnum::LINEAR);
  EXPECT_EQ(aColor.getRed(),    182);
  EXPECT_EQ(aColor.getGreen(),  181);
  EXPECT_EQ(aColor.getBlue(),   0);

  aColor.setRGBfromWavelengthCM(572, mjr::colorRGBA8b::cmfInterpolationEnum::BUMP);
  EXPECT_EQ(aColor.getRed(),    167);
  EXPECT_EQ(aColor.getGreen(),  169);
  EXPECT_EQ(aColor.getBlue(),   0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_WavelengthCM, FLoat) {

  mjr::colorRGBA32F cColor;
  mjr::colorRGBA32F dColor;

  cColor.setToBlack();
  cColor.setRGBfromWavelengthCM(570);
  EXPECT_NEAR(cColor.getRed(),    0.679159,          0.00001);
  EXPECT_NEAR(cColor.getGreen(),  0.743843,          0.00001);
  EXPECT_NEAR(cColor.getBlue(),   0.00798483,        0.00001);
  EXPECT_NEAR(cColor.getAlpha(),  cColor.minChanVal, 0.00001);

  cColor.setToWhite();
  cColor.setRGBfromWavelengthCM(570);
  EXPECT_NEAR(cColor.getRed(),    0.679159,          0.00001);
  EXPECT_NEAR(cColor.getGreen(),  0.743843,          0.00001);
  EXPECT_NEAR(cColor.getBlue(),   0.00798483,        0.00001);
  EXPECT_NEAR(cColor.getAlpha(),  cColor.maxChanVal, 0.00001);

  cColor.setRGBfromWavelengthCM(571, mjr::colorRGBA32F::cmfInterpolationEnum::FLOOR);
  dColor.setRGBfromWavelengthCM(570);
  EXPECT_NEAR(cColor.getRed(),    dColor.getRed(),   0.00001);
  EXPECT_NEAR(cColor.getGreen(),  dColor.getGreen(), 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   dColor.getBlue(),  0.00001);

  cColor.setRGBfromWavelengthCM(571, mjr::colorRGBA32F::cmfInterpolationEnum::CEILING);
  dColor.setRGBfromWavelengthCM(575);
  EXPECT_NEAR(cColor.getRed(),    dColor.getRed(),   0.00001);
  EXPECT_NEAR(cColor.getGreen(),  dColor.getGreen(), 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   dColor.getBlue(),  0.00001);

  cColor.setRGBfromWavelengthCM(571, mjr::colorRGBA32F::cmfInterpolationEnum::NEAREST);
  dColor.setRGBfromWavelengthCM(570);
  EXPECT_NEAR(cColor.getRed(),    dColor.getRed(),   0.00001);
  EXPECT_NEAR(cColor.getGreen(),  dColor.getGreen(), 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   dColor.getBlue(),  0.00001);

  cColor.setRGBfromWavelengthCM(574, mjr::colorRGBA32F::cmfInterpolationEnum::NEAREST);
  dColor.setRGBfromWavelengthCM(575);
  EXPECT_NEAR(cColor.getRed(),    dColor.getRed(),   0.00001);
  EXPECT_NEAR(cColor.getGreen(),  dColor.getGreen(), 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   dColor.getBlue(),  0.00001);

  cColor.setRGBfromWavelengthCM(572, mjr::colorRGBA32F::cmfInterpolationEnum::LINEAR);
  EXPECT_NEAR(cColor.getRed(),    0.713749886,       0.00001);
  EXPECT_NEAR(cColor.getGreen(),  0.710754037,       0.00001);
  EXPECT_NEAR(cColor.getBlue(),   0.00187643478,     0.00001);

  cColor.setRGBfromWavelengthCM(572, mjr::colorRGBA32F::cmfInterpolationEnum::BUMP);
  EXPECT_NEAR(cColor.getRed(),    0.654946387,       0.00001);
  EXPECT_NEAR(cColor.getGreen(),  0.662842572,       0.00001);
  EXPECT_NEAR(cColor.getBlue(),   3.4287558e-07,     0.00001);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_WavelengthLA, Integer) {

  mjr::colorRGBA8b  aColor;

  aColor.setToBlack();
  aColor.setRGBfromWavelengthLA(570);
  EXPECT_EQ(aColor.getRed(),    0xda);
  EXPECT_EQ(aColor.getGreen(),  0xff);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  aColor.minChanVal);

  aColor.setToWhite();
  aColor.setRGBfromWavelengthLA(570);
  EXPECT_EQ(aColor.getRed(),    0xda);
  EXPECT_EQ(aColor.getGreen(),  0xff);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  aColor.maxChanVal);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_WavelengthLA, Float) {

  mjr::colorRGBA32F aColor;

  aColor.setToBlack();
  aColor.setRGBfromWavelengthLA(570);
  EXPECT_NEAR(aColor.getRed(),    0.857142866,       0.00001);
  EXPECT_NEAR(aColor.getGreen(),  1.000000000,       0.00001);
  EXPECT_NEAR(aColor.getBlue(),   0.000000000,       0.00001);
  EXPECT_NEAR(aColor.getAlpha(),  aColor.minChanVal, 0.00001);

  aColor.setToWhite();
  aColor.setRGBfromWavelengthLA(570);
  EXPECT_NEAR(aColor.getRed(),    0.857142866,       0.00001);
  EXPECT_NEAR(aColor.getGreen(),  1.000000000,       0.00001);
  EXPECT_NEAR(aColor.getBlue(),   0.000000000,       0.00001);
  EXPECT_NEAR(aColor.getAlpha(),  aColor.maxChanVal, 0.00001);

}

#if !(MISSING_P1907R1)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_csCubeHelix_tpl, Float) {

  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.25).getC0(),  0.085,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.25).getC1(),  0.325,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.25).getC2(),  0.298,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.50).getC0(),  0.628,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.50).getC1(),  0.475,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.50).getC2(),  0.286,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.75).getC0(),  0.780,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.75).getC1(),  0.702,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.75).getC2(),  0.929,    0.01);


  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.25).getC0(),  0.280,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.25).getC1(),  0.202,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.25).getC2(),  0.429,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.50).getC0(),  0.372,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.50).getC1(),  0.525,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.50).getC2(),  0.714,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.75).getC0(),  0.585,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.75).getC1(),  0.825,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.75).getC2(),  0.798,    0.01);


  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.25).getC0(),  0.388,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.25).getC1(),  0.163,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.25).getC2(),  0.342,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.50).getC0(),  0.684,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.50).getC1(),  0.384,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.50).getC2(),  0.623,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.75).getC0(),  0.888,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.75).getC1(),  0.663,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.75).getC2(),  0.842,    0.01);

  typedef mjr::colorTpl<double, 3, 2, 1, 0> permcolor3c64F;

  EXPECT_NEAR(permcolor3c64F::csCHstd::c(0.25).getC2(),  0.085,    0.01);
  EXPECT_NEAR(permcolor3c64F::csCHstd::c(0.25).getC1(),  0.325,    0.01);
  EXPECT_NEAR(permcolor3c64F::csCHstd::c(0.25).getC0(),  0.298,    0.01);

}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MISC_various_tfrm, Integer) {

  mjr::colorRGB8b aColor;
  mjr::colorRGB8b bColor;
  mjr::colorRGB8b dColor;
  mjr::colorRGB8b cColor;

  aColor.setRGBfromLogPackIntARGB(0xFF00FF);
  bColor.setRGBfromLogPackIntARGB(0x00FFFF);
  dColor.setRGBfromLogPackIntARGB(0x0100FF);

  cColor.setToBlack();
  cColor.tfrmCopy(aColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMaxI(bColor); // Intensity equal, NOOP
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMinI(bColor); // Intensity equal, NOOP
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMax(bColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0xFF);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMin(bColor);
  EXPECT_EQ(cColor.getC0(),  0x00);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=dColor;
  cColor.tfrmSaw(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00000100), mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00FFFFFF));
  EXPECT_EQ(cColor.getC0(),  0x01);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=dColor;
  cColor.tfrmStep(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00000100), mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00FFFFFF));
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmDirac(bColor);
  EXPECT_EQ(cColor.getC0(),  0x00);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmDiracTot(bColor);
  EXPECT_EQ(cColor.getC0(),  0x00);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0x00);

  cColor=aColor;
  cColor.tfrmDiracTot(aColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0xFF);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmFuzzyDirac(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00FE01F0), mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00010101));
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0xFF);
  EXPECT_EQ(cColor.getC2(),  0x00);

  cColor=aColor;
  cColor.tfrmMean(bColor);
  EXPECT_EQ(cColor.getC0(),  0x7f);
  EXPECT_EQ(cColor.getC1(),  0x7f);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=dColor;
  cColor.tfrmGmean(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00030102));
  EXPECT_EQ(cColor.getC0(),  0x01);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0x16);

  cColor=aColor;
  cColor.tfrmGreyScaleRGB();
  EXPECT_EQ(cColor.getC0(),  0x48);
  EXPECT_EQ(cColor.getC1(),  0x48);
  EXPECT_EQ(cColor.getC2(),  0x48);

  cColor=bColor;
  cColor.tfrmGreyScaleRGB();
  EXPECT_EQ(cColor.getC0(),  0xC8);
  EXPECT_EQ(cColor.getC1(),  0xC8);
  EXPECT_EQ(cColor.getC2(),  0xC8);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MISC_various_tfrm, FLoat) {

  mjr::colorRGB32F aColor;
  mjr::colorRGB32F bColor;
  mjr::colorRGB32F dColor;
  mjr::colorRGB32F cColor;

  aColor.setChansRGB(2.0, 0.0, 2.0);
  bColor.setChansRGB(0.0, 2.0, 2.0);
  dColor.setChansRGB(0.0, 1.0, 2.0);

  cColor.setToBlack();
  cColor.tfrmCopy(aColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMaxI(bColor); // Intensity equal, NOOP
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMinI(bColor); // Intensity equal, NOOP
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMax(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMin(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  // cColor=dColor;
  // cColor.tfrmSaw(mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0000100), mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0FFFFFF));
  // EXPECT_NEAR(cColor.getC0(),  0x01, 0.00001);
  // EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  // EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  // cColor=dColor;
  // cColor.tfrmStep(mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0000100), mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0FFFFFF));
  // EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  // EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  // EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmDirac(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001);

  cColor=aColor;
  cColor.tfrmDiracTot(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor=aColor;
  cColor.tfrmDiracTot(aColor);
  EXPECT_NEAR(cColor.getC0(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001);

  // cColor=aColor;
  // cColor.tfrmFuzzyDirac(mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0FE01F0), mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0010101));
  // EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  // EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  // EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMean(bColor);
  EXPECT_NEAR(cColor.getC0(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=dColor;
  cColor.tfrmGmean(mjr::colorRGB32F().setChansRGB(8.0, 25.0, 2.0));
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  5.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmGreyScaleRGB();
  EXPECT_NEAR(cColor.getC0(),  0.569599986, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.569599986, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.569599986, 0.00001);

  cColor=bColor;
  cColor.tfrmGreyScaleRGB();
  EXPECT_NEAR(cColor.getC0(),  1.57480001, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  1.57480001, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.57480001, 0.00001);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_tfrm_websafe, Comprehensive) {

  mjr::colorRGB8b  aColor;
  mjr::colorRGB8b  bColor;
  mjr::colorRGB32F cColor;
  mjr::colorRGBA8b dColor;

  aColor.setChansRGB(0x00, 0x33, 0x66);
  bColor.setChansRGB(0x00, 0x33, 0x66);
  aColor.tfrmWebSafeRGB();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setChansRGB(0x99, 0xCC, 0xFF);
  bColor.setChansRGB(0x99, 0xCC, 0xFF);
  aColor.tfrmWebSafeRGB();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setChansRGB(0x01, 0x34, 0x67);
  bColor.setChansRGB(0x00, 0x33, 0x66);
  aColor.tfrmWebSafeRGB();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setChansRGB(0x98, 0xCB, 0xFE);
  bColor.setChansRGB(0x99, 0xCC, 0xFF);
  aColor.tfrmWebSafeRGB();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  cColor.setChansRGB(0.05F, 0.15F, 0.35F);
  cColor.tfrmWebSafeRGB();
  EXPECT_NEAR(cColor.getRed(),    0.0,    0.0001);
  EXPECT_NEAR(cColor.getGreen(),  0.2,    0.0001);
  EXPECT_NEAR(cColor.getBlue(),   0.4,    0.0001);

  cColor.setChansRGB(0.55F, 0.75F, 0.95F);
  cColor.tfrmWebSafeRGB();
  EXPECT_NEAR(cColor.getRed(),    0.6,    0.0001);
  EXPECT_NEAR(cColor.getGreen(),  0.8,    0.0001);
  EXPECT_NEAR(cColor.getBlue(),   1.0,    0.0001);

  dColor.setChans(0xCB);
  dColor.tfrmWebSafeRGB();
  EXPECT_EQ(dColor.getRed(),    0xCC);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xCC);
  EXPECT_EQ(dColor.getAlpha(),  0xCB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_tfrm_PowPow, Integer) {
  mjr::colorRGB8b  aColor;
  mjr::colorRGBA8b bColor;

  aColor.setChansRGB(0, 50, 148);
  aColor.tfrmLn(5.0);
  EXPECT_EQ(aColor.getRed(),    0); // No op zero
  EXPECT_EQ(aColor.getGreen(),  19);
  EXPECT_EQ(aColor.getBlue(),   24);

  aColor.setChansRGB(0, 50, 148);
  aColor.tfrmLn(1.0);
  EXPECT_EQ(aColor.getRed(),    0); // No op zero
  EXPECT_EQ(aColor.getGreen(),  3);
  EXPECT_EQ(aColor.getBlue(),   4);

  aColor.setChansRGB(0, 50, 148);
  aColor.tfrmLn1();
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  3);
  EXPECT_EQ(aColor.getBlue(),   5);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqr();
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  9);
  EXPECT_EQ(aColor.getBlue(),   39);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqrt();
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  112);
  EXPECT_EQ(aColor.getBlue(),   159);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(2.0);
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  9);
  EXPECT_EQ(aColor.getBlue(),   39);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(0.5);
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  112);
  EXPECT_EQ(aColor.getBlue(),   159);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowRGB(1, 2.0, 0.5);
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  9);
  EXPECT_EQ(aColor.getBlue(),   159);

  bColor.setToWhite();
  bColor.setChansRGB(0, 50, 100);
  bColor.tfrmStdPowRGB(1, 2.0, 0.5);
  EXPECT_EQ(bColor.getRed(),    0);
  EXPECT_EQ(bColor.getGreen(),  9);
  EXPECT_EQ(bColor.getBlue(),   159);
  EXPECT_EQ(bColor.getAlpha(),  0xff);

  bColor.setToBlack();
  bColor.setChansRGB(0, 50, 100);
  bColor.tfrmStdPowRGB(1, 2.0, 0.5);
  EXPECT_EQ(bColor.getRed(),    0);
  EXPECT_EQ(bColor.getGreen(),  9);
  EXPECT_EQ(bColor.getBlue(),   159);
  EXPECT_EQ(bColor.getAlpha(),  0x00);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_tfrm_PowPow, Float) {

  mjr::colorRGB32F aColor;

  aColor.setChansRGB(0, 50, 148);
  aColor.tfrmLn(5.0);
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001); // No op zero
  EXPECT_NEAR(aColor.getGreen(),  19.5601150272, 0.00001);
  EXPECT_NEAR(aColor.getBlue(),   24.9860613688, 0.00001);

  aColor.setChansRGB(0, -1, 148);
  aColor.tfrmLn(1.0);
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001); // No op zero
  EXPECT_NEAR(aColor.getGreen(),  -1,            0.00001); // No op negative
  EXPECT_NEAR(aColor.getBlue(),   4.99721227376, 0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmLn1();
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  3.93182563272, 0.00001);
  EXPECT_NEAR(aColor.getBlue(),   4.61512051684, 0.00001);

  aColor.setChansRGB(0, -2, 100);
  aColor.tfrmLn1();
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001); // No op zero
  EXPECT_NEAR(aColor.getGreen(), -2.0,           0.00001); // No op negative
  EXPECT_NEAR(aColor.getBlue(),   4.61512051684, 0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqr();
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  2500,          0.00001);
  EXPECT_NEAR(aColor.getBlue(),   10000,         0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqrt();
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  7.07106781,    0.00001);
  EXPECT_NEAR(aColor.getBlue(),   10,            0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(2.0);
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  2500,          0.00001);
  EXPECT_NEAR(aColor.getBlue(),   10000,         0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(0.5);
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  7.07106781,    0.00001);
  EXPECT_NEAR(aColor.getBlue(),   10,            0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowRGB(1, 2.0, 0.5);
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  2500,          0.00001);
  EXPECT_NEAR(aColor.getBlue(),   10,            0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_tfrm_GryLevScl, Integer) {

  mjr::colorRGB8b  aColor;
  mjr::colorRGBA8b cColor;

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2, 4);
  EXPECT_EQ(aColor.getRed(),    24);
  EXPECT_EQ(aColor.getGreen(),  44);
  EXPECT_EQ(aColor.getBlue(),   54);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2.5, 4);
  EXPECT_EQ(aColor.getRed(),    29);
  EXPECT_EQ(aColor.getGreen(),  54);
  EXPECT_EQ(aColor.getBlue(),   66);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_EQ(aColor.getRed(),    24);
  EXPECT_EQ(aColor.getGreen(),  54);
  EXPECT_EQ(aColor.getBlue(),   77);

  cColor.setToWhite();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_EQ(cColor.getRed(),    24);
  EXPECT_EQ(cColor.getGreen(),  54);
  EXPECT_EQ(cColor.getBlue(),   77);
  EXPECT_EQ(cColor.getAlpha(),  0xff);

  cColor.setToBlack();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_EQ(cColor.getRed(),    24);
  EXPECT_EQ(cColor.getGreen(),  54);
  EXPECT_EQ(cColor.getBlue(),   77);
  EXPECT_EQ(cColor.getAlpha(),  0x00);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_tfrm_GryLevSclflt, Float) {

  mjr::colorRGB32F  aColor;
  mjr::colorRGBA32F cColor;

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2, 4);
  EXPECT_NEAR(aColor.getRed(),    24.0, 0.00001);
  EXPECT_NEAR(aColor.getGreen(),  44.0, 0.00001);
  EXPECT_NEAR(aColor.getBlue(),   54.0, 0.00001);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2.5, 4);
  EXPECT_NEAR(aColor.getRed(),    29.0, 0.00001);
  EXPECT_NEAR(aColor.getGreen(),  54.0, 0.00001);
  EXPECT_NEAR(aColor.getBlue(),   66.5, 0.00001);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_NEAR(aColor.getRed(),    24.0, 0.00001);
  EXPECT_NEAR(aColor.getGreen(),  54.0, 0.00001);
  EXPECT_NEAR(aColor.getBlue(),   77.0, 0.00001);

  cColor.setToWhite();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_NEAR(cColor.getRed(),    24.0, 0.00001);
  EXPECT_NEAR(cColor.getGreen(),  54.0, 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   77.0, 0.00001);
  EXPECT_NEAR(cColor.getAlpha(),   1.0, 0.00001);

  cColor.setToBlack();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_NEAR(cColor.getRed(),    24.0, 0.00001);
  EXPECT_NEAR(cColor.getGreen(),  54.0, 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   77.0, 0.00001);
  EXPECT_NEAR(cColor.getAlpha(),   0.0, 0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_wMean_and_linearInterpolate, Integer) {

  mjr::colorRGBA8b a1Color(10, 20, 30, 40);
  mjr::colorRGBA8b a2Color(10, 30, 20, 40);
  mjr::colorRGBA8b a3Color(40, 20, 30, 10);
  mjr::colorRGBA8b a4Color(90, 70, 10, 20);

  mjr::colorRGBA8b aColor;
  mjr::colorRGBA8b cColor;

 ////////////////////////////////////////////////////////////////////////////////

 aColor.wMean(1.0F, 1.0F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  20);
 EXPECT_EQ(aColor.getC1(),  50);
 EXPECT_EQ(aColor.getC2(),  50);
 EXPECT_EQ(aColor.getC3(),  80);

 aColor.wMean(1.0F, 1.0F, 1.0F, a1Color, a2Color, a3Color);
 EXPECT_EQ(aColor.getC0(),  60);
 EXPECT_EQ(aColor.getC1(),  70);
 EXPECT_EQ(aColor.getC2(),  80);
 EXPECT_EQ(aColor.getC3(),  90);

 aColor.wMean(1.0F, 1.0F, 1.0F, 1.0F, a1Color, a2Color, a3Color, a4Color);
 EXPECT_EQ(aColor.getC0(),  150);
 EXPECT_EQ(aColor.getC1(),  140);
 EXPECT_EQ(aColor.getC2(),   90);
 EXPECT_EQ(aColor.getC3(),  110);

 aColor.wMean(0.1F, 1.0F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  11);
 EXPECT_EQ(aColor.getC1(),  32);
 EXPECT_EQ(aColor.getC2(),  23);
 EXPECT_EQ(aColor.getC3(),  44);

 aColor.wMean(0.1F, 1.0F, 1.0F, a1Color, a2Color, a3Color);
 EXPECT_EQ(aColor.getC0(),  51);
 EXPECT_EQ(aColor.getC1(),  52);
 EXPECT_EQ(aColor.getC2(),  53);
 EXPECT_EQ(aColor.getC3(),  54);

 aColor.wMean(0.1F, 1.0F, 1.0F, 1.0F, a1Color, a2Color, a3Color, a4Color);
 EXPECT_EQ(aColor.getC0(),  141);
 EXPECT_EQ(aColor.getC1(),  122);
 EXPECT_EQ(aColor.getC2(),   63);
 EXPECT_EQ(aColor.getC3(),   74);

 ////////////////////////////////////////////////////////////////////////////////

 aColor.linearInterpolate(0.0, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  a1Color.getC0());
 EXPECT_EQ(aColor.getC1(),  a1Color.getC1());
 EXPECT_EQ(aColor.getC2(),  a1Color.getC2());
 EXPECT_EQ(aColor.getC3(),  a1Color.getC3());

 aColor.linearInterpolate(1.0, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  a2Color.getC0());
 EXPECT_EQ(aColor.getC1(),  a2Color.getC1());
 EXPECT_EQ(aColor.getC2(),  a2Color.getC2());
 EXPECT_EQ(aColor.getC3(),  a2Color.getC3());

 aColor.linearInterpolate(0.5, a1Color, a2Color);
 cColor.uMean(0.5F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  cColor.getC0());
 EXPECT_EQ(aColor.getC1(),  cColor.getC1());
 EXPECT_EQ(aColor.getC2(),  cColor.getC2());
 EXPECT_EQ(aColor.getC3(),  cColor.getC3());

 aColor.linearInterpolate(0.25, a1Color, a2Color);
 cColor.uMean(0.75F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  cColor.getC0());
 EXPECT_EQ(aColor.getC1(),  cColor.getC1());
 EXPECT_EQ(aColor.getC2(),  cColor.getC2());
 EXPECT_EQ(aColor.getC3(),  cColor.getC3());

 aColor.linearInterpolate(0.75, a1Color, a2Color);
 cColor.uMean(0.25F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  cColor.getC0());
 EXPECT_EQ(aColor.getC1(),  cColor.getC1());
 EXPECT_EQ(aColor.getC2(),  cColor.getC2());
 EXPECT_EQ(aColor.getC3(),  cColor.getC3());

 ////////////////////////////////////////////////////////////////////////////////
 aColor.uMean(0.2F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  .2*10+.8*10);
 EXPECT_EQ(aColor.getC1(),  .2*20+.8*30);
 EXPECT_EQ(aColor.getC2(),  .2*30+.8*20);
 EXPECT_EQ(aColor.getC3(),  .2*40+.8*40);

 aColor.uMean(0.1F, 0.3F, a1Color, a2Color, a3Color);
 EXPECT_EQ(aColor.getC0(),  .1*10+.3*10+0.6*40);
 EXPECT_EQ(aColor.getC1(),  .1*20+.3*30+0.6*20);
 EXPECT_EQ(aColor.getC2(),  .1*30+.3*20+0.6*30);
 EXPECT_EQ(aColor.getC3(),  .1*40+.3*40+0.6*10);

 aColor.uMean(0.1F, 0.3F, 0.4F, a1Color, a2Color, a3Color, a4Color);
 EXPECT_EQ(aColor.getC0(),  .1*10+.3*10+0.4*40+0.2*90);
 EXPECT_EQ(aColor.getC1(),  .1*20+.3*30+0.4*20+0.2*70);
 EXPECT_EQ(aColor.getC2(),  .1*30+.3*20+0.4*30+0.2*10);
 EXPECT_EQ(aColor.getC3(),  .1*40+.3*40+0.4*10+0.2*20);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_wMean, Float) {

  mjr::colorRGBA32F bColor;
  mjr::colorRGBA32F b1Color(10, 20, 30, 40);
  mjr::colorRGBA32F b2Color(10, 30, 20, 40);
  mjr::colorRGBA32F b3Color(40, 20, 30, 10);
  mjr::colorRGBA32F b4Color(90, 70, 10, 20);

 bColor.wMean(1.0F, 1.0F, b1Color, b2Color);
 EXPECT_NEAR(bColor.getC0(),  20, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  50, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  50, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  80, 0.00001);

 bColor.wMean(1.0F, 1.0F, 1.0F, b1Color, b2Color, b3Color);
 EXPECT_NEAR(bColor.getC0(),  60, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  70, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  80, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  90, 0.00001);

 bColor.wMean(1.0F, 1.0F, 1.0F, 1.0F, b1Color, b2Color, b3Color, b4Color);
 EXPECT_NEAR(bColor.getC0(),  150, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  140, 0.00001);
 EXPECT_NEAR(bColor.getC2(),   90, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  110, 0.00001);

 bColor.wMean(0.1F, 1.0F, b1Color, b2Color);
 EXPECT_NEAR(bColor.getC0(),  11, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  32, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  23, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  44, 0.00001);

 bColor.wMean(0.1F, 1.0F, 1.0F, b1Color, b2Color, b3Color);
 EXPECT_NEAR(bColor.getC0(),  51, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  52, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  53, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  54, 0.00001);

 bColor.wMean(0.1F, 1.0F, 1.0F, 1.0F, b1Color, b2Color, b3Color, b4Color);
 EXPECT_NEAR(bColor.getC0(),  141, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  122, 0.00001);
 EXPECT_NEAR(bColor.getC2(),   63, 0.00001);
 EXPECT_NEAR(bColor.getC3(),   74, 0.00001);

 bColor.uMean(0.2F, b1Color, b2Color);
 EXPECT_NEAR(bColor.getC0(),  .2*10+.8*10, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  .2*20+.8*30, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  .2*30+.8*20, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  .2*40+.8*40, 0.00001);

 bColor.uMean(0.1F, 0.3F, b1Color, b2Color, b3Color);
 EXPECT_NEAR(bColor.getC0(),  .1*10+.3*10+0.6*40, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  .1*20+.3*30+0.6*20, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  .1*30+.3*20+0.6*30, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  .1*40+.3*40+0.6*10, 0.00001);

 bColor.uMean(0.1F, 0.3F, 0.4F, b1Color, b2Color, b3Color, b4Color);
 EXPECT_NEAR(bColor.getC0(),  .1*10+.3*10+0.4*40+0.2*90, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  .1*20+.3*30+0.4*20+0.2*70, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  .1*30+.3*20+0.4*30+0.2*10, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  .1*40+.3*40+0.4*10+0.2*20, 0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_setRGBfromUnitHSL_and_setRGBfromUnitHSV, Integer) {

  mjr::colorRGB8b aColor;
  mjr::colorRGB8b bColor;

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0.5);
  bColor.setToRed();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL( 60/360.0, 1, 0.5);
  bColor.setToYellow();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(120/360.0, 1, 0.5);
  bColor.setToGreen();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0.5);
  bColor.setToCyan();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(240/360.0, 1, 0.5);
  bColor.setToBlue();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(300/360.0, 1, 0.5);
  bColor.setToMagenta();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 1.0);
  bColor.setToRed();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV( 60/360.0, 1, 1.0);
  bColor.setToYellow();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV( 420/360.0, 1, 1.0);
  bColor.setToYellow();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(120/360.0, 1, 1.0);
  bColor.setToGreen();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 1, 1.0);
  bColor.setToCyan();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(240/360.0, 1, 1.0);
  bColor.setToBlue();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(300/360.0, 1, 1.0);
  bColor.setToMagenta();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 1);
  bColor.setToWhite();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 1);
  bColor.setToWhite();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 1);
  bColor.setToWhite();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 0, 1);
  bColor.setToWhite();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 0, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_setRGBfromUnitHSL_and_setRGBfromUnitHSV, FLoat) {

  mjr::colorRGB32F aColor;
  mjr::colorRGB32F bColor;

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0.5);
  bColor.setToRed();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL( 60/360.0, 1, 0.5);
  bColor.setToYellow();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL( 420/360.0, 1, 0.5);
  bColor.setToYellow();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(120/360.0, 1, 0.5);
  bColor.setToGreen();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0.5);
  bColor.setToCyan();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(240/360.0, 1, 0.5);
  bColor.setToBlue();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(300/360.0, 1, 0.5);
  bColor.setToMagenta();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 1.0);
  bColor.setToRed();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV( 60/360.0, 1, 1.0);
  bColor.setToYellow();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(120/360.0, 1, 1.0);
  bColor.setToGreen();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(180/360.0, 1, 1.0);
  bColor.setToCyan();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(240/360.0, 1, 1.0);
  bColor.setToBlue();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(300/360.0, 1, 1.0);
  bColor.setToMagenta();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 1);
  bColor.setToWhite();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(180/360.0, 1, 1);
  bColor.setToWhite();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 1);
  bColor.setToWhite();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(180/360.0, 0, 1);
  bColor.setToWhite();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(180/360.0, 0, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(180/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_csCBSpectral, IntInComprehensive) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0,  3).isEqualRGB(aColor.setChansRGB(252, 141,  89))); // smallest
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1,  3).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2,  3).isEqualRGB(aColor.setChansRGB(153, 213, 148)));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0, 11).isEqualRGB(aColor.setChansRGB(158,   1,  66))); // biggest
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1, 11).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2, 11).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3, 11).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4, 11).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5, 11).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6, 11).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7, 11).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8, 11).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9, 11).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10, 11).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3,  3).isEqualRGB(aColor.setChansRGB(252, 141,  89))); // wrap index
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4,  3).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5,  3).isEqualRGB(aColor.setChansRGB(153, 213, 148)));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(11, 11).isEqualRGB(aColor.setChansRGB(158,   1,  66))); // wrap index
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(12, 11).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(13, 11).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(14, 11).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(15, 11).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(16, 11).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(17, 11).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(18, 11).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(19, 11).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(20, 11).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(21, 11).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0    ).isEqualRGB(aColor.setChansRGB(158,   1,  66)));  // missing -> 11
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1    ).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2    ).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3    ).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4    ).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5    ).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6    ).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7    ).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8    ).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9    ).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10    ).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0,  1).isEqualRGB(aColor.setChansRGB(252, 141,  89)));  // too small -> 3
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1,  1).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2,  1).isEqualRGB(aColor.setChansRGB(153, 213, 148)));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0, 50).isEqualRGB(aColor.setChansRGB(158,   1,  66)));  // too big -> 11
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1, 50).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2, 50).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3, 50).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4, 50).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5, 50).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6, 50).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7, 50).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8, 50).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9, 50).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10, 50).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0, 3);
  EXPECT_EQ(aColor.getRed(),    252);
  EXPECT_EQ(aColor.getGreen(),  141);
  EXPECT_EQ(aColor.getBlue(),    89);
  EXPECT_EQ(aColor.getAlpha(),    mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0, 3);
  EXPECT_EQ(aColor.getRed(),     252);
  EXPECT_EQ(aColor.getGreen(),   141);
  EXPECT_EQ(aColor.getBlue(),     89);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal); // Not set!

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0,  3).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F)); // smallest
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2,  3).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0, 11).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F)); // biggest
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10, 11).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3,  3).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F)); // wrap index
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5,  3).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(11, 11).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F)); // wrap index
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(12, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(13, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(14, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(15, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(16, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(17, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(18, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(19, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(20, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(21, 11).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0    ).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // missing -> 11
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1    ).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2    ).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3    ).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4    ).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5    ).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6    ).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7    ).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8    ).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9    ).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10    ).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0,  1).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F));  // too small -> 3
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1,  1).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2,  1).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0, 50).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // too big -> 11
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1, 50).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2, 50).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3, 50).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4, 50).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5, 50).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6, 50).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7, 50).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8, 50).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9, 50).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10, 50).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0, 3);
  EXPECT_EQ(bColor.getAlpha(),    mjr::colorRGBA32F::minChanVal); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0, 3);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA32F::maxChanVal); // Not set!

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_csCBSpectral, FltInComprehensive) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  0/2.0F,  3).isCloseRGB(aColor.setChansRGB(252, 141,  89), 2)); // smallest
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  1/2.0F,  3).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  2/2.0F,  3).isCloseRGB(aColor.setChansRGB(153, 213, 148), 2));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0/10.0F, 11).isCloseRGB(aColor.setChansRGB(158,   1,  66), 2)); // biggest
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1/10.0F, 11).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2/10.0F, 11).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3/10.0F, 11).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4/10.0F, 11).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5/10.0F, 11).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6/10.0F, 11).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7/10.0F, 11).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8/10.0F, 11).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9/10.0F, 11).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10/10.0F, 11).isCloseRGB(aColor.setChansRGB( 94,  79, 162), 2));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  3/2.0F,  3).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2)); // wrap index

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 1/10.0F, 11).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2)); // wrap index
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 2/10.0F, 11).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 3/10.0F, 11).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 4/10.0F, 11).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 5/10.0F, 11).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 6/10.0F, 11).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 7/10.0F, 11).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 8/10.0F, 11).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(1+ 9/10.0F, 11).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0/10.0F    ).isCloseRGB(aColor.setChansRGB(158,   1,  66), 2));  // missing -> 11
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1/10.0F    ).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2/10.0F    ).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3/10.0F    ).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4/10.0F    ).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5/10.0F    ).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6/10.0F    ).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7/10.0F    ).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8/10.0F    ).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9/10.0F    ).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10/10.0F    ).isCloseRGB(aColor.setChansRGB( 94,  79, 162), 2));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  0/2.0F,  1).isCloseRGB(aColor.setChansRGB(252, 141,  89), 2));  // too small -> 3
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  1/2.0F,  1).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(  2/2.0F,  1).isCloseRGB(aColor.setChansRGB(153, 213, 148), 2));

  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 0/10.0F, 50).isCloseRGB(aColor.setChansRGB(158,   1,  66), 2));  // too big -> 11
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 1/10.0F, 50).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 2/10.0F, 50).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 3/10.0F, 50).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 4/10.0F, 50).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 5/10.0F, 50).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 6/10.0F, 50).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 7/10.0F, 50).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 8/10.0F, 50).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c( 9/10.0F, 50).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csCBSpectral::c(10/10.0F, 50).isCloseRGB(aColor.setChansRGB( 94,  79, 162), 2));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0/2.0F, 3);
  EXPECT_EQ(aColor.getAlpha(),    mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0/2.0F, 3);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal); // Not set!

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0/2.0F,  3).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F)); // smallest
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1/2.0F,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2/2.0F,  3).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0/10.0F, 11).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F)); // biggest
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1/10.0F, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2/10.0F, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3/10.0F, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4/10.0F, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5/10.0F, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6/10.0F, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7/10.0F, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8/10.0F, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9/10.0F, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10/10.0F, 11).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3/2.0F,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+1/10.0F, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+2/10.0F, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+3/10.0F, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+4/10.0F, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+5/10.0F, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+6/10.0F, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+7/10.0F, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+8/10.0F, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(1+9/10.0F, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));

// ////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0/10.0F    ).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // missing -> 11
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1/10.0F    ).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2/10.0F    ).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3/10.0F    ).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4/10.0F    ).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5/10.0F    ).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6/10.0F    ).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7/10.0F    ).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8/10.0F    ).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9/10.0F    ).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10/10.0F    ).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0/2.0F,  1).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F));  // too small -> 3
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1/2.0F,  1).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2/2.0F,  1).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 0/10.0F, 50).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // too big -> 11
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 1/10.0F, 50).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 2/10.0F, 50).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 3/10.0F, 50).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 4/10.0F, 50).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 5/10.0F, 50).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 6/10.0F, 50).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 7/10.0F, 50).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 8/10.0F, 50).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c( 9/10.0F, 50).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCBSpectral::c(10/10.0F, 50).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0/2.0F, 3);
  EXPECT_EQ(bColor.getAlpha(),    mjr::colorRGBA32F::minChanVal); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0/2.0F, 3);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA32F::maxChanVal); // Not set!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_isClose_and_isCloseRGB, Comprehensive) {

  mjr::colorRGB8b   aLcolor;
  mjr::colorRGBA8b  bLcolor;
  mjr::colorRGB32F  cLcolor;
  mjr::colorRGBA32F dLcolor;

  mjr::colorRGB8b   aRcolor;
  mjr::colorRGBA8b  bRcolor;
  mjr::colorRGB32F  cRcolor;
  mjr::colorRGBA32F dRcolor;

  aLcolor.setToBlack();
  bLcolor.setToBlack();
  cLcolor.setToBlack();
  dLcolor.setToBlack();

  aRcolor.setToBlack();
  bRcolor.setToBlack();
  cRcolor.setToBlack();
  dRcolor.setToBlack();

  EXPECT_TRUE(aLcolor.isClose(aRcolor, 0));
  EXPECT_TRUE(bLcolor.isClose(bRcolor, 0));
  EXPECT_TRUE(cLcolor.isClose(cRcolor, 0));
  EXPECT_TRUE(dLcolor.isClose(dRcolor, 0));

  EXPECT_TRUE(aLcolor.isCloseRGB(aRcolor, 0));
  EXPECT_TRUE(bLcolor.isCloseRGB(bRcolor, 0));
  EXPECT_TRUE(cLcolor.isCloseRGB(cRcolor, 0));
  EXPECT_TRUE(dLcolor.isCloseRGB(dRcolor, 0));

  aLcolor.setChanToMax(0);
  bLcolor.setChanToMax(0);
  cLcolor.setChanToMax(0);
  dLcolor.setChanToMax(0);

  EXPECT_FALSE(aLcolor.isClose(aRcolor, 0));
  EXPECT_FALSE(bLcolor.isClose(bRcolor, 0));
  EXPECT_FALSE(cLcolor.isClose(cRcolor, 0));
  EXPECT_FALSE(dLcolor.isClose(dRcolor, 0));

  EXPECT_FALSE(aLcolor.isCloseRGB(aRcolor, 0));
  EXPECT_FALSE(bLcolor.isCloseRGB(bRcolor, 0));
  EXPECT_FALSE(cLcolor.isCloseRGB(cRcolor, 0));
  EXPECT_FALSE(dLcolor.isCloseRGB(dRcolor, 0));

  aRcolor.setChanToMax(0);
  bRcolor.setChanToMax(0);
  cRcolor.setChanToMax(0);
  dRcolor.setChanToMax(0);

  EXPECT_TRUE(aLcolor.isClose(aRcolor, 0));
  EXPECT_TRUE(bLcolor.isClose(bRcolor, 0));
  EXPECT_TRUE(cLcolor.isClose(cRcolor, 0));
  EXPECT_TRUE(dLcolor.isClose(dRcolor, 0));

  EXPECT_TRUE(aLcolor.isCloseRGB(aRcolor, 0));
  EXPECT_TRUE(bLcolor.isCloseRGB(bRcolor, 0));
  EXPECT_TRUE(cLcolor.isCloseRGB(cRcolor, 0));
  EXPECT_TRUE(dLcolor.isCloseRGB(dRcolor, 0));

  bRcolor.setChanToMax(3);
  dRcolor.setChanToMax(3);

  EXPECT_FALSE(bLcolor.isClose(bRcolor, 0));
  EXPECT_FALSE(dLcolor.isClose(dRcolor, 0));

  EXPECT_TRUE(bLcolor.isCloseRGB(bRcolor, 0));
  EXPECT_TRUE(dLcolor.isCloseRGB(dRcolor, 0));

  aLcolor.setChansRGB(1, 2, 3);
  aRcolor.setChansRGB(1, 3, 4);

  EXPECT_FALSE(aLcolor.isClose(aRcolor, 0));
  EXPECT_FALSE(aRcolor.isClose(aLcolor, 0));

  EXPECT_TRUE(aLcolor.isClose(aRcolor, 1));  // false only if a channel delta is GREATER THAN epsilon
  EXPECT_TRUE(aRcolor.isClose(aLcolor, 1));

  EXPECT_TRUE(aLcolor.isClose(aRcolor, 2));
  EXPECT_TRUE(aRcolor.isClose(aLcolor, 2));

  cLcolor.setChansRGB(1, 2, 3);
  cRcolor.setChansRGB(1, 3, 4);

  EXPECT_FALSE(cLcolor.isClose(cRcolor, 0.0F));
  EXPECT_FALSE(cRcolor.isClose(cLcolor, 0.0F));

  EXPECT_FALSE(cLcolor.isClose(cRcolor, 0.9999F));
  EXPECT_FALSE(cRcolor.isClose(cLcolor, 0.9999F));

  EXPECT_TRUE(cLcolor.isClose(cRcolor, 1.0F));  // Edge case is ill-defined for FP arithmetic, but OK here as we used numbers that are exactly representable -- might fail on other hardware.
  EXPECT_TRUE(cRcolor.isClose(cLcolor, 1.0F));

  EXPECT_TRUE(cLcolor.isClose(cRcolor, 1.0001F));
  EXPECT_TRUE(cRcolor.isClose(cLcolor, 1.0001F));

  EXPECT_TRUE(cLcolor.isClose(cRcolor, 2.0F));
  EXPECT_TRUE(cRcolor.isClose(cLcolor, 2.0F));
}

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_setRGBfromColorSpace, Comprehensive) {

  mjr::colorRGB8b  aColor, bColor;
  mjr::colorRGBA8b cColor, dColor;
  mjr::colorRGB32F eColor, fColor;
  mjr::colorRGB16b gColor, hColor;

  ////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::RGB, 0, 0.5, 1);
  EXPECT_EQ(aColor.getRed(),    mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getGreen(),  mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(aColor.getBlue(),   mjr::colorRGB8b::maxChanVal);

  eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::RGB, 0, 0.5, 1);
  EXPECT_EQ(eColor.getRed(),    mjr::colorRGB32F::minChanVal);
  EXPECT_EQ(eColor.getGreen(),  mjr::colorRGB32F::meanChanVal);
  EXPECT_EQ(eColor.getBlue(),   mjr::colorRGB32F::maxChanVal);

  gColor.setRGBfromColorSpace(mjr::colorRGB16b::colorSpaceEnum::RGB, 0, 0.5, 1);
  EXPECT_EQ(gColor.getRed(),    mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(gColor.getGreen(),  mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(gColor.getBlue(),   mjr::colorRGB16b::maxChanVal);

  cColor.setToWhite();
  cColor.setRGBfromColorSpace(mjr::colorRGBA8b::colorSpaceEnum::RGB, 0, 0.5, 1);
  EXPECT_EQ(cColor.getRed(),    mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getGreen(),  mjr::colorRGBA8b::meanChanVal);
  EXPECT_EQ(cColor.getBlue(),   mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getAlpha(),  0xFF); // Not set

  cColor.setToBlack();
  cColor.setRGBfromColorSpace(mjr::colorRGBA8b::colorSpaceEnum::RGB, 0, 0.5, 1);
  EXPECT_EQ(cColor.getRed(),    mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getGreen(),  mjr::colorRGBA8b::meanChanVal);
  EXPECT_EQ(cColor.getBlue(),   mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getAlpha(),  0x00); // Not set

  for(double r=0; r<1.0; r=r+0.1)
    for(double g=0; g<1.0; g=g+0.1)
      for(double b=0; b<1.0; b=b+0.1) // BOOST_TEST_CHECK x 1000
        EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::RGB, r, g, b).isEqualRGB(bColor.setChansRGB_dbl(r, g, b)));

  ////////////////////////////////////////////////////////////////////////////////

  // HSL & HSV are pretty well tested elseware.

  ////////////////////////////////////////////////////////////////////////////////
  //   0-100 reals   reals
  //   0.0,    0.0,    0.0               0.00000000000000,   0.00000000000000,   0.00000000000000
  //   0.0, -100.0,    0.0               0.00000000000000,  42.50011693400831,   0.00000000000000
  //   0.0,  100.0,    0.0              96.73833014676526,   0.00000000000000,   6.73101465756404
  //   0.0,    0.0, -100.0               0.00000000000000,  28.17831280013103, 148.60141206787873
  //   0.0,    0.0,  100.0              52.41394321977139,   0.00000000000000,   0.00000000000000
  // 100.0,    0.0,    0.0             255.00000000000000, 255.00000000000000, 254.98144635564927
  //  50.0,   50.0,   50.0             206.61345904246030,  75.47718797538901,  33.52976908891374
  //  50.0,  -50.0,   50.0              35.14702068347071, 137.45770493758675,  16.12671766273848
  //  50.0,  -50.0,  -50.0               0.00000000000000, 143.15667349842120, 203.43118280505934
  //  50.0,   50.0,  -50.0             157.75797959913612,  86.69682271747450, 204.99202043092524

  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(  0,   0,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0, -100.0,    0.0).isEqualRGB(bColor.setChansRGB(  0,  42,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,  100.0,    0.0).isEqualRGB(bColor.setChansRGB( 96,   0,   6)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,    0.0, -100.0).isEqualRGB(bColor.setChansRGB(  0,  28, 148)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,    0.0,  100.0).isEqualRGB(bColor.setChansRGB( 52,   0,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB, 100.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(255, 255, 254)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,   50.0,   50.0).isEqualRGB(bColor.setChansRGB(206,  75,  33)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,  -50.0,   50.0).isEqualRGB(bColor.setChansRGB( 35, 137,  16)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,  -50.0,  -50.0).isEqualRGB(bColor.setChansRGB(  0, 143, 203)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,   50.0,  -50.0).isEqualRGB(bColor.setChansRGB(157,  86, 204)));

  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0, -100.0,    0.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,  42.50011693400831F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,  100.0,    0.0).isCloseRGB(fColor.setChansRGB( 96.73833014676526F/255.0F,   0.00000000000000F/255.0F,   6.73101465756404F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,    0.0, -100.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,  28.17831280013103F/255.0F, 148.60141206787873F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,    0.0,  100.0).isCloseRGB(fColor.setChansRGB( 52.41394321977139F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB, 100.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(255.00000000000000F/255.0F, 255.00000000000000F/255.0F, 254.98144635564927F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,   50.0,   50.0).isCloseRGB(fColor.setChansRGB(206.61345904246030F/255.0F,  75.47718797538901F/255.0F,  33.52976908891374F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,  -50.0,   50.0).isCloseRGB(fColor.setChansRGB( 35.14702068347071F/255.0F, 137.45770493758675F/255.0F,  16.12671766273848F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,  -50.0,  -50.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F, 143.15667349842120F/255.0F, 203.43118280505934F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,   50.0,  -50.0).isCloseRGB(fColor.setChansRGB(157.75797959913612F/255.0F,  86.69682271747450F/255.0F, 204.99202043092524F/255.0F), 0.00001F));

  ////////////////////////////////////////////////////////////////////////////////
  //   0-1     0-1     0-1
  //   0.0,    0.0,    0.0            0.00000000000000,   0.00000000000000,   0.00000000000000
  //   1.0,    0.0,    0.0           50.42455181463890,   0.00000000000000,   1.83509220000000
  //   0.0,    1.0,    0.0            0.00000000000000,  37.29504496314512,   0.00000000000000
  //   0.0,    0.0,    1.0            0.00000000000000,   1.36725900000000,  26.38515827433519
  //   1.0,    1.0,    0.0           35.27435545247001,  23.88691519243730,   0.00000000000000
  //   1.0,    0.0,    1.0           46.09063114907088,   0.00000000000000,  27.25916547197178
  //   0.0,    1.0,    1.0            0.00000000000000,  37.76511040594671,  22.93126475355600

  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB( 0,   0,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   1.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(50,   0,   1)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    1.0,    0.0).isEqualRGB(bColor.setChansRGB( 0,  37,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    0.0,    1.0).isEqualRGB(bColor.setChansRGB( 0,   1,  26)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   1.0,    1.0,    0.0).isEqualRGB(bColor.setChansRGB(35,  23,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   1.0,    0.0,    1.0).isEqualRGB(bColor.setChansRGB(46,   0,  27)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    1.0,    1.0).isEqualRGB(bColor.setChansRGB( 0,  37,  22)));

  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 1.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(50.42455181463890F/255.0F,   0.00000000000000F/255.0F,   1.83509220000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    1.0,    0.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,  37.29504496314512F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    0.0,    1.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,   1.36725900000000F/255.0F,  26.38515827433519F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 1.0,    1.0,    0.0).isCloseRGB(fColor.setChansRGB(35.27435545247001F/255.0F,  23.88691519243730F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 1.0,    0.0,    1.0).isCloseRGB(fColor.setChansRGB(46.09063114907088F/255.0F,   0.00000000000000F/255.0F,  27.25916547197178F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    1.0,    1.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,  37.76511040594671F/255.0F,  22.93126475355600F/255.0F), 0.00001F));

  ////////////////////////////////////////////////////////////////////////////////
  //   0-100 0-100   0-360
  //   0.0,    0.0,    0.0             0.00000000000000,   0.00000000000000,   0.00000000000000
  //   0.0,  100.0,    0.0            96.73833014676526,   0.00000000000000,   6.73101465756404
  //   0.0,   50.0,    0.0            57.41225747257089,   0.00000000000000,   2.34936006058456
  //   0.0,    0.0,  180.0             0.00000000000000,   0.00000000000000,   0.00000000000000
  //   0.0,   50.0,  180.0             0.00000000000000,  28.32099136175329,   0.00000000000000
  //  50.0,   50.0,  180.0             0.00000000000000, 139.16169169667540, 117.60474230139480
  // 100.0,  100.0,  360.0           255.00000000000000, 155.40224018978810, 255.00000000000000
  // 100.0,  100.0,  180.0             0.00000000000000, 255.00000000000000, 252.06306109593692
  // 100.0,  100.0,   60.0           255.00000000000000, 211.98994181103800,  78.02765922273178

  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(  0,   0,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,  100.0,    0.0).isEqualRGB(bColor.setChansRGB( 96,   0,   6)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,   50.0,    0.0).isEqualRGB(bColor.setChansRGB( 57,   0,   2)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,    0.0,  180.0).isEqualRGB(bColor.setChansRGB(  0,   0,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,   50.0,  180.0).isEqualRGB(bColor.setChansRGB(  0,  28,   0)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,  50.0,   50.0,  180.0).isEqualRGB(bColor.setChansRGB(  0, 139, 117)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH, 100.0,  100.0,  360.0).isEqualRGB(bColor.setChansRGB(255, 155, 255)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH, 100.0,  100.0,  180.0).isEqualRGB(bColor.setChansRGB(  0, 255, 252)));
  EXPECT_TRUE(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH, 100.0,  100.0,   60.0).isEqualRGB(bColor.setChansRGB(255, 211,  78)));

  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,  100.0,    0.0).isCloseRGB(fColor.setChansRGB( 96.73833014676526F/255.0F,   0.00000000000000F/255.0F,   6.73101465756404F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,   50.0,    0.0).isCloseRGB(fColor.setChansRGB( 57.41225747257089F/255.0F,   0.00000000000000F/255.0F,   2.34936006058456F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,    0.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,   50.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,  28.32099136175329F/255.0F,   0.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,  50.0,   50.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F, 139.16169169667540F/255.0F, 117.60474230139480F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH, 100.0,  100.0,  360.0).isCloseRGB(fColor.setChansRGB(255.00000000000000F/255.0F, 155.40224018978810F/255.0F, 255.00000000000000F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH, 100.0,  100.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F, 255.00000000000000F/255.0F, 252.06306109593692F/255.0F), 0.00001F));
  EXPECT_TRUE(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH, 100.0,  100.0,   60.0).isCloseRGB(fColor.setChansRGB(255.00000000000000F/255.0F, 211.98994181103800F/255.0F,  78.02765922273178F/255.0F), 0.00001F));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_csFPcircular12, IntInComprehensive) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 0).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 1).isEqualRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 2).isEqualRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 3).isEqualRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 4).isEqualRGB(aColor.setChansRGB(0x66, 0xCC, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 5).isEqualRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 6).isEqualRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 7).isEqualRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 8).isEqualRGB(aColor.setChansRGB(0x00, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 9).isEqualRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(10).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(11).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x7D)));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(12).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x00))); // wrap
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(13).isEqualRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(14).isEqualRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(15).isEqualRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(16).isEqualRGB(aColor.setChansRGB(0x66, 0xCC, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(17).isEqualRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(18).isEqualRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(19).isEqualRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(20).isEqualRGB(aColor.setChansRGB(0x00, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(21).isEqualRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(22).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(23).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x7D)));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0);
  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),    mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0);
  EXPECT_EQ(aColor.getRed(),     0xFF);
  EXPECT_EQ(aColor.getGreen(),   0x00);
  EXPECT_EQ(aColor.getBlue(),    0x00);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal); // Not set!

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 0).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 1).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x7D/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 2).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 3).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 4).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xCC/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 5).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xFF/255.0F, 0xB2/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 6).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0xFF/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 7).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x7D/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 8).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 9).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c(10).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c(11).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x7D/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0);
  EXPECT_NEAR(bColor.getAlpha(),    mjr::colorRGBA32F::minChanVal, 0.0001); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0);
  EXPECT_NEAR(bColor.getAlpha(),  mjr::colorRGBA32F::maxChanVal, 0.0001); // Not set!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_csFPcircular12, FltInComprehensive) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 0/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 1/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 2/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 3/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 4/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xCC, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 5/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 6/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 7/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 8/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x00, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 9/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(10/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(11/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0x7D), 2));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 1/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00), 2)); // wrap
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 2/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 3/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 4/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xCC, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 5/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 6/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 7/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 8/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x00, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 9/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+10/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF), 2));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0.0F);
  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),    mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0.0F);
  EXPECT_EQ(aColor.getRed(),     0xFF);
  EXPECT_EQ(aColor.getGreen(),   0x00);
  EXPECT_EQ(aColor.getBlue(),    0x00);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal); // Not set!

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 0/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 1/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x7D/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 2/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 3/11.0F).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 4/11.0F).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xCC/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 5/11.0F).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xFF/255.0F, 0xB2/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 6/11.0F).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0xFF/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 7/11.0F).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x7D/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 8/11.0F).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 9/11.0F).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c(10/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c(11/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x7D/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0.0F);
  EXPECT_NEAR(bColor.getAlpha(),    mjr::colorRGBA32F::minChanVal, 0.0001); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0.0F);
  EXPECT_NEAR(bColor.getAlpha(),  mjr::colorRGBA32F::maxChanVal, 0.0001); // Not set!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_rgb2colorSpace, Comprehensive) {

  mjr::colorRGB8b              aColor;
  mjr::colorRGB8b::colConDbl3  bColor;
  mjr::colorRGB32F             cColor;
  mjr::colorRGB32F::colConDbl3 dColor;
  mjr::colorRGB16b             eColor;
  mjr::colorRGB16b::colConDbl3 fColor;
  mjr::colorRGB32b             gColor;
  mjr::colorRGB32b::colConDbl3 hColor;

  ////////////////////////////////////////////////////////////////////////////////

  aColor.setChansRGB(mjr::colorRGB8b::minChanVal, mjr::colorRGB8b::meanChanVal, mjr::colorRGB8b::maxChanVal);
  bColor = aColor.rgb2colorSpace(mjr::colorRGB8b::colorSpaceEnum::RGB);
  EXPECT_NEAR(bColor.getC0(),  0.0,    0.00001);
  EXPECT_NEAR(bColor.getC1(),  0.5,    0.01);        // Can't get much accuracy with 8-bit
  EXPECT_NEAR(bColor.getC2(),  1.0,    0.00001);

  eColor.setChansRGB(mjr::colorRGB16b::minChanVal, mjr::colorRGB16b::meanChanVal, mjr::colorRGB16b::maxChanVal);
  fColor = eColor.rgb2colorSpace(mjr::colorRGB16b::colorSpaceEnum::RGB);
  EXPECT_NEAR(fColor.getC0(),  0.0,    0.00001);
  EXPECT_NEAR(fColor.getC1(),  0.5,    0.0001);      // A bit more accuracy with 16-bit
  EXPECT_NEAR(fColor.getC2(),  1.0,    0.00001);

  gColor.setChansRGB(mjr::colorRGB32b::minChanVal, mjr::colorRGB32b::meanChanVal, mjr::colorRGB32b::maxChanVal);
  hColor = gColor.rgb2colorSpace(mjr::colorRGB32b::colorSpaceEnum::RGB);
  EXPECT_NEAR(hColor.getC0(),  0.0,    0.00001);
  EXPECT_NEAR(hColor.getC1(),  0.5,    0.00001);     // A bit more accuracy with 32-bit
  EXPECT_NEAR(hColor.getC2(),  1.0,    0.00001);

  ////////////////////////////////////////////////////////////////////////////////

  //   0.00000000000000   0.5000000000000000   1.00000000000000000 RGB
  // 210.11764705181122   1.0000000000000000   0.50000000000000000 HSL
  // 210.11764705181122   1.0000000000000000   1.00000000000000000 HSV
  //  54.58302990500775  19.1017817806751750 -71.14430025970830000 LAB
  //  25.704111183644635 22.5282223672892700  97.60137039454821000 XYZ
  //  54.58302990500775  73.6640314308147600 285.02909316255295000 LCH

  cColor.setChansRGB(mjr::colorRGB32F::minChanVal, mjr::colorRGB32F::meanChanVal, mjr::colorRGB32F::maxChanVal);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::RGB);
  EXPECT_NEAR(dColor.getC0(),    0.000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC1(),    0.500000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    1.000000000000000, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::HSL);
  EXPECT_NEAR(dColor.getC0(),  210.000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC1(),    1.000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    0.500000000000000, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::HSV);
  EXPECT_NEAR(dColor.getC0(),  210.000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC1(),    1.000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    1.000000000000000, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB);
  EXPECT_NEAR(dColor.getC0(),   54.583029905007749, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   19.106431157445371, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  -71.140167945193781, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ);
  EXPECT_NEAR(dColor.getC0(),   25.704111183644635, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   22.528222367289271, 0.00001);
  EXPECT_NEAR(dColor.getC2(),   97.601370394548212, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH);
  EXPECT_NEAR(dColor.getC0(),   54.583029905007749, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   73.661246302547553, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  285.033419356169360, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////

  //   0.400000000000000   0.6000000000000000   0.800000000000000 RGB
  // 209.999996870756100   0.4999999962747098   0.600000002980232 HSL
  // 209.999996870756100   0.5000000000000000   0.800000000000000 HSV
  //  61.625634479116870  -2.8148222106305076 -31.439123763222420 LAB
  //  27.769805832971585  29.9668794742762760  61.447302014049825 XYZ
  //  61.625634479116870  31.5648812302006830 264.883809161551100 LCH

  cColor.setChansRGB_dbl(0.4, 0.6, 0.8);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::RGB);
  EXPECT_NEAR(dColor.getC0(),     0.400000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC1(),    0.6000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC2(),     0.800000000000000, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::HSL);
  EXPECT_NEAR(dColor.getC0(),  209.999996870756100, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   0.4999999962747098, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    0.600000002980232, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::HSV);
  EXPECT_NEAR(dColor.getC0(),  209.999996870756100, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   0.5000000000000000, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    0.800000000000000, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB);
  EXPECT_NEAR(dColor.getC0(),   61.625634479116870, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  -2.8148222106305076, 0.01);           //  MJR TODO NOTE  Why?  Need to check into the inaccuracy here.
  EXPECT_NEAR(dColor.getC2(),  -31.439123763222420, 0.01);           //  MJR TODO NOTE  Why?  Need to check into the inaccuracy here.

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ);
  EXPECT_NEAR(dColor.getC0(),    27.769805832971585, 0.00001);
  EXPECT_NEAR(dColor.getC1(),   29.9668794742762760, 0.00001);
  EXPECT_NEAR(dColor.getC2(),    61.447302014049825, 0.00001);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH);
  EXPECT_NEAR(dColor.getC0(),   61.625634479116870, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  31.5648812302006830, 0.01);           //  MJR TODO NOTE  Why?  Need to check into the inaccuracy here.
  EXPECT_NEAR(dColor.getC2(),  264.883809161551100, 0.01);           //  MJR TODO NOTE  Why?  Need to check into the inaccuracy here.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_csBin, Comprehensive) {

  mjr::colorRGB8b   a0Color, a1Color;
  mjr::colorRGB32F  b0Color, b1Color;

  a0Color.setToBlack();
  a1Color.setToWhite();

  b0Color.setToBlack();
  b1Color.setToWhite();

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(0).isEqualRGB(a0Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(2).isEqualRGB(a0Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(4).isEqualRGB(a0Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(6).isEqualRGB(a0Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(8).isEqualRGB(a0Color));

  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(1).isEqualRGB(a1Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(3).isEqualRGB(a1Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(5).isEqualRGB(a1Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(7).isEqualRGB(a1Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(9).isEqualRGB(a1Color));

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(0).isEqualRGB(b0Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(2).isEqualRGB(b0Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(4).isEqualRGB(b0Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(6).isEqualRGB(b0Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(8).isEqualRGB(b0Color));

  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(1).isEqualRGB(b1Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(3).isEqualRGB(b1Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(5).isEqualRGB(b1Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(7).isEqualRGB(b1Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(9).isEqualRGB(b1Color));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MISC_setColorCons, Comprehensive) {

  mjr::colorRGBA8b   aColor; // integer color with imperfect mask
  mjr::colorRGBA64b  bColor; // integer color without mask
  mjr::colorRGBA32F  cColor; // floating point color with mask
  mjr::colorRGBA64F  dColor; // floating point color without mask

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToBlack();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  bColor.setToWhite();
  bColor.setToBlack();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);

  cColor.setToWhite();
  cColor.setToBlack();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);

  dColor.setToWhite();
  dColor.setToBlack();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToWhite();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  bColor.setToBlack();
  bColor.setToWhite();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);

  cColor.setToBlack();
  cColor.setToWhite();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);

  dColor.setToBlack();
  dColor.setToWhite();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToRed();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  bColor.setToBlack();
  bColor.setToRed();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);

  cColor.setToBlack();
  cColor.setToRed();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);

  dColor.setToBlack();
  dColor.setToRed();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToRed();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  bColor.setToWhite();
  bColor.setToRed();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);

  cColor.setToWhite();
  cColor.setToRed();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);

  dColor.setToWhite();
  dColor.setToRed();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToGreen();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  bColor.setToBlack();
  bColor.setToGreen();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);

  cColor.setToBlack();
  cColor.setToGreen();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);

  dColor.setToBlack();
  dColor.setToGreen();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToGreen();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  bColor.setToWhite();
  bColor.setToGreen();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);

  cColor.setToWhite();
  cColor.setToGreen();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);

  dColor.setToWhite();
  dColor.setToGreen();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToBlue();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  bColor.setToBlack();
  bColor.setToBlue();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);

  cColor.setToBlack();
  cColor.setToBlue();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);

  dColor.setToBlack();
  dColor.setToBlue();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToBlue();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  bColor.setToWhite();
  bColor.setToBlue();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);

  cColor.setToWhite();
  cColor.setToBlue();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);

  dColor.setToWhite();
  dColor.setToBlue();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToCyan();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  bColor.setToBlack();
  bColor.setToCyan();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);

  cColor.setToBlack();
  cColor.setToCyan();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);

  dColor.setToBlack();
  dColor.setToCyan();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToCyan();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  bColor.setToWhite();
  bColor.setToCyan();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);

  cColor.setToWhite();
  cColor.setToCyan();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);

  dColor.setToWhite();
  dColor.setToCyan();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToMagenta();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  bColor.setToBlack();
  bColor.setToMagenta();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);

  cColor.setToBlack();
  cColor.setToMagenta();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);

  dColor.setToBlack();
  dColor.setToMagenta();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToMagenta();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  bColor.setToWhite();
  bColor.setToMagenta();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);

  cColor.setToWhite();
  cColor.setToMagenta();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);

  dColor.setToWhite();
  dColor.setToMagenta();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToYellow();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  bColor.setToBlack();
  bColor.setToYellow();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);

  cColor.setToBlack();
  cColor.setToYellow();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);

  dColor.setToBlack();
  dColor.setToYellow();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToYellow();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  bColor.setToWhite();
  bColor.setToYellow();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);

  cColor.setToWhite();
  cColor.setToYellow();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);

  dColor.setToWhite();
  dColor.setToYellow();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToHalf();
  EXPECT_EQ(aColor.getC0(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.meanChanVal);

  bColor.setToBlack();
  bColor.setToHalf();
  EXPECT_EQ(bColor.getC0(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.meanChanVal);

  cColor.setToBlack();
  cColor.setToHalf();
  EXPECT_NEAR(cColor.getC0(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.meanChanVal, 0.00001);

  dColor.setToBlack();
  dColor.setToHalf();
  EXPECT_NEAR(dColor.getC0(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.meanChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToHalf();
  EXPECT_EQ(aColor.getC0(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.meanChanVal);

  bColor.setToWhite();
  bColor.setToHalf();
  EXPECT_EQ(bColor.getC0(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.meanChanVal);

  cColor.setToWhite();
  cColor.setToHalf();
  EXPECT_NEAR(cColor.getC0(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.meanChanVal, 0.00001);

  dColor.setToWhite();
  dColor.setToHalf();
  EXPECT_NEAR(dColor.getC0(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.meanChanVal, 0.00001);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_csHSLh, Comprehensive) {

  ////////////////////////////////////////////////////////////////////////////////

  mjr::colorRGBA8b aColor;

  aColor.setToWhite();
  mjr::colorRGBA8b::csHSLhB::c(aColor, mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGB8b::maxChanVal); // unchanged

  aColor.setToBlack();
  mjr::colorRGBA8b::csHSLhB::c(aColor, mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGB8b::minChanVal); // unchanged

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::minChanVal).getRed(),            mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::minChanVal).getGreen(),          mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::minChanVal).getBlue(),           mjr::colorRGB8b::meanChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::minChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::minChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal).getRed(),           mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal).getGreen(),         mjr::colorRGB8b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal).getBlue(),          mjr::colorRGB8b::minChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);  // wrap
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhB::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhC::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhG::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhM::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhR::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal + 1).getRed(),       mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal + 1).getGreen(),     mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csHSLhY::c(mjr::colorRGB8b::meanChanVal + 1).getBlue(),      mjr::colorRGB8b::meanChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::minChanVal).getRed(),          mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::minChanVal).getGreen(),        mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::minChanVal).getBlue(),         mjr::colorRGB16b::meanChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::minChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::maxChanVal - 1);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::minChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::minChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal).getRed(),         mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal).getGreen(),       mjr::colorRGB16b::maxChanVal - 1);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal).getBlue(),        mjr::colorRGB16b::minChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);  // wrap
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhB::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhC::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhG::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhM::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhR::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal + 1).getRed(),     mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal + 1).getGreen(),   mjr::colorRGB16b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB16b::csHSLhY::c(mjr::colorRGB16b::meanChanVal + 1).getBlue(),    mjr::colorRGB16b::meanChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(0.0).getRed(),                                   mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(0.0).getGreen(),                                 mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(0.0).getBlue(),                                  mjr::colorRGB32F::meanChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::maxChanVal, 0.00001); // Note for floating point clrChanT, csHSLh_tpl gets to maxChanVal

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::maxChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::minChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::maxChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::minChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::minChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal).getRed(),        mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal).getGreen(),      mjr::colorRGB32F::maxChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal).getBlue(),       mjr::colorRGB32F::minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);  // wrap to zoeo -- not meanChanVal.  One of the oddities of floating pont wrap.
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhB::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhC::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhG::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhM::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhR::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);

  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal + 1).getRed(),    mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal + 1).getGreen(),  mjr::colorRGB32F::meanChanVal, 0.00001);
  EXPECT_NEAR(mjr::colorRGB32F::csHSLhY::c(mjr::colorRGBA32F::meanChanVal + 1).getBlue(),   mjr::colorRGB32F::meanChanVal, 0.00001);
}

#if !(MISSING_P1907R1)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_csPLY, Comprehensive) {

  mjr::colorRGBA8b aColor;

  aColor.setToWhite();
  mjr::colorRGBA8b::csPLYgrey::c(aColor, 0.0);
  EXPECT_EQ(aColor.getRed(),    mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getBlue(),   mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getGreen(),  mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGB8b::maxChanVal); // unchanged

  aColor.setToBlack();
  mjr::colorRGBA8b::csPLYgrey::c(aColor, 0.0);
  EXPECT_EQ(aColor.getRed(),    mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getBlue(),   mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getGreen(),  mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGB8b::minChanVal); // unchanged

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.0).getRed(),    mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.0).getGreen(),  mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.0).getBlue(),   mjr::colorRGB8b::minChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.5).getRed(),    mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.5).getGreen(),  mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.5).getBlue(),   mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(1.0).getRed(),    mjr::colorRGB8b::maxChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(1.0).getGreen(),  mjr::colorRGB8b::maxChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(1.0).getBlue(),   mjr::colorRGB8b::maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.0).getRed(),    mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.0).getGreen(),  mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.0).getBlue(),   mjr::colorRGB8b::minChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.5).getRed(),    0x3F); // 255 * 0.5 * 0.5 = 63.75
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.5).getGreen(),  0x3F);
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.5).getBlue(),   0x3F);

  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(1.0).getRed(),    mjr::colorRGB8b::maxChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(1.0).getGreen(),  mjr::colorRGB8b::maxChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(1.0).getBlue(),   mjr::colorRGB8b::maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  typedef mjr::colorRGB64F::csPLY_tpl< 10.6666666666667, -16.000000000000,  6.3333333333333, 0.00000000000000,                    // [[0.0, 0.00000], [0.25, 0.750000], [0.50, 0.500000], [1.0, 1.00000]];
                                       -9.3333333333333,  13.000000000000, -4.6666666666666, 1.00000000000000,                    // [[0.0, 1.00000], [0.25, 0.500000], [0.50, 0.750000], [1.0, 0.00000]];
                                        4.4117333333333,  -5.902400000000,  1.9936666666666, 0.28480000000000> csPLYfoo;          // [[0.0, 0.28480], [0.25, 0.483250], [0.50, 0.357500], [1.0, 0.78780]]

  EXPECT_NEAR(csPLYfoo::c(0.00).getRed(),    0.000000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.00).getGreen(),  1.000000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.00).getBlue(),   0.284800, 0.00001);

  EXPECT_NEAR(csPLYfoo::c(0.25).getRed(),    0.750000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.25).getGreen(),  0.500000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.25).getBlue(),   0.483250, 0.00001);

  EXPECT_NEAR(csPLYfoo::c(0.50).getRed(),    0.500000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.50).getGreen(),  0.750000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.50).getBlue(),   0.357500, 0.00001);

  EXPECT_NEAR(csPLYfoo::c(1.00).getRed(),    1.000000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(1.00).getGreen(),  0.000000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(1.00).getBlue(),   0.787800, 0.00001);
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_csCColdeRainbow, FltInComprehensive) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

  aColor.setToWhite();
  mjr::colorRGBA8b::csCColdeRainbow::c(aColor, 0.0);
  EXPECT_EQ(aColor.getRed(),    mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(aColor.getGreen(),  mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(aColor.getBlue(),   mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::minChanVal); // Corner colors set ALL channels -- primary colors set them all to minChanVal

  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(   0/1530.0).isEqualRGB(aColor.setToRed()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 255/1530.0).isEqualRGB(aColor.setToYellow()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 510/1530.0).isEqualRGB(aColor.setToGreen()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 765/1530.0).isEqualRGB(aColor.setToCyan()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1020/1530.0).isEqualRGB(aColor.setToBlue()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1275/1530.0).isEqualRGB(aColor.setToMagenta()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1530/1530.0).isEqualRGB(aColor.setToRed()));

  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(2.0).isEqualRGB(aColor.setToRed()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(3.0).isEqualRGB(aColor.setToRed()));

  for(double i=0.0; i<1.0; i=i+0.001) // EXPECT_EQ x 1000
    EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(i).isEqualRGB(aColor.cmpRGBcornerCGradiant(i, "RYGCBMR")));

  aColor.cmpRGBcornerCGradiant(10/1530.0, "RYGCBMR");
  EXPECT_EQ(aColor.getRed(),    0xff);
  EXPECT_EQ(aColor.getGreen(),  10);
  EXPECT_EQ(aColor.getBlue(),   0);

  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  mjr::colorRGBA32F::csCColdeRainbow::c(bColor, 0.0F);
  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA32F::maxChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA32F::minChanVal);
  EXPECT_EQ(bColor.getBlue(),   mjr::colorRGBA32F::minChanVal);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA32F::minChanVal); // Corner colors set ALL channels -- primary colors set them all to minChanVal

  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(   0/1530.0).isCloseRGB(bColor.setToRed(),     0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c( 255/1530.0).isCloseRGB(bColor.setToYellow(),  0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c( 510/1530.0).isCloseRGB(bColor.setToGreen(),   0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c( 765/1530.0).isCloseRGB(bColor.setToCyan(),    0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(1020/1530.0).isCloseRGB(bColor.setToBlue(),    0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(1275/1530.0).isCloseRGB(bColor.setToMagenta(), 0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(1530/1530.0).isCloseRGB(bColor.setToRed(),     0.000001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(2.0).isCloseRGB(bColor.setToRed(),             0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(3.0).isCloseRGB(bColor.setToRed(),             0.000001F));

  for(double i=0.0; i<1.0; i=i+0.001) // TEST x 1000
    EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(i).isCloseRGB(bColor.cmpRGBcornerCGradiant(i, "RYGCBMR"), 0.000001F));

  bColor.cmpRGBcornerCGradiant(10/1530.0, "RYGCBMR");
  EXPECT_NEAR(bColor.getRed(),    1,               0.00001);
  EXPECT_NEAR(bColor.getGreen(),  0.0392156862745, 0.00001);
  EXPECT_NEAR(bColor.getBlue(),   0,               0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_csCColdeRainbow, IntInComprehensive) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

  aColor.setToWhite();
  mjr::colorRGBA8b::csCColdeRainbow::c(aColor, 0u);
  EXPECT_EQ(aColor.getRed(),    mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(aColor.getGreen(),  mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(aColor.getBlue(),   mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal); // unchanged

  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(   0u).isEqualRGB(aColor.setToRed()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 255u).isEqualRGB(aColor.setToYellow()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 510u).isEqualRGB(aColor.setToGreen()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 765u).isEqualRGB(aColor.setToCyan()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1020u).isEqualRGB(aColor.setToBlue()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1275u).isEqualRGB(aColor.setToMagenta()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1530u).isEqualRGB(aColor.setToRed()));

  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1531u).isEqualRGB(aColor.setToRed()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1786u).isEqualRGB(aColor.setToYellow()));

  for(unsigned int i=0; i<1531; i++)   // EXPECT_EQ x 1531
    EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(i).isEqualRGB(aColor.cmpRGBcornerDGradiant(i, "RYGCBMR")));

  aColor.cmpRGBcornerDGradiant(10u, "RYGCBMR");
  EXPECT_EQ(aColor.getRed(),    0xff);
  EXPECT_EQ(aColor.getGreen(),  10);
  EXPECT_EQ(aColor.getBlue(),   0);

  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  mjr::colorRGBA32F::csCColdeRainbow::c(bColor, 0u);
  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA32F::maxChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA32F::minChanVal);
  EXPECT_EQ(bColor.getBlue(),   mjr::colorRGBA32F::minChanVal);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA32F::maxChanVal); // unchanged

  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(0*0x100000000ul).isCloseRGB(bColor.setToRed(),      0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(1*0x100000000ul).isCloseRGB(bColor.setToYellow(),   0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(2*0x100000000ul).isCloseRGB(bColor.setToGreen(),    0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(3*0x100000000ul).isCloseRGB(bColor.setToCyan(),     0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(4*0x100000000ul).isCloseRGB(bColor.setToBlue(),     0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(5*0x100000000ul).isCloseRGB(bColor.setToMagenta(),  0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(6*0x100000000ul).isCloseRGB(bColor.setToRed(),      0.000001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(6*0x100000000ul+1).isCloseRGB(bColor.setToRed(),    0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(7*0x100000000ul+1).isCloseRGB(bColor.setToYellow(), 0.000001F));

  for(uint64_t i=0; i<0x600000000; i=i+0x600000)  // TEST x 4096
    EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(i).isCloseRGB(bColor.cmpRGBcornerDGradiant(i, "RYGCBMR"), 0.000001F));

  bColor.cmpRGBcornerDGradiant(168430090, "RYGCBMR");
  EXPECT_NEAR(bColor.getRed(),    1,               0.00001);
  EXPECT_NEAR(bColor.getGreen(),  0.0392156862745, 0.00001);
  EXPECT_NEAR(bColor.getBlue(),   0,               0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_conCol, Comprehensive) {
  // The simplicity of these functions doesn't warrant complex testing.  If the constructors & set/get work on a simple test case, then they probably work.

  mjr::color8c16b aColor {mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal};
  mjr::color8c16b bColor {mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal};

  EXPECT_TRUE(aColor.getColConRGB_byte().isEqual( mjr::color8c16b::colConRGBbyte {   0, 255,   0                          }));
  EXPECT_TRUE(bColor.getColConRGB_byte().isEqual( mjr::color8c16b::colConRGBbyte { 255,   0, 255                          }));
  EXPECT_TRUE(aColor.getColConRGBA_byte().isEqual(mjr::color8c16b::colConRGBAbyte{   0, 255,   0, 255                     }));
  EXPECT_TRUE(bColor.getColConRGBA_byte().isEqual(mjr::color8c16b::colConRGBAbyte{ 255,   0, 255,   0                     }));
  EXPECT_TRUE(aColor.getColConRGB_dbl().isEqual(  mjr::color8c16b::colConRGBdbl  { 0.0, 1.0, 0.0                          }));
  EXPECT_TRUE(bColor.getColConRGB_dbl().isEqual(  mjr::color8c16b::colConRGBdbl  { 1.0, 0.0, 1.0                          }));
  EXPECT_TRUE(aColor.getColConRGBA_dbl().isEqual( mjr::color8c16b::colConRGBAdbl { 0.0, 1.0, 0.0, 1.0                     }));
  EXPECT_TRUE(bColor.getColConRGBA_dbl().isEqual( mjr::color8c16b::colConRGBAdbl { 1.0, 0.0, 1.0, 0.0                     }));
  EXPECT_TRUE(aColor.getColCon_byte().isEqual(    mjr::color8c16b::colConALLbyte {   0, 255,   0, 255,   0, 255,   0, 255 }));
  EXPECT_TRUE(bColor.getColCon_byte().isEqual(    mjr::color8c16b::colConALLbyte { 255,   0, 255,   0, 255,   0, 255,   0 }));
  EXPECT_TRUE(aColor.getColCon_dbl().isEqual(     mjr::color8c16b::colConALLdbl  { 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 }));
  EXPECT_TRUE(bColor.getColCon_dbl().isEqual(     mjr::color8c16b::colConALLdbl  { 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0 }));

  mjr::color8c16b cColor;
  mjr::color8c16b dColor;

  mjr::color8c16b a3nColor {mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal};
  mjr::color8c16b b3xColor {mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal};
  mjr::color8c16b a4nColor {mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal};
  mjr::color8c16b b4xColor {mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal};

  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(a3nColor.isEqual(cColor.setChansRGB_byte( mjr::color8c16b::colConRGBbyte {   0, 255,   0                          })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(b3xColor.isEqual(dColor.setChansRGB_byte( mjr::color8c16b::colConRGBbyte { 255,   0, 255                          })));
  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(a4nColor.isEqual(cColor.setChansRGBA_byte(mjr::color8c16b::colConRGBAbyte{   0, 255,   0, 255                     })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(b4xColor.isEqual(dColor.setChansRGBA_byte(mjr::color8c16b::colConRGBAbyte{ 255,   0, 255,   0                     })));
  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(a3nColor.isEqual(cColor.setChansRGB_dbl(  mjr::color8c16b::colConRGBdbl  { 0.0, 1.0, 0.0                          })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(b3xColor.isEqual(dColor.setChansRGB_dbl(  mjr::color8c16b::colConRGBdbl  { 1.0, 0.0, 1.0                          })));
  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(a4nColor.isEqual(cColor.setChansRGBA_dbl( mjr::color8c16b::colConRGBAdbl { 0.0, 1.0, 0.0, 1.0                     })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(b4xColor.isEqual(dColor.setChansRGBA_dbl( mjr::color8c16b::colConRGBAdbl { 1.0, 0.0, 1.0, 0.0                     })));
  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(aColor.isEqual(cColor.setChans_byte(      mjr::color8c16b::colConALLbyte {   0, 255,   0, 255,   0, 255,   0, 255 })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(bColor.isEqual(dColor.setChans_byte(      mjr::color8c16b::colConALLbyte { 255,   0, 255,   0, 255,   0, 255,   0 })));
  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(aColor.isEqual(cColor.setChans_dbl(       mjr::color8c16b::colConALLdbl  { 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(bColor.isEqual(dColor.setChans_dbl(       mjr::color8c16b::colConALLdbl  { 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0 })));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(bestRedChan_and_bestBlueChan_and_bestGreenChan_and_bestAlphaChan, Integer) {
  mjr::color1c8b aColor;
  mjr::color2c8b bColor;
  mjr::color3c8b cColor;
  mjr::color4c8b dColor;
  mjr::color8c8b eColor;

  EXPECT_EQ(aColor.bestRedChan(),     0);
  EXPECT_EQ(bColor.bestRedChan(),     0);
  EXPECT_EQ(cColor.bestRedChan(),     0);
  EXPECT_EQ(dColor.bestRedChan(),     0);
  EXPECT_EQ(eColor.bestRedChan(),     0);

  EXPECT_EQ(aColor.bestGreenChan(),   0);
  EXPECT_EQ(bColor.bestGreenChan(),   1);
  EXPECT_EQ(cColor.bestGreenChan(),   1);
  EXPECT_EQ(dColor.bestGreenChan(),   1);
  EXPECT_EQ(eColor.bestGreenChan(),   1);

  EXPECT_EQ(aColor.bestBlueChan(),    0);
  EXPECT_EQ(bColor.bestBlueChan(),   -1);
  EXPECT_EQ(cColor.bestBlueChan(),    2);
  EXPECT_EQ(dColor.bestBlueChan(),    2);
  EXPECT_EQ(eColor.bestBlueChan(),    2);

  EXPECT_EQ(aColor.bestAlphaChan(),  -1);
  EXPECT_EQ(bColor.bestAlphaChan(),  -1);
  EXPECT_EQ(cColor.bestAlphaChan(),  -1);
  EXPECT_EQ(dColor.bestAlphaChan(),   3);
  EXPECT_EQ(eColor.bestAlphaChan(),   3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FUN_distDeltaE1976, bit8) {

  mjr::colorRGBA8b   aColor;
  mjr::colorRGBA8b   bColor;

  aColor.setToWhite();
  bColor.setToBlack();
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  100.0, 0.0001);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  100.0, 0.0001);
  aColor.setToWhite();
  bColor.setToWhite();
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  0.0, 0.0001);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  0.0, 0.0001);
  aColor.setToBlack();
  bColor.setChansRGB(128, 64, 192);
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  87.0379, 0.001);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  87.0382, 0.0001);
  //EXPECT_NEAR(aColor.distDeltaE2000(bColor),  40.2871, 0.0001);
  aColor.setToBlack();
  bColor.setChansRGB(128, 128, 128);
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  53.585, 0.0001);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  53.585, 0.0001);
  //EXPECT_NEAR(aColor.distDeltaE2000(bColor),  39.9344, 0.0001);
  aColor.setToBlack();
  bColor.setChansRGB(32, 64, 128);
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  50.1239, 0.01);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  50.1239, 0.01);
  //EXPECT_NEAR(aColor.distDeltaE2000(bColor),  28.4580, 0.0001);
  aColor.setToWhite();
  bColor.setChansRGB(32, 64, 128);
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  82.8934, 0.001);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  82.8807, 0.01);
  //EXPECT_NEAR(aColor.distDeltaE2000(bColor),  63.5853, 0.0001);
}

/** @endcond */
