#!/bin/sh

if [ $# -eq 2 ]
then
    filesdir=$1
    searchstr=$2
else
    echo "Two arguments expected by $# are given"
    exit 1
fi

if [ ! -d "${filesdir}" ]
then
    echo $(pwd)
    echo "${filesdir} is not a valid directory."
    exit 1
fi

X=$(find $filesdir -type f | wc -l)
Y=$(grep -r $searchstr $filesdir | wc -l)
echo "The number of files are $X and the number of matching lines are $Y"