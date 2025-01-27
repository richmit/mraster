// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      r_draw_primatives.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2025-01-25
 @brief     Unit tests for basic color methods.@EOL
 @keywords  gtest
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 2022-2025, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(r_draw_primatives, int_coordinates) {

  // We instantiate every drawing function in ramCanvas so that we can check for compile time errors and do some basic functionality testing.

  const int BSIZE = 60;

  mjr::ramCanvasRGB8b aRamCanvas(BSIZE, BSIZE, 0, BSIZE-1, 0, BSIZE-1); mjr::ramCanvasRGB8b RaRamCanvas(BSIZE, BSIZE, 0, BSIZE-1, 0, BSIZE-1);
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
  EXPECT_EQ(RaRamCanvas.readRAWfile("../data/utest/ut-draw_primatives_int.mrw"), 0);
  EXPECT_TRUE(RaRamCanvas.isEqual(aRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.scaleUpProximal(5);
  aRamCanvas.writeTIFFfile("ut-draw_primatives_int.tiff");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(r_draw_primatives, float_coordinates) {


  // We instantiate every drawing function in ramCanvas so that we can check for compile time errors and do some basic functionality testing.

  const int BSIZE = 60;

  mjr::ramCanvasRGB32F aRamCanvas(BSIZE, BSIZE, 0, BSIZE-1, 0, BSIZE-1); mjr::ramCanvasRGB32F RaRamCanvas(BSIZE, BSIZE, 0, BSIZE-1, 0, BSIZE-1);
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
  EXPECT_EQ(RaRamCanvas.readRAWfile("../data/utest/ut-draw_primatives_flt.mrw"), 0);
  EXPECT_TRUE(RaRamCanvas.isEqual(aRamCanvas));

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
  aRamCanvas.scaleUpProximal(5);
  aRamCanvas.writeTIFFfile("ut-draw_primatives_flt.tiff");
}
