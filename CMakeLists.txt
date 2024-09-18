######################################################################################################################################################
######################################################################################################################################################
cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
set(OpenGL_GL_PREFERENCE "GLVND") # Alternative

######################################################################################################################################################
# Proejct meta data

project(MRaster
  VERSION 20.12.3.0
  DESCRIPTION "Image Processing Library"
  HOMEPAGE_URL "https://github.com/richmit/mraster/"
  LANGUAGES CXX)

set(MRASTER_VERSION_DATE  2024-08-20)
mark_as_advanced(MRASTER_VERSION_DATE)

######################################################################################################################################################
# Here are the options we use to modify the build -- these options are passed to cmake like so: cmake -DO_OPENSSL=YES or -DO_OPENSSL=NO

OPTION(O_DOXYGEN "Include support for doxygen"                   ON )
OPTION(O_TIFF    "Include support for libTIFF"                   ON )
OPTION(O_OPENGL  "Include support for OpenGL & GLUT"             ON )
OPTION(O_OPENMP  "Include support for OpenMP"                    ON )
OPTION(O_BTEST   "Include support for boost.test"                ON )
OPTION(O_SDL2    "Include support for SDL2"                      ON )
OPTION(O_128_INT "Include support for 128-bit ints if possible"  ON )

######################################################################################################################################################
# Find tools & libraries used to build primary/secondary/tertiary targets.  Set config include file variables for options.

if(O_DOXYGEN)
  set(MRASTER_OPT_DOXYGEN "1")
  find_package(Doxygen)
else()
  set(MRASTER_OPT_DOXYGEN "0")
endif()

if(O_TIFF)
  set(MRASTER_OPT_TIFF "1")
  find_package(TIFF)
else()
  set(MRASTER_OPT_TIFF "0")
endif()

if(O_OPENGL)
  set(MRASTER_OPT_OPENGL "1")
  find_package(OpenGL)
  find_package(GLUT)
else()
  set(MRASTER_OPT_OPENGL "0")
endif()

if(O_OPENMP)
  set(MRASTER_OPT_OPENMP "1")
  find_package(OpenMP)
else()
  set(MRASTER_OPT_OPENMP "0")
endif()

if(O_SDL2)
  set(MRASTER_OPT_SDL2 "1")
  find_package (SDL2)
else()
  set(MRASTER_OPT_SDL2 "0")
endif()

if(O_BTEST)
  set(MRASTER_OPT_BTEST "1")
  find_package(Boost COMPONENTS unit_test_framework)
else()
  set(MRASTER_OPT_BTEST "0")
endif()

IF(O_128_INT)
  set(MRASTER_OPT_128_INT "1")
else()
  set(MRASTER_OPT_128_INT "0")
endif()

mark_as_advanced(MRASTER_OPT_128_INT MRASTER_OPT_BTEST MRASTER_OPT_DOXYGEN  MRASTER_OPT_OPENGL MRASTER_OPT_OPENMP MRASTER_OPT_SDL2 MRASTER_OPT_TIFF)

######################################################################################################################################################
# Setup  config include files variables related to found requirements

if(Doxygen_FOUND)
  set(MRASTER_FOUND_DOXYGEN "1")
else()
  set(MRASTER_FOUND_DOXYGEN "0")
endif()

if(TIFF_FOUND)
  set(MRASTER_FOUND_TIFF "1")
else()
  set(MRASTER_FOUND_TIFF "0")
endif()

if(OpenGL_FOUND)
  set(MRASTER_FOUND_OPENGL "1")
else()
  set(MRASTER_FOUND_OPENGL "0")
endif()

if(GLUT_FOUND)
  set(MRASTER_FOUND_GLUT "1")
else()
  set(MRASTER_FOUND_GLUT "0")
endif()

if(OpenMP_FOUND)
  set(MRASTER_FOUND_OPENMP "1")
else()
  set(MRASTER_FOUND_OPENMP "0")
endif()

if(SDL2_FOUND)
  set(MRASTER_FOUND_SDL2 "1")
else()
  set(MRASTER_FOUND_SDL2 "0")
endif()

if(Boost_FOUND)
  set(MRASTER_FOUND_BTEST "1")
else()
  set(MRASTER_FOUND_BTEST "0")
endif()

mark_as_advanced(MRASTER_FOUND_DOXYGEN MRASTER_FOUND_TIFF MRASTER_FOUND_OPENGL MRASTER_FOUND_OPENMP MRASTER_FOUND_SDL2 MRASTER_FOUND_BTEST)

######################################################################################################################################################

set(TARGETS_REQ_NONE "BurningShip" "apollony" "apomorph" "bifurcation_diagram" "biomorph1" "biomorph2" "biomorphMorph" "bmark" "chaos_game" "circles"
                       "collatz" "color_all" "color_interp_hsl_vs_rgb" "color_lut_cubehelix" "color_lut_docs" "color_lut_indexed"
                       "color_lut_indexedC" "color_lut_poly" "color_lut_rainbows" "color_lut_ramp_cube" "color_lut_ramp_cubeC" "color_lut_ramp_misc"
                       "color_web_rectangle" "color_web_triangle" "convertRawToTIFF" "cplxColor" "dlaSeed" "heart2022" "invertedMandelbrot"
                       "julia" "juliaM" "juliaM2" "level_curves" "lorenz_fuz" "lorenz_multi" "mandelbrot_binary" 
                       "mandelbrot_biomorph" "mandelbrot_bm_cplx" "mandelbrot_bm_cplx_hyper" "mandelbrot_bm_real"
                       "mandelbrot_emboss" "mandelbrot_grayscale" "mandelbrot_orbits" "attracting_torus_shadow" 
                       "mandelbrot_potential" "mandelbrot_real_cfun" "mandelbrot_triangle" "multibrotMovie" "multibrotSnaps"
                       "peterdejong" "barrymartin" "tinkerbell" "tinkerbell_search"
                       "pickoverPopcorn" "sic" "sic_search" "sierpinski_triangle" "sprott2d" "test_draw_fonts" "test_images" "tippets" "tricorn"
                       "tricornMovie" "types" "butterfly")
set(TARGETS_REQ_OPENGL "glut_image")
set(TARGETS_REQ_TIFF   "brownianDiffusion" "displayImageSDL2" "dlaBrownian" "dlaDrift" "img_process" "test_interp_scale" "geomTfrm_LensDistortion"
                       "geomTfrm_Arb"  "geomTfrm_Rotate" "mandelbrot_precomp_p1")
set(TARGETS_USE_OPENMP "mandelbrot_bm_cplx_openmp" "mandelbrot_precomp" "mandelbrot_precomp_p1" "mandelbrot_count_movie"
                       "mandelbrot_distance" "mandelbrot_wave" "peterdejongM" "newton_orbits" "newton_simple" "newton_max_mod" "mandelbrot_pickover"
                       "mandelbrot_ltrap" "newton_max_back" "newton_min_angle" "mandelbrot_simple" 
                       "newton_half" "newton_vs" "newton_z6" "newton_modified" "newton_min_root" "newton_3updown" "newton_roter" "attracting_torus_shadowM"
                       "laguerre_3updown" "laguerre_simple")
set(TARGETS_REQ_BTEST  "utest_colorTpl_ia64nGCC" "utest_colorTpl" "utest_ramCanvasTpl" "utest_mjrmath")
set(TARGETS_REQ_SDL2   "displayImageSDL2")

# Construct list of targets we can build
set(EXAMPLE_TARGETS ${TARGETS_REQ_NONE} ${TARGETS_REQ_TIFF} ${TARGETS_USE_OPENMP} ${TARGETS_REQ_BTEST} ${TARGETS_REQ_OPENGL} ${TARGETS_REQ_SDL2})

if(((NOT OpenGL_FOUND) OR (NOT GLUT_FOUND)) AND TARGETS_REQ_OPENGL)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_OPENGL})
  message(WARNING "Example programs requiring OpenGL/GLUT will NOT be built!")
