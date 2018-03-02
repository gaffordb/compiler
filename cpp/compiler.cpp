#include <iostream>
#include "parser_driver.h"

int main(int argc, char *argv[]) {
    parser_driver driver (argv[1]);
    shared_ptr<Exp> prog = driver.parse();
    std::cout << prog->eval() << std::endl;
}
