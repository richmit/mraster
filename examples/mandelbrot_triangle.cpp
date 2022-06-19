// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      mandelbrot_triangle.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Mandelbrot set using an edge detection algorithm.@EOL
 @std       C++98
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

  The ramCanvas library has a very rich (some would say bloated) collection of functions that do essentially the same thing just in slightly different ways.
  The reason for this is so that the library can support legacy code directly, and generally bend itself to different programming styles and needs.

  One example of this are the "point objects" and associated methods.  Of the nice things about the point objects defined in the ramCanvas object is that they
  are binary compatible with the most common point and complex formats used -- including the complex that are contained in the C and C++ standards and the
  complex used in Fortran.  As a good example, the findAlphaTriangle, traceBoundry, and inSet functions existed long before the ramCanvas library, yet one is
  able to directly make use of the preexisting data types.

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

typedef struct { double x; double y; } complex;

int MAXCOUNT;

const int MAXTRCNT = 250000;
complex thePath[MAXTRCNT];

int inSet(complex tstPt);
int findAlphaTriangle(int maxCnt, int ptA, int ptB, double slop, complex triangle[3]);
int traceBoundry(int maxCnt, double epsilon, int goOtherWay, complex alphaTriangle[3], complex thePath[], int *pathLen);
int orbCmp(complex tstPt);

/* **************************************************************** */
int main(void) {
  auto startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  // Pick a triangle type and size..
//  complex protoAlphaTriangle[3] = { {0.0, 0.0}, {0.50, 0.0}, {0.500, 0.50} };    // Big       right triangles
//  complex protoAlphaTriangle[3] = { {0.0, 0.0}, {0.10, 0.0}, {0.100, 0.10} };    // Small     right triangles
//  complex protoAlphaTriangle[3] = { {0.0, 0.0}, {0.01, 0.0}, {0.010, 0.01} };    // Tiny      right triangles
//  complex protoAlphaTriangle[3] = { {0.0, 0.0}, {0.50, 0.0}, {0.240, 0.50} };    // Big       non-right triangles
//  complex protoAlphaTriangle[3] = { {0.0, 0.0}, {0.10, 0.0}, {0.050, 0.10} };    // Small     non-right triangles
//  complex protoAlphaTriangle[3] = { {0.0, 0.0}, {0.01, 0.0}, {0.001, 0.01} };    // Tiny      non-right triangles
  complex protoAlphaTriangle[3] = { {0.0, 0.0}, {0.001, 0.0}, {0.0001, 0.001} }; // Tiny-Tiny non-right triangles

  mjr::ramCanvas3c8b theRamCanvas(7680/4, 7680/4, -2.1, 1.1, -1.5, 1.5);

  // First we draw a greyscale Mandelbrot set for reference.
  if(true) {
    mjr::color3c8b aColor;
    aColor.setToWhite();
    MAXCOUNT = 255;
    std::cout << "INFO(main): Draw reference set via fill algorithm." << std::endl;
    for(int yy=0;yy<theRamCanvas.get_numYpix();yy++) {
      for(int xx=0;xx<theRamCanvas.get_numXpix();xx++) {
        complex tpt;
        tpt.x = theRamCanvas.int2realX(xx);
        tpt.y = theRamCanvas.int2realY(yy);
        int clr = orbCmp(tpt);
        theRamCanvas.drawPoint(xx, yy, aColor.cmpGrey3x((100*clr)%768));
      }
    }
  }

  // Now we trace several set boundaries
  for(MAXCOUNT = 1;  MAXCOUNT < 10;  MAXCOUNT++) {
    std::cout <<  "INFO(main): Curve: " << MAXCOUNT << std::endl;
    // Find alpha
    complex alphaTriangle[3];
    for(int i=0; i<3; i++)
      alphaTriangle[i] = protoAlphaTriangle[i];
    if(findAlphaTriangle(MAXTRCNT, 0, 1, 0.0, alphaTriangle)) {
      int thePathLen;
      traceBoundry(MAXTRCNT, 0.00003, 0, alphaTriangle, thePath, &thePathLen);
      theRamCanvas.drawPLCurve(thePathLen+1, (mjr::ramCanvas3c8b::pointFltType *)thePath, mjr::color3c8b(255, 0, 255));
    }
  }

  theRamCanvas.writeTIFFfile("mandelbrot_triangle.tiff");
  std::cout << "Runtime " << static_cast<double>(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) - startTime)/(60.0) << " min" << std::endl;
}

