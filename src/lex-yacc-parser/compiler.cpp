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

int main(int argc, char **argv) {
  int c;
  bool blex = false;
  bool bparse = false;
  bool step = false;
  if(argc < 2) {
    printf("usage: compiler <filename>\n");
    exit(1);
  }
  while(1) {
    static struct option long_options[] =
    {
      {"lex", no_argument, NULL, 'l'},
      {"parse", no_argument, NULL, 'p'},
      {"help", no_argument, NULL, 'h'},
      {"step", no_argument, NULL, 's'}
    };

    int option_index = 0;
    c = getopt_long (argc, argv, "::l::p::h::s", long_options, &option_index);

    if(c != -1) {
      switch(c) {
        case 'h': {
          printf("Usage: compiler [flags] [args]\n");
          printf("Available flags:\n--parse\tprints the output from parsing.\n");
          printf("--lex\tprints the output from lexing.\n");
          printf("--help\tdisplays program usage information.\n");
          return 0;
          break;
        }
        case 'l': {
          blex = true;
          //lex
          break;
        }
        case 'p': {
          bparse = true;
          //parse
          break;
        }
        case 's': {
          step = true;
          break;
        }
        case '?': {
          break;
        }
        default:
        abort();
      }
    }
    parser_driver driver (argv[optind]);
    shared_ptr<Exp> expr = driver.parse(blex);
    if(bparse){
      std::cout << expr << std::endl;
      return 0;
    }
    std::cout << expr->eval() << std::endl;
    return 0;
  }
}
