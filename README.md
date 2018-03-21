# Compiler
#### Created by Ben Gafford
Compiler (being) built in C++.  

More details to come in the future.  

## Language Syntax
Language is defined as the following:   
```
e ::= (e) | n | b | e1 (+) e2 | if e1 then e2 else e3
    | x | let x : t = e1 in e2 | fun (x:t1) : t2 |-> e | fix f (x:t1) : t2 |-> e | e1 e2
    | () | (e1 . e2) | fst e | snd e
    | ref e | e1 : e2 | #e | e1 ; e2
    | while e1 do e2 end
```

## Types
Types defined as the following:
```
t ::= int | bool | unit | <t> | t1 -> t2 | t1 * t2
```

## Dependencies
* `getopt`
* `g++`
* `bison` version >= 3.0.4
* `flex`  version >= 2.6.4
* `ncurses`

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

### v0.0.6 (3/20/2018)
* Added multiline comments (nested comments allowed)
* Added state and relevant types and expressions
  * References, dereference operator, while loops, statement sequencing
* Added basic REPL infrastructure -- TODO: actually compile and display user input
