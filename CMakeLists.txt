######################################################################################################################################################
######################################################################################################################################################
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

######################################################################################################################################################
# Proejct meta data

project(MRaster CXX)

set(PROJECT_VERSION_DATE  2022-08-20)
set(PROJECT_VERSION_ID    v20.8.1b)
mark_as_advanced(PROJECT_VERSION_DATE PROJECT_VERSION_ID)

######################################################################################################################################################
# Here are the options we use to modify the build -- these options are passed to cmake like so: cmake -DO_OPENSSL=YES or -DO_OPENSSL=NO

OPTION(O_DOXYGEN "Include support for doxygen"         ON  )
OPTION(O_TIFF    "Include support for libTIFF"         ON  )
OPTION(O_OPENGL  "Include support for OpenGL & GLUT"   ON  )
OPTION(O_OPENMP  "Include support for OpenMP"          ON  )
OPTION(O_MOVIE   "Include support making movies"       ON  )
OPTION(O_RAY     "Include support ray-tracing"         ON  )
OPTION(O_BTEST   "Include support for boost.test"      ON  )
OPTION(O_SDL2    "Include support for SDL2"            ON )

set(POVRAY_HINT "c:/Program Files/POV-Ray/v3.7/bin/")

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

if(O_SDL2)
find_package (SDL2)
endif()

if(O_BTEST)
find_package(Boost COMPONENTS unit_test_framework)
endif()

######################################################################################################################################################

set(TARGETS_REQ_NONE   "apollony" "apomorph" "bifurcation_diagram" "biomorph1" "biomorph2" "bmark" "chaos_game" "circles" "color_all"
                       "color_interp_hsl_vs_rgb" "color_lut_cubehelix" "color_lut_docs" "color_lut_indexed" "color_lut_indexedC" "color_lut_poly"
                       "color_lut_rainbows" "color_lut_ramp_cube" "color_lut_ramp_misc" "color_web_rectangle" "color_web_triangle" "cplxColor"
                       "dlaSeed" "heart2022" "level_curves" "lorenz_fuz" "lorenz_multi" "mandelbrot_binary" "mandelbrot_bm_cplx"
                       "mandelbrot_bm_cplx_hyper" "mandelbrot_bm_real" "mandelbrot_real_cfun" "mandelbrot_bm_real_eqop" "mandelbrot_cycles"
                       "mandelbrot_distance" "mandelbrot_distance_old" "mandelbrot_emboss" "mandelbrot_grayscale" "mandelbrot_orbits"
                       "mandelbrot_potential" "mandelbrot_triangle" "newton_bm_cplx" "newton_bm_real" "newton_half" "newton_max_mod" "newton_vs"
                       "newton_z6" "peterdejong" "peterdejongM" "sic" "sic_search" "sierpinski_triangle" "sprott2d" 
                       "test_draw_btriangle" "test_draw_fonts" "test_draw_glyph" "test_draw_misc" "test_draw_strings"
                       "tippets" "types" "color_lut_ramp_cubeC")
set(TARGETS_REQ_OPENGL "glut_image")
set(TARGETS_REQ_TIFF   "brownianDiffusion" "dlaBrownian" "dlaDrift" "img_process" "test_interp_scale" "geomTfrm_LensDistortion" "geomTfrm_Arb" 
                       "geomTfrm_Rotate" "displayImageSDL2")
set(TARGETS_REQ_OPENMP "mandelbrot_bm_cplx_openmp")
set(TARGETS_REQ_BTEST  "utest_colorTpl_ia64nGCC" "utest_colorTpl" "utest_ramCanvasTpl")
set(TARGETS_REQ_SDL2   "displayImageSDL2")

# Construct list of targets we can build
set(EXAMPLE_TARGETS ${TARGETS_REQ_NONE} ${TARGETS_REQ_TIFF} ${TARGETS_REQ_OPENMP} ${TARGETS_REQ_BTEST} ${TARGETS_REQ_OPENGL} ${TARGETS_REQ_SDL2})

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
if((NOT SDL2_FOUND) AND TARGETS_REQ_SDL2)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_SDL2})
  message(WARNING "SDL2 example programs will NOT be built!")
