// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      mainPage.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Doxygen content.@EOL
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

/**
 @mainpage
 Introduction
 ============

 This library delivers flexible and easy programmatic access to a broad range of low level, high performance raster graphics drawing techniques.

 The primary use case is direct image synthesis for visualization of mathematical objects

   - Raster based fractals like the Mandelbrot set

   - Real functions on R^2 (level curves, filled contours, scalar fields, etc...)

   - Complex functions (phase portraits)

   - Iterated system fractals like the Sierpinski gasket

   - Povray Maps (Bump, texture, and normal) and Height fields

   - Continuous color schemes for 1) Drawing tools (Inkscape), 2) SVG files, 3) Scientific visualization tools (Visit)

 Secondary use cases mostly include research topics

   - Back end for a my ray tracing manifolds with non-linear optics in 4D euclidean space

   - Optical distortion correction

   - Stenography

   - Image encryption

   - Image compression

 Design goals:

   - Extreme portability (ISO C++ only, minimal external library requirements, etc...)

   - Ease of use and adaptability to many use cases

     What do I mean by "adaptability"?  For example, colors may be set via naive types, numeric characters, hex strings, web color hex strings, name strings,
     enumerated corner names, symbolic characters, or floating point numbers.  The idea is to make the classes adapt to the setting in which they are being
     used, and not to force programmers to adapt.

   - High performance

     When performance and portability are at odds, portability wins.

 History
 =======

 This library began in the mid 80's as an abstraction layer on top of Microsoft, Apple, and X11 GUI APIs.  It was written in C and made heavy use of macros to
 translate my "wrapper API" into the native API.  The primary goal was to draw a mathematical object on screen, and allow the user to interact with it.

 In the late 80s and early 90s I began to make use of HPC hardware (supercomputers) located at various sites around the globe and was faced with the new
 challenge of drawing pictures without the aid of a graphics device or underlying APIs.  In order to use remote supercomputers to draw pictures off screen, I
 added a "RAM frame buffer" to this library.  Around the same time I began to take serious advantage of OpenGL hardware and software on RS/6000 and HP
 workstations.  This spelled the end for the library as it had existed before, and started an evolution to exclusively supporting RAM frame buffers.

 Once the limitations of adapting to underlying GUI APIs was removed, I was free to provide better organization and capabilities for abstraction and extension
 within the library itself.  The natural answer to both was reimplementing the entire thing in C++.

 In the mid 90's I found myself moving beyond 32bit RGBA -- RAW camera images, astrophotographs from CCDs, microscope imagers, and digital film scanners
 producing 16/32-bit greyscale and 48-bit RGB.  So I used templates to allow the ramCanvas to support such images, added quite a lot of image processing
 functionality, and broadened image file support (non-standard TIFF and FITS).

 Later tools began to appear for high dynamic range images, and standard image formats began to become broadly supported.  Around this same time, FOSS image
 processing platforms (imagej, GIMP, and ImageMagick) started to become more feature rich and robust.  Once I started using these tools, I refactored this
 library by removing external image library support (CFITSIO, libtiff, libjpeg, and libpng) dependencies and most of the image processing functionality
 (spatial methods, FFT, and general geometric transforms). This left behind a small kernel of routines for basic raster image drawing.

 Later I removed floating point images, and added optional libtiff support back.  This was done in such a way that most canvas objects may now be written to
 disk in a bit perfect way, and then read back in.  libtiff is only required for reading images, so the library is still free of dependencies for most of the
 identified use cases.

 Kool features
 =============

   - It has quite a bit of documentation generated with doxygen.  I used this project to really learn how doxygen works, and the result was more
     documentation than code. :)

   - Portable C++.

   - Good performance.

   - Write support for some image formats with no dependency on external libraries.

     - TGA (24-bit and the non-standard 8/16/32-bit greyscale images used by PovRay).

     - TIFF (usually bit perfect representations)

   - Reasonably efficient techniques are used for primitive scanline conversion and clipping.

   - Simple, but powerful, color support including HSV, wavelength, and RGB color specifications.  Unique color schemes are supported including 256,
     765, and 1020 level grey maps.  I have also included six different RGB color ramps (768 levels for 24-bit truecolor).  In addition, a 65K
     greyscale map is supported for generating Povray height fields.

   - "moveTo/lineTo" and "absolute" techniques are supported.

   - Every canvas has both an integer and real coordinate system.  The orientation of all axes is under user control.

   - The precision of floating point pixel coordinates is user selectable, as is the integer type used for pixel coordinate values.

   - Conditional compilation techniques can render different forms of the library tuned for various tasks.  For example, the moveTo/lineTo subsystem
     can be disabled.

   - Special versions of functions exist that have no error checking or clipping that provide abstraction for extensions, but don't impose a speed
     penalty or a deep knowledge of C++.

 Notes on the Code
 =================

 The code for this library all lives within the namespace of 'mjr' -- my initials.  This should help to avoid namespace conflicts.

 At this time everything is mostly implemented in header files with only large, static data sets placed into libraries.  This is a serious shift from the
 library based system used before.

 As far as I know this code infringes upon no patents or other IP.

 Organization of the code and include files
 ==========================================

 The library is template based and the primary players, canvas and color classes, are all templates.  Common data types, 4 channel/24-bit color
 types and canvases that use them for example, all have typedefs.  In addition, the various headers implementing the templates are included by
 headers defining the typedefs.  In this way, common usage of the library requires no use of template syntax (or the extra typing).

 The include files:

   - color.hpp ......... The include file most users will include for color support
   - ramCanvas.hpp ..... The include file most users will include for ramCanvas support (includes color.hpp)
   - ramConfig.hpp ..... Common config macros
   - colorTpl.hpp ...... Implementation of the color/pixel object
   - ramCanvasTpl.hpp .. Implementation for ramCanvasTpl object
   - colorData.cpp ..... Constants for color computations and color schemes
   - colorData.hpp ..... Include file for colorData.cpp
   - mapclamp.hpp ...... Fast functions used for clamping integers
   - mainPage.cpp ...... Documentation

 About Color Type Templates
 ==========================

 Color types are intended to store all color information for a single pixel.  Most common image structures can be identified by the number of
 channels (Red, Green, and Blue for example) and the depth of each channel (8-bit for example).  The most common configurations are:

           |---------+---------+------+-------+------------------+-------------------------------------------------|
           | Channel |    Bits | Data |  bits |                  |                                                 |
           |   Count |     Per | Data |   per | Common Name      | Notes                                           |
           |         | Channel |      | pixel |                  |                                                 |
           |---------+---------+------+-------+------------------+-------------------------------------------------|
           |       3 |       8 | RGB  |    24 | 24-bit truecolor | Very common format.                             |
           |       4 |       8 | RGBA |    32 | truecolor+alpha  | Very common format.                             |
           |       3 |      16 | RGB  |    48 | 48-bit color     | High quality digital camera sensors.             |
           |       3 |      32 | RGB  |    96 | 96-bit color     | Usually a fusion from multiple CCDs             |
           |       1 |       8 | Grey |     8 | 8-bit greyscale  | Surveillance and Low Quality scientific imaging |
           |       1 |      16 | Grey |    16 | 16-bit greyscale | Typical scientific CCD equipment                |
           |       1 |      32 | Grey |    32 | 32-bit greyscale | High end scientific CCD equipment               |
           |---------+---------+------+-------+------------------+-------------------------------------------------|

 Drawing
 =======

 Primitive drawing functions generally come in several forms:

    - foo(<integer_coords>, <color>)
    - foo(<integer_coords>)
    - foo()
    - foo(<float_coords>, <color>)
    - foo(<float_coords>)
    - foo(<integer_points>, <color>)
    - foo(<integer_points>)
    - foo(<float_points>, <color>)
    - foo(<float_points>)
    - foo(<array_of_integer_points>, <color>)
    - foo(<array_of_integer_points>)
    - foo(<array_of_float_points>, <color>)
    - foo(<array_of_float_points>)

 This library supports both the "moveTo/lineTo" paradigm (i.e. move to A, draw line to B), and the "absolute" paradigm (i.e. draw a line from A to B).
 Because of this, some primitive drawing functions also have forms with fewer coordinates specified.  For example, we have a point drawing function that takes
 no arguments.  just with fewer coordinates.  Some primitives, like circles, require extra parameters to describe the primitive.  Such parameters right before
 the color arguments or last in the argument list if no color is specified.

 Various Color Schemes
 =====================

 Color Cube Edge/Diagonal Graph Color Schemes
 --------------------------------------------

 The RGB color cube:

                                  _________________________
                           green / _____________________  /| yellow
                                / / ___________________/ / |
                               / / /| |               / /  |
                              / / / | |              / / . |
                             / / /| | |             / / /| |
                            / / / | | |            / / / | |
                           / / /  | | |     white / / /| | |
                          / /_/__________________/ / / | | |
                         /________________________/ /  | | |
                    cyan | ______________________ | |  | | |
                         | | |    | | |_________| | |__| | |
                         | | |    | |___________| | |____| |
                         | | |   / / ___________| | |_  / / red
                         | | |  / / /           | | |/ / /
                         | | | / / /  black     | | | / /
                         | | |/ / /             | | |/ /
                         | | | / /              | | ' /
                         | | |/_/_______________| |  /
                         | |____________________| | /
                    blue |________________________|/ magenta

                  Vertexes and Center of the RGB Color Cube:
                  Name     R     G     B     Abriv
                  black    0.0   0.0   0.0   0
                  blue     0.0   0.0   1.0   b
                  green    0.0   1.0   0.0   g
                  red      1.0   0.0   0.0   r
                  yellow   1.0   1.0   0.0   y
                  cyan     0.0   1.0   1.0   c
                  magenta  1.0   0.0   1.0   m
                  white    1.0   1.0   1.0   w
                  grey50   0.5   0.5   0.5   h

 The edges of the cube taken with the corners as vertexes form a graph (we call it the cube edge graph).  Every trail (a walk with unique edges) with n edges
 generates a color scheme with maxChanVal*n-1 unique colors.  To make this scheme unique, we define the tree to have one of it's end points the "start" of the
 scheme -- so we can map the integers from [0,maxChanVal*n] to unique colors.

 Example:

    BCG defines a trail starting at B (blue), moving to C (cyan) next, and ending at G (green).  The color scheme has 0 mapped to blue (the first vertex), 256
    mapped to cyan (the second vertex), and 511 mapped to green (the final vertex).  For values between two vertex points, we linearly interpolate between the
    two values.

 If we expand the graph to also include edges between the diagonal points of each face (cyan to yellow for example), we have a larger graph with more options.
 We call this graph the face edge/diagonal graph.

 Color schemes defined in this way have several advantages, but can also be misleading because our perception of color change is non-linear across
 many such color maps.  We illustrate several useful and/or commonly used face edge/diagonal graph color schemes.

 Lastly, we can expand that graph by adding one vertex at the center of the cube -- we call it 'h'.  We add edges from the center to each corner.  We
 call this the "complete cube graph with center".

 Some API Notes
 --------------

 The color class implements many common and/or useful color cube graph based color schemes directly via named methods.  In addition, the class
 supports all graphs via the cmpColorRamp method -- this method takes a simple list of edges to traverse.

 The Color Cube Rainbow
 ----------------------

 This is one of the most commonly seen color schemes in scientific visualization, and it is also one of the worst because it can be misleading when
 mapped to linear values.

 The color cube rainbow map is generated by the unique six segment (6 vertex) cycle in the face edge graph not involving white or black.  Also known
 as the "Color Cube Rainbow".

 This is color scheme is not suggested for general use; however, ignoring this advice is so popular that a special method provides named support for the
 color cube rainbow:

  - RYGCBMR -- cmpClrCubeRainbow()

 If we expand to the edge face/diagonal graph, then we have may more six segment cycles not involving white or black.  None of them are commonly
 used; however, in some cases they preform better then the standard color cube rainbow map -- because the regions of extreme nonlinear perception in
 color change are in different places.  None of these maps is suggested for general use, and they are not commonly used enough to rate a named
 method.

  - RBCGYMR
  - RBCMYGR
  - RBGCMYR
  - RBGCYMR
  - RBGYCMR
  - RBMCGYR
  - RBMCYGR
  - RBMYCGR
  - RGBCMYR
  - RGBCYMR
  - RGBMCYR
  - RGCBMYR
  - RGYCBMR
  - RMBGCYR
  - RMCBGYR

 Hitting all the corners
 -----------------------

  A common request is for a cycle in the face edge graph that uses every corner color of the RGB cube.  Not only do we have one, but 6 uniquely
  different ones -- not counting rearrangements or reversals.

   - 0BCGYWMR0
   - 0BCWMRYG0
   - 0BMRYWCG0
   - 0BMWCGYR0
   - 0GCBMWYR0
   - 0GYWCBMR0

  Another common request is for trees (so no color is used twice) starting at black and ending at white.  Several trees exist of with lengths of 7
  segments and 5 segments.  None of them are of much use because they suffer from the same limitations as the color cube rainbow.  They are:

   - 0BCGYRMW
   - 0BMRYGCW
   - 0GCBMRYW
   - 0GYRMBCW
   - 0RMBCGYW
   - 0RYGCBMW
   - 0BCGYW
   - 0BMRYW
   - 0GCBMW
   - 0GYRMW
   - 0RMBCW
   - 0RYGCW

  The three segment trees from black to white are useful, and methods exist to support them directly.  The three segment trees have the useful quality
  that the intensity (sum of the components) is a monotone increasing function from zero up to three.  One of them (0RYW) is often called the "fire
  ramp" as it ranges from black (flame base), up to yellow, then red, and finally to white hot.

   - 0BCW == sumRampBGR()
   - 0BMW == sumRampBRG()
   - 0GCW == sumRampGBR()
   - 0GYW == sumRampGRB()
   - 0RMW == sumRampRBG()
   - 0RYW == sumRampRGB() == fireRamp()

  A popular trend is to use luminance based color schemes from the HLS color space.  This popularity is primarily due to a few very well received
  papers published in the early and mid 1990's following on the work of S. S. Stevens.  Some HLS schemes don't suffer from the perceptional
  non-linearity that some popular RGB schemes suffer from. What most people don't realize is that many of the most popular luminance based color
  schemes in the HLS color space are actually edge graphs in the RGB color cube!  It is also true that the most common "bad" color scheme in the RGB
  cube (the colorCubeRainbow), is an edge graph in the HLS hexcone!  In the end, the thing to remember is that both color spaces have both good and
  bad color schemes.  Of particular note, are the two segment trees from black to white in the RGB edge/diagonal graph -- they are the same as the two
  segment graphs in the edges of the HLS hexcone from black to white!

   - 0RW -- H=0   red edge of the HLS hexcone
   - 0YW -- H=60  yellow edge of the HLS hexcone
   - 0GW -- H=120 green edge of the HLS hexcone
   - 0CW -- H=180 cyan edge of the HLS hexcone
   - 0BW -- H=240 blue edge of the HLS hexcone
   - 0MW -- H=300 magenta edge of the HLS hexcone

 Hot Too Cold
 ------------

 A very common color map used to map data with ranges from cold up to hot is known as the "cold too hot ramp".  This ramp provides colors from blue, up
 through green, and ends in red. It suffers from the same defects as the color cube rainbow; however, its use is so common that special support is provided
 via a named method.

  - BCGYR -- cmpColdToHot()

 The traditional cold to hot ramp can be improved -- this is my personal opinion.  This new ramp still has the same problems the color cube rainbow has;
 however, it is more attractive.  This one moves from white (ice), up to water (blue), and then up to red (hot) via yellow.

  - WCBYR -- cmpIceToWaterToHot()

 Constant Intensity Cycles
 -------------------------

 Two cycles, with three edges each, exhibiting constant intensity for every color in the color scheme are genuinely useful.  They have the advantage that they
 always render a "bright" color.  The lower intensity version is best for projected media that don't do well with yellow.

  - CMY == cmpConstTwoRamp() -- intensity == 2
  - BRG == cmpConstOneRamp() -- intensity == 1

 One Segment Diverging Maps
 --------------------------

 One edge trees in the face diagonal graph with a nearly constant intensity of 2 along the entire edge are useful for "diverging" or "bipolar" color
 schemes.  By definition, such color schemes will never involve black or white.

 While rarely used, the following maps are useful and suggested.  None of them have the problems associated with the color cube rainbow.

  - YC  ==  cmpUpDownRampBr()
  - YM  ==  cmpUpDownRampBg()
  - MC  ==  cmpUpDownRampGr()
  - MY  ==  cmpUpDownRampGb()
  - CM  ==  cmpUpDownRampRg()
  - CY  ==  cmpUpDownRampRb()

 The naming convention for the methods is not obvious.  Take, for example, cmpUpDownRampBr.  This is so named because of the computational algorithm
 used to compute the scheme: Blue up, red down, green constant (maxChanVal).

 Three Segment Diverging Maps
 ----------------------------

 Some three edge trees utilizing very different colors for starting and terminal points can form very nice "divergent" color maps.  Such maps can
 successfully illustrate variables with both positive and negative values or two mutually exclusive, opposing variables.  Only two are directly
 supported via named methods (selected for attractiveness):

  - BWR  intensity between 1 and 3
  - CWM  intensity between 2 and 3

 Out of the graph
 ----------------

 A popular trend is to use saturation based color schemes from the HLS color space -- see the earlier comments regarding luminance based color
 schemes.  Essentially, such color maps extend from the center of HLS space, (0.0, 0.5, 0), to one of the primary color vertexes --- which have the
 same colors as the vertexes of the RGB cube excluding black and white.  As luck would have it, such sequences are the same as extending linearly
 from the center of RGB space, (0.5, 0.5, 0.5), to one of the vertexes excluding black and white!  One can think of this as extending the edge graph
 of the RGB cube with an extra vertex at the center of the cube.

 So we add a vertex to the RGB color cube edge graph.  We place it at the center of the cube, and add edges between this new vertex and the existing
 corners of the cube.  We call this new vertex 'H' -- for "Half way between everything". Using this new vertex, we have the following saturation
 based color schemes:

  - HR -- cmpRampGrey2R()
  - HG -- cmpRampGrey2G()
  - HB -- cmpRampGrey2B()
  - HC -- cmpRampGrey2C()
  - HY -- cmpRampGrey2Y()
  - HM -- cmpRampGrey2M()

 The traversal from black to white -- through the center point -- is directly supported via a named method.  Note that cmpColorRamp supports this via
 a graph string of "0W".

  - 0HW -- cmpGreyRGB()

 The other diagonal traversals (diagonal meaning through the center of the cube) are essentially two of the HLS saturation based schemes placed back
 to back.  They can form effective divergent color schemes.  Black to white is technical one of them, but we have already covered that one.  Note
 that the cmpColorRamp function will support this class of schemes with a two element graph -- the first vertex and the last. The remaining three
 diagonal schemes are as follows:

  - CHR -- cmpDiagRampCR()
  - MHG -- cmpDiagRampMG()
  - YHB -- cmpDiagRampYB()

 Special Indexed Pallets
 -----------------------

 Some special indexed color pallets exist in the library.  Some common ones are:

  - Black and White
  - Web Safe 216

 Several carefully selected pallets are also supported from Cynthia Brewer's ColorBrewer application or from the geography department at U of Oregon.
 For reference, both original sources (hopefully still on the web):

  - http://geography.uoregon.edu/datagraphics/color_scales.htm
  - http://www.ColorBrewer.org

 If you publish something using one of the color schemes from ColorBrewer, then Cynthia Brewer requests that you cite her work.  The following
 paragraph is from the original source:

            5. Citation
            Ahhh, that lavish citation I'm hoping for...
            Wording depends on context and I'm not too picky.
            If you add a note in the corner of a map, how about one of these:
                - Colors from www.ColorBrewer.org by Cynthia A. Brewer, Geography, Pennsylvania State University.
                - Map colors based on www.ColorBrewer.org, by Cynthia A. Brewer, Penn State.
                - Color symbols: ColorBrewer.org
            A reference in a journal article or report might look like:
                - Brewer, Cynthia A., 200x. http://www.ColorBrewer.org, accessed date.

 As a side note, Cynthia Brewer has a very nice book about making maps.  It is quite a nice read even for people who don't make maps for a living.
 You might check it out: "Designing Better Maps : A Guide for GIS Users".  Last I checked, the ISBN was 1589480899.

 Color Resources
 ---------------

 Some color resources on the web:

  - http://geography.uoregon.edu/datagraphics/color_scales.htm
  - http://www.ColorBrewer.org
  - http://www.caida.org/~youngh/colorscales/nonlinear.html
  - http://www.internettg.org/newsletter/mar99/accessibility_color_challenged.html
  - http://www.research.ibm.com/dx/proceedings/pravda/index.htm
  - http://www.research.ibm.com/dx/proceedings/pravda/truevis.htm
  - http://www.research.ibm.com/people/l/lloydt/color/color.HTM

  S. S. Stevens did the ground work upon which modern luminance and saturation based color schemes are based.  The original reference:

   - Stevens, S. S.  Matching Functions Between Loudness and Ten Other Continua. Perception and Psychophysics, 1, pp. 5-8, 1966
*/
