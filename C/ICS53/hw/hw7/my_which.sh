#!/bin/bash

argc=$#

if [[ $argc == 0 ]]
then
    echo "Usage: my_which command [commands]"
    exit 0
fi

path=$(echo $PATH | tr ":" "\n" | sort | uniq | tr "\n" " ")

for i in $@; do
    for p in ${path[*]}; do
        found=$(ls -a1 "$p" | grep ^$i$ | head -n 1)
        if [[ -n $found ]]
        then
           echo "$p/$i"
           break
        fi
    done
done

