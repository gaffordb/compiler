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
#include <vector>

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
  FARROW      "|->"
  LPAREN      "("
  RPAREN      ")"
  SMALLER     "<"
  BIGGER      ">"
  COLON       ":"
  UNIT        "()"
  INTTYPE     "int"
  BOOLTYPE    "bool"
  UNITTYPE    "unit"
  FIRST       "fst"
  SECOND      "snd"
  DOT         " . "
  SEMICOLON   ";"
  POUNDO      "#"
  SETTER      ":="
  REF         "ref"
  WHILE       "while"
  DO          "do"
;

%token <int> INT "vint"
%token <bool> BOOL "vbool"
%token <const char*> VAR "var"

%right ";"
%left ">" "<="
%left "+" "-"
%left "*" "/"
%left ":="
%left "#"

%type  < shared_ptr<Exp> > exp
%type  < shared_ptr<Exp> > exp1
%type  < shared_ptr<Typ> > typ
%parse-param {shared_ptr<Exp> *ret}

%%

%start prog;

prog:
  exp1 "eof"                       { *ret = $1; }
| "eof"                            { }


exp1:
  exp1 exp                         { $$ = make_shared<EApp>($1, $2);    }
| "fst" exp                        { $$ = make_shared<EFst>($2);        }
| "snd" exp                        { $$ = make_shared<ESnd>($2);        }
| exp                              { std::swap ($$, $1);                }

exp:
  "var"                            { $$ = make_shared<EVar>($1);        }
| "vint"                           { $$ = make_shared<ELit>($1);        }
| "vbool"                          { $$ = make_shared<ELit>($1);        }
| "()"                             { $$ = make_shared<EUnit>();         }
| "let" "var" ":" typ "=" exp1 "in" exp1
                                   { $$ = make_shared<ELet>(make_shared<EVar>($2), $6, $8, $4);
                                     $$->ctx.insert({$2, $4});          }
| "fun" "(" "var" ":" typ ")" ":" typ "|->" exp1
                                   { $$ = make_shared<EFun>(make_shared<EVar>($3), $10, $5, $8);
                                     $$->ctx.insert({$3, $5});          }
| "fix" "var" "(" "var" ":" typ ")" ":" typ "|->" exp1
                                   { $$ = make_shared<EFix>($2, make_shared<EVar>($4), $11, $6, $9);
                                     $$->ctx.insert({$2, $9});
                                     $$->ctx.insert({$4, $6});          }
| "(" exp1 " . " exp1 ")"          { $$ = make_shared<EPair>($2, $4);   }
|  "(" exp1 ")"                    { std::swap ($$, $2);                }
|  exp1 "*" exp1                   { $$ = make_shared<EMult>($1, $3);   }
|  exp1 "/" exp1                   { $$ = make_shared<EDiv>($1, $3);    }
|  exp1 "-" exp1                   { $$ = make_shared<EMinus>($1, $3);  }
|  exp1 "+" exp1                   { $$ = make_shared<EPlus>($1, $3);   }
|  "if" exp1 "then" exp1 "else" exp1  { $$ = make_shared<EIf>($2, $4, $6); }
|  "while" exp1 "do" exp1          { $$ = make_shared<EWhile>($2, $4);  }
|  exp1 "<=" exp1                  { $$ = make_shared<ELeq>($1, $3);    }
|  exp1 ">" exp1                   { $$ = make_shared<EBigger>($1, $3); }
|  "ref" exp1                      { $$ = make_shared<ERef>($2);        }
|  exp1 ":=" exp1                  { $$ = make_shared<ESet>($1, $3);    }
|  "#" exp1                        { $$ = make_shared<EDeref>($2);      }
|  exp1 ";" exp1                   { $$ = make_shared<ESeq>($1, $3);    }

typ:
  "int"                            { $$ = make_shared<TInt>();        }
| "bool"                           { $$ = make_shared<TBool>();       }
| "unit"                           { $$ = make_shared<TUnit>();       }
| typ "->" typ                     { $$ = make_shared<TFun>($1, $3);  }
| typ "*" typ                      { $$ = make_shared<TPair>($1, $3); }
| "<" typ ">"                      { $$ = make_shared<TRef>($2);      }

%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const std::string &m) { driver.error(m); }
