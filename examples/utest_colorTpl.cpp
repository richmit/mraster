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
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

#include "ramCanvas.hpp"

#if 0

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
// | DIRECT   | distMaxAbs                                                                                                   |
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
// |          | ccBin01                                                                                                      |
// |          | ccBinGB                                                                                                      |
// |          | ccBinRB                                                                                                      |
// |          | ccBinMC                                                                                                      |
// |          | ccBinYC                                                                                                      |
// |          | ccBinRG                                                                                                      |
// |          | ccBinMY                                                                                                      |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | csBin_tpl                                                                                                    |
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
// |          | csHSLhB                                                                                                      |
// |          | csHSLhC                                                                                                      |
// |          | csHSLhG                                                                                                      |
// |          | csHSLhM                                                                                                      |
// |          | csHSLhR                                                                                                      |
// |          | csHSLhY                                                                                                      |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | csHSLh_tpl                                                                                                   |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | csPGrey3x                                                                                                    |
// |          | csPGrey4x                                                                                                    |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | csPLY_tpl                                                                                                    |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | csPLYcividis                                                                                                 |
// |          | csPLYgrey                                                                                                    |
// |          | csPLYhsvRB                                                                                                   |
// |          | csPLYinferno                                                                                                 |
// |          | csPLYmagma                                                                                                   |
// |          | csPLYparula                                                                                                  |
// |          | csPLYplasma                                                                                                  |
// |          | csPLYquad                                                                                                    |
// |          | csPLYturbo                                                                                                   |
// |          | csPLYviridis                                                                                                 |
// |----------+--------------------------------------------------------------------------------------------------------------|
// |          | csRainbowCM                                                                                                  |
// |          | csRainbowLA                                                                                                  |
// |----------+--------------------------------------------------------------------------------------------------------------|
// | DIRECT   | setRGBfromWavelengthCM(double wavelength, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR); |
// | DIRECT   | setRGBfromWavelengthLA(double wavelength);                                                                   |
// |----------+--------------------------------------------------------------------------------------------------------------|


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_dbl_8) {

  mjr::color4c8b aColor;

  BOOST_TEST_CHECK(mjr::color4c8b::maxChanVal  == 255);
  BOOST_TEST_CHECK(mjr::color4c8b::minChanVal  == 0);

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c8b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChan_dbl(0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c8b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGB_dbl(1.0, 1.0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c8b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChan_dbl(1, 0.5);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 127);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c8b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 127);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 127.0/mjr::color4c8b::maxChanVal, boost::test_tools::tolerance(0.005));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c8b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChans_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c8b::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 255);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 1.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGBA_dbl(1.0, 0.0, 0.5, 0.5);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 127);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 127);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 127);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 127);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 127.0/mjr::color4c8b::maxChanVal, boost::test_tools::tolerance(0.005));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 127.0/mjr::color4c8b::maxChanVal, boost::test_tools::tolerance(0.005));

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c8b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_dbl_16, * boost::unit_test::tolerance(0.001)) {

  mjr::color4c16b aColor;

  BOOST_TEST_CHECK(mjr::color4c16b::maxChanVal  == 65535);
  BOOST_TEST_CHECK(mjr::color4c16b::minChanVal  == 0);

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c16b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChan_dbl(0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c16b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGB_dbl(1.0, 1.0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c16b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChan_dbl(1, 0.5);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 32767);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c16b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 127);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 32767.0/mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c16b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChans_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c16b::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 255);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 1.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGBA_dbl(1.0, 0.0, 0.5, 0.5);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 32767);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 32767);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 127);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 127);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 32767.0/mjr::color4c16b::maxChanVal, boost::test_tools::tolerance(0.005));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 32767.0/mjr::color4c16b::maxChanVal, boost::test_tools::tolerance(0.005));

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c16b::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_dbl_64F, * boost::unit_test::tolerance(0.00001)) {

  mjr::color4c64F aColor;

  BOOST_TEST_CHECK(mjr::color4c64F::maxChanVal  == 1.0);
  BOOST_TEST_CHECK(mjr::color4c64F::minChanVal  == 0.0);

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c64F::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChan_dbl(0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c64F::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGB_dbl(1.0, 1.0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c64F::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChan_dbl(1, 0.5);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.5);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c64F::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 127);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.5);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c64F::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChans_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c64F::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 255);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 1.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGBA_dbl(1.0, 0.0, 0.5, 0.5);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.5);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.5);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 127);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 127);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.5);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.5);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c64F::minChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_byte_8) {

  mjr::color4c8b aColor;

  aColor.setToBlack();
  aColor.setChan_byte(0, 11);
  aColor.setChan_byte(1, 22);
  aColor.setChan_byte(2, 33);
  aColor.setChan_byte(3, 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 11);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 22);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 33);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 11);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 22);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 33);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 44);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setC0_byte(55);
  aColor.setC1_byte(66);
  aColor.setC2_byte(77);
  aColor.setC3_byte(88);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 55);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 66);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 77);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 88);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 55);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 66);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 77);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 88);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChans_byte(99);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 99);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 99);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 99);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 99);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 99);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGB_byte(33, 44, 55);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 33);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 44);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 55);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 99);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 33);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 44);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 55);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 99);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGBA_byte(11, 22, 33, 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 11);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 22);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 33);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 11);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 22);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 33);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 44);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  // Test that max & min are hit
  aColor.setChansRGBA_byte(0, 255, 0, 255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c8b::maxChanVal);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_byte_16) {

  mjr::color4c16b aColor;

  aColor.setToBlack();
  aColor.setChan_byte(0, 11);
  aColor.setChan_byte(1, 22);
  aColor.setChan_byte(2, 33);
  aColor.setChan_byte(3, 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0xB0B);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0x1616);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0x2121);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0x2C2C);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 11);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 22);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 33);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 44);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setC0_byte(55);
  aColor.setC1_byte(66);
  aColor.setC2_byte(77);
  aColor.setC3_byte(88);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 14135);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 16962);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 19789);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 22616);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 55);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 66);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 77);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 88);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChans_byte(99);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 25443);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 25443);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 25443);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 25443);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 99);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGB_byte(33, 44, 55);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 8481);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 11308);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 14135);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 25443);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 33);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 44);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 55);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 99);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGBA_byte(11, 22, 33, 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 2827);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 5654);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 8481);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 11308);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 11);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 22);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 33);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 44);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  // Test that max & min are hit
  aColor.setChansRGBA_byte(0, 255, 0, 255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c16b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c16b::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c16b::maxChanVal);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_byte_64F, * boost::unit_test::tolerance(0.0001)) {

  mjr::color4c64F aColor;

  aColor.setToBlack();
  aColor.setChan_byte(0, 11);
  aColor.setChan_byte(1, 22);
  aColor.setChan_byte(2, 34); // 33 has a rounding error :)
  aColor.setChan_byte(3, 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.043137254902);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.0862745098039);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.133333333333);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.172549019608);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 11);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 22);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 34);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 44);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setC0_byte(55);
  aColor.setC1_byte(65); // 66 has rounding error :)
  aColor.setC2_byte(77);
  aColor.setC3_byte(88);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.21568627450980393);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.254901960784);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.30196078431372547);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.34509803921568627);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 55);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 65);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 77);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 88);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChans_byte(99);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.38823529411764707);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.38823529411764707);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.38823529411764707);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.38823529411764707);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 99);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGB_byte(34, 44, 55);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.133333333333);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.17254901960784313);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.21568627450980393);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.38823529411764707);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 34);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 44);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 55);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 99);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGBA_byte(11, 22, 34, 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.043137254902);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.08627450980392157);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.133333333333);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.17254901960784313);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 11);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 22);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 34);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 44);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  // Test that max & min are hit
  aColor.setChansRGBA_byte(0, 255, 0, 255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == mjr::color4c64F::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == mjr::color4c64F::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == mjr::color4c64F::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_8) {

  mjr::color4c8b aColor;

  aColor.setToBlack();
  aColor.setChan(0, 11);
  aColor.setChan(1, 22);
  aColor.setChan(2, 33);
  aColor.setChan(3, 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 11);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 22);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 33);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 11);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 22);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 33);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 44);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setC0(55);
  aColor.setC1(66);
  aColor.setC2(77);
  aColor.setC3(88);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 55);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 66);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 77);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 88);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 55);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 66);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 77);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 88);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChans(99);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 99);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 99);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 99);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 99);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 99);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 99);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGB(33, 44, 55);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 33);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 44);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 55);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 99);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 33);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 44);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 55);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 99);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGBA(11, 22, 33, 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 11);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 22);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 33);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 11);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 22);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 33);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 44);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_16) {

  mjr::color4c16b aColor;

  aColor.setToBlack();
  aColor.setChan(0, 1024);
  aColor.setChan(1, 2048);
  aColor.setChan(2, 4096);
  aColor.setChan(3, 8192);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 1024);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 2048);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 4096);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 8192);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0x03);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0x07);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0x0f);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0x1f);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setC0(8192);
  aColor.setC1(4096);
  aColor.setC2(2048);
  aColor.setC3(1024);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 8192);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 4096);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2048);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 1024);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0x1f);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0x0f);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0x07);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0x03);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

   aColor.setChans(32768);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 32768);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 32768);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 32768);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 32768);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0x7f);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0x7f);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0x7f);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0x7f);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGB(4096, 8192, 16384);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 4096);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 8192);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 16384);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 32768);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0x0f);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0x1f);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0x3f);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0x7f);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGBA(1024, 2048, 4096, 8192);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 1024);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 2048);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 4096);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 8192);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0x03);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0x07);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0x0f);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0x1f);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  //Corners
  aColor.setChans(0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0) == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(0) == aColor.getC0_dbl());

  aColor.setChans(65535);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC1());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC1_byte());

  BOOST_TEST_CHECK(aColor.getChan_dbl(0) == 1.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(0) == aColor.getC1_dbl());

 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_64F) {

  mjr::color4c64F aColor;

  aColor.setToBlack();
  aColor.setChan(0, 0.25);
  aColor.setChan(1, 0.50);
  aColor.setChan(2, 0.75);
  aColor.setChan(3, 1.00);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.25);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.50);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.75);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 1.00);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) ==  63);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 127);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 191);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 255);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setC0(1.00);
  aColor.setC1(0.75);
  aColor.setC2(0.50);
  aColor.setC3(0.25);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 1.00);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.75);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.50);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.25);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 191);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 127);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 63);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

   aColor.setChans(0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 0);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGB(0.75, 0.50, 1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.75);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.50);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 1.00);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.00);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 191);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 127);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 255);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 0);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());

  aColor.setChansRGBA(0.25, 0.50, 0.75, 1.00);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.25);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.50);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.75);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 1.00);

  BOOST_TEST_CHECK(aColor.getChan(0)      == aColor.getC0());
  BOOST_TEST_CHECK(aColor.getChan(1)      == aColor.getC1());
  BOOST_TEST_CHECK(aColor.getChan(2)      == aColor.getC2());
  BOOST_TEST_CHECK(aColor.getChan(3)      == aColor.getC3());

  BOOST_TEST_CHECK(aColor.getChan_byte(0) ==  63);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 127);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 191);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 255);

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == aColor.getC0_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == aColor.getC1_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == aColor.getC2_byte());
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == aColor.getC3_byte());
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(constr_64F) {

  mjr::color4c64F aColor(0.25);
  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.25);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.25);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.25);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.25);

  mjr::color4c64F cColor(0.25, 0.50, 0.75);
  BOOST_TEST_CHECK(cColor.getChan(0)      == 0.25);
  BOOST_TEST_CHECK(cColor.getChan(1)      == 0.50);
  BOOST_TEST_CHECK(cColor.getChan(2)      == 0.75);
  BOOST_TEST_CHECK(cColor.getChan(3)      == 0.00);

  mjr::color4c64F dColor(1.00, 0.75, 0.50, 0.25);
  BOOST_TEST_CHECK(dColor.getChan(0)      == 1.00);
  BOOST_TEST_CHECK(dColor.getChan(1)      == 0.75);
  BOOST_TEST_CHECK(dColor.getChan(2)      == 0.50);
  BOOST_TEST_CHECK(dColor.getChan(3)      == 0.25);

  mjr::color4c64F eColor(dColor);
  BOOST_TEST_CHECK(eColor.getChan(0)      == 1.00);
  BOOST_TEST_CHECK(eColor.getChan(1)      == 0.75);
  BOOST_TEST_CHECK(eColor.getChan(2)      == 0.50);
  BOOST_TEST_CHECK(eColor.getChan(3)      == 0.25);

  mjr::color4c64F f0Color(mjr::color4c64F::cornerColorEnum::BLACK);
  mjr::color4c64F fRColor(mjr::color4c64F::cornerColorEnum::RED);
  mjr::color4c64F fGColor(mjr::color4c64F::cornerColorEnum::GREEN);
  mjr::color4c64F fBColor(mjr::color4c64F::cornerColorEnum::BLUE);
  mjr::color4c64F fYColor(mjr::color4c64F::cornerColorEnum::YELLOW);
  mjr::color4c64F fCColor(mjr::color4c64F::cornerColorEnum::CYAN);
  mjr::color4c64F fMColor(mjr::color4c64F::cornerColorEnum::MAGENTA);
  mjr::color4c64F f1Color(mjr::color4c64F::cornerColorEnum::WHITE);

  BOOST_TEST_CHECK(f0Color.getC0() == 0.0);
  BOOST_TEST_CHECK(fRColor.getC0() == 1.0);
  BOOST_TEST_CHECK(fGColor.getC0() == 0.0);
  BOOST_TEST_CHECK(fBColor.getC0() == 0.0);
  BOOST_TEST_CHECK(fYColor.getC0() == 1.0);
  BOOST_TEST_CHECK(fCColor.getC0() == 0.0);
  BOOST_TEST_CHECK(fMColor.getC0() == 1.0);
  BOOST_TEST_CHECK(f1Color.getC0() == 1.0);

  BOOST_TEST_CHECK(f0Color.getC1() == 0.0);
  BOOST_TEST_CHECK(fRColor.getC1() == 0.0);
  BOOST_TEST_CHECK(fGColor.getC1() == 1.0);
  BOOST_TEST_CHECK(fBColor.getC1() == 0.0);
  BOOST_TEST_CHECK(fYColor.getC1() == 1.0);
  BOOST_TEST_CHECK(fCColor.getC1() == 1.0);
  BOOST_TEST_CHECK(fMColor.getC1() == 0.0);
  BOOST_TEST_CHECK(f1Color.getC1() == 1.0);

  BOOST_TEST_CHECK(f0Color.getC2() == 0.0);
  BOOST_TEST_CHECK(fRColor.getC2() == 0.0);
  BOOST_TEST_CHECK(fGColor.getC2() == 0.0);
  BOOST_TEST_CHECK(fBColor.getC2() == 1.0);
  BOOST_TEST_CHECK(fYColor.getC2() == 0.0);
  BOOST_TEST_CHECK(fCColor.getC2() == 1.0);
  BOOST_TEST_CHECK(fMColor.getC2() == 1.0);
  BOOST_TEST_CHECK(f1Color.getC2() == 1.0);

  BOOST_TEST_CHECK(f0Color.getC3() == 0.0);
  BOOST_TEST_CHECK(fRColor.getC3() == 0.0); // primary
  BOOST_TEST_CHECK(fGColor.getC3() == 0.0); // primary
  BOOST_TEST_CHECK(fBColor.getC3() == 0.0); // primary
  BOOST_TEST_CHECK(fYColor.getC3() == 1.0); // secondary
  BOOST_TEST_CHECK(fCColor.getC3() == 1.0); // secondary
  BOOST_TEST_CHECK(fMColor.getC3() == 1.0); // secondary
  BOOST_TEST_CHECK(f1Color.getC3() == 1.0);

  // magic string -- corner with single character.

  mjr::color4c64F g0Color("0");
  mjr::color4c64F gRColor("R");
  mjr::color4c64F gGColor("G");
  mjr::color4c64F gBColor("B");
  mjr::color4c64F gYColor("Y");
  mjr::color4c64F gCColor("C");
  mjr::color4c64F gMColor("M");
  mjr::color4c64F g1Color("W");

  BOOST_TEST_CHECK(g0Color.getC0() == 0.0);
  BOOST_TEST_CHECK(gRColor.getC0() == 1.0);
  BOOST_TEST_CHECK(gGColor.getC0() == 0.0);
  BOOST_TEST_CHECK(gBColor.getC0() == 0.0);
  BOOST_TEST_CHECK(gYColor.getC0() == 1.0);
  BOOST_TEST_CHECK(gCColor.getC0() == 0.0);
  BOOST_TEST_CHECK(gMColor.getC0() == 1.0);
  BOOST_TEST_CHECK(g1Color.getC0() == 1.0);

  BOOST_TEST_CHECK(g0Color.getC1() == 0.0);
  BOOST_TEST_CHECK(gRColor.getC1() == 0.0);
  BOOST_TEST_CHECK(gGColor.getC1() == 1.0);
  BOOST_TEST_CHECK(gBColor.getC1() == 0.0);
  BOOST_TEST_CHECK(gYColor.getC1() == 1.0);
  BOOST_TEST_CHECK(gCColor.getC1() == 1.0);
  BOOST_TEST_CHECK(gMColor.getC1() == 0.0);
  BOOST_TEST_CHECK(g1Color.getC1() == 1.0);

  BOOST_TEST_CHECK(g0Color.getC2() == 0.0);
  BOOST_TEST_CHECK(gRColor.getC2() == 0.0);
  BOOST_TEST_CHECK(gGColor.getC2() == 0.0);
  BOOST_TEST_CHECK(gBColor.getC2() == 1.0);
  BOOST_TEST_CHECK(gYColor.getC2() == 0.0);
  BOOST_TEST_CHECK(gCColor.getC2() == 1.0);
  BOOST_TEST_CHECK(gMColor.getC2() == 1.0);
  BOOST_TEST_CHECK(g1Color.getC2() == 1.0);

  BOOST_TEST_CHECK(g0Color.getC3() == 0.0);
  BOOST_TEST_CHECK(gRColor.getC3() == 0.0); // primary
  BOOST_TEST_CHECK(gGColor.getC3() == 0.0); // primary
  BOOST_TEST_CHECK(gBColor.getC3() == 0.0); // primary
  BOOST_TEST_CHECK(gYColor.getC3() == 1.0); // secondary
  BOOST_TEST_CHECK(gCColor.getC3() == 1.0); // secondary
  BOOST_TEST_CHECK(gMColor.getC3() == 1.0); // secondary
  BOOST_TEST_CHECK(g1Color.getC3() == 1.0);

  // magic string -- corner with full name

  mjr::color4c64F h0Color("black");
  mjr::color4c64F hRColor("Red");
  mjr::color4c64F hGColor("GREEN");
  mjr::color4c64F hBColor("blue");
  mjr::color4c64F hYColor("YeLLoW");
  mjr::color4c64F hCColor("CYAN");
  mjr::color4c64F hMColor("MAGENTA");
  mjr::color4c64F h1Color("White");

  BOOST_TEST_CHECK(h0Color.getC0() == 0.0);
  BOOST_TEST_CHECK(hRColor.getC0() == 1.0);
  BOOST_TEST_CHECK(hGColor.getC0() == 0.0);
  BOOST_TEST_CHECK(hBColor.getC0() == 0.0);
  BOOST_TEST_CHECK(hYColor.getC0() == 1.0);
  BOOST_TEST_CHECK(hCColor.getC0() == 0.0);
  BOOST_TEST_CHECK(hMColor.getC0() == 1.0);
  BOOST_TEST_CHECK(h1Color.getC0() == 1.0);

  BOOST_TEST_CHECK(h0Color.getC1() == 0.0);
  BOOST_TEST_CHECK(hRColor.getC1() == 0.0);
  BOOST_TEST_CHECK(hGColor.getC1() == 1.0);
  BOOST_TEST_CHECK(hBColor.getC1() == 0.0);
  BOOST_TEST_CHECK(hYColor.getC1() == 1.0);
  BOOST_TEST_CHECK(hCColor.getC1() == 1.0);
  BOOST_TEST_CHECK(hMColor.getC1() == 0.0);
  BOOST_TEST_CHECK(h1Color.getC1() == 1.0);

  BOOST_TEST_CHECK(h0Color.getC2() == 0.0);
  BOOST_TEST_CHECK(hRColor.getC2() == 0.0);
  BOOST_TEST_CHECK(hGColor.getC2() == 0.0);
  BOOST_TEST_CHECK(hBColor.getC2() == 1.0);
  BOOST_TEST_CHECK(hYColor.getC2() == 0.0);
  BOOST_TEST_CHECK(hCColor.getC2() == 1.0);
  BOOST_TEST_CHECK(hMColor.getC2() == 1.0);
  BOOST_TEST_CHECK(h1Color.getC2() == 1.0);

  BOOST_TEST_CHECK(h0Color.getC3() == 0.0);
  BOOST_TEST_CHECK(hRColor.getC3() == 0.0); // primary
  BOOST_TEST_CHECK(hGColor.getC3() == 0.0); // primary
  BOOST_TEST_CHECK(hBColor.getC3() == 0.0); // primary
  BOOST_TEST_CHECK(hYColor.getC3() == 1.0); // secondary
  BOOST_TEST_CHECK(hCColor.getC3() == 1.0); // secondary
  BOOST_TEST_CHECK(hMColor.getC3() == 1.0); // secondary
  BOOST_TEST_CHECK(h1Color.getC3() == 1.0);

  mjr::color4c64F iColor("zoogo");   // unknown color => black
  BOOST_TEST_CHECK(iColor.getC0() == 0.0);
  BOOST_TEST_CHECK(iColor.getC1() == 0.0);
  BOOST_TEST_CHECK(iColor.getC2() == 0.0);
  BOOST_TEST_CHECK(iColor.getC3() == 0.0);

  mjr::color4c64F jColor("z");   // unknown color => black
  BOOST_TEST_CHECK(jColor.getC0() == 0.0);
  BOOST_TEST_CHECK(jColor.getC1() == 0.0);
  BOOST_TEST_CHECK(jColor.getC2() == 0.0);
  BOOST_TEST_CHECK(jColor.getC3() == 0.0);

  mjr::color4c64F kColor("#aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd");
  BOOST_TEST_CHECK(kColor.getC0() == 0.66666666666, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(kColor.getC1() == 0.73333333333, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(kColor.getC2() == 0.80000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(kColor.getC3() == 0.86666666666, boost::test_tools::tolerance(0.00001));

 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(constr_8b) {

  mjr::color4c8b aColor(123);
  BOOST_TEST_CHECK(aColor.getChan(0) == 123);
  BOOST_TEST_CHECK(aColor.getChan(1) == 123);
  BOOST_TEST_CHECK(aColor.getChan(2) == 123);
  BOOST_TEST_CHECK(aColor.getChan(3) == 123);

  mjr::color4c8b cColor(33, 44, 55);
  BOOST_TEST_CHECK(cColor.getChan(0) == 33);
  BOOST_TEST_CHECK(cColor.getChan(1) == 44);
  BOOST_TEST_CHECK(cColor.getChan(2) == 55);
  BOOST_TEST_CHECK(cColor.getChan(3) == 0);

  mjr::color4c8b dColor(66, 77, 88, 99);
  BOOST_TEST_CHECK(dColor.getChan(0) == 66);
  BOOST_TEST_CHECK(dColor.getChan(1) == 77);
  BOOST_TEST_CHECK(dColor.getChan(2) == 88);
  BOOST_TEST_CHECK(dColor.getChan(3) == 99);

  mjr::color4c8b eColor(dColor);
  BOOST_TEST_CHECK(eColor.getChan(0) == 66);
  BOOST_TEST_CHECK(eColor.getChan(1) == 77);
  BOOST_TEST_CHECK(eColor.getChan(2) == 88);
  BOOST_TEST_CHECK(eColor.getChan(3) == 99);

  mjr::color4c8b f0Color(mjr::color4c8b::cornerColorEnum::BLACK);
  mjr::color4c8b fRColor(mjr::color4c8b::cornerColorEnum::RED);
  mjr::color4c8b fGColor(mjr::color4c8b::cornerColorEnum::GREEN);
  mjr::color4c8b fBColor(mjr::color4c8b::cornerColorEnum::BLUE);
  mjr::color4c8b fYColor(mjr::color4c8b::cornerColorEnum::YELLOW);
  mjr::color4c8b fCColor(mjr::color4c8b::cornerColorEnum::CYAN);
  mjr::color4c8b fMColor(mjr::color4c8b::cornerColorEnum::MAGENTA);
  mjr::color4c8b f1Color(mjr::color4c8b::cornerColorEnum::WHITE);

  BOOST_TEST_CHECK(f0Color.getC0()   == 0);
  BOOST_TEST_CHECK(fRColor.getC0()   == 255);
  BOOST_TEST_CHECK(fGColor.getC0()   == 0);
  BOOST_TEST_CHECK(fBColor.getC0()   == 0);
  BOOST_TEST_CHECK(fYColor.getC0()   == 255);
  BOOST_TEST_CHECK(fCColor.getC0()   == 0);
  BOOST_TEST_CHECK(fMColor.getC0()   == 255);
  BOOST_TEST_CHECK(f1Color.getC0()   == 255);

  BOOST_TEST_CHECK(f0Color.getC1()   == 0);
  BOOST_TEST_CHECK(fRColor.getC1()   == 0);
  BOOST_TEST_CHECK(fGColor.getC1()   == 255);
  BOOST_TEST_CHECK(fBColor.getC1()   == 0);
  BOOST_TEST_CHECK(fYColor.getC1()   == 255);
  BOOST_TEST_CHECK(fCColor.getC1()   == 255);
  BOOST_TEST_CHECK(fMColor.getC1()   == 0);
  BOOST_TEST_CHECK(f1Color.getC1()   == 255);

  BOOST_TEST_CHECK(f0Color.getC2()   == 0);
  BOOST_TEST_CHECK(fRColor.getC2()   == 0);
  BOOST_TEST_CHECK(fGColor.getC2()   == 0);
  BOOST_TEST_CHECK(fBColor.getC2()   == 255);
  BOOST_TEST_CHECK(fYColor.getC2()   == 0);
  BOOST_TEST_CHECK(fCColor.getC2()   == 255);
  BOOST_TEST_CHECK(fMColor.getC2()   == 255);
  BOOST_TEST_CHECK(f1Color.getC2()   == 255);

  BOOST_TEST_CHECK(f0Color.getC3()   == 0);
  BOOST_TEST_CHECK(fRColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(fGColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(fBColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(fYColor.getC3()   == 255); // secondary
  BOOST_TEST_CHECK(fCColor.getC3()   == 255); // secondary
  BOOST_TEST_CHECK(fMColor.getC3()   == 255); // secondary
  BOOST_TEST_CHECK(f1Color.getC3()   == 255);

  // magic string -- corner with single character.

  mjr::color4c8b g0Color("0");
  mjr::color4c8b gRColor("R");
  mjr::color4c8b gGColor("G");
  mjr::color4c8b gBColor("B");
  mjr::color4c8b gYColor("Y");
  mjr::color4c8b gCColor("C");
  mjr::color4c8b gMColor("M");
  mjr::color4c8b g1Color("W");

  BOOST_TEST_CHECK(g0Color.getC0()   == 0);
  BOOST_TEST_CHECK(gRColor.getC0()   == 255);
  BOOST_TEST_CHECK(gGColor.getC0()   == 0);
  BOOST_TEST_CHECK(gBColor.getC0()   == 0);
  BOOST_TEST_CHECK(gYColor.getC0()   == 255);
  BOOST_TEST_CHECK(gCColor.getC0()   == 0);
  BOOST_TEST_CHECK(gMColor.getC0()   == 255);
  BOOST_TEST_CHECK(g1Color.getC0()   == 255);

  BOOST_TEST_CHECK(g0Color.getC1()   == 0);
  BOOST_TEST_CHECK(gRColor.getC1()   == 0);
  BOOST_TEST_CHECK(gGColor.getC1()   == 255);
  BOOST_TEST_CHECK(gBColor.getC1()   == 0);
  BOOST_TEST_CHECK(gYColor.getC1()   == 255);
  BOOST_TEST_CHECK(gCColor.getC1()   == 255);
  BOOST_TEST_CHECK(gMColor.getC1()   == 0);
  BOOST_TEST_CHECK(g1Color.getC1()   == 255);

  BOOST_TEST_CHECK(g0Color.getC2()   == 0);
  BOOST_TEST_CHECK(gRColor.getC2()   == 0);
  BOOST_TEST_CHECK(gGColor.getC2()   == 0);
  BOOST_TEST_CHECK(gBColor.getC2()   == 255);
  BOOST_TEST_CHECK(gYColor.getC2()   == 0);
  BOOST_TEST_CHECK(gCColor.getC2()   == 255);
  BOOST_TEST_CHECK(gMColor.getC2()   == 255);
  BOOST_TEST_CHECK(g1Color.getC2()   == 255);

  BOOST_TEST_CHECK(g0Color.getC3()   == 0);
  BOOST_TEST_CHECK(gRColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(gGColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(gBColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(gYColor.getC3()   == 255); // secondary
  BOOST_TEST_CHECK(gCColor.getC3()   == 255); // secondary
  BOOST_TEST_CHECK(gMColor.getC3()   == 255); // secondary
  BOOST_TEST_CHECK(g1Color.getC3()   == 255);

  // magic string -- corner with full name

  mjr::color4c8b h0Color("black");
  mjr::color4c8b hRColor("Red");
  mjr::color4c8b hGColor("GREEN");
  mjr::color4c8b hBColor("blue");
  mjr::color4c8b hYColor("YeLLoW");
  mjr::color4c8b hCColor("CYAN");
  mjr::color4c8b hMColor("MAGENTA");
  mjr::color4c8b h1Color("White");

  BOOST_TEST_CHECK(h0Color.getC0()   == 0);
  BOOST_TEST_CHECK(hRColor.getC0()   == 255);
  BOOST_TEST_CHECK(hGColor.getC0()   == 0);
  BOOST_TEST_CHECK(hBColor.getC0()   == 0);
  BOOST_TEST_CHECK(hYColor.getC0()   == 255);
  BOOST_TEST_CHECK(hCColor.getC0()   == 0);
  BOOST_TEST_CHECK(hMColor.getC0()   == 255);
  BOOST_TEST_CHECK(h1Color.getC0()   == 255);

  BOOST_TEST_CHECK(h0Color.getC1()   == 0);
  BOOST_TEST_CHECK(hRColor.getC1()   == 0);
  BOOST_TEST_CHECK(hGColor.getC1()   == 255);
  BOOST_TEST_CHECK(hBColor.getC1()   == 0);
  BOOST_TEST_CHECK(hYColor.getC1()   == 255);
  BOOST_TEST_CHECK(hCColor.getC1()   == 255);
  BOOST_TEST_CHECK(hMColor.getC1()   == 0);
  BOOST_TEST_CHECK(h1Color.getC1()   == 255);

  BOOST_TEST_CHECK(h0Color.getC2()   == 0);
  BOOST_TEST_CHECK(hRColor.getC2()   == 0);
  BOOST_TEST_CHECK(hGColor.getC2()   == 0);
  BOOST_TEST_CHECK(hBColor.getC2()   == 255);
  BOOST_TEST_CHECK(hYColor.getC2()   == 0);
  BOOST_TEST_CHECK(hCColor.getC2()   == 255);
  BOOST_TEST_CHECK(hMColor.getC2()   == 255);
  BOOST_TEST_CHECK(h1Color.getC2()   == 255);

  BOOST_TEST_CHECK(h0Color.getC3()   == 0);
  BOOST_TEST_CHECK(hRColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(hGColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(hBColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(hYColor.getC3()   == 255); // secondary
  BOOST_TEST_CHECK(hCColor.getC3()   == 255); // secondary
  BOOST_TEST_CHECK(hMColor.getC3()   == 255); // secondary
  BOOST_TEST_CHECK(h1Color.getC3()   == 255);

  mjr::color4c8b iColor("zoogo");   // unknown color => black
  BOOST_TEST_CHECK(iColor.getC0()    == 0);
  BOOST_TEST_CHECK(iColor.getC1()    == 0);
  BOOST_TEST_CHECK(iColor.getC2()    == 0);
  BOOST_TEST_CHECK(iColor.getC3()    == 0);

  mjr::color4c8b jColor("z");   // unknown color => black
  BOOST_TEST_CHECK(jColor.getC0()    == 0);
  BOOST_TEST_CHECK(jColor.getC1()    == 0);
  BOOST_TEST_CHECK(jColor.getC2()    == 0);
  BOOST_TEST_CHECK(jColor.getC3()    == 0);

  mjr::color4c8b kColor("#aabbccdd");
  BOOST_TEST_CHECK(kColor.getC0()    == 0xAA);
  BOOST_TEST_CHECK(kColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(kColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(kColor.getC3()    == 0xDD);

  mjr::color4c8b lColor("#bbccdd");
  BOOST_TEST_CHECK(lColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(lColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(lColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(lColor.getC3()    == 0x0);

  mjr::color4c8b mColor("#aa");
  BOOST_TEST_CHECK(mColor.getC0()    == 0xAA);
  BOOST_TEST_CHECK(mColor.getC1()    == 0x0);
  BOOST_TEST_CHECK(mColor.getC2()    == 0x0);
  BOOST_TEST_CHECK(mColor.getC3()    == 0x0);

  mjr::color4c8b nColor("#a");
  BOOST_TEST_CHECK(nColor.getC0()    == 0x0);
  BOOST_TEST_CHECK(nColor.getC1()    == 0x0);
  BOOST_TEST_CHECK(nColor.getC2()    == 0x0);
  BOOST_TEST_CHECK(nColor.getC3()    == 0x0);

 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(constr_16b) {

  mjr::color4c16b aColor(123);
  BOOST_TEST_CHECK(aColor.getChan(0) == 123);
  BOOST_TEST_CHECK(aColor.getChan(1) == 123);
  BOOST_TEST_CHECK(aColor.getChan(2) == 123);
  BOOST_TEST_CHECK(aColor.getChan(3) == 123);

  mjr::color4c16b cColor(33, 44, 55);
  BOOST_TEST_CHECK(cColor.getChan(0) == 33);
  BOOST_TEST_CHECK(cColor.getChan(1) == 44);
  BOOST_TEST_CHECK(cColor.getChan(2) == 55);
  BOOST_TEST_CHECK(cColor.getChan(3) == 0);

  mjr::color4c16b dColor(66, 77, 88, 99);
  BOOST_TEST_CHECK(dColor.getChan(0) == 66);
  BOOST_TEST_CHECK(dColor.getChan(1) == 77);
  BOOST_TEST_CHECK(dColor.getChan(2) == 88);
  BOOST_TEST_CHECK(dColor.getChan(3) == 99);

  mjr::color4c16b eColor(dColor);
  BOOST_TEST_CHECK(eColor.getChan(0) == 66);
  BOOST_TEST_CHECK(eColor.getChan(1) == 77);
  BOOST_TEST_CHECK(eColor.getChan(2) == 88);
  BOOST_TEST_CHECK(eColor.getChan(3) == 99);

  mjr::color4c16b f0Color(mjr::color4c16b::cornerColorEnum::BLACK);
  mjr::color4c16b fRColor(mjr::color4c16b::cornerColorEnum::RED);
  mjr::color4c16b fGColor(mjr::color4c16b::cornerColorEnum::GREEN);
  mjr::color4c16b fBColor(mjr::color4c16b::cornerColorEnum::BLUE);
  mjr::color4c16b fYColor(mjr::color4c16b::cornerColorEnum::YELLOW);
  mjr::color4c16b fCColor(mjr::color4c16b::cornerColorEnum::CYAN);
  mjr::color4c16b fMColor(mjr::color4c16b::cornerColorEnum::MAGENTA);
  mjr::color4c16b f1Color(mjr::color4c16b::cornerColorEnum::WHITE);

  BOOST_TEST_CHECK(f0Color.getC0()   == 0);
  BOOST_TEST_CHECK(fRColor.getC0()   == 65535);
  BOOST_TEST_CHECK(fGColor.getC0()   == 0);
  BOOST_TEST_CHECK(fBColor.getC0()   == 0);
  BOOST_TEST_CHECK(fYColor.getC0()   == 65535);
  BOOST_TEST_CHECK(fCColor.getC0()   == 0);
  BOOST_TEST_CHECK(fMColor.getC0()   == 65535);
  BOOST_TEST_CHECK(f1Color.getC0()   == 65535);

  BOOST_TEST_CHECK(f0Color.getC1()   == 0);
  BOOST_TEST_CHECK(fRColor.getC1()   == 0);
  BOOST_TEST_CHECK(fGColor.getC1()   == 65535);
  BOOST_TEST_CHECK(fBColor.getC1()   == 0);
  BOOST_TEST_CHECK(fYColor.getC1()   == 65535);
  BOOST_TEST_CHECK(fCColor.getC1()   == 65535);
  BOOST_TEST_CHECK(fMColor.getC1()   == 0);
  BOOST_TEST_CHECK(f1Color.getC1()   == 65535);

  BOOST_TEST_CHECK(f0Color.getC2()   == 0);
  BOOST_TEST_CHECK(fRColor.getC2()   == 0);
  BOOST_TEST_CHECK(fGColor.getC2()   == 0);
  BOOST_TEST_CHECK(fBColor.getC2()   == 65535);
  BOOST_TEST_CHECK(fYColor.getC2()   == 0);
  BOOST_TEST_CHECK(fCColor.getC2()   == 65535);
  BOOST_TEST_CHECK(fMColor.getC2()   == 65535);
  BOOST_TEST_CHECK(f1Color.getC2()   == 65535);

  BOOST_TEST_CHECK(f0Color.getC3()   == 0);
  BOOST_TEST_CHECK(fRColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(fGColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(fBColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(fYColor.getC3()   == 65535); // secondary
  BOOST_TEST_CHECK(fCColor.getC3()   == 65535); // secondary
  BOOST_TEST_CHECK(fMColor.getC3()   == 65535); // secondary
  BOOST_TEST_CHECK(f1Color.getC3()   == 65535);

  // magic string -- corner with single character.

  mjr::color4c16b g0Color("0");
  mjr::color4c16b gRColor("R");
  mjr::color4c16b gGColor("G");
  mjr::color4c16b gBColor("B");
  mjr::color4c16b gYColor("Y");
  mjr::color4c16b gCColor("C");
  mjr::color4c16b gMColor("M");
  mjr::color4c16b g1Color("W");

  BOOST_TEST_CHECK(g0Color.getC0()   == 0);
  BOOST_TEST_CHECK(gRColor.getC0()   == 65535);
  BOOST_TEST_CHECK(gGColor.getC0()   == 0);
  BOOST_TEST_CHECK(gBColor.getC0()   == 0);
  BOOST_TEST_CHECK(gYColor.getC0()   == 65535);
  BOOST_TEST_CHECK(gCColor.getC0()   == 0);
  BOOST_TEST_CHECK(gMColor.getC0()   == 65535);
  BOOST_TEST_CHECK(g1Color.getC0()   == 65535);

  BOOST_TEST_CHECK(g0Color.getC1()   == 0);
  BOOST_TEST_CHECK(gRColor.getC1()   == 0);
  BOOST_TEST_CHECK(gGColor.getC1()   == 65535);
  BOOST_TEST_CHECK(gBColor.getC1()   == 0);
  BOOST_TEST_CHECK(gYColor.getC1()   == 65535);
  BOOST_TEST_CHECK(gCColor.getC1()   == 65535);
  BOOST_TEST_CHECK(gMColor.getC1()   == 0);
  BOOST_TEST_CHECK(g1Color.getC1()   == 65535);

  BOOST_TEST_CHECK(g0Color.getC2()   == 0);
  BOOST_TEST_CHECK(gRColor.getC2()   == 0);
  BOOST_TEST_CHECK(gGColor.getC2()   == 0);
  BOOST_TEST_CHECK(gBColor.getC2()   == 65535);
  BOOST_TEST_CHECK(gYColor.getC2()   == 0);
  BOOST_TEST_CHECK(gCColor.getC2()   == 65535);
  BOOST_TEST_CHECK(gMColor.getC2()   == 65535);
  BOOST_TEST_CHECK(g1Color.getC2()   == 65535);

  BOOST_TEST_CHECK(g0Color.getC3()   == 0);
  BOOST_TEST_CHECK(gRColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(gGColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(gBColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(gYColor.getC3()   == 65535); // secondary
  BOOST_TEST_CHECK(gCColor.getC3()   == 65535); // secondary
  BOOST_TEST_CHECK(gMColor.getC3()   == 65535); // secondary
  BOOST_TEST_CHECK(g1Color.getC3()   == 65535);

  // magic string -- corner with full name

  mjr::color4c16b h0Color("black");
  mjr::color4c16b hRColor("Red");
  mjr::color4c16b hGColor("GREEN");
  mjr::color4c16b hBColor("blue");
  mjr::color4c16b hYColor("YeLLoW");
  mjr::color4c16b hCColor("CYAN");
  mjr::color4c16b hMColor("MAGENTA");
  mjr::color4c16b h1Color("White");

  BOOST_TEST_CHECK(h0Color.getC0()   == 0);
  BOOST_TEST_CHECK(hRColor.getC0()   == 65535);
  BOOST_TEST_CHECK(hGColor.getC0()   == 0);
  BOOST_TEST_CHECK(hBColor.getC0()   == 0);
  BOOST_TEST_CHECK(hYColor.getC0()   == 65535);
  BOOST_TEST_CHECK(hCColor.getC0()   == 0);
  BOOST_TEST_CHECK(hMColor.getC0()   == 65535);
  BOOST_TEST_CHECK(h1Color.getC0()   == 65535);

  BOOST_TEST_CHECK(h0Color.getC1()   == 0);
  BOOST_TEST_CHECK(hRColor.getC1()   == 0);
  BOOST_TEST_CHECK(hGColor.getC1()   == 65535);
  BOOST_TEST_CHECK(hBColor.getC1()   == 0);
  BOOST_TEST_CHECK(hYColor.getC1()   == 65535);
  BOOST_TEST_CHECK(hCColor.getC1()   == 65535);
  BOOST_TEST_CHECK(hMColor.getC1()   == 0);
  BOOST_TEST_CHECK(h1Color.getC1()   == 65535);

  BOOST_TEST_CHECK(h0Color.getC2()   == 0);
  BOOST_TEST_CHECK(hRColor.getC2()   == 0);
  BOOST_TEST_CHECK(hGColor.getC2()   == 0);
  BOOST_TEST_CHECK(hBColor.getC2()   == 65535);
  BOOST_TEST_CHECK(hYColor.getC2()   == 0);
  BOOST_TEST_CHECK(hCColor.getC2()   == 65535);
  BOOST_TEST_CHECK(hMColor.getC2()   == 65535);
  BOOST_TEST_CHECK(h1Color.getC2()   == 65535);

  BOOST_TEST_CHECK(h0Color.getC3()   == 0);
  BOOST_TEST_CHECK(hRColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(hGColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(hBColor.getC3()   == 0); // primary
  BOOST_TEST_CHECK(hYColor.getC3()   == 65535); // secondary
  BOOST_TEST_CHECK(hCColor.getC3()   == 65535); // secondary
  BOOST_TEST_CHECK(hMColor.getC3()   == 65535); // secondary
  BOOST_TEST_CHECK(h1Color.getC3()   == 65535);

  mjr::color4c16b iColor("zoogo");   // unknown color => black
  BOOST_TEST_CHECK(iColor.getC0()    == 0);
  BOOST_TEST_CHECK(iColor.getC1()    == 0);
  BOOST_TEST_CHECK(iColor.getC2()    == 0);
  BOOST_TEST_CHECK(iColor.getC3()    == 0);

  mjr::color4c16b jColor("z");   // unknown color => black
  BOOST_TEST_CHECK(jColor.getC0()    == 0);
  BOOST_TEST_CHECK(jColor.getC1()    == 0);
  BOOST_TEST_CHECK(jColor.getC2()    == 0);
  BOOST_TEST_CHECK(jColor.getC3()    == 0);

  mjr::color4c16b kColor("#aaaabbbbccccdddd");
  BOOST_TEST_CHECK(kColor.getC0()    == 0xAAAA);
  BOOST_TEST_CHECK(kColor.getC1()    == 0xBBBB);
  BOOST_TEST_CHECK(kColor.getC2()    == 0xCCCC);
  BOOST_TEST_CHECK(kColor.getC3()    == 0xDDDD);

  mjr::color4c16b lColor("#bbbbccccdddd");
  BOOST_TEST_CHECK(lColor.getC0()    == 0xBBBB);
  BOOST_TEST_CHECK(lColor.getC1()    == 0xCCCC);
  BOOST_TEST_CHECK(lColor.getC2()    == 0xDDDD);
  BOOST_TEST_CHECK(lColor.getC3()    == 0x0);

  mjr::color4c16b mColor("#aaaa");
  BOOST_TEST_CHECK(mColor.getC0()    == 0xAAAA);
  BOOST_TEST_CHECK(mColor.getC1()    == 0x0);
  BOOST_TEST_CHECK(mColor.getC2()    == 0x0);
  BOOST_TEST_CHECK(mColor.getC3()    == 0x0);

  mjr::color4c16b nColor("#aaa");
  BOOST_TEST_CHECK(nColor.getC0()    == 0x0);
  BOOST_TEST_CHECK(nColor.getC1()    == 0x0);
  BOOST_TEST_CHECK(nColor.getC2()    == 0x0);
  BOOST_TEST_CHECK(nColor.getC3()    == 0x0);

 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chans_hex_8b) {

  mjr::color4c8b aColor("0");
  aColor.setToWhite();
  aColor.setChans("#aabbccdd");
  BOOST_TEST_CHECK(aColor.getC0() == 0xAA);
  BOOST_TEST_CHECK(aColor.getC1() == 0xBB);
  BOOST_TEST_CHECK(aColor.getC2() == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3() == 0xDD);

  // undefined chans left alown
  aColor.setToWhite();
  aColor.setChans("#bbccdd");
  BOOST_TEST_CHECK(aColor.getC0() == 0xBB);
  BOOST_TEST_CHECK(aColor.getC1() == 0xCC);
  BOOST_TEST_CHECK(aColor.getC2() == 0xDD);
  BOOST_TEST_CHECK(aColor.getC3() == 0xFF);

  aColor.setToWhite();
  aColor.setChans("#aa");
  BOOST_TEST_CHECK(aColor.getC0() == 0xAA);
  BOOST_TEST_CHECK(aColor.getC1() == 0xFF);
  BOOST_TEST_CHECK(aColor.getC2() == 0xFF);
  BOOST_TEST_CHECK(aColor.getC3() == 0xFF);

  aColor.setToWhite();
  aColor.setChans("#aaa");
  BOOST_TEST_CHECK(aColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(aColor.getC1() == 0xFF);
  BOOST_TEST_CHECK(aColor.getC2() == 0xFF);
  BOOST_TEST_CHECK(aColor.getC3() == 0xFF);

  // undefined chans set to min
  aColor.setToWhite();
  aColor.setChans("#bbccdd", true);
  BOOST_TEST_CHECK(aColor.getC0() == 0xBB);
  BOOST_TEST_CHECK(aColor.getC1() == 0xCC);
  BOOST_TEST_CHECK(aColor.getC2() == 0xDD);
  BOOST_TEST_CHECK(aColor.getC3() == 0x0000);

  aColor.setToWhite();
  aColor.setChans("#aa", true);
  BOOST_TEST_CHECK(aColor.getC0() == 0xAA);
  BOOST_TEST_CHECK(aColor.getC1() == 0x0000);
  BOOST_TEST_CHECK(aColor.getC2() == 0x0000);
  BOOST_TEST_CHECK(aColor.getC3() == 0x0000);

  aColor.setToWhite();
  aColor.setChans("#a", true);
  BOOST_TEST_CHECK(aColor.getC0() == 0x0000);
  BOOST_TEST_CHECK(aColor.getC1() == 0x0000);
  BOOST_TEST_CHECK(aColor.getC2() == 0x0000);
  BOOST_TEST_CHECK(aColor.getC3() == 0x0000);

 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chans_hex_16b) {

  mjr::color4c16b aColor("0");
  aColor.setToWhite();
  aColor.setChans("#aaaabbbbccccdddd");
  BOOST_TEST_CHECK(aColor.getC0() == 0xAAAA);
  BOOST_TEST_CHECK(aColor.getC1() == 0xBBBB);
  BOOST_TEST_CHECK(aColor.getC2() == 0xCCCC);
  BOOST_TEST_CHECK(aColor.getC3() == 0xDDDD);

  // undefined chans left alown
  aColor.setToWhite();
  aColor.setChans("#bbbbccccdddd");
  BOOST_TEST_CHECK(aColor.getC0() == 0xBBBB);
  BOOST_TEST_CHECK(aColor.getC1() == 0xCCCC);
  BOOST_TEST_CHECK(aColor.getC2() == 0xDDDD);
  BOOST_TEST_CHECK(aColor.getC3() == 0xFFFF);

  aColor.setToWhite();
  aColor.setChans("#aaaa");
  BOOST_TEST_CHECK(aColor.getC0() == 0xAAAA);
  BOOST_TEST_CHECK(aColor.getC1() == 0xFFFF);
  BOOST_TEST_CHECK(aColor.getC2() == 0xFFFF);
  BOOST_TEST_CHECK(aColor.getC3() == 0xFFFF);

  aColor.setToWhite();
  aColor.setChans("#aaa");
  BOOST_TEST_CHECK(aColor.getC0() == 0xFFFF);
  BOOST_TEST_CHECK(aColor.getC1() == 0xFFFF);
  BOOST_TEST_CHECK(aColor.getC2() == 0xFFFF);
  BOOST_TEST_CHECK(aColor.getC3() == 0xFFFF);

  // undefined chans set to min
  aColor.setToWhite();
  aColor.setChans("#bbbbccccdddd", true);
  BOOST_TEST_CHECK(aColor.getC0() == 0xBBBB);
  BOOST_TEST_CHECK(aColor.getC1() == 0xCCCC);
  BOOST_TEST_CHECK(aColor.getC2() == 0xDDDD);
  BOOST_TEST_CHECK(aColor.getC3() == 0x0000);

  aColor.setToWhite();
  aColor.setChans("#aaaa", true);
  BOOST_TEST_CHECK(aColor.getC0() == 0xAAAA);
  BOOST_TEST_CHECK(aColor.getC1() == 0x0000);
  BOOST_TEST_CHECK(aColor.getC2() == 0x0000);
  BOOST_TEST_CHECK(aColor.getC3() == 0x0000);

  aColor.setToWhite();
  aColor.setChans("#aaa", true);
  BOOST_TEST_CHECK(aColor.getC0() == 0x0000);
  BOOST_TEST_CHECK(aColor.getC1() == 0x0000);
  BOOST_TEST_CHECK(aColor.getC2() == 0x0000);
  BOOST_TEST_CHECK(aColor.getC3() == 0x0000);

 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chans_hex_64F) {

  mjr::color4c64F aColor("0");
  aColor.setToWhite();
  aColor.setChans("#aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd");
  BOOST_TEST_CHECK(aColor.getC0() == 0.66666666666, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC1() == 0.73333333333, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC2() == 0.80000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC3() == 0.86666666666, boost::test_tools::tolerance(0.00001));

  // undefined chans left alown
  aColor.setToWhite();
  aColor.setChans("#bbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd");
  BOOST_TEST_CHECK(aColor.getC0() == 0.73333333333, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC1() == 0.80000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC2() == 0.86666666666, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC3() == 1.00000000000, boost::test_tools::tolerance(0.00001));

  aColor.setToWhite();
  aColor.setChans("#aaaaaaaaaaaaaaaa");
  BOOST_TEST_CHECK(aColor.getC0() == 0.66666666666, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC1() == 1.00000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC2() == 1.00000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC3() == 1.00000000000, boost::test_tools::tolerance(0.00001));

  aColor.setToWhite();
  aColor.setChans("#aaa");
  BOOST_TEST_CHECK(aColor.getC0() == 1.00000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC1() == 1.00000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC2() == 1.00000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC3() == 1.00000000000, boost::test_tools::tolerance(0.00001));

  // undefined chans set to min
  aColor.setToWhite();
  aColor.setChans("#bbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd", true);
  BOOST_TEST_CHECK(aColor.getC0() == 0.73333333333, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC1() == 0.80000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC2() == 0.86666666666, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC3() == 0.00000000000, boost::test_tools::tolerance(0.00001));

  aColor.setToWhite();
  aColor.setChans("#aaaaaaaaaaaaaaaa", true);
  BOOST_TEST_CHECK(aColor.getC0() == 0.66666666666, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC1() == 0.00000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC2() == 0.00000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC3() == 0.00000000000, boost::test_tools::tolerance(0.00001));

  aColor.setToWhite();
  aColor.setChans("#aaa", true);
  BOOST_TEST_CHECK(aColor.getC0() == 0.00000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC1() == 0.00000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC2() == 0.00000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getC3() == 0.00000000000, boost::test_tools::tolerance(0.00001));

 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_8_RGB) {

  // For these tests we are mostly concerned with R, G, B, & A being
  // put in the right places.  Conversions between double/byte and
  // clrChanT are tested pretty well elsewhere.

  typedef mjr::colorTpl<mjr::colChanI8, 4, 1, 2, 3, 0> colorARGB8;
  colorARGB8 aColor;

  aColor.setToBlack();
  aColor.setRed(colorARGB8::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen(colorARGB8::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue(colorARGB8::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha(colorARGB8::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_byte(255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_byte(255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_byte(255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_byte(255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(1, 2, 3, 4);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 4);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(1, 2, 3);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_byte(1, 2, 3, 4);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 4);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_byte(1, 2, 3);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_dbl(0.25, 0.50, 0.75, 1.00);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0xFF);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0x3F);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0x7F);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0xBF);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_dbl(1.00, 0.25, 0.50);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0x00);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0xFF);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0x3F);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0x7F);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(colorARGB8::clrChanTup4(1, 2, 3, 4));

  BOOST_TEST_CHECK(aColor.getChan(0)      == 4);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(colorARGB8::clrChanTup3(1, 2, 3));

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 3);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_16_RGB) {

  typedef mjr::colorTpl<mjr::colChanI16, 4, 1, 2, 3, 0> colorARGB8;
  colorARGB8 aColor;

  aColor.setToBlack();
  aColor.setRed(colorARGB8::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen(colorARGB8::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue(colorARGB8::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha(colorARGB8::maxChanVal);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_byte(255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_byte(255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_byte(255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_byte(255);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == colorARGB8::maxChanVal);
  BOOST_TEST_CHECK(aColor.getChan(1)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(2)      == colorARGB8::minChanVal);
  BOOST_TEST_CHECK(aColor.getChan(3)      == colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(1, 2, 3, 4);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 4);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(1, 2, 3);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_byte(1, 2, 3, 4);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 1028);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 257);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 514);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 771);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_byte(1, 2, 3);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 257);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 514);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 771);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_dbl(0.25, 0.50, 0.75, 1.00);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0xFFFF);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0x3FFF);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0x7FFF);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0xBFFF);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_dbl(1.00, 0.25, 0.50);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0x0000);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0xFFFF);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0x3FFF);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0x7FFF);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(colorARGB8::clrChanTup4(1, 2, 3, 4));

  BOOST_TEST_CHECK(aColor.getChan(0)      == 4);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(colorARGB8::clrChanTup3(1, 2, 3));

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 2);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 3);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set8_fromLogPackIntARGB) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(aColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xDD);
  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA);

  aColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(aColor.getC1()    == 0xDD);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA); // From before

  eColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  BOOST_TEST_CHECK(eColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(eColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(eColor.getBlue()  == 0xBB);

  BOOST_TEST_CHECK(eColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(eColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(eColor.getC2()    == 0xBB);

  bColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(bColor.getC3()    == 0xAA);

  bColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(bColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC3()    == 0xAA); // From before

  fColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  BOOST_TEST_CHECK(fColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(fColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(fColor.getBlue()  == 0xBB);

  BOOST_TEST_CHECK(fColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(fColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(fColor.getC0()    == 0xBB);

  cColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  BOOST_TEST_CHECK(cColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(cColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(cColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(cColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(cColor.getC3()    == 0xAA);

  cColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  BOOST_TEST_CHECK(cColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(cColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(cColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(cColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(cColor.getC3()    == 0xAA); // From before

  dColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  BOOST_TEST_CHECK(dColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(dColor.getC3()    == 0xBB);
  BOOST_TEST_CHECK(dColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(dColor.getC1()    == 0xDD);
  BOOST_TEST_CHECK(dColor.getC0()    == 0xAA);

  dColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  BOOST_TEST_CHECK(dColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(dColor.getC3()    == 0xDD);
  BOOST_TEST_CHECK(dColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(dColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(dColor.getC0()    == 0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set8_fromLogPackIntRGBA) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(aColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xDD);
  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA);

  aColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(aColor.getC1()    == 0xDD);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA); // From before

  eColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  BOOST_TEST_CHECK(eColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(eColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(eColor.getBlue()  == 0xBB);

  BOOST_TEST_CHECK(eColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(eColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(eColor.getC2()    == 0xBB);

  bColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(bColor.getC3()    == 0xAA);

  bColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(bColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC3()    == 0xAA); // From before

  fColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  BOOST_TEST_CHECK(fColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(fColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(fColor.getBlue()  == 0xBB);

  BOOST_TEST_CHECK(fColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(fColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(fColor.getC0()    == 0xBB);

  cColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  BOOST_TEST_CHECK(cColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(cColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(cColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(cColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(cColor.getC3()    == 0xAA);

  cColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  BOOST_TEST_CHECK(cColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(cColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(cColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(cColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(cColor.getC3()    == 0xAA); // From before

  dColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  BOOST_TEST_CHECK(dColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(dColor.getC3()    == 0xBB);
  BOOST_TEST_CHECK(dColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(dColor.getC1()    == 0xDD);
  BOOST_TEST_CHECK(dColor.getC0()    == 0xAA);

  dColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  BOOST_TEST_CHECK(dColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(dColor.getC3()    == 0xDD);
  BOOST_TEST_CHECK(dColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(dColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(dColor.getC0()    == 0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set8_fromLogPackIntABGR) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(aColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xDD);
  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA);

  aColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(aColor.getC1()    == 0xDD);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA); // From before

  eColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  BOOST_TEST_CHECK(eColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(eColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(eColor.getBlue()  == 0xBB);

  BOOST_TEST_CHECK(eColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(eColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(eColor.getC2()    == 0xBB);

  bColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(bColor.getC3()    == 0xAA);

  bColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(bColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC3()    == 0xAA); // From before

  fColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  BOOST_TEST_CHECK(fColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(fColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(fColor.getBlue()  == 0xBB);

  BOOST_TEST_CHECK(fColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(fColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(fColor.getC0()    == 0xBB);

  cColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  BOOST_TEST_CHECK(cColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(cColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(cColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(cColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(cColor.getC3()    == 0xAA);

  cColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  BOOST_TEST_CHECK(cColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(cColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(cColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(cColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(cColor.getC3()    == 0xAA); // From before

  dColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  BOOST_TEST_CHECK(dColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(dColor.getC3()    == 0xBB);
  BOOST_TEST_CHECK(dColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(dColor.getC1()    == 0xDD);
  BOOST_TEST_CHECK(dColor.getC0()    == 0xAA);

  dColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  BOOST_TEST_CHECK(dColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(dColor.getC3()    == 0xDD);
  BOOST_TEST_CHECK(dColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(dColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(dColor.getC0()    == 0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set8_fromLogPackIntABRG) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(aColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xDD);
  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA);

  aColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(aColor.getC1()    == 0xDD);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA); // From before

  eColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  BOOST_TEST_CHECK(eColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(eColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(eColor.getBlue()  == 0xBB);

  BOOST_TEST_CHECK(eColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(eColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(eColor.getC2()    == 0xBB);

  bColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(bColor.getC3()    == 0xAA);

  bColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(bColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC3()    == 0xAA); // From before

  fColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  BOOST_TEST_CHECK(fColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(fColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(fColor.getBlue()  == 0xBB);

  BOOST_TEST_CHECK(fColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(fColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(fColor.getC0()    == 0xBB);

  cColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  BOOST_TEST_CHECK(cColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(cColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(cColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(cColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(cColor.getC3()    == 0xAA);

  cColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  BOOST_TEST_CHECK(cColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(cColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(cColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(cColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(cColor.getC3()    == 0xAA); // From before

  dColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  BOOST_TEST_CHECK(dColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(dColor.getC3()    == 0xBB);
  BOOST_TEST_CHECK(dColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(dColor.getC1()    == 0xDD);
  BOOST_TEST_CHECK(dColor.getC0()    == 0xAA);

  dColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  BOOST_TEST_CHECK(dColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(dColor.getC3()    == 0xDD);
  BOOST_TEST_CHECK(dColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(dColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(dColor.getC0()    == 0xAA); // From before
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set8_fromLogPackIntBGRA) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorBGRA8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(aColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xDD);
  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA);

  aColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(aColor.getC1()    == 0xDD);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA); // From before

  eColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  BOOST_TEST_CHECK(eColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(eColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(eColor.getBlue()  == 0xBB);

  BOOST_TEST_CHECK(eColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(eColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(eColor.getC2()    == 0xBB);

  bColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(bColor.getC3()    == 0xAA);

  bColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(bColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC3()    == 0xAA); // From before

  fColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  BOOST_TEST_CHECK(fColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(fColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(fColor.getBlue()  == 0xBB);

  BOOST_TEST_CHECK(fColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(fColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(fColor.getC0()    == 0xBB);

  cColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  BOOST_TEST_CHECK(cColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(cColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(cColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(cColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(cColor.getC3()    == 0xAA);

  cColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  BOOST_TEST_CHECK(cColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(cColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(cColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(cColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(cColor.getC3()    == 0xAA); // From before

  dColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  BOOST_TEST_CHECK(dColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xDD);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xAA);

  BOOST_TEST_CHECK(dColor.getC2()    == 0xBB);
  BOOST_TEST_CHECK(dColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(dColor.getC0()    == 0xDD);
  BOOST_TEST_CHECK(dColor.getC3()    == 0xAA);

  dColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  BOOST_TEST_CHECK(dColor.getRed()   == 0xDD);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xBB);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xAA); // From before

  BOOST_TEST_CHECK(dColor.getC2()    == 0xDD);
  BOOST_TEST_CHECK(dColor.getC1()    == 0xCC);
  BOOST_TEST_CHECK(dColor.getC0()    == 0xBB);
  BOOST_TEST_CHECK(dColor.getC3()    == 0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set16_fromLogPackIntARGB) {

  // We really just need to make sure the scale works for 16bit -- i.e. that the bytes of the integer are truely inturprted by set*_byte() members.

  mjr::colorRGBA16b bColor;
  mjr::colorRGB16b  eColor;

  bColor.setRGBAfromLogPackIntARGB(0xFF00FF80);

  BOOST_TEST_CHECK(bColor.getRed()   == mjr::colorRGBA16b::minChanVal);
  BOOST_TEST_CHECK(bColor.getGreen() == mjr::colorRGBA16b::maxChanVal);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x8080);
  BOOST_TEST_CHECK(bColor.getAlpha() == mjr::colorRGBA16b::maxChanVal);

  BOOST_TEST_CHECK(bColor.getC0()    == mjr::colorRGBA16b::minChanVal);
  BOOST_TEST_CHECK(bColor.getC1()    == mjr::colorRGBA16b::maxChanVal);
  BOOST_TEST_CHECK(bColor.getC2()    == 0x8080);
  BOOST_TEST_CHECK(bColor.getC3()    == mjr::colorRGBA16b::maxChanVal);

  bColor.setRGBfromLogPackIntARGB(0x00FF00FF);

  BOOST_TEST_CHECK(bColor.getRed()   == mjr::colorRGBA16b::maxChanVal);
  BOOST_TEST_CHECK(bColor.getGreen() == mjr::colorRGBA16b::minChanVal);
  BOOST_TEST_CHECK(bColor.getBlue()  == mjr::colorRGBA16b::maxChanVal);
  BOOST_TEST_CHECK(bColor.getAlpha() == mjr::colorRGBA16b::maxChanVal); // From before

  BOOST_TEST_CHECK(bColor.getC0()    == mjr::colorRGBA16b::maxChanVal);
  BOOST_TEST_CHECK(bColor.getC1()    == mjr::colorRGBA16b::minChanVal);
  BOOST_TEST_CHECK(bColor.getC2()    == mjr::colorRGBA16b::maxChanVal);
  BOOST_TEST_CHECK(bColor.getC3()    == mjr::colorRGBA16b::maxChanVal); // From before

  eColor.setRGBfromLogPackIntARGB(0x00FF00FF);

  BOOST_TEST_CHECK(eColor.getRed()   == mjr::colorRGBA16b::maxChanVal);
  BOOST_TEST_CHECK(eColor.getGreen() == mjr::colorRGBA16b::minChanVal);
  BOOST_TEST_CHECK(eColor.getBlue()  == mjr::colorRGBA16b::maxChanVal);

  BOOST_TEST_CHECK(eColor.getC0()    == mjr::colorRGBA16b::maxChanVal);
  BOOST_TEST_CHECK(eColor.getC1()    == mjr::colorRGBA16b::minChanVal);
  BOOST_TEST_CHECK(eColor.getC2()    == mjr::colorRGBA16b::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set8_saved_fromLogPackIntARGB) {

  // Make sure channels that should not be changed are not.

  mjr::colorRGBA8b bColor;
  mjr::color5c8b   cColor;

  bColor.setToWhite();
  bColor.setRGBfromLogPackIntARGB(0x00000000);

  BOOST_TEST_CHECK(bColor.getRed()   == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(bColor.getGreen() == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(bColor.getBlue()  == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(bColor.getAlpha() == mjr::colorRGBA8b::maxChanVal);

  bColor.setToBlack();
  bColor.setRGBfromLogPackIntARGB(0xFFFFFFFF);

  BOOST_TEST_CHECK(bColor.getRed()   == mjr::colorRGBA8b::maxChanVal);
  BOOST_TEST_CHECK(bColor.getGreen() == mjr::colorRGBA8b::maxChanVal);
  BOOST_TEST_CHECK(bColor.getBlue()  == mjr::colorRGBA8b::maxChanVal);
  BOOST_TEST_CHECK(bColor.getAlpha() == mjr::colorRGBA8b::minChanVal);

  cColor.setToWhite();
  cColor.setRGBAfromLogPackIntARGB(0x00000000);

  BOOST_TEST_CHECK(cColor.getRed()   == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(cColor.getGreen() == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(cColor.getBlue()  == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(cColor.getAlpha() == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(cColor.getChan(4) == mjr::colorRGBA8b::maxChanVal);

  cColor.setToBlack();
  cColor.setRGBAfromLogPackIntARGB(0xFFFFFFFF);

  BOOST_TEST_CHECK(cColor.getRed()   == mjr::colorRGBA8b::maxChanVal);
  BOOST_TEST_CHECK(cColor.getGreen() == mjr::colorRGBA8b::maxChanVal);
  BOOST_TEST_CHECK(cColor.getBlue()  == mjr::colorRGBA8b::maxChanVal);
  BOOST_TEST_CHECK(cColor.getAlpha() == mjr::colorRGBA8b::maxChanVal);
  BOOST_TEST_CHECK(cColor.getChan(4) == mjr::colorRGBA8b::minChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(setRGBcmpGreyTGA16bit) {

  mjr::colorRGBA8b aColor;
  mjr::colorRGB8b  bColor;

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA16bit(0x0000);

  BOOST_TEST_CHECK(bColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(bColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x00);

  BOOST_TEST_CHECK(bColor.getC0()    == 0x00);
  BOOST_TEST_CHECK(bColor.getC1()    == 0x00);
  BOOST_TEST_CHECK(bColor.getC2()    == 0x00);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA16bit(0xFFFF);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x00);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xFF);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xFF);
  BOOST_TEST_CHECK(bColor.getC2()    == 0x00);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA16bit(0xAABB);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xAA);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xBB);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x00);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xAA);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC2()    == 0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA16bit(0x0000);

  BOOST_TEST_CHECK(bColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(bColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x00);

  BOOST_TEST_CHECK(bColor.getC0()    == 0x00);
  BOOST_TEST_CHECK(bColor.getC1()    == 0x00);
  BOOST_TEST_CHECK(bColor.getC2()    == 0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA16bit(0xFFFF);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x00);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xFF);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xFF);
  BOOST_TEST_CHECK(bColor.getC2()    == 0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA16bit(0xAABB);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xAA);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xBB);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x00);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xAA);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC2()    == 0x00);

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA16bit(0x0000);

  BOOST_TEST_CHECK(aColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(aColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0x00);

  BOOST_TEST_CHECK(aColor.getC0()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC1()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC2()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC3()    == 0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA16bit(0xFFFF);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0x00);

  BOOST_TEST_CHECK(aColor.getC0()    == 0xFF);
  BOOST_TEST_CHECK(aColor.getC1()    == 0xFF);
  BOOST_TEST_CHECK(aColor.getC2()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC3()    == 0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA16bit(0xAABB);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xAA);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xBB);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0x00);

  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA);
  BOOST_TEST_CHECK(aColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC2()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC3()    == 0x00);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA16bit(0x0000);

  BOOST_TEST_CHECK(aColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(aColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xFF);

  BOOST_TEST_CHECK(aColor.getC0()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC1()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC2()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA16bit(0xFFFF);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xFF);

  BOOST_TEST_CHECK(aColor.getC0()    == 0xFF);
  BOOST_TEST_CHECK(aColor.getC1()    == 0xFF);
  BOOST_TEST_CHECK(aColor.getC2()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA16bit(0xAABB);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xAA);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xBB);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xFF);

  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA);
  BOOST_TEST_CHECK(aColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC2()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xFF);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(setRGBcmpGreyTGA24bit) {

  mjr::colorRGBA8b aColor;
  mjr::colorRGB8b  bColor;

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA24bit(0x00000000);

  BOOST_TEST_CHECK(bColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(bColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x00);

  BOOST_TEST_CHECK(bColor.getC0()    == 0x00);
  BOOST_TEST_CHECK(bColor.getC1()    == 0x00);
  BOOST_TEST_CHECK(bColor.getC2()    == 0x00);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xFF);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xFF);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xFF);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xFF);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xAA);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xBB);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xCC);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xAA);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xCC);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA24bit(0x00000000);

  BOOST_TEST_CHECK(bColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(bColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x00);

  BOOST_TEST_CHECK(bColor.getC0()    == 0x00);
  BOOST_TEST_CHECK(bColor.getC1()    == 0x00);
  BOOST_TEST_CHECK(bColor.getC2()    == 0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xFF);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xFF);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xFF);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xFF);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  BOOST_TEST_CHECK(bColor.getRed()   == 0xAA);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xBB);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xCC);

  BOOST_TEST_CHECK(bColor.getC0()    == 0xAA);
  BOOST_TEST_CHECK(bColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(bColor.getC2()    == 0xCC);

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA24bit(0x00000000);

  BOOST_TEST_CHECK(aColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(aColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0x00);

  BOOST_TEST_CHECK(aColor.getC0()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC1()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC2()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC3()    == 0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xFF);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0x00);

  BOOST_TEST_CHECK(aColor.getC0()    == 0xFF);
  BOOST_TEST_CHECK(aColor.getC1()    == 0xFF);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xFF);
  BOOST_TEST_CHECK(aColor.getC3()    == 0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xAA);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xBB);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xCC);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0x00);

  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA);
  BOOST_TEST_CHECK(aColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0x00);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA24bit(0x00000000);

  BOOST_TEST_CHECK(aColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(aColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xFF);

  BOOST_TEST_CHECK(aColor.getC0()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC1()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC2()    == 0x00);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xFF);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xFF);

  BOOST_TEST_CHECK(aColor.getC0()    == 0xFF);
  BOOST_TEST_CHECK(aColor.getC1()    == 0xFF);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xFF);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xAA);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xBB);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xCC);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xFF);

  BOOST_TEST_CHECK(aColor.getC0()    == 0xAA);
  BOOST_TEST_CHECK(aColor.getC1()    == 0xBB);
  BOOST_TEST_CHECK(aColor.getC2()    == 0xCC);
  BOOST_TEST_CHECK(aColor.getC3()    == 0xFF);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_logic_cover) {

  mjr::colorRGBA8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorRGBA8b cColor;

  aColor.setRGBAfromLogPackIntRGBA(0xAABBCCDD);
  bColor.setRGBAfromLogPackIntRGBA(0x11223344);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xAA);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xBB);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xCC);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xDD);

  BOOST_TEST_CHECK(bColor.getRed()   == 0x11);
  BOOST_TEST_CHECK(bColor.getGreen() == 0x22);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x33);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0x44);

  cColor = aColor;
  cColor.tfrmNot();
  BOOST_TEST_CHECK(cColor.getRed()   == 0x55);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x44);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x33);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x22);

  cColor = aColor;
  cColor.tfrmOr(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xBB);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xFF);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xDD);

  cColor = aColor;
  cColor.tfrmNor(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0x44);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x44);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x22);

  cColor = aColor;
  cColor.tfrmAnd(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x22);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x44);

  cColor = aColor;
  cColor.tfrmNand(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xDD);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xFF);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xBB);

  cColor = aColor;
  cColor.tfrmXor(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xBB);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x99);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xFF);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x99);

  cColor = aColor;
  cColor.tfrmNxor(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0x44);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x66);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x66);

//  MJR TODO NOTE BOOST_AUTO_TEST_CASE: Add tfrmShiftL & tfrmShiftR

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_logic_noCover) {

  mjr::colorRGBA64b aColor;
  mjr::colorRGBA64b bColor;
  mjr::colorRGBA64b cColor;

  aColor.setChansRGBA(0xAAAAAAAAAAAAAAAAu, 0xBBBBBBBBBBBBBBBBu, 0xCCCCCCCCCCCCCCCCu, 0xDDDDDDDDDDDDDDDDu);
  bColor.setChansRGBA(0x1111111111111111u, 0x2222222222222222u, 0x3333333333333333u, 0x4444444444444444u);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xAAAAAAAAAAAAAAAAu);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xBBBBBBBBBBBBBBBBu);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xCCCCCCCCCCCCCCCCu);
  BOOST_TEST_CHECK(aColor.getAlpha() == 0xDDDDDDDDDDDDDDDDu);

  BOOST_TEST_CHECK(bColor.getRed()   == 0x1111111111111111u);
  BOOST_TEST_CHECK(bColor.getGreen() == 0x2222222222222222u);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0x3333333333333333u);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0x4444444444444444u);

  cColor = aColor;
  cColor.tfrmNot();
  BOOST_TEST_CHECK(cColor.getRed()   == 0x5555555555555555u);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x4444444444444444u);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x3333333333333333u);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x2222222222222222u);

  cColor = aColor;
  cColor.tfrmOr(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xBBBBBBBBBBBBBBBBu);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xBBBBBBBBBBBBBBBBu);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xFFFFFFFFFFFFFFFFu);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xDDDDDDDDDDDDDDDDu);

  cColor = aColor;
  cColor.tfrmNor(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0x4444444444444444u);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x4444444444444444u);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x0000000000000000u);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x2222222222222222u);

  cColor = aColor;
  cColor.tfrmAnd(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0x0000000000000000u);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x2222222222222222u);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x0000000000000000u);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x4444444444444444u);

  cColor = aColor;
  cColor.tfrmNand(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFFFFFFFFFFFFFFFFu);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xDDDDDDDDDDDDDDDDu);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xFFFFFFFFFFFFFFFFu);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xBBBBBBBBBBBBBBBBu);

  cColor = aColor;
  cColor.tfrmXor(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xBBBBBBBBBBBBBBBBu);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x9999999999999999u);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xFFFFFFFFFFFFFFFFu);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x9999999999999999u);

  cColor = aColor;
  cColor.tfrmNxor(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0x4444444444444444u);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x6666666666666666u);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x0000000000000000u);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x6666666666666666u);


//  MJR TODO NOTE BOOST_AUTO_TEST_CASE: Add tfrmShiftL & tfrmShiftR
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_arith) {

  mjr::colorRGB8b aColor;
  mjr::colorRGB8b bColor;
  mjr::colorRGB8b dColor;
  mjr::colorRGB8b cColor;

  aColor.setRGBfromLogPackIntARGB(0xFF00FF);
  bColor.setRGBfromLogPackIntARGB(0x00FFFF);
  dColor.setRGBfromLogPackIntARGB(0x0100FF);

  BOOST_TEST_CHECK(aColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(aColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0xFF);

  BOOST_TEST_CHECK(bColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(bColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0xFF);

  BOOST_TEST_CHECK(dColor.getRed()   == 0x01);
  BOOST_TEST_CHECK(dColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xFF);

  cColor=aColor;
  cColor.tfrmMix(0.0, bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=aColor;
  cColor.tfrmMix(0.5, bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0x7F);
  BOOST_TEST_CHECK(cColor.getC1() == 0x7F);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=aColor;
  cColor.tfrmMix(1.0, bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0x00);
  BOOST_TEST_CHECK(cColor.getC1() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor = aColor;
  cColor.tfrmInvert();
  BOOST_TEST_CHECK(cColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x00);

  cColor = aColor;
  cColor.tfrmAdd(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xFE); // Overflow wrap

  cColor = aColor;
  cColor.tfrmAddClamp(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xFF); // Overflow clamp

  cColor = aColor;
  cColor.tfrmMult(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x01); // Overflow wrap

  cColor = aColor;
  cColor.tfrmMultClamp(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0x00);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0xFF); // Overflow clamp

  cColor = aColor;
  cColor.tfrmDiv(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFF); // NOOP as bot=0
  BOOST_TEST_CHECK(cColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x01);

  cColor = aColor;
  cColor.tfrmMod(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFF); // NOOP as bot=0
  BOOST_TEST_CHECK(cColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x00);

  cColor = aColor;
  cColor.tfrmDiff(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x01); // Underflow wrap
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x00);

  cColor = aColor;
  cColor.tfrmDiffClamp(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x00); // Overflow clamp
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x00);

  cColor = aColor;
  cColor.tfrmAbsDiff(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(cColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x00);

  cColor = aColor;
  cColor.tfrmSqDiff(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0x01); // Overflow wrap
  BOOST_TEST_CHECK(cColor.getGreen() == 0x01); // Overflow wrap
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x00);

  cColor = aColor;
  cColor.tfrmNegDiffClamp(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0x00); // Overflow clamp
  BOOST_TEST_CHECK(cColor.getGreen() == 0xFF);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x00);

  cColor = aColor;
  cColor.tfrmAddDivClamp(bColor, dColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x02);

  cColor = aColor;
  cColor.tfrmSignDiff(bColor);
  BOOST_TEST_CHECK(cColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(cColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(cColor.getBlue()  == 0x7F);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_arith_FLT) {

  mjr::colorRGB32F aColor;
  mjr::colorRGB32F bColor;
  mjr::colorRGB32F dColor;
  mjr::colorRGB32F cColor;

  aColor.setChansRGB(2.0, 0.0, 2.0);
  bColor.setChansRGB(0.0, 2.0, 2.0);
  dColor.setChansRGB(0.0, 2.0, 2.0);

  cColor=aColor;
  cColor.tfrmMix(0.0, bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=aColor;
  cColor.tfrmMix(0.5, bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 1.0);
  BOOST_TEST_CHECK(cColor.getC1() == 1.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=aColor;
  cColor.tfrmMix(1.0, bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0.0);
  BOOST_TEST_CHECK(cColor.getC1() == 2.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor = aColor;
  cColor.tfrmInvert();
  BOOST_TEST_CHECK(cColor.getC0() == -1.0);
  BOOST_TEST_CHECK(cColor.getC1() ==  1.0);
  BOOST_TEST_CHECK(cColor.getC2() == -1.0);

  cColor = aColor;
  cColor.tfrmAdd(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  BOOST_TEST_CHECK(cColor.getC1() == 2.0);
  BOOST_TEST_CHECK(cColor.getC2() == 4.0);

  cColor = aColor;
  cColor.tfrmAddClamp(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 1.0); // clamped to maxChanVal
  BOOST_TEST_CHECK(cColor.getC1() == 1.0); // clamped to maxChanVal
  BOOST_TEST_CHECK(cColor.getC2() == 1.0); // clamped to maxChanVal

  cColor = aColor;
  cColor.tfrmMult(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 4.0);

  cColor = aColor;
  cColor.tfrmMultClamp(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 1.0); // clamped to maxChanVal

  cColor = aColor;
  cColor.tfrmDiv(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0); // NOOP as bot=0
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 1.0);

  cColor = aColor;
  cColor.tfrmMod(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0); // NOOP as bot=0
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 0.0);

  cColor = aColor;
  cColor.tfrmDiff(bColor);
  BOOST_TEST_CHECK(cColor.getC0() ==  2.0);
  BOOST_TEST_CHECK(cColor.getC1() == -2.0);
  BOOST_TEST_CHECK(cColor.getC2() ==  0.0);

  cColor = aColor;
  cColor.tfrmDiffClamp(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0); // Clamp on bottom only
  BOOST_TEST_CHECK(cColor.getC1() == 0.0); //clamped to minChanVal
  BOOST_TEST_CHECK(cColor.getC2() == 0.0);

  cColor = aColor;
  cColor.tfrmAbsDiff(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  BOOST_TEST_CHECK(cColor.getC1() == 2.0);
  BOOST_TEST_CHECK(cColor.getC2() == 0.0);

  cColor = aColor;
  cColor.tfrmSqDiff(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 4.0);
  BOOST_TEST_CHECK(cColor.getC1() == 4.0);
  BOOST_TEST_CHECK(cColor.getC2() == 0.0);

  cColor = aColor;
  cColor.tfrmNegDiffClamp(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0.0); // Underflow clamp bottom
  BOOST_TEST_CHECK(cColor.getC1() == 2.0);
  BOOST_TEST_CHECK(cColor.getC2() == 0.0);

  cColor = aColor;
  cColor.tfrmAddDivClamp(bColor, dColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0); // NOOP bot=0
  BOOST_TEST_CHECK(cColor.getC1() == 1.0);
  BOOST_TEST_CHECK(cColor.getC2() == 1.0); // Overflow clamp at top

  cColor = aColor;
  cColor.tfrmSignDiff(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 1.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 0.5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(isBlack_and_isBlackRGB) {

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

  BOOST_TEST_CHECK(aColor.isBlack()  == true);
  BOOST_TEST_CHECK(bColor.isBlack()  == true);
  BOOST_TEST_CHECK(cColor.isBlack()  == true);
  BOOST_TEST_CHECK(dColor.isBlack()  == true);
  BOOST_TEST_CHECK(fColor.isBlack()  == true);
  BOOST_TEST_CHECK(gColor.isBlack()  == true);

  BOOST_TEST_CHECK(aColor.isBlackRGB()  == true);
  BOOST_TEST_CHECK(bColor.isBlackRGB()  == true);
  BOOST_TEST_CHECK(cColor.isBlackRGB()  == true);
  BOOST_TEST_CHECK(dColor.isBlackRGB()  == true);
  BOOST_TEST_CHECK(fColor.isBlackRGB()  == true);
  BOOST_TEST_CHECK(gColor.isBlackRGB()  == true);

  aColor.setChanToMax(0);
  bColor.setChanToMax(0);
  cColor.setChanToMax(0);
  dColor.setChanToMax(0);
  fColor.setChanToMax(0);
  gColor.setChanToMax(0);

  BOOST_TEST_CHECK(aColor.isBlack()  == false);
  BOOST_TEST_CHECK(bColor.isBlack()  == false);
  BOOST_TEST_CHECK(cColor.isBlack()  == false);
  BOOST_TEST_CHECK(dColor.isBlack()  == false);
  BOOST_TEST_CHECK(fColor.isBlack()  == false);
  BOOST_TEST_CHECK(gColor.isBlack()  == false);

  BOOST_TEST_CHECK(aColor.isBlackRGB()  == false);
  BOOST_TEST_CHECK(bColor.isBlackRGB()  == false);
  BOOST_TEST_CHECK(cColor.isBlackRGB()  == false);
  BOOST_TEST_CHECK(dColor.isBlackRGB()  == false);
  BOOST_TEST_CHECK(fColor.isBlackRGB()  == false);
  BOOST_TEST_CHECK(gColor.isBlackRGB()  == false);

  aColor.setToWhite();
  bColor.setToWhite();
  cColor.setToWhite();
  dColor.setToWhite();
  fColor.setToWhite();
  gColor.setToWhite();

  BOOST_TEST_CHECK(aColor.isBlack()  == false);
  BOOST_TEST_CHECK(bColor.isBlack()  == false);
  BOOST_TEST_CHECK(cColor.isBlack()  == false);
  BOOST_TEST_CHECK(dColor.isBlack()  == false);
  BOOST_TEST_CHECK(fColor.isBlack()  == false);
  BOOST_TEST_CHECK(gColor.isBlack()  == false);

  BOOST_TEST_CHECK(aColor.isBlackRGB()  == false);
  BOOST_TEST_CHECK(bColor.isBlackRGB()  == false);
  BOOST_TEST_CHECK(cColor.isBlackRGB()  == false);
  BOOST_TEST_CHECK(dColor.isBlackRGB()  == false);
  BOOST_TEST_CHECK(fColor.isBlackRGB()  == false);
  BOOST_TEST_CHECK(gColor.isBlackRGB()  == false);

  bColor.setChansRGBA(0, 0, 0, 1);
  fColor.setChansRGBA(0, 0, 0, 1);

  BOOST_TEST_CHECK(bColor.isBlack()  == false);
  BOOST_TEST_CHECK(fColor.isBlack()  == false);

  BOOST_TEST_CHECK(bColor.isBlackRGB()  == true);
  BOOST_TEST_CHECK(fColor.isBlackRGB()  == true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(isEqual_and_isEqualRGB_and_isNotEqual) {

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

  BOOST_TEST_CHECK(aLcolor.isEqual(aRcolor)  == true);
  BOOST_TEST_CHECK(bLcolor.isEqual(bRcolor)  == true);
  BOOST_TEST_CHECK(cLcolor.isEqual(cRcolor)  == true);
  BOOST_TEST_CHECK(dLcolor.isEqual(dRcolor)  == true);
  BOOST_TEST_CHECK(fLcolor.isEqual(fRcolor)  == true);
  BOOST_TEST_CHECK(gLcolor.isEqual(gRcolor)  == true);

  BOOST_TEST_CHECK(aLcolor.isNotEqual(aRcolor)  == false);
  BOOST_TEST_CHECK(bLcolor.isNotEqual(bRcolor)  == false);
  BOOST_TEST_CHECK(cLcolor.isNotEqual(cRcolor)  == false);
  BOOST_TEST_CHECK(dLcolor.isNotEqual(dRcolor)  == false);
  BOOST_TEST_CHECK(fLcolor.isNotEqual(fRcolor)  == false);
  BOOST_TEST_CHECK(gLcolor.isNotEqual(gRcolor)  == false);

  BOOST_TEST_CHECK(aLcolor.isEqualRGB(aRcolor)  == true);
  BOOST_TEST_CHECK(bLcolor.isEqualRGB(bRcolor)  == true);
  BOOST_TEST_CHECK(cLcolor.isEqualRGB(cRcolor)  == true);
  BOOST_TEST_CHECK(dLcolor.isEqualRGB(dRcolor)  == true);
  BOOST_TEST_CHECK(fLcolor.isEqualRGB(fRcolor)  == true);
  BOOST_TEST_CHECK(gLcolor.isEqualRGB(gRcolor)  == true);

  aLcolor.setChanToMax(0);
  bLcolor.setChanToMax(0);
  cLcolor.setChanToMax(0);
  dLcolor.setChanToMax(0);
  fLcolor.setChanToMax(0);
  gLcolor.setChanToMax(0);

  BOOST_TEST_CHECK(aLcolor.isEqual(aRcolor)  == false);
  BOOST_TEST_CHECK(bLcolor.isEqual(bRcolor)  == false);
  BOOST_TEST_CHECK(cLcolor.isEqual(cRcolor)  == false);
  BOOST_TEST_CHECK(dLcolor.isEqual(dRcolor)  == false);
  BOOST_TEST_CHECK(fLcolor.isEqual(fRcolor)  == false);
  BOOST_TEST_CHECK(gLcolor.isEqual(gRcolor)  == false);

  BOOST_TEST_CHECK(aLcolor.isNotEqual(aRcolor)  == true);
  BOOST_TEST_CHECK(bLcolor.isNotEqual(bRcolor)  == true);
  BOOST_TEST_CHECK(cLcolor.isNotEqual(cRcolor)  == true);
  BOOST_TEST_CHECK(dLcolor.isNotEqual(dRcolor)  == true);
  BOOST_TEST_CHECK(fLcolor.isNotEqual(fRcolor)  == true);
  BOOST_TEST_CHECK(gLcolor.isNotEqual(gRcolor)  == true);

  BOOST_TEST_CHECK(aLcolor.isEqualRGB(aRcolor)  == false);
  BOOST_TEST_CHECK(bLcolor.isEqualRGB(bRcolor)  == false);
  BOOST_TEST_CHECK(cLcolor.isEqualRGB(cRcolor)  == false);
  BOOST_TEST_CHECK(dLcolor.isEqualRGB(dRcolor)  == false);
  BOOST_TEST_CHECK(fLcolor.isEqualRGB(fRcolor)  == false);
  BOOST_TEST_CHECK(gLcolor.isEqualRGB(gRcolor)  == false);

  aRcolor.setChanToMax(0);
  bRcolor.setChanToMax(0);
  cRcolor.setChanToMax(0);
  dRcolor.setChanToMax(0);
  fRcolor.setChanToMax(0);
  gRcolor.setChanToMax(0);

  BOOST_TEST_CHECK(aLcolor.isEqual(aRcolor)  == true);
  BOOST_TEST_CHECK(bLcolor.isEqual(bRcolor)  == true);
  BOOST_TEST_CHECK(cLcolor.isEqual(cRcolor)  == true);
  BOOST_TEST_CHECK(dLcolor.isEqual(dRcolor)  == true);
  BOOST_TEST_CHECK(fLcolor.isEqual(fRcolor)  == true);
  BOOST_TEST_CHECK(gLcolor.isEqual(gRcolor)  == true);

  BOOST_TEST_CHECK(aLcolor.isNotEqual(aRcolor)  == false);
  BOOST_TEST_CHECK(bLcolor.isNotEqual(bRcolor)  == false);
  BOOST_TEST_CHECK(cLcolor.isNotEqual(cRcolor)  == false);
  BOOST_TEST_CHECK(dLcolor.isNotEqual(dRcolor)  == false);
  BOOST_TEST_CHECK(fLcolor.isNotEqual(fRcolor)  == false);
  BOOST_TEST_CHECK(gLcolor.isNotEqual(gRcolor)  == false);

  BOOST_TEST_CHECK(aLcolor.isEqualRGB(aRcolor)  == true);
  BOOST_TEST_CHECK(bLcolor.isEqualRGB(bRcolor)  == true);
  BOOST_TEST_CHECK(cLcolor.isEqualRGB(cRcolor)  == true);
  BOOST_TEST_CHECK(dLcolor.isEqualRGB(dRcolor)  == true);
  BOOST_TEST_CHECK(fLcolor.isEqualRGB(fRcolor)  == true);
  BOOST_TEST_CHECK(gLcolor.isEqualRGB(gRcolor)  == true);

  aLcolor.setToWhite();
  bLcolor.setToWhite();
  cLcolor.setToWhite();
  dLcolor.setToWhite();
  fLcolor.setToWhite();
  gLcolor.setToWhite();

  BOOST_TEST_CHECK(aLcolor.isEqual(aRcolor)  == false);
  BOOST_TEST_CHECK(bLcolor.isEqual(bRcolor)  == false);
  BOOST_TEST_CHECK(cLcolor.isEqual(cRcolor)  == false);
  BOOST_TEST_CHECK(dLcolor.isEqual(dRcolor)  == false);
  BOOST_TEST_CHECK(fLcolor.isEqual(fRcolor)  == false);
  BOOST_TEST_CHECK(gLcolor.isEqual(gRcolor)  == false);

  BOOST_TEST_CHECK(aLcolor.isNotEqual(aRcolor)  == true);
  BOOST_TEST_CHECK(bLcolor.isNotEqual(bRcolor)  == true);
  BOOST_TEST_CHECK(cLcolor.isNotEqual(cRcolor)  == true);
  BOOST_TEST_CHECK(dLcolor.isNotEqual(dRcolor)  == true);
  BOOST_TEST_CHECK(fLcolor.isNotEqual(fRcolor)  == true);
  BOOST_TEST_CHECK(gLcolor.isNotEqual(gRcolor)  == true);

  BOOST_TEST_CHECK(aLcolor.isEqualRGB(aRcolor)  == false);
  BOOST_TEST_CHECK(bLcolor.isEqualRGB(bRcolor)  == false);
  BOOST_TEST_CHECK(cLcolor.isEqualRGB(cRcolor)  == false);
  BOOST_TEST_CHECK(dLcolor.isEqualRGB(dRcolor)  == false);
  BOOST_TEST_CHECK(fLcolor.isEqualRGB(fRcolor)  == false);
  BOOST_TEST_CHECK(gLcolor.isEqualRGB(gRcolor)  == false);

  bLcolor.setChansRGBA(1, 2, 3, 4);
  fLcolor.setChansRGBA(1, 2, 3, 4);

  bRcolor.setChansRGBA(1, 2, 3, 5);
  fRcolor.setChansRGBA(1, 2, 3, 5);

  BOOST_TEST_CHECK(bLcolor.isEqual(bRcolor)  == false);
  BOOST_TEST_CHECK(fLcolor.isEqual(fRcolor)  == false);

  BOOST_TEST_CHECK(bLcolor.isEqualRGB(bRcolor)  == true);
  BOOST_TEST_CHECK(fLcolor.isEqualRGB(fRcolor)  == true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(setColorCons) {

  mjr::colorRGBA8b   aColor; // integer color with imperfect mask
  mjr::colorRGBA64b  bColor; // integer color without mask
  mjr::colorRGBA32F  cColor; // floating point color with mask
  mjr::colorRGBA64F  dColor; // floating point color without mask

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.minChanVal);

  bColor.setToWhite();
  bColor.setToBlack();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.minChanVal);

  cColor.setToWhite();
  cColor.setToBlack();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.minChanVal);

  dColor.setToWhite();
  dColor.setToBlack();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToWhite();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.maxChanVal);

  bColor.setToBlack();
  bColor.setToWhite();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.maxChanVal);

  cColor.setToBlack();
  cColor.setToWhite();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.maxChanVal);

  dColor.setToBlack();
  dColor.setToWhite();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToRed();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.minChanVal);

  bColor.setToBlack();
  bColor.setToRed();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.minChanVal);

  cColor.setToBlack();
  cColor.setToRed();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.minChanVal);

  dColor.setToBlack();
  dColor.setToRed();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToRed();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.minChanVal);

  bColor.setToWhite();
  bColor.setToRed();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.minChanVal);

  cColor.setToWhite();
  cColor.setToRed();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.minChanVal);

  dColor.setToWhite();
  dColor.setToRed();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToGreen();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.minChanVal);

  bColor.setToBlack();
  bColor.setToGreen();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.minChanVal);

  cColor.setToBlack();
  cColor.setToGreen();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.minChanVal);

  dColor.setToBlack();
  dColor.setToGreen();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToGreen();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.minChanVal);

  bColor.setToWhite();
  bColor.setToGreen();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.minChanVal);

  cColor.setToWhite();
  cColor.setToGreen();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.minChanVal);

  dColor.setToWhite();
  dColor.setToGreen();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToBlue();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.minChanVal);

  bColor.setToBlack();
  bColor.setToBlue();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.minChanVal);

  cColor.setToBlack();
  cColor.setToBlue();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.minChanVal);

  dColor.setToBlack();
  dColor.setToBlue();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToBlue();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.minChanVal);

  bColor.setToWhite();
  bColor.setToBlue();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.minChanVal);

  cColor.setToWhite();
  cColor.setToBlue();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.minChanVal);

  dColor.setToWhite();
  dColor.setToBlue();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToCyan();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.maxChanVal);

  bColor.setToBlack();
  bColor.setToCyan();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.maxChanVal);

  cColor.setToBlack();
  cColor.setToCyan();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.maxChanVal);

  dColor.setToBlack();
  dColor.setToCyan();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToCyan();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.maxChanVal);

  bColor.setToWhite();
  bColor.setToCyan();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.maxChanVal);

  cColor.setToWhite();
  cColor.setToCyan();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.maxChanVal);

  dColor.setToWhite();
  dColor.setToCyan();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToMagenta();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.maxChanVal);

  bColor.setToBlack();
  bColor.setToMagenta();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.maxChanVal);

  cColor.setToBlack();
  cColor.setToMagenta();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.maxChanVal);

  dColor.setToBlack();
  dColor.setToMagenta();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToMagenta();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.maxChanVal);

  bColor.setToWhite();
  bColor.setToMagenta();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.maxChanVal);

  cColor.setToWhite();
  cColor.setToMagenta();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.maxChanVal);

  dColor.setToWhite();
  dColor.setToMagenta();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToYellow();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.maxChanVal);

  bColor.setToBlack();
  bColor.setToYellow();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.maxChanVal);

  cColor.setToBlack();
  cColor.setToYellow();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.maxChanVal);

  dColor.setToBlack();
  dColor.setToYellow();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToYellow();
  BOOST_TEST_CHECK(aColor.getC0() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC1() == aColor.maxChanVal);
  BOOST_TEST_CHECK(aColor.getC2() == aColor.minChanVal);
  BOOST_TEST_CHECK(aColor.getC3() == aColor.maxChanVal);

  bColor.setToWhite();
  bColor.setToYellow();
  BOOST_TEST_CHECK(bColor.getC0() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC1() == bColor.maxChanVal);
  BOOST_TEST_CHECK(bColor.getC2() == bColor.minChanVal);
  BOOST_TEST_CHECK(bColor.getC3() == bColor.maxChanVal);

  cColor.setToWhite();
  cColor.setToYellow();
  BOOST_TEST_CHECK(cColor.getC0() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC1() == cColor.maxChanVal);
  BOOST_TEST_CHECK(cColor.getC2() == cColor.minChanVal);
  BOOST_TEST_CHECK(cColor.getC3() == cColor.maxChanVal);

  dColor.setToWhite();
  dColor.setToYellow();
  BOOST_TEST_CHECK(dColor.getC0() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC1() == dColor.maxChanVal);
  BOOST_TEST_CHECK(dColor.getC2() == dColor.minChanVal);
  BOOST_TEST_CHECK(dColor.getC3() == dColor.maxChanVal);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(dist_int) {

  mjr::colorRGBA8b   aColor;
  mjr::colorRGBA8b   bColor;

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToBlack();

  BOOST_TEST_CHECK(aColor.distHypot( bColor) == std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*4));
  BOOST_TEST_CHECK(aColor.distSumAbs(bColor) == mjr::colorRGBA8b::maxChanVal*4);
  BOOST_TEST_CHECK(aColor.distMaxAbs(bColor) == mjr::colorRGBA8b::maxChanVal);

  BOOST_TEST_CHECK(bColor.distHypot( aColor) == std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*4));
  BOOST_TEST_CHECK(bColor.distSumAbs(aColor) == mjr::colorRGBA8b::maxChanVal*4);
  BOOST_TEST_CHECK(bColor.distMaxAbs(aColor) == mjr::colorRGBA8b::maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToWhite();

  BOOST_TEST_CHECK(aColor.distHypot( bColor) == 0);
  BOOST_TEST_CHECK(aColor.distSumAbs(bColor) == 0);
  BOOST_TEST_CHECK(aColor.distMaxAbs(bColor) == 0);

  BOOST_TEST_CHECK(bColor.distHypot( aColor) == 0);
  BOOST_TEST_CHECK(bColor.distSumAbs(aColor) == 0);
  BOOST_TEST_CHECK(bColor.distMaxAbs(aColor) == 0);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToCyan();
  bColor.setToBlack();

  BOOST_TEST_CHECK(aColor.distHypot( bColor) == std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*3), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.distSumAbs(bColor) == mjr::colorRGBA8b::maxChanVal*3);
  BOOST_TEST_CHECK(aColor.distMaxAbs(bColor) == mjr::colorRGBA8b::maxChanVal);

  BOOST_TEST_CHECK(bColor.distHypot( aColor) == std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*3), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(bColor.distSumAbs(aColor) == mjr::colorRGBA8b::maxChanVal*3);
  BOOST_TEST_CHECK(bColor.distMaxAbs(aColor) == mjr::colorRGBA8b::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(dist_flt) {

  mjr::colorRGBA32F   aColor;
  mjr::colorRGBA32F   bColor;

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToBlack();

  BOOST_TEST_CHECK(aColor.distHypot( bColor) == std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*4));
  BOOST_TEST_CHECK(aColor.distSumAbs(bColor) == mjr::colorRGBA32F::maxChanVal*4);
  BOOST_TEST_CHECK(aColor.distMaxAbs(bColor) == mjr::colorRGBA32F::maxChanVal);

  BOOST_TEST_CHECK(bColor.distHypot( aColor) == std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*4));
  BOOST_TEST_CHECK(bColor.distSumAbs(aColor) == mjr::colorRGBA32F::maxChanVal*4);
  BOOST_TEST_CHECK(bColor.distMaxAbs(aColor) == mjr::colorRGBA32F::maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToWhite();

  BOOST_TEST_CHECK(aColor.distHypot( bColor) == 0);
  BOOST_TEST_CHECK(aColor.distSumAbs(bColor) == 0);
  BOOST_TEST_CHECK(aColor.distMaxAbs(bColor) == 0);

  BOOST_TEST_CHECK(bColor.distHypot( aColor) == 0);
  BOOST_TEST_CHECK(bColor.distSumAbs(aColor) == 0);
  BOOST_TEST_CHECK(bColor.distMaxAbs(aColor) == 0);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToCyan();
  bColor.setToBlack();

  BOOST_TEST_CHECK(aColor.distHypot( bColor) == std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*3), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.distSumAbs(bColor) == mjr::colorRGBA32F::maxChanVal*3);
  BOOST_TEST_CHECK(aColor.distMaxAbs(bColor) == mjr::colorRGBA32F::maxChanVal);

  BOOST_TEST_CHECK(bColor.distHypot( aColor) == std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*3), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(bColor.distSumAbs(aColor) == mjr::colorRGBA32F::maxChanVal*3);
  BOOST_TEST_CHECK(bColor.distMaxAbs(aColor) == mjr::colorRGBA32F::maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setChansRGBA(0.5, 0.5, 0.5, 0.5);
  bColor.setToBlack();

  BOOST_TEST_CHECK(aColor.distHypot( bColor) == std::sqrt(0.5*0.5*4));
  BOOST_TEST_CHECK(aColor.distSumAbs(bColor) == 0.5*4);
  BOOST_TEST_CHECK(aColor.distMaxAbs(bColor) == 0.5);

  BOOST_TEST_CHECK(bColor.distHypot( aColor) == std::sqrt(0.5*0.5*4));
  BOOST_TEST_CHECK(bColor.distSumAbs(aColor) == 0.5*4);
  BOOST_TEST_CHECK(bColor.distMaxAbs(aColor) == 0.5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(lum_int) {

  BOOST_TEST_CHECK(mjr::colorRGBA8b( 2, 5, 7, 11).rgb2GreyDotProd(13, 17, 23)          == 272);
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 11).rgb2GreyDotProd(13, 17, 23)          == 272);

  BOOST_TEST_CHECK(mjr::colorRGBA8b(255, 255, 255, 255).rgb2GreyDotProd(255, 255, 255) == 195075); // Too big for an arith SP type...

  BOOST_TEST_CHECK(mjr::colorRGBA8b( 2, 5, 7, 11).luminanceRGB()                       == 0.0176729411765, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 11).luminanceRGB()                       == 4.5066,          boost::test_tools::tolerance(0.00001));

  BOOST_TEST_CHECK(mjr::colorRGBA8b( 2, 5, 7, 11).intensityRGB()                       == 14);
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 11).intensityRGB()                       == 14);

  BOOST_TEST_CHECK(mjr::colorRGBA8b( 2, 5, 7, 11).intensity()                          == 25);
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 11).intensity()                          == 25);

  BOOST_TEST_CHECK(mjr::colorRGBA8b( 2, 5, 7, 11).intensityScaledRGB()                 == 0.0183006562, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 11).intensityScaledRGB()                 == 4.66666698,   boost::test_tools::tolerance(0.00001));

  BOOST_TEST_CHECK(mjr::colorRGBA8b( 2, 5, 7, 11).intensityScaled()                    == 0.0245098039216, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 11).intensityScaled()                    == 6.25,            boost::test_tools::tolerance(0.00001));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(dotProd_getMax_getMin) {

  BOOST_TEST_CHECK(mjr::colorRGBA8b(2, 5, 7, 11).dotProd(mjr::colorRGBA8b(13, 17, 23, 27))  == 569);
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 11).dotProd(mjr::colorRGBA32F(13, 17, 23, 27)) == 569);

  BOOST_TEST_CHECK(mjr::colorRGBA8b(255, 255, 255, 255).dotProd(mjr::colorRGBA8b(255, 255, 255, 255))  == 260100); // Too big for an arith SP type...

  BOOST_TEST_CHECK(mjr::colorRGBA8b(2, 5, 7, 11).getMaxC()    == 11);
  BOOST_TEST_CHECK(mjr::colorRGBA8b(2, 5, 7, 11).getMaxRGB()  == 7);
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 11).getMaxC()   == 11);
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 11).getMaxRGB() == 7);

  BOOST_TEST_CHECK(mjr::colorRGBA8b(2, 5, 7, 1).getMinC()     == 1);
  BOOST_TEST_CHECK(mjr::colorRGBA8b(2, 5, 7, 1).getMinRGB()   == 2);
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 1).getMinC()    == 1);
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2, 5, 7, 1).getMinRGB()  == 2);

  BOOST_TEST_CHECK(mjr::colorRGB8b(2, 5, 7).getMaxC()         == 7);
  BOOST_TEST_CHECK(mjr::colorRGB32F(2, 5, 7).getMaxC()        == 7);

  BOOST_TEST_CHECK(mjr::colorRGB8b(2, 5, 7).getMinC()         == 2);
  BOOST_TEST_CHECK(mjr::colorRGB32F(2, 5, 7).getMinC()        == 2);

  mjr::color2c8b aColor; aColor.setC0(5); aColor.setC1(2);
  mjr::color2c8b bColor; bColor.setC0(5); bColor.setC1(2);

  BOOST_TEST_CHECK(aColor.getMaxC()                           == 5);
  BOOST_TEST_CHECK(bColor.getMaxC()                           == 5);

  BOOST_TEST_CHECK(aColor.getMinC()                           == 2);
  BOOST_TEST_CHECK(bColor.getMinC()                           == 2);

  BOOST_TEST_CHECK(mjr::colorRGBA8b(2).getMaxC()              == 2);
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2).getMaxC()             == 2);

  BOOST_TEST_CHECK(mjr::colorRGBA8b(2).getMinC()              == 2);
  BOOST_TEST_CHECK(mjr::colorRGBA32F(2).getMinC()             == 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(WavelengthCM) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA8b  bColor;

  mjr::colorRGBA32F cColor;
  mjr::colorRGBA32F dColor;

  aColor.setToBlack();
  aColor.setRGBfromWavelengthCM(570);
  BOOST_TEST_CHECK(aColor.getRed()   == 173);
  BOOST_TEST_CHECK(aColor.getGreen() == 189);
  BOOST_TEST_CHECK(aColor.getBlue()  == 2);
  BOOST_TEST_CHECK(aColor.getAlpha() == aColor.minChanVal);

  aColor.setToWhite();
  aColor.setRGBfromWavelengthCM(570);
  BOOST_TEST_CHECK(aColor.getRed()   == 173);
  BOOST_TEST_CHECK(aColor.getGreen() == 189);
  BOOST_TEST_CHECK(aColor.getBlue()  == 2);
  BOOST_TEST_CHECK(aColor.getAlpha() == aColor.maxChanVal);

  aColor.setRGBfromWavelengthCM(571, mjr::colorRGBA8b::cmfInterpolationEnum::FLOOR);
  bColor.setRGBfromWavelengthCM(570);
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromWavelengthCM(571, mjr::colorRGBA8b::cmfInterpolationEnum::CEILING);
  bColor.setRGBfromWavelengthCM(575);
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromWavelengthCM(571, mjr::colorRGBA8b::cmfInterpolationEnum::NEAREST);
  bColor.setRGBfromWavelengthCM(570);
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromWavelengthCM(574, mjr::colorRGBA8b::cmfInterpolationEnum::NEAREST);
  bColor.setRGBfromWavelengthCM(575);
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromWavelengthCM(572, mjr::colorRGBA8b::cmfInterpolationEnum::LINEAR);
  BOOST_TEST_CHECK(aColor.getRed()   == 182);
  BOOST_TEST_CHECK(aColor.getGreen() == 181);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0);

  aColor.setRGBfromWavelengthCM(572, mjr::colorRGBA8b::cmfInterpolationEnum::BUMP);
  BOOST_TEST_CHECK(aColor.getRed()   == 167);
  BOOST_TEST_CHECK(aColor.getGreen() == 169);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0);

