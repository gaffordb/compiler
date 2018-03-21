SRC=$(SRCDIR)compiler.cpp $(SRCDIR)lang.cpp $(SRCDIR)parser_driver.cpp
LEX_OUTPUT=$(SRCDIR)scanner.yy.cpp
BISON_OUTPUT=$(SRCDIR)parser.yy.cpp
BISON_AUX=$(SRCDIR)location.hh $(SRCDIR)parser.yy.cpp $(SRCDIR)parser.yy.hpp $(SRCDIR)position.hh $(SRCDIR)stack.hh $(SRCDIR)parser.h
CC=g++
CC_FLAGS=-std=c++14 -O3 -Wall -Wno-deprecated-register -Wno-duplicate-decl-specifier
SRCDIR=src/lex-yacc-parser/
ROOT=.

.PHONY : all repl compiler clean

compiler : ${LEX_OUTPUT} ${BISON_OUTPUT} ${SRC}
	${CC} -o $@ ${CC_FLAGS} $^

repl :
	g++ -o ./bin/repl -std=c++14 -O3 -Wall -Wno-deprecated-register -Wno-duplicate-decl-specifier $(SRCDIR)interpreter.cpp $(SRCDIR)lang.cpp $(SRCDIR)parser_driver.cpp $(SRCDIR)scanner.yy.cpp $(SRCDIR)parser.yy.cpp -lcurses


$(SRCDIR)scanner.yy.cpp : $(SRCDIR)scanner.l
	flex -o $@ $<

$(SRCDIR)parser.yy.cpp : $(SRCDIR)parser.yy
	bison -o $@ $<


clean :
	rm -rf ./bin
	rm -rf ${BISON_OUTPUT} ${BISON_AUX}
	rm -rf ${LEX_OUTPUT}
#pushd $(SRCDIR); make; popd;
build::
	mkdir -p ./bin; make; make repl; mv compiler $(ROOT)/bin/compiler; $(ROOT)/test/compiler-tests.sh &> /dev/null;