endif()
if((NOT OpenMP_FOUND) AND TARGETS_USE_OPENMP)
  message(WARNING "Example programs that can use OpenMP, but don't require it, will generally have longer runtimes!")
endif()
if((NOT TIFF_FOUND) AND TARGETS_REQ_TIFF)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_TIFF})
  message(WARNING "Example programs requiring TIFF will NOT be built!")
endif()
if((NOT Boost_FOUND) AND TARGETS_REQ_BTEST)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_BTEST})
  message(WARNING "Unit tests will NOT be built!")
endif()
if((NOT SDL2_FOUND) AND TARGETS_REQ_SDL2)
  list(REMOVE_ITEM EXAMPLE_TARGETS ${TARGETS_REQ_SDL2})
  message(WARNING "Example programs requiring SDL2 will NOT be built!")
endif()

list(REMOVE_DUPLICATES EXAMPLE_TARGETS)

if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "Intel"))
    message("Warning:")
    message("Warning: Clang & Intel ICC compilers currently have incomplete implimentations of P1907R1.")
    message("Warning: csPLY_tpl & csCubeHelix_tpl require P1907R1 (floating point template arguments).")
    message("Warning: Examples that can't be built: color_lut_poly.cpp, color_lut_docs.cpp, color_lut_cubehelix.cpp, heart2022.cpp")
    message("Warning:")
    list(REMOVE_ITEM EXAMPLE_TARGETS "color_lut_poly" "color_lut_docs" "color_lut_cubehelix" "heart2022")                            # missing floating point template parameters
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
    message("Warning: Examples that can't be built: color_lut_poly.cpp, color_lut_docs.cpp, color_lut_cubehelix.cpp, heart2022.cpp")
    message("Warning: Logical member functions tfrmOr, tfrmNor, tfrmAnd, tfrmNand, tfrmXor, tfrmNxor, ")
    message("Warning: tfrmNot, tfrmShiftL, & tfrmShiftR will not have floating point channel support! ")
    message("Warning:")
  endif()
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message("Warning:")
  message("Warning: MSVC support is currently experimental.")
  message("Warning: clrChanT of double is the same as float!")
  message("Warning:")
endif()

# Add a target for each example we can build
foreach(CURTGT IN LISTS EXAMPLE_TARGETS)
  add_executable(${CURTGT} EXCLUDE_FROM_ALL "examples/${CURTGT}.cpp")
  target_include_directories(${CURTGT} AFTER PRIVATE lib)
  target_compile_features(${CURTGT} PUBLIC cxx_std_20)
  target_include_directories(${CURTGT} BEFORE PRIVATE ${CMAKE_BINARY_DIR})

  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${CURTGT} PUBLIC -Wstrict-overflow=0)
    target_compile_options(${CURTGT} PUBLIC -ffast-math)
    target_compile_options(${CURTGT} PUBLIC -Wall -Wconversion -Wno-unknown-pragmas -Wextra -Wno-deprecated-copy)
    target_compile_options(${CURTGT} PUBLIC -Ofast)
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
  endif()

  # Add build requirements for examples using Boost Test
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
  list (FIND TARGETS_USE_OPENMP ${CURTGT} TMPR)
  if (OPENMP_FOUND AND (${TMPR} GREATER -1))
    target_compile_options(${CURTGT} PUBLIC ${OpenMP_CXX_FLAGS})
    target_include_directories(${CURTGT} PRIVATE ${OpenMP_INCLUDE_PATH})
    target_link_libraries(${CURTGT} ${OpenMP_CXX_LIBRARIES}) # ${PROJECT_LINK_LIBS}).
  endif()

  # Add build requirements for examples using libTIFF
  list (FIND TARGETS_REQ_TIFF ${CURTGT} TMPR)
  if(TIFF_FOUND AND (${TMPR} GREATER -1))
    target_compile_definitions(${CURTGT} PUBLIC MRASTER_FOUND_TIFF=1)
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

add_custom_target(examples
  DEPENDS ${EXAMPLE_TARGETS}
  COMMENT "Building Examples"
)