////////////////////////////////////////////////////////////////////////////////

  cColor.setToBlack();
  cColor.setRGBfromWavelengthCM(570);
  BOOST_TEST_CHECK(cColor.getRed()   == 0.679159,      boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getGreen() == 0.743843,      boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getBlue()  == 0.00798483,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getAlpha() == cColor.minChanVal);

  cColor.setToWhite();
  cColor.setRGBfromWavelengthCM(570);
  BOOST_TEST_CHECK(cColor.getRed()   == 0.679159,      boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getGreen() == 0.743843,      boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getBlue()  == 0.00798483,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getAlpha() == cColor.maxChanVal);

  cColor.setRGBfromWavelengthCM(571, mjr::colorRGBA32F::cmfInterpolationEnum::FLOOR);
  dColor.setRGBfromWavelengthCM(570);
  BOOST_TEST_CHECK(cColor.getRed()   == dColor.getRed());
  BOOST_TEST_CHECK(cColor.getGreen() == dColor.getGreen());
  BOOST_TEST_CHECK(cColor.getBlue()  == dColor.getBlue());

  cColor.setRGBfromWavelengthCM(571, mjr::colorRGBA32F::cmfInterpolationEnum::CEILING);
  dColor.setRGBfromWavelengthCM(575);
  BOOST_TEST_CHECK(cColor.getRed()   == dColor.getRed());
  BOOST_TEST_CHECK(cColor.getGreen() == dColor.getGreen());
  BOOST_TEST_CHECK(cColor.getBlue()  == dColor.getBlue());

  cColor.setRGBfromWavelengthCM(571, mjr::colorRGBA32F::cmfInterpolationEnum::NEAREST);
  dColor.setRGBfromWavelengthCM(570);
  BOOST_TEST_CHECK(cColor.getRed()   == dColor.getRed());
  BOOST_TEST_CHECK(cColor.getGreen() == dColor.getGreen());
  BOOST_TEST_CHECK(cColor.getBlue()  == dColor.getBlue());

  cColor.setRGBfromWavelengthCM(574, mjr::colorRGBA32F::cmfInterpolationEnum::NEAREST);
  dColor.setRGBfromWavelengthCM(575);
  BOOST_TEST_CHECK(cColor.getRed()   == dColor.getRed());
  BOOST_TEST_CHECK(cColor.getGreen() == dColor.getGreen());
  BOOST_TEST_CHECK(cColor.getBlue()  == dColor.getBlue());

  cColor.setRGBfromWavelengthCM(572, mjr::colorRGBA32F::cmfInterpolationEnum::LINEAR);
  BOOST_TEST_CHECK(cColor.getRed()   == 0.713749886,   boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getGreen() == 0.710754037,   boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getBlue()  == 0.00187643478, boost::test_tools::tolerance(0.00001));

  cColor.setRGBfromWavelengthCM(572, mjr::colorRGBA32F::cmfInterpolationEnum::BUMP);
  BOOST_TEST_CHECK(cColor.getRed()   == 0.654946387,   boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getGreen() == 0.662842572,   boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getBlue()  == 3.4287558e-07, boost::test_tools::tolerance(0.00001));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(WavelengthLA) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA8b  bColor;

  mjr::colorRGBA32F cColor;
  mjr::colorRGBA32F dColor;

  aColor.setToBlack();
  aColor.setRGBfromWavelengthLA(570);
  BOOST_TEST_CHECK(aColor.getRed()   == 0xda);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xff);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == aColor.minChanVal);

  aColor.setToWhite();
  aColor.setRGBfromWavelengthLA(570);
  BOOST_TEST_CHECK(aColor.getRed()   == 0xda);
  BOOST_TEST_CHECK(aColor.getGreen() == 0xff);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == aColor.maxChanVal);

////////////////////////////////////////////////////////////////////////////////

  cColor.setToBlack();
  cColor.setRGBfromWavelengthLA(570);
  BOOST_TEST_CHECK(cColor.getRed()   == 0.857142866,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getGreen() == 1.000000000,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getBlue()  == 0.000000000,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getAlpha() == cColor.minChanVal);

  cColor.setToWhite();
  cColor.setRGBfromWavelengthLA(570);
  BOOST_TEST_CHECK(cColor.getRed()   == 0.857142866,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getGreen() == 1.000000000,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getBlue()  == 0.000000000,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(cColor.getAlpha() == cColor.maxChanVal);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(csCubeHelix_tpl, * boost::unit_test::tolerance(0.01)) {

  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.25).getC0() == 0.085);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.25).getC1() == 0.325);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.25).getC2() == 0.298);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.50).getC0() == 0.628);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.50).getC1() == 0.475);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.50).getC2() == 0.286);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.75).getC0() == 0.780);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.75).getC1() == 0.702);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.75).getC2() == 0.929);


  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.25).getC0() == 0.280);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.25).getC1() == 0.202);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.25).getC2() == 0.429);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.50).getC0() == 0.372);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.50).getC1() == 0.525);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.50).getC2() == 0.714);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.75).getC0() == 0.585);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.75).getC1() == 0.825);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.75).getC2() == 0.798);


  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.25).getC0() == 0.388);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.25).getC1() == 0.163);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.25).getC2() == 0.342);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.50).getC0() == 0.684);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.50).getC1() == 0.384);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.50).getC2() == 0.623);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.75).getC0() == 0.888);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.75).getC1() == 0.663);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.75).getC2() == 0.842);

  typedef mjr::colorTpl<double, 3, 2, 1, 0> permcolor3c64F;

  BOOST_TEST_CHECK(permcolor3c64F::csCHstd::c(0.25).getC2() == 0.085);
  BOOST_TEST_CHECK(permcolor3c64F::csCHstd::c(0.25).getC1() == 0.325);
  BOOST_TEST_CHECK(permcolor3c64F::csCHstd::c(0.25).getC0() == 0.298);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_misc) {

  mjr::colorRGB8b aColor;
  mjr::colorRGB8b bColor;
  mjr::colorRGB8b dColor;
  mjr::colorRGB8b cColor;

  aColor.setRGBfromLogPackIntARGB(0xFF00FF);
  bColor.setRGBfromLogPackIntARGB(0x00FFFF);
  dColor.setRGBfromLogPackIntARGB(0x0100FF);


  cColor.setToBlack();
  cColor.tfrmCopy(aColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=aColor;
  cColor.tfrmMaxI(bColor); // Intensity equal, NOOP
  BOOST_TEST_CHECK(cColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=aColor;
  cColor.tfrmMinI(bColor); // Intensity equal, NOOP
  BOOST_TEST_CHECK(cColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=aColor;
  cColor.tfrmMax(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC1() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=aColor;
  cColor.tfrmMin(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0x00);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=dColor;
  cColor.tfrmSaw(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00000100), mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00FFFFFF));
  BOOST_TEST_CHECK(cColor.getC0() == 0x01);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=dColor;
  cColor.tfrmStep(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00000100), mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00FFFFFF));
  BOOST_TEST_CHECK(cColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=aColor;
  cColor.tfrmDirac(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0x00);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=aColor;
  cColor.tfrmDiracTot(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0x00);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0x00);

  cColor=aColor;
  cColor.tfrmDiracTot(aColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC1() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=aColor;
  cColor.tfrmFuzzyDirac(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00FE01F0), mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00010101));
  BOOST_TEST_CHECK(cColor.getC0() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC1() == 0xFF);
  BOOST_TEST_CHECK(cColor.getC2() == 0x00);

  cColor=aColor;
  cColor.tfrmMean(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0x7f);
  BOOST_TEST_CHECK(cColor.getC1() == 0x7f);
  BOOST_TEST_CHECK(cColor.getC2() == 0xFF);

  cColor=dColor;
  cColor.tfrmGmean(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00030102));
  BOOST_TEST_CHECK(cColor.getC0() == 0x01);
  BOOST_TEST_CHECK(cColor.getC1() == 0x00);
  BOOST_TEST_CHECK(cColor.getC2() == 0x16);

  cColor=aColor;
  cColor.tfrmGreyScaleRGB();
  BOOST_TEST_CHECK(cColor.getC0() == 0x48);
  BOOST_TEST_CHECK(cColor.getC1() == 0x48);
  BOOST_TEST_CHECK(cColor.getC2() == 0x48);

  cColor=bColor;
  cColor.tfrmGreyScaleRGB();
  BOOST_TEST_CHECK(cColor.getC0() == 0xC8);
  BOOST_TEST_CHECK(cColor.getC1() == 0xC8);
  BOOST_TEST_CHECK(cColor.getC2() == 0xC8);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_misc_FLT, * boost::unit_test::tolerance(0.00001)) {

  mjr::colorRGB32F aColor;
  mjr::colorRGB32F bColor;
  mjr::colorRGB32F dColor;
  mjr::colorRGB32F cColor;

  aColor.setChansRGB(2.0, 0.0, 2.0);
  bColor.setChansRGB(0.0, 2.0, 2.0);
  dColor.setChansRGB(0.0, 1.0, 2.0);

  cColor.setToBlack();
  cColor.tfrmCopy(aColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=aColor;
  cColor.tfrmMaxI(bColor); // Intensity equal, NOOP
  BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=aColor;
  cColor.tfrmMinI(bColor); // Intensity equal, NOOP
  BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=aColor;
  cColor.tfrmMax(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  BOOST_TEST_CHECK(cColor.getC1() == 2.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=aColor;
  cColor.tfrmMin(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  // cColor=dColor;
  // cColor.tfrmSaw(mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0000100), mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0FFFFFF));
  // BOOST_TEST_CHECK(cColor.getC0() == 0x01);
  // BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  // BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  // cColor=dColor;
  // cColor.tfrmStep(mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0000100), mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0FFFFFF));
  // BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  // BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  // BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=aColor;
  cColor.tfrmDirac(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 1.0);

  cColor=aColor;
  cColor.tfrmDiracTot(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 0.0);
  BOOST_TEST_CHECK(cColor.getC1() == 0.0);
  BOOST_TEST_CHECK(cColor.getC2() == 0.0);

  cColor=aColor;
  cColor.tfrmDiracTot(aColor);
  BOOST_TEST_CHECK(cColor.getC0() == 1.0);
  BOOST_TEST_CHECK(cColor.getC1() == 1.0);
  BOOST_TEST_CHECK(cColor.getC2() == 1.0);

  // cColor=aColor;
  // cColor.tfrmFuzzyDirac(mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0FE01F0), mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0010101));
  // BOOST_TEST_CHECK(cColor.getC0() == 2.0);
  // BOOST_TEST_CHECK(cColor.getC1() == 2.0);
  // BOOST_TEST_CHECK(cColor.getC2() == 0.0);

  cColor=aColor;
  cColor.tfrmMean(bColor);
  BOOST_TEST_CHECK(cColor.getC0() == 1.0);
  BOOST_TEST_CHECK(cColor.getC1() == 1.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=dColor;
  cColor.tfrmGmean(mjr::colorRGB32F().setChansRGB(8.0, 25.0, 2.0));
  BOOST_TEST_CHECK(cColor.getC0() == 0.0);
  BOOST_TEST_CHECK(cColor.getC1() == 5.0);
  BOOST_TEST_CHECK(cColor.getC2() == 2.0);

  cColor=aColor;
  cColor.tfrmGreyScaleRGB();
  BOOST_TEST_CHECK(cColor.getC0() == 0.569599986);
  BOOST_TEST_CHECK(cColor.getC1() == 0.569599986);
  BOOST_TEST_CHECK(cColor.getC2() == 0.569599986);

  cColor=bColor;
  cColor.tfrmGreyScaleRGB();
  BOOST_TEST_CHECK(cColor.getC0() == 1.57480001);
  BOOST_TEST_CHECK(cColor.getC1() == 1.57480001);
  BOOST_TEST_CHECK(cColor.getC2() == 1.57480001);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_websafe) {

  mjr::colorRGB8b  aColor;
  mjr::colorRGB8b  bColor;
  mjr::colorRGB32F cColor;
  mjr::colorRGBA8b dColor;

  aColor.setChansRGB(0x00, 0x33, 0x66);
  bColor.setChansRGB(0x00, 0x33, 0x66);
  aColor.tfrmWebSafeRGB();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setChansRGB(0x99, 0xCC, 0xFF);
  bColor.setChansRGB(0x99, 0xCC, 0xFF);
  aColor.tfrmWebSafeRGB();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setChansRGB(0x01, 0x34, 0x67);
  bColor.setChansRGB(0x00, 0x33, 0x66);
  aColor.tfrmWebSafeRGB();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setChansRGB(0x98, 0xCB, 0xFE);
  bColor.setChansRGB(0x99, 0xCC, 0xFF);
  aColor.tfrmWebSafeRGB();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  cColor.setChansRGB(0.05F, 0.15F, 0.35F);
  cColor.tfrmWebSafeRGB();
  BOOST_TEST_CHECK(cColor.getRed()   == 0.0,    boost::test_tools::tolerance(0.0001));
  BOOST_TEST_CHECK(cColor.getGreen() == 0.2,    boost::test_tools::tolerance(0.0001));
  BOOST_TEST_CHECK(cColor.getBlue()  == 0.4,    boost::test_tools::tolerance(0.0001));

  cColor.setChansRGB(0.55F, 0.75F, 0.95F);
  cColor.tfrmWebSafeRGB();
  BOOST_TEST_CHECK(cColor.getRed()   == 0.6,    boost::test_tools::tolerance(0.0001));
  BOOST_TEST_CHECK(cColor.getGreen() == 0.8,    boost::test_tools::tolerance(0.0001));
  BOOST_TEST_CHECK(cColor.getBlue()  == 1.0,    boost::test_tools::tolerance(0.0001));

  dColor.setChans(0xCB);
  dColor.tfrmWebSafeRGB();
  BOOST_TEST_CHECK(dColor.getRed()   == 0xCC);
  BOOST_TEST_CHECK(dColor.getGreen() == 0xCC);
  BOOST_TEST_CHECK(dColor.getBlue()  == 0xCC);
  BOOST_TEST_CHECK(dColor.getAlpha() == 0xCB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_PowPow_int) {

  mjr::colorRGB8b  aColor;
  mjr::colorRGBA8b bColor;

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmLn();
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 3);
  BOOST_TEST_CHECK(aColor.getBlue()  == 4);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqr();
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 9);
  BOOST_TEST_CHECK(aColor.getBlue()  == 39);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqrt();
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 112);
  BOOST_TEST_CHECK(aColor.getBlue()  == 159);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(2.0);
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 9);
  BOOST_TEST_CHECK(aColor.getBlue()  == 39);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(0.5);
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 112);
  BOOST_TEST_CHECK(aColor.getBlue()  == 159);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowRGB(1, 2.0, 0.5);
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 9);
  BOOST_TEST_CHECK(aColor.getBlue()  == 159);

  bColor.setToWhite();
  bColor.setChansRGB(0, 50, 100);
  bColor.tfrmStdPowRGB(1, 2.0, 0.5);
  BOOST_TEST_CHECK(bColor.getRed()   == 0);
  BOOST_TEST_CHECK(bColor.getGreen() == 9);
  BOOST_TEST_CHECK(bColor.getBlue()  == 159);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0xff);

  bColor.setToBlack();
  bColor.setChansRGB(0, 50, 100);
  bColor.tfrmStdPowRGB(1, 2.0, 0.5);
  BOOST_TEST_CHECK(bColor.getRed()   == 0);
  BOOST_TEST_CHECK(bColor.getGreen() == 9);
  BOOST_TEST_CHECK(bColor.getBlue()  == 159);
  BOOST_TEST_CHECK(bColor.getAlpha() == 0x00);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_PowPow_flt, * boost::unit_test::tolerance(0.00001)) {

  mjr::colorRGB32F aColor;

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmLn();
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 3.93182563272);
  BOOST_TEST_CHECK(aColor.getBlue()  == 4.61512051684);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqr();
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 2500);
  BOOST_TEST_CHECK(aColor.getBlue()  == 10000);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqrt();
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 7.07106781);
  BOOST_TEST_CHECK(aColor.getBlue()  == 10);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(2.0);
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 2500);
  BOOST_TEST_CHECK(aColor.getBlue()  == 10000);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(0.5);
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 7.07106781);
  BOOST_TEST_CHECK(aColor.getBlue()  == 10);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowRGB(1, 2.0, 0.5);
  BOOST_TEST_CHECK(aColor.getRed()   == 0);
  BOOST_TEST_CHECK(aColor.getGreen() == 2500);
  BOOST_TEST_CHECK(aColor.getBlue()  == 10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_GryLevScl_int) {

  mjr::colorRGB8b  aColor;
  mjr::colorRGBA8b cColor;

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2, 4);
  BOOST_TEST_CHECK(aColor.getRed()   == 24);
  BOOST_TEST_CHECK(aColor.getGreen() == 44);
  BOOST_TEST_CHECK(aColor.getBlue()  == 54);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2.5, 4);
  BOOST_TEST_CHECK(aColor.getRed()   == 29);
  BOOST_TEST_CHECK(aColor.getGreen() == 54);
  BOOST_TEST_CHECK(aColor.getBlue()  == 66);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  BOOST_TEST_CHECK(aColor.getRed()   == 24);
  BOOST_TEST_CHECK(aColor.getGreen() == 54);
  BOOST_TEST_CHECK(aColor.getBlue()  == 77);

  cColor.setToWhite();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  BOOST_TEST_CHECK(cColor.getRed()   == 24);
  BOOST_TEST_CHECK(cColor.getGreen() == 54);
  BOOST_TEST_CHECK(cColor.getBlue()  == 77);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xff);

  cColor.setToBlack();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  BOOST_TEST_CHECK(cColor.getRed()   == 24);
  BOOST_TEST_CHECK(cColor.getGreen() == 54);
  BOOST_TEST_CHECK(cColor.getBlue()  == 77);
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x00);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(tfrm_GryLevSclflt, * boost::unit_test::tolerance(0.00001)) {

  mjr::colorRGB32F  aColor;
  mjr::colorRGBA32F cColor;

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2, 4);
  BOOST_TEST_CHECK(aColor.getRed()   == 24.0);
  BOOST_TEST_CHECK(aColor.getGreen() == 44.0);
  BOOST_TEST_CHECK(aColor.getBlue()  == 54.0);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2.5, 4);
  BOOST_TEST_CHECK(aColor.getRed()   == 29.0);
  BOOST_TEST_CHECK(aColor.getGreen() == 54.0);
  BOOST_TEST_CHECK(aColor.getBlue()  == 66.5);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  BOOST_TEST_CHECK(aColor.getRed()   == 24.0);
  BOOST_TEST_CHECK(aColor.getGreen() == 54.0);
  BOOST_TEST_CHECK(aColor.getBlue()  == 77.0);

  cColor.setToWhite();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  BOOST_TEST_CHECK(cColor.getRed()   == 24.0);
  BOOST_TEST_CHECK(cColor.getGreen() == 54.0);
  BOOST_TEST_CHECK(cColor.getBlue()  == 77.0);
  BOOST_TEST_CHECK(cColor.getAlpha() ==  1.0);

  cColor.setToBlack();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  BOOST_TEST_CHECK(cColor.getRed()   == 24.0);
  BOOST_TEST_CHECK(cColor.getGreen() == 54.0);
  BOOST_TEST_CHECK(cColor.getBlue()  == 77.0);
  BOOST_TEST_CHECK(cColor.getAlpha() ==  0.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(wmean, * boost::unit_test::tolerance(0.01)) {

  mjr::colorRGBA8b a1Color(10, 20, 30, 40);
  mjr::colorRGBA8b a2Color(10, 30, 20, 40);
  mjr::colorRGBA8b a3Color(40, 20, 30, 10);
  mjr::colorRGBA8b a4Color(90, 70, 10, 20);

  mjr::colorRGBA8b aColor;
  mjr::colorRGBA8b cColor;

  mjr::colorRGBA32F b1Color(10, 20, 30, 40);
  mjr::colorRGBA32F b2Color(10, 30, 20, 40);
  mjr::colorRGBA32F b3Color(40, 20, 30, 10);
  mjr::colorRGBA32F b4Color(90, 70, 10, 20);

  mjr::colorRGBA32F bColor;

 ////////////////////////////////////////////////////////////////////////////////

 aColor.wMean(1.0F, 1.0F, a1Color, a2Color);
 BOOST_TEST_CHECK(aColor.getC0() == 20);
 BOOST_TEST_CHECK(aColor.getC1() == 50);
 BOOST_TEST_CHECK(aColor.getC2() == 50);
 BOOST_TEST_CHECK(aColor.getC3() == 80);

 aColor.wMean(1.0F, 1.0F, 1.0F, a1Color, a2Color, a3Color);
 BOOST_TEST_CHECK(aColor.getC0() == 60);
 BOOST_TEST_CHECK(aColor.getC1() == 70);
 BOOST_TEST_CHECK(aColor.getC2() == 80);
 BOOST_TEST_CHECK(aColor.getC3() == 90);

 aColor.wMean(1.0F, 1.0F, 1.0F, 1.0F, a1Color, a2Color, a3Color, a4Color);
 BOOST_TEST_CHECK(aColor.getC0() == 150);
 BOOST_TEST_CHECK(aColor.getC1() == 140);
 BOOST_TEST_CHECK(aColor.getC2() ==  90);
 BOOST_TEST_CHECK(aColor.getC3() == 110);

 aColor.wMean(0.1F, 1.0F, a1Color, a2Color);
 BOOST_TEST_CHECK(aColor.getC0() == 11);
 BOOST_TEST_CHECK(aColor.getC1() == 32);
 BOOST_TEST_CHECK(aColor.getC2() == 23);
 BOOST_TEST_CHECK(aColor.getC3() == 44);

 aColor.wMean(0.1F, 1.0F, 1.0F, a1Color, a2Color, a3Color);
 BOOST_TEST_CHECK(aColor.getC0() == 51);
 BOOST_TEST_CHECK(aColor.getC1() == 52);
 BOOST_TEST_CHECK(aColor.getC2() == 53);
 BOOST_TEST_CHECK(aColor.getC3() == 54);

 aColor.wMean(0.1F, 1.0F, 1.0F, 1.0F, a1Color, a2Color, a3Color, a4Color);
 BOOST_TEST_CHECK(aColor.getC0() == 141);
 BOOST_TEST_CHECK(aColor.getC1() == 122);
 BOOST_TEST_CHECK(aColor.getC2() ==  63);
 BOOST_TEST_CHECK(aColor.getC3() ==  74);

 ////////////////////////////////////////////////////////////////////////////////

 bColor.wMean(1.0F, 1.0F, b1Color, b2Color);
 BOOST_TEST_CHECK(bColor.getC0() == 20);
 BOOST_TEST_CHECK(bColor.getC1() == 50);
 BOOST_TEST_CHECK(bColor.getC2() == 50);
 BOOST_TEST_CHECK(bColor.getC3() == 80);

 bColor.wMean(1.0F, 1.0F, 1.0F, b1Color, b2Color, b3Color);
 BOOST_TEST_CHECK(bColor.getC0() == 60);
 BOOST_TEST_CHECK(bColor.getC1() == 70);
 BOOST_TEST_CHECK(bColor.getC2() == 80);
 BOOST_TEST_CHECK(bColor.getC3() == 90);

 bColor.wMean(1.0F, 1.0F, 1.0F, 1.0F, b1Color, b2Color, b3Color, b4Color);
 BOOST_TEST_CHECK(bColor.getC0() == 150);
 BOOST_TEST_CHECK(bColor.getC1() == 140);
 BOOST_TEST_CHECK(bColor.getC2() ==  90);
 BOOST_TEST_CHECK(bColor.getC3() == 110);

 bColor.wMean(0.1F, 1.0F, b1Color, b2Color);
 BOOST_TEST_CHECK(bColor.getC0() == 11);
 BOOST_TEST_CHECK(bColor.getC1() == 32);
 BOOST_TEST_CHECK(bColor.getC2() == 23);
 BOOST_TEST_CHECK(bColor.getC3() == 44);

 bColor.wMean(0.1F, 1.0F, 1.0F, b1Color, b2Color, b3Color);
 BOOST_TEST_CHECK(bColor.getC0() == 51);
 BOOST_TEST_CHECK(bColor.getC1() == 52);
 BOOST_TEST_CHECK(bColor.getC2() == 53);
 BOOST_TEST_CHECK(bColor.getC3() == 54);

 bColor.wMean(0.1F, 1.0F, 1.0F, 1.0F, b1Color, b2Color, b3Color, b4Color);
 BOOST_TEST_CHECK(bColor.getC0() == 141);
 BOOST_TEST_CHECK(bColor.getC1() == 122);
 BOOST_TEST_CHECK(bColor.getC2() ==  63);
 BOOST_TEST_CHECK(bColor.getC3() ==  74);


 ////////////////////////////////////////////////////////////////////////////////

 aColor.linearInterpolate(0.0, a1Color, a2Color);
 BOOST_TEST_CHECK(aColor.getC0() == a1Color.getC0());
 BOOST_TEST_CHECK(aColor.getC1() == a1Color.getC1());
 BOOST_TEST_CHECK(aColor.getC2() == a1Color.getC2());
 BOOST_TEST_CHECK(aColor.getC3() == a1Color.getC3());

 aColor.linearInterpolate(1.0, a1Color, a2Color);
 BOOST_TEST_CHECK(aColor.getC0() == a2Color.getC0());
 BOOST_TEST_CHECK(aColor.getC1() == a2Color.getC1());
 BOOST_TEST_CHECK(aColor.getC2() == a2Color.getC2());
 BOOST_TEST_CHECK(aColor.getC3() == a2Color.getC3());

 aColor.linearInterpolate(0.5, a1Color, a2Color);
 cColor.uMean(0.5F, a1Color, a2Color);
 BOOST_TEST_CHECK(aColor.getC0() == cColor.getC0());
 BOOST_TEST_CHECK(aColor.getC1() == cColor.getC1());
 BOOST_TEST_CHECK(aColor.getC2() == cColor.getC2());
 BOOST_TEST_CHECK(aColor.getC3() == cColor.getC3());

 aColor.linearInterpolate(0.25, a1Color, a2Color);
 cColor.uMean(0.75F, a1Color, a2Color);
 BOOST_TEST_CHECK(aColor.getC0() == cColor.getC0());
 BOOST_TEST_CHECK(aColor.getC1() == cColor.getC1());
 BOOST_TEST_CHECK(aColor.getC2() == cColor.getC2());
 BOOST_TEST_CHECK(aColor.getC3() == cColor.getC3());

 aColor.linearInterpolate(0.75, a1Color, a2Color);
 cColor.uMean(0.25F, a1Color, a2Color);
 BOOST_TEST_CHECK(aColor.getC0() == cColor.getC0());
 BOOST_TEST_CHECK(aColor.getC1() == cColor.getC1());
 BOOST_TEST_CHECK(aColor.getC2() == cColor.getC2());
 BOOST_TEST_CHECK(aColor.getC3() == cColor.getC3());

 ////////////////////////////////////////////////////////////////////////////////
 aColor.uMean(0.2F, a1Color, a2Color);
 BOOST_TEST_CHECK(aColor.getC0() == .2*10+.8*10);
 BOOST_TEST_CHECK(aColor.getC1() == .2*20+.8*30);
 BOOST_TEST_CHECK(aColor.getC2() == .2*30+.8*20);
 BOOST_TEST_CHECK(aColor.getC3() == .2*40+.8*40);

 aColor.uMean(0.1F, 0.3F, a1Color, a2Color, a3Color);
 BOOST_TEST_CHECK(aColor.getC0() == .1*10+.3*10+0.6*40);
 BOOST_TEST_CHECK(aColor.getC1() == .1*20+.3*30+0.6*20);
 BOOST_TEST_CHECK(aColor.getC2() == .1*30+.3*20+0.6*30);
 BOOST_TEST_CHECK(aColor.getC3() == .1*40+.3*40+0.6*10);

 aColor.uMean(0.1F, 0.3F, 0.4F, a1Color, a2Color, a3Color, a4Color);
 BOOST_TEST_CHECK(aColor.getC0() == .1*10+.3*10+0.4*40+0.2*90);
 BOOST_TEST_CHECK(aColor.getC1() == .1*20+.3*30+0.4*20+0.2*70);
 BOOST_TEST_CHECK(aColor.getC2() == .1*30+.3*20+0.4*30+0.2*10);
 BOOST_TEST_CHECK(aColor.getC3() == .1*40+.3*40+0.4*10+0.2*20);

 ////////////////////////////////////////////////////////////////////////////////

 bColor.uMean(0.2F, b1Color, b2Color);
 BOOST_TEST_CHECK(bColor.getC0() == .2*10+.8*10);
 BOOST_TEST_CHECK(bColor.getC1() == .2*20+.8*30);
 BOOST_TEST_CHECK(bColor.getC2() == .2*30+.8*20);
 BOOST_TEST_CHECK(bColor.getC3() == .2*40+.8*40);

 bColor.uMean(0.1F, 0.3F, b1Color, b2Color, b3Color);
 BOOST_TEST_CHECK(bColor.getC0() == .1*10+.3*10+0.6*40);
 BOOST_TEST_CHECK(bColor.getC1() == .1*20+.3*30+0.6*20);
 BOOST_TEST_CHECK(bColor.getC2() == .1*30+.3*20+0.6*30);
 BOOST_TEST_CHECK(bColor.getC3() == .1*40+.3*40+0.6*10);

 bColor.uMean(0.1F, 0.3F, 0.4F, b1Color, b2Color, b3Color, b4Color);
 BOOST_TEST_CHECK(bColor.getC0() == .1*10+.3*10+0.4*40+0.2*90);
 BOOST_TEST_CHECK(bColor.getC1() == .1*20+.3*30+0.4*20+0.2*70);
 BOOST_TEST_CHECK(bColor.getC2() == .1*30+.3*20+0.4*30+0.2*10);
 BOOST_TEST_CHECK(bColor.getC3() == .1*40+.3*40+0.4*10+0.2*20);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(hsl_hsv_int) {

  mjr::colorRGB8b aColor;
  mjr::colorRGB8b bColor;

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0.5);
  bColor.setToRed();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL( 60/360.0, 1, 0.5);
  bColor.setToYellow();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(120/360.0, 1, 0.5);
  bColor.setToGreen();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0.5);
  bColor.setToCyan();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(240/360.0, 1, 0.5);
  bColor.setToBlue();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(300/360.0, 1, 0.5);
  bColor.setToMagenta();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 1.0);
  bColor.setToRed();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV( 60/360.0, 1, 1.0);
  bColor.setToYellow();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV( 420/360.0, 1, 1.0);
  bColor.setToYellow();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(120/360.0, 1, 1.0);
  bColor.setToGreen();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 1, 1.0);
  bColor.setToCyan();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(240/360.0, 1, 1.0);
  bColor.setToBlue();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(300/360.0, 1, 1.0);
  bColor.setToMagenta();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 1);
  bColor.setToWhite();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 1);
  bColor.setToWhite();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 1);
  bColor.setToWhite();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 0, 1);
  bColor.setToWhite();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 0, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 1, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(hsl_hsv_flt, * boost::unit_test::tolerance(0.01)) {

  mjr::colorRGB32F aColor;
  mjr::colorRGB32F bColor;

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0.5);
  bColor.setToRed();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL( 60/360.0, 1, 0.5);
  bColor.setToYellow();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL( 420/360.0, 1, 0.5);
  bColor.setToYellow();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(120/360.0, 1, 0.5);
  bColor.setToGreen();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0.5);
  bColor.setToCyan();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(240/360.0, 1, 0.5);
  bColor.setToBlue();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(300/360.0, 1, 0.5);
  bColor.setToMagenta();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 1.0);
  bColor.setToRed();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV( 60/360.0, 1, 1.0);
  bColor.setToYellow();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(120/360.0, 1, 1.0);
  bColor.setToGreen();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 1, 1.0);
  bColor.setToCyan();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(240/360.0, 1, 1.0);
  bColor.setToBlue();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(300/360.0, 1, 1.0);
  bColor.setToMagenta();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 1);
  bColor.setToWhite();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 1);
  bColor.setToWhite();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 1);
  bColor.setToWhite();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 0, 1);
  bColor.setToWhite();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 0, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 1, 0);
  bColor.setToBlack();
  BOOST_TEST_CHECK(aColor.getRed()   == bColor.getRed());
  BOOST_TEST_CHECK(aColor.getGreen() == bColor.getGreen());
  BOOST_TEST_CHECK(aColor.getBlue()  == bColor.getBlue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(csCColdeRainbow_int, * boost::unit_test::tolerance(0.01)) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

  aColor.setToWhite();
  mjr::colorRGBA8b::csCColdeRainbow::c(aColor, 0u);
  BOOST_TEST_CHECK(aColor.getRed()   == mjr::colorRGBA8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getGreen() == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getBlue()  == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getAlpha() == mjr::colorRGBA8b::minChanVal); // Corner colors set ALL channels -- primary colors set them all to minChanVal

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(   0u).isEqualRGB(aColor.setToRed())     == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c( 255u).isEqualRGB(aColor.setToYellow())  == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c( 510u).isEqualRGB(aColor.setToGreen())   == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c( 765u).isEqualRGB(aColor.setToCyan())    == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(1020u).isEqualRGB(aColor.setToBlue())    == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(1275u).isEqualRGB(aColor.setToMagenta()) == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(1530u).isEqualRGB(aColor.setToRed())     == true);

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(1531u).isEqualRGB(aColor.setToRed())     == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(1786u).isEqualRGB(aColor.setToYellow())  == true);

  for(unsigned int i=0; i<1531; i++)   // BOOST_TEST_CHECK x 1531
    BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(i).isEqualRGB(aColor.cmpRGBcornerDGradiant(i, "RYGCBMR")) == true);

  aColor.cmpRGBcornerDGradiant(10u, "RYGCBMR");
  BOOST_TEST_CHECK(aColor.getRed()   == 0xff);
  BOOST_TEST_CHECK(aColor.getGreen() == 10);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0);

////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  mjr::colorRGBA32F::csCColdeRainbow::c(bColor, 0u);
  BOOST_TEST_CHECK(bColor.getRed()   == mjr::colorRGBA32F::maxChanVal);
  BOOST_TEST_CHECK(bColor.getGreen() == mjr::colorRGBA32F::minChanVal);
  BOOST_TEST_CHECK(bColor.getBlue()  == mjr::colorRGBA32F::minChanVal);
  BOOST_TEST_CHECK(bColor.getAlpha() == mjr::colorRGBA32F::minChanVal); // Corner colors set ALL channels -- primary colors set them all to minChanVal

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(0*0x100000000ul).isEqualRGB(bColor.setToRed())     == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(1*0x100000000ul).isEqualRGB(bColor.setToYellow())  == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(2*0x100000000ul).isEqualRGB(bColor.setToGreen())   == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(3*0x100000000ul).isEqualRGB(bColor.setToCyan())    == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(4*0x100000000ul).isEqualRGB(bColor.setToBlue())    == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(5*0x100000000ul).isEqualRGB(bColor.setToMagenta()) == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(6*0x100000000ul).isEqualRGB(bColor.setToRed())     == true);

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(6*0x100000000ul+1).isEqualRGB(bColor.setToRed())     == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(7*0x100000000ul+1).isEqualRGB(bColor.setToYellow())  == true);

  for(uint64_t i=0; i<0x600000000; i=i+0x60000)  // BOOST_TEST_CHECK x 65536
    BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(i).isEqualRGB(bColor.cmpRGBcornerDGradiant(i, "RYGCBMR")) == true);

  bColor.cmpRGBcornerDGradiant(168430090, "RYGCBMR");
  BOOST_TEST_CHECK(bColor.getRed()   == 1);
  BOOST_TEST_CHECK(bColor.getGreen() == 0.0392156862745);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(csCColdeRainbow_flt, * boost::unit_test::tolerance(0.01)) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

  aColor.setToWhite();
  mjr::colorRGBA8b::csCColdeRainbow::c(aColor, 0.0);
  BOOST_TEST_CHECK(aColor.getRed()   == mjr::colorRGBA8b::maxChanVal);
  BOOST_TEST_CHECK(aColor.getGreen() == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getBlue()  == mjr::colorRGBA8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getAlpha() == mjr::colorRGBA8b::minChanVal); // Corner colors set ALL channels -- primary colors set them all to minChanVal

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(   0/1530.0).isEqualRGB(aColor.setToRed())     == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c( 255/1530.0).isEqualRGB(aColor.setToYellow())  == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c( 510/1530.0).isEqualRGB(aColor.setToGreen())   == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c( 765/1530.0).isEqualRGB(aColor.setToCyan())    == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(1020/1530.0).isEqualRGB(aColor.setToBlue())    == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(1275/1530.0).isEqualRGB(aColor.setToMagenta()) == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(1530/1530.0).isEqualRGB(aColor.setToRed())     == true);

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(2.0).isEqualRGB(aColor.setToRed())  == true);
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(3.0).isEqualRGB(aColor.setToRed())  == true);

  for(double i=0.0; i<1.0; i=i+0.001) // BOOST_TEST_CHECK x 1000
    BOOST_TEST_CHECK(mjr::colorRGBA8b::csCColdeRainbow::c(i).isEqualRGB(aColor.cmpRGBcornerCGradiant(i, "RYGCBMR")) == true);

  aColor.cmpRGBcornerCGradiant(10/1530.0, "RYGCBMR");
  BOOST_TEST_CHECK(aColor.getRed()   == 0xff);
  BOOST_TEST_CHECK(aColor.getGreen() == 10);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0);

