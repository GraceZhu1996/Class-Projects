#!/bin/bash

argc=$#

if [[ $argc == 0 ]]
then
    echo "Usage: dircheck command [commands]"
    exit 0
fi

for i in $@
do
    echo [$i]
    echo "Subdir count: $(find $i ! -path $i -type d | wc -l)"
    echo "File count: $(find $i ! -path $i -type f | wc -l)"
    echo "0 length files:"
    echo "$(find $i ! -path $i -type f -exec du -s {} \; | grep '^0' | tr '0' ' ')"
    echo "Total: $(du -c $i | tail -n 1 | grep -Eo '[0-9]{1,}')"
done


