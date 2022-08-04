// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      color_lut_docs.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Produce preview impages for every color scheme -- for documentation.@EOL
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef mjr::color3c8b              ct;
typedef mjr::color3c8b::csIntType   csIt;
typedef mjr::color3c8b::csNatType   csNt;


int main(void) {
  int tall = 128;
  int gap = 8;
  mjr::ramCanvas3c8b theRC;

  int maxColors = 1024;
  theRC.resizeCanvas(maxColors, tall);
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csPLYgrey::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0)));    } theRC.writeTIFFfile("color_lut_docs_csPLYgrey.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csPLYquad::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0)));    } theRC.writeTIFFfile("color_lut_docs_csPLYquad.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csPLYturbo::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0)));   } theRC.writeTIFFfile("color_lut_docs_csPLYturbo.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csPLYparula::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0)));  } theRC.writeTIFFfile("color_lut_docs_csPLYparula.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csPLYmagma::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0)));   } theRC.writeTIFFfile("color_lut_docs_csPLYmagma.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csPLYinferno::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0))); } theRC.writeTIFFfile("color_lut_docs_csPLYinferno.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csPLYplasma::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0)));  } theRC.writeTIFFfile("color_lut_docs_csPLYplasma.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csPLYviridis::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0))); } theRC.writeTIFFfile("color_lut_docs_csPLYviridis.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csPLYcividis::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0))); } theRC.writeTIFFfile("color_lut_docs_csPLYcividis.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csPLYhsvRB::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0)));   } theRC.writeTIFFfile("color_lut_docs_csPLYhsvRB.tiff");

  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csCHstd::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0)));      } theRC.writeTIFFfile("color_lut_docs_csCHstd.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csCHblu::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0)));      } theRC.writeTIFFfile("color_lut_docs_csCHblu.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, ct::csCHvio::c(mjr::genLinMap(x, 0, 1024, 0.0, 1.0)));      } theRC.writeTIFFfile("color_lut_docs_csCHvio.tiff");

  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, mjr::color3c8b::csRainbowLA::c(maxColors, x));                                                    } theRC.writeTIFFfile("color_lut_docs_csRainbowLA.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, mjr::color3c8b::csRainbowCM::c(maxColors, x, mjr::ramCanvas3c8b::cmfInterpolationEnum::FLOOR));   } theRC.writeTIFFfile("color_lut_docs_csRainbowCMf.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, mjr::color3c8b::csRainbowCM::c(maxColors, x, mjr::ramCanvas3c8b::cmfInterpolationEnum::CEILING)); } theRC.writeTIFFfile("color_lut_docs_csRainbowCMc.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, mjr::color3c8b::csRainbowCM::c(maxColors, x, mjr::ramCanvas3c8b::cmfInterpolationEnum::NEAREST)); } theRC.writeTIFFfile("color_lut_docs_csRainbowCMn.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, mjr::color3c8b::csRainbowCM::c(maxColors, x, mjr::ramCanvas3c8b::cmfInterpolationEnum::LINEAR));  } theRC.writeTIFFfile("color_lut_docs_csRainbowCMl.tiff");
  for(int x=0;x<maxColors;x++) { theRC.drawLine(x, 0, x, tall, mjr::color3c8b::csRainbowCM::c(maxColors, x, mjr::ramCanvas3c8b::cmfInterpolationEnum::BUMP));    } theRC.writeTIFFfile("color_lut_docs_csRainbowCMb.tiff");

  theRC.resizeCanvas(ct::csPGrey3x::numC, tall); for(csIt x=0;x<ct::csPGrey3x::numC;x++) { theRC.drawLine(x, 0, x, tall, ct::csPGrey3x::c(x));      } theRC.writeTIFFfile("color_lut_docs_csPGrey3x.tiff");
  theRC.resizeCanvas(ct::csPGrey4x::numC, tall); for(csIt x=0;x<ct::csPGrey4x::numC;x++) { theRC.drawLine(x, 0, x, tall, ct::csPGrey4x::c(x));      } theRC.writeTIFFfile("color_lut_docs_csPGrey4x.tiff");

  theRC.resizeCanvas(ct::csCCdiag01::numC,              tall); for(csIt x=0;x<ct::csCCdiag01::numC;             x++) { theRC.drawLine(x, 0, x, tall, ct::csCCdiag01::c(x));              } theRC.writeTIFFfile("color_lut_docs_csCCdiag01.tiff");
  theRC.resizeCanvas(ct::csPGrey3x::numC,               tall); for(csIt x=0;x<ct::csPGrey3x::numC;              x++) { theRC.drawLine(x, 0, x, tall, ct::csPGrey3x::c(x));               } theRC.writeTIFFfile("color_lut_docs_csPGrey3x.tiff");
  theRC.resizeCanvas(ct::csPGrey4x::numC,               tall); for(csIt x=0;x<ct::csPGrey4x::numC;              x++) { theRC.drawLine(x, 0, x, tall, ct::csPGrey4x::c(x));               } theRC.writeTIFFfile("color_lut_docs_csPGrey4x.tiff");
  theRC.resizeCanvas(ct::csCCsumRGB::numC,              tall); for(csIt x=0;x<ct::csCCsumRGB::numC;             x++) { theRC.drawLine(x, 0, x, tall, ct::csCCsumRGB::c(x));              } theRC.writeTIFFfile("color_lut_docs_csCCsumRGB.tiff");
  theRC.resizeCanvas(ct::csCCsumBGR::numC,              tall); for(csIt x=0;x<ct::csCCsumBGR::numC;             x++) { theRC.drawLine(x, 0, x, tall, ct::csCCsumBGR::c(x));              } theRC.writeTIFFfile("color_lut_docs_csCCsumBGR.tiff");
  theRC.resizeCanvas(ct::csCCsumGRB::numC,              tall); for(csIt x=0;x<ct::csCCsumGRB::numC;             x++) { theRC.drawLine(x, 0, x, tall, ct::csCCsumGRB::c(x));              } theRC.writeTIFFfile("color_lut_docs_csCCsumGRB.tiff");
  theRC.resizeCanvas(ct::csCCsumBRG::numC,              tall); for(csIt x=0;x<ct::csCCsumBRG::numC;             x++) { theRC.drawLine(x, 0, x, tall, ct::csCCsumBRG::c(x));              } theRC.writeTIFFfile("color_lut_docs_csCCsumBRG.tiff");
  theRC.resizeCanvas(ct::csCCsumGBR::numC,              tall); for(csIt x=0;x<ct::csCCsumGBR::numC;             x++) { theRC.drawLine(x, 0, x, tall, ct::csCCsumGBR::c(x));              } theRC.writeTIFFfile("color_lut_docs_csCCsumGBR.tiff");
  theRC.resizeCanvas(ct::csCCsumRBG::numC,              tall); for(csIt x=0;x<ct::csCCsumRBG::numC;             x++) { theRC.drawLine(x, 0, x, tall, ct::csCCsumRBG::c(x));              } theRC.writeTIFFfile("color_lut_docs_csCCsumRBG.tiff");
  theRC.resizeCanvas(ct::csCCudRg::numC,                tall); for(csIt x=0;x<ct::csCCudRg::numC;               x++) { theRC.drawLine(x, 0, x, tall, ct::csCCudRg::c(x));                } theRC.writeTIFFfile("color_lut_docs_csCCudRg.tiff");
  theRC.resizeCanvas(ct::csCCudRb::numC,                tall); for(csIt x=0;x<ct::csCCudRb::numC;               x++) { theRC.drawLine(x, 0, x, tall, ct::csCCudRb::c(x));                } theRC.writeTIFFfile("color_lut_docs_csCCudRb.tiff");
  theRC.resizeCanvas(ct::csCCudGr::numC,                tall); for(csIt x=0;x<ct::csCCudGr::numC;               x++) { theRC.drawLine(x, 0, x, tall, ct::csCCudGr::c(x));                } theRC.writeTIFFfile("color_lut_docs_csCCudGr.tiff");
  theRC.resizeCanvas(ct::csCCudGb::numC,                tall); for(csIt x=0;x<ct::csCCudGb::numC;               x++) { theRC.drawLine(x, 0, x, tall, ct::csCCudGb::c(x));                } theRC.writeTIFFfile("color_lut_docs_csCCudGb.tiff");
  theRC.resizeCanvas(ct::csCCudBr::numC,                tall); for(csIt x=0;x<ct::csCCudBr::numC;               x++) { theRC.drawLine(x, 0, x, tall, ct::csCCudBr::c(x));                } theRC.writeTIFFfile("color_lut_docs_csCCudBr.tiff");
  theRC.resizeCanvas(ct::csCCudBg::numC,                tall); for(csIt x=0;x<ct::csCCudBg::numC;               x++) { theRC.drawLine(x, 0, x, tall, ct::csCCudBg::c(x));                } theRC.writeTIFFfile("color_lut_docs_csCCudBg.tiff");                                                                                                       
  theRC.resizeCanvas(ct::csCColdeRainbow::numC,         tall); for(csIt x=0;x<ct::csCColdeRainbow::numC;        x++) { theRC.drawLine(x, 0, x, tall, ct::csCColdeRainbow::c(x));         } theRC.writeTIFFfile("color_lut_docs_csCColdeRainbow.tiff");                                                                                                       
  theRC.resizeCanvas(ct::csCColdeIceToWaterToHot::numC, tall); for(csIt x=0;x<ct::csCColdeIceToWaterToHot::numC;x++) { theRC.drawLine(x, 0, x, tall, ct::csCColdeIceToWaterToHot::c(x)); } theRC.writeTIFFfile("color_lut_docs_csCColdeIceToWaterToHot.tiff");                                                                                                                                                        
  theRC.resizeCanvas(ct::csCColdeColdToHot::numC,       tall); for(csIt x=0;x<ct::csCColdeColdToHot::numC;      x++) { theRC.drawLine(x, 0, x, tall, ct::csCColdeColdToHot::c(x));       } theRC.writeTIFFfile("color_lut_docs_csCColdeColdToHot.tiff");
  theRC.resizeCanvas(ct::csCColdeFireRamp::numC,        tall); for(csIt x=0;x<ct::csCColdeFireRamp::numC;       x++) { theRC.drawLine(x, 0, x, tall, ct::csCColdeFireRamp::c(x));        } theRC.writeTIFFfile("color_lut_docs_csCColdeFireRamp.tiff");
  theRC.resizeCanvas(ct::csCCconsTwo::numC,             tall); for(csIt x=0;x<ct::csCCconsTwo::numC;            x++) { theRC.drawLine(x, 0, x, tall, ct::csCCconsTwo::c(x));             } theRC.writeTIFFfile("color_lut_docs_csCCconsTwo.tiff");
  theRC.resizeCanvas(ct::csCCconsOne::numC,             tall); for(csIt x=0;x<ct::csCCconsOne::numC;            x++) { theRC.drawLine(x, 0, x, tall, ct::csCCconsOne::c(x));             } theRC.writeTIFFfile("color_lut_docs_csCCconsOne.tiff");                                                                                                       
  theRC.resizeCanvas(ct::csCCdiagCR::numC,              tall); for(csIt x=0;x<ct::csCCdiagCR::numC;             x++) { theRC.drawLine(x, 0, x, tall, ct::csCCdiagCR::c(x));              } theRC.writeTIFFfile("color_lut_docs_csCCdiagCR.tiff");
  theRC.resizeCanvas(ct::csCCdiagMG::numC,              tall); for(csIt x=0;x<ct::csCCdiagMG::numC;             x++) { theRC.drawLine(x, 0, x, tall, ct::csCCdiagMG::c(x));              } theRC.writeTIFFfile("color_lut_docs_csCCdiagMG.tiff");
  theRC.resizeCanvas(ct::csCCdiagYB::numC,              tall); for(csIt x=0;x<ct::csCCdiagYB::numC;             x++) { theRC.drawLine(x, 0, x, tall, ct::csCCdiagYB::c(x));              } theRC.writeTIFFfile("color_lut_docs_csCCdiagYB.tiff");
  theRC.resizeCanvas(ct::csHSLhR::numC,                 tall); for(csNt x=0;x<ct::csHSLhR::numC;                x++) { theRC.drawLine(x, 0, x, tall, ct::csHSLhR::c(x));                 } theRC.writeTIFFfile("color_lut_docs_csHSLhR.tiff");
  theRC.resizeCanvas(ct::csHSLhG::numC,                 tall); for(csNt x=0;x<ct::csHSLhG::numC;                x++) { theRC.drawLine(x, 0, x, tall, ct::csHSLhG::c(x));                 } theRC.writeTIFFfile("color_lut_docs_csHSLhG.tiff");
  theRC.resizeCanvas(ct::csHSLhB::numC,                 tall); for(csNt x=0;x<ct::csHSLhB::numC;                x++) { theRC.drawLine(x, 0, x, tall, ct::csHSLhB::c(x));                 } theRC.writeTIFFfile("color_lut_docs_csHSLhB.tiff");
  theRC.resizeCanvas(ct::csHSLhM::numC,                 tall); for(csNt x=0;x<ct::csHSLhM::numC;                x++) { theRC.drawLine(x, 0, x, tall, ct::csHSLhM::c(x));                 } theRC.writeTIFFfile("color_lut_docs_csHSLhM.tiff");
  theRC.resizeCanvas(ct::csHSLhY::numC,                 tall); for(csNt x=0;x<ct::csHSLhY::numC;                x++) { theRC.drawLine(x, 0, x, tall, ct::csHSLhY::c(x));                 } theRC.writeTIFFfile("color_lut_docs_csHSLhY.tiff");
  theRC.resizeCanvas(ct::csHSLhC::numC,                 tall); for(csNt x=0;x<ct::csHSLhC::numC;                x++) { theRC.drawLine(x, 0, x, tall, ct::csHSLhC::c(x));                 } theRC.writeTIFFfile("color_lut_docs_csHSLhC.tiff");

  int tg = tall+gap;
