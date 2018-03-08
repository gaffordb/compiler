%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "parser_driver.h"
# include "parser.yy.hpp"
#include <stdbool.h>
#include <string.h>

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1
%}

%option noyywrap nounput batch debug noinput

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
bool  (#)(t|f)
blank [ \t]

%%

{blank}+    { }
[\n]+       { }

//"eof"       { exit(0); }
"+"         { return yy::parser::make_PLUS(); }
"-"         { return yy::parser::make_MINUS(); }
"/"         { return yy::parser::make_DIVIDE(); }
"*"         { return yy::parser::make_MULTIPLY(); }
"if"        { return yy::parser::make_IF(); }
"then"      { return yy::parser::make_THEN(); }
"else"      { return yy::parser::make_ELSE(); }
"<="        { return yy::parser::make_LEQUAL(); }
"("         { return yy::parser::make_LPAREN(); }
")"         { return yy::parser::make_RPAREN(); }

{bool} {
  bool b;
  if(strcmp(yytext, "#t") == 0) {
    b = true;
  } else if(strcmp(yytext, "#f") == 0) {
    b = false;
  } else {
    driver.error("invalid character in bool");
  }
  return yy::parser::make_BOOL(b);
}

{int} {
    errno = 0;
    long n = strtol (yytext, NULL, 10);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
        driver.error ("integer is out of range");
    }
    return yy::parser::make_INT(n);
}
.          { driver.error ("invalid character in int"); }
<<EOF>>    { return yy::parser::make_END(); }
%%

void parser_driver::scan_begin () {
    yy_flex_debug = 0;
    if (file.empty () || file == "-") {
        yyin = stdin;
    } else if (!(yyin = fopen (file.c_str (), "r"))) {
        error ("cannot open " + file + ": " + strerror(errno));
        exit (EXIT_FAILURE);
    }
}
void parser_driver::scan_end () {
    fclose (yyin);
}
