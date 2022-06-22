// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      color_lut_indexed.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw several examples of indexed color pallets.@EOL
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
***************************************************************************************************************************************************************/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <string>                                                        /* C++ strings             C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b theRamCanvas(450, 832);
  mjr::ramCanvas3c8b::colorType aColor;
  for(int doWS=0; doWS<2; doWS++) {
    int i = 0;
    for(int x=0;x<48;x++) {
      int y = 0;
      y++; aColor.icpSetColor(i, mjr::icp_uO_BrBu_10);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_BrBu_12);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_BuDOr_12);     if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_BuDOr_18);     if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_BuDRd_12);     if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_BuDRd_18);     if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_BuGr_14);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_BuGy_8);       if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_BuOrR_14);     if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_BuOr_12);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_BuOr_8);       if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_Bu_10);        if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_Bu_7);         if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_Cat_12);       if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_GrMg_16);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_RdYlBu_11b);   if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_uO_StepSeq_25);   if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Accent_08);    if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Blues_09);     if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_BrBG_11);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_BuGn_09);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_BuPu_09);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Dark2_08);     if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_GnBu_09);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Greens_09);    if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Greys_09);     if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_OrRd_09);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Oranges_09);   if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_PRGn_11);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Paired_12);    if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Pastel2_08);   if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_PiYG_11);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_PuBuGn_09);    if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_PuBu_09);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_PuOr_11);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_PuRd_09);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Purples_09);   if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_RdBu_11);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_RdGy_11);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_RdPu_09);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_RdYlBu_11);    if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_RdYlGn_11);    if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Reds_09);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Set1_09);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Set2_08);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Set3_12);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_Spectral_11);  if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_YlGnBu_09);    if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_YlGn_09);      if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      y++; aColor.icpSetColor(i, mjr::icp_CB_YlOrRd_09);    if(doWS) aColor.tfrmWebSafe216();  theRamCanvas.drawFillRectangle(x*16, y*16, x*16+14, y*16+14, aColor);
      i++;
    }
    theRamCanvas.writeTIFFfile(std::string("color_lut_indexed") + (doWS?"WS":"TC") + ".tiff");
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
