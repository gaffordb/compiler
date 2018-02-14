#include "parse.h"
#include "error.h"
#include <string>

using namespace std;

Parse::Lit::Lit(string data) {
  if(data.at(0) == 't') {
    this->data = "true";
  } else if(data.at(0) == 'f') {
    this->data = "false";
  } else {
    this->data = data;
  }
}

Parse::Ifop::Ifop(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2,
  std::shared_ptr<Exp> e3) {
    this->e1 = e1;
    this->e2 = e2;
    this->e3 = e3;
  }

  Parse::Plus::Plus(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2) {
    this->e1 = e1;
    this->e2 = e2;
  }

  Parse::Minus::Minus(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2) {
    this->e1 = e1;
    this->e2 = e2;
  }

  Parse::Divide::Divide(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2) {
    this->e1 = e1;
    this->e2 = e2;
  }

  Parse::Multiply::Multiply(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2) {
    this->e1 = e1;
    this->e2 = e2;
  }

  Parse::Lequal::Lequal(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2) {
    this->e1 = e1;
    this->e2 = e2;
  }

  std::string Parse::Operator::interpret(void) {
    print_error("This should not happen. Trying to interpret raw op.\n");
    return "exit() in print_error, so this can't be reached...";
  }

  bool Parse::validInt(string& s) {
    return isdigit(s.at(0)) || s.at(0) == '-';
  }
  bool Parse::validBool(string& s) {
    return (s.at(0) == 't' || s.at(0) == 'f');
  }

  std::string Parse::Plus::interpret(void) {
    std::string val1 = this->e1->interpret();
    std::string val2 = this->e2->interpret();

    if(validInt(val1) && validInt(val2)) {
      return to_string((stoi(val1) + stoi(val2)));
    } else {
      print_error("Error. Cannot add boolean expression(s).\n");
      return "";
    }
  }

  std::string Parse::Minus::interpret(void) {
    std::string val1 = this->e1->interpret();
    std::string val2 = this->e2->interpret();

    if(validInt(val1) && validInt(val2)) {
      return to_string((stoi(val1) - stoi(val2)));
    } else {
      print_error("Error. Cannot subtract boolean expression(s).\n");
      return "";
    }
  }

  std::string Parse::Multiply::interpret(void) {
    std::string val1 = this->e1->interpret();
    std::string val2 = this->e2->interpret();

    if(validInt(val1) && validInt(val2)) {
      return to_string((stoi(val1) * stoi(val2)));
    } else {
      print_error("Error. Cannot multiply boolean expression(s).\n");
      return "";
    }
  }

  std::string Parse::Divide::interpret(void) {
    std::string val1 = this->e1->interpret();
    std::string val2 = this->e2->interpret();

    if(validInt(val1) && validInt(val2)) {
      if(stoi(val2) == 0) {
        print_error("Error. Cannot divide by zero.\n");
      }
      return to_string((stoi(val1) / stoi(val2)));
    } else {
      print_error("Error. Cannot add boolean expression(s).\n");
      return "";
    }
  }

  std::string Parse::Ifop::interpret(void) {
    string val1 = this->e1->interpret();
    string val2 = this->e2->interpret();
    string val3 = this->e3->interpret();
    bool cond;
    if(validBool(val1)) {
      cond = val1.at(0) == 't';
    } else {
      print_error("Error. Invalid argument(s) to if.\n");
    }
    if((validInt(val2) || validBool(val2)) && (validInt(val3) || validBool(val3))) {
      return cond ? val2 : val3;
    }
    else {
      print_error("Error. Invalid argument(s) to if.\n");
      return "";
    }
  }

  std::string Parse::Lequal::interpret(void) {
    string left = this->e1->interpret();
    string right = this->e2->interpret();

    if(validInt(left) && validInt(right)) {
      return (stoi(left) <= stoi(right)) ? "true" : "false";
    } else {
      print_error("Error. Cannot compare boolean expression(s).\n");
      return "";
    }
  }
  std::string Parse::Lit::interpret(void) {
    if(this->data.at(0) == 'f') {
      return "false";
    } else if(this->data.at(0) == 't') {
      return "true";
    } else {
      return this->data;
    }
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
        switch(t.type) {
          case tint: {
            advance();
            Parse::Lit l(to_string(t.data.i));
            return make_shared<Parse::Lit>(l);
          }
          case tbool: {
            advance();
            Parse::Lit l(string(1, t.data.ch));
            return make_shared<Parse::Lit>(l);
          }
          case tlparen: {
            //consume lparen
            advance();

            TokenType curop = consume(ptoks->at(pos));

            shared_ptr<Exp> e1 = make_shared<Parse::Exp>();
            e1 = parse();

            shared_ptr<Exp> e2 = make_shared<Parse::Exp>();
            e2 = parse();

            if(curop == tif) {
              shared_ptr<Exp> e3 = make_shared<Parse::Exp>();
              e3 = parse();
              Parse::Ifop o(e1, e2, e3);

              //consume lparen
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
