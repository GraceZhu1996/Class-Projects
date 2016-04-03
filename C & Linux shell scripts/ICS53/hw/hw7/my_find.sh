#!/bin/bash

#settings
IFS=$'\n'
argc=$#
path="."
declare -A options

#Prints arg1 and does exec on arg2 if available
do_echo(){
    print_=${options["-print"]}
    brackets="{}"
    if [[ -n $2 ]] #if exec option
    then
        command=$(echo "$2" | sed '/^$/d' | sed "s|$brackets|'"$1"'|g")
        eval "$command"
    else
        if [[ $print_ == 1 ]]; then echo "$1"; fi
    fi
}

do_find(){
    #Handle name option
    if [[ -n ${options["-name"]} ]]; then name_=${options["-name"]}; fi
    #Handle type option
    if [[ -n ${options["-type"]} ]]; then type_=${options["-type"]}; fi
    #Handle exec option
    if [[ -n ${options["-exec"]} ]]; then exec_=${options["-exec"]}; fi
    
    content=$(ls -a1 "$1") #Get dir contents
    #Print the working directory first before it's contents
    if [[ -d "$1" && "$type_" != "f" ]]
    then
        if [[ -z "$name_" ]] || [[ "$1" =~ "$name_" ]]; then do_echo "$1" "$exec_"; fi
    fi

    #Handle it's contents
    for f in ${content[*]}
    do
        if [[ "$f" == "." || "$f" == "./" || "$f" == ".." || "$f" == "../" ]]; then continue; fi
        local longpath="$1/$f"
        if [[ -f "$longpath" && "$type_" != "d" ]]
        then
            if [[ -z "$name_" ]] || [[ "$longpath" =~ "$name_" ]]
            then 
                do_echo "$longpath" "$exec_"
            fi
        
        elif [[ -d "$longpath" ]]
        then
            do_find $longpath;
        fi
    done
}

#Loop through and parse arguments
options["-print"]=0 #By default
for ((i=1 ; i <= argc ; i++))
do 
    if [[ ${1:0:1} == "-" ]]
    then
        s="$1"
        if [[ $s == "-print" ]]
        then
            options["-print"]=1
        elif [[ $s == "-exec" ]]
        then
            shift
            while [[ -n $1 && $1 != ";" ]]; do
                options["-exec"]="${options[$s]} $1"
                shift
            done
            break
        else
            shift
            options["$s"]="$1"
        fi
    else
        if [[ $i == 1 ]]
        then
            path="$1"
        #else
        #    echo "This should never be printed [$1]."
        fi
    fi
    shift
done
do_find $path 

