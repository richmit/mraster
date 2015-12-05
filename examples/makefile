# -*- Mode:Makefile; Coding:us-ascii-unix; fill-column:158 -*-
################################################################################################################################################################
##
# @file      makefile
# @author    Mitch Richling <http://www.mitchr.me>
# @brief     Makefile for ramCanvas example programs.@EOL
# @copyright
#  @parblock
#  Copyright (c) 2015, Mitchell Jay Richling <http://www.mitchr.me> All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
#  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.
#
#  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#
#  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without
#     specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
#  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#  @endparblock
################################################################################################################################################################


################################################################################################################################################################
# Build examples with third party library dependencies
DO_IMAGEMAGICK = NO
DO_GLUT        = YES
DO_CFITSIO     = NO

################################################################################################################################################################
# ramCanvas stuff
RCHOME 	  = ../lib
RCHPPF    = $(RCHOME)/point2d.hpp $(RCHOME)/colorData.hpp $(RCHOME)/colorTpl.hpp $(RCHOME)/ramCanvasTpl.hpp $(RCHOME)/ramConfig.hpp $(RCHOME)/mapclamp.hpp $(RCHOME)/color.hpp $(RCHOME)/ramCanvas.hpp
RCCPPF    = $(RCHOME)/colorData.cpp $(RCHOME)/hersheyFontData.cpp

################################################################################################################################################################
# Define targets
TCOLORS  = colorAll colorWebTriangle colorWebRectangle colorCubeGraphRamps colorIndexedPallets colorGeneralRamps colorRainbows colorInterplHLSvsRGB
TTEST    = testDraw testDraw2 bmark testColor testPoint testStrings testGlyph testFonts testBaryTry
TIMGPRO  = imgProExample
TFRACTAL = mandelbrot_c sierpinskiTriangle newton3_c newton3_c newton2_c newton newton_c distanceMandelbrot mandelbrot potMandelbrot triangleMandelbrot peterdejong sic sic_search tippets biomorph1 biomorph2 bifurcationDiagram
TMATHGR  = levelCCurves

TGLUT    = glutImage
TIMK     = readIMfile
TFITS    = readFITSfile

TARGETS  := $(TCOLORS) $(TTEST) $(TFRACTAL) $(TMATHGR) $(TIMGPRO)

################################################################################################################################################################
# POV-Ray

#POPT = -Q11 +A0.05
#POPT = -Q3  +A0.99

################################################################################################################################################################
# Get platform
UNAME_S := $(shell uname -s)

################################################################################################################################################################
# Set the compiler
ifeq "$(UNAME_S)" 'Darwin'
	CXX = clang++
else	
    CXX ?= g++
endif

################################################################################################################################################################
# Set the compiler options
ifeq "$(CXX)" 'g++'
    CXXFLAGS = -Wstrict-overflow=0 -ffast-math -std=c++14 -Wall -O5 -I$(RCHOME)
endif
ifeq "$(CXX)" 'clang++'
    CXXFLAGS = -Wstrict-overflow=0 -ffast-math -std=c++14 -Wall -O3 -I$(RCHOME)
endif
ifeq "$(CXX)" 'icc'
	CXXFLAGS = -std=c++14 -Wall -O3 -I$(RCHOME)
endif

################################################################################################################################################################
# If we are building imagemagic executable, find the libraries
ifeq "$(DO_IMAGEMAGICK)" 'YES'
    IMFLAGS = `pkg-config --cflags --libs ImageMagick`
    TARGETS += $(TIMK)
endif

################################################################################################################################################################
# If we are building glut binaries, find the libraries
ifeq "$(DO_GLUT)" 'YES'
   ifeq "$(UNAME_S)" 'Darwin'
       GLUTFLAGS = -framework AGL -framework GLUT -framework OpenGL -framework Carbon -framework ApplicationServices -lobjc -dylib_file /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib
   else
       GLUTFLAGS = -lglut -lGL -lGLU
   endif
   TARGETS += $(TGLUT)
endif

################################################################################################################################################################
all : $(TARGETS)

vtest :
	echo $(UNAME_S)
	echo $(CXX)

newton : newton.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) newton.cpp -o newton

newton_c : newton_c.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) newton_c.cpp -o newton_c

newton2_c : newton2_c.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) newton2_c.cpp -o newton2_c

newton3_c : newton3_c.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) newton3_c.cpp -o newton3_c

biomorph1 : biomorph1.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) biomorph1.cpp -o biomorph1

biomorph2 : biomorph2.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) biomorph2.cpp -o biomorph2

bifurcationDiagram : bifurcationDiagram.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) bifurcationDiagram.cpp -o bifurcationDiagram

peterdejong : peterdejong.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) peterdejong.cpp -o peterdejong

sic : sic.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) sic.cpp -o sic

sic_search : sic_search.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) sic_search.cpp -o sic_search

colorAll : colorAll.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) colorAll.cpp -o colorAll

colorWebTriangle : colorWebTriangle.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) colorWebTriangle.cpp -o colorWebTriangle

colorWebRectangle : colorWebRectangle.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) colorWebRectangle.cpp -o colorWebRectangle

bmark : bmark.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) bmark.cpp -o bmark

testDraw : testDraw.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) testDraw.cpp -o testDraw

testBaryTry : testBaryTry.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) testBaryTry.cpp -o testBaryTry

testPoint : testPoint.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) testPoint.cpp -o testPoint

