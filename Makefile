SRC=$(SRCDIR)compiler.cpp $(SRCDIR)lang.cpp $(SRCDIR)parser_driver.cpp
LEX_OUTPUT=$(SRCDIR)scanner.yy.cpp
BISON_OUTPUT=$(SRCDIR)parser.yy.cpp
BISON_AUX=$(SRCDIR)location.hh $(SRCDIR)parser.yy.cpp $(SRCDIR)parser.yy.hpp $(SRCDIR)position.hh $(SRCDIR)stack.hh $(SRCDIR)parser.h
CC=g++
CC_FLAGS=-std=c++14 -O3 -Wall -Wno-deprecated-register
SRCDIR=src/lex-yacc-parser/
ROOT=.
.PHONY : compiler clean

compiler : ${LEX_OUTPUT} ${BISON_OUTPUT} ${SRC}
	${CC} -o $@ ${CC_FLAGS} $^

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
	mkdir -p ./bin; make; mv compiler $(ROOT)/bin; $(ROOT)/test/compiler-tests.sh &> /dev/null; $(ROOT)/test/parse-tests.sh &> /dev/null;
