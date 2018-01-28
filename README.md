# Compiler
##### Ben Gafford
Compiler (being) built in C++.  
More details to come in the future.  

## Dependencies
* `getopt`
* `g++`

## Build Instructions
* Clone repository onto your system.
* Enter the following command at the base of the directory:  
    `make testit`  
     * This will compile `program.cpp` into `program` and place the binary into `bin/`, and test the newly created executable.  
## Usage 
```
program [flags] [args]  
Available flags:  
  -length	prints the lengths of each of the arguments  
  -help	prints the help message
``` 

## Changelog
### v0.0.1 (1/29/2018)
* Build infrastructure set up
* Example .cpp file in place
* Testing infrastructure set up in run-tests.sh
* Added pre-commit hook to ensure functional build
* Basic README setup


