%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "parser_driver.h"
# include "parser.yy.hpp"
#include <stdbool.h>
#include <string.h>
#define DEBUG_MODE false
// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.

//CREDIT TO:
//https://stackoverflow.com/questions/34493467/how-to-handle-nested-comment-in-flex
//for help w/ multiline comments

# undef yywrap
# define yywrap() 1
static yy::location loc;
%}

%option noyywrap nounput batch debug noinput nodefault


int   [-]*[0-9]+
bool  (#)(t|f)
blank [ \t]
%x IN_COMMENT

%{
  #define YY_USER_ACTION  loc.columns (yyleng);
%}

%%
  int comment_nesting = 0;

%{
  loc.step();
%}

<INITIAL>{
"/*"      {BEGIN(IN_COMMENT);}
}
<IN_COMMENT>{
  "/*"           { ++comment_nesting; }
  "*"+"/"        { if (comment_nesting) --comment_nesting;
                   else BEGIN(INITIAL); }
  "*"+           ;
  [^/*\n]+       ; /**/
  [/]            ;
  \n             ;
}

{blank}+    { loc.step(); }
[\n]+       { loc.lines(yyleng); loc.step(); }

"+"         { if(DEBUG_MODE) {printf("token: |+|\n");}
              return yy::parser::make_PLUS(loc);     }
"-"         { if(DEBUG_MODE) {printf("token: |-|\n");}
              return yy::parser::make_MINUS(loc);    }
"/"         { if(DEBUG_MODE) {printf("token: |/|\n");}
              return yy::parser::make_DIVIDE(loc);   }
"*"         { if(DEBUG_MODE) {printf("token: |*|\n");}
              return yy::parser::make_MULTIPLY(loc); }
"if"        { if(DEBUG_MODE) {printf("token: |if|\n");}
              return yy::parser::make_IF(loc);       }
"then"      { if(DEBUG_MODE) {printf("token: |then|\n");}
              return yy::parser::make_THEN(loc);     }
"else"      { if(DEBUG_MODE) {printf("token: |else|\n");}
              return yy::parser::make_ELSE(loc);     }
"<="        { if(DEBUG_MODE) {printf("token: |<=|\n");}
              return yy::parser::make_LEQUAL(loc);   }
">="        { if(DEBUG_MODE) {printf("token: |>=|\n");}
              return yy::parser::make_GEQUAL(loc);   }
"let"       { if(DEBUG_MODE) {printf("token: |let|\n");}
              return yy::parser::make_LET(loc);      }
"fun"       { if(DEBUG_MODE) {printf("token: |fun|\n");}
              return yy::parser::make_FUN(loc);      }
"fix"       { if(DEBUG_MODE) {printf("token: |fix|\n");}
              return yy::parser::make_FIX(loc);      }
"="         { if(DEBUG_MODE) {printf("token: |=|\n");}
              return yy::parser::make_EQUALS(loc);   }
"in"        { if(DEBUG_MODE) {printf("token: |in|\n");}
              return yy::parser::make_IN(loc);       }
"->"        { if(DEBUG_MODE) {printf("token: |->|\n");}
              return yy::parser::make_RARROW(loc);   }
"|->"        { if(DEBUG_MODE) {printf("token: ||->|\n");}
              return yy::parser::make_FARROW(loc);   }
"("         { if(DEBUG_MODE) {printf("token: |(|\n");}
              return yy::parser::make_LPAREN(loc);   }
")"         { if(DEBUG_MODE) {printf("token: |)|\n");}
              return yy::parser::make_RPAREN(loc);   }
"<"         { if(DEBUG_MODE) {printf("token: |<|\n");}
              return yy::parser::make_SMALLER(loc);   }
">"         { if(DEBUG_MODE) {printf("token: |>|\n");}
              return yy::parser::make_BIGGER(loc);   }
":"         { if(DEBUG_MODE) {printf("token: |:|\n");}
              return yy::parser::make_COLON(loc);   }
"()"        { if(DEBUG_MODE) {printf("token: |()|\n");}
              return yy::parser::make_UNIT(loc);   }
"int"       { if(DEBUG_MODE) {printf("token: |int|\n");}
              return yy::parser::make_INTTYPE(loc);   }
"bool"      { if(DEBUG_MODE) {printf("token: |bool|\n");}
              return yy::parser::make_BOOLTYPE(loc);   }
"unit"      { if(DEBUG_MODE) {printf("token: |unit|\n");}
              return yy::parser::make_UNITTYPE(loc);   }
"fst"       { if(DEBUG_MODE) {printf("token: |fst|\n");}
              return yy::parser::make_FIRST(loc);   }
"snd"       { if(DEBUG_MODE) {printf("token: |snd|\n");}
              return yy::parser::make_SECOND(loc);   }
" . "       { if(DEBUG_MODE) {printf("token: | . |\n");}
              return yy::parser::make_DOT(loc);   }
";"         { if(DEBUG_MODE) {printf("token: |;|\n");}
              return yy::parser::make_SEMICOLON(loc);   }
"#"         { if(DEBUG_MODE) {printf("token: |#|\n");}
              return yy::parser::make_POUNDO(loc);   }
":="        { if(DEBUG_MODE) {printf("token: |:=|\n");}
              return yy::parser::make_SETTER(loc);   }
"ref"       { if(DEBUG_MODE) {printf("token: |ref|\n");}
              return yy::parser::make_REF(loc);   }
"while"     { if(DEBUG_MODE) {printf("token: |while|\n");}
              return yy::parser::make_WHILE(loc);   }
"do"        { if(DEBUG_MODE) {printf("token: |do|\n");}
              return yy::parser::make_DO(loc);   }
"end"       { if(DEBUG_MODE) {printf("token: |end|\n");}
              return yy::parser::make_ENDL(loc);   }
"array"     { if(DEBUG_MODE) {printf("token: |array|\n");}
              return yy::parser::make_ARRAY(loc);   }
"new"       { if(DEBUG_MODE) {printf("token: |new|\n");}
              return yy::parser::make_NEW(loc);   }
"["         { if(DEBUG_MODE) {printf("token: |[|\n");}
              return yy::parser::make_LBRACK(loc);   }
"]"         { if(DEBUG_MODE) {printf("token: |]|\n");}
              return yy::parser::make_RBRACK(loc);   }
"{"         { if(DEBUG_MODE) {printf("token: |{|\n");}
              return yy::parser::make_CLBRACK(loc);   }
"}"         { if(DEBUG_MODE) {printf("token: |}|\n");}
              return yy::parser::make_CRBRACK(loc);   }
"{}"        { if(DEBUG_MODE) {printf("token: |{}|\n");}
              return yy::parser::make_NIL(loc);   }
"::"        { if(DEBUG_MODE) {printf("token: |::|\n");}
              return yy::parser::make_CONS(loc);   }
"car"       { if(DEBUG_MODE) {printf("token: |car|\n");}
              return yy::parser::make_CAR(loc);   }
"cdr"       { if(DEBUG_MODE) {printf("token: |cdr|\n");}
              return yy::parser::make_CDR(loc);   }
"empty?"    { if(DEBUG_MODE) {printf("token: |empty?|\n");}
              return yy::parser::make_EMPTY(loc);   }


[a-zA-Z][a-zA-Z0-9]* {
  const char *yycopy = strdup(yytext);
  if(DEBUG_MODE) {printf("token: %s\n", yycopy);}
  return yy::parser::make_VAR(yycopy, loc);
}

<<EOF>> {
  return yy::parser::make_END(loc);
}

{bool} {
  bool b = false;
  if(strcmp(yytext, "#t") == 0) {
    b = true;
  } else if(strcmp(yytext, "#f") == 0) {
    b = false;
  } else {
    driver.error(loc, "invalid character in bool");
  }
  if(DEBUG_MODE) {printf("token: %d\n", b);}
  return yy::parser::make_BOOL(b, loc);
}

{int} {
    errno = 0;
    long n = strtol (yytext, NULL, 10);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
        driver.error (loc, "integer is out of range");
    }
    if(DEBUG_MODE) {printf("token: %ld\n", n);}
    return yy::parser::make_INT(n, loc);
}
.	{ driver.error(loc, "invalid character"); }

%%

void parser_driver::scan_begin () {
    yy_flex_debug = 0;
    if (file.empty () || file == "-") {
        yyin = stdin;
    } else if (!(yyin = fopen (file.c_str (), "r"))) {
        error (loc, "cannot open " + file + ": " + strerror(errno));
        exit (EXIT_FAILURE);
    }
}
void parser_driver::scan_end () {
    fclose (yyin);
}
