SRC=compiler.cpp lang.cpp parser_driver.cpp
LEX_OUTPUT=scanner.yy.cpp
BISON_OUTPUT=parser.yy.cpp
BISON_AUX=location.hh parser.yy.cpp parser.yy.hpp position.hh stack.hh parser.h
CC=g++
CC_FLAGS=-std=c++14 -O3 -Wall -Wno-deprecated-register

.PHONY : compiler clean

compiler : ${LEX_OUTPUT} ${BISON_OUTPUT} ${SRC}
	${CC} -o $@ ${CC_FLAGS} $^

scanner.yy.cpp : scanner.l
	flex -o $@ $<

parser.yy.cpp : parser.yy
	bison -o $@ $<

clean :
	rm -rf compiler
	rm -rf ${BISON_OUTPUT} ${BISON_AUX}
	rm -rf ${LEX_OUTPUT}

	#build::
	#	mkdir -p ./bin; make all; $(ROOT)/test/run-tests.sh; $(ROOT)/test/run-parse-tests.sh;
