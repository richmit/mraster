// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      sic.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw fractals inspired by the book Symmetry in Chaos.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/sic/index.html
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

  Fractals inspired by the book "Symmetry in Chaos" by Michael Field and Martin Golubitsky.

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathSTR.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b rct;
typedef rct::colorType ct;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<std::array<mjr::ramCanvas1c16b::coordFltType, 12>> params {
  /*  lambda       alpha      beta     gamma      omega   n    ipw   xmin  xmax   ymin  ymax    1=mean */
  { 1.375390, -0.4212800,  0.26969,  0.08352,  0.338347,  6, 15.00, -1.30, 1.30, -1.30, 1.30, 1.0}, // 0  |
  { 1.600230, -1.1340800, -0.17506,  0.67872,  0.049490,  6, 14.00,  0.10, 0.70,  0.43, 0.90, 0.0}, // 1  |  WACKY
  { 1.000890, -0.7678100,  1.89425, -1.13943, -0.688827,  7, 10.00, -0.90, 0.90, -0.90, 0.90, 0.0}, // 2  |
  {-1.563400,  1.7238200,  0.74440,  0.71874,  0.258907,  3,  8.00, -0.75, 0.75, -0.75, 0.75, 1.0}, // 3  |
  { 1.361000, -1.8225400, -0.92635, -1.74108, -0.761120,  5,  2.00, -0.70, 0.70, -0.70, 0.70, 1.0}, // 4  |
  { 1.609310, -1.6924900,  0.85055,  0.26523, -0.716769,  5,  4.00, -0.90, 0.90, -0.90, 0.90, 0.0}, // 5  |
  { 1.464900, -1.8825700, -1.47205, -0.83559, -0.701477,  4,  3.00, -0.80, 0.80, -0.80, 0.80, 1.0}, // 6  |
  { 1.622110, -1.0694500, -0.11181,  0.62253,  0.784032,  4,  2.00, -1.20, 1.20, -1.20, 1.20, 1.0}, // 7  |
  {-1.380150,  0.7472100,  1.17094,  0.05782, -0.574188,  6, 10.00, -1.00, 1.00, -1.00, 1.00, 0.0}, // 8  |
  { 0.335010, -1.3467500, -0.65137, -0.87848, -1.231490,  5, 10.00, -1.20, 1.20, -1.20, 1.20, 1.0}, // 9  |
  {-1.496290,  1.8701600, -1.93938, -0.88084, -0.139602,  3, 10.00, -0.55, 0.55, -0.55, 0.55, 1.0}, // 10 |
  {-1.248610,  1.0816100, -0.50731,  0.97272, -0.853955, 11, 10.00, -1.00, 1.00, -1.00, 1.00, 0.0}, // 11 |
  {-1.991900,  1.8219100, -0.38273,  0.68143,  0.493416, 11, 10.00, -1.00, 1.00, -1.00, 1.00, 0.0}, // 12 |
  { 1.694170, -1.2730200,  0.75035, -1.28615,  0.561096,  6,  2.50, -1.10, 1.10, -1.10, 1.10, 1.0}, // 13 |
  {-0.386753, -0.0610025, -1.02847,  0.78619, -0.984828,  3,  5.00, -1.20, 1.20, -1.20, 1.20, 0.0}, // 14 | special
  { 0.982876, -1.1125600, 0.500411, -1.44111, -1.008560,  4,  7.00, -0.80, 0.80, -0.80, 0.80, 0.0}, // 15 | special
  {-1.257170,  0.0390811,  0.13892, -0.87058,  0.023977,  7,  2.60, -1.20, 1.20, -1.20, 1.20, 1.0}, // 16 | Neat
  { 1.008500,  0.2275230, -0.56604, -0.62146,  0.693161,  5,  3.00, -1.20, 1.20, -1.20, 1.20, 1.0}, // 17 |
  { 1.618250, -1.6035300,  1.13920, -1.60120, -0.761638,  5,  2.80, -1.00, 1.00, -1.00, 1.00, 0.0}, // 18 |
  {-0.960670,  0.0834029,  1.01438,  1.05748, -0.599590, 21,  2.60, -1.20, 1.20, -1.20, 1.20, 1.0}, // 19 |
  { 0.908230,  0.3047990,  1.03560,  0.29872, -0.473521,  7,  3.00, -1.20, 1.20, -1.20, 1.20, 0.0}, // 20 |
  { 1.873130, -1.2822600, -1.28938, -1.36355, -0.141951, 21,  2.00, -1.10, 1.10, -1.10, 1.10, 1.0}, // 21 | NICE
  { 1.536250, -0.6547000, -1.43255, -0.24270,  0.128769, 31,  2.50, -1.00, 1.00, -1.00, 1.00, 0.0}, // 22 | NICE
  {-2.080000,  1.0000000, -0.10000,  0.16700,  0.000000,  7,  4.00, -1.20, 1.20, -1.20, 1.20, 0.0}, // 23 | d7 SIC BOOK
  {-2.500000,  5.0000000, -1.90000,  1.00000,  0.180000,  5,  2.75, -0.75, 0.75, -0.75, 0.75, 0.0}, // 24 | Z5 SIC BOOK
  { 2.500000, -2.5000000,  0.00000,  0.90000,  0.000000,  3,  2.75, -1.40, 1.40, -1.40, 1.40, 0.0}, // 25 | D3 SIC BOOK
  { 2.600000, -2.0000000,  0.00000, -0.50000,  0.000000,  5,  4.75, -1.30, 1.30, -1.30, 1.30, 1.0}, // 26 | D5 SIC BOOK
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// This is *identical* to what we did in pickoverPopcorn.cpp -- just way shorter.  It is longer still because we don't make this a subclass of
// mjr::ramCanvasPixelFilter::HomoBase in order to illustrate how to implement a RC pixel filter from scratch.  Also note we didn't need to DIY the color
// gradient with cmpRGBcornerDGradiant() as this gradient (0RYBCW) is available as a pre-built color scheme: csCCfractal0RYBCW.
class g2rgb8 {
  private:
    mjr::ramCanvas1c16b& attachedRC;
    int factor;
  public:
    g2rgb8(mjr::ramCanvas1c16b& aRC, uint64_t newFactor) : attachedRC(aRC), factor(static_cast<int>(newFactor)) {  }
    inline bool isIntAxOrientationNaturalX() { return attachedRC.isIntAxOrientationNaturalX(); }
    inline bool isIntAxOrientationNaturalY() { return attachedRC.isIntAxOrientationNaturalY(); }
    inline mjr::ramCanvas1c16b::coordIntType getNumPixX() { return attachedRC.getNumPixX(); }
    inline mjr::ramCanvas1c16b::coordIntType getNumPixY() { return attachedRC.getNumPixY(); }
    typedef mjr::colorRGB8b colorType;
    inline colorType getPxColorNC(rct::coordIntType x, rct::coordIntType y) { 
      colorType retColor;
      rct::csIntType tmp = static_cast<rct::csIntType>(attachedRC.getPxColorNC(x, y).getC0() * 1275 / factor);
      return retColor.cmpRGBcornerDGradiant(tmp, "0RYBCW");
    }
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int BSIZ = 7680/4;
  mjr::ramCanvas1c16b::colorType aColor;
  aColor.setChans(1);
  for(decltype(params.size()) j=0; j<params.size(); ++j) {
    mjr::ramCanvas1c16b theRamCanvas(BSIZ, BSIZ, params[j][7], params[j][8], params[j][9], params[j][10]);
    typename mjr::ramCanvas1c16b::coordFltType lambda = params[j][0];
    typename mjr::ramCanvas1c16b::coordFltType alpha  = params[j][1];
    typename mjr::ramCanvas1c16b::coordFltType beta   = params[j][2];
    typename mjr::ramCanvas1c16b::coordFltType gamma  = params[j][3];
    typename mjr::ramCanvas1c16b::coordFltType w      = params[j][4];
    double ipw   = static_cast<double>(params[j][6]);
    int n        = static_cast<int>(  params[j][5]);
    int filter   = static_cast<int>(  params[j][11]);

    std::complex<typename mjr::ramCanvas1c16b::coordFltType> cplxi (0,1);

    uint64_t maxitr = 10000000000ul;

    std::complex<typename mjr::ramCanvas1c16b::coordFltType> z(.01,.01);
    uint64_t maxII = 0;
    for(uint64_t i=0;i<maxitr;i++) {
      z = (lambda + alpha*z*std::conj(z)+beta*std::pow(z, n).real() + w*cplxi)*z+gamma*std::pow(std::conj(z), n-1);
      typename mjr::ramCanvas1c16b::coordFltType x=z.real(), y=z.imag();
      if(i>1000)
        theRamCanvas.incPxChan(x, y);
      if(theRamCanvas.getPxColor(x, y).getC0() > maxII) {
        maxII = theRamCanvas.getPxColor(x, y).getC0();
        if(maxII > 16384) { // 1/4 of max possible intensity
          std::cout << "ITER(" << j <<  "): " << i << " MAXS: " << maxII << " EXIT: Maximum image intensity reached" << std::endl;
          break;
        }
      }
      if((i % 10000000) == 0)
        std::cout << "ITER(" << j <<  "): " << i << " MAXS: " << maxII << std::endl;
    }

    std::cout << "ITER(" << j <<  "): " << "Big TIFF" << std::endl;
    theRamCanvas.writeTIFFfile("sic_" + mjr::math::str::fmt_int(j, 2, '0') + ".tiff");

    // Root image transform
    std::cout << "ITER(" << j <<  "): " << "TFRM & SCALE" << std::endl;
    theRamCanvas.autoHistStrech();
    //theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas1c16b::colorType::tfrmLn);
    theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas1c16b::colorType::tfrmStdPow, 1/ipw);
    if(filter)
      theRamCanvas.scaleDownMean(4);
    else
      theRamCanvas.scaleDownMax(4);
    theRamCanvas.autoHistStrech();

    // Compte new image max intensity
    std::cout << "ITER(" << j <<  "): " << "MAX" << std::endl;
    maxII = 0;
    for(auto& pixel : theRamCanvas)
      if(pixel.getC0() > maxII)
        maxII = pixel.getC0();

    std::cout << "ITER(" << j <<  "): " << "TIFF" << std::endl;
    /* Dump the 16-bit grayscale TIFF */
    theRamCanvas.writeTIFFfile("sicM_" + mjr::math::str::fmt_int(j, 2, '0') + ".tiff");
    /* Now we would like a false color version (24-bit RGB).   We could create a new canvas like this:
               rct cRamCanvas(theRamCanvas.getNumPixX(), theRamCanvas.getNumPixY());
               for(mjr::ramCanvas1c16b::coordIntType y=0;y<theRamCanvas.getNumPixY();y++)
                 for(mjr::ramCanvas1c16b::coordIntType x=0;x<theRamCanvas.getNumPixX();x++) {
                   auto ci = static_cast<rct::csIntType>(theRamCanvas.getPxColorRefNC(x, y).getC0() * 1275 / maxII)
                   cRamCanvas.getPxColorRefNC(x, y).cmpRGBcornerDGradiant(ci, "0RYBCW");
                 }
               cRamCanvas.writeTIFFfile("sicC_" + mjr::math::str::fmt_int(j, 2, '0') + ".tiff");
       We have a better way.  One that dosen't require the RAM to create a brand new canvas.  We can use
       the filter option of writeTIFFfile! */
    g2rgb8 pxFilt(theRamCanvas, maxII);
    theRamCanvas.writeTIFFfile("sicCC_" + mjr::math::str::fmt_int(j, 2, '0') + ".tiff", pxFilt, false);
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */
