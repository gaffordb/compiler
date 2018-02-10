#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <vector>
#include "parse.h"

using namespace std;
namespace Parse {
  class Exp {
  public:
    virtual int interpret(void);
  };

  class Lit : public Exp {
  public:
    int data;
    Lit(int data) {
      this->data = data;
    }
    int interpret() {
      return data;
    }
  };

  class Plus : public Exp {
  public:
    shared_ptr<Exp> e1, e2;
    Plus(shared_ptr<Exp> e1, shared_ptr<Exp> e2) {
      this->e1 = e1;
      this->e2 = e2;
    }
    int interpret() {
      return e1->interpret() + e2->interpret();
    }
  };
  class Parser {
    int pos;
    shared_ptr<vector<Token> > ptoks;

    void advance(void) {
      pos++;
    }

    void consume(TokenType t) {
      if(t == ptoks->at(pos).type) {
        advance();
      } else {
        //cout << "Expected " << t << "found " << ptoks->at(pos) << endl
      }
    }
  public:
    Parser(shared_ptr<vector<Token> > ptoks) {
      this->ptoks = ptoks;
      pos = 0;
    }

    shared_ptr<Exp> parse() {
      if(pos < ptoks->size()) {
        Token t = ptoks->at(pos);
        switch(t.type) {
          case tint: {
            advance();
            Lit l(t.data.i);
            return make_shared<Lit>(l);
          }
          case tlparen: {
            consume(tlparen);
            consume(tplus);
            shared_ptr<Exp> e1 = make_shared<Exp>();
            e1 = parse();
            shared_ptr<Exp> e2 = make_shared<Exp>();
            e2 = parse();
            consume(trparen);
            Plus p(e1, e2);
            return make_shared<Plus>(p);
          }
          default:
          break;
          //cout << "Expected a token: " << t << endl;
        }
      } else {
        //cout << "Error parsing, no tokens found." << endl;
      }

      return nullptr;
    }


  };
}
