// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      utest_ramCanvasTpl.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-08-24
 @brief     unit tests for ramCanvasTpl on 64-bit little endian hardware -- like ia64/x86_64.@EOL
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

  std::ifstream ifsHa("ut-save_file-a.mrw"); ifsHa.get(strBuf, 101, '\0'); ifsHa.close(); BOOST_CHECK_EQUAL_COLLECTIONS(aRawHeader, aRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHb("ut-save_file-b.mrw"); ifsHb.get(strBuf, 101, '\0'); ifsHb.close(); BOOST_CHECK_EQUAL_COLLECTIONS(bRawHeader, bRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHc("ut-save_file-c.mrw"); ifsHc.get(strBuf, 101, '\0'); ifsHc.close(); BOOST_CHECK_EQUAL_COLLECTIONS(cRawHeader, cRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHd("ut-save_file-d.mrw"); ifsHd.get(strBuf, 101, '\0'); ifsHd.close(); BOOST_CHECK_EQUAL_COLLECTIONS(dRawHeader, dRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHe("ut-save_file-e.mrw"); ifsHe.get(strBuf, 101, '\0'); ifsHe.close(); BOOST_CHECK_EQUAL_COLLECTIONS(eRawHeader, eRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHf("ut-save_file-f.mrw"); ifsHf.get(strBuf, 101, '\0'); ifsHf.close(); BOOST_CHECK_EQUAL_COLLECTIONS(fRawHeader, fRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHg("ut-save_file-g.mrw"); ifsHg.get(strBuf, 101, '\0'); ifsHg.close(); BOOST_CHECK_EQUAL_COLLECTIONS(gRawHeader, gRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHh("ut-save_file-h.mrw"); ifsHh.get(strBuf, 101, '\0'); ifsHh.close(); BOOST_CHECK_EQUAL_COLLECTIONS(hRawHeader, hRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHi("ut-save_file-i.mrw"); ifsHi.get(strBuf, 101, '\0'); ifsHi.close(); BOOST_CHECK_EQUAL_COLLECTIONS(iRawHeader, iRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHj("ut-save_file-j.mrw"); ifsHj.get(strBuf, 101, '\0'); ifsHj.close(); BOOST_CHECK_EQUAL_COLLECTIONS(jRawHeader, jRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHk("ut-save_file-k.mrw"); ifsHk.get(strBuf, 101, '\0'); ifsHk.close(); BOOST_CHECK_EQUAL_COLLECTIONS(kRawHeader, kRawHeader+100, strBuf, strBuf+100);
  std::ifstream ifsHl("ut-save_file-l.mrw"); ifsHl.get(strBuf, 101, '\0'); ifsHl.close(); BOOST_CHECK_EQUAL_COLLECTIONS(lRawHeader, lRawHeader+100, strBuf, strBuf+100);

  // I checked this file by hand on 2022-08-28. sha256: 94c07f28db463165acc539a88c8a31c13646890204c7548d72ec3b3bda851c9c
  // hexDump.rb -t 0 -c -w 16 -b 3 -p 100 ut-save_file-a.mrw | less -SR
  std::ifstream ifsag("ut-save_file-a.mrw");
  std::ifstream ifsar("../data/utest/ut-save_file-a.mrw");
  std::istream_iterator<char> bag(ifsag), eag;
  std::istream_iterator<char> bar(ifsar), ear;
  BOOST_CHECK_EQUAL_COLLECTIONS(bag, eag, bar, ear);

  // I checked this file by hand on 2022-08-28. sha256: daeac55ba6fdf084ece356ce86fba5f0b501ba375b0765d3b1e0aed91bde78b5
  // hexDump.rb -t 0 -c -w 16 -b 6 -p 100 ut-save_file-b.mrw | less -RS
  std::ifstream ifsbg("ut-save_file-b.mrw");
  std::ifstream ifsbr("../data/utest/ut-save_file-b.mrw");
  std::istream_iterator<char> bbg(ifsbg), ebg;
  std::istream_iterator<char> bbr(ifsbr), ebr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bbg, ebg, bbr, ebr);

  // I checked this file qby hand on 2022-08-28. sha256: d29aa9add19842ba1f2cd98e48a5987b645e8357180984b9b88186733ee4b99f
  // hexDump.rb -t 0 -c -w 16 -b 12 -p 100 ut-save_file-c.mrw | less -RS
  std::ifstream ifscg("ut-save_file-c.mrw");
  std::ifstream ifscr("../data/utest/ut-save_file-c.mrw");
  std::istream_iterator<char> bcg(ifscg), ecg;
  std::istream_iterator<char> bcr(ifscr), ecr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bcg, ecg, bcr, ecr);

  // I checked this file qby hand on 2022-08-28. sha256: bf987ec465ba232f3339b87bb9a90b52ec282d31f91378821965c06d72cc1720
  // hexDump.rb -t -1 -c -w 16 -b 24 -p 100 ut-save_file-d.mrw | less -RS
  std::ifstream ifsdg("ut-save_file-d.mrw");
  std::ifstream ifsdr("../data/utest/ut-save_file-d.mrw");
  std::istream_iterator<char> bdg(ifsdg), edg;
  std::istream_iterator<char> bdr(ifsdr), edr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bdg, edg, bdr, edr);

  // I checked this file qby hand on 2022-08-28. sha256: eb74e602fc69f5755a276c0bcc3c7acc473def2fb7288e324b6463f45d7f8816
  // hexDump.rb -t 0 -c -w 16 -b 12 -p 100 ut-save_file-e.mrw | less -RS
  std::ifstream ifseg("ut-save_file-e.mrw");
  std::ifstream ifser("../data/utest/ut-save_file-e.mrw");
  std::istream_iterator<char> beg(ifseg), eeg;
  std::istream_iterator<char> ber(ifser), eer;
  BOOST_CHECK_EQUAL_COLLECTIONS(beg, eeg, ber, eer);

  // I checked this file qby hand on 2022-08-28. sha256: 060b545e73ce68ea60f9413ba8611cea1ddf30c986c6ad9384d137939927465d
  // I did the conversion by hand, so I should double check it...
  // hexDump.rb -t -1 -c -w 16 -b 24 -p 100 ut-save_file-f.mrw | less -RS
  std::ifstream ifsfg("ut-save_file-f.mrw");
  std::ifstream ifsfr("../data/utest/ut-save_file-f.mrw");
  std::istream_iterator<char> bfg(ifsfg), efg;
  std::istream_iterator<char> bfr(ifsfr), efr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bfg, efg, bfr, efr);

  // I checked this file qby hand on 2022-08-28. sha256: 24c15670cd4776abbad82f9ad3fa6c83c90dca367c6931bb9dce6b7565108a97
  // hexDump.rb -t 0 -c -w 16 -b 1 -p 100 ut-save_file-g.mrw | less -RS
  std::ifstream ifsgg("ut-save_file-g.mrw");
  std::ifstream ifsgr("../data/utest/ut-save_file-g.mrw");
  std::istream_iterator<char> bgg(ifsgg), egg;
  std::istream_iterator<char> bgr(ifsgr), egr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bgg, egg, bgr, egr);

  // I checked this file qby hand on 2022-08-28. sha256: a2daf01cd91b48e850b4db7424dc06d689fe557bc777b20f7dda6954c9bd0618
  // hexDump.rb -t 0 -c -w 16 -b 2 -p 100 ut-save_file-h.mrw | less -RS
  std::ifstream ifshg("ut-save_file-h.mrw");
  std::ifstream ifshr("../data/utest/ut-save_file-h.mrw");
  std::istream_iterator<char> bhg(ifshg), ehg;
  std::istream_iterator<char> bhr(ifshr), ehr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bhg, ehg, bhr, ehr);

  // I checked this file qby hand on 2022-08-28. sha256: e54e75ae84fe412648121cf55ba39a0c05405474a0a1cd19ac6dfc92ac839be0 *ut-save_file-i.mrw
  // hexDump.rb -t 0 -c -w 16 -b 4 -p 100 ut-save_file-i.mrw | less -RS
  std::ifstream ifsig("ut-save_file-i.mrw");
  std::ifstream ifsir("../data/utest/ut-save_file-i.mrw");
  std::istream_iterator<char> big(ifsig), eig;
  std::istream_iterator<char> bir(ifsir), eir;
  BOOST_CHECK_EQUAL_COLLECTIONS(big, eig, bir, eir);

  // I checked this file qby hand on 2022-08-28. sha256: 3144a77040b5a25c9c089d7cf32d6ee0f832a23b71de1f2d1b3fafab4b82408c
  // hexDump.rb -t 0 -c -w 16 -b 8 -p 100 ut-save_file-j.mrw | less -RS
  std::ifstream ifsjg("ut-save_file-j.mrw");
  std::ifstream ifsjr("../data/utest/ut-save_file-j.mrw");
  std::istream_iterator<char> bjg(ifsjg), ejg;
  std::istream_iterator<char> bjr(ifsjr), ejr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bjg, ejg, bjr, ejr);

  // I checked this file qby hand on 2022-08-28. sha256: 25ce4b85baca2aa4ea8f4635e82abb4e1aa92e55ec6a9caf9b5558a1d0574a66
  // hexDump.rb -t 0 -c -w 16 -b 4 -p 100 ut-save_file-k.mrw | less -RS
  std::ifstream ifskg("ut-save_file-k.mrw");
  std::ifstream ifskr("../data/utest/ut-save_file-k.mrw");
  std::istream_iterator<char> bkg(ifskg), ekg;
  std::istream_iterator<char> bkr(ifskr), ekr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bkg, ekg, bkr, ekr);

  // I checked this file qby hand on 2022-08-28. sha256: 007879b182639b37a54358067f742c86bccb1ec0cb85a67a9f648ebf56c44294
  // I did the conversion by hand, so I should double check it...
  // hexDump.rb -t -1 -c -w 16 -b 8 -p 100 ut-save_file-l.mrw | less -RS
  std::ifstream ifslg("ut-save_file-l.mrw");
  std::ifstream ifslr("../data/utest/ut-save_file-l.mrw");
  std::istream_iterator<char> blg(ifslg), elg;
  std::istream_iterator<char> blr(ifslr), elr;
  BOOST_CHECK_EQUAL_COLLECTIONS(blg, elg, blr, elr);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(circles) {

  mjr::ramCanvas1c8b aRamCanvas(63, 63);
  mjr::ramCanvas1c8b bRamCanvas(63, 63);
  mjr::color1c8b aColor(mjr::color1c8b::cornerColorEnum::WHITE);
  mjr::color1c8b bColor(mjr::color1c8b::cornerColorEnum::BLACK);

  for(int i=2; i<32; i+=2)
    aRamCanvas.drawCircle(31, 31, i, aColor);

  bRamCanvas.drawFillCircle(31, 31, 30, aColor);

  aRamCanvas.writeRAWfile("ut-circles-a.mrw");
  bRamCanvas.writeRAWfile("ut-circles-b.mrw");

  aRamCanvas.scaleUpProximal(8);
  bRamCanvas.scaleUpProximal(8);

  aRamCanvas.writeTIFFfile("ut-circles-a.tiff");
  bRamCanvas.writeTIFFfile("ut-circles-b.tiff");

  std::ifstream ifsag("ut-circles-a.mrw");
  std::ifstream ifsar("../data/utest/ut-circles-a.mrw");
  std::istream_iterator<char> bag(ifsag), eag;
  std::istream_iterator<char> bar(ifsar), ear;
  BOOST_CHECK_EQUAL_COLLECTIONS(bag, eag, bar, ear);

  std::ifstream ifsbg("ut-circles-b.mrw");
  std::ifstream ifsbr("../data/utest/ut-circles-b.mrw");
  std::istream_iterator<char> bbg(ifsbg), ebg;
  std::istream_iterator<char> bbr(ifsbr), ebr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bbg, ebg, bbr, ebr);

  mjr::ramCanvas1c8b cRamCanvas(32, 32);
  cRamCanvas.drawCircle(31, 31, 16, aColor);
  cRamCanvas.drawCircle(16, -5, 15, aColor);
  cRamCanvas.drawCircle(5,  20, 8, aColor);

  cRamCanvas.writeRAWfile("ut-circles-c.mrw");
  cRamCanvas.scaleUpProximal(20);
  cRamCanvas.writeTIFFfile("ut-circles-c.tiff");

  std::ifstream ifscg("ut-circles-c.mrw");
  std::ifstream ifscr("../data/utest/ut-circles-c.mrw");
  std::istream_iterator<char> bcg(ifscg), ecg;
  std::istream_iterator<char> bcr(ifscr), ecr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bcg, ecg, bcr, ecr);

  mjr::ramCanvas1c8b dRamCanvas(32, 32);
  dRamCanvas.drawFillCircle(31, 31, 16, aColor);
  dRamCanvas.drawFillCircle(16, -5, 15, aColor);
  dRamCanvas.drawFillCircle(5,  20, 8, aColor);

  dRamCanvas.writeRAWfile("ut-circles-d.mrw");
  dRamCanvas.scaleUpProximal(20);
  dRamCanvas.writeTIFFfile("ut-circles-d.tiff");

  std::ifstream ifsdg("ut-circles-d.mrw");
  std::ifstream ifsdr("../data/utest/ut-circles-d.mrw");
  std::istream_iterator<char> bdg(ifsdg), edg;
  std::istream_iterator<char> bdr(ifsdr), edr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bdg, edg, bdr, edr);

  mjr::ramCanvas1c8b eRamCanvas(32, 32);
  eRamCanvas.drawFillCircle(16, 16, 17, aColor);

  eRamCanvas.writeRAWfile("ut-circles-e.mrw");
  eRamCanvas.scaleUpProximal(20);
  eRamCanvas.writeTIFFfile("ut-circles-e.tiff");

  std::ifstream ifseg("ut-circles-e.mrw");
  std::ifstream ifser("../data/utest/ut-circles-e.mrw");
  std::istream_iterator<char> beg(ifseg), eeg;
  std::istream_iterator<char> ber(ifser), eer;
  BOOST_CHECK_EQUAL_COLLECTIONS(beg, eeg, ber, eer);

  mjr::ramCanvas1c8b fRamCanvas(32, 32);
  fRamCanvas.drawFillCircle(16, 16, 50, aColor);

  fRamCanvas.writeRAWfile("ut-circles-f.mrw");
  fRamCanvas.scaleUpProximal(20);
  fRamCanvas.writeTIFFfile("ut-circles-f.tiff");

  std::ifstream ifsfg("ut-circles-f.mrw");
  std::ifstream ifsfr("../data/utest/ut-circles-f.mrw");
  std::istream_iterator<char> bfg(ifsfg), efg;
  std::istream_iterator<char> bfr(ifsfr), efr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bfg, efg, bfr, efr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(rectanglesO) {

  // The drawRectangle method is pretty simple, but has several edge cases around clipping.  It is also weird about how it uses it's arguments.

  mjr::ramCanvas1c8b::colorType aColor(mjr::ramCanvas1c8b::colorType::cornerColorEnum::WHITE);

  // open: The args are used not points (x1, y1) & (x2, y2), but rather as x and y ranges.
  mjr::ramCanvas1c8b aRamCanvas(9, 9);
  mjr::ramCanvas1c8b bRamCanvas(9, 9);

  aRamCanvas.drawRectangle(1, 1, 7, 7, aColor);

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawRectangle(1, 1, 7, 7, aColor);
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawRectangle(7, 1, 1, 7, aColor);
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawRectangle(1, 7, 7, 1, aColor);
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawRectangle(7, 7, 1, 1, aColor);
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());

  aRamCanvas.writeRAWfile("ut-rectanglesO-a.mrw");
  aRamCanvas.scaleUpProximal(20);
  aRamCanvas.writeTIFFfile("ut-rectanglesO-a.tiff");

  // open: clip ALL corner (canvas inside rectangle)
  mjr::ramCanvas1c8b cRamCanvas(9, 9);

  cRamCanvas.drawRectangle(-4, -2, 25,  12, aColor);

  cRamCanvas.writeRAWfile("ut-rectanglesO-c.mrw");
  cRamCanvas.scaleUpProximal(20);
  cRamCanvas.writeTIFFfile("ut-rectanglesO-c.tiff");

  std::ifstream ifscg("ut-rectanglesO-c.mrw");
  std::ifstream ifscr("../data/utest/ut-rectanglesO-c.mrw");
  std::istream_iterator<char> bcg(ifscg), ecg;
  std::istream_iterator<char> bcr(ifscr), ecr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bcg, ecg, bcr, ecr);

  // open: clip ALL corner (canvas inside rectangle)
  mjr::ramCanvas1c8b dRamCanvas(9, 9);

  dRamCanvas.drawRectangle(-9,  2, -4,   7, aColor); // to left
  dRamCanvas.drawRectangle(16,  2, 24,   7, aColor); // to right
  dRamCanvas.drawRectangle( 2,  12, 7,  17, aColor); // to top
  dRamCanvas.drawRectangle( 2, -17, 7, -10, aColor); // to bot
  dRamCanvas.drawRectangle(-9, -15, -4, -7, aColor); // to left below
  dRamCanvas.drawRectangle(10,  15, 14, 17, aColor); // to right up

  dRamCanvas.writeRAWfile("ut-rectanglesO-d.mrw");
  dRamCanvas.scaleUpProximal(20);
  dRamCanvas.writeTIFFfile("ut-rectanglesO-d.tiff");

  std::ifstream ifsdg("ut-rectanglesO-d.mrw");
  std::ifstream ifsdr("../data/utest/ut-rectanglesO-d.mrw");
  std::istream_iterator<char> bdg(ifsdg), edg;
  std::istream_iterator<char> bdr(ifsdr), edr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bdg, edg, bdr, edr);

  // open: clip one corner
  mjr::ramCanvas1c8b eRamCanvas(9, 9);

  eRamCanvas.drawRectangle( 6,  6, 12,  12, aColor);
  eRamCanvas.drawRectangle( 6,  2, 12, -12, aColor);
  eRamCanvas.drawRectangle(-6,  6,  2,  16, aColor);
  eRamCanvas.drawRectangle(-6, -6,  2,   2, aColor);

  eRamCanvas.writeRAWfile("ut-rectanglesO-e.mrw");
  eRamCanvas.scaleUpProximal(20);
  eRamCanvas.writeTIFFfile("ut-rectanglesO-e.tiff");

  std::ifstream ifseg("ut-rectanglesO-e.mrw");
  std::ifstream ifser("../data/utest/ut-rectanglesO-e.mrw");
  std::istream_iterator<char> beg(ifseg), eeg;
  std::istream_iterator<char> ber(ifser), eer;
  BOOST_CHECK_EQUAL_COLLECTIONS(beg, eeg, ber, eer);

  // open: clip one side
  mjr::ramCanvas1c8b fRamCanvas(9, 9);

  fRamCanvas.drawRectangle( 2,   7,  6, 12, aColor); // top
  fRamCanvas.drawRectangle( 7,   2, 20,  6, aColor); // right
  fRamCanvas.drawRectangle(-6,   2,  1,  6, aColor);  // left
  fRamCanvas.drawRectangle( 2, -27,  6,  1, aColor); // bot

  fRamCanvas.writeRAWfile("ut-rectanglesO-f.mrw");
  fRamCanvas.scaleUpProximal(20);
  fRamCanvas.writeTIFFfile("ut-rectanglesO-f.tiff");

  std::ifstream ifsfg("ut-rectanglesO-f.mrw");
  std::ifstream ifsfr("../data/utest/ut-rectanglesO-f.mrw");
  std::istream_iterator<char> bfg(ifsfg), efg;
  std::istream_iterator<char> bfr(ifsfr), efr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bfg, efg, bfr, efr);

  // open: clip one side (T/B)
  mjr::ramCanvas1c8b gRamCanvas(9, 9);

  gRamCanvas.drawRectangle(-3,   7, 26, 12, aColor); // top
  gRamCanvas.drawRectangle(-4, -27, 30,  1, aColor); // bot

  gRamCanvas.writeRAWfile("ut-rectanglesO-g.mrw");
  gRamCanvas.scaleUpProximal(20);
  gRamCanvas.writeTIFFfile("ut-rectanglesO-g.tiff");

  std::ifstream ifsgg("ut-rectanglesO-g.mrw");
  std::ifstream ifsgr("../data/utest/ut-rectanglesO-g.mrw");
  std::istream_iterator<char> bgg(ifsgg), egg;
  std::istream_iterator<char> bgr(ifsgr), egr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bgg, egg, bgr, egr);

  // open: clip one side (L/R)
  mjr::ramCanvas1c8b hRamCanvas(9, 9);

  hRamCanvas.drawRectangle( 7,  -2, 20, 36, aColor); // right
  hRamCanvas.drawRectangle(-6,  -5,  1, 16, aColor);  // left

  hRamCanvas.writeRAWfile("ut-rectanglesO-h.mrw");
  hRamCanvas.scaleUpProximal(20);
  hRamCanvas.writeTIFFfile("ut-rectanglesO-h.tiff");

  std::ifstream ifshg("ut-rectanglesO-h.mrw");
  std::ifstream ifshr("../data/utest/ut-rectanglesO-h.mrw");
  std::istream_iterator<char> bhg(ifshg), ehg;
  std::istream_iterator<char> bhr(ifshr), ehr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bhg, ehg, bhr, ehr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(rectanglesF) {

  // The drawFillRectangle method is pretty simple, but has several edge cases around clipping.  It is also weird about how it uses it's arguments.

  mjr::ramCanvas1c8b::colorType aColor(mjr::ramCanvas1c8b::colorType::cornerColorEnum::WHITE);

  // open: The args are used not points (x1, y1) & (x2, y2), but rather as x and y ranges.
  mjr::ramCanvas1c8b aRamCanvas(9, 9);
  mjr::ramCanvas1c8b bRamCanvas(9, 9);

  aRamCanvas.drawFillRectangle(1, 1, 7, 7, aColor);

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawFillRectangle(1, 1, 7, 7, aColor);
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawFillRectangle(7, 1, 1, 7, aColor);
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawFillRectangle(1, 7, 7, 1, aColor);
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());

  bRamCanvas.clrCanvasToBlack();
  bRamCanvas.drawFillRectangle(7, 7, 1, 1, aColor);
  BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());

  aRamCanvas.writeRAWfile("ut-rectanglesF-a.mrw");
  aRamCanvas.scaleUpProximal(20);
  aRamCanvas.writeTIFFfile("ut-rectanglesF-a.tiff");

  // open: clip ALL corner (canvas inside rectangle)
  mjr::ramCanvas1c8b cRamCanvas(9, 9);

  cRamCanvas.drawFillRectangle(-4, -2, 25,  12, aColor);

  cRamCanvas.writeRAWfile("ut-rectanglesF-c.mrw");
  cRamCanvas.scaleUpProximal(20);
  cRamCanvas.writeTIFFfile("ut-rectanglesF-c.tiff");

  std::ifstream ifscg("ut-rectanglesF-c.mrw");
  std::ifstream ifscr("../data/utest/ut-rectanglesF-c.mrw");
  std::istream_iterator<char> bcg(ifscg), ecg;
  std::istream_iterator<char> bcr(ifscr), ecr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bcg, ecg, bcr, ecr);

  // open: clip ALL corner (canvas inside rectangle)
  mjr::ramCanvas1c8b dRamCanvas(9, 9);

  dRamCanvas.drawFillRectangle(-9,  2, -4,   7, aColor); // to left
  dRamCanvas.drawFillRectangle(16,  2, 24,   7, aColor); // to right
  dRamCanvas.drawFillRectangle( 2,  12, 7,  17, aColor); // to top
  dRamCanvas.drawFillRectangle( 2, -17, 7, -10, aColor); // to bot
  dRamCanvas.drawFillRectangle(-9, -15, -4, -7, aColor); // to left below
  dRamCanvas.drawFillRectangle(10,  15, 14, 17, aColor); // to right up

  dRamCanvas.writeRAWfile("ut-rectanglesF-d.mrw");
  dRamCanvas.scaleUpProximal(20);
  dRamCanvas.writeTIFFfile("ut-rectanglesF-d.tiff");

  std::ifstream ifsdg("ut-rectanglesF-d.mrw");
  std::ifstream ifsdr("../data/utest/ut-rectanglesF-d.mrw");
  std::istream_iterator<char> bdg(ifsdg), edg;
  std::istream_iterator<char> bdr(ifsdr), edr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bdg, edg, bdr, edr);

  // open: clip one corner
  mjr::ramCanvas1c8b eRamCanvas(9, 9);

  eRamCanvas.drawFillRectangle( 6,  6, 12,  12, aColor);
  eRamCanvas.drawFillRectangle( 6,  2, 12, -12, aColor);
  eRamCanvas.drawFillRectangle(-6,  6,  2,  16, aColor);
  eRamCanvas.drawFillRectangle(-6, -6,  2,   2, aColor);

  eRamCanvas.writeRAWfile("ut-rectanglesF-e.mrw");
  eRamCanvas.scaleUpProximal(20);
  eRamCanvas.writeTIFFfile("ut-rectanglesF-e.tiff");

  std::ifstream ifseg("ut-rectanglesF-e.mrw");
  std::ifstream ifser("../data/utest/ut-rectanglesF-e.mrw");
  std::istream_iterator<char> beg(ifseg), eeg;
  std::istream_iterator<char> ber(ifser), eer;
  BOOST_CHECK_EQUAL_COLLECTIONS(beg, eeg, ber, eer);

  // open: clip one side
  mjr::ramCanvas1c8b fRamCanvas(9, 9);

  fRamCanvas.drawFillRectangle( 2,   7,  6, 12, aColor); // top
  fRamCanvas.drawFillRectangle( 7,   2, 20,  6, aColor); // right
  fRamCanvas.drawFillRectangle(-6,   2,  1,  6, aColor);  // left
  fRamCanvas.drawFillRectangle( 2, -27,  6,  1, aColor); // bot

  fRamCanvas.writeRAWfile("ut-rectanglesF-f.mrw");
  fRamCanvas.scaleUpProximal(20);
  fRamCanvas.writeTIFFfile("ut-rectanglesF-f.tiff");

  std::ifstream ifsfg("ut-rectanglesF-f.mrw");
  std::ifstream ifsfr("../data/utest/ut-rectanglesF-f.mrw");
  std::istream_iterator<char> bfg(ifsfg), efg;
  std::istream_iterator<char> bfr(ifsfr), efr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bfg, efg, bfr, efr);

  // open: clip one side (T/B)
  mjr::ramCanvas1c8b gRamCanvas(9, 9);

  gRamCanvas.drawFillRectangle(-3,   7, 26, 12, aColor); // top
  gRamCanvas.drawFillRectangle(-4, -27, 30,  1, aColor); // bot

  gRamCanvas.writeRAWfile("ut-rectanglesF-g.mrw");
  gRamCanvas.scaleUpProximal(20);
  gRamCanvas.writeTIFFfile("ut-rectanglesF-g.tiff");

  std::ifstream ifsgg("ut-rectanglesF-g.mrw");
  std::ifstream ifsgr("../data/utest/ut-rectanglesF-g.mrw");
  std::istream_iterator<char> bgg(ifsgg), egg;
  std::istream_iterator<char> bgr(ifsgr), egr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bgg, egg, bgr, egr);

  // open: clip one side (L/R)
  mjr::ramCanvas1c8b hRamCanvas(9, 9);

  hRamCanvas.drawFillRectangle( 7,  -2, 20, 36, aColor); // right
  hRamCanvas.drawFillRectangle(-6,  -5,  1, 16, aColor);  // left

  hRamCanvas.writeRAWfile("ut-rectanglesF-h.mrw");
  hRamCanvas.scaleUpProximal(20);
  hRamCanvas.writeTIFFfile("ut-rectanglesF-h.tiff");

  std::ifstream ifshg("ut-rectanglesF-h.mrw");
  std::ifstream ifshr("../data/utest/ut-rectanglesF-h.mrw");
  std::istream_iterator<char> bhg(ifshg), ehg;
  std::istream_iterator<char> bhr(ifshr), ehr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bhg, ehg, bhr, ehr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(draw_point) {

  mjr::ramCanvasRGB8b aRamCanvas(20, 20, 0.0, 19.0, 0.0, 19.0);
  aRamCanvas.setRealAxOrientationY(mjr::ramCanvasRGB8b::realAxisOrientation::INVERTED);
  mjr::colorRGB8b aColor(mjr::colorRGB8b::cornerColorEnum::RED);
  mjr::colorRGB8b bColor(mjr::colorRGB8b::cornerColorEnum::BLUE);
  mjr::colorRGB8b cColor(mjr::colorRGB8b::cornerColorEnum::MAGENTA);
  mjr::colorRGB8b dColor(mjr::colorRGB8b::cornerColorEnum::CYAN);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType({2, 2}),                      aColor);  // Initializeer list
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(4, 2),                        bColor);  // two arg
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(std::tuple<int,int>(6, 2)),   aColor);  // tuple<int,int>
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(std::tuple<int,short>(8, 2)), bColor);  // tuple<int,short>
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(std::complex<int>(10, 2)),    aColor);  // complex<int>
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(std::vector<int>({14, 2})),   aColor);  // vector<int)
  int aArI[2] = {16, 2};
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(aArI),                        bColor);  // array of int
  int aArS[2] = {18, 2};
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointIntType(aArS),                        aColor);  // array of short

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawPoint(std::complex<int>(2, 4),     bColor);                                     // complex<int>    -- complex<short>   no work
  aRamCanvas.drawPoint(std::tuple<int,int>(4, 4),   aColor);                                     // tuple<int,int>  -- tuple<int,short> no work
  aRamCanvas.drawPoint(std::vector<int>({6, 4}),    bColor);                                     // vector<int>

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType({2, 2}),                       cColor); // Initializeer list
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(4, 2),                         dColor); // two arg
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(std::tuple<int,int>(6, 2)),    cColor); // tuple<int,int>
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(std::tuple<int,short>(8, 2)),  dColor); // tuple<int,short>
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(std::complex<double>(10, 2)),  cColor); // complex<double>
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(std::complex<double>(12, 2)),  dColor); // complex<double>
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(std::vector<double>({14, 2})), cColor); // vector<double>
  double aArD[2] = {16, 2};
  aRamCanvas.drawPoint(mjr::ramCanvasRGB8b::pointFltType(aArD),                         dColor); // array of double

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.drawPoint(std::complex<double>(2, 4),       dColor);                                // complex<double>   -- complex<double> no work
  aRamCanvas.drawPoint(std::tuple<double,double>(4, 4),  cColor);                                // tuple<double,double>  -- tuple<double,double> no work
  aRamCanvas.drawPoint(std::vector<double>({6, 4}),      dColor);                                // vector<double>

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.writeRAWfile("ut-points-a.mrw");
  aRamCanvas.scaleUpProximal(20);
  aRamCanvas.writeTIFFfile("ut-points-a.tiff");
  
  std::ifstream ifsag("ut-points-a.mrw");
  std::ifstream ifsar("../data/utest/ut-points-a.mrw");
  std::istream_iterator<char> bag(ifsag), eag;
  std::istream_iterator<char> bar(ifsar), ear;
  BOOST_CHECK_EQUAL_COLLECTIONS(bag, eag, bar, ear);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(lines_ep_swap) {

// Make sure we get the same result regardless of point order in drawLine call

  mjr::ramCanvas1c8b aRamCanvas(16, 16);
  mjr::ramCanvas1c8b bRamCanvas(16, 16);
  mjr::ramCanvas1c8b::colorType aColor(mjr::ramCanvas1c8b::colorType::cornerColorEnum::WHITE);

  int x1, y1, x2, y2;
  for(int i=0; i<16; i++) {
    y1 = i;
    x1 = 0;
    y2 = 15-y1;
    x2 = 15;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());
    y1 = 0;
    x1 = i;
    y2 = 15;
    x2 = 15-x1;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());
    // Clip on right
    y1 = i;
    x1 = 0;
    y2 = 15-y1;
    x2 = 25;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());
    // Clip on top
    y1 = 0;
    x1 = i;
    y2 = 25;
    x2 = 15-x1;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());
    // Clip on left
    y1 = i;
    x1 = -5;
    y2 = 15-y1;
    x2 = 15;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());
    // Clip on bot
    y1 = -10;
    x1 = i;
    y2 = 15;
    x2 = 15-x1;
    aRamCanvas.clrCanvasToBlack();
    aRamCanvas.drawLine(x1, y1, x2, y2, aColor);
    bRamCanvas.clrCanvasToBlack();
    bRamCanvas.drawLine(x2, y2, x1, y1, aColor);
    BOOST_CHECK_EQUAL_COLLECTIONS(aRamCanvas.begin(), aRamCanvas.end(), bRamCanvas.begin(), bRamCanvas.end());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(btriangle) {

  mjr::ramCanvas3c8b aRamCanvas(153, 83);

  aRamCanvas.drawFillTriangle(81, 31, 1, 9, 51, 81, "green", "red",   "blue");
  aRamCanvas.drawTriangle    (81, 31, 1, 9, 51, 81, "white");

  aRamCanvas.drawFillTriangle(71, 1, 151, 31, 121, 81, "red",   "green", "blue");
  aRamCanvas.drawTriangle    (71, 1, 151, 31, 121, 81, "white");

  aRamCanvas.writeRAWfile("ut-btriangle-a.mrw");
  aRamCanvas.scaleUpProximal(20);
  aRamCanvas.writeTIFFfile("ut-btriangle-a.tiff");
  
  std::ifstream ifsag("ut-btriangle-a.mrw");
  std::ifstream ifsar("../data/utest/ut-btriangle-a.mrw");
  std::istream_iterator<char> bag(ifsag), eag;
  std::istream_iterator<char> bar(ifsar), ear;
  BOOST_CHECK_EQUAL_COLLECTIONS(bag, eag, bar, ear);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(glyph_axis) {

  // Make sure glyphs render right side up and forward.  The images in RAM will differ, but the *FILES* should be identical.

  mjr::ramCanvas3c8b aRamCanvas(127, 127);
  aRamCanvas.drawLine(0, 63, 127, 63, "blue");
  aRamCanvas.drawLine(63, 0, 63, 127, "blue");
  aRamCanvas.setIntAxOrientationX(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  aRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  aRamCanvas.drawHersheyGlyph(505, 63, 63,  1,  1, "red");
  aRamCanvas.drawHersheyGlyph(505, 63, 63,  2,  2, "red");
  aRamCanvas.drawHersheyGlyph(505, 63, 63,  4,  4, "red");


  aRamCanvas.writeRAWfile("ut-glyph_axis-a.mrw");
  aRamCanvas.scaleUpProximal(4);
  aRamCanvas.writeTIFFfile("ut-glyph_axis-a.tiff");

  mjr::ramCanvas3c8b bRamCanvas(127, 127);
  bRamCanvas.drawLine(0, 63, 127, 63, "blue");
  bRamCanvas.drawLine(63, 0, 63, 127, "blue");
  bRamCanvas.setIntAxOrientationX(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  bRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  bRamCanvas.drawHersheyGlyph(505, 63, 63,  1,  1, "red");
  bRamCanvas.drawHersheyGlyph(505, 63, 63,  2,  2, "red");
  bRamCanvas.drawHersheyGlyph(505, 63, 63,  4,  4, "red");
  
  bRamCanvas.writeRAWfile("ut-glyph_axis-b.mrw");
  bRamCanvas.scaleUpProximal(4);
  bRamCanvas.writeTIFFfile("ut-glyph_axis-b.tiff");

  mjr::ramCanvas3c8b cRamCanvas(127, 127);
  cRamCanvas.drawLine(0, 63, 127, 63, "blue");
  cRamCanvas.drawLine(63, 0, 63, 127, "blue");
  cRamCanvas.setIntAxOrientationX(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  cRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::NATURAL);
  cRamCanvas.drawHersheyGlyph(505, 63, 63,  1,  1, "red");
  cRamCanvas.drawHersheyGlyph(505, 63, 63,  2,  2, "red");
  cRamCanvas.drawHersheyGlyph(505, 63, 63,  4,  4, "red");

  cRamCanvas.writeRAWfile("ut-glyph_axis-c.mrw");
  cRamCanvas.scaleUpProximal(4);
  cRamCanvas.writeTIFFfile("ut-glyph_axis-c.tiff");

  mjr::ramCanvas3c8b dRamCanvas(127, 127);
  dRamCanvas.drawLine(0, 63, 127, 63, "blue");
  dRamCanvas.drawLine(63, 0, 63, 127, "blue");
  dRamCanvas.setIntAxOrientationX(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  dRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  dRamCanvas.drawHersheyGlyph(505, 63, 63,  1,  1, "red");
  dRamCanvas.drawHersheyGlyph(505, 63, 63,  2,  2, "red");
  dRamCanvas.drawHersheyGlyph(505, 63, 63,  4,  4, "red");

  dRamCanvas.writeRAWfile("ut-glyph_axis-d.mrw");
  dRamCanvas.scaleUpProximal(4);
  dRamCanvas.writeTIFFfile("ut-glyph_axis-d.tiff");
  
  std::ifstream ifsag("ut-glyph_axis-a.mrw");
  std::ifstream ifsaar("../data/utest/ut-glyph_axis-a.mrw");
  std::istream_iterator<char> bag(ifsag), eag;
  std::istream_iterator<char> baar(ifsaar), eaar;
  BOOST_CHECK_EQUAL_COLLECTIONS(bag, eag, baar, eaar);

  std::ifstream ifsbg("ut-glyph_axis-b.mrw");
  std::ifstream ifsabr("../data/utest/ut-glyph_axis-a.mrw");
  std::istream_iterator<char> bbg(ifsbg), ebg;
  std::istream_iterator<char> babr(ifsabr), eabr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bbg, ebg, babr, eabr);

  std::ifstream ifscg("ut-glyph_axis-c.mrw");
  std::ifstream ifsacr("../data/utest/ut-glyph_axis-a.mrw");
  std::istream_iterator<char> bcg(ifscg), ecg;
  std::istream_iterator<char> bacr(ifsacr), eacr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bcg, ecg, bacr, eacr);

  std::ifstream ifsdg("ut-glyph_axis-d.mrw");
  std::ifstream ifsadr("../data/utest/ut-glyph_axis-a.mrw");
  std::istream_iterator<char> bdg(ifsdg), edg;
  std::istream_iterator<char> badr(ifsadr), eadr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bdg, edg, badr, eadr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(strings) {

  mjr::ramCanvas3c8b aRamCanvas(450, 100);
  int y;
  aRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  aRamCanvas.drawLine(50, 0,  50, 512, "blue");
  y = 18;
  aRamCanvas.drawLine(0, y,   1024, y, "blue");
  aRamCanvas.drawString("Hello, World!", mjr::hershey::font::ROMAN_SL_SANSERIF, 50, y, "red",  1, 16);
  y+=50;
  aRamCanvas.drawLine(0, y,   1024, y, "blue");
  aRamCanvas.drawString("Hello, World!", mjr::hershey::font::ROMAN_SL_SANSERIF, 50, y, "red",  2, 15);

  aRamCanvas.writeRAWfile("ut-strings-a.mrw");
  aRamCanvas.scaleUpProximal(4);
  aRamCanvas.writeTIFFfile("ut-strings-a.tiff");

  std::ifstream ifsag("ut-strings-a.mrw");
  std::ifstream ifsar("../data/utest/ut-strings-a.mrw");
  std::istream_iterator<char> bag(ifsag), eag;
  std::istream_iterator<char> bar(ifsar), ear;
  BOOST_CHECK_EQUAL_COLLECTIONS(bag, eag, bar, ear);

  mjr::ramCanvas3c8b bRamCanvas(450, 100);
  bRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED);
  y =18;
  bRamCanvas.drawStringBox("Hello, World!", mjr::hershey::font::ROMAN_SL_SANSERIF, 50, y, "red", "green",  1, 16);
  bRamCanvas.drawLine(0, y,   1024, y, "blue");
  y+=50;
  bRamCanvas.drawStringBox("Hello, World!", mjr::hershey::font::ROMAN_SL_SANSERIF, 50, y, "red", "green",  2, 15);
  bRamCanvas.drawLine(0, y,   1024, y, "blue");
  bRamCanvas.drawLine(50, 0,  50, 512, "blue");

  bRamCanvas.writeRAWfile("ut-strings-b.mrw");
  bRamCanvas.scaleUpProximal(4);
  bRamCanvas.writeTIFFfile("ut-strings-b.tiff");
  
  std::ifstream ifsbg("ut-strings-b.mrw");
  std::ifstream ifsbr("../data/utest/ut-strings-b.mrw");
  std::istream_iterator<char> bbg(ifsbg), ebg;
  std::istream_iterator<char> bbr(ifsbr), ebr;
  BOOST_CHECK_EQUAL_COLLECTIONS(bbg, ebg, bbr, ebr);
}

#endif

/** @endcond */


// TODO:
//  - Convert test_draw_fonts.cpp to a demo
//  - Add unit tests for fonts
//  - Test TIFF files in save_file test case -- ex: tiffinfo to at least check for correct tags.
//  - Geometric transforms
//  - Homogeneous transforms
//  - Convolution


  // XRamCanvas.writeRAWfile("ut-strings-X.mrw");
  // XRamCanvas.scaleUpProximal(20);
  // XRamCanvas.writeTIFFfile("ut-strings-X.tiff");
  //
  // std::ifstream ifsXg("ut-strings-X.mrw");
  // std::ifstream ifsXr("../data/utest/ut-strings-X.mrw");
  // std::istream_iterator<char> bXg(ifsXg), eXg;
  // std::istream_iterator<char> bXr(ifsXr), eXr;
  // BOOST_CHECK_EQUAL_COLLECTIONS(bXg, eXg, bXr, eXr);

/** @endcond */
