#!/bin/bash

source=$1
compiled=$2

if [ -f $source ]
then
  gcc $source -o $compiled && ./$compiled
else
  echo "provided file is incorrect"
fi
