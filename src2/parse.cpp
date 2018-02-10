#include "parse.h"

using namespace std;

  Parse::Lit::Lit(int data) {
    this->data = data;
  }
  int Parse::Lit::interpret(void) {
    return this->data;
  }

  Parse::Plus::Plus(shared_ptr<Parse::Exp> e1, shared_ptr<Parse::Exp> e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
  int Parse::Plus::interpret(void) {
    return this->e1->interpret() + this->e2->interpret();
  }
  void Parse::Parser::advance(void) {
    this->pos++;
  }
  void Parse::Parser::consume(TokenType t) {
    if(t == ptoks->at(pos).type) {
      advance();
    } else {
      //cout << "Expected " << t << "found " << ptoks->at(pos) << endl
    }
  }
  Parse::Parser::Parser(shared_ptr<vector<Token> > ptoks) {
    this->ptoks = ptoks;
    pos = 0;
  }

  shared_ptr<Parse::Exp> Parse::Parser::parse(void) {
    if(pos < ptoks->size()) {
      Token t = ptoks->at(pos);
      switch(t.type) {
        case tint: {
          advance();
          Parse::Lit l(t.data.i);
          return make_shared<Parse::Lit>(l);
        }
        case tlparen: {
          consume(tlparen);
          consume(tplus);
          shared_ptr<Exp> e1 = make_shared<Parse::Exp>();
          e1 = parse();
          shared_ptr<Exp> e2 = make_shared<Parse::Exp>();
          e2 = parse();
          consume(trparen);
          Parse::Plus p(e1, e2);
          return make_shared<Parse::Plus>(p);
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
