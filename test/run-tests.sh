#!/bin/bash
#this only works if i'm in the correct directory... howtodothisnotshitty?
echo Running test 1...

./bin/program foo bar baz > tmp.txt
OUT=$(diff tmp.txt test/test1.out)
rm tmp.txt
if [ ${#OUT} == 0 ]; then
    echo Test successful.
    exit 0
else
    echo Code broken!
    exit 1
fi