/* **************************************************************** */
int orbCmp(complex tstPt) {
  mjr::ramCanvas3c8b::coordFltType zx = 0.0;
  mjr::ramCanvas3c8b::coordFltType zy = 0.0;
  int count = 0;
  mjr::ramCanvas3c8b::coordFltType  tempx;
  while(1) {
    if(zx * zx + zy * zy >= 4)
      return count;
    if(count > MAXCOUNT)
      return 0;
    tempx = zx * zx - zy * zy + tstPt.x;
    zy = 2 * zx * zy + tstPt.y;
    zx = tempx;
    count++;
  }
}

/* **************************************************************** */
int inSet(complex tstPt) {
  if(orbCmp(tstPt)) // Transform "count" => 1 or zero for inSet return
    return 1;
  else
    return 0;
}

/* **************************************************************** */
/* Return 1 if found, return 0 other wise. */
int findAlphaTriangle(int maxCnt, int ptA, int ptB, double slop, complex triangle[3]) {
  int printDebug=2;
  int hitCount;
  int count = 0;
  mjr::ramCanvas3c8b::coordFltType xDelta = triangle[ptB].x - triangle[ptA].x;
  mjr::ramCanvas3c8b::coordFltType yDelta = triangle[ptB].y - triangle[ptA].y;

  // Shrink the delta some....
  xDelta = (xDelta - xDelta * slop);
  yDelta = (yDelta - yDelta * slop);

  while(1) {
    /* Check the current triangle -- note we recheck many points, but we will fix this later... */
    hitCount = inSet(triangle[0])+inSet(triangle[1])+inSet(triangle[2]);
    if( (hitCount >= 1) && (hitCount <= 2) ) {
      if(printDebug>1)
        std::cerr <<  "INFO(findAlphaTriangle): Found alpha triangle!" << std::endl;
      return 1;
    } else {
      /* Slide the current triangle over a bit... */
      for(int i=0; i<3; i++) {
        triangle[i].x = triangle[i].x + xDelta;
        triangle[i].y = triangle[i].y + yDelta;
      }
    }
    count++;
    if(count > maxCnt) {
      if(printDebug)
        std::cerr <<  "ERROR(findAlphaTriangle): Too many iterations!" << std::endl;
      return 0;
    }
  }
}

/*  This function finds an approximation to the boundary of a region in the plane.  The region is defined by an boolean-like valued function that accepting a
    point in the plane --- i.e. it returns 1 if the point is in the set, and 0 otherwise.  The approximation to the boundary is based upon a triangulation of
    the plane -- the triangulation is induced by the alphaTriangle argument.  The return is a list of line segments, each traversing individual triangles in
    the given triangulation -- each segment has endpoints at the midpoints of triangle edges.  The alphaTriangle must have at least on vertex in the set and
    one outside of the set.  The function then finds a neighboring triangle in the triangulation that has the same characteristic -- i.e. one point in and one
    point out.  The function then repeats the process.  The function ends when maxCnt triangles have been found or until the path gets within epsilon of its
    starting point.

    @param maxCnt The maximum number of iterations before the function will exit.
    @param epsilon If the boundary traced comes within epsilon of the original point, the function will return.
    @param goOtherWay If the alphaTriangle has two points in the region and this argument is non-zero, then the boundary trace will proceed in the opposite
           direction it normally would. Useful for tracing boundaries that are not simple closed curves.
    @param alphaTriangle The first triangle.  It must have at least one vertex in the region and one vertex not in the region.
    @param thePath array holding the path upon exit.  This must have at least maxCnt elements.
    @param pathLen contains max index of a point in thePath upon exit -- not the number of elements.  It will be -1 if no points are in the array.
    @return 0 The triangle was entire in or out of the region.
    @return 1 Boundary came back upon self
    @return 2 Max iteration count reached
    @return 3 goOtherWay==1, and was of no use */
