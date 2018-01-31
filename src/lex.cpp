#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

using namespace std;

class Token {
public: String data;

};
class LParenToken {
  data = "(";
};

class RParenToken {
  data = ")";
};

class OperatorToken {

};

class intToken {

};

typedef struct tokenList {
  Token data;
  tokenList_t *next;
} tokenList_t;

int main(int argc, char **argv) {
  return 0;
}
