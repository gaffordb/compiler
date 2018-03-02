#include "parser_driver.h"

parser_driver::parser_driver(const std::string &f) : file(f) { }

parser_driver::~parser_driver() { }

shared_ptr<Exp> parser_driver::parse() {
    scan_begin();
    shared_ptr<Exp> ret;
    yy::parser parser (*this, &ret);
    parser.set_debug_level(0);
    result = parser.parse();
    scan_end();
    return ret;
}

void parser_driver::error (const std::string &m) {
    std::cerr << m << std::endl;
}

