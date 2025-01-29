#!/bin/sh

INFILE="$1"

export MSYS2_ARG_CONV_EXCL='*'

OUTNAM=`echo $INFILE | sed 's/\.[^.]*$//'`.mrw
INMETA=`identify -format '%w %h %z %[channels]\n' $INFILE`

echo "MJRRAW"                                                                                                                      > $OUTNAM
echo $INMETA | awk '{printf("%019dx%019dy%027dc%011dbUNSsINTtLTLi\n", $1, $2, $3, $3)}'                                           >> $OUTNAM
magick $INFILE `echo $INMETA | awk '{print "-size " $1 "x" $2 " -depth " $3 " -endian LSB " ($4~/gray/ ? "gray:" : "rgb:") }'`-   >> $OUTNAM
