#!/bin/bash


#
# MSYS instructions
#
# From the msys2 shell use something like this:
#
#   mkdir build; cd build
#
# Then do this
#
#   echo "RUN CMAKE"; cmake -G "MSYS Makefiles" -DCMAKE_CXX_COMPILER=clang++ -DO_TIFF=YES ..
#
# or this
#
#   echo "RUN CMAKE"; cmake -G "MSYS Makefiles" -DCMAKE_CXX_COMPILER=g++.exe -DO_TIFF=YES ..
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
       - -DO_IM=[YES|NO]
       - -DO_OPENGL=[YES|NO]
       - -DO_OPENMP=[YES|NO]
       - -DO_PNG=[YES|NO]
       - -DO_STATIC=[YES|NO]
       - -DO_TIFF=[YES|NO]

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