//  theRC.resizeCanvas(ct::csCBSpectral::maxNumC*tg, tall); for(csNt x=0;x<ct::csCBSpectral::maxNumC;                x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBSpectral::c(x));                 } theRC.writeTIFFfile("color_lut_docs_csCBSpectral.tiff");

  theRC.resizeCanvas(ct::csCBAccent::maxNumC*tg,  tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBAccent::maxNumC;   x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBAccent::c(x));   } theRC.writeTIFFfile("color_lut_docs_csCBAccent.tiff");
  theRC.resizeCanvas(ct::csCBBlues::maxNumC*tg,   tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBBlues::maxNumC;    x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBBlues::c(x));    } theRC.writeTIFFfile("color_lut_docs_csCBBlues.tiff");
  theRC.resizeCanvas(ct::csCBBrBG::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBBrBG::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBBrBG::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBBrBG.tiff");
  theRC.resizeCanvas(ct::csCBBuGn::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBBuGn::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBBuGn::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBBuGn.tiff");
  theRC.resizeCanvas(ct::csCBBuPu::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBBuPu::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBBuPu::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBBuPu.tiff");
  theRC.resizeCanvas(ct::csCBDark2::maxNumC*tg,   tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBDark2::maxNumC;    x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBDark2::c(x));    } theRC.writeTIFFfile("color_lut_docs_csCBDark2.tiff");
  theRC.resizeCanvas(ct::csCBGnBu::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBGnBu::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBGnBu::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBGnBu.tiff");
  theRC.resizeCanvas(ct::csCBGreens::maxNumC*tg,  tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBGreens::maxNumC;   x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBGreens::c(x));   } theRC.writeTIFFfile("color_lut_docs_csCBGreens.tiff");
  theRC.resizeCanvas(ct::csCBGreys::maxNumC*tg,   tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBGreys::maxNumC;    x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBGreys::c(x));    } theRC.writeTIFFfile("color_lut_docs_csCBGreys.tiff");
  theRC.resizeCanvas(ct::csCBOrRd::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBOrRd::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBOrRd::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBOrRd.tiff");
  theRC.resizeCanvas(ct::csCBOranges::maxNumC*tg, tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBOranges::maxNumC;  x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBOranges::c(x));  } theRC.writeTIFFfile("color_lut_docs_csCBOranges.tiff");
  theRC.resizeCanvas(ct::csCBPRGn::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBPRGn::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBPRGn::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBPRGn.tiff");
  theRC.resizeCanvas(ct::csCBPaired::maxNumC*tg,  tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBPaired::maxNumC;   x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBPaired::c(x));   } theRC.writeTIFFfile("color_lut_docs_csCBPaired.tiff");
  theRC.resizeCanvas(ct::csCBPastel1::maxNumC*tg, tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBPastel1::maxNumC;  x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBPastel1::c(x));  } theRC.writeTIFFfile("color_lut_docs_csCBPastel1.tiff");
  theRC.resizeCanvas(ct::csCBPastel2::maxNumC*tg, tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBPastel2::maxNumC;  x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBPastel2::c(x));  } theRC.writeTIFFfile("color_lut_docs_csCBPastel2.tiff");
  theRC.resizeCanvas(ct::csCBPiYG::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBPiYG::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBPiYG::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBPiYG.tiff");
  theRC.resizeCanvas(ct::csCBPuBu::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBPuBu::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBPuBu::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBPuBu.tiff");
  theRC.resizeCanvas(ct::csCBPuBuGn::maxNumC*tg,  tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBPuBuGn::maxNumC;   x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBPuBuGn::c(x));   } theRC.writeTIFFfile("color_lut_docs_csCBPuBuGn.tiff");
  theRC.resizeCanvas(ct::csCBPuOr::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBPuOr::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBPuOr::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBPuOr.tiff");
  theRC.resizeCanvas(ct::csCBPuRd::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBPuRd::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBPuRd::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBPuRd.tiff");
  theRC.resizeCanvas(ct::csCBPurples::maxNumC*tg, tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBPurples::maxNumC;  x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBPurples::c(x));  } theRC.writeTIFFfile("color_lut_docs_csCBPurples.tiff");
  theRC.resizeCanvas(ct::csCBRdBu::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBRdBu::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBRdBu::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBRdBu.tiff");
  theRC.resizeCanvas(ct::csCBRdGy::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBRdGy::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBRdGy::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBRdGy.tiff");
  theRC.resizeCanvas(ct::csCBRdPu::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBRdPu::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBRdPu::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBRdPu.tiff");
  theRC.resizeCanvas(ct::csCBRdYlBu::maxNumC*tg,  tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBRdYlBu::maxNumC;   x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBRdYlBu::c(x));   } theRC.writeTIFFfile("color_lut_docs_csCBRdYlBu.tiff");
  theRC.resizeCanvas(ct::csCBRdYlGn::maxNumC*tg,  tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBRdYlGn::maxNumC;   x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBRdYlGn::c(x));   } theRC.writeTIFFfile("color_lut_docs_csCBRdYlGn.tiff");
  theRC.resizeCanvas(ct::csCBReds::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBReds::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBReds::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBReds.tiff");
  theRC.resizeCanvas(ct::csCBSet1::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBSet1::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBSet1::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBSet1.tiff");
  theRC.resizeCanvas(ct::csCBSet2::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBSet2::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBSet2::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBSet2.tiff");
  theRC.resizeCanvas(ct::csCBSet3::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBSet3::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBSet3::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBSet3.tiff");
  theRC.resizeCanvas(ct::csCBSpectral::maxNumC*tg,tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBSpectral::maxNumC; x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBSpectral::c(x)); } theRC.writeTIFFfile("color_lut_docs_csCBSpectral.tiff");
  theRC.resizeCanvas(ct::csCBYlGn::maxNumC*tg,    tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBYlGn::maxNumC;     x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBYlGn::c(x));     } theRC.writeTIFFfile("color_lut_docs_csCBYlGn.tiff");
  theRC.resizeCanvas(ct::csCBYlGnBu::maxNumC*tg,  tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBYlGnBu::maxNumC;   x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBYlGnBu::c(x));   } theRC.writeTIFFfile("color_lut_docs_csCBYlGnBu.tiff");
  theRC.resizeCanvas(ct::csCBYlOrBr::maxNumC*tg,  tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBYlOrBr::maxNumC;   x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBYlOrBr::c(x));   } theRC.writeTIFFfile("color_lut_docs_csCBYlOrBr.tiff");
  theRC.resizeCanvas(ct::csCBYlOrRd::maxNumC*tg,  tall); theRC.clrCanvas("white");for(csNt x=0;x<ct::csCBYlOrRd::maxNumC;   x++) { theRC.drawFillRectangle(x*tg, 0, x*tg+tall, tall, ct::csCBYlOrRd::c(x));   } theRC.writeTIFFfile("color_lut_docs_csCBYlOrRd.tiff");


}
