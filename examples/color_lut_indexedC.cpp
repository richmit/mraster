// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      color_lut_indexedC.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw continous colorbrewer2 color gradients.@EOL
 @std       C++20
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
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

typedef mjr::color3c8b              ct;
typedef mjr::color3c8b::csIntType   cit;
typedef mjr::color3c8b::channelType cct;
typedef mjr::hershey::font          hft;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b theRamCanvas(800+500, 36*64+62);
  mjr::ramCanvas3c8b::colorType aColor;
  theRamCanvas.clrCanvasToBlack();
  int j = 0;

  j++; for(ct::csIntType i=0;i<65*ct::csCBAccent::maxNumC;  i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBAccent::c(i/65.0/ct::csCBAccent::maxNumC));      } theRamCanvas.drawString(" csCBAccent   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBBlues::maxNumC;   i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBBlues::c(i/65.0/ct::csCBBlues::maxNumC));        } theRamCanvas.drawString(" csCBBlues    ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBBrBG::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBBrBG::c(i/65.0/ct::csCBBrBG::maxNumC));          } theRamCanvas.drawString(" csCBBrBG     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBBuGn::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBBuGn::c(i/65.0/ct::csCBBuGn::maxNumC));          } theRamCanvas.drawString(" csCBBuGn     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBBuPu::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBBuPu::c(i/65.0/ct::csCBBuPu::maxNumC));          } theRamCanvas.drawString(" csCBBuPu     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBDark2::maxNumC;   i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBDark2::c(i/65.0/ct::csCBDark2::maxNumC));        } theRamCanvas.drawString(" csCBDark2    ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBGnBu::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBGnBu::c(i/65.0/ct::csCBGnBu::maxNumC));          } theRamCanvas.drawString(" csCBGnBu     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBGreens::maxNumC;  i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBGreens::c(i/65.0/ct::csCBGreens::maxNumC));      } theRamCanvas.drawString(" csCBGreens   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBGreys::maxNumC;   i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBGreys::c( i/65.0/ct::csCBGreys::maxNumC));       } theRamCanvas.drawString(" csCBGreys    ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBOrRd::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBOrRd::c(i/65.0/ct::csCBOrRd::maxNumC));          } theRamCanvas.drawString(" csCBOrRd     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBOranges::maxNumC; i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBOranges::c(i/65.0/ct::csCBOranges::maxNumC));    } theRamCanvas.drawString(" csCBOranges  ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBPRGn::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBPRGn::c(i/65.0/ct::csCBPRGn::maxNumC));          } theRamCanvas.drawString(" csCBPRGn     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBPaired::maxNumC;  i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBPaired::c(i/65.0/ct::csCBPaired::maxNumC));      } theRamCanvas.drawString(" csCBPaired   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBPastel1::maxNumC; i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBPastel1::c(i/65.0/ct::csCBPastel1::maxNumC));    } theRamCanvas.drawString(" csCBPastel1  ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBPastel2::maxNumC; i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBPastel2::c(i/65.0/ct::csCBPastel2::maxNumC));    } theRamCanvas.drawString(" csCBPastel2  ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBPiYG::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBPiYG::c(i/65.0/ct::csCBPiYG::maxNumC));          } theRamCanvas.drawString(" csCBPiYG     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBPuBu::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBPuBu::c(i/65.0/ct::csCBPuBu::maxNumC));          } theRamCanvas.drawString(" csCBPuBu     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBPuBuGn::maxNumC;  i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBPuBuGn::c(i/65.0/ct::csCBPuBuGn::maxNumC));      } theRamCanvas.drawString(" csCBPuBuGn   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBPuOr::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBPuOr::c(i/65.0/ct::csCBPuOr::maxNumC));          } theRamCanvas.drawString(" csCBPuOr     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBPuRd::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBPuRd::c(i/65.0/ct::csCBPuRd::maxNumC));          } theRamCanvas.drawString(" csCBPuRd     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBPurples::maxNumC; i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBPurples::c(i/65.0/ct::csCBPurples::maxNumC));    } theRamCanvas.drawString(" csCBPurples  ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBRdBu::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBRdBu::c(i/65.0/ct::csCBRdBu::maxNumC));          } theRamCanvas.drawString(" csCBRdBu     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBRdGy::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBRdGy::c(i/65.0/ct::csCBRdGy::maxNumC));          } theRamCanvas.drawString(" csCBRdGy     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBRdPu::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBRdPu::c(i/65.0/ct::csCBRdPu::maxNumC));          } theRamCanvas.drawString(" csCBRdPu     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBRdYlBu::maxNumC;  i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBRdYlBu::c(i/65.0/ct::csCBRdYlBu::maxNumC));      } theRamCanvas.drawString(" csCBRdYlBu   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBRdYlGn::maxNumC;  i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBRdYlGn::c(i/65.0/ct::csCBRdYlGn::maxNumC));      } theRamCanvas.drawString(" csCBRdYlGn   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBReds::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBReds::c(i/65.0/ct::csCBReds::maxNumC));          } theRamCanvas.drawString(" csCBReds     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBSet1::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBSet1::c(i/65.0/ct::csCBSet1::maxNumC));          } theRamCanvas.drawString(" csCBSet1     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBSet2::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBSet2::c(i/65.0/ct::csCBSet2::maxNumC));          } theRamCanvas.drawString(" csCBSet2     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBSet3::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBSet3::c(i/65.0/ct::csCBSet3::maxNumC));          } theRamCanvas.drawString(" csCBSet3     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBSpectral::maxNumC;i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBSpectral::c( i/65.0/ct::csCBSpectral::maxNumC)); } theRamCanvas.drawString(" csCBSpectral ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBYlGn::maxNumC;    i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBYlGn::c(i/65.0/ct::csCBYlGn::maxNumC));          } theRamCanvas.drawString(" csCBYlGn     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBYlGnBu::maxNumC;  i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBYlGnBu::c(i/65.0/ct::csCBYlGnBu::maxNumC));      } theRamCanvas.drawString(" csCBYlGnBu   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBYlOrBr::maxNumC;  i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBYlOrBr::c(i/65.0/ct::csCBYlOrBr::maxNumC));      } theRamCanvas.drawString(" csCBYlOrBr   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<65*ct::csCBYlOrRd::maxNumC;  i++) { theRamCanvas.drawLine(500+i, j*64, 500+i, j*64+62, ct::csCBYlOrRd::c(i/65.0/ct::csCBYlOrRd::maxNumC));      } theRamCanvas.drawString(" csCBYlOrRd   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 

  theRamCanvas.writeTIFFfile("color_lut_indexedC.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