////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  mjr::colorRGBA32F::csCColdeRainbow::c(bColor, 0.0F);
  BOOST_TEST_CHECK(bColor.getRed()   == mjr::colorRGBA32F::maxChanVal);
  BOOST_TEST_CHECK(bColor.getGreen() == mjr::colorRGBA32F::minChanVal);
  BOOST_TEST_CHECK(bColor.getBlue()  == mjr::colorRGBA32F::minChanVal);
  BOOST_TEST_CHECK(bColor.getAlpha() == mjr::colorRGBA32F::minChanVal); // Corner colors set ALL channels -- primary colors set them all to minChanVal

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(   0/1530.0).isEqualRGB(bColor.setToRed())     == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c( 255/1530.0).isEqualRGB(bColor.setToYellow())  == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c( 510/1530.0).isEqualRGB(bColor.setToGreen())   == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c( 765/1530.0).isEqualRGB(bColor.setToCyan())    == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(1020/1530.0).isEqualRGB(bColor.setToBlue())    == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(1275/1530.0).isEqualRGB(bColor.setToMagenta()) == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(1530/1530.0).isEqualRGB(bColor.setToRed())     == true);

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(2.0).isEqualRGB(bColor.setToRed())  == true);
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(3.0).isEqualRGB(bColor.setToRed())  == true);

  for(double i=0.0; i<1.0; i=i+0.001) // BOOST_TEST_CHECK x 1000
    BOOST_TEST_CHECK(mjr::colorRGBA32F::csCColdeRainbow::c(i).isEqualRGB(bColor.cmpRGBcornerCGradiant(i, "RYGCBMR")) == true);

  bColor.cmpRGBcornerCGradiant(10/1530.0, "RYGCBMR");
  BOOST_TEST_CHECK(bColor.getRed()   == 1);
  BOOST_TEST_CHECK(bColor.getGreen() == 0.0392156862745);
  BOOST_TEST_CHECK(bColor.getBlue()  == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(csCBSpectral_int) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 0,  3).isEqualRGB(aColor.setChansRGB(252, 141,  89))); // smallest
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 1,  3).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 2,  3).isEqualRGB(aColor.setChansRGB(153, 213, 148)));

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 0, 11).isEqualRGB(aColor.setChansRGB(158,   1,  66))); // biggest
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 1, 11).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 2, 11).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 3, 11).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 4, 11).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 5, 11).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 6, 11).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 7, 11).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 8, 11).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 9, 11).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(10, 11).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 3,  3).isEqualRGB(aColor.setChansRGB(252, 141,  89))); // wrap index
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 4,  3).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 5,  3).isEqualRGB(aColor.setChansRGB(153, 213, 148)));

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(11, 11).isEqualRGB(aColor.setChansRGB(158,   1,  66))); // wrap index
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(12, 11).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(13, 11).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(14, 11).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(15, 11).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(16, 11).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(17, 11).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(18, 11).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(19, 11).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(20, 11).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(21, 11).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 0    ).isEqualRGB(aColor.setChansRGB(158,   1,  66)));  // missing -> 11
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 1    ).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 2    ).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 3    ).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 4    ).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 5    ).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 6    ).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 7    ).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 8    ).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 9    ).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(10    ).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 0,  1).isEqualRGB(aColor.setChansRGB(252, 141,  89)));  // too small -> 3
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 1,  1).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 2,  1).isEqualRGB(aColor.setChansRGB(153, 213, 148)));

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 0, 50).isEqualRGB(aColor.setChansRGB(158,   1,  66)));  // too big -> 11
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 1, 50).isEqualRGB(aColor.setChansRGB(213,  62,  79)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 2, 50).isEqualRGB(aColor.setChansRGB(244, 109,  67)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 3, 50).isEqualRGB(aColor.setChansRGB(253, 174,  97)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 4, 50).isEqualRGB(aColor.setChansRGB(254, 224, 139)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 5, 50).isEqualRGB(aColor.setChansRGB(255, 255, 191)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 6, 50).isEqualRGB(aColor.setChansRGB(230, 245, 152)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 7, 50).isEqualRGB(aColor.setChansRGB(171, 221, 164)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 8, 50).isEqualRGB(aColor.setChansRGB(102, 194, 165)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 9, 50).isEqualRGB(aColor.setChansRGB( 50, 136, 189)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(10, 50).isEqualRGB(aColor.setChansRGB( 94,  79, 162)));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0, 3);
  BOOST_TEST_CHECK(aColor.getRed()   == 252);
  BOOST_TEST_CHECK(aColor.getGreen() == 141);
  BOOST_TEST_CHECK(aColor.getBlue()  ==  89);
  BOOST_TEST_CHECK(aColor.getAlpha() ==   mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0, 3);
  BOOST_TEST_CHECK(aColor.getRed()   ==  252);
  BOOST_TEST_CHECK(aColor.getGreen() ==  141);
  BOOST_TEST_CHECK(aColor.getBlue()  ==   89);
  BOOST_TEST_CHECK(aColor.getAlpha() == mjr::colorRGBA8b::maxChanVal); // Not set!

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 0,  3).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F)); // smallest
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 1,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 2,  3).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 0, 11).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F)); // biggest
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 1, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 2, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 3, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 4, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 5, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 6, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 7, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 8, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 9, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(10, 11).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 3,  3).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F)); // wrap index
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 4,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 5,  3).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(11, 11).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F)); // wrap index
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(12, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(13, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(14, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(15, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(16, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(17, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(18, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(19, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(20, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(21, 11).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 0    ).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // missing -> 11
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 1    ).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 2    ).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 3    ).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 4    ).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 5    ).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 6    ).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 7    ).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 8    ).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 9    ).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(10    ).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 0,  1).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F));  // too small -> 3
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 1,  1).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 2,  1).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 0, 50).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // too big -> 11
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 1, 50).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 2, 50).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 3, 50).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 4, 50).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 5, 50).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 6, 50).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 7, 50).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 8, 50).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 9, 50).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(10, 50).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0, 3);
  BOOST_TEST_CHECK(bColor.getAlpha() ==   mjr::colorRGBA32F::minChanVal); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0, 3);
  BOOST_TEST_CHECK(bColor.getAlpha() == mjr::colorRGBA32F::maxChanVal); // Not set!

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(csCBSpectral_flt) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(  0/2.0F,  3).isCloseRGB(aColor.setChansRGB(252, 141,  89), 2)); // smallest
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(  1/2.0F,  3).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(  2/2.0F,  3).isCloseRGB(aColor.setChansRGB(153, 213, 148), 2));

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 0/10.0F, 11).isCloseRGB(aColor.setChansRGB(158,   1,  66), 2)); // biggest
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 1/10.0F, 11).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 2/10.0F, 11).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 3/10.0F, 11).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 4/10.0F, 11).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 5/10.0F, 11).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 6/10.0F, 11).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 7/10.0F, 11).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 8/10.0F, 11).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 9/10.0F, 11).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(10/10.0F, 11).isCloseRGB(aColor.setChansRGB( 94,  79, 162), 2));

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(  3/2.0F,  3).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2)); // wrap index

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(1+ 1/10.0F, 11).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2)); // wrap index
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(1+ 2/10.0F, 11).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(1+ 3/10.0F, 11).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(1+ 4/10.0F, 11).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(1+ 5/10.0F, 11).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(1+ 6/10.0F, 11).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(1+ 7/10.0F, 11).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(1+ 8/10.0F, 11).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(1+ 9/10.0F, 11).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 0/10.0F    ).isCloseRGB(aColor.setChansRGB(158,   1,  66), 2));  // missing -> 11
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 1/10.0F    ).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 2/10.0F    ).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 3/10.0F    ).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 4/10.0F    ).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 5/10.0F    ).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 6/10.0F    ).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 7/10.0F    ).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 8/10.0F    ).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 9/10.0F    ).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(10/10.0F    ).isCloseRGB(aColor.setChansRGB( 94,  79, 162), 2));

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(  0/2.0F,  1).isCloseRGB(aColor.setChansRGB(252, 141,  89), 2));  // too small -> 3
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(  1/2.0F,  1).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(  2/2.0F,  1).isCloseRGB(aColor.setChansRGB(153, 213, 148), 2));

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 0/10.0F, 50).isCloseRGB(aColor.setChansRGB(158,   1,  66), 2));  // too big -> 11
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 1/10.0F, 50).isCloseRGB(aColor.setChansRGB(213,  62,  79), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 2/10.0F, 50).isCloseRGB(aColor.setChansRGB(244, 109,  67), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 3/10.0F, 50).isCloseRGB(aColor.setChansRGB(253, 174,  97), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 4/10.0F, 50).isCloseRGB(aColor.setChansRGB(254, 224, 139), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 5/10.0F, 50).isCloseRGB(aColor.setChansRGB(255, 255, 191), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 6/10.0F, 50).isCloseRGB(aColor.setChansRGB(230, 245, 152), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 7/10.0F, 50).isCloseRGB(aColor.setChansRGB(171, 221, 164), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 8/10.0F, 50).isCloseRGB(aColor.setChansRGB(102, 194, 165), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c( 9/10.0F, 50).isCloseRGB(aColor.setChansRGB( 50, 136, 189), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csCBSpectral::c(10/10.0F, 50).isCloseRGB(aColor.setChansRGB( 94,  79, 162), 2));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0/2.0F, 3);
  BOOST_TEST_CHECK(aColor.getAlpha() ==   mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csCBSpectral::c(aColor, 0/2.0F, 3);
  BOOST_TEST_CHECK(aColor.getAlpha() == mjr::colorRGBA8b::maxChanVal); // Not set!

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 0/2.0F,  3).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F)); // smallest
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 1/2.0F,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 2/2.0F,  3).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 0/10.0F, 11).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F)); // biggest
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 1/10.0F, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 2/10.0F, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 3/10.0F, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 4/10.0F, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 5/10.0F, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 6/10.0F, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 7/10.0F, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 8/10.0F, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 9/10.0F, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(10/10.0F, 11).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 3/2.0F,  3).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(1+1/10.0F, 11).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(1+2/10.0F, 11).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(1+3/10.0F, 11).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(1+4/10.0F, 11).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(1+5/10.0F, 11).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(1+6/10.0F, 11).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(1+7/10.0F, 11).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(1+8/10.0F, 11).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(1+9/10.0F, 11).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));

