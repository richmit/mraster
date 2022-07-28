######################################################################################################################################################
######################################################################################################################################################
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

######################################################################################################################################################
# Proejct meta data

project(MRaster CXX)

set(PROJECT_VERSION_DATE  2022-07-28)
set(PROJECT_VERSION_ID    20.0.0a)
mark_as_advanced(PROJECT_VERSION_DATE PROJECT_VERSION_ID)

######################################################################################################################################################
# Here are the options we use to modify the build -- these options are passed to cmake like so: cmake -DO_OPENSSL=YES or -DO_OPENSSL=NO

OPTION(O_DOXYGEN "Include support for doxygen"         ON  )
OPTION(O_TIFF    "Include support for libTIFF"         ON  )
OPTION(O_OPENGL  "Include support for OpenGL & GLUT"   ON  )
OPTION(O_OPENMP  "Include support for OpenMP"          ON  )
OPTION(O_PNG     "Include support for libPNG"          OFF )
OPTION(O_IM      "Include support for ImageMagick"     OFF )
OPTION(O_MOVIE   "Include support making movies"       ON  )
OPTION(O_RAY     "Include support ray-tracing"         ON  )
OPTION(O_EIGEN   "Include support for eigen"           OFF )
OPTION(O_STATIC  "Build a static library"              OFF )
OPTION(O_BTEST   "Include support for boost.test"      ON  )

set(POVRAY_HINT "c:/Program Files/POV-Ray/v3.7/bin/")

######################################################################################################################################################

if(O_STATIC)
  add_library(mrr STATIC lib/colorData.cpp lib/hersheyFontData.cpp)
else()
  add_library(mrr SHARED lib/colorData.cpp lib/hersheyFontData.cpp)
endif()

######################################################################################################################################################
# Find tools & libraries used to build primary/secondary/tertiary targets

if(O_MOVIE)
  find_program(MAKEMOV avconv)
  find_program(MAKEMOV ffmpeg)
  if(${MAKEMOV} STREQUAL "MAKEMOV-NOTFOUND")
    message(WARNING "Could not find movie making command for MAKEMOV")
  endif()
endif()

if(O_RAY)
  find_program(POVRAY pvengine HINTS ${POVRAY_HINT})
  find_program(POVRAY povray)
  if(${POVRAY} STREQUAL "POVRAY-NOTFOUND")
    message(WARNING "Could not find POV-ray for POVRAY")
  endif()
endif()

if(O_DOXYGEN)
  find_package(Doxygen)
endif()

if(O_TIFF)
  find_package(TIFF)
endif()

if(O_OPENGL)
  find_package(OpenGL)
  find_package(GLUT)
endif()

if(O_OPENMP)
  find_package(OpenMP)
endif()

if(O_PNG)
  find_package(PNG)
endif()

if(O_IM)
  find_package(ImageMagick COMPONENTS MagickWand MagickCore)
endif()

if(O_EIGEN)
find_package (Eigen3 3.3 NO_MODULE)
endif()

if(O_BTEST)
find_package(Boost COMPONENTS unit_test_framework)
endif()

######################################################################################################################################################

set(TARGETS_REQ_NONE   "apollony" "apomorph" "bifurcation_diagram" "biomorph1" "biomorph2" "bmark" "chaos_game" "circles" "color_all"
                       "color_lut_ramp_misc" "cplxColor" "dlaSeed" "level_curves" "lorenz_fuz" "lorenz_multi" "mandelbrot_binary" "mandelbrot_bm_cplx"
                       "mandelbrot_bm_cplx_hyper" "mandelbrot_bm_real" "mandelbrot_cycles" "mandelbrot_distance" "mandelbrot_distance_old"
                       "mandelbrot_emboss" "mandelbrot_grayscale" "mandelbrot_orbits" "mandelbrot_potential" "mandelbrot_triangle" "newton_bm_cplx"
                       "newton_bm_real" "newton_half" "newton_max_mod" "newton_vs" "newton_z6" "peterdejong" "peterdejongM" "sic" "sic_search"
                       "sierpinski_triangle" "sprott2d" "testPoint" "test_draw_btriangle" "test_color" "test_draw_misc" "test_draw_primatives"
                       "tippets" "mandelbrot_bm_real_eqop" "test_float" "types")
set(TARGETS_REQ_MRRL   "color_lut_indexed" "color_lut_rainbows" "color_web_rectangle" "color_web_triangle" "test_draw_fonts" "test_draw_glyph"
                       "test_draw_strings" "color_interp_hsl_vs_rgb" "color_lut_ramp_cube")
set(TARGETS_REQ_OPENGL "glut_image")
set(TARGETS_REQ_TIFF   "brownianDiffusion" "dlaBrownian" "dlaDrift" "img_process" "test_interp_scale" "geomTfrm_LensDistortion" "geomTfrm_Arb" 
                       "geomTfrm_Rotate")
set(TARGETS_REQ_OPENMP "mandelbrot_bm_cplx_openmp")
set(TARGETS_REQ_BTEST  "utest_foo" "utest_color_types_ia64nGCC" "utest_color_methods")
set(TARGETS_REQ_PNG    )
set(TARGETS_REQ_IM     )

# Construct list of targets we can build
set(EXAMPLE_TARGETS ${TARGETS_REQ_NONE} ${TARGETS_REQ_MRRL} ${TARGETS_REQ_OPENGL} ${TARGETS_REQ_TIFF} ${TARGETS_REQ_OPENMP} ${TARGETS_REQ_BTEST} ${TARGETS_REQ_PNG} ${TARGETS_REQ_IM})

if(((NOT OpenGL_FOUND) OR (NOT GLUT_FOUND)) AND TARGETS_REQ_OPENGL)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_OPENGL})
  message(WARNING "OpenGL/GLUT example programs will NOT be built!.")
