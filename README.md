# Compiler
#### Created by Ben Gafford
Compiler (being) built in C++.  
Currently able to parse basic S-Expressions. Full language syntax is as follows: 
```
e ::= n | (+ e1 e2) | (- e1 e2) | (* e1 e2) | (/ e1 e2)
    | true | false | (<= e1 e2) | (if e1 e2 e3)
```

More details to come in the future.  

## Dependencies
* `getopt`
* `g++`

## Build Instructions
* Clone repository onto your system.
* Enter the following command at the base of the directory:  
    `make build`  
     * This will compile relevant files into executables, and place them into bin, and test the created files.
* In order to include pre-commit hooks with your local repository, enter the following command at the base of your repository:  
    `ln -s /absolute/path/to/repo/compiler/githooks/pre-commit .git/hooks/pre-commit`
    
## Usage
Program:  
* print out `args`  
* use `flags` as indicated below  
```
program [flags] [args]  
Available flags:  
  -length   prints the lengths of each of the arguments  
  -help     prints the help message
``` 
Driver:  
* parse valid S-Expressions from text files given in `filename`  
```
driver [filename]
Available flags: [none]

```

## Language Syntax
Language is defined as the following:   
```
e ::= n | (+ e1 e2) | (- e1 e2) | (* e1 e2) | (/ e1 e2)
    | true | false | (<= e1 e2) | (if e1 e2 e3)
```
## Changelog
### v0.0.1 (1/29/2018)
* Build infrastructure set up
* Example .cpp file in place
* Testing infrastructure set up in run-tests.sh
* Added pre-commit hook to ensure functional build
* Basic README setup

### v0.0.2 (2/13/2018)
* Fixed code linter and pre-commit hook
* Added tocheck.txt to include all of the files to be run through linter
* Included driver.cpp, parse.cpp, lex.cpp, parse.h, lex.h.
* Added testing for driver

