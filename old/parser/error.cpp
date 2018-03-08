#include<stdio.h>
#include<string>
#include "error.h"

void print_error(std::string error_message) {
  fprintf(stderr, "%s\n", error_message.c_str());
  exit(EXIT_FAILURE);
}