endif()

list(REMOVE_DUPLICATES EXAMPLE_TARGETS)

if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Intel"))
    message("Warning: Clang & Intel ICC compilers currently have incomplete implimentations of P1907R1.")
    message("Warning: csPLY_tpl & csCubeHelix_tpl require P1907R1 (floating point template arguments).")
    message("Warning: Examples that can't be built: color_lut_poly.cpp, color_lut_docs.cpp, color_lut_cubehelix.cpp, heart2022.cpp")
    list(REMOVE_ITEM EXAMPLE_TARGETS "color_lut_poly" "color_lut_docs" "color_lut_cubehelix" "heart2022")                            # missing floating point template parameters
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message("Warning: MSVC support is currently experimental")
endif()

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
    target_compile_options(${CURTGT} PUBLIC -DMISSING_P1907R1=1)                                                       # missing floating point template parameters
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    target_compile_options(${CURTGT} PUBLIC -Wall)
    target_compile_options(${CURTGT} PUBLIC -O3)
    target_compile_options(${CURTGT} PUBLIC -DMISSING_P1907R1=1)                                                       # missing floating point template parameters
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    #message("Warning: MSVC support is currently experimental")
  endif()

  # Add build requirements for examples using OpenGL
  list (FIND TARGETS_REQ_BTEST ${CURTGT} TMPR)
  if((Boost_FOUND) AND (${TMPR} GREATER -1))
    target_link_libraries(${CURTGT} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  endif()

  # Add build requirements for examples using OpenGL
  list (FIND TARGETS_REQ_OPENGL ${CURTGT} TMPR)
  if(OpenGL_FOUND AND GLUT_FOUND AND (${TMPR} GREATER -1))
    if((CMAKE_CXX_PLATFORM_ID STREQUAL "MinGW") AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
      target_compile_options(${CURTGT} PUBLIC "-mwindows")
      target_link_options(${CURTGT} PUBLIC "-Wl,-subsystem,windows")
    endif()
    target_include_directories(${CURTGT} PRIVATE ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIR} )
    target_link_libraries(${CURTGT} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
  endif()

  # Add builtd requirements for examples using OpenMP
  list (FIND TARGETS_REQ_OPENMP ${CURTGT} TMPR)
  if (OPENMP_FOUND AND (${TMPR} GREATER -1))
    target_compile_options(${CURTGT} PUBLIC ${OpenMP_CXX_FLAGS})
    target_include_directories(${CURTGT} PRIVATE ${OpenMP_INCLUDE_PATH})
    target_link_libraries(${CURTGT} ${OpenMP_CXX_LIBRARIES}) # ${PROJECT_LINK_LIBS}).
  endif()

  # Add build requirements for examples using libTIFF
  list (FIND TARGETS_REQ_TIFF ${CURTGT} TMPR)
  if(TIFF_FOUND AND (${TMPR} GREATER -1))
    target_compile_definitions(${CURTGT} PUBLIC TIFF_FOUND=1)
    target_include_directories(${CURTGT} PRIVATE ${TIFF_INCLUDE_DIRS})
    target_link_libraries(${CURTGT} ${TIFF_LIBRARIES})
  endif()

  # Add build requirements for examples using SDL2
  list (FIND TARGETS_REQ_SDL2 ${CURTGT} TMPR)
  if(SDL2_FOUND AND (${TMPR} GREATER -1))
    if((CMAKE_CXX_PLATFORM_ID STREQUAL "MinGW") AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
      target_compile_options(${CURTGT} PUBLIC "-mwindows")
      target_link_options(${CURTGT} PUBLIC "-Wl,-subsystem,windows")
    endif()
    target_compile_definitions(${CURTGT} PUBLIC SDL2_FOUND=1)
    target_include_directories(${CURTGT} PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${CURTGT} ${SDL2_LIBRARIES})
  endif()
endforeach(CURTGT)

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
