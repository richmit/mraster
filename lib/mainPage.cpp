// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
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
********************************************************************************************************************************************************.H.E.**/

/**
 @mainpage
 Introduction
 ============

 This library delivers flexible and easy access to a broad range of low level, high performance raster graphics techniques.

 The primary use case is direct image synthesis for mathematical visualization

   - Raster based fractals like the Mandelbrot set

   - strange attractor projections, incidence histograms, bifurcation plots, etc...

   - Real functions on R^2 (level curves, filled contours, scalar fields, etc...)

   - Complex functions (phase portraits)

   - Iterated system fractals like the Sierpinski gasket

   - Povray Maps (Bump, texture, and normal) and Height fields

 Secondary use cases include

   - Backend for my ray tracing tools (manifolds with non-linear optics in 4D euclidean space)

   - Optical distortion correction

   - Stenography

   - Image encryption

   - Image compression

   - Images with very high HDR and/or channel depth -- astrographs, satellite imagery, etc...

 Design goals:

   - Extreme portability (ISO C++ only, minimal external library requirements, etc...)

   - Ease of use

     My goal was to be able to hand this package to a student with minimal C++ experience, and have them be able to create a Mandelbrot image in an few
     minutes.  For the most part my students were very successful!

   - Adaptability to many use cases

     My goal is to enable people with existing code to use this library to create images without rearchtecting their code.  This is especially important
     for mathematisons and scientests who may not be C++ expertes.

     The idea is to make the classes adapt to the setting in which they are being used, and not to force programmers to adapt.  For example, colors may be set
     via naive types, numeric characters, hex strings, web color hex strings, name strings, enumerated corner names, symbolic characters, or floating point
     numbers.  As another exmple points for drawing functison be be provided as coordinate pairs, point objects, complex numbers, tuples, arrays, etc...

   - High performance

 History
 =======


 This library began in the mid 80's as an abstraction layer on top of Microsoft, Apple, and X11 GUI APIs.  It was written in C and made heavy use of macros to
 translate my "wrapper API" into the native API.  The primary goal was to draw a mathematical object on screen, and allow the user to interact with it.

 As I began to make use of supercomputers at far flung locations around the globe, I was faced with the new challenge of drawing pictures without the aid of a
 graphics device or underlying APIs.  In response I added a "RAM frame buffer" to this library.  Eventually OpenGL became my on-screen graphics API of choice, leaving
 this library to evolve toward exclusively supporting RAM frame buffers.

 Once the limitations of adapting to underlying GUI APIs was removed, I was free to provide better organization and capabilities for abstraction and extension
 within the library itself.  The natural answer to both was rewriting the entire thing in C++.

 Eventually I found myself moving beyond 32bit RGBA -- RAW camera images, astro-photographs from CCDs, microscope imaging devices, and digital film scanners producing
 16/32-bit greyscale and 48-bit RGB.  So I used templates to allow the ramCanvas to support such images, added quite a lot of image processing functionality,
 and broadened image file support using external libraries.  The code required quite a bit of low-level trickery in order to get the best performance from the
 C++ compilers of the day.

 Eventually the support burden associated with supporting a dozen external image I/O libraries became too much.  So I decided to trim that down to just
 libTIFF -- TIFF is both broadly supported and can represent most of the image types provided my mraster.  libTIFF is only required for reading images, so the
 library is still free of dependencies for most of the identified use cases.

 When C++20 became widely supported I decided it was time for a complete refactor.  Most of the low-level trickery used in the code to achieve high
 performance was no longer required because compilers were so much smarter.  In particular the ugly performance hack of overlaying a struct on the channel
 arrays became unnecessary.  With the removal of the structs, I was free to remove the names they imposed -- eliminating the confusing RGB'esq references.  I
 was also able to remove most of the manual loop unrolling!  In addition to simplifying performance critical code, C++ also provided a real opportunity to
 refactor the templates using concepts resulting in smaller, safer, simpler code.

 And that's how we got the mraster we have today.  

 Kool features
 =============

   - It has quite a bit of documentation generated with doxygen.  

   - Portable C++.

   - Good performance.

   - Write support for TGA and TIFF images with no dependency on external libraries.

     - TGA (24-bit and the non-standard 8/16/32-bit greyscale images used by PovRay).

     - TIFF (usually bit perfect representations)

   - Efficient techniques for primitive scanline conversion and clipping.

   - Simple, but powerful, color support including HSV, wavelength, and RGB color specifications.  Unique color schemes are supported including 256,
     765, and 1020 level grey maps.  I have also included six different RGB color ramps (768 levels for 24-bit truecolor).  In addition, a 65K
     greyscale map is supported for generating Povray height fields.

   - "moveTo/lineTo" and "absolute" techniques are supported.

   - Old school "pixel paint" techniques are supported (set, xor, and, etc....)

   - Conditional compilation can be used to remove "moveTo/lineTo" and "pixel paint" -- these features can impose a 2x-3x performance penality.

   - Every canvas has both an integer and real coordinate system.  The orientation of all axes is under user control.

   - The precision of floating point pixel coordinates is user selectable, as is the integer type used for pixel coordinate values.


 Notes on the Code
 =================

 The code for this library all lives within the namespace of 'mjr' -- my initials.  This should help to avoid namespace conflicts.

 At this time everything is mostly implemented in header files with only large, static data sets placed into libraries.  

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
   - mjrmath.hpp ....... Simple math stuff
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
           |       3 |      16 | RGB  |    48 | 48-bit color     | High quality digital camera sensors.            |
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
 no arguments.  Just with fewer coordinates.  Some primitives, like circles, require extra parameters to describe the primitive.  Such parameters right before
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
 supports all graphs via the cmpRGBcolorRamp method -- this method takes a simple list of edges to traverse.

 The Color Cube Rainbow
 ----------------------

 This is one of the most commonly seen color schemes in scientific visualization, and it is also one of the worst because it can be misleading when
 mapped to linear values.

 The color cube rainbow map is generated by the unique six segment (6 vertex) cycle in the face edge graph not involving white or black.  Also known
 as the "Color Cube Rainbow".

 This is color scheme is not suggested for general use; however, ignoring this advice is so popular that a special method provides named support for the
 color cube rainbow:

  - RYGCBMR -- setRGBcmpClrCubeRainbow()

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

  A popular trend is to use luminance based color schemes from the HSL color space.  This popularity is primarily due to a few very well received
  papers published in the early and mid 1990's following on the work of S. S. Stevens.  Some HSL schemes don't suffer from the perceptional
  non-linearity that some popular RGB schemes suffer from. What most people don't realize is that many of the most popular luminance based color
  schemes in the HSL color space are actually edge graphs in the RGB color cube!  It is also true that the most common "bad" color scheme in the RGB
  cube (the colorCubeRainbow), is an edge graph in the HSL hexcone!  In the end, the thing to remember is that both color spaces have both good and
  bad color schemes.  Of particular note, are the two segment trees from black to white in the RGB edge/diagonal graph -- they are the same as the two
  segment graphs in the edges of the HSL hexcone from black to white!

   - 0RW -- H=0   red edge of the HSL hexcone
   - 0YW -- H=60  yellow edge of the HSL hexcone
   - 0GW -- H=120 green edge of the HSL hexcone
   - 0CW -- H=180 cyan edge of the HSL hexcone
   - 0BW -- H=240 blue edge of the HSL hexcone
   - 0MW -- H=300 magenta edge of the HSL hexcone

 Hot Too Cold
 ------------

 A very common color map used to map data with ranges from cold up to hot is known as the "cold too hot ramp".  This ramp provides colors from blue, up
 through green, and ends in red. It suffers from the same defects as the color cube rainbow; however, its use is so common that special support is provided
 via a named method.

  - BCGYR -- setRGBcmpColdToHot()

 The traditional cold to hot ramp can be improved -- this is my personal opinion.  This new ramp still has the same problems the color cube rainbow has;
 however, it is more attractive.  This one moves from white (ice), up to water (blue), and then up to red (hot) via yellow.

  - WCBYR -- setRGBcmpIceToWaterToHot()

 Constant Intensity Cycles
 -------------------------

 Two cycles, with three edges each, exhibiting constant intensity for every color in the color scheme are genuinely useful.  They have the advantage that they
 always render a "bright" color.  The lower intensity version is best for projected media that don't do well with yellow.

  - CMY == setRGBcmpConstTwoRamp() -- intensity == 2
  - BRG == setRGBcmpConstOneRamp() -- intensity == 1

 One Segment Diverging Maps
 --------------------------

 One edge trees in the face diagonal graph with a nearly constant intensity of 2 along the entire edge are useful for "diverging" or "bipolar" color
 schemes.  By definition, such color schemes will never involve black or white.

 While rarely used, the following maps are useful and suggested.  None of them have the problems associated with the color cube rainbow.

  - YC  ==  setRGBcmpUpDownRampBr()
  - YM  ==  setRGBcmpUpDownRampBg()
  - MC  ==  setRGBcmpUpDownRampGr()
  - MY  ==  setRGBcmpUpDownRampGb()
  - CM  ==  setRGBcmpUpDownRampRg()
  - CY  ==  setRGBcmpUpDownRampRb()

 The naming convention for the methods is not obvious.  Take, for example, setRGBcmpUpDownRampBr.  This is so named because of the computational algorithm
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

 A popular trend is to use saturation based color schemes from the HSL color space -- see the earlier comments regarding luminance based color
 schemes.  Essentially, such color maps extend from the center of HSL space, (0.0, 0.5, 0), to one of the primary color vertexes --- which have the
 same colors as the vertexes of the RGB cube excluding black and white.  As luck would have it, such sequences are the same as extending linearly
 from the center of RGB space, (0.5, 0.5, 0.5), to one of the vertexes excluding black and white!  One can think of this as extending the edge graph
 of the RGB cube with an extra vertex at the center of the cube.

 So we add a vertex to the RGB color cube edge graph.  We place it at the center of the cube, and add edges between this new vertex and the existing
 corners of the cube.  We call this new vertex 'H' -- for "Half way between everything". Using this new vertex, we have the following saturation
 based color schemes:

  - HR -- setRGBcmpRampGrey2R()
  - HG -- setRGBcmpRampGrey2G()
  - HB -- setRGBcmpRampGrey2B()
  - HC -- setRGBcmpRampGrey2C()
  - HY -- setRGBcmpRampGrey2Y()
  - HM -- setRGBcmpRampGrey2M()

 The traversal from black to white -- through the center point -- is directly supported via a named method.  Note that cmpRGBcolorRamp supports this via
 a graph string of "0W".

  - 0HW -- setRGBcmpGreyRGB()

 The other diagonal traversals (diagonal meaning through the center of the cube) are essentially two of the HSL saturation based schemes placed back
 to back.  They can form effective divergent color schemes.  Black to white is technical one of them, but we have already covered that one.  Note
 that the cmpRGBcolorRamp function will support this class of schemes with a two element graph -- the first vertex and the last. The remaining three
 diagonal schemes are as follows:

  - CHR -- setRGBcmpDiagRampCR()
  - MHG -- setRGBcmpDiagRampMG()
  - YHB -- setRGBcmpDiagRampYB()

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