add_custom_target(clean-images
  COMMAND  rm -f *.tga *.tif *.tiff *.mrw *.bin
  COMMENT "Cleaning Image files"
)

if(EXISTS "c:/Users/richmit/Documents/WWW/site/SS/mraster/doc-lib/")
  add_custom_target(install-doc-lib
    DEPENDS doc-lib
    COMMAND  rsync -rlt --log-format=%f --stats --delete --delete-excluded --modify-window=2 doc-lib/ /c/Users/richmit/Documents/WWW/site/SS/mraster/doc-lib
    COMMENT "Put doc-lib data in web site directory"
  )
endif()

if(EXISTS "c:/Users/richmit/Documents/WWW/site/SS/mraster/doc-examples/")
  add_custom_target(install-doc-examples
    DEPENDS doc-examples
    COMMAND  rsync -rlt --log-format=%f --stats --delete --delete-excluded --modify-window=2 doc-examples/ /c/Users/richmit/Documents/WWW/site/SS/mraster/doc-examples
    COMMENT "Put doc-examples data in web site directory"
  )
endif()

######################################################################################################################################################
# Generate an include file with various methdata about the build.

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/mraster_config.hpp.cmake ${CMAKE_BINARY_DIR}/mraster_config.hpp)

######################################################################################################################################################
# Add targets for documentation

if(Doxygen_FOUND)
  foreach(DOXINPUT IN ITEMS "lib" "examples")
    message("Info: Generateing doxygen target for ${DOXINPUT}")
    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/Doxyfile.cmake ${CMAKE_BINARY_DIR}/doc-${DOXINPUT}/Doxyfile)
    add_custom_target(doc-${DOXINPUT}
      COMMAND ${DOXYGEN_EXECUTABLE} > dox.out
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc-${DOXINPUT}
      COMMENT "Generating ${DOXINPUT} documentation with Doxygen"
      VERBATIM)
  endforeach(DOXINPUT)
else()
  message("Warning: Doxygen not found.  No documentation targets!")
endif()

######################################################################################################################################################
# Create interface target for the entire project

set(MRASTER_INCLUDES "build/mraster_config.hpp"
                     "lib/MRcolor.hpp" 
                     "lib/MRcolorTpl.hpp"
                     "lib/hersheyFont.hpp"
                     "lib/mjrmath.hpp"
                     "lib/MRpoint2d.hpp"
                     "lib/ramCanvas.hpp"
                     "lib/ramCanvasTpl.hpp")
add_library(MRaster INTERFACE ${MRASTER_INCLUDES})
if(TIFF_FOUND)
  target_compile_definitions(MRaster INTERFACE MRASTER_FOUND_TIFF=1)
  target_include_directories(MRaster INTERFACE ${TIFF_INCLUDE_DIRS})
  target_link_libraries(MRaster INTERFACE ${TIFF_LIBRARIES})
endif()
target_include_directories(MRaster INTERFACE 
                           "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib>"
                           "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/build>"
                           "$<INSTALL_INTERFACE:include>")

######################################################################################################################################################
# Export the library interface cmake file

export(TARGETS MRaster FILE "${CMAKE_BINARY_DIR}/MRasterLib.cmake")

######################################################################################################################################################
# Create Package Files

include(CMakePackageConfigHelpers)

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/MRasterConfig.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/MRasterConfig.cmake"
                              INSTALL_DESTINATION $"{CMAKE_INSTALL_LIBDIR}/cmake/MRaster")

write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/MRasterConfigVersion.cmake"
                                 COMPATIBILITY AnyNewerVersion)

######################################################################################################################################################
# Install
#
# This configuration "installs" all the stuff required to build things with mraster into the export directory:
#  - Non-deprecated Header files
#  - cmake package
#  - cmake export for library

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/build/install")
include(GNUInstallDirs)
install(FILES ${MRASTER_INCLUDES} TYPE INCLUDE)
install(TARGETS MRaster EXPORT MRasterLib)

install(EXPORT MRasterLib
        FILE MRasterLib.cmake
        DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/MRaster")

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/MRasterConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/MRasterConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/MRaster")
