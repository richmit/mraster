#~/bin/sh

# Use:  mrw2any.sh inputFile [outputFormat]
#      If missing, the outputFormat defaults to "png"
#
# Assumes unsigned integer data.  Only works on 1-4 channel images.

if [ -z "$2" ] ; then
  TOFMT="png"
else
  TOFMT="$2"
fi
  
if [ -e $1 ] ; then
  OUTNAM=`echo $1 | sed 's/\.[^.]*$//'`."$TOFMT"
  if [ -e $OUTNAM ] ; then
    echo "ERROR: Output file already exists: $OUTNAM"
  else
    CONCMD=`head -n 2 $1 | tail -n 1 | awk '{t[1]="gray"; t[1]="graya"; t[3]="rgb"; t[4]="rgba"; split($0, a, /[xycbsti]/); print "convert -interlace none -endian " (a[7]~/LTL/?"LSB":"MSB") " -depth " (a[4]+0) " -size " (a[1]+0) "x" (a[2]+0) "+100 " (t[a[3]+0]?t[a[3]+0]:"ERROR") ":"}'`
    if echo "$CONCMD" | grep 'ERROR:' >/dev/null ; then
      echo "ERROR: Couldn't figure out command.  Probably a bad channel count (not 1, 3, or 4)."
      echo "Best we could do: $CONCMD$1 $OUTNAM"
    else
      echo "COMMAND: $CONCMD$1 $OUTNAM"
      `$CONCMD$1 $OUTNAM`
      ls -l $OUTNAM
    fi    
  fi
else
  echo "ERROR: File not found: $1"
fi