endif()
if((NOT OpenMP_FOUND) AND TARGETS_REQ_OPENMP)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_OPENMP})
  message(WARNING "OpenMP example programs will NOT be built!")
endif()
if((NOT TIFF_FOUND) AND TARGETS_REQ_TIFF)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_TIFF})
  message(WARNING "TIFF example programs will NOT be built!")
endif()
if((NOT Boost_FOUND) AND TARGETS_REQ_BTEST)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_BTEST})
  message(WARNING "Unit tests will NOT be built!")
endif()
if((NOT PNG_FOUND) AND TARGETS_REQ_PNG)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_PNG})
  message(WARNING "PNG example programs will NOT be built!")
endif()
if((NOT IM_FOUND) AND TARGETS_REQ_IM)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_IM})
  message(WARNING "IM example programs will NOT be built!")
endif()

list(REMOVE_DUPLICATES EXAMPLE_TARGETS)

# Add a target for each example we can build
foreach(CURTGT IN LISTS EXAMPLE_TARGETS)
  add_executable(${CURTGT} "examples/${CURTGT}.cpp")
  target_include_directories(${CURTGT} PRIVATE lib)
  target_compile_features(${CURTGT} PUBLIC cxx_std_20)
  target_include_directories(${CURTGT} PRIVATE ${CMAKE_BINARY_DIR})

  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${CURTGT} PUBLIC -Wstrict-overflow=0)
    target_compile_options(${CURTGT} PUBLIC -ffast-math)
    target_compile_options(${CURTGT} PUBLIC -Wall -Wconversion -Wno-unknown-pragmas -Wextra -Wno-deprecated-copy)
    target_compile_options(${CURTGT} PUBLIC -Ofast)
  elseif((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
    target_compile_options(${CURTGT} PUBLIC -Wstrict-overflow=0)
    target_compile_options(${CURTGT} PUBLIC -ffast-math)
    target_compile_options(${CURTGT} PUBLIC -Wall -Wconversion -Wno-unknown-pragmas -Wextra -Wno-sign-conversion)
    target_compile_options(${CURTGT} PUBLIC -O3)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    target_compile_options(${CURTGT} PUBLIC -Wall)
    target_compile_options(${CURTGT} PUBLIC -O3)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("Warning: MSVC support is currently experimental")
  endif()
endforeach(CURTGT)

# Add build requirements for examples using OpenGL
if(Boost_FOUND)
  foreach(CURTGT IN LISTS TARGETS_REQ_BTEST)
    target_link_libraries(${CURTGT} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  endforeach(CURTGT)
endif()

# Add link requirements for examples using the mrraster library (not just headers)
foreach(CURTGT IN LISTS TARGETS_REQ_MRRL)
  target_link_libraries(${CURTGT} mrr)
endforeach(CURTGT)

# Add build requirements for examples using OpenGL
if(OpenGL_FOUND AND GLUT_FOUND)
  foreach(CURTGT IN LISTS TARGETS_REQ_OPENGL)
    target_include_directories(${CURTGT} PRIVATE ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIR} )
    target_link_libraries(${CURTGT} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
  endforeach(CURTGT)
endif()

# Add builtd requirements for examples using OpenMP
if (OPENMP_FOUND)
  foreach(CURTGT IN LISTS TARGETS_REQ_OPENMP)
    target_compile_options(${CURTGT} PUBLIC ${OpenMP_CXX_FLAGS})
    target_include_directories(${CURTGT} PRIVATE ${OpenMP_INCLUDE_PATH})
    target_link_libraries(${CURTGT} ${OpenMP_CXX_LIBRARIES}) # ${PROJECT_LINK_LIBS}).
  endforeach(CURTGT)
endif()

# Add build requirements for examples using libTIFF
if(TIFF_FOUND)
  foreach(CURTGT IN LISTS TARGETS_REQ_TIFF)
    target_compile_definitions(${CURTGT} PUBLIC TIFF_FOUND=1)
    target_include_directories(${CURTGT} PRIVATE ${TIFF_INCLUDE_DIRS})
    target_link_libraries(${CURTGT} ${TIFF_LIBRARIES})
  endforeach(CURTGT)
endif()

# The circles target needs drawing mode support
target_compile_definitions(circles PUBLIC SUPPORT_DRAWING_MODE=1)

# Suppress GCC maybe-uninitialized warnings for level_curves
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(level_curves PRIVATE -Wno-maybe-uninitialized)
endif()

######################################################################################################################################################

add_custom_target(clean-images
  COMMAND  rm -f *.tga *.tif *.tiff *.mrw *.bin
  COMMENT "Cleaning Image files"
)

######################################################################################################################################################

# Add targets using povray

######################################################################################################################################################

# Add targets making movies

######################################################################################################################################################
# Generate an include file with various methdata about the build.

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.hpp.cmake ${CMAKE_BINARY_DIR}/config.hpp)

######################################################################################################################################################

# Add targets for documentation
if(Doxygen_FOUND)
  foreach(DOXINPUT IN ITEMS "lib" "examples")
    message("Info: Generateing doxygen target for ${DOXINPUT}")
    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/Doxyfile.cmake ${CMAKE_BINARY_DIR}/doc-${DOXINPUT}/Doxyfile)
    add_custom_target(doc-${DOXINPUT}
      COMMAND ${DOXYGEN_EXECUTABLE} > dox.out
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc-${DOXINPUT}
      COMMENT "Generating documentation with Doxygen"
      VERBATIM)
  endforeach(DOXINPUT)
else()
  message("Warning: Doxygen not found.  No documentation targets!")
endif()
