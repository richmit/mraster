// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      test_draw_primatives.cpp
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

   We instantiate every drawing function in ramCanvas so that we can check for compile time errors and do some basic functionality testing.

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

int main(void) {
  const int BSIZE = 60;

  mjr::ramCanvasRGB8b theRamCanvas(BSIZE, BSIZE, 0, BSIZE-1, 0, BSIZE-1);
  mjr::colorRGB8b aColor(mjr::colorRGB8b::cornerColor::RED);
  mjr::colorRGB8b bColor(mjr::colorRGB8b::cornerColor::GREEN);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  theRamCanvas.drawPoint(1, 1, aColor);                                               // drawPoint(iCrd x, iCrd y, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.moveTo(2, 1);
  theRamCanvas.drawPoint();                                                           // drawPoint();
  theRamCanvas.moveTo(3, 1);
  theRamCanvas.drawPoint(aColor);                                                     // drawPoint(clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawPoint(4, 1);                                                       // drawPoint(iCrd x, iCrd y);
  theRamCanvas.setDfltColor(aColor);
  theRamCanvas.drawPoint(5.0, 2.0);                                                   // drawPoint(fCrd x, fCrd y);
  theRamCanvas.drawPoint(6.0, 2.0, bColor);                                           // drawPoint(fCrd x, fCrd y, clr color);
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::rcPointInt({7, 1}), aColor);                 // drawPoint(iPnt thePoint, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::rcPointInt({8, 1}));                         // drawPoint(iPnt thePoint);
  theRamCanvas.setDfltColor(aColor);
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::rcPointFlt({9.0, 2.0}));                     // drawPoint(fPnt thePoint);
  theRamCanvas.drawPoint(mjr::ramCanvasRGB8b::rcPointFlt({10.0, 2.0}), bColor);            // drawPoint(fPnt thePoint, clr color);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  theRamCanvas.drawLine(1, 4, 1, 6, aColor);                                          // drawLine(iCrd x1, iCrd y1, iCrd x2, iCrd y2, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.moveTo(2, 4);
  theRamCanvas.drawLine(2, 6);                                                        // drawLine(iCrd x,  iCrd y);
  theRamCanvas.setDfltColor(aColor);
  theRamCanvas.moveTo(3.0, 5.0);
  theRamCanvas.drawLine(3.0, 7.0);                                                    // drawLine(fCrd x,  fCrd y);
  theRamCanvas.moveTo(4, 4);
  theRamCanvas.drawLine(4, 6, bColor);                                                // drawLine(iCrd x,  iCrd y,  clr color);
  theRamCanvas.moveTo(5.0, 5.0);
  theRamCanvas.drawLine(5.0, 7.0, aColor);                                            // drawLine(fCrd x,  fCrd y,  clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawLine(6, 4, 6, 6);                                                  // drawLine(iCrd x1, iCrd y1, iCrd x2, iCrd y2);
  theRamCanvas.setDfltColor(aColor);
  theRamCanvas.drawLine(7.0, 5.0, 7.0, 7.0);                                          // drawLine(fCrd x1, fCrd y1, fCrd x2, fCrd y2);
  theRamCanvas.drawLine(8.0, 5.0, 8.0, 7.0, bColor);                                  // drawLine(fCrd x1, fCrd y1, fCrd x2, fCrd y2, clr color);
  theRamCanvas.setDfltColor(aColor);
  theRamCanvas.moveTo(mjr::ramCanvasRGB8b::rcPointFlt({9.0, 5.0}));
  theRamCanvas.drawLine(mjr::ramCanvasRGB8b::rcPointFlt({9.0, 7.0}));                      // drawLine(fPnt point1);
  theRamCanvas.moveTo(10.0, 5.0);
  theRamCanvas.drawLine(mjr::ramCanvasRGB8b::rcPointFlt({10.0, 7.0}), bColor);             // drawLine(fPnt point1, clr color);
  theRamCanvas.setDfltColor(aColor);
  theRamCanvas.moveTo(11, 4);
  theRamCanvas.drawLine(mjr::ramCanvasRGB8b::rcPointInt({11, 6}));                         // drawLine(iPnt point1);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.moveTo(mjr::ramCanvasRGB8b::rcPointInt({12, 4}));
  theRamCanvas.drawLine(mjr::ramCanvasRGB8b::rcPointInt({12, 6}), aColor);                 // drawLine(iPnt point1, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawLine(mjr::ramCanvasRGB8b::rcPointFlt({13, 5.0}),
                        mjr::ramCanvasRGB8b::rcPointFlt({13, 7.0}));                       // drawLine(fPnt point1, fPnt point2);
  theRamCanvas.drawLine(mjr::ramCanvasRGB8b::rcPointFlt({14, 5.0}),
                        mjr::ramCanvasRGB8b::rcPointFlt({14, 7.0}), aColor);               // drawLine(fPnt point1, fPnt point2, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawLine(mjr::ramCanvasRGB8b::rcPointInt({15, 4}),
                        mjr::ramCanvasRGB8b::rcPointInt({15, 6}));                         // drawLine(iPnt point1, iPnt point2);
  theRamCanvas.drawLine(mjr::ramCanvasRGB8b::rcPointInt({16, 5}),
                        mjr::ramCanvasRGB8b::rcPointInt({16, 6}), aColor);                 // drawLine(iPnt point1, iPnt point2, clr color);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  theRamCanvas.drawTriangle(1, 9, 4, 9, 4, 12,  aColor);                              // drawTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3,
                                                                                      //              clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawTriangle(6, 9, 9, 9, 9, 12);                                       // drawTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3);
  theRamCanvas.drawTriangle(11.0, 10.0, 14.0, 10.0, 14.0, 13.0,  aColor);             // drawTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3,
                                                                                      //              clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawTriangle(16.0, 10.0, 19.0, 10.0, 19.0, 13.0);                      // drawTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3);
  theRamCanvas.drawTriangle(mjr::ramCanvasRGB8b::rcPointInt({1, 14}),
                            mjr::ramCanvasRGB8b::rcPointInt({4, 14}),
                            mjr::ramCanvasRGB8b::rcPointInt({4, 17}),  aColor);            // drawTriangle(iPnt point1, iPnt point2, iPnt point3, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawTriangle(mjr::ramCanvasRGB8b::rcPointInt({6, 14}),
                            mjr::ramCanvasRGB8b::rcPointInt({9, 14}),
                            mjr::ramCanvasRGB8b::rcPointInt({9, 17}));                     // drawTriangle(iPnt point1, iPnt point2, iPnt point3);
  theRamCanvas.drawTriangle(mjr::ramCanvasRGB8b::rcPointFlt({11.0, 15.0}),
                            mjr::ramCanvasRGB8b::rcPointFlt({14.0, 15.0}),
                            mjr::ramCanvasRGB8b::rcPointFlt({14.0, 18.0}),  aColor);       // drawTriangle(fPnt point1, fPnt point2, fPnt point3, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawTriangle(mjr::ramCanvasRGB8b::rcPointFlt({16.0, 15.0}),
                            mjr::ramCanvasRGB8b::rcPointFlt({19.0, 15.0}),
                            mjr::ramCanvasRGB8b::rcPointFlt({19.0, 18.0}));                // drawTriangle(fPnt point1, fPnt point2, fPnt point3);
  mjr::ramCanvasRGB8b::rcPointInt ptl1[3] = { {1, 19}, {4, 19}, {4, 22} };
  theRamCanvas.drawTriangle(ptl1, aColor);                                            // drawTriangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::rcPointInt ptl2[3] = { {6, 19}, {9, 19}, {9, 22} };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawTriangle(ptl2);                                                    // drawTriangle(iPnt *thePoints);
  mjr::ramCanvasRGB8b::rcPointFlt ptl3[3] = { {11.0, 20.0},
                                         {14.0, 20.0},
                                         {14.0, 23.0} };
  theRamCanvas.drawTriangle(ptl3, aColor);                                            // drawTriangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::rcPointFlt ptl4[3] = { {16.0, 20.0},
                                         {19.0, 20.0},
                                         {19.0, 23.0} };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawTriangle(ptl4);                                                    // drawTriangle(fPnt *thePoints);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  theRamCanvas.drawFillTriangle(21, 9, 24, 9, 24, 12,  aColor);                       // drawFillTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3,
                                                                                      //                  clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillTriangle(26, 9, 29, 9, 29, 12);                                // drawFillTriangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, iCrd x3, iCrd y3);
  theRamCanvas.drawFillTriangle(31.0, 10.0, 34.0, 10.0, 34.0, 13.0,  aColor);         // drawFillTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3
                                                                                      //                  clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillTriangle(36.0, 10.0, 39.0, 10.0, 39.0, 13.0);                  // drawFillTriangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, fCrd x3, fCrd y3);
  theRamCanvas.drawFillTriangle(mjr::ramCanvasRGB8b::rcPointInt({21, 14}),
                                mjr::ramCanvasRGB8b::rcPointInt({24, 14}),
                                mjr::ramCanvasRGB8b::rcPointInt({24, 17}),  aColor);       // drawFillTriangle(iPnt point1, iPnt point2, iPnt point3, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillTriangle(mjr::ramCanvasRGB8b::rcPointInt({26, 14}),
                                mjr::ramCanvasRGB8b::rcPointInt({29, 14}),
                                mjr::ramCanvasRGB8b::rcPointInt({29, 17}));                // drawFillTriangle(iPnt point1, iPnt point2, iPnt point3);
  theRamCanvas.drawFillTriangle(mjr::ramCanvasRGB8b::rcPointFlt({31.0, 15.0}),
                                mjr::ramCanvasRGB8b::rcPointFlt({34.0, 15.0}),
                                mjr::ramCanvasRGB8b::rcPointFlt({34.0, 18.0}),  aColor);   // drawFillTriangle(fPnt point1, fPnt point2, fPnt point3, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillTriangle(mjr::ramCanvasRGB8b::rcPointFlt({36.0, 15.0}),
                                mjr::ramCanvasRGB8b::rcPointFlt({39.0, 15.0}),
                                mjr::ramCanvasRGB8b::rcPointFlt({39.0, 18.0}));            // drawFillTriangle(fPnt point1, fPnt point2, fPnt point3);
  mjr::ramCanvasRGB8b::rcPointInt ptl5[3] = { {21, 19}, {24, 19}, {24, 22} };
  theRamCanvas.drawFillTriangle(ptl5, aColor);                                        // drawFillTriangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::rcPointInt ptl6[3] = { {26, 19}, {29, 19}, {29, 22} };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillTriangle(ptl6);                                                // drawFillTriangle(iPnt *thePoints);
  mjr::ramCanvasRGB8b::rcPointFlt ptl7[3] = { {31.0, 20.0},
                                         {34.0, 20.0},
                                         {34.0, 23.0} };
  theRamCanvas.drawFillTriangle(ptl7, aColor);                                        // drawFillTriangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::rcPointFlt ptl8[3] = { {36.0, 20.0},
                                         {39.0, 20.0},
                                         {39.0, 23.0} };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillTriangle(ptl8);                                                // drawFillTriangle(fPnt *thePoints);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  theRamCanvas.drawCircle(3, 27, 2, aColor);                                          // drawCircle(iCrd centerX, iCrd centerY, iCrd radiusX, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawCircle(9, 27, 2);                                                  // drawCircle(iCrd centerX, iCrd centerY, iCrd radius);
  theRamCanvas.moveTo(15, 27);
  theRamCanvas.setDfltColor(aColor);
  theRamCanvas.drawCircle(2);                                                         // drawCircle(iCrd radius);
  theRamCanvas.drawCircle(21.0, 28.0, 2.0, bColor);                                   // drawCircle(fCrd centerX, fCrd centerY, fCrd radiusX, clr color);
  theRamCanvas.setDfltColor(aColor);
  theRamCanvas.drawCircle(27.0, 28.0, 2.0);                                           // drawCircle(fCrd centerX, fCrd centerY, fCrd radiusX);
  theRamCanvas.moveTo(33.0, 28.0);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawCircle(2.0);                                                       // drawCircle(fCrd radiusX);
  theRamCanvas.drawCircle(mjr::ramCanvasRGB8b::rcPointInt({39, 27}), 2, aColor);           // drawCircle(iPnt centerPoint, iCrd radiusX, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawCircle(mjr::ramCanvasRGB8b::rcPointInt({45, 27}), 2);                   // drawCircle(iPnt centerPoint, iCrd radiusX);
  theRamCanvas.drawCircle(mjr::ramCanvasRGB8b::rcPointFlt({51.0, 28.0}), 2.0, aColor);     // drawCircle(fPnt centerPoint, fCrd radiusX, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawCircle(mjr::ramCanvasRGB8b::rcPointFlt({57.0, 28.0}), 2.0);             // drawCircle(fPnt centerPoint, fCrd radiusX);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  theRamCanvas.drawFillCircle(3, 33, 2, aColor);                                      // drawFillCircle(iCrd centerX, iCrd centerY, iCrd radiusX, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillCircle(9, 33, 2);                                              // drawFillCircle(iCrd centerX, iCrd centerY, iCrd radiusX);
  theRamCanvas.moveTo(15, 33);
  theRamCanvas.setDfltColor(aColor);
  theRamCanvas.drawFillCircle(2);                                                     // drawFillCircle(iCrd radiusX);
  theRamCanvas.drawFillCircle(21.0, 34.0, 2.0, bColor);                               // drawFillCircle(fCrd centerX, fCrd centerY, fCrd radiusX, clr color);
  theRamCanvas.setDfltColor(aColor);
  theRamCanvas.drawFillCircle(27.0, 34.0, 2.0);                                       // drawFillCircle(fCrd centerX, fCrd centerY, fCrd radiusX);
  theRamCanvas.moveTo(33.0, 34.0);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillCircle(2.0);                                                   // drawFillCircle(fCrd radiusX);
  theRamCanvas.drawFillCircle(mjr::ramCanvasRGB8b::rcPointInt({39, 33}), 2, aColor);       // drawFillCircle(iPnt centerPoint, iCrd radiusX, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillCircle(mjr::ramCanvasRGB8b::rcPointInt({45, 33}), 2);               // drawFillCircle(iPnt centerPoint, iCrd radiusX);
  theRamCanvas.drawFillCircle(mjr::ramCanvasRGB8b::rcPointFlt({51.0, 34.0}), 2.0, aColor); // drawFillCircle(fPnt centerPoint, fCrd radiusX, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillCircle(mjr::ramCanvasRGB8b::rcPointFlt({57.0, 34.0}), 2.0);         // drawFillCircle(fPnt centerPoint, fCrd radiusX);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  theRamCanvas.drawRectangle(2, 38, 4, 40, aColor);                                   // drawRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawRectangle(6, 38, 8, 40);                                           // drawRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2);
  theRamCanvas.drawRectangle(10.0, 39.0, 12.0, 41.0, aColor);                         // drawRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawRectangle(14.0, 39.0, 16.0, 41.0);                                 // drawRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2);
  theRamCanvas.drawRectangle(mjr::ramCanvasRGB8b::rcPointInt({18, 38}),
                             mjr::ramCanvasRGB8b::rcPointInt({20, 40}), aColor);           // drawRectangle(iPnt point1, iPnt point2, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawRectangle(mjr::ramCanvasRGB8b::rcPointInt({22, 38}),
                             mjr::ramCanvasRGB8b::rcPointInt({24, 40}));                   // drawRectangle(iPnt point1, iPnt point2);
  theRamCanvas.drawRectangle(mjr::ramCanvasRGB8b::rcPointFlt({26.0, 39.0}),
                             mjr::ramCanvasRGB8b::rcPointFlt({28.0, 41.0}), aColor);       // drawRectangle(fPnt point1, fPnt point2, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawRectangle(mjr::ramCanvasRGB8b::rcPointFlt({30.0, 39.0}),
                             mjr::ramCanvasRGB8b::rcPointFlt({32.0, 41.0}));               // drawRectangle(fPnt point1, fPnt point2);
  mjr::ramCanvasRGB8b::rcPointInt ptl9[2] = { {34, 38}, {36, 40} };
  theRamCanvas.drawRectangle(ptl9, aColor);                                           // drawRectangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::rcPointInt ptl10[2] = { {38, 38}, {40, 40} };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawRectangle(ptl10);                                                  // drawRectangle(iPnt *thePoints);
  mjr::ramCanvasRGB8b::rcPointFlt ptl11[2] = { {42.0, 39.0}, {44.0, 41.0} };
  theRamCanvas.drawRectangle(ptl11, aColor);                                          // drawRectangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::rcPointFlt ptl12[2] = { {46.0, 39.0}, {48.0, 41.0} };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawRectangle(ptl12);                                                  // drawRectangle(fPnt *thePoints);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  theRamCanvas.drawFillRectangle(2, 42, 4, 44, aColor);                               // drawFillRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillRectangle(6, 42, 8, 44);                                       // drawFillRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2);
  theRamCanvas.drawFillRectangle(10.0, 43.0, 12.0, 45.0, aColor);                     // drawFillRectangle(fCrd x1, fCrd y1, fCrd x2, fCrd y2, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillRectangle(14.0, 43.0, 16.0, 45.0);                             // drawFillRectangle(iCrd x1, iCrd y1, iCrd x2, iCrd y2);
  theRamCanvas.drawFillRectangle(mjr::ramCanvasRGB8b::rcPointInt({18, 42}),
                                 mjr::ramCanvasRGB8b::rcPointInt({20, 44}), aColor);       // drawFillRectangle(iPnt point1, iPnt point2, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillRectangle(mjr::ramCanvasRGB8b::rcPointInt({22, 42}),
                                 mjr::ramCanvasRGB8b::rcPointInt({24, 44}));               // drawFillRectangle(iPnt point1, iPnt point2);
  theRamCanvas.drawFillRectangle(mjr::ramCanvasRGB8b::rcPointFlt({26.0, 43.0}),
                                 mjr::ramCanvasRGB8b::rcPointFlt({28.0, 45.0}), aColor);   // drawFillRectangle(fPnt point1, fPnt point2, clr color);
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillRectangle(mjr::ramCanvasRGB8b::rcPointFlt({30.0, 43.0}),
                                 mjr::ramCanvasRGB8b::rcPointFlt({32.0, 45.0}));           // drawFillRectangle(fPnt point1, fPnt point2);
  mjr::ramCanvasRGB8b::rcPointInt ptl13[2] = { {34, 42}, {36, 44} };
  theRamCanvas.drawFillRectangle(ptl13, aColor);                                      // drawFillRectangle(iPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::rcPointInt ptl14[2] = { {38, 42}, {40, 44} };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillRectangle(ptl14);                                              // drawFillRectangle(iPnt *thePoints);
  mjr::ramCanvasRGB8b::rcPointFlt ptl15[2] = { {42.0, 43.0}, {44.0, 45.0} };
  theRamCanvas.drawFillRectangle(ptl15, aColor);                                      // drawFillRectangle(fPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::rcPointFlt ptl16[2] = { {46.0, 43.0}, {48.0, 45.0} };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawFillRectangle(ptl16);                                              // drawFillRectangle(fPnt *thePoints);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  mjr::ramCanvasRGB8b::rcCordInt icx1[3] = {  2,  4,  4 };
  mjr::ramCanvasRGB8b::rcCordInt icy1[3] = { 46, 46, 48 };
  theRamCanvas.drawPLCurve(3, icx1, icy1, aColor);                                    // drawPLCurve(int numPoints, iCrd *x, iCrd *y, clr color);
  mjr::ramCanvasRGB8b::rcCordInt icx2[3] = {  6,  8,  8 };
  mjr::ramCanvasRGB8b::rcCordInt icy2[3] = { 46, 46, 48 };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawPLCurve(3, icx2, icy2);                                            // drawPLCurve(int numPoints, iCrd *x, iCrd *y);
  mjr::ramCanvasRGB8b::rcCordFlt fcx1[3] = { 10.0, 12.0, 12.0 };
  mjr::ramCanvasRGB8b::rcCordFlt fcy1[3] = { 47.0, 47.0, 49.0 };
  theRamCanvas.drawPLCurve(3, fcx1, fcy1, aColor);                                    // drawPLCurve(int numPoints, fCrd *x, fCrd *y, clr color);
  mjr::ramCanvasRGB8b::rcCordFlt fcx2[3] = { 14.0, 16.0, 16.0 };
  mjr::ramCanvasRGB8b::rcCordFlt fcy2[3] = { 47.0, 47.0, 49.0 };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawPLCurve(3, fcx2, fcy2);                                            // drawPLCurve(int numPoints, fCrd *x, fCrd *y);
  mjr::ramCanvasRGB8b::rcPointInt ptl17[3] = { {18, 46},
                                          {20, 46},
                                          {20, 48} };
  theRamCanvas.drawPLCurve(3, ptl17, aColor);                                         // drawPLCurve(int numPoints, iPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::rcPointInt ptl18[3] = { {22, 46},
                                          {24, 46},
                                          {24, 48} };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawPLCurve(3, ptl18);                                                 // drawPLCurve(int numPoints, iPnt *thePoints);
  mjr::ramCanvasRGB8b::rcPointFlt ptl19[3] = { {26.0, 47.0},
                                          {28.0, 47.0},
                                          {28.0, 49.0} };
  theRamCanvas.drawPLCurve(3, ptl19, aColor);                                         // drawPLCurve(int numPoints, fPnt *thePoints, clr color);
  mjr::ramCanvasRGB8b::rcPointFlt ptl20[3] = { {30.0, 47.0},
                                          {32.0, 47.0},
                                          {32.0, 49.0} };
  theRamCanvas.setDfltColor(bColor);
  theRamCanvas.drawPLCurve(3, ptl20);                                                 // drawPLCurve(int numPoints, fPnt *thePoints);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  theRamCanvas.scaleUpProximal(5);
  theRamCanvas.writeTIFFfile("test_draw_primatives.tiff");
}
