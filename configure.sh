#!/usr/bin/env -S bash
# -*- Mode:Shell-script; Coding:us-ascii-unix; fill-column:158 -*-
#########################################################################################################################################################.H.S.##
##
# @file      configure.sh
# @author    Mitch Richling http://www.mitchr.me/
# @date      2025-01-30
# @brief     Just a little helper for people accustomed to GNU autotools.@EOL
# @std       bash
# @copyright 
#  @parblock
#  Copyright (c) 2024-2025, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.
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
#########################################################################################################################################################.H.E.##

#---------------------------------------------------------------------------------------------------------------------------------------------------------------
if [ ! -e CMakeLists.txt ]; then
  echo "ERROR(configure.sh): Missing CMakeLists.txt file!"
  exit
fi

#---------------------------------------------------------------------------------------------------------------------------------------------------------------
if [ -z "$CONFIGURE_DEBUG" ]; then
  CONFIGURE_DEBUG='N'
fi

if [ -z "$CONFIGURE_DOIT" ]; then
  CONFIGURE_DOIT='Y'
fi

#---------------------------------------------------------------------------------------------------------------------------------------------------------------
if [[ "${@}" == *'-h'* ]]; then
  cat <<EOF

  Run this script from the project root directory with the CMakeLists.txt.

  A wrapper to quickly run cmake with my preferred arguments.  This script
  understands a few things about my development environment and some conventions
  I follow when using CMake.  For example it knows about the compilers and
  platforms I normally use, and how I specify optional dependencies in
  CMakeLists.txt.

  Use: configure.sh [configure options] [cmake arguments]

    Environment Variables:
     - CONFIGURE_DEBUG ... Set to 'Y' to print debugging output
     - CONFIGURE_DOIT .... Set to 'N' to suppress running 'rm' and/or 'cmake'

    Explicitly Ignored Environment Variables:
     - CMAKE_CXX_COMPILER
     - CMAKE_EXPORT_COMPILE_COMMANDS
     - CMAKE_GENERATOR
     - CMAKE_BUILD_TYPE

    Configure Options:
     - -h Print this help message
     - -C Delete the build directory before running cmake
     - -F Delete the build directory before running cmake without conformation  
          See also: the CMake option --fresh

    Common Cmake Arguments:
     - Target -- leave it off to get the default
       - -G 'MSYS Makefiles'        <-- Default when MSYS2 is detected
       - -G 'Visual Studio 17 2022'
       - -G 'Unix Makefiles'        <-- Default when MSYS2 is not detected
       - -G Ninja
     - Compiler -- leave it off to get the default
       - -DCMAKE_CXX_COMPILER=clang++
       - -DCMAKE_CXX_COMPILER=g++    <-- 'MSYS Makefiles' default
       - -DCMAKE_CXX_COMPILER=g++-## <-- 'Unix Makefiles' default if versioned
                                         g++-[0-9][0-9] file is in /usr/bin/.
                                         The ## is replaced with highest numbered 
                                         version found.
       - -DCMAKE_CXX_COMPILER=g++    <-- 'Unix Makefiles' default when a
                                         versioned g++ is not found.
       - -DCMAKE_CXX_COMPILER=cl.exe <-- Default for 'Visual Studio 17 2022'
       - -DCMAKE_CXX_COMPILER=nvc++  <-- NVIDIA HPC C++ Compiler
       - -DCMAKE_CXX_COMPILER=icpx   <-- Intel oneAPI DPC++/C++ Compiler
     - Unless overridden on the command line, the following options are set:
       - -DCMAKE_EXPORT_COMPILE_COMMANDS=1
       - -CMAKE_BUILD_TYPE=Release
       - -B build
EOF

  if grep -Eq '^OPTION\([A-Z0-9_]+' CMakeLists.txt; then
    echo '     - Optional features'
    sed -En 's/^[#O]PTION\(([A-Z0-9_]+)( +)"([^"]+)".*(ON|OFF).*$/       - -D\1=[ON|OFF] \2 \3 (Default: \4)/p' < CMakeLists.txt
  fi

  OPH='     - Search Paths For MR* Components'
  for opath in 'MRaster' 'MRPTree' 'MRMathCPP'; do
    if grep -q "${opath}_PATH" CMakeLists.txt; then
      if [ -n "$OPH" ]; then
        echo "$OPH"
      fi
      OPH=''
      echo "       - -D${opath}_PATH=<PATH>"
    fi
  done

  exit
fi

if [ "$1" == "-C" ]; then
  shift
  CLEAN_DIR='YES'
  CLEAN_ASK='YES'
elif [ "$1" == "-F" ]; then
  shift
  CLEAN_DIR='YES'
  CLEAN_ASK='NO'
else
  CLEAN_DIR='NO'
  CLEAN_ASK='NO'
fi

#---------------------------------------------------------------------------------------------------------------------------------------------------------------
declare -a CMAKE_ARGS