// ////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 0/10.0F    ).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // missing -> 11
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 1/10.0F    ).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 2/10.0F    ).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 3/10.0F    ).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 4/10.0F    ).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 5/10.0F    ).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 6/10.0F    ).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 7/10.0F    ).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 8/10.0F    ).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 9/10.0F    ).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(10/10.0F    ).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 0/2.0F,  1).isCloseRGB(bColor.setChansRGB(252/255.0F, 141/255.0F,  89/255.0F), 0.00001F));  // too small -> 3
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 1/2.0F,  1).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 2/2.0F,  1).isCloseRGB(bColor.setChansRGB(153/255.0F, 213/255.0F, 148/255.0F), 0.00001F));

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 0/10.0F, 50).isCloseRGB(bColor.setChansRGB(158/255.0F,   1/255.0F,  66/255.0F), 0.00001F));  // too big -> 11
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 1/10.0F, 50).isCloseRGB(bColor.setChansRGB(213/255.0F,  62/255.0F,  79/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 2/10.0F, 50).isCloseRGB(bColor.setChansRGB(244/255.0F, 109/255.0F,  67/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 3/10.0F, 50).isCloseRGB(bColor.setChansRGB(253/255.0F, 174/255.0F,  97/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 4/10.0F, 50).isCloseRGB(bColor.setChansRGB(254/255.0F, 224/255.0F, 139/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 5/10.0F, 50).isCloseRGB(bColor.setChansRGB(255/255.0F, 255/255.0F, 191/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 6/10.0F, 50).isCloseRGB(bColor.setChansRGB(230/255.0F, 245/255.0F, 152/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 7/10.0F, 50).isCloseRGB(bColor.setChansRGB(171/255.0F, 221/255.0F, 164/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 8/10.0F, 50).isCloseRGB(bColor.setChansRGB(102/255.0F, 194/255.0F, 165/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c( 9/10.0F, 50).isCloseRGB(bColor.setChansRGB( 50/255.0F, 136/255.0F, 189/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csCBSpectral::c(10/10.0F, 50).isCloseRGB(bColor.setChansRGB( 94/255.0F,  79/255.0F, 162/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0/2.0F, 3);
  BOOST_TEST_CHECK(bColor.getAlpha() ==   mjr::colorRGBA32F::minChanVal); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0/2.0F, 3);
  BOOST_TEST_CHECK(bColor.getAlpha() == mjr::colorRGBA32F::maxChanVal); // Not set!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(isClose_and_isCloseRGB) {

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

  BOOST_TEST_CHECK(aLcolor.isClose(aRcolor, 0)  == true);
  BOOST_TEST_CHECK(bLcolor.isClose(bRcolor, 0)  == true);
  BOOST_TEST_CHECK(cLcolor.isClose(cRcolor, 0)  == true);
  BOOST_TEST_CHECK(dLcolor.isClose(dRcolor, 0)  == true);

  BOOST_TEST_CHECK(aLcolor.isCloseRGB(aRcolor, 0)  == true);
  BOOST_TEST_CHECK(bLcolor.isCloseRGB(bRcolor, 0)  == true);
  BOOST_TEST_CHECK(cLcolor.isCloseRGB(cRcolor, 0)  == true);
  BOOST_TEST_CHECK(dLcolor.isCloseRGB(dRcolor, 0)  == true);

  aLcolor.setChanToMax(0);
  bLcolor.setChanToMax(0);
  cLcolor.setChanToMax(0);
  dLcolor.setChanToMax(0);

  BOOST_TEST_CHECK(aLcolor.isClose(aRcolor, 0)  == false);
  BOOST_TEST_CHECK(bLcolor.isClose(bRcolor, 0)  == false);
  BOOST_TEST_CHECK(cLcolor.isClose(cRcolor, 0)  == false);
  BOOST_TEST_CHECK(dLcolor.isClose(dRcolor, 0)  == false);

  BOOST_TEST_CHECK(aLcolor.isCloseRGB(aRcolor, 0)  == false);
  BOOST_TEST_CHECK(bLcolor.isCloseRGB(bRcolor, 0)  == false);
  BOOST_TEST_CHECK(cLcolor.isCloseRGB(cRcolor, 0)  == false);
  BOOST_TEST_CHECK(dLcolor.isCloseRGB(dRcolor, 0)  == false);

  aRcolor.setChanToMax(0);
  bRcolor.setChanToMax(0);
  cRcolor.setChanToMax(0);
  dRcolor.setChanToMax(0);

  BOOST_TEST_CHECK(aLcolor.isClose(aRcolor, 0)  == true);
  BOOST_TEST_CHECK(bLcolor.isClose(bRcolor, 0)  == true);
  BOOST_TEST_CHECK(cLcolor.isClose(cRcolor, 0)  == true);
  BOOST_TEST_CHECK(dLcolor.isClose(dRcolor, 0)  == true);

  BOOST_TEST_CHECK(aLcolor.isCloseRGB(aRcolor, 0)  == true);
  BOOST_TEST_CHECK(bLcolor.isCloseRGB(bRcolor, 0)  == true);
  BOOST_TEST_CHECK(cLcolor.isCloseRGB(cRcolor, 0)  == true);
  BOOST_TEST_CHECK(dLcolor.isCloseRGB(dRcolor, 0)  == true);

  bRcolor.setChanToMax(3);
  dRcolor.setChanToMax(3);

  BOOST_TEST_CHECK(bLcolor.isClose(bRcolor, 0)  == false);
  BOOST_TEST_CHECK(dLcolor.isClose(dRcolor, 0)  == false);

  BOOST_TEST_CHECK(bLcolor.isCloseRGB(bRcolor, 0)  == true);
  BOOST_TEST_CHECK(dLcolor.isCloseRGB(dRcolor, 0)  == true);

  aLcolor.setChansRGB(1, 2, 3);
  aRcolor.setChansRGB(1, 3, 4);

  BOOST_TEST_CHECK(aLcolor.isClose(aRcolor, 0)  == false);
  BOOST_TEST_CHECK(aRcolor.isClose(aLcolor, 0)  == false);

  BOOST_TEST_CHECK(aLcolor.isClose(aRcolor, 1)  == true);  // false only if a channel delta is GREATER THAN epsilon
  BOOST_TEST_CHECK(aRcolor.isClose(aLcolor, 1)  == true);

  BOOST_TEST_CHECK(aLcolor.isClose(aRcolor, 2)  == true);
  BOOST_TEST_CHECK(aRcolor.isClose(aLcolor, 2)  == true);

  cLcolor.setChansRGB(1, 2, 3);
  cRcolor.setChansRGB(1, 3, 4);

  BOOST_TEST_CHECK(cLcolor.isClose(cRcolor, 0.0F)  == false);
  BOOST_TEST_CHECK(cRcolor.isClose(cLcolor, 0.0F)  == false);

  BOOST_TEST_CHECK(cLcolor.isClose(cRcolor, 0.9999F)  == false);
  BOOST_TEST_CHECK(cRcolor.isClose(cLcolor, 0.9999F)  == false);

  BOOST_TEST_CHECK(cLcolor.isClose(cRcolor, 1.0F)  == true);  // Edge case is ill-defined for FP arithmetic, but OK here as we used numbers that are exactly representable -- might fail on other hardware.
  BOOST_TEST_CHECK(cRcolor.isClose(cLcolor, 1.0F)  == true);

  BOOST_TEST_CHECK(cLcolor.isClose(cRcolor, 1.0001F)  == true); 
  BOOST_TEST_CHECK(cRcolor.isClose(cLcolor, 1.0001F)  == true);

  BOOST_TEST_CHECK(cLcolor.isClose(cRcolor, 2.0F)  == true);
  BOOST_TEST_CHECK(cRcolor.isClose(cLcolor, 2.0F)  == true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(setRGBfromColorSpace) {

  mjr::colorRGB8b  aColor, bColor;
  mjr::colorRGBA8b cColor, dColor;
  mjr::colorRGB32F eColor, fColor;
  mjr::colorRGB16b gColor, hColor;

  ////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::RGB, 0, 0.5, 1);
  BOOST_TEST_CHECK(aColor.getRed()   == mjr::colorRGB8b::minChanVal);
  BOOST_TEST_CHECK(aColor.getGreen() == mjr::colorRGB8b::meanChanVal);
  BOOST_TEST_CHECK(aColor.getBlue()  == mjr::colorRGB8b::maxChanVal);

  eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::RGB, 0, 0.5, 1);
  BOOST_TEST_CHECK(eColor.getRed()   == mjr::colorRGB32F::minChanVal);
  BOOST_TEST_CHECK(eColor.getGreen() == mjr::colorRGB32F::meanChanVal);
  BOOST_TEST_CHECK(eColor.getBlue()  == mjr::colorRGB32F::maxChanVal);

  gColor.setRGBfromColorSpace(mjr::colorRGB16b::colorSpaceEnum::RGB, 0, 0.5, 1);
  BOOST_TEST_CHECK(gColor.getRed()   == mjr::colorRGB16b::minChanVal);
  BOOST_TEST_CHECK(gColor.getGreen() == mjr::colorRGB16b::meanChanVal);
  BOOST_TEST_CHECK(gColor.getBlue()  == mjr::colorRGB16b::maxChanVal);

  cColor.setToWhite();
  cColor.setRGBfromColorSpace(mjr::colorRGBA8b::colorSpaceEnum::RGB, 0, 0.5, 1);
  BOOST_TEST_CHECK(cColor.getRed()   == mjr::colorRGBA8b::minChanVal); 
  BOOST_TEST_CHECK(cColor.getGreen() == mjr::colorRGBA8b::meanChanVal);
  BOOST_TEST_CHECK(cColor.getBlue()  == mjr::colorRGBA8b::maxChanVal); 
  BOOST_TEST_CHECK(cColor.getAlpha() == 0xFF); // Not set

  cColor.setToBlack();
  cColor.setRGBfromColorSpace(mjr::colorRGBA8b::colorSpaceEnum::RGB, 0, 0.5, 1);
  BOOST_TEST_CHECK(cColor.getRed()   == mjr::colorRGBA8b::minChanVal); 
  BOOST_TEST_CHECK(cColor.getGreen() == mjr::colorRGBA8b::meanChanVal);
  BOOST_TEST_CHECK(cColor.getBlue()  == mjr::colorRGBA8b::maxChanVal); 
  BOOST_TEST_CHECK(cColor.getAlpha() == 0x00); // Not set

  for(double r=0; r<1.0; r=r+0.1)
    for(double g=0; g<1.0; g=g+0.1)
      for(double b=0; b<1.0; b=b+0.1) // BOOST_TEST_CHECK x 1000
        BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::RGB, r, g, b).isEqualRGB(bColor.setChansRGB_dbl(r, g, b)) == true);

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

  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(  0,   0,   0)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0, -100.0,    0.0).isEqualRGB(bColor.setChansRGB(  0,  42,   0)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,  100.0,    0.0).isEqualRGB(bColor.setChansRGB( 96,   0,   6)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,    0.0, -100.0).isEqualRGB(bColor.setChansRGB(  0,  28, 148)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,   0.0,    0.0,  100.0).isEqualRGB(bColor.setChansRGB( 52,   0,   0)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB, 100.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(255, 255, 254)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,   50.0,   50.0).isEqualRGB(bColor.setChansRGB(206,  75,  33)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,  -50.0,   50.0).isEqualRGB(bColor.setChansRGB( 35, 137,  16)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,  -50.0,  -50.0).isEqualRGB(bColor.setChansRGB(  0, 143, 203)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LAB,  50.0,   50.0,  -50.0).isEqualRGB(bColor.setChansRGB(157,  86, 204)) == true);

  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0, -100.0,    0.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,  42.50011693400831F/255.0F,   0.00000000000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,  100.0,    0.0).isCloseRGB(fColor.setChansRGB( 96.73833014676526F/255.0F,   0.00000000000000F/255.0F,   6.73101465756404F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,    0.0, -100.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,  28.17831280013103F/255.0F, 148.60141206787873F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,   0.0,    0.0,  100.0).isCloseRGB(fColor.setChansRGB( 52.41394321977139F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB, 100.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(255.00000000000000F/255.0F, 255.00000000000000F/255.0F, 254.98144635564927F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,   50.0,   50.0).isCloseRGB(fColor.setChansRGB(206.61345904246030F/255.0F,  75.47718797538901F/255.0F,  33.52976908891374F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,  -50.0,   50.0).isCloseRGB(fColor.setChansRGB( 35.14702068347071F/255.0F, 137.45770493758675F/255.0F,  16.12671766273848F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,  -50.0,  -50.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F, 143.15667349842120F/255.0F, 203.43118280505934F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB,  50.0,   50.0,  -50.0).isCloseRGB(fColor.setChansRGB(157.75797959913612F/255.0F,  86.69682271747450F/255.0F, 204.99202043092524F/255.0F), 0.00001F) == true);

  ////////////////////////////////////////////////////////////////////////////////
  //   0-1     0-1     0-1
  //   0.0,    0.0,    0.0            0.00000000000000,   0.00000000000000,   0.00000000000000
  //   1.0,    0.0,    0.0           50.42455181463890,   0.00000000000000,   1.83509220000000
  //   0.0,    1.0,    0.0            0.00000000000000,  37.29504496314512,   0.00000000000000
  //   0.0,    0.0,    1.0            0.00000000000000,   1.36725900000000,  26.38515827433519
  //   1.0,    1.0,    0.0           35.27435545247001,  23.88691519243730,   0.00000000000000
  //   1.0,    0.0,    1.0           46.09063114907088,   0.00000000000000,  27.25916547197178
  //   0.0,    1.0,    1.0            0.00000000000000,  37.76511040594671,  22.93126475355600

  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB( 0,   0,   0)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   1.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(50,   0,   1)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    1.0,    0.0).isEqualRGB(bColor.setChansRGB( 0,  37,   0)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    0.0,    1.0).isEqualRGB(bColor.setChansRGB( 0,   1,  26)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   1.0,    1.0,    0.0).isEqualRGB(bColor.setChansRGB(35,  23,   0)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   1.0,    0.0,    1.0).isEqualRGB(bColor.setChansRGB(46,   0,  27)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::XYZ,   0.0,    1.0,    1.0).isEqualRGB(bColor.setChansRGB( 0,  37,  22)) == true);

  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 1.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(50.42455181463890F/255.0F,   0.00000000000000F/255.0F,   1.83509220000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    1.0,    0.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,  37.29504496314512F/255.0F,   0.00000000000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    0.0,    1.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,   1.36725900000000F/255.0F,  26.38515827433519F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 1.0,    1.0,    0.0).isCloseRGB(fColor.setChansRGB(35.27435545247001F/255.0F,  23.88691519243730F/255.0F,   0.00000000000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 1.0,    0.0,    1.0).isCloseRGB(fColor.setChansRGB(46.09063114907088F/255.0F,   0.00000000000000F/255.0F,  27.25916547197178F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ, 0.0,    1.0,    1.0).isCloseRGB(fColor.setChansRGB( 0.00000000000000F/255.0F,  37.76511040594671F/255.0F,  22.93126475355600F/255.0F), 0.00001F) == true);

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

  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,    0.0,    0.0).isEqualRGB(bColor.setChansRGB(  0,   0,   0)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,  100.0,    0.0).isEqualRGB(bColor.setChansRGB( 96,   0,   6)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,   50.0,    0.0).isEqualRGB(bColor.setChansRGB( 57,   0,   2)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,    0.0,  180.0).isEqualRGB(bColor.setChansRGB(  0,   0,   0)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,   0.0,   50.0,  180.0).isEqualRGB(bColor.setChansRGB(  0,  28,   0)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH,  50.0,   50.0,  180.0).isEqualRGB(bColor.setChansRGB(  0, 139, 117)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH, 100.0,  100.0,  360.0).isEqualRGB(bColor.setChansRGB(255, 155, 255)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH, 100.0,  100.0,  180.0).isEqualRGB(bColor.setChansRGB(  0, 255, 252)) == true);
  BOOST_TEST_CHECK(aColor.setRGBfromColorSpace(mjr::colorRGB8b::colorSpaceEnum::LCH, 100.0,  100.0,   60.0).isEqualRGB(bColor.setChansRGB(255, 211,  78)) == true);

  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,    0.0,    0.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,  100.0,    0.0).isCloseRGB(fColor.setChansRGB( 96.73833014676526F/255.0F,   0.00000000000000F/255.0F,   6.73101465756404F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,   50.0,    0.0).isCloseRGB(fColor.setChansRGB( 57.41225747257089F/255.0F,   0.00000000000000F/255.0F,   2.34936006058456F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,    0.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,   0.00000000000000F/255.0F,   0.00000000000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,   0.0,   50.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F,  28.32099136175329F/255.0F,   0.00000000000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH,  50.0,   50.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F, 139.16169169667540F/255.0F, 117.60474230139480F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH, 100.0,  100.0,  360.0).isCloseRGB(fColor.setChansRGB(255.00000000000000F/255.0F, 155.40224018978810F/255.0F, 255.00000000000000F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH, 100.0,  100.0,  180.0).isCloseRGB(fColor.setChansRGB(  0.00000000000000F/255.0F, 255.00000000000000F/255.0F, 252.06306109593692F/255.0F), 0.00001F) == true);
  BOOST_TEST_CHECK(eColor.setRGBfromColorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH, 100.0,  100.0,   60.0).isCloseRGB(fColor.setChansRGB(255.00000000000000F/255.0F, 211.98994181103800F/255.0F,  78.02765922273178F/255.0F), 0.00001F) == true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(rgb2colorSpace) {

  mjr::colorRGB8b                aColor;
  mjr::colorRGB8b::colSpaceDbl3  bColor;
  mjr::colorRGB32F               cColor;
  mjr::colorRGB32F::colSpaceDbl3 dColor;
  mjr::colorRGB16b               eColor;
  mjr::colorRGB16b::colSpaceDbl3 fColor;
  mjr::colorRGB32b               gColor;
  mjr::colorRGB32b::colSpaceDbl3 hColor;

  ////////////////////////////////////////////////////////////////////////////////

  aColor.setChansRGB(mjr::colorRGB8b::minChanVal, mjr::colorRGB8b::meanChanVal, mjr::colorRGB8b::maxChanVal);
  bColor = aColor.rgb2colorSpace(mjr::colorRGB8b::colorSpaceEnum::RGB);
  BOOST_TEST_CHECK(bColor.getC0() == 0.0,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(bColor.getC1() == 0.5,    boost::test_tools::tolerance(0.01));        // Can't get much accuracy with 8-bit
  BOOST_TEST_CHECK(bColor.getC2() == 1.0,    boost::test_tools::tolerance(0.00001));

  eColor.setChansRGB(mjr::colorRGB16b::minChanVal, mjr::colorRGB16b::meanChanVal, mjr::colorRGB16b::maxChanVal);
  fColor = eColor.rgb2colorSpace(mjr::colorRGB16b::colorSpaceEnum::RGB);
  BOOST_TEST_CHECK(fColor.getC0() == 0.0,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(fColor.getC1() == 0.5,    boost::test_tools::tolerance(0.0001));      // A bit more accuracy with 16-bit
  BOOST_TEST_CHECK(fColor.getC2() == 1.0,    boost::test_tools::tolerance(0.00001));

  gColor.setChansRGB(mjr::colorRGB32b::minChanVal, mjr::colorRGB32b::meanChanVal, mjr::colorRGB32b::maxChanVal);
  hColor = gColor.rgb2colorSpace(mjr::colorRGB32b::colorSpaceEnum::RGB);
  BOOST_TEST_CHECK(hColor.getC0() == 0.0,    boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(hColor.getC1() == 0.5,    boost::test_tools::tolerance(0.00001));     // A bit more accuracy with 32-bit
  BOOST_TEST_CHECK(hColor.getC2() == 1.0,    boost::test_tools::tolerance(0.00001));

  ////////////////////////////////////////////////////////////////////////////////

  //   0.00000000000000   0.5000000000000000   1.00000000000000000 RGB 
  // 210.11764705181122   1.0000000000000000   0.50000000000000000 HSL
  // 210.11764705181122   1.0000000000000000   1.00000000000000000 HSV
  //  54.58302990500775  19.1017817806751750 -71.14430025970830000 LAB
  //  25.704111183644635 22.5282223672892700  97.60137039454821000 XYZ
  //  54.58302990500775  73.6640314308147600 285.02909316255295000 LCH

  cColor.setChansRGB(mjr::colorRGB32F::minChanVal, mjr::colorRGB32F::meanChanVal, mjr::colorRGB32F::maxChanVal);

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::RGB);
  BOOST_TEST_CHECK(dColor.getC0() ==   0.000000000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC1() ==   0.500000000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC2() ==   1.000000000000000, boost::test_tools::tolerance(0.00001));

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::HSL);
  BOOST_TEST_CHECK(dColor.getC0() == 210.000000000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC1() ==   1.000000000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC2() ==   0.500000000000000, boost::test_tools::tolerance(0.00001));

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::HSV);
  BOOST_TEST_CHECK(dColor.getC0() == 210.000000000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC1() ==   1.000000000000000, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC2() ==   1.000000000000000, boost::test_tools::tolerance(0.00001));

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::LAB);
  BOOST_TEST_CHECK(dColor.getC0() ==  54.583029905007749, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC1() ==  19.106431157445371, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC2() == -71.140167945193781, boost::test_tools::tolerance(0.00001));

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::XYZ);
  BOOST_TEST_CHECK(dColor.getC0() ==  25.704111183644635, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC1() ==  22.528222367289271, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC2() ==  97.601370394548212, boost::test_tools::tolerance(0.00001));

  dColor = cColor.rgb2colorSpace(mjr::colorRGB32F::colorSpaceEnum::LCH);
  BOOST_TEST_CHECK(dColor.getC0() ==  54.583029905007749, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC1() ==  73.661246302547553, boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(dColor.getC2() == 285.033419356169360, boost::test_tools::tolerance(0.00001));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(csFPcircular12_int) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 0).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x00)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 1).isEqualRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 2).isEqualRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 3).isEqualRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 4).isEqualRGB(aColor.setChansRGB(0x66, 0xCC, 0x00)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 5).isEqualRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 6).isEqualRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 7).isEqualRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 8).isEqualRGB(aColor.setChansRGB(0x00, 0x00, 0xFF)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 9).isEqualRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(10).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(11).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x7D)));

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(12).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x00))); // wrap
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(13).isEqualRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(14).isEqualRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(15).isEqualRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(16).isEqualRGB(aColor.setChansRGB(0x66, 0xCC, 0x00)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(17).isEqualRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(18).isEqualRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(19).isEqualRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(20).isEqualRGB(aColor.setChansRGB(0x00, 0x00, 0xFF)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(21).isEqualRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(22).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF)));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(23).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x7D)));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0);
  BOOST_TEST_CHECK(aColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(aColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() ==   mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0);
  BOOST_TEST_CHECK(aColor.getRed()   ==  0xFF);
  BOOST_TEST_CHECK(aColor.getGreen() ==  0x00);
  BOOST_TEST_CHECK(aColor.getBlue()  ==  0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == mjr::colorRGBA8b::maxChanVal); // Not set!

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 0).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x00/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 1).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x7D/255.0F, 0x00/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 2).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 3).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 4).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xCC/255.0F, 0x00/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 5).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xFF/255.0F, 0xB2/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 6).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0xFF/255.0F, 0xFF/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 7).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x7D/255.0F, 0xFF/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 8).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 9).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c(10).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c(11).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x7D/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0);
  BOOST_TEST_CHECK(bColor.getAlpha() ==   mjr::colorRGBA32F::minChanVal); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0);
  BOOST_TEST_CHECK(bColor.getAlpha() == mjr::colorRGBA32F::maxChanVal); // Not set!

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(csCBSpectral_flt) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 0/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0x00), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 1/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 2/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 3/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 4/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xCC, 0x00), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 5/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 6/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 7/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 8/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x00, 0xFF), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c( 9/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(10/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(11/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0x7D), 2));

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(1+ 1/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00), 2)); // wrap
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(1+ 2/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(1+ 3/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(1+ 4/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xCC, 0x00), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(1+ 5/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(1+ 6/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(1+ 7/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(1+ 8/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x00, 0xFF), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(1+ 9/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF), 2));
  BOOST_TEST_CHECK(mjr::colorRGBA8b::csFPcircular12::c(1+10/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF), 2));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0.0F);
  BOOST_TEST_CHECK(aColor.getRed()   == 0xFF);
  BOOST_TEST_CHECK(aColor.getGreen() == 0x00);
  BOOST_TEST_CHECK(aColor.getBlue()  == 0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() ==   mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0.0F);
  BOOST_TEST_CHECK(aColor.getRed()   ==  0xFF);
  BOOST_TEST_CHECK(aColor.getGreen() ==  0x00);
  BOOST_TEST_CHECK(aColor.getBlue()  ==  0x00);
  BOOST_TEST_CHECK(aColor.getAlpha() == mjr::colorRGBA8b::maxChanVal); // Not set!

////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 0/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x00/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 1/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x7D/255.0F, 0x00/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 2/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 3/11.0F).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 4/11.0F).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xCC/255.0F, 0x00/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 5/11.0F).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xFF/255.0F, 0xB2/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 6/11.0F).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0xFF/255.0F, 0xFF/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 7/11.0F).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x7D/255.0F, 0xFF/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 8/11.0F).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c( 9/11.0F).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c(10/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  BOOST_TEST_CHECK(mjr::colorRGBA32F::csFPcircular12::c(11/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x7D/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0.0F);
  BOOST_TEST_CHECK(bColor.getAlpha() ==   mjr::colorRGBA32F::minChanVal); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0.0F);
  BOOST_TEST_CHECK(bColor.getAlpha() == mjr::colorRGBA32F::maxChanVal); // Not set!
}

#endif



/** @endcond */


// So far:  3967 hand written test cases
// So far: 70067 generated test cases
