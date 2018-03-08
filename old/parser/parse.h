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
#include <string>
#include "lex.h"

namespace Parse {
  class Exp {
  public:
    virtual std::string interpret(void){return "dicks";}
  };

  class Lit : public Exp {
  public:
    Lit(std::string data);
    std::string data;
    std::string interpret(void);
  };

  bool validInt(std::string& s);
  bool validBool(std::string& s);

  class Operator : public Exp {
  public:
    std::shared_ptr<Exp> e1, e2;
    std::string interpret(void);
  };

  class Plus : public Operator {
  public:
    Plus(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
    std::string interpret(void);
  };

  class Minus : public Operator {
  public:
    Minus(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
    std::string interpret(void);
  };

  class Multiply : public Operator {
  public:
    Multiply(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
    std::string interpret(void);
  };

  class Divide : public Operator {
  public:
    Divide(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
    std::string interpret(void);
  };

  //this is special tho! add another expression!
  class Ifop : public Operator {
  public:
    std::shared_ptr<Exp> e3;
    Ifop(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2,
      std::shared_ptr<Exp> e3);
      std::string interpret(void);
    };

    class Lequal : public Operator {
    public:
      Lequal(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
      std::string interpret(void);
    };

    class Parser {
      int pos;
      std::shared_ptr<std::vector<Token> > ptoks;
      void advance(void);
      TokenType consume(Token& t);
    public:
      Parser(std::shared_ptr<std::vector<Token> > ptoks);
      std::shared_ptr<Exp> parse(void);
    };

    std::shared_ptr<Parse::Operator> instantiate_operator(TokenType t, std::shared_ptr<Exp> e1,
      std::shared_ptr<Exp> e2);

    }

    #endif
