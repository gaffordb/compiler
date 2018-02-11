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
    //Exp();
    virtual int interpret(void){return 0;}
    virtual ~Exp(){};
  };

  class Lit : public Exp {
  public:
    int data;
    Lit(int data);
    int interpret(void);
  };

  class Operator : public Exp {
  public:
    std::shared_ptr<Exp> e1, e2;
    int interpret(void);
  };

  class Plus : public Operator {
  public:
    Plus(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
    int interpret(void);
  };

  class Minus : public Operator {
  public:
    Minus(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
    int interpret(void);
  };

  class Multiply : public Operator {
  public:
    Multiply(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
    int interpret(void);
  };

  class Divide : public Operator {
  public:
    Divide(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
    int interpret(void);
  };

  //this is special tho! add another expression!
  class Ifop : public Operator {
  public:
    std::shared_ptr<Exp> e3;
    Ifop(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2,
      std::shared_ptr<Exp> e3);
      int interpret(void);
    };

    class Lequal : public Operator {
    public:
      Lequal(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);
      int interpret(void);
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
