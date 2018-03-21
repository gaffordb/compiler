#include <iostream>
#include "parser_driver.h"
#include <fstream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>


using namespace std;

int main(void) {
  ofstream myfile;
  myfile.open ("testinputerino.txt");
  myfile << "1 + 2";
  myfile.close();

  parser_driver driver ("testinputerino.txt");
  shared_ptr<Exp> expr = driver.parse(0);
  std::cout << expr->eval() << std::endl;
  return 0;
}
