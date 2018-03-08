#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <vector>
#include <fstream>
#include "lex.h"
#include "error.h"

using namespace std;

//constructor for char-based and bool-based tokens
Token::Token(TokenType t, char ch) {
  this->type = t;
  this->data.ch = ch;
}

//constructor for int-based tokens
Token::Token(TokenType t, int n) {
  this->type = t;
  this->data.i = n;
}

//constructor for float-based tokens
Token::Token(TokenType t, float f) {
  this->type = t;
  this->data.f = f;
}

bool isOperator(Token& t) {
  TokenType type = t.type;
  return type == tplus
  || type == tminus
  || type == tmult
  || type == tdiv
  || type == tif
  || type == tlequal;
}

std::ostream& operator<<(std::ostream &strm, Token const& token) {
  switch(token.type) {
    case tminus:
    case tmult:
    case tdiv:
    case tlparen:
    case trparen:
    case tplus: {
      strm << token.data.ch;
      break;
    }
    case tif: {
      strm << "if";
      break;
    }
    case tlequal: {
      strm << "<=";
      break;
    }
    case tfloat: {
      strm << token.data.f;
      break;
    }
    case tint: {
      strm << token.data.i;
      break;
    }
    case tbool: {
      strm << token.data.b;
      break;
    }
    print_error("Invalid token type. Exiting.\n");
  }
  return strm;
}

shared_ptr<vector<Token> > Token::lex(std::ifstream& in) {
  vector<Token> vec;
  shared_ptr<vector<Token> > toklist_ptr = make_shared<vector<Token> >(vec);
  while(1) {
    char cur = in.get();
    if(in.eof()) {
      return toklist_ptr;
    }
    if(isdigit(cur)) {
      string num;

      //read the rest of the number
      while(!in.eof() && isdigit(cur)) {
        num += cur;
        cur = in.get();
      }

      in.unget();
      toklist_ptr->push_back(Token(tint, atoi(num.c_str())));

      //dealin' with everything else
    } else {
      switch(cur) {
        case '(': {
          toklist_ptr->push_back(Token(tlparen, '('));
          break;
        }
        case ')': {
          toklist_ptr->push_back(Token(trparen, ')'));
          break;
        }
        case '+': {
          toklist_ptr->push_back(Token(tplus, '+'));
          break;
        }
        case '*': {
          toklist_ptr->push_back(Token(tmult, '*'));
          break;
        }
        case '/': {
          toklist_ptr->push_back(Token(tdiv, '/'));
          break;
        }
        case '-': {
          toklist_ptr->push_back(Token(tminus, '-'));
          break;
        }

        //true token
        case 't': {
          if(in.get() == 'r'
          && in.get() == 'u'
          && in.get() == 'e') {
            toklist_ptr->push_back(Token(tbool, 't'));
            break;
          } else {
            print_error("Unexpected character sequence. Exiting.\n");
          }
        }

        //false token
        case 'f': {
          if(in.get() == 'a'
          && in.get() == 'l'
          && in.get() == 's'
          && in.get() == 'e') {
            toklist_ptr->push_back(Token(tbool, 'f'));
            break;
          } else {
            print_error("Unexpected character sequence. Exiting.\n");
          }
        }

        //if token
        case 'i': {
          if(in.get() == 'f') {
            toklist_ptr->push_back(Token(tif, '?'));
            break;
          } else {
            in.unget();
            print_error("Unexpected character sequence. Exiting.\n");
          }
        }

        //lequal token
        case '<': {
          if(in.get() == '=') {
            toklist_ptr->push_back(Token(tlequal, '<'));
            break;
          } else { //THIS NEEDS TO BE CHANGED IF '<' gets added to language
          in.unget();
          print_error("Unexpected character sequence. Exiting.\n");
        }
      }
      case ' ':
      case '\t':
      case '\r':
      case '\n':
      //whitespace, advance cur
      break;
      default:
      print_error("Unexpected character sequence. Exiting.\n");
      break;
    }
  }
}
return toklist_ptr;
}
