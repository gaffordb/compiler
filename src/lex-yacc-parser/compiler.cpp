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
    //g_stack_next_alloc = 0; //maybe not necessary
    parser_driver driver (argv[optind]);
    shared_ptr<Exp> expr = driver.parse(blex);
    //sleep(1);
    //printf("whatisgoinon");
    //std::cout << expr << std::endl;m
    //exit(1);
    //auto prog = driver.parse(0);
    if(bparse){
      std::cout << expr << std::endl;
      return 0;
    }
    std::cout << expr->eval() << std::endl;
    return 0;
  }
}
/*
ifstream infile;
infile.open(argv[optind]);
if(infile.is_open()){
shared_ptr<vector<Token> > toklist_ptr = Token::lex(infile);
if(blex && !bparse) {
cout << string_of_token_list(toklist_ptr) << endl;
return 0;
} else if(bparse) {
//cout << string_of_exp_list(explist_ptr) << endl;
}
Parser p(toklist_ptr);
shared_ptr<Exp> e(p.parse());
cout << e->interpret() << endl;
infile.close();
} else {
print_error("Error. File not found.");
}
return 0;
}
*/
