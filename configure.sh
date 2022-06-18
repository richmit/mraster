#!/bin/bash

if [[ "$1" == '-'* ]]; then
  cat <<EOF

  Use: configure.sh [TARGET_TYPE]
  
       TARGET_TYPE is the cmake -G option
        Some popular choices:
          - 'MSYS Makefiles' 
          - 'Visual Studio 17 2022'
          - 'Unix Makefiles'
          - Ninja          
  
       If TARGET_TYPE is not provided, then the system default will be
       used unless $MSYSTEM is set in which case 'MSYS Makefiles' will
       be used.

EOF
exit
fi

if [ -e examples -a -e lib -a -e CMakeLists.txt ] ; then
  if [ -e build ] ; then
    echo 'The "build" directory already exists.  Remove it, and run this script again.'
  else
    mkdir build
    cd build

    if [ -n "$MSYSTEM" ] ; then
      CMAKE_G='MSYS Makefiles'
    fi
    if [ -n "$1" ] ; then
      CMAKE_G=$1
    fi

    if [ -n "$CMAKE_G" ] ; then
      cmake -G "$CMAKE_G" ../
    else
      cmake ../
    fi

    echo 'Now you can build with soemthing like this:'
    echo '   cd build'
    echo '   make bmark'
  fi
else
    echo 'Can not find one or more of examples/, lib/, or CMakeLists.txt.  Are you in the correct directory?'
fi
