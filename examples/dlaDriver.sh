#!/bin/bash

# [dlaBrowian|dlaDrift] [border|center|circles] ### ###

if [ -e ${1}_${2}.tiff ] ; then
  mv ${1}_${2}.tiff ${1}_${2}_in.tiff
  ${1} ${1}_${2}_in.tiff ${1}_${2}.tiff ${3} ${4}
else
  ${1} dlaSeed_${2}.tiff ${1}_${2}.tiff ${3} ${4}
fi
