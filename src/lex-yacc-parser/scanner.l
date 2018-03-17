%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "parser_driver.h"
# include "parser.yy.hpp"
#include <stdbool.h>
#include <string.h>
#define DEBUG_MODE true
// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1
%}

%option noyywrap nounput batch debug noinput nodefault

int   [0-9]+
bool  (#)(t|f)
blank [ \t]
%%
{blank}+    { }
[\n]+       { }

"+"         { if(DEBUG_MODE) {printf("token: |+|\n");}
              return yy::parser::make_PLUS();     }
"-"         { if(DEBUG_MODE) {printf("token: |-|\n");}
              return yy::parser::make_MINUS();    }
"/"         { if(DEBUG_MODE) {printf("token: |/|\n");}
              return yy::parser::make_DIVIDE();   }
"*"         { if(DEBUG_MODE) {printf("token: |*|\n");}
              return yy::parser::make_MULTIPLY(); }
"if"        { if(DEBUG_MODE) {printf("token: |if|\n");}
              return yy::parser::make_IF();       }
"then"      { if(DEBUG_MODE) {printf("token: |then|\n");}
              return yy::parser::make_THEN();     }
"else"      { if(DEBUG_MODE) {printf("token: |else|\n");}
              return yy::parser::make_ELSE();     }
"<="        { if(DEBUG_MODE) {printf("token: |<=|\n");}
              return yy::parser::make_LEQUAL();   }
"let"       { if(DEBUG_MODE) {printf("token: |let|\n");}
              return yy::parser::make_LET();      }
"fun"       { if(DEBUG_MODE) {printf("token: |fun|\n");}
              return yy::parser::make_FUN();      }
"fix"       { if(DEBUG_MODE) {printf("token: |fix|\n");}
              return yy::parser::make_FIX();      }
"="         { if(DEBUG_MODE) {printf("token: |=|\n");}
              return yy::parser::make_EQUALS();   }
"in"        { if(DEBUG_MODE) {printf("token: |in|\n");}
              return yy::parser::make_IN();       }
"->"        { if(DEBUG_MODE) {printf("token: |->|\n");}
              return yy::parser::make_RARROW();   }
"("         { if(DEBUG_MODE) {printf("token: |(|\n");}
              return yy::parser::make_LPAREN();   }
")"         { if(DEBUG_MODE) {printf("token: |)|\n");}
              return yy::parser::make_RPAREN();   }
">"         { if(DEBUG_MODE) {printf("token: |>|\n");}
              return yy::parser::make_BIGGER();   }

[a-zA-Z][a-zA-Z0-9]* {
  const char *yycopy = strdup(yytext);
  if(DEBUG_MODE) {printf("token: %s\n", yycopy);}
  return yy::parser::make_VAR(yycopy);
}

<<EOF>> {
  return yy::parser::make_END();
}

{bool} {
  bool b = false;
  if(strcmp(yytext, "#t") == 0) {
    b = true;
  } else if(strcmp(yytext, "#f") == 0) {
    b = false;
  } else {
    driver.error("invalid character in bool");
  }
  if(DEBUG_MODE) {printf("token: %d\n", b);}
  return yy::parser::make_BOOL(b);
}

{int} {
    errno = 0;
    long n = strtol (yytext, NULL, 10);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
        driver.error ("integer is out of range");
    }
    if(DEBUG_MODE) {printf("token: %ld\n", n);}
    return yy::parser::make_INT(n);
}
.	fprintf(stderr, "bad input character '%s' at line %d\n", yytext, yylineno);

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
