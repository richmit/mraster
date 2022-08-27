// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      utest_ramCanvasTpl.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-08-24
 @brief     unit tests for ramCanvasTpl.@EOL
 @keywords
 @std       C++20
 @see
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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

#include "ramCanvas.hpp"
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <fstream>
#include <iterator>

#if 1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(draw_primatives_int) {

  // We instantiate every drawing function in ramCanvas so that we can check for compile time errors and do some basic functionality testing.

  const int BSIZE = 60;

  mjr::ramCanvasRGB8b aRamCanvas(BSIZE, BSIZE, 0, BSIZE-1, 0, BSIZE-1);
  mjr::colorRGB8b aColor(mjr::colorRGB8b::cornerColorEnum::RED);
  mjr::colorRGB8b bColor(mjr::colorRGB8b::cornerColorEnum::GREEN);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawPoint(1, 1, aColor);                                                      // drawPoint(iCrd x, iCrd y, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.moveTo(2, 1);
  aRamCanvas.drawPoint();                                                                  // drawPoint();
  aRamCanvas.moveTo(3, 1);
  aRamCanvas.drawPoint(aColor);                                                            // drawPoint(clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPoint(4, 1);                                                              // drawPoint(iCrd x, iCrd y);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawPoint(5.0, 2.0);                                                          // drawPoint(fCrd x, fCrd y);
  aRamCanvas.drawPoint(6.0, 2.0, bColor);                                                  // drawPoint(fCrd x, fCrd y, clr color);
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType({7, 1}), aColor);                 // drawPoint(iPnt thePoint, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType({8, 1}));                         // drawPoint(iPnt thePoint);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType({9.0, 2.0}));                     // drawPoint(fPnt thePoint);
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType({10.0, 2.0}), bColor);            // drawPoint(fPnt thePoint, clr color);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawLine(1, 4, 1, 6, aColor);                                                 // drawLine(iCrd x1, iCrd y1, iCrd x2, iCrd y2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.moveTo(2, 4);
  aRamCanvas.drawLine(2, 6);                                                               // drawLine(iCrd x,  iCrd y);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.moveTo(3.0, 5.0);
  aRamCanvas.drawLine(3.0, 7.0);                                                           // drawLine(fCrd x,  fCrd y);
  aRamCanvas.moveTo(4, 4);
  aRamCanvas.drawLine(4, 6, bColor);                                                       // drawLine(iCrd x,  iCrd y,  clr color);
  aRamCanvas.moveTo(5.0, 5.0);
  aRamCanvas.drawLine(5.0, 7.0, aColor);                                                   // drawLine(fCrd x,  fCrd y,  clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawLine(6, 4, 6, 6);                                                         // drawLine(iCrd x1, iCrd y1, iCrd x2, iCrd y2);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawLine(7.0, 5.0, 7.0, 7.0);                                                 // drawLine(fCrd x1, fCrd y1, fCrd x2, fCrd y2);
  aRamCanvas.drawLine(8.0, 5.0, 8.0, 7.0, bColor);                                         // drawLine(fCrd x1, fCrd y1, fCrd x2, fCrd y2, clr color);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.moveTo(mjr::ramCanvasRGB8b::pointFltType({9.0, 5.0}));
  aRamCanvas.drawLine(mjr::ramCanvasRGB8b::pointFltType({9.0, 7.0}));                      // drawLine(fPnt point1);
  aRamCanvas.moveTo(10.0, 5.0);
  aRamCanvas.drawLine(mjr::ramCanvasRGB8b::pointFltType({10.0, 7.0}), bColor);             // drawLine(fPnt point1, clr color);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.moveTo(11, 4);
  aRamCanvas.drawLine(mjr::ramCanvasRGB8b::pointIntType({11, 6}));                         // drawLine(iPnt point1);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.moveTo(mjr::ramCanvasRGB8b::pointIntType({12, 4}));
  aRamCanvas.drawLine(mjr::ramCanvasRGB8b::pointIntType({12, 6}), aColor);                 // drawLine(iPnt point1, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawLine(mjr::ramCanvasRGB8b::pointFltType({13, 5.0}),
                        mjr::ramCanvasRGB8b::pointFltType({13, 7.0}));                       // drawLine(fPnt point1, fPnt point2);
  aRamCanvas.drawLine(mjr::ramCanvasRGB8b::pointFltType({14, 5.0}),
                        mjr::ramCanvasRGB8b::pointFltType({14, 7.0}), aColor);               // drawLine(fPnt point1, fPnt point2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawLine(mjr::ramCanvasRGB8b::pointIntType({15, 4}),
                        mjr::ramCanvasRGB8b::pointIntType({15, 6}));                         // drawLine(iPnt point1, iPnt point2);
  aRamCanvas.drawLine(mjr::ramCanvasRGB8b::pointIntType({16, 5}),
                        mjr::ramCanvasRGB8b::pointIntType({16, 6}), aColor);                 // drawLine(iPnt point1, iPnt point2, clr color);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawTriangle(1, 9, 4, 9, 4, 12,  aColor);                                     // drawTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3,
                                                                                             //              clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(6, 9, 9, 9, 9, 12);                                              // drawTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3);
  aRamCanvas.drawTriangle(11.0, 10.0, 14.0, 10.0, 14.0, 13.0,  aColor);                    // drawTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3,
                                                                                             //              clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(16.0, 10.0, 19.0, 10.0, 19.0, 13.0);                             // drawTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3);
  aRamCanvas.drawTriangle(mjr::ramCanvasRGB8b::pointIntType({1, 14}),
                            mjr::ramCanvasRGB8b::pointIntType({4, 14}),
                            mjr::ramCanvasRGB8b::pointIntType({4, 17}),  aColor);            // drawTriangle(iPnt point1, iPnt point2, iPnt point3, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(mjr::ramCanvasRGB8b::pointIntType({6, 14}),
                            mjr::ramCanvasRGB8b::pointIntType({9, 14}),
                            mjr::ramCanvasRGB8b::pointIntType({9, 17}));                     // drawTriangle(iPnt point1, iPnt point2, iPnt point3);
  aRamCanvas.drawTriangle(mjr::ramCanvasRGB8b::pointFltType({11.0, 15.0}),
                            mjr::ramCanvasRGB8b::pointFltType({14.0, 15.0}),
                            mjr::ramCanvasRGB8b::pointFltType({14.0, 18.0}),  aColor);       // drawTriangle(fPnt point1, fPnt point2, fPnt point3, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(mjr::ramCanvasRGB8b::pointFltType({16.0, 15.0}),
                            mjr::ramCanvasRGB8b::pointFltType({19.0, 15.0}),
                            mjr::ramCanvasRGB8b::pointFltType({19.0, 18.0}));                // drawTriangle(fPnt point1, fPnt point2, fPnt point3);
  mjr::ramCanvasRGB8b::pointIntType ptl1[3] = { {1, 19}, {4, 19}, {4, 22} };
  aRamCanvas.drawTriangle(ptl1, aColor);                                                   // drawTriangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::pointIntType ptl2[3] = { {6, 19}, {9, 19}, {9, 22} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(ptl2);                                                           // drawTriangle(iPnt *thePoints);
  mjr::ramCanvasRGB8b::pointFltType ptl3[3] = { {11.0, 20.0},
                                                {14.0, 20.0},
                                                {14.0, 23.0} };
  aRamCanvas.drawTriangle(ptl3, aColor);                                                   // drawTriangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::pointFltType ptl4[3] = { {16.0, 20.0},
                                                {19.0, 20.0},
                                                {19.0, 23.0} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(ptl4);                                                           // drawTriangle(fPnt *thePoints);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawFillTriangle(21, 9, 24, 9, 24, 12,  aColor);                              // drawFillTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3,
                                                                                             //                  clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(26, 9, 29, 9, 29, 12);                                       // drawFillTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3);
  aRamCanvas.drawFillTriangle(31.0, 10.0, 34.0, 10.0, 34.0, 13.0,  aColor);                // drawFillTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3
                                                                                             //                  clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(36.0, 10.0, 39.0, 10.0, 39.0, 13.0);                         // drawFillTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3);
  aRamCanvas.drawFillTriangle(mjr::ramCanvasRGB8b::pointIntType({21, 14}),
                                mjr::ramCanvasRGB8b::pointIntType({24, 14}),
                                mjr::ramCanvasRGB8b::pointIntType({24, 17}),  aColor);       // drawFillTriangle(iPnt point1, iPnt point2, iPnt point3, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(mjr::ramCanvasRGB8b::pointIntType({26, 14}),
                                mjr::ramCanvasRGB8b::pointIntType({29, 14}),
                                mjr::ramCanvasRGB8b::pointIntType({29, 17}));                // drawFillTriangle(iPnt point1, iPnt point2, iPnt point3);
  aRamCanvas.drawFillTriangle(mjr::ramCanvasRGB8b::pointFltType({31.0, 15.0}),
                                mjr::ramCanvasRGB8b::pointFltType({34.0, 15.0}),
                                mjr::ramCanvasRGB8b::pointFltType({34.0, 18.0}),  aColor);   // drawFillTriangle(fPnt point1, fPnt point2, fPnt point3, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(mjr::ramCanvasRGB8b::pointFltType({36.0, 15.0}),
                                mjr::ramCanvasRGB8b::pointFltType({39.0, 15.0}),
                                mjr::ramCanvasRGB8b::pointFltType({39.0, 18.0}));            // drawFillTriangle(fPnt point1, fPnt point2, fPnt point3);
  mjr::ramCanvasRGB8b::pointIntType ptl5[3] = { {21, 19}, {24, 19}, {24, 22} };
  aRamCanvas.drawFillTriangle(ptl5, aColor);                                               // drawFillTriangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::pointIntType ptl6[3] = { {26, 19}, {29, 19}, {29, 22} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(ptl6);                                                       // drawFillTriangle(iPnt *thePoints);
  mjr::ramCanvasRGB8b::pointFltType ptl7[3] = { {31.0, 20.0},
                                                {34.0, 20.0},
                                                {34.0, 23.0} };
  aRamCanvas.drawFillTriangle(ptl7, aColor);                                               // drawFillTriangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::pointFltType ptl8[3] = { {36.0, 20.0},
                                                {39.0, 20.0},
                                                {39.0, 23.0} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(ptl8);                                                       // drawFillTriangle(fPnt *thePoints);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawCircle(3, 27, 2, aColor);                                                 // drawCircle(iCrd centerX, iCrd centerY, iCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawCircle(9, 27, 2);                                                         // drawCircle(iCrd centerX, iCrd centerY, iCrd radius);
  aRamCanvas.moveTo(15, 27);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawCircle(2);                                                                // drawCircle(iCrd radius);
  aRamCanvas.drawCircle(21.0, 28.0, 2.0, bColor);                                          // drawCircle(fCrd centerX, fCrd centerY, fCrd radiusX, clr color);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawCircle(27.0, 28.0, 2.0);                                                  // drawCircle(fCrd centerX, fCrd centerY, fCrd radiusX);
  aRamCanvas.moveTo(33.0, 28.0);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawCircle(2.0);                                                              // drawCircle(fCrd radiusX);
  aRamCanvas.drawCircle(mjr::ramCanvasRGB8b::pointIntType({39, 27}), 2, aColor);           // drawCircle(iPnt centerPoint, iCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawCircle(mjr::ramCanvasRGB8b::pointIntType({45, 27}), 2);                   // drawCircle(iPnt centerPoint, iCrd radiusX);
  aRamCanvas.drawCircle(mjr::ramCanvasRGB8b::pointFltType({51.0, 28.0}), 2.0, aColor);     // drawCircle(fPnt centerPoint, fCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawCircle(mjr::ramCanvasRGB8b::pointFltType({57.0, 28.0}), 2.0);             // drawCircle(fPnt centerPoint, fCrd radiusX);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawFillCircle(3, 33, 2, aColor);                                             // drawFillCircle(iCrd centerX, iCrd centerY, iCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillCircle(9, 33, 2);                                                     // drawFillCircle(iCrd centerX, iCrd centerY, iCrd radiusX);
  aRamCanvas.moveTo(15, 33);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawFillCircle(2);                                                            // drawFillCircle(iCrd radiusX);
  aRamCanvas.drawFillCircle(21.0, 34.0, 2.0, bColor);                                      // drawFillCircle(fCrd centerX, fCrd centerY, fCrd radiusX, clr color);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawFillCircle(27.0, 34.0, 2.0);                                              // drawFillCircle(fCrd centerX, fCrd centerY, fCrd radiusX);
  aRamCanvas.moveTo(33.0, 34.0);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillCircle(2.0);                                                          // drawFillCircle(fCrd radiusX);
  aRamCanvas.drawFillCircle(mjr::ramCanvasRGB8b::pointIntType({39, 33}), 2, aColor);       // drawFillCircle(iPnt centerPoint, iCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillCircle(mjr::ramCanvasRGB8b::pointIntType({45, 33}), 2);               // drawFillCircle(iPnt centerPoint, iCrd radiusX);
  aRamCanvas.drawFillCircle(mjr::ramCanvasRGB8b::pointFltType({51.0, 34.0}), 2.0, aColor); // drawFillCircle(fPnt centerPoint, fCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillCircle(mjr::ramCanvasRGB8b::pointFltType({57.0, 34.0}), 2.0);         // drawFillCircle(fPnt centerPoint, fCrd radiusX);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawRectangle(2, 38, 4, 40, aColor);                                          // drawRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(6, 38, 8, 40);                                                  // drawRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2);
  aRamCanvas.drawRectangle(10.0, 39.0, 12.0, 41.0, aColor);                                // drawRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(14.0, 39.0, 16.0, 41.0);                                        // drawRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2);
  aRamCanvas.drawRectangle(mjr::ramCanvasRGB8b::pointIntType({18, 38}),
                             mjr::ramCanvasRGB8b::pointIntType({20, 40}), aColor);           // drawRectangle(iPnt point1, iPnt point2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(mjr::ramCanvasRGB8b::pointIntType({22, 38}),
                             mjr::ramCanvasRGB8b::pointIntType({24, 40}));                   // drawRectangle(iPnt point1, iPnt point2);
  aRamCanvas.drawRectangle(mjr::ramCanvasRGB8b::pointFltType({26.0, 39.0}),
                             mjr::ramCanvasRGB8b::pointFltType({28.0, 41.0}), aColor);       // drawRectangle(fPnt point1, fPnt point2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(mjr::ramCanvasRGB8b::pointFltType({30.0, 39.0}),
                             mjr::ramCanvasRGB8b::pointFltType({32.0, 41.0}));               // drawRectangle(fPnt point1, fPnt point2);
  mjr::ramCanvasRGB8b::pointIntType ptl9[2] = { {34, 38}, {36, 40} };
  aRamCanvas.drawRectangle(ptl9, aColor);                                                  // drawRectangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::pointIntType ptl10[2] = { {38, 38}, {40, 40} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(ptl10);                                                         // drawRectangle(iPnt *thePoints);
  mjr::ramCanvasRGB8b::pointFltType ptl11[2] = { {42.0, 39.0}, {44.0, 41.0} };
  aRamCanvas.drawRectangle(ptl11, aColor);                                                 // drawRectangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::pointFltType ptl12[2] = { {46.0, 39.0}, {48.0, 41.0} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(ptl12);                                                         // drawRectangle(fPnt *thePoints);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawFillRectangle(2, 42, 4, 44, aColor);                                      // drawFillRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(6, 42, 8, 44);                                              // drawFillRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2);
  aRamCanvas.drawFillRectangle(10.0, 43.0, 12.0, 45.0, aColor);                            // drawFillRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(14.0, 43.0, 16.0, 45.0);                                    // drawFillRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2);
  aRamCanvas.drawFillRectangle(mjr::ramCanvasRGB8b::pointIntType({18, 42}),
                                 mjr::ramCanvasRGB8b::pointIntType({20, 44}), aColor);       // drawFillRectangle(iPnt point1, iPnt point2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(mjr::ramCanvasRGB8b::pointIntType({22, 42}),
                                 mjr::ramCanvasRGB8b::pointIntType({24, 44}));               // drawFillRectangle(iPnt point1, iPnt point2);
  aRamCanvas.drawFillRectangle(mjr::ramCanvasRGB8b::pointFltType({26.0, 43.0}),
                                 mjr::ramCanvasRGB8b::pointFltType({28.0, 45.0}), aColor);   // drawFillRectangle(fPnt point1, fPnt point2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(mjr::ramCanvasRGB8b::pointFltType({30.0, 43.0}),
                                 mjr::ramCanvasRGB8b::pointFltType({32.0, 45.0}));           // drawFillRectangle(fPnt point1, fPnt point2);
  mjr::ramCanvasRGB8b::pointIntType ptl13[2] = { {34, 42}, {36, 44} };
  aRamCanvas.drawFillRectangle(ptl13, aColor);                                             // drawFillRectangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::pointIntType ptl14[2] = { {38, 42}, {40, 44} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(ptl14);                                                     // drawFillRectangle(iPnt *thePoints);
  mjr::ramCanvasRGB8b::pointFltType ptl15[2] = { {42.0, 43.0}, {44.0, 45.0} };
  aRamCanvas.drawFillRectangle(ptl15, aColor);                                             // drawFillRectangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::pointFltType ptl16[2] = { {46.0, 43.0}, {48.0, 45.0} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(ptl16);                                                     // drawFillRectangle(fPnt *thePoints);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  mjr::ramCanvasRGB8b::coordIntType icx1[3] = {  2,  4,  4 };
  mjr::ramCanvasRGB8b::coordIntType icy1[3] = { 46, 46, 48 };
  aRamCanvas.drawPLCurve(3, icx1, icy1, aColor);                                           // drawPLCurve(int numPoints, iCrd *x, iCrd *y, clr color);
  mjr::ramCanvasRGB8b::coordIntType icx2[3] = {  6,  8,  8 };
  mjr::ramCanvasRGB8b::coordIntType icy2[3] = { 46, 46, 48 };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPLCurve(3, icx2, icy2);                                                   // drawPLCurve(int numPoints, iCrd *x, iCrd *y);
  mjr::ramCanvasRGB8b::coordFltType fcx1[3] = { 10.0, 12.0, 12.0 };
  mjr::ramCanvasRGB8b::coordFltType fcy1[3] = { 47.0, 47.0, 49.0 };
  aRamCanvas.drawPLCurve(3, fcx1, fcy1, aColor);                                           // drawPLCurve(int numPoints, fCrd *x, fCrd *y, clr color);
  mjr::ramCanvasRGB8b::coordFltType fcx2[3] = { 14.0, 16.0, 16.0 };
  mjr::ramCanvasRGB8b::coordFltType fcy2[3] = { 47.0, 47.0, 49.0 };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPLCurve(3, fcx2, fcy2);                                                   // drawPLCurve(int numPoints, fCrd *x, fCrd *y);
  mjr::ramCanvasRGB8b::pointIntType ptl17[3] = { {18, 46},
                                                 {20, 46},
                                                 {20, 48} };
  aRamCanvas.drawPLCurve(3, ptl17, aColor);                                                // drawPLCurve(int numPoints, iPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::pointIntType ptl18[3] = { {22, 46},
                                                 {24, 46},
                                                 {24, 48} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPLCurve(3, ptl18);                                                        // drawPLCurve(int numPoints, iPnt *thePoints);
  mjr::ramCanvasRGB8b::pointFltType ptl19[3] = { {26.0, 47.0},
                                                 {28.0, 47.0},
                                                 {28.0, 49.0} };
  aRamCanvas.drawPLCurve(3, ptl19, aColor);                                                // drawPLCurve(int numPoints, fPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::pointFltType ptl20[3] = { {30.0, 47.0},
                                                 {32.0, 47.0},
                                                 {32.0, 49.0} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPLCurve(3, ptl20);                                                        // drawPLCurve(int numPoints, fPnt *thePoints);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.writeRAWfile("ut-draw_primatives_int.mrw");
  aRamCanvas.scaleUpProximal(5);
  aRamCanvas.writeTIFFfile("ut-draw_primatives_int.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  std::ifstream ifs1("ut-draw_primatives_int.mrw");
  std::ifstream ifs2("../data/utest/ut-draw_primatives_int.mrw");

  std::istream_iterator<char> b1(ifs1), e1;
  std::istream_iterator<char> b2(ifs2), e2;

  BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(draw_primatives_flt) {

  // We instantiate every drawing function in ramCanvas so that we can check for compile time errors and do some basic functionality testing.

  const int BSIZE = 60;

  mjr::ramCanvasRGB32F aRamCanvas(BSIZE, BSIZE, 0, BSIZE-1, 0, BSIZE-1);
  mjr::colorRGB32F aColor(mjr::colorRGB32F::cornerColorEnum::RED);
  mjr::colorRGB32F bColor(mjr::colorRGB32F::cornerColorEnum::GREEN);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawPoint(1, 1, aColor);                                                      // drawPoint(iCrd x, iCrd y, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.moveTo(2, 1);
  aRamCanvas.drawPoint();                                                                  // drawPoint();
  aRamCanvas.moveTo(3, 1);
  aRamCanvas.drawPoint(aColor);                                                            // drawPoint(clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPoint(4, 1);                                                              // drawPoint(iCrd x, iCrd y);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawPoint(5.0, 2.0);                                                          // drawPoint(fCrd x, fCrd y);
  aRamCanvas.drawPoint(6.0, 2.0, bColor);                                                  // drawPoint(fCrd x, fCrd y, clr color);
  aRamCanvas.drawPoint(mjr::ramCanvasRGB32F::pointIntType({7, 1}), aColor);                 // drawPoint(iPnt thePoint, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPoint(mjr::ramCanvasRGB32F::pointIntType({8, 1}));                         // drawPoint(iPnt thePoint);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawPoint(mjr::ramCanvasRGB32F::pointFltType({9.0, 2.0}));                     // drawPoint(fPnt thePoint);
  aRamCanvas.drawPoint(mjr::ramCanvasRGB32F::pointFltType({10.0, 2.0}), bColor);            // drawPoint(fPnt thePoint, clr color);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawLine(1, 4, 1, 6, aColor);                                                 // drawLine(iCrd x1, iCrd y1, iCrd x2, iCrd y2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.moveTo(2, 4);
  aRamCanvas.drawLine(2, 6);                                                               // drawLine(iCrd x,  iCrd y);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.moveTo(3.0, 5.0);
  aRamCanvas.drawLine(3.0, 7.0);                                                           // drawLine(fCrd x,  fCrd y);
  aRamCanvas.moveTo(4, 4);
  aRamCanvas.drawLine(4, 6, bColor);                                                       // drawLine(iCrd x,  iCrd y,  clr color);
  aRamCanvas.moveTo(5.0, 5.0);
  aRamCanvas.drawLine(5.0, 7.0, aColor);                                                   // drawLine(fCrd x,  fCrd y,  clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawLine(6, 4, 6, 6);                                                         // drawLine(iCrd x1, iCrd y1, iCrd x2, iCrd y2);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawLine(7.0, 5.0, 7.0, 7.0);                                                 // drawLine(fCrd x1, fCrd y1, fCrd x2, fCrd y2);
  aRamCanvas.drawLine(8.0, 5.0, 8.0, 7.0, bColor);                                         // drawLine(fCrd x1, fCrd y1, fCrd x2, fCrd y2, clr color);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.moveTo(mjr::ramCanvasRGB32F::pointFltType({9.0, 5.0}));
  aRamCanvas.drawLine(mjr::ramCanvasRGB32F::pointFltType({9.0, 7.0}));                      // drawLine(fPnt point1);
  aRamCanvas.moveTo(10.0, 5.0);
  aRamCanvas.drawLine(mjr::ramCanvasRGB32F::pointFltType({10.0, 7.0}), bColor);             // drawLine(fPnt point1, clr color);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.moveTo(11, 4);
  aRamCanvas.drawLine(mjr::ramCanvasRGB32F::pointIntType({11, 6}));                         // drawLine(iPnt point1);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.moveTo(mjr::ramCanvasRGB32F::pointIntType({12, 4}));
  aRamCanvas.drawLine(mjr::ramCanvasRGB32F::pointIntType({12, 6}), aColor);                 // drawLine(iPnt point1, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawLine(mjr::ramCanvasRGB32F::pointFltType({13, 5.0}),
                        mjr::ramCanvasRGB32F::pointFltType({13, 7.0}));                       // drawLine(fPnt point1, fPnt point2);
  aRamCanvas.drawLine(mjr::ramCanvasRGB32F::pointFltType({14, 5.0}),
                        mjr::ramCanvasRGB32F::pointFltType({14, 7.0}), aColor);               // drawLine(fPnt point1, fPnt point2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawLine(mjr::ramCanvasRGB32F::pointIntType({15, 4}),
                        mjr::ramCanvasRGB32F::pointIntType({15, 6}));                         // drawLine(iPnt point1, iPnt point2);
  aRamCanvas.drawLine(mjr::ramCanvasRGB32F::pointIntType({16, 5}),
                        mjr::ramCanvasRGB32F::pointIntType({16, 6}), aColor);                 // drawLine(iPnt point1, iPnt point2, clr color);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawTriangle(1, 9, 4, 9, 4, 12,  aColor);                                     // drawTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3,
                                                                                             //              clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(6, 9, 9, 9, 9, 12);                                              // drawTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3);
  aRamCanvas.drawTriangle(11.0, 10.0, 14.0, 10.0, 14.0, 13.0,  aColor);                    // drawTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3,
                                                                                             //              clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(16.0, 10.0, 19.0, 10.0, 19.0, 13.0);                             // drawTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3);
  aRamCanvas.drawTriangle(mjr::ramCanvasRGB32F::pointIntType({1, 14}),
                            mjr::ramCanvasRGB32F::pointIntType({4, 14}),
                            mjr::ramCanvasRGB32F::pointIntType({4, 17}),  aColor);            // drawTriangle(iPnt point1, iPnt point2, iPnt point3, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(mjr::ramCanvasRGB32F::pointIntType({6, 14}),
                            mjr::ramCanvasRGB32F::pointIntType({9, 14}),
                            mjr::ramCanvasRGB32F::pointIntType({9, 17}));                     // drawTriangle(iPnt point1, iPnt point2, iPnt point3);
  aRamCanvas.drawTriangle(mjr::ramCanvasRGB32F::pointFltType({11.0, 15.0}),
                            mjr::ramCanvasRGB32F::pointFltType({14.0, 15.0}),
                            mjr::ramCanvasRGB32F::pointFltType({14.0, 18.0}),  aColor);       // drawTriangle(fPnt point1, fPnt point2, fPnt point3, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(mjr::ramCanvasRGB32F::pointFltType({16.0, 15.0}),
                            mjr::ramCanvasRGB32F::pointFltType({19.0, 15.0}),
                            mjr::ramCanvasRGB32F::pointFltType({19.0, 18.0}));                // drawTriangle(fPnt point1, fPnt point2, fPnt point3);
  mjr::ramCanvasRGB32F::pointIntType ptl1[3] = { {1, 19}, {4, 19}, {4, 22} };
  aRamCanvas.drawTriangle(ptl1, aColor);                                                   // drawTriangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB32F::pointIntType ptl2[3] = { {6, 19}, {9, 19}, {9, 22} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(ptl2);                                                           // drawTriangle(iPnt *thePoints);
  mjr::ramCanvasRGB32F::pointFltType ptl3[3] = { {11.0, 20.0},
                                                {14.0, 20.0},
                                                {14.0, 23.0} };
  aRamCanvas.drawTriangle(ptl3, aColor);                                                   // drawTriangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB32F::pointFltType ptl4[3] = { {16.0, 20.0},
                                                {19.0, 20.0},
                                                {19.0, 23.0} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawTriangle(ptl4);                                                           // drawTriangle(fPnt *thePoints);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawFillTriangle(21, 9, 24, 9, 24, 12,  aColor);                              // drawFillTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3,
                                                                                             //                  clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(26, 9, 29, 9, 29, 12);                                       // drawFillTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3);
  aRamCanvas.drawFillTriangle(31.0, 10.0, 34.0, 10.0, 34.0, 13.0,  aColor);                // drawFillTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3
                                                                                             //                  clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(36.0, 10.0, 39.0, 10.0, 39.0, 13.0);                         // drawFillTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3);
  aRamCanvas.drawFillTriangle(mjr::ramCanvasRGB32F::pointIntType({21, 14}),
                                mjr::ramCanvasRGB32F::pointIntType({24, 14}),
                                mjr::ramCanvasRGB32F::pointIntType({24, 17}),  aColor);       // drawFillTriangle(iPnt point1, iPnt point2, iPnt point3, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(mjr::ramCanvasRGB32F::pointIntType({26, 14}),
                                mjr::ramCanvasRGB32F::pointIntType({29, 14}),
                                mjr::ramCanvasRGB32F::pointIntType({29, 17}));                // drawFillTriangle(iPnt point1, iPnt point2, iPnt point3);
  aRamCanvas.drawFillTriangle(mjr::ramCanvasRGB32F::pointFltType({31.0, 15.0}),
                                mjr::ramCanvasRGB32F::pointFltType({34.0, 15.0}),
                                mjr::ramCanvasRGB32F::pointFltType({34.0, 18.0}),  aColor);   // drawFillTriangle(fPnt point1, fPnt point2, fPnt point3, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(mjr::ramCanvasRGB32F::pointFltType({36.0, 15.0}),
                                mjr::ramCanvasRGB32F::pointFltType({39.0, 15.0}),
                                mjr::ramCanvasRGB32F::pointFltType({39.0, 18.0}));            // drawFillTriangle(fPnt point1, fPnt point2, fPnt point3);
  mjr::ramCanvasRGB32F::pointIntType ptl5[3] = { {21, 19}, {24, 19}, {24, 22} };
  aRamCanvas.drawFillTriangle(ptl5, aColor);                                               // drawFillTriangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB32F::pointIntType ptl6[3] = { {26, 19}, {29, 19}, {29, 22} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(ptl6);                                                       // drawFillTriangle(iPnt *thePoints);
  mjr::ramCanvasRGB32F::pointFltType ptl7[3] = { {31.0, 20.0},
                                                {34.0, 20.0},
                                                {34.0, 23.0} };
  aRamCanvas.drawFillTriangle(ptl7, aColor);                                               // drawFillTriangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB32F::pointFltType ptl8[3] = { {36.0, 20.0},
                                                {39.0, 20.0},
                                                {39.0, 23.0} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillTriangle(ptl8);                                                       // drawFillTriangle(fPnt *thePoints);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawCircle(3, 27, 2, aColor);                                                 // drawCircle(iCrd centerX, iCrd centerY, iCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawCircle(9, 27, 2);                                                         // drawCircle(iCrd centerX, iCrd centerY, iCrd radius);
  aRamCanvas.moveTo(15, 27);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawCircle(2);                                                                // drawCircle(iCrd radius);
  aRamCanvas.drawCircle(21.0, 28.0, 2.0, bColor);                                          // drawCircle(fCrd centerX, fCrd centerY, fCrd radiusX, clr color);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawCircle(27.0, 28.0, 2.0);                                                  // drawCircle(fCrd centerX, fCrd centerY, fCrd radiusX);
  aRamCanvas.moveTo(33.0, 28.0);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawCircle(2.0);                                                              // drawCircle(fCrd radiusX);
  aRamCanvas.drawCircle(mjr::ramCanvasRGB32F::pointIntType({39, 27}), 2, aColor);           // drawCircle(iPnt centerPoint, iCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawCircle(mjr::ramCanvasRGB32F::pointIntType({45, 27}), 2);                   // drawCircle(iPnt centerPoint, iCrd radiusX);
  aRamCanvas.drawCircle(mjr::ramCanvasRGB32F::pointFltType({51.0, 28.0}), 2.0, aColor);     // drawCircle(fPnt centerPoint, fCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawCircle(mjr::ramCanvasRGB32F::pointFltType({57.0, 28.0}), 2.0);             // drawCircle(fPnt centerPoint, fCrd radiusX);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawFillCircle(3, 33, 2, aColor);                                             // drawFillCircle(iCrd centerX, iCrd centerY, iCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillCircle(9, 33, 2);                                                     // drawFillCircle(iCrd centerX, iCrd centerY, iCrd radiusX);
  aRamCanvas.moveTo(15, 33);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawFillCircle(2);                                                            // drawFillCircle(iCrd radiusX);
  aRamCanvas.drawFillCircle(21.0, 34.0, 2.0, bColor);                                      // drawFillCircle(fCrd centerX, fCrd centerY, fCrd radiusX, clr color);
  aRamCanvas.setDfltColor(aColor);
  aRamCanvas.drawFillCircle(27.0, 34.0, 2.0);                                              // drawFillCircle(fCrd centerX, fCrd centerY, fCrd radiusX);
  aRamCanvas.moveTo(33.0, 34.0);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillCircle(2.0);                                                          // drawFillCircle(fCrd radiusX);
  aRamCanvas.drawFillCircle(mjr::ramCanvasRGB32F::pointIntType({39, 33}), 2, aColor);       // drawFillCircle(iPnt centerPoint, iCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillCircle(mjr::ramCanvasRGB32F::pointIntType({45, 33}), 2);               // drawFillCircle(iPnt centerPoint, iCrd radiusX);
  aRamCanvas.drawFillCircle(mjr::ramCanvasRGB32F::pointFltType({51.0, 34.0}), 2.0, aColor); // drawFillCircle(fPnt centerPoint, fCrd radiusX, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillCircle(mjr::ramCanvasRGB32F::pointFltType({57.0, 34.0}), 2.0);         // drawFillCircle(fPnt centerPoint, fCrd radiusX);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawRectangle(2, 38, 4, 40, aColor);                                          // drawRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(6, 38, 8, 40);                                                  // drawRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2);
  aRamCanvas.drawRectangle(10.0, 39.0, 12.0, 41.0, aColor);                                // drawRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(14.0, 39.0, 16.0, 41.0);                                        // drawRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2);
  aRamCanvas.drawRectangle(mjr::ramCanvasRGB32F::pointIntType({18, 38}),
                             mjr::ramCanvasRGB32F::pointIntType({20, 40}), aColor);           // drawRectangle(iPnt point1, iPnt point2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(mjr::ramCanvasRGB32F::pointIntType({22, 38}),
                             mjr::ramCanvasRGB32F::pointIntType({24, 40}));                   // drawRectangle(iPnt point1, iPnt point2);
  aRamCanvas.drawRectangle(mjr::ramCanvasRGB32F::pointFltType({26.0, 39.0}),
                             mjr::ramCanvasRGB32F::pointFltType({28.0, 41.0}), aColor);       // drawRectangle(fPnt point1, fPnt point2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(mjr::ramCanvasRGB32F::pointFltType({30.0, 39.0}),
                             mjr::ramCanvasRGB32F::pointFltType({32.0, 41.0}));               // drawRectangle(fPnt point1, fPnt point2);
  mjr::ramCanvasRGB32F::pointIntType ptl9[2] = { {34, 38}, {36, 40} };
  aRamCanvas.drawRectangle(ptl9, aColor);                                                  // drawRectangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB32F::pointIntType ptl10[2] = { {38, 38}, {40, 40} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(ptl10);                                                         // drawRectangle(iPnt *thePoints);
  mjr::ramCanvasRGB32F::pointFltType ptl11[2] = { {42.0, 39.0}, {44.0, 41.0} };
  aRamCanvas.drawRectangle(ptl11, aColor);                                                 // drawRectangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB32F::pointFltType ptl12[2] = { {46.0, 39.0}, {48.0, 41.0} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawRectangle(ptl12);                                                         // drawRectangle(fPnt *thePoints);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawFillRectangle(2, 42, 4, 44, aColor);                                      // drawFillRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(6, 42, 8, 44);                                              // drawFillRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2);
  aRamCanvas.drawFillRectangle(10.0, 43.0, 12.0, 45.0, aColor);                            // drawFillRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(14.0, 43.0, 16.0, 45.0);                                    // drawFillRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2);
  aRamCanvas.drawFillRectangle(mjr::ramCanvasRGB32F::pointIntType({18, 42}),
                                 mjr::ramCanvasRGB32F::pointIntType({20, 44}), aColor);       // drawFillRectangle(iPnt point1, iPnt point2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(mjr::ramCanvasRGB32F::pointIntType({22, 42}),
                                 mjr::ramCanvasRGB32F::pointIntType({24, 44}));               // drawFillRectangle(iPnt point1, iPnt point2);
  aRamCanvas.drawFillRectangle(mjr::ramCanvasRGB32F::pointFltType({26.0, 43.0}),
                                 mjr::ramCanvasRGB32F::pointFltType({28.0, 45.0}), aColor);   // drawFillRectangle(fPnt point1, fPnt point2, clr color);
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(mjr::ramCanvasRGB32F::pointFltType({30.0, 43.0}),
                                 mjr::ramCanvasRGB32F::pointFltType({32.0, 45.0}));           // drawFillRectangle(fPnt point1, fPnt point2);
  mjr::ramCanvasRGB32F::pointIntType ptl13[2] = { {34, 42}, {36, 44} };
  aRamCanvas.drawFillRectangle(ptl13, aColor);                                             // drawFillRectangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB32F::pointIntType ptl14[2] = { {38, 42}, {40, 44} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(ptl14);                                                     // drawFillRectangle(iPnt *thePoints);
  mjr::ramCanvasRGB32F::pointFltType ptl15[2] = { {42.0, 43.0}, {44.0, 45.0} };
  aRamCanvas.drawFillRectangle(ptl15, aColor);                                             // drawFillRectangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB32F::pointFltType ptl16[2] = { {46.0, 43.0}, {48.0, 45.0} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawFillRectangle(ptl16);                                                     // drawFillRectangle(fPnt *thePoints);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  mjr::ramCanvasRGB32F::coordIntType icx1[3] = {  2,  4,  4 };
  mjr::ramCanvasRGB32F::coordIntType icy1[3] = { 46, 46, 48 };
  aRamCanvas.drawPLCurve(3, icx1, icy1, aColor);                                           // drawPLCurve(int numPoints, iCrd *x, iCrd *y, clr color);
  mjr::ramCanvasRGB32F::coordIntType icx2[3] = {  6,  8,  8 };
  mjr::ramCanvasRGB32F::coordIntType icy2[3] = { 46, 46, 48 };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPLCurve(3, icx2, icy2);                                                   // drawPLCurve(int numPoints, iCrd *x, iCrd *y);
  mjr::ramCanvasRGB32F::coordFltType fcx1[3] = { 10.0, 12.0, 12.0 };
  mjr::ramCanvasRGB32F::coordFltType fcy1[3] = { 47.0, 47.0, 49.0 };
  aRamCanvas.drawPLCurve(3, fcx1, fcy1, aColor);                                           // drawPLCurve(int numPoints, fCrd *x, fCrd *y, clr color);
  mjr::ramCanvasRGB32F::coordFltType fcx2[3] = { 14.0, 16.0, 16.0 };
  mjr::ramCanvasRGB32F::coordFltType fcy2[3] = { 47.0, 47.0, 49.0 };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPLCurve(3, fcx2, fcy2);                                                   // drawPLCurve(int numPoints, fCrd *x, fCrd *y);
  mjr::ramCanvasRGB32F::pointIntType ptl17[3] = { {18, 46},
                                                 {20, 46},
                                                 {20, 48} };
  aRamCanvas.drawPLCurve(3, ptl17, aColor);                                                // drawPLCurve(int numPoints, iPnt *thePoints, clr color);
  mjr::ramCanvasRGB32F::pointIntType ptl18[3] = { {22, 46},
                                                 {24, 46},
                                                 {24, 48} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPLCurve(3, ptl18);                                                        // drawPLCurve(int numPoints, iPnt *thePoints);
  mjr::ramCanvasRGB32F::pointFltType ptl19[3] = { {26.0, 47.0},
                                                 {28.0, 47.0},
                                                 {28.0, 49.0} };
  aRamCanvas.drawPLCurve(3, ptl19, aColor);                                                // drawPLCurve(int numPoints, fPnt *thePoints, clr color);
  mjr::ramCanvasRGB32F::pointFltType ptl20[3] = { {30.0, 47.0},
                                                 {32.0, 47.0},
                                                 {32.0, 49.0} };
  aRamCanvas.setDfltColor(bColor);
  aRamCanvas.drawPLCurve(3, ptl20);                                                        // drawPLCurve(int numPoints, fPnt *thePoints);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.writeRAWfile("ut-draw_primatives_flt.mrw");
  aRamCanvas.scaleUpProximal(5);
  aRamCanvas.writeTIFFfile("ut-draw_primatives_flt.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  std::ifstream ifs1("ut-draw_primatives_flt.mrw");
  std::ifstream ifs2("../data/utest/ut-draw_primatives_flt.mrw");

  std::istream_iterator<char> b1(ifs1), e1;
  std::istream_iterator<char> b2(ifs2), e2;

  BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(save_file) {

  const int WIDE = 16;
  const int TALL = 8;

  mjr::ramCanvasRGB8b  aRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB8b::colorType  aColor; typedef mjr::ramCanvasRGB8b::colorChanType  aCt;
  mjr::ramCanvasRGB16b bRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB16b::colorType bColor; typedef mjr::ramCanvasRGB16b::colorChanType bCt;
  mjr::ramCanvasRGB32b cRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB32b::colorType cColor; typedef mjr::ramCanvasRGB32b::colorChanType cCt;
  mjr::ramCanvasRGB64b dRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB64b::colorType dColor; typedef mjr::ramCanvasRGB64b::colorChanType dCt;
  mjr::ramCanvasRGB32F eRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB32F::colorType eColor; typedef mjr::ramCanvasRGB32F::colorChanType eCt;
  mjr::ramCanvasRGB64F fRamCanvas(WIDE, TALL);   mjr::ramCanvasRGB64F::colorType fColor; typedef mjr::ramCanvasRGB64F::colorChanType fCt;
  mjr::ramCanvas1c8b   gRamCanvas(WIDE, TALL);   mjr::ramCanvas1c8b::colorType   gColor; typedef mjr::ramCanvas1c8b::colorChanType   gCt;
  mjr::ramCanvas1c16b  hRamCanvas(WIDE, TALL);   mjr::ramCanvas1c16b::colorType  hColor; typedef mjr::ramCanvas1c16b::colorChanType  hCt;
  mjr::ramCanvas1c32b  iRamCanvas(WIDE, TALL);   mjr::ramCanvas1c32b::colorType  iColor; typedef mjr::ramCanvas1c32b::colorChanType  iCt;
  mjr::ramCanvas1c64b  jRamCanvas(WIDE, TALL);   mjr::ramCanvas1c64b::colorType  jColor; typedef mjr::ramCanvas1c64b::colorChanType  jCt;
  mjr::ramCanvas1c32F  kRamCanvas(WIDE, TALL);   mjr::ramCanvas1c32F::colorType  kColor; typedef mjr::ramCanvas1c32F::colorChanType  kCt;
  mjr::ramCanvas1c64F  lRamCanvas(WIDE, TALL);   mjr::ramCanvas1c64F::colorType  lColor; typedef mjr::ramCanvas1c64F::colorChanType  lCt;

  for(int x=0;x<aRamCanvas.getNumPixX();x++)
    for(int y=0;y<aRamCanvas.getNumPixY();y++) {
      aRamCanvas.drawPoint(x, y, aColor.setChansRGB((aCt)x, (aCt)y, (aCt)(x+y)));
      bRamCanvas.drawPoint(x, y, bColor.setChansRGB((bCt)x, (bCt)y, (bCt)(x+y)));
      cRamCanvas.drawPoint(x, y, cColor.setChansRGB((cCt)x, (cCt)y, (cCt)(x+y)));
      dRamCanvas.drawPoint(x, y, dColor.setChansRGB((dCt)x, (dCt)y, (dCt)(x+y)));
      eRamCanvas.drawPoint(x, y, eColor.setChansRGB((eCt)x, (eCt)y, (eCt)(x+y)));
      fRamCanvas.drawPoint(x, y, fColor.setChansRGB((fCt)x, (fCt)y, (fCt)(x+y)));
      gRamCanvas.drawPoint(x, y, gColor.setChans((gCt)(x+y)));
      hRamCanvas.drawPoint(x, y, hColor.setChans((hCt)(x+y)));
      iRamCanvas.drawPoint(x, y, iColor.setChans((iCt)(x+y)));
      jRamCanvas.drawPoint(x, y, jColor.setChans((jCt)(x+y)));
      kRamCanvas.drawPoint(x, y, kColor.setChans((kCt)(x+y)));
      lRamCanvas.drawPoint(x, y, lColor.setChans((lCt)(x+y)));
    }

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Write TIFF files.  These need to be checked outside of this source.  tiffinfo for starters.
  //  MJR TODO NOTE BOOST_AUTO_TEST_CASE: Add an external script to check the TIFF files.
  aRamCanvas.writeTIFFfile("ut-save_file-a.tiff");
  bRamCanvas.writeTIFFfile("ut-save_file-b.tiff");
  cRamCanvas.writeTIFFfile("ut-save_file-c.tiff");
  dRamCanvas.writeTIFFfile("ut-save_file-d.tiff");
  eRamCanvas.writeTIFFfile("ut-save_file-e.tiff");
  fRamCanvas.writeTIFFfile("ut-save_file-f.tiff");
  gRamCanvas.writeTIFFfile("ut-save_file-g.tiff");
  hRamCanvas.writeTIFFfile("ut-save_file-h.tiff");
  iRamCanvas.writeTIFFfile("ut-save_file-i.tiff");
  jRamCanvas.writeTIFFfile("ut-save_file-j.tiff");
  kRamCanvas.writeTIFFfile("ut-save_file-k.tiff");
  lRamCanvas.writeTIFFfile("ut-save_file-l.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Make sure headers are correct for MRW files
  //  MJR TODO NOTE BOOST_AUTO_TEST_CASE: Should check entire contents of file

  aRamCanvas.writeRAWfile("ut-save_file-a.mrw");
  bRamCanvas.writeRAWfile("ut-save_file-b.mrw");
  cRamCanvas.writeRAWfile("ut-save_file-c.mrw");
  dRamCanvas.writeRAWfile("ut-save_file-d.mrw");
  eRamCanvas.writeRAWfile("ut-save_file-e.mrw");
  fRamCanvas.writeRAWfile("ut-save_file-f.mrw");
  gRamCanvas.writeRAWfile("ut-save_file-g.mrw");
  hRamCanvas.writeRAWfile("ut-save_file-h.mrw");
  iRamCanvas.writeRAWfile("ut-save_file-i.mrw");
  jRamCanvas.writeRAWfile("ut-save_file-j.mrw");
  kRamCanvas.writeRAWfile("ut-save_file-k.mrw");
  lRamCanvas.writeRAWfile("ut-save_file-l.mrw");

  char aRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000003c00000000008bUNSsINTtLTLi\012";
  char bRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000003c00000000016bUNSsINTtLTLi\012";
  char cRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000003c00000000032bUNSsINTtLTLi\012";
  char dRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000003c00000000064bUNSsINTtLTLi\012";
  char eRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000003c00000000032bSGNsFLTtLTLi\012";
  char fRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000003c00000000064bSGNsFLTtLTLi\012";
  char gRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000001c00000000008bUNSsINTtLTLi\012";
  char hRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000001c00000000016bUNSsINTtLTLi\012";
  char iRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000001c00000000032bUNSsINTtLTLi\012";
  char jRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000001c00000000064bUNSsINTtLTLi\012";
  char kRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000001c00000000032bSGNsFLTtLTLi\012";
  char lRawHeader[101] = "MJRRAW\0120000000000000000016x0000000000000000008y000000000000000000000000001c00000000064bSGNsFLTtLTLi\012";

  char strBuf[256];

  std::ifstream ifsa("ut-save_file-a.mrw"); ifsa.get(strBuf, 101, '\0'); ifsa.close(); BOOST_CHECK_EQUAL_COLLECTIONS(aRawHeader, aRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsb("ut-save_file-b.mrw"); ifsb.get(strBuf, 101, '\0'); ifsb.close(); BOOST_CHECK_EQUAL_COLLECTIONS(bRawHeader, bRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsc("ut-save_file-c.mrw"); ifsc.get(strBuf, 101, '\0'); ifsc.close(); BOOST_CHECK_EQUAL_COLLECTIONS(cRawHeader, cRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsd("ut-save_file-d.mrw"); ifsd.get(strBuf, 101, '\0'); ifsd.close(); BOOST_CHECK_EQUAL_COLLECTIONS(dRawHeader, dRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifse("ut-save_file-e.mrw"); ifse.get(strBuf, 101, '\0'); ifse.close(); BOOST_CHECK_EQUAL_COLLECTIONS(eRawHeader, eRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsf("ut-save_file-f.mrw"); ifsf.get(strBuf, 101, '\0'); ifsf.close(); BOOST_CHECK_EQUAL_COLLECTIONS(fRawHeader, fRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsg("ut-save_file-g.mrw"); ifsg.get(strBuf, 101, '\0'); ifsg.close(); BOOST_CHECK_EQUAL_COLLECTIONS(gRawHeader, gRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsh("ut-save_file-h.mrw"); ifsh.get(strBuf, 101, '\0'); ifsh.close(); BOOST_CHECK_EQUAL_COLLECTIONS(hRawHeader, hRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsi("ut-save_file-i.mrw"); ifsi.get(strBuf, 101, '\0'); ifsi.close(); BOOST_CHECK_EQUAL_COLLECTIONS(iRawHeader, iRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsj("ut-save_file-j.mrw"); ifsj.get(strBuf, 101, '\0'); ifsj.close(); BOOST_CHECK_EQUAL_COLLECTIONS(jRawHeader, jRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsk("ut-save_file-k.mrw"); ifsk.get(strBuf, 101, '\0'); ifsk.close(); BOOST_CHECK_EQUAL_COLLECTIONS(kRawHeader, kRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsl("ut-save_file-l.mrw"); ifsl.get(strBuf, 101, '\0'); ifsl.close(); BOOST_CHECK_EQUAL_COLLECTIONS(lRawHeader, lRawHeader+100, strBuf, strBuf+100);

  // Here is a nice way to look at the data part of the image files
  //   - hexDump.rb -w 16 -b 3 -p 100 ut-save_file-a.mrw | less -RS
  //   - hexDump.rb -w 16 -b 6 -p 100 ut-save_file-b.mrw | less -RS

  // Nice way to look at file a
  // head -n 2 ut-save_file-a.mrw; hexDump.rb -t 0 -c -w 16 -b 3 -p 100 ut-save_file-a.mrw
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(lines_no_clip) {

// The line draw algorithm has many cases.  We try to hit them all.

  const int WIDE = 16+16+16+1;
  const int TALL = 18;

  mjr::ramCanvas1c8b aRamCanvas(WIDE, TALL);
  mjr::ramCanvas1c8b::colorType aColor;

  std::vector<std::vector<int>> lns {{ 1,  1,  1, 11},
                                     { 1,  1, 11, 16},
                                     { 1,  1, 11, 11},
                                     { 1,  1, 11,  6},
                                     { 1,  1, 11,  1},
                                     {13, 16, 23, 11},
                                     {13, 16, 23,  6},
                                     {13, 16, 23,  1}};

  aColor.setToWhite();
  for(auto pts : lns) {
    aRamCanvas.drawLine(   pts[2], pts[3],    pts[0], pts[1], aColor);
    aRamCanvas.drawLine(24+pts[0], pts[1], 24+pts[2], pts[3], aColor);
  }

  aRamCanvas.writeRAWfile("ut-lines_no_clip.mrw");
  aRamCanvas.scaleUpProximal(10);
  aRamCanvas.writeTIFFfile("ut-lines_no_clip.tiff");

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  std::ifstream ifs1("ut-lines_no_clip.mrw");
  std::ifstream ifs2("../data/utest/ut-lines_no_clip.mrw");

  std::istream_iterator<char> b1(ifs1), e1;
  std::istream_iterator<char> b2(ifs2), e2;

  BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(lines_clip) {

  // The line draw algorithm has many cases.  We try to hit them all.

  std::vector<std::vector<int>> lns {{ -8, -16,   8,  16},
                                     {-16, -16,  16,  16},
                                     {-16,  -8,  16,   8},
                                     {-16,   0,  16,   0},
                                     {-16,   8,  16,  -8},
                                     {-16,  16,  16, -16},
                                     { -8,  16,   8, -16},
                                     {  0, -16,   0,  16}};

  mjr::ramCanvas1c8b::colorType aColor;
  aColor.setToWhite();

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // no-clip
  mjr::ramCanvas1c8b bRamCanvas(40, 40);
  mjr::ramCanvas1c8b cRamCanvas(40, 40);

  for(auto pts : lns) {
    bRamCanvas.drawLine(19+pts[0], 19+pts[1], 19+pts[2], 19+pts[3], aColor);
    cRamCanvas.drawLine(19+pts[2], 19+pts[3], 19+pts[0], 19+pts[1], aColor);
  }

  bRamCanvas.writeRAWfile("ut-lines_clip-b.mrw");
  bRamCanvas.scaleUpProximal(10);
  bRamCanvas.writeTIFFfile("ut-lines_clip-b.tiff");

  cRamCanvas.writeRAWfile("ut-lines_clip-c.mrw");
  cRamCanvas.scaleUpProximal(10);
  cRamCanvas.writeTIFFfile("ut-lines_clip-c.tiff");

  BOOST_CHECK_EQUAL_COLLECTIONS(bRamCanvas.begin(), bRamCanvas.end(), cRamCanvas.begin(), cRamCanvas.end());

  std::ifstream ifsbg("ut-lines_clip-b.mrw");
  std::ifstream ifsbr("../data/utest/ut-lines_clip-b.mrw");

  std::istream_iterator<char> bbg(ifsbg), ebg;
  std::istream_iterator<char> bbr(ifsbr), ebr;

  BOOST_CHECK_EQUAL_COLLECTIONS(bbg, ebg, bbr, ebr);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // bot/left-clip
  mjr::ramCanvas1c8b dRamCanvas(25, 25);
  mjr::ramCanvas1c8b eRamCanvas(25, 25);

  for(auto pts : lns) {
    dRamCanvas.drawLine(7+pts[0], 7+pts[1], 7+pts[2], 7+pts[3], aColor);
    eRamCanvas.drawLine(7+pts[2], 7+pts[3], 7+pts[0], 7+pts[1], aColor);
  }

  dRamCanvas.writeRAWfile("ut-lines_clip-d.mrw");
  dRamCanvas.scaleUpProximal(10);
  dRamCanvas.writeTIFFfile("ut-lines_clip-d.tiff");

  eRamCanvas.writeRAWfile("ut-lines_clip-e.mrw");
  eRamCanvas.scaleUpProximal(10);
  eRamCanvas.writeTIFFfile("ut-lines_clip-e.tiff");

  BOOST_CHECK_EQUAL_COLLECTIONS(dRamCanvas.begin(), dRamCanvas.end(), eRamCanvas.begin(), eRamCanvas.end());

  std::ifstream ifsdg("ut-lines_clip-d.mrw");
  std::ifstream ifsdr("../data/utest/ut-lines_clip-d.mrw");

  std::istream_iterator<char> bdg(ifsdg), edg;
  std::istream_iterator<char> bdr(ifsdr), edr;

  BOOST_CHECK_EQUAL_COLLECTIONS(bdg, edg, bdr, edr);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // top/right-clip
  mjr::ramCanvas1c8b fRamCanvas(25, 25);
  mjr::ramCanvas1c8b gRamCanvas(25, 25);

  for(auto pts : lns) {
    fRamCanvas.drawLine(17+pts[0], 17+pts[1], 17+pts[2], 17+pts[3], aColor);
    gRamCanvas.drawLine(17+pts[2], 17+pts[3], 17+pts[0], 17+pts[1], aColor);
  }

  fRamCanvas.writeRAWfile("ut-lines_clip-f.mrw");
  fRamCanvas.scaleUpProximal(10);
  fRamCanvas.writeTIFFfile("ut-lines_clip-f.tiff");

  gRamCanvas.writeRAWfile("ut-lines_clip-g.mrw");
  gRamCanvas.scaleUpProximal(10);
  gRamCanvas.writeTIFFfile("ut-lines_clip-g.tiff");

  BOOST_CHECK_EQUAL_COLLECTIONS(fRamCanvas.begin(), fRamCanvas.end(), gRamCanvas.begin(), gRamCanvas.end());

  std::ifstream ifsfg("ut-lines_clip-f.mrw");
  std::ifstream ifsfr("../data/utest/ut-lines_clip-f.mrw");

  std::istream_iterator<char> bfg(ifsfg), efg;
  std::istream_iterator<char> bfr(ifsfr), efr;

  BOOST_CHECK_EQUAL_COLLECTIONS(bfg, efg, bfr, efr);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  // all-clip
  mjr::ramCanvas1c8b hRamCanvas(15, 15);
  mjr::ramCanvas1c8b iRamCanvas(15, 15);

  for(auto pts : lns) {
    hRamCanvas.drawLine(7+pts[0], 7+pts[1], 7+pts[2], 7+pts[3], aColor);
    iRamCanvas.drawLine(7+pts[2], 7+pts[3], 7+pts[0], 7+pts[1], aColor);
  }

  hRamCanvas.writeRAWfile("ut-lines_clip-h.mrw");
  hRamCanvas.scaleUpProximal(10);
  hRamCanvas.writeTIFFfile("ut-lines_clip-h.tiff");

  iRamCanvas.writeRAWfile("ut-lines_clip-i.mrw");
  iRamCanvas.scaleUpProximal(10);
  iRamCanvas.writeTIFFfile("ut-lines_clip-i.tiff");

  BOOST_CHECK_EQUAL_COLLECTIONS(hRamCanvas.begin(), hRamCanvas.end(), iRamCanvas.begin(), iRamCanvas.end());

  std::ifstream ifshg("ut-lines_clip-h.mrw");
  std::ifstream ifshr("../data/utest/ut-lines_clip-h.mrw");

  std::istream_iterator<char> bhg(ifshg), ehg;
  std::istream_iterator<char> bhr(ifshr), ehr;

  BOOST_CHECK_EQUAL_COLLECTIONS(bhg, ehg, bhr, ehr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(triangles) {

  // Try to hit many of the special cases for triangle rendering. For filled triangles, that includes the cases cA-cS in ramCanvasTpl::drawFillTriangleUtl.
  // It also means trying to get some good coverage of the special cases in ramCanvasTpl::triangleEdger as well.  One critical care about is that the edges of
  // triangles (open, solid, and shaded) are *identical*.  Another is that the results should be invariant under permutations of the points in the function
  // call.

  std::vector<std::vector<int>> tri {{ 0,  0, 16,  0,  8,  8}, // flat bot, ctr,  45
                                     { 0,  0, 16,  0,  8, 16}, // flat bot, ctr, <45
                                     { 0,  0, 16,  0,  8,  4}, // flat bot, ctr, >45
                                     { 0,  0,  8,  0,  0,  8}, // flat bot, lft,  45
                                     { 0,  0,  8,  0,  0, 16}, // flat bot, lft, <45
                                     { 0,  0,  8,  0,  0,  4}, // flat bot, lft, >45
                                     { 0,  0,  8,  0,  8,  8}, // flat bot, rgt,  45
                                     { 0,  0,  8,  0,  8, 16}, // flat bot, rgt, <45
                                     { 0,  0,  8,  0,  8,  4}, // flat bot, rgt, >45
                                     { 0, 16, 16, 16,  8,  8}, // flat top, ctr,  45
                                     { 0, 16, 16, 16,  8,  0}, // flat top, ctr, <45
                                     { 0, 16, 16, 16,  8, 12}, // flat top, ctr, >45
                                     { 0, 16,  8, 16,  0,  8}, // flat top, lft,  45
                                     { 0, 16,  8, 16,  0,  0}, // flat top, lft, <45
                                     { 0, 16,  8, 16,  0, 12}, // flat top, lft, >45
                                     { 0, 16,  8, 16,  8,  8}, // flat top, rgt,  45
                                     { 0, 16,  8, 16,  8,  0}, // flat top, rgt, <45
                                     { 0, 16,  8, 16,  8, 12}, // flat top, rgt, >45
                                     { 0,  0,  0, 16,  8,  8}, // flat lft, ctr,  45
                                     { 0,  0,  0, 16, 16,  8}, // flat lft, ctr, <45
                                     { 0,  0,  0, 16,  4,  8}, // flat lft, ctr, >45
                                     { 0,  0,  0,  8,  8,  0}, // flat lft, bot,  45
                                     { 0,  0,  0,  8, 16,  0}, // flat lft, bot, <45
                                     { 0,  0,  0,  8,  4,  0}, // flat lft, bot, >45
                                     { 0,  0,  0,  8,  8,  8}, // flat lft, top,  45
                                     { 0,  0,  0,  8, 16,  8}, // flat lft, top, <45
                                     { 0,  0,  0,  8,  4,  8}, // flat lft, top, >45
                                     {16,  0, 16, 16,  8,  8}, // flat rgt, ctr,  45
                                     {16,  0, 16, 16,  0,  8}, // flat rgt, ctr, <45
                                     {16,  0, 16, 16, 12,  8}, // flat rgt, ctr, >45
                                     {16,  0, 16,  8,  8,  0}, // flat rgt, bot,  45
                                     {16,  0, 16,  8,  0,  0}, // flat rgt, bot, <45
                                     {16,  0, 16,  8, 12,  0}, // flat rgt, bot, >45
                                     {16,  0, 16,  8,  8,  8}, // flat rgt, lft,  45
                                     {16,  0, 16,  8,  0,  8}, // flat rgt, lft, <45
                                     {16,  0, 16,  8, 12,  8}, // flat rgt, lft, >45
                                     { 0,  0, 16,  0,  8,  0}, // flat hoz, ctr
                                     { 0,  0, 16,  0,  0,  0}, // flat hoz, lft
                                     { 0,  0, 16,  0, 16,  0}, // flat hoz, rgt
                                     { 0,  0,  0, 16,  0,  8}, // flat vrt, ctr
                                     { 0,  0,  0, 16,  0,  0}, // flat vrt, bot
                                     { 0,  0,  0, 16,  0, 16}, // flat vrt, top
                                     { 8,  8,  8,  8,  8,  8}, // one point
                                     { 0,  0,  0,  0, 16, 16}, // line 45
                                     { 0, 16,  0, 16, 16,  0}, // line -45
                                     { 0,  0,  0,  0, 16,  4}, // line small slope
                                     { 0,  0,  0,  0, 16,  8}, // line small slope
                                     { 0, 16,  0, 16, 16,  8}, // line small -slope
                                     { 0, 16,  0, 16, 16, 12}, // line small -slope
                                     { 0,  0,  0,  0,  4, 16}, // line big slope
                                     { 0,  0,  0,  0,  8, 16}, // line big slope
                                     { 0, 16,  0, 16, 12,  0}, // line big -slope
                                     { 0, 16,  0, 16,  8,  0}, // line big -slope
                                     { 0,  0,  8,  8, 16, 16}, // 45 1-3 pt in ctr
                                     { 0,  0,  4,  8, 16, 16}, // 45 1-3 pt above
                                     { 0,  0, 12,  8, 16, 16}, // 45 1-3 pt below
                                     //{ 4,  0,  8,  8, 12, 16}, // >45 1-3 pt in ctr
                                     { 4,  0,  6,  8, 12, 16}, // >45 1-3 pt off -2
                                     { 4,  0,  4,  8, 12, 16}, // >45 1-3 pt off -4
                                     { 4,  0,  0,  8, 12, 16}, // >45 1-3 pt off -8
                                     { 4,  0, 10,  8, 12, 16}, // >45 1-3 pt off +2
                                     { 4,  0, 12,  8, 12, 16}, // >45 1-3 pt off +4
                                     { 4,  0, 16,  8, 12, 16}, // >45 1-3 pt off +8
                                     //{ 4, 16,  8,  8, 12,  0}, // >-45 1-3 pt in ctr
                                     { 4, 16,  6,  8, 12,  0}, // >-45 1-3 pt off -2
                                     { 4, 16,  4,  8, 12,  0}, // >-45 1-3 pt off -4
                                     { 4, 16,  0,  8, 12,  0}, // >-45 1-3 pt off -8
                                     { 4, 16, 10,  8, 12,  0}, // >-45 1-3 pt off +2
                                     { 4, 16, 12,  8, 12,  0}, // >-45 1-3 pt off +4
                                     { 4, 16, 16,  8, 12,  0}, // >-45 1-3 pt off +8
                                     //{ 0,  4,  8,  8, 16, 12}, // <45 1-3 pt in ctr
                                     { 0,  4,  8,  6, 16, 12}, // <45 1-3 pt off -2
                                     { 0,  4,  8,  4, 16, 12}, // <45 1-3 pt off -4
                                     { 0,  4,  8,  0, 16, 12}, // <45 1-3 pt off -8
                                     { 0,  4,  8, 10, 16, 12}, // <45 1-3 pt off +2
                                     { 0,  4,  8, 12, 16, 12}, // <45 1-3 pt off +4
                                     { 0,  4,  8, 16, 16, 12}, // <45 1-3 pt off +8
                                     {16, 4,   8,  6,  0, 12}, // >-45 1-3 pt off -2
                                     {16, 4,   8,  4,  0, 12}, // >-45 1-3 pt off -4
                                     {16, 4,   8,  0,  0, 12}, // >-45 1-3 pt off -8
                                     {16, 4,   8, 10,  0, 12}, // >-45 1-3 pt off +2
                                     {16, 4,   8, 12,  0, 12}, // >-45 1-3 pt off +4
                                     {16, 4,   8, 16,  0, 12}, // >-45 1-3 pt off +8
                                     {16, 4,   8,  8,  0, 12}  // >-45 1-3 pt in ctr
                                    };

  mjr::ramCanvas1c8b::colorType aColor(mjr::ramCanvas1c8b::colorType::cornerColorEnum::WHITE);
  mjr::ramCanvas3c8b::colorType bColor(mjr::ramCanvas3c8b::colorType::cornerColorEnum::BLUE);
  mjr::ramCanvas3c8b::colorType cColor(mjr::ramCanvas3c8b::colorType::cornerColorEnum::GREEN);
  mjr::ramCanvas3c8b::colorType dColor(mjr::ramCanvas3c8b::colorType::cornerColorEnum::RED);

  mjr::ramCanvas1c8b aRamCanvas(163, 163);
  mjr::ramCanvas1c8b bRamCanvas(163, 163);
  mjr::ramCanvas1c8b cRamCanvas(163, 163);
  mjr::ramCanvas1c8b dRamCanvas(163, 163);
  mjr::ramCanvas1c8b eRamCanvas(163, 163);
  mjr::ramCanvas1c8b fRamCanvas(163, 163);

  mjr::ramCanvas1c8b gRamCanvas(163, 163);
  mjr::ramCanvas1c8b hRamCanvas(163, 163);
  mjr::ramCanvas1c8b iRamCanvas(163, 163);
  mjr::ramCanvas1c8b jRamCanvas(163, 163);
  mjr::ramCanvas1c8b kRamCanvas(163, 163);
  mjr::ramCanvas1c8b lRamCanvas(163, 163);

  mjr::ramCanvas3c8b mRamCanvas(163, 163);
  mjr::ramCanvas3c8b nRamCanvas(163, 163);
  mjr::ramCanvas3c8b oRamCanvas(163, 163);
  mjr::ramCanvas3c8b pRamCanvas(163, 163);
  mjr::ramCanvas3c8b qRamCanvas(163, 163);
  mjr::ramCanvas3c8b rRamCanvas(163, 163);

  for(int i=0; i<9; i++) {
    for(int j=0; j<9; j++) {
      unsigned k = i + j * 9;
      if (k < tri.size()) {
        auto pts = tri[k];;
        int xo = 1+18*i;
        int yo = 1+18*j;
        aRamCanvas.drawTriangle(xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], aColor);
        bRamCanvas.drawTriangle(xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], aColor);
        cRamCanvas.drawTriangle(xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], aColor);
        dRamCanvas.drawTriangle(xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], aColor);
        eRamCanvas.drawTriangle(xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], aColor);
        fRamCanvas.drawTriangle(xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], aColor);

        gRamCanvas.drawFillTriangle(xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], aColor);
        hRamCanvas.drawFillTriangle(xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], aColor);
        iRamCanvas.drawFillTriangle(xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], aColor);
        jRamCanvas.drawFillTriangle(xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], aColor);
        kRamCanvas.drawFillTriangle(xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], aColor);
        lRamCanvas.drawFillTriangle(xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], aColor);


        mRamCanvas.drawFillTriangle(xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], bColor, cColor, dColor);
        nRamCanvas.drawFillTriangle(xo+pts[2], yo+pts[3], xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], cColor, dColor, bColor);
        oRamCanvas.drawFillTriangle(xo+pts[4], yo+pts[5], xo+pts[0], yo+pts[1], xo+pts[2], yo+pts[3], dColor, bColor, cColor);
        pRamCanvas.drawFillTriangle(xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], dColor, cColor, bColor);
        qRamCanvas.drawFillTriangle(xo+pts[2], yo+pts[3], xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], cColor, bColor, dColor);
        rRamCanvas.drawFillTriangle(xo+pts[0], yo+pts[1], xo+pts[4], yo+pts[5], xo+pts[2], yo+pts[3], bColor, dColor, cColor);
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  aRamCanvas.writeRAWfile("ut-triangles-a.mrw");
  bRamCanvas.writeRAWfile("ut-triangles-b.mrw");
  cRamCanvas.writeRAWfile("ut-triangles-c.mrw");
  dRamCanvas.writeRAWfile("ut-triangles-d.mrw");
  eRamCanvas.writeRAWfile("ut-triangles-e.mrw");
  fRamCanvas.writeRAWfile("ut-triangles-f.mrw");

  aRamCanvas.scaleUpProximal(8);
  bRamCanvas.scaleUpProximal(8);
  cRamCanvas.scaleUpProximal(8);
  dRamCanvas.scaleUpProximal(8);
  eRamCanvas.scaleUpProximal(8);
  fRamCanvas.scaleUpProximal(8);

  aRamCanvas.writeTIFFfile("ut-triangles-a.tiff");
  bRamCanvas.writeTIFFfile("ut-triangles-b.tiff");
  cRamCanvas.writeTIFFfile("ut-triangles-c.tiff");
  dRamCanvas.writeTIFFfile("ut-triangles-d.tiff");
  eRamCanvas.writeTIFFfile("ut-triangles-e.tiff");
  fRamCanvas.writeTIFFfile("ut-triangles-f.tiff");

  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), cRamCanvas.begin(), cRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), dRamCanvas.begin(), dRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), eRamCanvas.begin(), eRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), fRamCanvas.begin(), fRamCanvas.end());

  std::ifstream ifsag("ut-triangles-a.mrw");
  std::ifstream ifsar("../data/utest/ut-triangles-a.mrw");

  std::istream_iterator<char> bag(ifsag), eag;
  std::istream_iterator<char> bar(ifsar), ear;

  BOOST_CHECK_EQUAL_COLLECTIONS(bag, eag, bar, ear);

  ////////////////////////////////////////////////////////////////////////////////
  gRamCanvas.writeRAWfile("ut-triangles-g.mrw");
  hRamCanvas.writeRAWfile("ut-triangles-h.mrw");
  iRamCanvas.writeRAWfile("ut-triangles-i.mrw");
  jRamCanvas.writeRAWfile("ut-triangles-j.mrw");
  kRamCanvas.writeRAWfile("ut-triangles-k.mrw");
  lRamCanvas.writeRAWfile("ut-triangles-l.mrw");

  gRamCanvas.scaleUpProximal(8);
  hRamCanvas.scaleUpProximal(8);
  iRamCanvas.scaleUpProximal(8);
  jRamCanvas.scaleUpProximal(8);
  kRamCanvas.scaleUpProximal(8);
  lRamCanvas.scaleUpProximal(8);

  gRamCanvas.writeTIFFfile("ut-triangles-g.tiff");
  hRamCanvas.writeTIFFfile("ut-triangles-h.tiff");
  iRamCanvas.writeTIFFfile("ut-triangles-i.tiff");
  jRamCanvas.writeTIFFfile("ut-triangles-j.tiff");
  kRamCanvas.writeTIFFfile("ut-triangles-k.tiff");
  lRamCanvas.writeTIFFfile("ut-triangles-l.tiff");

  BOOST_CHECK_EQUAL_COLLECTIONS(gRamCanvas.begin(), gRamCanvas.end(), hRamCanvas.begin(), hRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(gRamCanvas.begin(), gRamCanvas.end(), iRamCanvas.begin(), iRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(gRamCanvas.begin(), gRamCanvas.end(), jRamCanvas.begin(), jRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(gRamCanvas.begin(), gRamCanvas.end(), kRamCanvas.begin(), kRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(gRamCanvas.begin(), gRamCanvas.end(), lRamCanvas.begin(), lRamCanvas.end());

  std::ifstream ifsgg("ut-triangles-g.mrw");
  std::ifstream ifsgr("../data/utest/ut-triangles-g.mrw");

  std::istream_iterator<char> bgg(ifsgg), egg;
  std::istream_iterator<char> bgr(ifsgr), egr;

  BOOST_CHECK_EQUAL_COLLECTIONS(bgg, egg, bgr, egr);

  ////////////////////////////////////////////////////////////////////////////////
  mRamCanvas.writeRAWfile("ut-triangles-m.mrw");
  nRamCanvas.writeRAWfile("ut-triangles-n.mrw");
  oRamCanvas.writeRAWfile("ut-triangles-o.mrw");
  pRamCanvas.writeRAWfile("ut-triangles-p.mrw");
  qRamCanvas.writeRAWfile("ut-triangles-q.mrw");
  rRamCanvas.writeRAWfile("ut-triangles-r.mrw");

  mRamCanvas.scaleUpProximal(8);
  nRamCanvas.scaleUpProximal(8);
  oRamCanvas.scaleUpProximal(8);
  pRamCanvas.scaleUpProximal(8);
  qRamCanvas.scaleUpProximal(8);
  rRamCanvas.scaleUpProximal(8);

  mRamCanvas.writeTIFFfile("ut-triangles-m.tiff");
  nRamCanvas.writeTIFFfile("ut-triangles-n.tiff");
  oRamCanvas.writeTIFFfile("ut-triangles-o.tiff");
  pRamCanvas.writeTIFFfile("ut-triangles-p.tiff");
  qRamCanvas.writeTIFFfile("ut-triangles-q.tiff");
  rRamCanvas.writeTIFFfile("ut-triangles-r.tiff");

  BOOST_CHECK_EQUAL_COLLECTIONS(mRamCanvas.begin(), mRamCanvas.end(), nRamCanvas.begin(), nRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(mRamCanvas.begin(), mRamCanvas.end(), oRamCanvas.begin(), oRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(mRamCanvas.begin(), mRamCanvas.end(), pRamCanvas.begin(), pRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(mRamCanvas.begin(), mRamCanvas.end(), qRamCanvas.begin(), qRamCanvas.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(mRamCanvas.begin(), mRamCanvas.end(), rRamCanvas.begin(), rRamCanvas.end());

  std::ifstream ifsmg("ut-triangles-m.mrw");
  std::ifstream ifsmr("../data/utest/ut-triangles-m.mrw");

  std::istream_iterator<char> bmg(ifsmg), emg;
  std::istream_iterator<char> bmr(ifsmr), emr;

  BOOST_CHECK_EQUAL_COLLECTIONS(bmg, emg, bmr, emr);
}

#endif


// Refrence mrg files:


// cp ut-draw_primatives_int.mrw ut-draw_primatives_flt.mrw ut-lines_no_clip.mrw ut-lines_clip-b.mrw ut-lines_clip-d.mrw ut-lines_clip-f.mrw ut-lines_clip-h.mrw ut-triangles-a.mrw ut-triangles-g.mrw ut-triangles-m.mrw ../data/utest/



/** @endcond */
