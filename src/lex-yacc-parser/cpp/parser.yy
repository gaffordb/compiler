%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"
%defines
%define parser_class_name {parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#ifndef YY_NULLPTR
  #define YY_NULLPTR nullptr
#endif
#include <string>
#include <memory>
#include "lang.h"
#include <stdbool.h>
class parser_driver;
using namespace std;
}

// The parsing context
%param { parser_driver &driver }

%define parse.trace
%define parse.error verbose

%code {
#include "parser_driver.h"
#include "lang.h"

using namespace std;
}

%define api.token.prefix {TOK_}
%token
  END     0   "eof"
  PLUS        "+"
  MINUS       "-"
  MULTIPLY    "*"
  DIVIDE      "/"
  IF          "if"
  THEN        "then"
  ELSE        "else"
  LEQUAL      "<="
  LPAREN      "("
  RPAREN      ")"
;

%token <int> INT "int"
%token <bool> BOOL "bool"
%type  < shared_ptr<Exp> > exp
%parse-param {shared_ptr<Exp> *ret}

%%

%start prog;

prog:
  exp "eof"                  { *ret = $1; }

exp:
  "int"                      { $$ = make_shared<ELit>($1);        }
|  "bool"                    { $$ = make_shared<ELit>($1);        }
| "(" exp ")"                { std::swap ($$, $2);                }
|  exp "+" exp               { $$ = make_shared<EPlus>($1, $3);   }
|  exp "*" exp               { $$ = make_shared<EMult>($1, $3);   }
|  "if" exp "then" exp "else" exp    { $$ = make_shared<EIf>($2, $4, $6); }
|  exp "<=" exp              { $$ = make_shared<ELeq>($1, $3);    }
|  exp "-" exp               { $$ = make_shared<EMinus>($1, $3);  }
|  exp "/" exp               { $$ = make_shared<EDiv>($1, $3);    }
%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const std::string &m) { driver.error(m); }
