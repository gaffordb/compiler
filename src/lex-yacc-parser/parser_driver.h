#pragma once

#include <string>
#include <map>
#include <memory>
#include "lang.h"
#include "parser.yy.hpp"

#define YY_DECL yy::parser::symbol_type yylex (parser_driver &driver)

YY_DECL;

class parser_driver {
public:
    parser_driver(const std::string &f);
    virtual ~parser_driver();

    std::string file;
    int result;

    //debug param: 0 for no debug info, > 0 for debug
    shared_ptr<Exp> parse(int debug);

    void error(const yy::parser::location_type &l, const std::string &m);

    // NOTE: Implemented in scanner.l
    void scan_begin();
    void scan_end();
};
