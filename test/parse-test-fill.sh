#!/bin/bash

NUM_TESTS=41
#sed "${NUM}q;d" file -- to get a specific line from a file
for ((i=0; i<NUM_TESTS; i++)); do
    echo Running test $i... 
    ./bin/compiler --parse "test/test-infix/test$i.in" > "test/test-infix/parse/test$i.out"
done
exit 0