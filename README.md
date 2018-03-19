# Compiler
#### Created by Ben Gafford
Compiler (being) built in C++.  

More details to come in the future.  

## Language Syntax
Language is defined as the following:   
```
e ::= n | b | e1 (+) e2 | if e1 then e2 else e3
    | x | let x = e1 in e2 | fun x -> e | fix f x -> e | e1 e2
```

## Dependencies
* `getopt`
* `g++`
* `bison`
* `flex`

## Build Instructions
* Clone repository onto your system.
* Enter the following command at the base of the directory:  
    `make build`  
     * This will compile relevant files into executables, and place them into bin, and test the created files.
* In order to include pre-commit hooks with your local repository, enter the following command at the base of your repository:  
    `ln -s /absolute/path/to/repo/compiler/githooks/pre-commit .git/hooks/pre-commit`
    
## Usage
Compiler: 
* parse and interpret valid expressions from text files given by `filename` 
```
compiler [flags] [filename]  
Available flags:  
  --parse   compiler processes input through the parsing phase, printing the 
  resulting abstract syntax tree in the form of an S-expression
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


### v0.0.3 (3/08/2018)
* Integrated lexer and parser generator
* Language syntax changed from S-expressions to infix syntax. 
* New test suite.
* Added testing through the parsing stage of compilation. 

### v0.0.4 (3/18/2018)
* Added let bindings, functions, fix expressions, and function application.
* Added relevant testing.
* Added macro that allows for catching bugs in the lexing phase.

### v0.0.5 (3/19/2018)
* Added static typing system.
* Added unit and pair type.
* Added fst and snd function.
