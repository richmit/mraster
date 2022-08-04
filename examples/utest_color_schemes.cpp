#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

#include "ramCanvas.hpp"

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
}

BOOST_AUTO_TEST_CASE(cmpRGBcornerGradiant_csCColdeRainbow, * boost::unit_test::tolerance(0.01)) {
  // for(csIt x=0;x<ct::csCColdeRainbow::numC;x++) 
  //   ct::csCColdeRainbow::c(x) === ct().cmpRGBcornerGradiant(x, "RYGCBMR");    
}
