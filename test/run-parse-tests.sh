#!/bin/bash

NUM_TESTS=4
#sed "${NUM}q;d" file -- to get a specific line from a file
for ((i=1; i<=NUM_TESTS; i++)); do
    echo Running test $i... 
    ./bin/driver "test/parsein/parse$i.in" > tmp.txt
    OUT=$(diff tmp.txt "test/parseout/parse$i.out")
    rm tmp.txt
    if [ ${#OUT} == 0 ]; then
	echo Test $i successful.
    else
	echo Test $i failed. 
	exit 1
    fi
done
echo All tests successful.
exit 0