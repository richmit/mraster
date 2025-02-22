######################################################################################################################################################
######################################################################################################################################################
cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

set(OpenGL_GL_PREFERENCE "GLVND") # Alternative
set(CMAKE_CXX_EXTENSIONS ON)

######################################################################################################################################################
# Proejct meta data

project(MRaster
  VERSION 22.0.0.0
  DESCRIPTION "Image Processing Library"
  HOMEPAGE_URL "https://github.com/richmit/mraster/"
  LANGUAGES CXX)

set(MRASTER_VERSION_DATE  2025-01-25)
mark_as_advanced(MRASTER_VERSION_DATE)

######################################################################################################################################################
# Include ctest
include(CTest)

######################################################################################################################################################
# Here are the options we use to modify the build -- these options are passed to cmake like so: cmake -DO_OPENSSL=YES or -DO_OPENSSL=NO

OPTION(O_DOXYGEN     "Doxygen support (documentation)"         ON  )
OPTION(O_GTEST       "Include support for Google Test"         ON  )
OPTION(O_TIFF        "libTIFF support (Advanced TIFF writer)"  ON  )
OPTION(O_OPENGL      "OpenGL & GLUT support"                   ON  )
OPTION(O_OPENMP      "OpenMP support"                          ON  )
OPTION(O_SDL2        "SDL2 support"                            ON  )
OPTION(O_128_INT     "128-bit integer support"                 ON  )
OPTION(OWNLOAD_GTEST "Download latest Google Test from Github" OFF )

######################################################################################################################################################
# Find tools & libraries used to build primary/secondary/tertiary targets.  Set config include file variables for options.

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

# CODE GEN: ~/MJR/core/codeBits/bin/src2orgListing ~/core/codeBits/cmake-template/include_gtest.cmake
if(O_GTEST)
  if(OWNLOAD_GTEST)
    message(STATUS "GTest: Downloading")
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/heads/main.zip
      DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    set(GTest_FOUND "YES") # If FetchContent_MakeAvailable didn't work, then cmake will error out.
  else()
    message(STATUS "GTest: Not downloading GTest")
    find_package(GTest)
  endif()
else()
  if(OWNLOAD_GTEST)
    message(FATAL_ERROR "-DO_GTEST must be YES if -DOWNLOAD_GTEST is YES!")
  endif()
endif()

# CODE GEN: ~/MJR/core/codeBits/bin/src2orgListing ../MRMathCPP/IncludeMRMathCPPLib.cmake 
find_file(MRMathCPP_PATH "MRMathCPPLib.cmake" PATHS "MRMathCPP/build"  "../MRMathCPP/build")
if(NOT MRMathCPP_PATH STREQUAL "MRMathCPP_PATH-NOTFOUND")
  message(STATUS "Found MRMathCPP: ${MRMathCPP_PATH}")
  include("${MRMathCPP_PATH}")
else()
  message(FATAL_ERROR " MRMathCPP Search Failed!\n"
                      "     The MRMathCPP repository must be located in the same directory as this repository,\n"
                      "     and must be configured with a build directory named 'build' at the root of the \n"
                      "     MRMathCPP repository.  That is to say, do the following in the same directory \n"
                      "     where you cloned this repository: \n"
                      "        git clone 'https://github.com/richmit/MRMathCPP.git'\n"
                      "        cd MRMathCPP/build                                  \n"
                      "        cmake ..                                            \n"
                      "        cd ../..                                            \n"
                      "     Then return to this repository, and try to configure it again.\n")
endif()
get_target_property(MRMathCPP_INCLUDE MRMathCPP INTERFACE_INCLUDE_DIRECTORIES)

######################################################################################################################################################
# Create interface target for the entire project

set(MRASTER_INCLUDES "lib/MRcolor.hpp" 
                     "lib/MRcolorTpl.hpp"
                     "lib/hersheyFont.hpp"
                     "lib/MRpoint2d.hpp"
                     "lib/ramCanvas.hpp"
                     "lib/ramCanvasPixelFilters.hpp"
                     "lib/ramCanvasTpl.hpp")
add_library(MRaster INTERFACE ${MRASTER_INCLUDES})
target_include_directories(MRaster INTERFACE "${PROJECT_SOURCE_DIR}/lib")
if(O_128_INT)
  target_compile_definitions(MRaster INTERFACE DMRASTER_OPT_128_INT=1)
endif()
target_include_directories(MRaster INTERFACE ${MRMathCPP_INCLUDE})
if(TIFF_FOUND)
  target_compile_definitions(MRaster INTERFACE MRASTER_FOUND_TIFF=1)
  target_include_directories(MRaster INTERFACE ${TIFF_INCLUDE_DIRS})
  target_link_libraries(MRaster INTERFACE ${TIFF_LIBRARIES})
