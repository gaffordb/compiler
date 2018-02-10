#include <iostream>
#include <fstream>
#include "parse.h"

using namespace std;
using namespace Parse;

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("usage: driver <filename>");
  }
  ifstream infile;
  infile.open(argv[1]);
  if(infile.is_open()){
    shared_ptr<vector<Token> > toklist_ptr = Token::lex(infile);
    Parser p(toklist_ptr);
    shared_ptr<Exp> e(p.parse());
    cout << e->interpret() << endl;
    infile.close();
  }
}
