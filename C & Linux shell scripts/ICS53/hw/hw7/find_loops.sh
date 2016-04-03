#!/bin/bash

#IFS=$'\n'
argc=$#
file="THis is a file"

for tok in ${file[*]}
do
    echo ${tok:0:2}
done