testStrings : testStrings.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) testStrings.cpp -o testStrings

testFonts : testFonts.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) testFonts.cpp -o testFonts

testGlyph : testGlyph.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) testGlyph.cpp -o testGlyph

colorCubeGraphRamps : colorCubeGraphRamps.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) colorCubeGraphRamps.cpp -o colorCubeGraphRamps

colorGeneralRamps : colorGeneralRamps.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) colorGeneralRamps.cpp -o colorGeneralRamps

distanceMandelbrot : distanceMandelbrot.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) distanceMandelbrot.cpp -o distanceMandelbrot

levelCCurves : levelCCurves.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) levelCCurves.cpp -lm -o levelCCurves

lineTest : lineTest.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) lineTest.cpp -o lineTest

mandelbrot : mandelbrot.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) mandelbrot.cpp -o mandelbrot

mandelbrot_c : mandelbrot_c.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) mandelbrot_c.cpp -o mandelbrot_c

potMandelbrot : potMandelbrot.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) potMandelbrot.cpp -o potMandelbrot

testDraw2 : testDraw2.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) testDraw2.cpp -o testDraw2

testColor : testColor.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) testColor.cpp -o testColor

sierpinskiTriangle : sierpinskiTriangle.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) sierpinskiTriangle.cpp -o sierpinskiTriangle

triangleMandelbrot : triangleMandelbrot.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) triangleMandelbrot.cpp -o triangleMandelbrot

colorIndexedPallets : colorIndexedPallets.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) colorIndexedPallets.cpp -o colorIndexedPallets

colorRainbows : colorRainbows.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) colorRainbows.cpp -o colorRainbows

colorInterplHLSvsRGB : colorInterplHLSvsRGB.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) colorInterplHLSvsRGB.cpp -o colorInterplHLSvsRGB

imgProExample : imgProExample.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) imgProExample.cpp -o imgProExample

tippets : tippets.cpp $(RCHPPF) $(RCCPPF)
		$(CXX) $(CXXFLAGS) $(RCCPPF) tippets.cpp -o tippets

glutImage : glutImage.cpp  $(RCHPPF) $(RCCPPF)

		$(CXX) $(CXXFLAGS) $(RCCPPF) glutImage.cpp -o glutImage $(GLUTFLAGS)

potMandelbrot_a_0.tga potMandelbrot_a_1.tga potMandelbrot_a_2.tga potMandelbrot_b_0.tga potMandelbrot_b_1.tga potMandelbrot_b_2.tga : potMandelbrot
	./potMandelbrot

potMandelbrot_b_0.mrd : potMandelbrot_b_0.mrw
	dd if=potMandelbrot_b_0.mrw skip=100 iflag=skip_bytes of=potMandelbrot_b_0.mrd

potMandelbrot_b_0d.png : potMandelbrot_b_0.pov potMandelbrot_b_0.tga
	povray -W3900 -H2275 -Q11 +A0.05 -AM2 -R6 +J5 +WT8 -P -D -OpotMandelbrot_b_0d.png -IpotMandelbrot_b_0.pov

potMandelbrot_b_1d.png : potMandelbrot_b_1.pov potMandelbrot_b_1.tga
	povray -W3900 -H2275 -Q11 +A0.05 -AM2 -R6 +J5 +WT8 -P -D -OpotMandelbrot_b_1d.png -IpotMandelbrot_b_1.pov   

potMandelbrot_b_2d.png : potMandelbrot_b_2.pov potMandelbrot_b_2.tga
	povray -W3900 -H2275 -Q11 +A0.05 -AM2 -R6 +J5 +WT8 -P -D -OpotMandelbrot_b_2d.png -IpotMandelbrot_b_2.pov

potMandelbrot_a_0d.png : potMandelbrot_a_0.pov potMandelbrot_a_0.tga
	povray -W3900 -H2275 -Q11 +A0.05 -AM2 -R6 +J5 +WT8 -P -D -OpotMandelbrot_a_0d.png -IpotMandelbrot_a_0.pov

potMandelbrot_a_1d.png : potMandelbrot_a_1.pov potMandelbrot_a_1.tga
	povray -W3900 -H2275 -Q11 +A0.05 -AM2 -R6 +J5 +WT8 -P -D -OpotMandelbrot_a_1d.png -IpotMandelbrot_a_1.pov   

potMandelbrot_a_2d.png : potMandelbrot_a_2.pov potMandelbrot_a_2.tga
	povray -W3900 -H2275 -Q11 +A0.05 -AM2 -R6 +J5 +WT8 -P -D -OpotMandelbrot_a_2d.png -IpotMandelbrot_a_2.pov

potMandelbrot_a_1t.png : potMandelbrot_a_1t.pov potMandelbrot_a_0.tga
	povray -W3900 -H3900 -Q11 +A0.05 -AM2 -R6 +J5 +WT8 -P -D -OpotMandelbrot_a_1t.png -IpotMandelbrot_a_1t.pov

render : potMandelbrot_b_0d.png potMandelbrot_b_1d.png potMandelbrot_b_2d.png potMandelbrot_a_0d.png potMandelbrot_a_1d.png potMandelbrot_a_2d.png potMandelbrot_a_1t.png
	espeak "render complete"

clean :
		rm -f *~
		rm -f a.out
		rm -f x.tga
		rm -f *.o
		rm -f *.bak
		rm -f $(TARGETS)
