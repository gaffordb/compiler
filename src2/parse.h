#ifndef PARSE_H
#define PARSE_H
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <vector>
#include "lex.h"

namespace Parse {
  class Exp {
  public:
    virtual int interpret(void) {return 0;}
  };

  class Lit : public Exp {
  public:
    int data;
    Lit(int data);
    int interpret(void);
  };

  class Plus : public Exp {
  public:
    std::shared_ptr<Exp> e1, e2;
    Plus(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
    int interpret(void);
  };
  class Parser {
    int pos;
    std::shared_ptr<std::vector<Token> > ptoks;
    void advance(void);
    void consume(TokenType t);
  public:
    Parser(std::shared_ptr<std::vector<Token> > ptoks);
    std::shared_ptr<Exp> parse(void);
  };
}
#endif
