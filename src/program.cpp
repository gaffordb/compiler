#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

using namespace std;

int main(int argc, char **argv) {
  int c;
  bool blength = false;

  while(1) {
  static struct option long_options[] = 
    {
      {"help", no_argument, NULL, 'h'},
      {"length", no_argument, NULL, 'l'}
    };

  int option_index = 0;
  c = getopt_long (argc, argv, "h::l::", long_options, &option_index);
  
  if(c != -1) {
    switch(c) {
    case 'h':
      printf("Usage: %s, [flags] [args]\n", argv[0]);
      printf("Available flags:\n-length\tprints the lengths");
      printf(" of each of the arguments\n");
      printf("-help\tprints the help message\n");
      return 0;
      break;
    case 'l':
      blength = true;
      break;
    case '?':
      break;
    default:
      abort();
    }
  }
  for(int i = optind; i < argc; i++) {
    string output = string(argv[i]);
    cout << (blength ? to_string(output.length()) : output);
    cout << endl;
  }
  return 0;
  }
}
