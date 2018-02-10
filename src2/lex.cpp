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

using namespace std;

//constructor for char-based tokens
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

std::ostream& operator<<(std::ostream &strm, Token const& token) {
  switch(token.type) {
    case tlparen:
    case trparen:
    case tplus: {
      strm << token.data.ch;
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
    default: fprintf(stderr, "Invalid token type");
    exit(EXIT_FAILURE);
  }
  return strm;
}

shared_ptr<vector<Token> > Token::lex(std::ifstream& in) {
  vector<Token> vec;
  shared_ptr<vector<Token> > toklist_ptr = make_shared<vector<Token> >(vec);
  while(!in.eof()) {
    char cur = in.get();
    //dealin' with numbers
    if(isdigit(cur)) {
      string num;
      while(isdigit(cur)) {
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
        default:
        //whitespace, advance cur
        break;
      }
    }
  }
  return toklist_ptr;
}
