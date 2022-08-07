#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

#include "ramCanvas.hpp"

// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | Method
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl();
// | ** | colorTpl(const colorType& aColor);
// | ** | colorTpl(clrChanT c1, clrChanT c2, clrChanT c3, clrChanT c4);
// | ** | colorTpl(clrChanT c1, clrChanT c2, clrChanT c3);
// | ** | colorTpl(clrChanT c1, clrChanT c2);
// | ** | colorTpl(clrChanT cVal);
// | ** | colorTpl(cornerColorEnum cornerColor);
// | ** | colorTpl(std::string colorString);
// | ** | colorTpl(const char* colorCString);
// | -- | ~colorTpl();
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// | -- | colorTpl& copy(colorArgType aCol);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// | ** | clrChanT getC0() const;
// | ** | clrChanT getC1() const requires (numChan>1);
// | ** | clrChanT getC2() const requires (numChan>2);
// | ** | clrChanT getC3() const requires (numChan>3);
// | ** | clrChanT getChan(int chan) const;
// | ** | colorTpl& setC0(clrChanT cVal);
// | ** | colorTpl& setC1(clrChanT cVal) requires (numChan>1);;
// | ** | colorTpl& setC2(clrChanT cVal) requires (numChan>2);;
// | ** | colorTpl& setC3(clrChanT cVal) requires (numChan>3);;
// | ** | colorTpl& setChan(int chan, clrChanT cVal);
// | -- | colorTpl& setChanToMax(int chan);
// | -- | colorTpl& setChanToMin(int chan);
// | ** | colorTpl& setChans(clrChanT c1, clrChanT c2, clrChanT c3, clrChanT c4);
// | ** | colorTpl& setChans(clrChanT c1, clrChanT c2, clrChanT c3);
// | ** | colorTpl& setChans(clrChanT c1, clrChanT c2);
// | ** | colorTpl& setChans(clrChanT cVal);
// |    | colorTpl& setChans(std::tuple<clrChanT, clrChanT, clrChanT, clrChanT> chanValues);
// |    | colorTpl& setChans(std::tuple<clrChanT, clrChanT, clrChanT> chanValues);
// |    | colorTpl& setChans(std::vector<clrChanT>& chanValues);
// | ** | colorTpl& setChans(std::string colorHexString, bool clearUndefinedChannels = false);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// | ** | double getC0_dbl() const;
// | ** | double getC1_dbl() const;
// | ** | double getC2_dbl() const;
// | ** | double getC3_dbl() const;
// | ** | double getChan_dbl(int chan) const;
// | ** | colorTpl& setChan_dbl(int chan, double cVal);
// | ** | colorTpl& setC0_dbl(double cVal);
// | ** | colorTpl& setC1_dbl(double cVal);
// | ** | colorTpl& setC2_dbl(double cVal);
// | ** | colorTpl& setC3_dbl(double cVal);
// | ** | colorTpl& setChans_dbl(double c1, double c2, double c3, double c4);
// | ** | colorTpl& setChans_dbl(double c1, double c2, double c3);
// | ** | colorTpl& setChans_dbl(double c1, double c2);
// | ** | colorTpl& setChans_dbl(double cVal);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// | ** | uint8_t getC0_byte() const;
// | ** | uint8_t getC1_byte() const;
// | ** | uint8_t getC2_byte() const;
// | ** | uint8_t getC3_byte() const;
// | ** | uint8_t getChan_byte(int chan) const;
// | ** | colorTpl& setChan_byte(int chan, uint8_t cVal);
// | ** | colorTpl& setC0_byte(uint8_t cVal);
// | ** | colorTpl& setC1_byte(uint8_t cVal);
// | ** | colorTpl& setC2_byte(uint8_t cVal);
// | ** | colorTpl& setC3_byte(uint8_t cVal);
// | ** | colorTpl& setChans_byte(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4);
// | ** | colorTpl& setChans_byte(uint8_t c1, uint8_t c2, uint8_t c3);
// | ** | colorTpl& setChans_byte(uint8_t c1, uint8_t c2);
// | ** | colorTpl& setChans_byte(uint8_t cVal);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// | -- | colorTpl& setToBlack();
// | -- | colorTpl& setToWhite();
// | -- | colorTpl& setToRed();
// | -- | colorTpl& setToBlue();
// | -- | colorTpl& setToGreen();
// | -- | colorTpl& setToCyan();
// | -- | colorTpl& setToYellow();
// | -- | colorTpl& setToMagenta();
// | ** | colorTpl& setToCorner(char cornerColor);
// | ** | colorTpl& setToCorner(cornerColorEnum cornerColor);
// | ** | colorTpl& setToCorner(std::string cornerColor);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& setRGBAfromLogPackIntABGR(uint32_t anInt);
// |    | colorTpl& setRGBfromLogPackIntABGR(uint32_t anInt);
// |    | colorTpl& setRGBAfromLogPackIntARGB(uint32_t anInt);
// |    | colorTpl& setRGBfromLogPackIntARGB(uint32_t anInt);
// |    | colorTpl& setRGBAfromLogPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx);
// |    | colorTpl& setRGBfromLogPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx);
// |    | colorTpl& setRGBAfromPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx);
// |    | colorTpl& setRGBfromPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& setRGBfromUnitHSV(double H, double S, double V);
// |    | colorTpl& setRGBfromUnitHSL(double H, double S, double L);
// |    | colorTpl& setRGBfromColorSpace(colorSpaceEnum space, double inCh1, double inCh2, double inCh3);
// |    | colorTpl& setRGBfromColorSpace(colorSpaceEnum space, colorTpl<double, 3> inColor);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& setRGBcmpGreyTGA16bit(uint16_t tga16val);
// |    | colorTpl& setRGBcmpGreyTGA24bit(uint32_t tga24val);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& setRGBfromWavelengthCM(double wavelength, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR);
// |    | colorTpl& setRGBfromWavelengthLA(double wavelength);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& cmpGradiant(double aDouble, std::vector<double> const& anchors, std::vector<colorType> const& colors);
// |    | colorTpl& cmpGradiant(double aDouble, std::vector<colorType> const& colors);
// |    | colorTpl& cmpRGBcornerGradiant(csIntType csIdx, const char *cornerColors);
// |    | colorTpl& cmpRGBcornerGradiant(csIntType csIdx, csIntType numColors, const char *cornerColors);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& interplColors(double aDouble, colorArgType col1, colorArgType col2);
// |    | colorTpl& interplColorSpace(colorSpaceEnum space, double aDouble, colorArgType col1, colorArgType col2);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& wMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3, channelArithFltType w4, colorArgType col1, colorArgType col2, colorArgType col3, colorArgType col4);
// |    | colorTpl& wMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3, colorArgType col1, colorArgType col2, colorArgType col3);
// |    | colorTpl& wMean(channelArithFltType w1, channelArithFltType w2, colorArgType col1, colorArgType col2);
// |    | colorTpl& uMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3, colorArgType col1, colorArgType col2, colorArgType col3, colorArgType col4);
// |    | colorTpl& uMean(channelArithFltType w1, channelArithFltType w2, colorArgType col1, colorArgType col2, colorArgType col3);
// |    | colorTpl& uMean(channelArithFltType w1, colorArgType col1, colorArgType col2);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& tfrmOr(colorArgType aCol) requires (std::integral<clrChanT>);
// |    | colorTpl& tfrmOr(colorArgType aCol) requires (std::floating_point<clrChanT>);
// |    | colorTpl& tfrmNor(colorArgType aCol) requires (std::integral<clrChanT>);
// |    | colorTpl& tfrmNor(colorArgType aCol) requires (std::floating_point<clrChanT>);
// |    | colorTpl& tfrmAnd(colorArgType aCol) requires (std::integral<clrChanT>);
// |    | colorTpl& tfrmAnd(colorArgType aCol) requires (std::floating_point<clrChanT>);
// |    | colorTpl& tfrmNand(colorArgType aCol) requires (std::integral<clrChanT>);
// |    | colorTpl& tfrmNand(colorArgType aCol) requires (std::floating_point<clrChanT>);
// |    | colorTpl& tfrmXor(colorArgType aCol) requires (std::integral<clrChanT>);
// |    | colorTpl& tfrmXor(colorArgType aCol) requires (std::floating_point<clrChanT>);
// |    | colorTpl& tfrmNxor(colorArgType aCol) requires (std::integral<clrChanT>);
// |    | colorTpl& tfrmNxor(colorArgType aCol) requires (std::floating_point<clrChanT>);
// |    | colorTpl& tfrmNot(void) requires (std::integral<clrChanT>);
// |    | colorTpl& tfrmNot(void) requires (std::floating_point<clrChanT>);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& tfrmSqDiff(colorArgType aCol);
// |    | colorTpl& tfrmAbsDiff(colorArgType aCol);
// |    | colorTpl& tfrmAdd(colorArgType aCol);
// |    | colorTpl& tfrmDiv(colorArgType aCol);
// |    | colorTpl& tfrmMult(colorArgType aCol);
// |    | colorTpl& tfrmMultClp(colorArgType aCol);
// |    | colorTpl& ScaleSignDiff(colorArgType aCol);
// |    | colorTpl& tfrmDiffClp(colorArgType aCol);
// |    | colorTpl& tfrmNegDiffClp(colorArgType aCol);
// |    | colorTpl& tfrmAddClp(colorArgType aCol);
// |    | colorTpl& tfrmAddDivClp(colorArgType aCol, colorArgType dCol);
// |    | colorTpl& tfrmDiff(colorArgType aCol);
// |    | colorTpl& tfrmMod(colorArgType aCol) requires (std::integral<clrChanT>);
// |    | colorTpl& tfrmMod(colorArgType aCol) requires (std::floating_point<clrChanT>);
// |    | colorTpl& tfrmInvert();
// |    | colorTpl& tfrmLn();
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& interplColors(double aDouble, colorArgType tooCol);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& tfrmCopy(colorArgType aCol);
// |    | colorTpl& tfrmMaxI(colorArgType aCol);
// |    | colorTpl& tfrmMinI(colorArgType aCol);
// |    | colorTpl& tfrmMax(colorArgType aCol);
// |    | colorTpl& tfrmMin(colorArgType aCol);
// |    | colorTpl& tfrmShiftL(colorArgType aCol) requires (std::integral<clrChanT>);
// |    | colorTpl& tfrmShiftL(colorArgType aCol) requires (std::floating_point<clrChanT>);
// |    | colorTpl& tfrmShiftR(colorArgType aCol) requires (std::integral<clrChanT>);
// |    | colorTpl& tfrmShiftR(colorArgType aCol) requires (std::floating_point<clrChanT>);
// |    | colorTpl& tfrmSaw(colorArgType lowCol, colorArgType highCol);
// |    | colorTpl& tfrmStep(colorArgType lowCol, colorArgType highCol);
// |    | colorTpl& tfrmDiracTot(colorArgType aCol);
// |    | colorTpl& tfrmDirac(colorArgType aCol);
// |    | colorTpl& tfrmFuzzyDirac(colorArgType ctrCol, colorArgType radCol);
// |    | colorTpl& tfrmMean(colorArgType aCol);
// |    | colorTpl& tfrmGmean(colorArgType aCol);
// |    | colorTpl& tfrmGmeanClp(colorArgType aCol);
// |    | colorTpl& tfrmGreyScale(void);
// |    | colorTpl& tfrmWebSafe216();
// |    | colorTpl& tfrmWebSafePro216();
// |    | colorTpl& tfrmWebSafeDeu216();
// |    | colorTpl& tfrmWebSafeTri216();
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl<double, 3> rgb2colorSpace(colorSpaceEnum space);
// |    | std::string colorSpaceToString(colorSpaceEnum space);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& tfrmLinearGreyLevelScale(double c, double b);
// |    | colorTpl& tfrmLinearGreyLevelScale(colorArgType from1, colorArgType from2, colorArgType to1, colorArgType to2);
// |    | colorTpl& tfrmLinearGreyLevelScale(double rc, double rb, double gc, double gb, double bc, double bb);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | colorTpl& tfrmStdPow(double p);
// |    | colorTpl& tfrmStdPow(double rp, double gp, double bp);
// |    | colorTpl& tfrmStdPowSqr(void);
// |    | colorTpl& tfrmStdPowSqrt(void);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | channelArithSDPType rgb2GreyDotProd(channelArithSDPType redWt, channelArithSDPType greenWt, channelArithSDPType blueWt);
// |    | channelArithFltType rgbLuminance(void);
// |    | channelArithSPType rgbSumIntensity(void);
// |    | channelArithSPType sumIntensity(void);
// |    | channelArithFltType rgbScaledIntensity(void);
// |    | channelArithFltType sumScaledIntensity(void);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | clrChanT getMaxC();
// |    | clrChanT getMinC();
// |    | clrChanT getMaxRGB();
// |    | clrChanT getMinRGB();
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | channelArithSPType dotProd(colorArgType aColor);
// |    | channelArithSPType distP2sq(colorArgType aColor);
// |    | channelArithSPType distAbs(colorArgType aColor);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | bool isEqual(colorArgType aColor);
// |    | bool isEqualRGB(colorArgType aColor);
// |    | bool isNotEqual(colorArgType aColor);
// |    | bool isBlack();
// |    | bool isBlackRGB();
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// |    | template <typename iT> clrChanT clipTop(iT arithValue);
// |    | template <typename iT> clrChanT clipBot(iT arithValue);
// |    | template <typename iT> clrChanT clipAll(iT arithValue);
// +----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_dbl_8) {

  mjr::color4c8b aColor;

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 127);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 127.0/255, boost::test_tools::tolerance(0.005));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 255);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0);
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
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 127.0/255, boost::test_tools::tolerance(0.005));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 127.0/255, boost::test_tools::tolerance(0.005));

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 255);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 32767);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 32767.0/65535);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 65535);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0);
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
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 32767.0/65535, boost::test_tools::tolerance(0.005));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 32767.0/65535, boost::test_tools::tolerance(0.005));

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 65535);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0);

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

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.5);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 0.0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.0);

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

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == 0.0);
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == 0.0);

  BOOST_TEST_CHECK(aColor.getChan_dbl(0)  == aColor.getC0_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(1)  == aColor.getC1_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(2)  == aColor.getC2_dbl(), boost::test_tools::tolerance(0.00001));
  BOOST_TEST_CHECK(aColor.getChan_dbl(3)  == aColor.getC3_dbl(), boost::test_tools::tolerance(0.00001));

  aColor.setChans_dbl(1.0);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 1.0);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 0.0);
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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 0.0);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 1.0);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 0.0);

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
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(set_chan_byte_16) {

  mjr::color4c16b aColor;

  aColor.setToBlack();
  aColor.setChan_byte(0, 11);
  aColor.setChan_byte(1, 22);
  aColor.setChan_byte(2, 33);
  aColor.setChan_byte(3, 44);

  BOOST_TEST_CHECK(aColor.getChan(0)      == 2816);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 5632);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 8448);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 11264);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 14080);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 16896);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 19712);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 22528);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 25344);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 25344);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 25344);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 25344);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 8448);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 11264);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 14080);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 25344);

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

  BOOST_TEST_CHECK(aColor.getChan(0)      == 2816);
  BOOST_TEST_CHECK(aColor.getChan(1)      == 5632);
  BOOST_TEST_CHECK(aColor.getChan(2)      == 8448);
  BOOST_TEST_CHECK(aColor.getChan(3)      == 11264);

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

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 4);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 8);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 16);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 32);

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

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 32);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 16); 
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 8);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 4);

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

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 128);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 128);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 128);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 128);

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

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 16);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 32);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 64);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 128);

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

  BOOST_TEST_CHECK(aColor.getChan_byte(0) == 4);
  BOOST_TEST_CHECK(aColor.getChan_byte(1) == 8);
  BOOST_TEST_CHECK(aColor.getChan_byte(2) == 16);
  BOOST_TEST_CHECK(aColor.getChan_byte(3) == 32);

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

