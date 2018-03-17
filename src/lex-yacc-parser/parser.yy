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
  LET         "let"
  FUN         "fun"
  FIX         "fix"
  EQUALS      "="
  IN          "in"
  RARROW      "->"
  LPAREN      "("
  RPAREN      ")"
  BIGGER      ">"
;

%token <int> INT "int"
%token <bool> BOOL "bool"
%token <const char*> VAR "var"
%type  < shared_ptr<Exp> > exp
%type  < shared_ptr<Exp> > exp1
%parse-param {shared_ptr<Exp> *ret}

%%

%start prog;

prog:
  exp1 "eof"                  { *ret = $1; }
| "eof"                       { printf("Poppin!\n"); exit(1);}


exp1:
  exp1 exp                         { $$ = make_shared<EApp>($1, $2);    }
| exp                              { std::swap ($$, $1);                }

exp:
  "var"                            { $$ = make_shared<EVar>($1);        }
| "int"                            { $$ = make_shared<ELit>($1);        }
| "bool"                           { $$ = make_shared<ELit>($1);        }
| "let" "var" "=" exp1 "in" exp1   { $$ = make_shared<ELet>(make_shared<EVar>($2), $4, $6); }
| "fun" "var" "->" exp1            { $$ = make_shared<EFun>(make_shared<EVar>($2), $4); }
| "fix" "var" "var" "->" exp       {
  shared_ptr<Exp> fexp = make_shared<EFun>(make_shared<EVar>($3), $5);
  fexp->subst(fexp->eval(), $2);
  $$ = fexp;
}
| "(" exp1 ")"                     { std::swap ($$, $2);                }
|  exp1 "+" exp1                   { $$ = make_shared<EPlus>($1, $3);   }
|  exp1 "*" exp1                   { $$ = make_shared<EMult>($1, $3);   }
|  "if" exp1 "then" exp1 "else" exp1  { $$ = make_shared<EIf>($2, $4, $6); }
|  exp1 "<=" exp1                  { $$ = make_shared<ELeq>($1, $3);    }
|  exp1 ">" exp1                   { $$ = make_shared<EBigger>($1, $3); }
|  exp1 "-" exp1                   { $$ = make_shared<EMinus>($1, $3);  }
|  exp1 "/" exp1                   { $$ = make_shared<EDiv>($1, $3);    }


%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const std::string &m) { driver.error(m); }