int traceBoundry(int maxCnt, double epsilon, int goOtherWay, complex alphaTriangle[3], complex thePath[], int *pathLen) {
  complex curTriangle[3];
  int printDebug=2;
  int pInState[3], pInStateSum;
  int insIdx, unkIdx, outIdx, tmpIdx;

  /* Initialize the first triangle, and get in/out of set info. */
  for(int i=0; i<3; i++) {
    curTriangle[i] = alphaTriangle[i];
    pInState[i]    = inSet(curTriangle[i]);
  } /* end for */

  // Make sure we have an appropriate number of "inSet" vertexes
  *pathLen = -1;  // Set now in case of return
  pInStateSum = 0;
  for(int i=0; i<3; i++)
    pInStateSum += pInState[i];
  if(pInStateSum >= 3) {
    if(printDebug)
      std::cerr <<  "ERROR(traceBoundry): All vertexes of alpha triangle in set!" << std::endl;
    return 0;
  } /* end if */
  if(pInStateSum <= 0) {
    if(printDebug)
      std::cerr <<  "ERROR(traceBoundry): No vertexes of alpha triangle in set!" << std::endl;
    return 0;
  } /* end if */

  // Set insIdx, unkIdx, and outIdx for the first triangle
  insIdx = unkIdx = outIdx = -1;
  for(int i=0; i<3; i++) {
    if(pInState[i]) {
      if(insIdx == -1) {
        insIdx = i;
      } else {
        if(goOtherWay) {
          unkIdx = insIdx;
          insIdx = i;
        } else {
          unkIdx = i;
        } /* end if/else */
      } /* end if/else */
    } else {
      if(outIdx == -1) {
        outIdx = i;
      } else {
        if(goOtherWay) {
          if(printDebug>1)
            std::cerr <<  "WARNING(traceBoundry): goOtherWay is ineffective in this case!" << std::endl;
          return 3;
        } /* end if */
        unkIdx = i;
      } /* end if/else */
    } /* end if/else */
  } /* end for */

  // Put the first point into the path array and increment pathLen.
  *pathLen = 0;
  thePath[*pathLen].x = (curTriangle[insIdx].x + curTriangle[outIdx].x)/2;
  thePath[*pathLen].y = (curTriangle[insIdx].y + curTriangle[outIdx].y)/2;

  // Main iteration loop
  for(int count=0;(count<(maxCnt-1))||(maxCnt==0);count++) {
    //Update the coordinates for our next triangle
    curTriangle[unkIdx].x = curTriangle[insIdx].x + curTriangle[outIdx].x - curTriangle[unkIdx].x;
    curTriangle[unkIdx].y = curTriangle[insIdx].y + curTriangle[outIdx].y - curTriangle[unkIdx].y;

    // Fix insIdx, outIdx, and unkIdx for the new triangle..
    if(inSet(curTriangle[unkIdx])) {
      tmpIdx = insIdx;
      insIdx = unkIdx;
      unkIdx = tmpIdx;
    } else {
      tmpIdx = outIdx;
      outIdx = unkIdx;
      unkIdx = tmpIdx;
    }  /* end if/else */

    // Update the path array
    (*pathLen)++;
    thePath[*pathLen].x = (curTriangle[insIdx].x + curTriangle[outIdx].x)/2;
    thePath[*pathLen].y = (curTriangle[insIdx].y + curTriangle[outIdx].y)/2;

    // Figure out if we have come back upon the alpha triangle.
    if( (fabs(thePath[*pathLen].x - thePath[0].x) + fabs(thePath[*pathLen].y - thePath[0].y)) < epsilon) {
      if(printDebug>1)
        std::cerr <<  "INFO(traceBoundry): Came back upon self (itr: " << count << ").  Done." << std::endl;
      return 1;
    }

  } /* end for */
  if(printDebug>1)
    std::cerr <<  "INFO(traceBoundry): Max iteration count reached.  Done." << std::endl;
  return 2;
} /* end func traceBoundry */
