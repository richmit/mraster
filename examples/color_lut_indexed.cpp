// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      color_lut_indexed.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw colorbrewer2 color pallets.@EOL
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
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <string>                                                        /* C++ strings             C++11    */

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

  j++; for(ct::csIntType i=0;i<ct::csCBAccent::maxNumC;  i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBAccent::c(i));   } theRamCanvas.drawString(" csCBAccent   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBBlues::maxNumC;   i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBBlues::c(i));    } theRamCanvas.drawString(" csCBBlues    ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBBrBG::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBBrBG::c(i));     } theRamCanvas.drawString(" csCBBrBG     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBBuGn::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBBuGn::c(i));     } theRamCanvas.drawString(" csCBBuGn     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBBuPu::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBBuPu::c(i));     } theRamCanvas.drawString(" csCBBuPu     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBDark2::maxNumC;   i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBDark2::c(i));    } theRamCanvas.drawString(" csCBDark2    ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBGnBu::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBGnBu::c(i));     } theRamCanvas.drawString(" csCBGnBu     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBGreens::maxNumC;  i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBGreens::c(i));   } theRamCanvas.drawString(" csCBGreens   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBGreys::maxNumC;   i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBGreys::c(i));    } theRamCanvas.drawString(" csCBGreys    ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBOrRd::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBOrRd::c(i));     } theRamCanvas.drawString(" csCBOrRd     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBOranges::maxNumC; i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBOranges::c(i));  } theRamCanvas.drawString(" csCBOranges  ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBPRGn::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBPRGn::c(i));     } theRamCanvas.drawString(" csCBPRGn     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBPaired::maxNumC;  i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBPaired::c(i));   } theRamCanvas.drawString(" csCBPaired   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBPastel1::maxNumC; i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBPastel1::c(i));  } theRamCanvas.drawString(" csCBPastel1  ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBPastel2::maxNumC; i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBPastel2::c(i));  } theRamCanvas.drawString(" csCBPastel2  ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBPiYG::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBPiYG::c(i));     } theRamCanvas.drawString(" csCBPiYG     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBPuBu::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBPuBu::c(i));     } theRamCanvas.drawString(" csCBPuBu     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBPuBuGn::maxNumC;  i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBPuBuGn::c(i));   } theRamCanvas.drawString(" csCBPuBuGn   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBPuOr::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBPuOr::c(i));     } theRamCanvas.drawString(" csCBPuOr     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBPuRd::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBPuRd::c(i));     } theRamCanvas.drawString(" csCBPuRd     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBPurples::maxNumC; i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBPurples::c(i));  } theRamCanvas.drawString(" csCBPurples  ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBRdBu::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBRdBu::c(i));     } theRamCanvas.drawString(" csCBRdBu     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBRdGy::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBRdGy::c(i));     } theRamCanvas.drawString(" csCBRdGy     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBRdPu::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBRdPu::c(i));     } theRamCanvas.drawString(" csCBRdPu     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBRdYlBu::maxNumC;  i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBRdYlBu::c(i));   } theRamCanvas.drawString(" csCBRdYlBu   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBRdYlGn::maxNumC;  i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBRdYlGn::c(i));   } theRamCanvas.drawString(" csCBRdYlGn   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBReds::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBReds::c(i));     } theRamCanvas.drawString(" csCBReds     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBSet1::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBSet1::c(i));     } theRamCanvas.drawString(" csCBSet1     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBSet2::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBSet2::c(i));     } theRamCanvas.drawString(" csCBSet2     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBSet3::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBSet3::c(i));     } theRamCanvas.drawString(" csCBSet3     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBSpectral::maxNumC;i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBSpectral::c(i)); } theRamCanvas.drawString(" csCBSpectral ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBYlGn::maxNumC;    i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBYlGn::c(i));     } theRamCanvas.drawString(" csCBYlGn     ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBYlGnBu::maxNumC;  i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBYlGnBu::c(i));   } theRamCanvas.drawString(" csCBYlGnBu   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBYlOrBr::maxNumC;  i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBYlOrBr::c(i));   } theRamCanvas.drawString(" csCBYlOrBr   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 
  j++; for(ct::csIntType i=0;i<ct::csCBYlOrRd::maxNumC;  i++) { theRamCanvas.drawFillRectangle(500+i*64, j*64, 500+i*64+62, j*64+62, ct::csCBYlOrRd::c(i));   } theRamCanvas.drawString(" csCBYlOrRd   ", hft::ROMAN_SL_SANSERIF, 0, j*64+28, "red",  1.5, 20); 

    theRamCanvas.writeTIFFfile("color_lut_indexed.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */
