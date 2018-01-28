#!/bin/bash
#this only works if i'm in the correct directory... howtodothisnotshitty?
echo Running test 1...
../bin/program foo bar baz > tmp.txt
OUT=$(diff tmp.txt test1.out)

if [ ${#OUT} == 0 ]; then
    echo Test successful.
else
    echo Code broken!
fi

rm tmp.txt