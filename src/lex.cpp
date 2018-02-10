#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <vector>
#include <fstream>

using namespace std;

union TokenData {
  char ch;
  float f;
  int i;
};
enum TokenType {
  tlparen, trparen, tplus, tfloat, tint
};

class Token {
public:
  TokenType type;
  TokenData data;
  //tostring
  friend std::ostream& operator<<(std::ostream &strm, Token const& token) {
    switch(token.type) {
      case tlparen:
      case trparen:
      case tplus:
      strm << token.data.ch;
      break;
      case tfloat:
      strm << token.data.f;
      case tint:
      strm << token.data.i;
      default: fprintf(stderr, "Invalid token type");
      exit(EXIT_FAILURE);
    }
    return strm;
  }

  //constructor for char-based tokens
  Token(TokenType t, char ch) {
    this->type = t;
    this->data.ch = ch;
  }

  //constructor for int-based tokens
  Token(TokenType t, int n) {
    this->type = t;
    this->data.i = n;
  }

  //constructor for float-based tokens
  Token(TokenType t, float f) {
    this->type = t;
    this->data.f = f;
  }

};

shared_ptr<vector<Token> > lex(std::ifstream& in) {
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
    } else {
      switch(cur) {
        case '(':
        toklist_ptr->push_back(Token(tlparen, '('));
        break;
        case ')':
        toklist_ptr->push_back(Token(trparen, ')'));
        break;
        case '+':
        toklist_ptr->push_back(Token(tplus, '+'));
        break;
        default:
        //whitespace, advance cur
        break;
      }
    }
  }
  return toklist_ptr;
}

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("usage: driver <filename>");
  }
  ifstream infile;
  infile.open(argv[1]);
  if(infile.is_open()){
    shared_ptr<vector<Token> > toklist_ptr = lex(infile);
    for(int i = 0; i < toklist_ptr->size(); i++) {
      cout << toklist_ptr->at(i);
    }
    cout << endl;
    infile.close();
  }
}
