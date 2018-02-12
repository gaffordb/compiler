#include "parse.h"
#include "error.h"

using namespace std;

Parse::Lit::Lit(int data) {
  this->data = data;
}
Parse::BLit::BLit(bool data) {
  this->data = data;
}
Parse::ILit::ILit(int data) {
  this->data = data;
}
Parse::Ifop::Ifop(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2,
  std::shared_ptr<Exp> e3){
    this->e1 = e1;
    this->e2 = e2;
    this->e3 = e3;
  }

  //c++ sux
  Parse::Plus::Plus(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2){
    this->e1 = e1;
    this->e2 = e2;
  }

  Parse::Minus::Minus(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2)
  {
    this->e1 = e1;
    this->e2 = e2;
  }

  Parse::Divide::Divide(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2)
  {
    this->e1 = e1;
    this->e2 = e2;
  }

  Parse::Multiply::Multiply(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2)
  {
    this->e1 = e1;
    this->e2 = e2;
  }

  Parse::Lequal::Lequal(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2)
  {
    this->e1 = e1;
    this->e2 = e2;
  }


  int Parse::Operator::interpret(void) {
    print_error("This should not happen. Trying to interpret raw op.\n");
    return -12;
  }

  int Parse::Plus::interpret(void) {
    return this->e1->interpret() + this->e2->interpret();
  }

  int Parse::Minus::interpret(void) {
    return this->e1->interpret() - this->e2->interpret();
  }

  int Parse::Multiply::interpret(void) {
    return this->e1->interpret() * this->e2->interpret();
  }

  int Parse::Divide::interpret(void) {
    if(this->e2->interpret() == 0) {
      print_error("Error: Cannot divide by zero. Exiting.\n");
    }
    return this->e1->interpret() / this->e2->interpret();
  }

  int Parse::Ifop::interpret(void) {
    //need to typecheck left and right... :(
    bool cond = this->e1->interpret();
    int left = this->e2->interpret();
    int right = this->e3->interpret();
    if(cond) {
      return left;
    } else {
      return right;
    }
  }

  bool Parse::Lequal::interpret(void) {
    int left = this->e1->interpret();//but you can't override return types...
    int right = this->e2->interpret();
    return left <= right;
  }

  void Parse::Parser::advance(void) {
    this->pos++;
  }

  TokenType Parse::Parser::consume(Token& t) {
    if(isOperator(t)) {
      advance();
      return t.type;
    } else {
      print_error("Unexpected token stream. Exiting.\n");
    }
    //this cannot happen
    return t.type;
  }

  Parse::Parser::Parser(shared_ptr<vector<Token> > ptoks) {
    this->ptoks = ptoks;
    pos = 0;
  }

  shared_ptr<Parse::Operator> Parse::instantiate_operator(TokenType t, std::shared_ptr<Exp> e1,
    std::shared_ptr<Exp> e2) {
      switch(t) {
        case tplus: {
          Parse::Plus o(e1, e2);
          return make_shared<Parse::Plus>(o);
          break;
        }
        case tminus: {
          Parse::Minus o(e1, e2);
          return make_shared<Parse::Minus>(o);
          break;
        }
        case tmult: {
          Parse::Multiply o(e1, e2);
          return make_shared<Parse::Multiply>(o);;
          break;
        }
        case tdiv: {
          Parse::Divide o(e1, e2);
          return make_shared<Parse::Divide>(o);;
          break;
        }
        case tif: {
          print_error("Error. Expected non-if operator. Exiting.");
          //Parse::Ifop o(e1, e2);
          exit(1);
          Parse::Ifop o(e1, e2);
          return make_shared<Parse::Ifop>(o);;
          break;
        }
        case tlequal: {
          Parse::Lequal o(e1, e2);
          return make_shared<Parse::Lequal>(o);;
          break;
        }
        default:
        print_error("Error. Expected Operator. Exiting.\n");
        exit(1);
        break;
      }
    }

    shared_ptr<Parse::Exp> Parse::Parser::parse(void) {
      if(pos < ptoks->size()) {
        Token t = ptoks->at(pos);
        //cout << "Munchin' on: " << t << endl;
        switch(t.type) {
          case tint: {
            advance();
            Parse::Lit l(t.data.i);
            return make_shared<Parse::Lit>(l);
          }
          case tbool: {
            advance();
            Parse::Lit l(t.data.b, true);
            return make_shared<Parse::Lit>(l);
          }
          case tlparen: {
            //consume lparen
            advance();

            TokenType curop = consume(ptoks->at(pos));
            //t = ptoks->at(pos);

            shared_ptr<Exp> e1 = make_shared<Parse::Exp>();
            e1 = parse();

            shared_ptr<Exp> e2 = make_shared<Parse::Exp>();
            e2 = parse();
            if(curop == tif) {
              shared_ptr<Exp> e3 = make_shared<Parse::Exp>();
              e3 = parse();
              Parse::Ifop o(e1, e2, e3);
              advance();
              return make_shared<Parse::Ifop>(o);
            } else {
              shared_ptr<Parse::Operator> o = Parse::instantiate_operator(curop, e1, e2);

              //consume lparen
              advance();

              return o;
            }
          }
          default:
          print_error("Unexpected token found. Exiting.\n");
          break;
        }
      } else {
        print_error("Error parsing, no tokens found.\n");
      }

      return nullptr;
    }