endif()

######################################################################################################################################################
# Export the library interface cmake file

export(TARGETS MRaster FILE "${CMAKE_BINARY_DIR}/MRasterLib.cmake")

######################################################################################################################################################

set(TARGETS_REQ_NONE   "BurningShip" "apollony" "apomorph" "bifurcation_diagram" "biomorph1" "biomorph2" "biomorphMorph" "bmark" "chaos_game"
                       "circles" "collatz" "color_all" "color_interp_hsl_vs_rgb" "color_lut_cubehelix" "color_lut_docs" "color_lut_indexed"
                       "color_lut_indexedC" "color_lut_poly" "color_lut_rainbows" "color_lut_ramp_cube" "color_lut_ramp_cubeC" "color_lut_ramp_misc"
                       "color_web_rectangle" "color_web_triangle" "convertRawToTIFF" "cplxColor" "dlaSeed" "heart2022" "heart2025" "invertedMandelbrot" "julia"
                       "juliaM" "juliaM2" "level_curves" "lorenz_fuz" "lorenz_multi" "mandelbrot_binary" "mandelbrot_biomorph" "mandelbrot_bm_cplx"
                       "mandelbrot_bm_cplx_hyper" "mandelbrot_bm_real" "mandelbrot_emboss" "mandelbrot_grayscale" "mandelbrot_orbits"
                       "attracting_torus_shadow" "mandelbrot_potential" "mandelbrot_real_cfun" "mandelbrot_triangle" "multibrotMovie"
                       "multibrotSnaps" "peterdejong" "barrymartin" "tinkerbell" "tinkerbell_search" "pickoverPopcorn" "sic" "sic_search"
                       "sierpinski_triangle" "sprott2d" "test_draw_fonts" "test_images" "tippets" "tricorn" "tricornMovie" "types" "butterfly"
                       "LevyCurve" "test_color_con" "demo_corners") 
set(TARGETS_REQ_OPENGL "glut_image")
set(TARGETS_REQ_TIFF   "brownianDiffusion" "displayImageSDL2" "dlaBrownian" "dlaDrift" "img_process" "test_interp_scale" "geomTfrm_LensDistortion"
                       "geomTfrm_Arb"  "geomTfrm_Rotate" "mandelbrot_precomp_p1")
set(TARGETS_USE_OPENMP "mandelbrot_bm_cplx_openmp" "mandelbrot_precomp" "mandelbrot_precomp_p1" "mandelbrot_count_movie" "mandelbrot_distance"
                       "mandelbrot_wave" "peterdejongM" "newton_orbits" "newton_simple" "newton_max_mod" "mandelbrot_pickover" "mandelbrot_ltrap"
                       "newton_max_back" "newton_min_angle" "mandelbrot_simple" "newton_min_angle_starfish" "newton_half" "newton_vs" "newton_z6"
                       "newton_modified" "newton_min_root" "newton_3updown" "newton_roter" "attracting_torus_shadowM" "laguerre_3updown"
                       "laguerre_simple" "kalisetJ" "kalisetM1" "kalisetM2" "phoenix" "phoenixI" "phoenixD" "phoenixM" "phoenixM2" "doublePendulum"
                       "doublePendulumM" "wakOrb01" "wakOrb02" "wakOrb03" "brusselator" "heartFrac" "duck" "mandelbrot_meanOrbit" "feather" 
                       "simone_attractor" "lorenz_mM" "peterdejongEAAO")
set(TARGETS_REQ_GTEST  "all_gtests"
                       "c_set_chan_dbl" "c_set_chan_byte" "c_set_chan_gen" "c_set_chan_const" "c_set_chan_hex" "c_set_rgba_pack" "c_set_rgb_tga"
                       "c_set_rgb_wavelengthCM" "c_set_rgb_wavelengthLA" "c_set_cs_csFPcircular12" "c_set_cs_csCBSpectral" "c_set_cs_csBin"
                       "c_set_cs_csHSLhX" "c_set_cs_csPLY" "c_set_cs_csCColdeRainbow" "c_comp_distDeltaE1976" "c_set_rgb_constant" "c_tfrm_logic"
                       "c_tfrm_arith" "c_comp_distX" "c_set_cs_csCubeHelix" "c_tfrm_misc" "c_tfrm_websafe" "c_tfrm_PowPow" "c_bool_isBlack"
                       "c_bool_isEqual" "c_comp_luminance" "c_set_rgb_unitHSx" "c_bool_isClose" "c_set_rgb_ColorSpace" "c_tfrm_GryLevScl"
                       "c_comp_dotProd" "c_comp_MinMax" "c_comp_linearInterpolate" "c_comp_wMean" "c_comp_rgb2colorSpace" "c_comp_bestChan"
                       "c_constructor" "c_int128_test" "r_draw_circles" "r_draw_point" "r_draw_primatives" "r_draw_lines" "r_draw_rectangles"
                       "r_draw_rectangles_filled" "r_save_file" "r_draw_triangles" "r_draw_triangles_filled" "r_tfrm_geom" "r_adjoin" "r_p_scale"
                       "r_draw_string" "r_draw_glyph")
