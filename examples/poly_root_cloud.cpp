// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      poly_root_cloud.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @brief     Draw the roots of paramaterized polynomials. @EOL
 @keywords  polynomial root
 @std       C++23
 @see       https://github.com/richmit/mraster/
 @copyright 
  @parblock
  Copyright (c) 2025, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.
  
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

  Plot roots of the polynomial p.  Two of the coefficients of p (c1 & c2) are parameterized by polynomials (p2 & p2) over the unit circle.  

  In pseudo-code:
    Loop
      Select sample points on the unit circle for t1 & t2
      Plug t1 & t2 into p1 & p2
      Set coefficients c1 & c2 in p to the value of p1 & p2
      Find the roots of p and plot them
    Repeat

  I made a prototype for this problem in Matlab.  In the Matlab code I placed semitransparent filled circles at each root, and allowed color to build up with
  repeated layers of roots.  This results in a "fuzzy" look spreading color more smoothly over the envelope of the root cloud. That code may be found here:
  https://github.com/richmit/PolyRootCloud/

  In this code I wanted to emphasize more directly the way the circles in the parametrization map to the root cloud space.  So I'm actually creating a
  histogram of root hits in the plane with a very fine grid, and using many more sample points on one parameter.  This produces a Spirograph'esq effect.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathUPLY.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// Overide the complex types in lapacke.h.
#define LAPACK_COMPLEX_CUSTOM         1
#define lapack_complex_float          std::complex<float>
#define lapack_complex_double         std::complex<double>

#include <lapacke.h>                                                     /* LAPACK C Interface      LAPACKE  */

typedef lapack_complex_double cplx;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef mjr::ramCanvas1c16b drc_t;
typedef mjr::color3c8b oc_t;
typedef mjr::ramCanvasPixelFilter::FuncHomoTransform<drc_t, oc_t> hpf_t;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();

  const int n1   = 1000;
  const int n2   = 100;
  const int c1   = 8;
  const int c2   = 12;
  const int XSIZ = 2048*8;  
  const int YSIZ = 2048*8;
  drc_t theRamCanvas(XSIZ, YSIZ, -2.5, 2.5, -2.5, 2.5);

# pragma omp parallel for schedule(static,1)
  for(int m1=0; m1<n1; m1++) {
    std::vector<cplx> p      = {{1.0,    0.0}, {-1.0,    0.0}, {0.0,    0.0}, { 0.0,   0.0}, {  0.0,    0.0}, {   0.0, 0.0}, {0.0,   0.0}, 
                                {0.0,    0.0}, { 0.0,    0.0}, {0.0,    0.0}, { 0.0,   0.0}, {  0.0,    0.0}, {   0.0, 0.0}, {0.0,   0.0}, 
                                {0.0,    0.0}, { 0.0,    0.0}, {0.0,    0.0}, {-0.1,   0.0}, {  0.1,    0.0}};
    std::vector<cplx> p1     = {{0.0,    0.0}, { 0.0,  100.0}, {0.0, -100.0}, { 0.0, 100.0}, {  0.0, -100.0}, {-100.0, 0.0}, {0.0, 100.0}};
    std::vector<cplx> p2     = {{0.0, -100.0}, { 0.0, -100.0}, {0.0,  100.0}, { 0.0, 100.0}, {100.0,    0.0}};
    int               pdg    = (int)p.size() - 1;
    lapack_int        n      = (lapack_int)p.size() - 1; // Companion matrix dimensions are the polynomial degree
    lapack_int        lwork  = -1;                       // Set to -1 for work size query
    cplx              *work;                             // Allocated later after query
    cplx              *a     = new cplx[n*n];
    cplx              *w     = new cplx[n];
    double            *rwork = new double[n*2];
    cplx              tmp;
    // Query the optimal value for lwork & allocate it
    if( 0 != LAPACKE_zgeev_work(LAPACK_COL_MAJOR, 'N', 'N', n, a, n, w, NULL, n, NULL, n, &tmp, lwork, rwork)) {
      std::cout << "ZGEEV Error (lwork query)" << std::endl;
      exit(1);
    }
    lwork = LAPACK_Z2INT(tmp) + 1;
    work  = new cplx[lwork];
    // Update p
    cplx t1 = std::exp(cplx(0.0, 1.0) * static_cast<double>(m1) * 2.0 * std::numbers::pi / static_cast<double>(n1));
    p[c1] = mjr::math::uply::eval(p1, t1);
    for(int m2=0; m2<n2; m2++) {
      // Update p
      cplx t2 = std::exp(cplx(0.0, 1.0) * static_cast<double>(m2) * 2.0 * std::numbers::pi / static_cast<double>(n2));
      p[c2] = mjr::math::uply::eval(p2, t2);
      // Compute the companion matrix and store it in a
      for(int i=0;i<n*n;i++)
        a[i] = cplx(0.0, 0.0);
      for(int i=1;i<n;i++)
        a[i*n+(i-1)] = cplx(1.0, 0.0);
      for(int i=1;i<=n;i++)
        a[(n-i)*n+(n-1)] = - p[i] / p[0];
      // Now find the eigenvalues.
      if( 0 != LAPACKE_zgeev_work(LAPACK_COL_MAJOR, 'N', 'N', n, a, n, w, NULL, n, NULL, n, work, lwork, rwork)) {
        std::cout << "ZGEEV Error (eigenvalue)" << std::endl;
        exit(1);
      }
      // Plot all the roots
#     pragma omp critical
      for(int j=0; j<pdg; j++) 
        if (theRamCanvas.getPxColor(w[j]).getC0() < 1275)
          theRamCanvas.incPxChan(w[j]);
    }
    // Update on progress
#   pragma omp critical
    std::cout << "Completed Cycle " << m1 << " of " << n1 << std::endl;
    // Free the memory for new'ed arrays.
    delete[] a;
    delete[] w;    
    delete[] work; 
    delete[] rwork;
  }

  // Transform for better colors
  theRamCanvas.applyHomoPixTfrm(&drc_t::colorType::tfrmStdPow, 0.5);
  theRamCanvas.scaleDownMax(8);

  // Write with color map
  theRamCanvas.writeTIFFfile("poly_root_cloud.tiff", hpf_t(theRamCanvas,[](auto inColor) { return oc_t::csCCfractal0RYBCW::c(inColor.getC0()); }));

  // Wrap things up
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */
