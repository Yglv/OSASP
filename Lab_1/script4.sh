#!/bin/bash

min=$1
max=$2
outfile=$3
mydir=`realpath $4`

if [ -d $mydir ]
then
 find $mydir -type f -size +$min -size -$max -printf '%p %sB\n'>$outfile
 find $mydir -type f | wc -l
else 
  echo "Provided dir is incorrect">&2
fi
 
  