set(TARGETS_REQ_SDL2   "displayImageSDL2")

# Construct list of targets we can build
set(COMBINED_TARGETS ${TARGETS_REQ_NONE} ${TARGETS_REQ_TIFF} ${TARGETS_USE_OPENMP} ${TARGETS_REQ_GTEST} ${TARGETS_REQ_OPENGL} ${TARGETS_REQ_SDL2})

if(((NOT OpenGL_FOUND) OR (NOT GLUT_FOUND)) AND TARGETS_REQ_OPENGL)
  list(REMOVE_ITEM COMBINED_TARGETS ${TARGETS_REQ_OPENGL})
  message(WARNING "Example programs requiring OpenGL/GLUT will NOT be built!")
endif()
if((NOT OpenMP_FOUND) AND TARGETS_USE_OPENMP)
  message(WARNING "Example programs that can use OpenMP, but don't require it, will generally have longer runtimes!")
endif()
if((NOT TIFF_FOUND) AND TARGETS_REQ_TIFF)
  list(REMOVE_ITEM COMBINED_TARGETS ${TARGETS_REQ_TIFF})
  message(WARNING "Example programs requiring TIFF will NOT be built!")
endif()
if((NOT GTest_FOUND) AND TARGETS_REQ_GTEST)
  list(REMOVE_ITEM COMBINED_TARGETS ${TARGETS_REQ_GTEST})
  message(WARNING "Unit tests will NOT be built!")
endif()
if((NOT SDL2_FOUND) AND TARGETS_REQ_SDL2)
  list(REMOVE_ITEM COMBINED_TARGETS ${TARGETS_REQ_SDL2})
  message(WARNING "Example programs requiring SDL2 will NOT be built!")
endif()

list(REMOVE_DUPLICATES COMBINED_TARGETS)

if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Intel"))
    message("Warning:")
    message("Warning: Clang & Intel compilers currently have incomplete implimentations of P1907R1.")
    message("Warning: csPLY_tpl & csCubeHelix_tpl require P1907R1 (floating point template arguments).")
    message("Warning: Examples that can't be built: color_lut_poly.cpp, color_lut_docs.cpp, color_lut_cubehelix.cpp, heart2022.cpp")
    message("Warning:")
    list(REMOVE_ITEM COMBINED_TARGETS "color_lut_poly" "color_lut_docs" "color_lut_cubehelix" "heart2022")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    message("Warning:")
    message("Warning: The Apple Clang compiler has an incomplete implimentation of p0476r2 (bit_cast).")
    message("Warning: Logical member functions tfrmOr, tfrmNor, tfrmAnd, tfrmNand, tfrmXor, tfrmNxor, ")
    message("Warning: tfrmNot, tfrmShiftL, & tfrmShiftR will not have floating point channel support! ")
    message("Warning:")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "11.0.0")
    message("Warning:")
    message("Warning: Older GCC verions don't support P0476R2 or P1907R1.")
    message("Warning: csPLY_tpl & csCubeHelix_tpl require P1907R1 (floating point template arguments).")
    message("Warning: Examples that can't be built: color_lut_poly, color_lut_docs, color_lut_cubehelix, heart2022")
    message("Warning: Logical member functions tfrmOr, tfrmNor, tfrmAnd, tfrmNand, tfrmXor, tfrmNxor, ")
    message("Warning: tfrmNot, tfrmShiftL, & tfrmShiftR will not have floating point channel support! ")
    message("Warning:")
    list(REMOVE_ITEM COMBINED_TARGETS "color_lut_poly" "color_lut_docs" "color_lut_cubehelix" "heart2022")
  endif()
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message("Warning:")
  message("Warning: If running cmake from MSYS2, make sure to specifically direct CMake to use")
  message("Warning: MSVC compatible libraries only.  For example, trying to use the MSYS2 versions")
  message("Warning: of libTIFF or GTest will not work with MSVC.  If you don't have compatible ")
  message("Warning: versions, then simply disable the features using command line options like")
  message("Warning: -DO_TIFF=NO and -DO_GTEST=NO.  Note that GTest may also be downloaded with")
  message("Warning: the -DOWNLOAD_GMAKE=YES option.")
  message("Warning:")
  message("Warning: Use 'Release' builds with MSVC as 'Debug' builds produce painfully slow binaries.")
  message("Warning:")