#
# Add build dir if missing
FOUND_IT='0'
i=1
while [ $i -le $# ]; do
  if [ "${!i}" == "-B" ]; then
    FOUND_IT=$i
  fi
  ((i++))
done
CMAKE_BDIR='build'
if [ "$FOUND_IT" == '0' ]; then
  CMAKE_ARGS+=('-B')
  CMAKE_ARGS+=("$CMAKE_BDIR")
else
  if [ "$FOUND_IT" -ge $# ]; then
    echo "ERROR: Found -B but no following argument!"
    exit
  fi
  ((FOUND_IT++))
  CMAKE_BDIR="${!FOUND_IT}"
fi

#
# If we need to clean, then CLEAN!!
if [ "$CLEAN_DIR" == 'YES' ]; then
  if [ -e "$CMAKE_BDIR" ]; then
    if [ "$CLEAN_ASK" == 'YES' ]; then
      if [ "$CONFIGURE_DOIT" == 'Y' ]; then
        echo "Contents of $CMAKE_BDIR: "
        ls -ld "$CMAKE_BDIR"/* | sed 's/^/    /'
        echo " "
        rm -rI "$CMAKE_BDIR"
      fi
    else
      if [ "$CONFIGURE_DOIT" == 'Y' ]; then
        rm -rf "$CMAKE_BDIR"
      fi
    fi
  else
    echo "WARNING: Build directory clean requested, but directory ($CMAKE_BDIR) not found!"
  fi
fi

#
# Add generator if missing
FOUND_IT='0'
i=1
while [ $i -le $# ]; do
  if [ "${!i}" == "-G" ]; then
    FOUND_IT=$i
  fi
  ((i++))
done
CMAKE_GEN="$CMAKE_GENERATOR"
if [ "$FOUND_IT" == '0' ]; then
  CMAKE_ARGS+=('-G')
  if [ -z "$CMAKE_GEN" ]; then
    if [ -n "$MSYSTEM" ]; then
      CMAKE_GEN='MSYS Makefiles'
    else
      CMAKE_GEN='Unix Makefiles'
    fi
  fi
  CMAKE_ARGS+=("$CMAKE_GEN")
else
  if [ "$FOUND_IT" -ge $# ]; then
    echo "ERROR: Found -G but no following argument!"
    exit
  fi
  ((FOUND_IT++))
  CMAKE_GEN="${!FOUND_IT}"
fi

#
# Add -DCMAKE_EXPORT_COMPILE_COMMANDS=1 if required
FOUND_IT='N'
for arg in "$@"; do
  if [[ "$arg" =~ ^-DCMAKE_EXPORT_COMPILE_COMMANDS=.+ ]]; then
    FOUND_IT='Y'
  fi
done
if [ "$FOUND_IT" == 'N' ]; then
  CMAKE_ARGS+=('-DCMAKE_EXPORT_COMPILE_COMMANDS=1')
fi

#
# Add -DCMAKE_BUILD_TYPE=Release if required
FOUND_IT='N'
for arg in "$@"; do
  if [[ "$arg" =~ ^-DCMAKE_BUILD_TYPE=.+ ]]; then
    FOUND_IT='Y'
  fi
done
if [ "$FOUND_IT" == 'N' ]; then
  CMAKE_ARGS+=('-DCMAKE_BUILD_TYPE=Release')
fi

#
# Add -DCMAKE_CXX_COMPILER if missing
FOUND_IT='N'
for arg in "$@"; do
  if [[ "$arg" =~ ^-DCMAKE_CXX_COMPILER=.+ ]]; then
    FOUND_IT='Y'
  fi
done
if [ "$FOUND_IT" == 'N' ]; then
  if [ "$CMAKE_GEN" == 'MSYS Makefiles' ]; then
    CMAKE_ARGS+=('-DCMAKE_CXX_COMPILER=g++.exe')
  else
    if [ "$CMAKE_GEN" == 'Unix Makefiles' ]; then
      HIGCC=$(ls /usr/bin/gcc-[0-9][0-9] 2>/dev/null | sort | tail -n 1)
      if [ -x "$HIGCC" ]; then
        CMAKE_ARGS+=('-DCMAKE_CXX_COMPILER=${HIGCC}')
      else
        CMAKE_ARGS+=('-DCMAKE_CXX_COMPILER=g++')
      fi
    fi
  fi
fi

#
# Report what we did
if [ "$CONFIGURE_DEBUG" == 'Y' ]; then
  echo Added CMAKE_ARGS: ${CMAKE_ARGS[@]}
  echo CMAKE_GEN: $CMAKE_GEN
  echo CMAKE_BDIR: $CMAKE_BDIR
fi

#
# Report what we did
CMAKE_ARGS+=("$@")

#
# Report what we did
if [ "$CONFIGURE_DEBUG" == 'Y' ]; then
  echo FINAL CMAKE_ARGS: ${CMAKE_ARGS[@]}
fi

#
# Run cmake
echo RUNNING: cmake "${CMAKE_ARGS[@]}"
if [ "$CONFIGURE_DOIT" == 'Y' ]; then
  if cmake "${CMAKE_ARGS[@]}"; then
    echo ""
    echo "The cmake configure appears to have been successful!"
    echo "Build with a command like the following:"
    echo "    cmake --build ${CMAKE_BDIR} --parallel 8 -t all"
    echo ""
  fi
fi
