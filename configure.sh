#!/bin/bash


#
# On most platforms, you do something like this:
#
#   mkdir build; cd build
#
# On MSYS2, you can then do this:Then do this (for CLANG):
#
#   cmake -G "MSYS Makefiles" -DCMAKE_CXX_COMPILER=clang++ ..
#
# or this (for GCC):
#
#   cmake -G "MSYS Makefiles" -DCMAKE_CXX_COMPILER=g++.exe ..
#
# or this (for MSVC):
#
#   cmake -G "Visual Studio 17 2022" ..
# And then run Visual Studio and open one of the proejct files.
#
# Other "O" options include: O_DOXYGEN, O_TIFF, O_OPENGL, O_OPENMP, O_PNG, O_IM, & O_STATIC
#
# Leave off the -DCMAKE_CXX_COMPILER... option to use the default compiler
#

CMD_LINE_ARGS="${@}"

if [[ "$CMD_LINE_ARGS" == *'-h'* ]]; then
  cat <<EOF

  Use: configure.sh [cmake arguments]

    Common Arguments:
     * Target -- leave it off and get 'MSYS Makefiles'
       - -G 'MSYS Makefiles' 
       - -G 'Visual Studio 17 2022'
       - -G 'Unix Makefiles'
       - -G Ninja
     * Compiler -- leave it off to get the default
       - -DCMAKE_CXX_COMPILER=clang++
       - -DCMAKE_CXX_COMPILER=g++
     * Optional features -- leave them off to enable everythign
       - -DO_DOXYGEN=[YES|NO]
       - -DO_OPENGL=[YES|NO]
       - -DO_OPENMP=[YES|NO]
       - -DO_TIFF=[YES|NO]     -- Provides advanced TIFF read functionality
       - -DO_O_SDL2=[YES|NO]
       - -DO_O_BTEST=[YES|NO]  -- Used for BOOT unit tests
EOF
exit
fi

if [ -e examples -a -e lib -a -e CMakeLists.txt ] ; then
  if [ -e build ] ; then
    echo 'The "build" directory already exists.  Remove it, and run this script again.'
  else
    mkdir build
    cd build

    if [[ "$CMD_LINE_ARGS" == *'-G'* ]]; then
      echo cmake "$@" ../
      cmake "$@" ../
    else
      echo cmake -G 'MSYS Makefiles' "$@" ../
      cmake -G 'MSYS Makefiles' "$@" ../
    fi

    echo 'Now you can build with soemthing like this:'
    echo '   cd build'
    echo '   make bmark'
  fi
else
    echo 'Can not find one or more of examples/, lib/, or CMakeLists.txt.  Are you in the correct directory?'
fi