endif()

# Add a target for each example we can build
foreach(CURTGT IN LISTS COMBINED_TARGETS)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples/${CURTGT}.cpp")
    add_executable(${CURTGT} EXCLUDE_FROM_ALL "examples/${CURTGT}.cpp")
    list(APPEND TARGETS_EXAMPLES ${CURTGT})
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ftests/${CURTGT}.cpp")
    add_executable(${CURTGT} EXCLUDE_FROM_ALL "ftests/${CURTGT}.cpp")
    list(APPEND TARGETS_FTEST ${CURTGT})
  elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/utests/${CURTGT}.cpp")
    if(NOT GTest_FOUND)
      message(NOTICE "Target ${CURTGT} will not be built (no GTest support)")
      continue()
    endif()
    add_executable(${CURTGT} EXCLUDE_FROM_ALL "utests/${CURTGT}.cpp")
    if(NOT CURTGT STREQUAL "all_gtests")
      list(APPEND TARGETS_UTEST ${CURTGT})
    endif()
  else()
    message("Warning: Unable to find source for target ${CURTGT}!")
    continue()
  endif()

  target_compile_features(${CURTGT} PUBLIC cxx_std_23)

  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${CURTGT} PUBLIC -Wstrict-overflow=0)
    target_compile_options(${CURTGT} PUBLIC -ffast-math)
    target_compile_options(${CURTGT} PUBLIC -Wall -Wconversion -Wno-unknown-pragmas -Wextra -Wno-deprecated-copy)
    target_compile_options(${CURTGT} PUBLIC -Ofast)
    #target_compile_options(${CURTGT} PUBLIC -march=native)
    if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "11.0.0")
      target_compile_options(${CURTGT} PUBLIC -DMISSING_P0476R2=1)                                                     # missing bit_cast template parameters
      target_compile_options(${CURTGT} PUBLIC -DMISSING_P1907R1=1)                                                       # missing floating point template parameters
    endif()
  elseif((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
    target_compile_options(${CURTGT} PUBLIC -Wstrict-overflow=0)
    target_compile_options(${CURTGT} PUBLIC -ffast-math)
    target_compile_options(${CURTGT} PUBLIC -Wall -Wconversion -Wno-unknown-pragmas -Wextra -Wno-sign-conversion)
    target_compile_options(${CURTGT} PUBLIC -O3)
    target_compile_options(${CURTGT} PUBLIC -DMISSING_P1907R1=1)                                                       # missing floating point template parameters
    if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
      target_compile_options(${CURTGT} PUBLIC -DMISSING_P0476R2=1)                                                     # missing bit_cast template parameters
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    target_compile_options(${CURTGT} PUBLIC -Wall)
    target_compile_options(${CURTGT} PUBLIC -O3)
    target_compile_options(${CURTGT} PUBLIC -DMISSING_P1907R1=1)                                                       # missing floating point template parameters
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    #message("Warning: MSVC support is currently experimental")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "NVHPC")
    target_compile_options(${CURTGT} PUBLIC -O3)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
    target_compile_options(${CURTGT} PUBLIC -O3)
  else()
    message(WARNING " Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
  endif()

  target_link_libraries(${CURTGT} PRIVATE MRaster)

  # Add build requirements for unit tests
  list (FIND TARGETS_REQ_GTEST ${CURTGT} TMPR)
  if((GTest_FOUND) AND (${TMPR} GREATER -1))
    target_link_libraries(${CURTGT} PRIVATE GTest::gtest_main)
    if(NOT CURTGT STREQUAL "all_gtests")
      add_test(NAME "${CURTGT}" COMMAND "${CURTGT}")
    endif()
  endif()

  # Add build requirements for examples using OpenGL
  list (FIND TARGETS_REQ_OPENGL ${CURTGT} TMPR)
  if(OpenGL_FOUND AND GLUT_FOUND AND (${TMPR} GREATER -1))
    if((CMAKE_CXX_PLATFORM_ID STREQUAL "MinGW") AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
      target_compile_options(${CURTGT} PUBLIC "-mwindows")
      target_link_options(${CURTGT} PUBLIC "-Wl,-subsystem,windows")
    endif()
    target_include_directories(${CURTGT} PRIVATE ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIR} )
    target_link_libraries(${CURTGT} PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
  endif()

  # Add builtd requirements for examples using OpenMP
  list (FIND TARGETS_USE_OPENMP ${CURTGT} TMPR)
  if (OPENMP_FOUND AND (${TMPR} GREATER -1))
    target_compile_options(${CURTGT} PUBLIC ${OpenMP_CXX_FLAGS})
    target_include_directories(${CURTGT} PRIVATE ${OpenMP_INCLUDE_PATH})
    target_link_libraries(${CURTGT} PRIVATE ${OpenMP_CXX_LIBRARIES}) # ${PROJECT_LINK_LIBS}).
  endif()

  # Add build requirements for examples using libTIFF
  list (FIND TARGETS_REQ_TIFF ${CURTGT} TMPR)
  if(TIFF_FOUND AND (${TMPR} GREATER -1))
    target_compile_definitions(${CURTGT} PUBLIC MRASTER_FOUND_TIFF=1)
    target_include_directories(${CURTGT} PRIVATE ${TIFF_INCLUDE_DIRS})
    target_link_libraries(${CURTGT} PRIVATE ${TIFF_LIBRARIES})
  endif()

  # Add build requirements for examples using SDL2
  list (FIND TARGETS_REQ_SDL2 ${CURTGT} TMPR)
  if(SDL2_FOUND AND (${TMPR} GREATER -1))
    if((CMAKE_CXX_PLATFORM_ID STREQUAL "MinGW") AND (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
      target_compile_options(${CURTGT} PUBLIC "-mwindows")
      target_link_options(${CURTGT} PUBLIC "-Wl,-subsystem,windows")
    endif()
    target_include_directories(${CURTGT} PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${CURTGT} PRIVATE ${SDL2_LIBRARIES})
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

if(TARGETS_EXAMPLES)
  add_custom_target(examples
    DEPENDS ${TARGETS_EXAMPLES}
    COMMENT "Building Examples"
  )
endif()

if(TARGETS_UTEST)
  add_custom_target(utests
    DEPENDS ${TARGETS_UTEST}
    COMMENT "Building Unit Tests"
  )
  add_custom_target(run-utests
    DEPENDS ${TARGETS_UTEST}
    COMMENT "Running Unit Tests"
    COMMAND cmake --build . -t test
  )
endif()

# CODE GEN: ~/MJR/core/codeBits/bin/src2orgListing ~/core/codeBits/cmake-template/include_doxygen-targets.cmake | sed 's/PROJECT_NAME/mraster/g; s/SRCP/"lib" "examples"/'
if(Doxygen_FOUND)
  foreach(DOXINPUT IN ITEMS "lib" "examples")
    message(STATUS "Generateing doxygen generation target for ${DOXINPUT}")
    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/Doxyfile.cmake ${CMAKE_BINARY_DIR}/doc-${DOXINPUT}/Doxyfile)
    set(DOXSRCF "doc-${DOXINPUT}")
    file(GLOB TMP LIST_DIRECTORIES false "${CMAKE_SOURCE_DIR}/${DOXINPUT}/[a-zA-Z0-9]*.?pp")
    list(APPEND DOXSRCF ${TMP})
    file(GLOB TMP LIST_DIRECTORIES false "${CMAKE_SOURCE_DIR}/${DOXINPUT}/[a-zA-Z0-9]*.f90")
    list(APPEND DOXSRCF ${TMP})
    add_custom_target(doc-${DOXINPUT}
      DEPENDS ${DOXSRCF}
      COMMAND ${DOXYGEN_EXECUTABLE} > dox.out
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc-${DOXINPUT}
      COMMENT "Generating ${DOXINPUT} documentation with Doxygen"
      VERBATIM)
    if(EXISTS "c:/Users/richmit/MJR/WWW/site/SS/mraster/doc-${DOXINPUT}/")
      message(STATUS "Generateing doxygen publish target for ${DOXINPUT}")
      add_custom_target("install-doc-${DOXINPUT}"
        DEPENDS ${DOXSRCF}
        COMMAND  rsync -rlt --log-format=%f --stats --delete --delete-excluded --modify-window=2 "doc-${DOXINPUT}/" "/c/Users/richmit/MJR/WWW/site/SS/mraster/doc-${DOXINPUT}"
        COMMENT "Put ${DOXINPUT} data in web site directory")
    endif()
  endforeach(DOXINPUT)
else()
  message(STATUS "Warning: Doxygen not found.  No documentation targets!")
endif()
