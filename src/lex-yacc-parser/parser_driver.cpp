#include "parser_driver.h"

parser_driver::parser_driver(const std::string &f) : file(f) { }

parser_driver::~parser_driver() { }

shared_ptr<Exp> parser_driver::parse(int debug) {
    scan_begin();
    //instantiate to deal with no expression case
    shared_ptr<Exp> ret = make_shared<EVar>("");
    yy::parser parser (*this, &ret);

    parser.set_debug_level(debug);
    result = parser.parse();
    scan_end();
    return ret;
}

void parser_driver::error (const std::string &m) {
    std::cerr << m << std::endl;
}
