#!/bin/bash

if [ $# -eq 2 ]
then
    writefile=$1
    writestr=$2
else
    echo "2 arguments are expected but $# are given"
    exit 1
fi

if [ -d $writefile ] 
then
    echo "$writefile is a directory : choose another filename or delete the directory to continue."
    exit 1
fi

dirpath=$(dirname "$writefile")

if [[ ( ! "$dirpath" -eq '.' ) || ( ! -d "$dirpath" ) ]]
then
    mkdir -p "$dirpath"
    if [ ! -d "$dirpath" ] 
    then
        echo "Cannot create $dirpath"
        exit 1
    fi
fi

echo "$writestr" > $writefile