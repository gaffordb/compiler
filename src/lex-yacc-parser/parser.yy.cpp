// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.yy.hpp"

// User implementation prologue.

#line 51 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 29 "src/lex-yacc-parser/parser.yy" // lalr1.cc:413

#include "parser_driver.h"
#include "lang.h"

using namespace std;

#line 60 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 127 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (parser_driver &driver_yyarg, shared_ptr<Exp> *ret_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg),
      ret (ret_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
      switch (that.type_get ())
    {
      case 42: // exp1
      case 43: // exp
        value.move<  shared_ptr<Exp>  > (that.value);
        break;

      case 44: // typ
        value.move<  shared_ptr<Typ>  > (that.value);
        break;

      case 38: // "vbool"
        value.move< bool > (that.value);
        break;

      case 39: // "var"
        value.move< const char* > (that.value);
        break;

      case 37: // "vint"
        value.move< int > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 42: // exp1
      case 43: // exp
        value.copy<  shared_ptr<Exp>  > (that.value);
        break;

      case 44: // typ
        value.copy<  shared_ptr<Typ>  > (that.value);
        break;

      case 38: // "vbool"
        value.copy< bool > (that.value);
        break;

      case 39: // "var"
        value.copy< const char* > (that.value);
        break;

      case 37: // "vint"
        value.copy< int > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 42: // exp1
      case 43: // exp
        yylhs.value.build<  shared_ptr<Exp>  > ();
        break;

      case 44: // typ
        yylhs.value.build<  shared_ptr<Typ>  > ();
        break;

      case 38: // "vbool"
        yylhs.value.build< bool > ();
        break;

      case 39: // "var"
        yylhs.value.build< const char* > ();
        break;

      case 37: // "vint"
        yylhs.value.build< int > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 96 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { *ret = yystack_[1].value.as<  shared_ptr<Exp>  > (); }
#line 556 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 3:
#line 97 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { }
#line 562 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 4:
#line 101 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EApp>(yystack_[1].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 568 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 5:
#line 102 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EFst>(yystack_[0].value.as<  shared_ptr<Exp>  > ());        }
#line 574 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 6:
#line 103 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ESnd>(yystack_[0].value.as<  shared_ptr<Exp>  > ());        }
#line 580 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 7:
#line 104 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { std::swap (yylhs.value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());                }
#line 586 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 8:
#line 107 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EVar>(yystack_[0].value.as< const char* > ());        }
#line 592 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 9:
#line 108 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ELit>(yystack_[0].value.as< int > ());        }
#line 598 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 10:
#line 109 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ELit>(yystack_[0].value.as< bool > ());        }
#line 604 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 11:
#line 110 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EUnit>();         }
#line 610 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 12:
#line 112 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ELet>(make_shared<EVar>(yystack_[6].value.as< const char* > ()), yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > (), yystack_[4].value.as<  shared_ptr<Typ>  > ());
                                     yylhs.value.as<  shared_ptr<Exp>  > ()->ctx.insert({yystack_[6].value.as< const char* > (), yystack_[4].value.as<  shared_ptr<Typ>  > ()});          }
#line 617 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 13:
#line 115 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EFun>(make_shared<EVar>(yystack_[7].value.as< const char* > ()), yystack_[0].value.as<  shared_ptr<Exp>  > (), yystack_[5].value.as<  shared_ptr<Typ>  > (), yystack_[2].value.as<  shared_ptr<Typ>  > ());
                                     yylhs.value.as<  shared_ptr<Exp>  > ()->ctx.insert({yystack_[7].value.as< const char* > (), yystack_[5].value.as<  shared_ptr<Typ>  > ()});          }
#line 624 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 14:
#line 118 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EFix>(yystack_[9].value.as< const char* > (), make_shared<EVar>(yystack_[7].value.as< const char* > ()), yystack_[0].value.as<  shared_ptr<Exp>  > (), yystack_[5].value.as<  shared_ptr<Typ>  > (), yystack_[2].value.as<  shared_ptr<Typ>  > ());
                                     yylhs.value.as<  shared_ptr<Exp>  > ()->ctx.insert({yystack_[9].value.as< const char* > (), make_shared<TFun>(yystack_[5].value.as<  shared_ptr<Typ>  > (), yystack_[2].value.as<  shared_ptr<Typ>  > ())});            //ctx for f
                                     yylhs.value.as<  shared_ptr<Exp>  > ()->ctx.insert({yystack_[7].value.as< const char* > (), yystack_[5].value.as<  shared_ptr<Typ>  > ()});          }
#line 632 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 15:
#line 121 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EPair>(yystack_[3].value.as<  shared_ptr<Exp>  > (), yystack_[1].value.as<  shared_ptr<Exp>  > ());   }
#line 638 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 16:
#line 122 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { std::swap (yylhs.value.as<  shared_ptr<Exp>  > (), yystack_[1].value.as<  shared_ptr<Exp>  > ());                }
#line 644 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 17:
#line 123 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EMult>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());   }
#line 650 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 18:
#line 124 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EDiv>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 656 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 19:
#line 125 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EMinus>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());  }
#line 662 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 20:
#line 126 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EPlus>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());   }
#line 668 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 21:
#line 127 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EIf>(yystack_[4].value.as<  shared_ptr<Exp>  > (), yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 674 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 22:
#line 128 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EWhile>(yystack_[3].value.as<  shared_ptr<Exp>  > (), yystack_[1].value.as<  shared_ptr<Exp>  > ());  }
#line 680 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 23:
#line 129 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ELeq>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 686 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 24:
#line 130 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EBigger>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 692 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 25:
#line 131 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ERef>(yystack_[0].value.as<  shared_ptr<Exp>  > ());        }
#line 698 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 26:
#line 132 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ESet>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 704 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 27:
#line 133 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EDeref>(yystack_[0].value.as<  shared_ptr<Exp>  > ());      }
#line 710 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 28:
#line 134 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ESeq>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 716 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 29:
#line 137 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TInt>();        }
#line 722 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 30:
#line 138 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TBool>();       }
#line 728 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 31:
#line 139 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TUnit>();       }
#line 734 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 32:
#line 140 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TFun>(yystack_[2].value.as<  shared_ptr<Typ>  > (), yystack_[0].value.as<  shared_ptr<Typ>  > ());  }
#line 740 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 33:
#line 141 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TPair>(yystack_[2].value.as<  shared_ptr<Typ>  > (), yystack_[0].value.as<  shared_ptr<Typ>  > ()); }
#line 746 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 34:
#line 142 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TRef>(yystack_[1].value.as<  shared_ptr<Typ>  > ());      }
#line 752 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;


#line 756 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -39;

  const signed char parser::yytable_ninf_ = -1;

  const short int
  parser::yypact_[] =
  {
     135,   -39,   561,   -38,   -13,   -23,   561,   -39,   561,   561,
     561,   561,   561,   -39,   -39,   -39,    22,   106,   -39,   209,
       4,    -9,    25,   172,   431,   -39,   -39,   590,   431,   246,
     -39,   -39,   561,   561,   561,   561,   561,   561,   561,   561,
     -39,   561,    51,    18,     5,   -39,   561,   561,   503,   503,
     532,   532,   468,   468,   431,   561,   283,    51,   -39,   -39,
     -39,    56,    51,    35,   320,   357,   561,    -1,    51,   561,
      51,     2,    51,   -39,   -39,   431,   -39,    46,   394,    -2,
      45,    26,   561,    51,    52,   431,     8,    51,   561,    43,
     431,   561,   431
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     3,     0,     0,     0,     0,     0,    11,     0,     0,
       0,     0,     0,     9,    10,     8,     0,     0,     7,     0,
       0,     0,     0,     0,     0,     5,     6,    27,    25,     0,
       1,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     0,     0,     0,     0,    16,     0,     0,    20,    19,
      17,    18,    23,    24,    28,    26,     0,     0,    29,    30,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    22,    21,    34,    33,     0,    32,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
      13,     0,    14
  };

  const short int
  parser::yypgoto_[] =
  {
     -39,   -39,    17,     0,   563
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    16,    24,    40,    61
  };

  const unsigned char
  parser::yytable_[] =
  {
      18,    20,    18,    68,    68,    21,    18,    68,    25,    26,
      18,    18,    18,    68,    70,    70,    22,    17,    70,    19,
      76,    80,    30,    23,    70,    88,    42,    27,    28,    29,
      43,    68,    18,    18,    18,    18,    18,    18,    18,    18,
      62,    18,    70,    44,    63,    84,    18,    18,    68,    48,
      49,    50,    51,    52,    53,    54,    55,    72,    56,    70,
      91,    68,    70,    64,    65,     0,    18,    83,     0,    18,
      69,    57,    70,     0,    87,    58,    59,    60,     0,     0,
       0,     0,    18,    75,     0,     0,    78,     0,    18,     0,
       0,    18,     0,     0,     0,     0,     0,     0,     0,    85,
       0,     0,     0,     0,     0,    90,    31,     0,    92,    32,
      33,    34,    35,     2,     0,     0,    36,     3,     4,     5,
       0,     0,     0,     0,     6,     0,     0,    37,     0,     7,
       0,     0,     0,     8,     9,     1,    38,    10,    39,    11,
      12,     0,     2,    13,    14,    15,     3,     4,     5,     0,
       0,     0,     0,     6,     0,     0,     0,     0,     7,     0,
       0,     0,     8,     9,     0,     0,    10,     0,    11,    12,
       0,     0,    13,    14,    15,    32,    33,    34,    35,     2,
       0,     0,    36,     3,     4,     5,     0,     0,     0,     0,
       6,    45,     0,    37,     0,     7,     0,     0,     0,     8,
       9,    46,    38,    10,    39,    11,    12,     0,     0,    13,
      14,    15,    32,    33,    34,    35,     2,    41,     0,    36,
       3,     4,     5,     0,     0,     0,     0,     6,     0,     0,
      37,     0,     7,     0,     0,     0,     8,     9,     0,    38,
      10,    39,    11,    12,     0,     0,    13,    14,    15,    32,
      33,    34,    35,     2,     0,     0,    36,     3,     4,     5,
       0,     0,     0,     0,     6,     0,     0,    37,     0,     7,
       0,     0,     0,     8,     9,     0,    38,    10,    39,    11,
      12,    47,     0,    13,    14,    15,    32,    33,    34,    35,
       2,     0,    66,    36,     3,     4,     5,     0,     0,     0,
       0,     6,     0,     0,    37,     0,     7,     0,     0,     0,
       8,     9,     0,    38,    10,    39,    11,    12,     0,     0,
      13,    14,    15,    32,    33,    34,    35,     2,     0,     0,
      36,     3,     4,     5,     0,     0,     0,     0,     6,    73,
       0,    37,     0,     7,     0,     0,     0,     8,     9,     0,
      38,    10,    39,    11,    12,     0,     0,    13,    14,    15,
      32,    33,    34,    35,     2,     0,     0,    36,     3,     4,
       5,     0,     0,     0,     0,     6,     0,     0,    37,     0,
       7,     0,     0,     0,     8,     9,     0,    38,    10,    39,
      11,    12,     0,    74,    13,    14,    15,    32,    33,    34,
      35,     2,     0,     0,    36,     3,     4,     5,     0,    82,
       0,     0,     6,     0,     0,    37,     0,     7,     0,     0,
       0,     8,     9,     0,    38,    10,    39,    11,    12,     0,
       0,    13,    14,    15,    32,    33,    34,    35,     2,     0,
       0,    36,     3,     4,     5,     0,     0,     0,     0,     6,
       0,     0,    37,     0,     7,     0,     0,     0,     8,     9,
       0,    38,    10,    39,    11,    12,     0,     0,    13,    14,
      15,    32,    33,    34,    35,     2,     0,     0,     0,     3,
       4,     5,     0,     0,     0,     0,     6,     0,     0,     0,
       0,     7,     0,     0,     0,     8,     9,     0,     0,    10,
      39,    11,    12,     0,     0,    13,    14,    15,    34,    35,
       2,     0,     0,     0,     3,     4,     5,     0,     0,     0,
       0,     6,     0,     0,     0,     0,     7,     0,     0,     0,
       8,     9,     0,     0,    10,    39,    11,    12,     0,     2,
      13,    14,    15,     3,     4,     5,     0,     0,     0,     0,
       6,     0,     0,     0,     0,     7,     0,     0,     0,     8,
       9,     0,     0,    10,    39,    11,    12,     0,     2,    13,
      14,    15,     3,     4,     5,     0,     0,     0,     0,     6,
       0,     0,     0,     0,     7,     0,     0,     0,     8,     9,
       0,     0,    10,     0,    11,    12,     0,     2,    13,    14,
      15,     3,     4,     5,     0,     0,     0,     0,     6,     0,
       0,     0,     0,     7,     0,     0,     0,     8,     9,     0,
      67,     0,     0,    11,    12,    71,     0,    13,    14,    15,
       0,    77,     0,    79,     0,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    86,     0,     0,     0,
      89
  };

  const signed char
  parser::yycheck_[] =
  {
       0,    39,     2,     5,     5,    18,     6,     5,     8,     9,
      10,    11,    12,     5,    16,    16,    39,     0,    16,     2,
      21,    19,     0,     6,    16,    17,    22,    10,    11,    12,
      39,     5,    32,    33,    34,    35,    36,    37,    38,    39,
      22,    41,    16,    18,    39,    19,    46,    47,     5,    32,
      33,    34,    35,    36,    37,    38,    39,    22,    41,    16,
      17,     5,    16,    46,    47,    -1,    66,    22,    -1,    69,
      14,    20,    16,    -1,    22,    24,    25,    26,    -1,    -1,
      -1,    -1,    82,    66,    -1,    -1,    69,    -1,    88,    -1,
      -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    -1,    -1,    88,     0,    -1,    91,     3,
       4,     5,     6,     7,    -1,    -1,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    23,
      -1,    -1,    -1,    27,    28,     0,    30,    31,    32,    33,
      34,    -1,     7,    37,    38,    39,    11,    12,    13,    -1,
      -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    27,    28,    -1,    -1,    31,    -1,    33,    34,
      -1,    -1,    37,    38,    39,     3,     4,     5,     6,     7,
      -1,    -1,    10,    11,    12,    13,    -1,    -1,    -1,    -1,
      18,    19,    -1,    21,    -1,    23,    -1,    -1,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    37,
      38,    39,     3,     4,     5,     6,     7,     8,    -1,    10,
      11,    12,    13,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      21,    -1,    23,    -1,    -1,    -1,    27,    28,    -1,    30,
      31,    32,    33,    34,    -1,    -1,    37,    38,    39,     3,
       4,     5,     6,     7,    -1,    -1,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    23,
      -1,    -1,    -1,    27,    28,    -1,    30,    31,    32,    33,
      34,    35,    -1,    37,    38,    39,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    21,    -1,    23,    -1,    -1,    -1,
      27,    28,    -1,    30,    31,    32,    33,    34,    -1,    -1,
      37,    38,    39,     3,     4,     5,     6,     7,    -1,    -1,
      10,    11,    12,    13,    -1,    -1,    -1,    -1,    18,    19,
      -1,    21,    -1,    23,    -1,    -1,    -1,    27,    28,    -1,
      30,    31,    32,    33,    34,    -1,    -1,    37,    38,    39,
       3,     4,     5,     6,     7,    -1,    -1,    10,    11,    12,
      13,    -1,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,
      23,    -1,    -1,    -1,    27,    28,    -1,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,     3,     4,     5,
       6,     7,    -1,    -1,    10,    11,    12,    13,    -1,    15,
      -1,    -1,    18,    -1,    -1,    21,    -1,    23,    -1,    -1,
      -1,    27,    28,    -1,    30,    31,    32,    33,    34,    -1,
      -1,    37,    38,    39,     3,     4,     5,     6,     7,    -1,
      -1,    10,    11,    12,    13,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    21,    -1,    23,    -1,    -1,    -1,    27,    28,
      -1,    30,    31,    32,    33,    34,    -1,    -1,    37,    38,
      39,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      12,    13,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    27,    28,    -1,    -1,    31,
      32,    33,    34,    -1,    -1,    37,    38,    39,     5,     6,
       7,    -1,    -1,    -1,    11,    12,    13,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      27,    28,    -1,    -1,    31,    32,    33,    34,    -1,     7,
      37,    38,    39,    11,    12,    13,    -1,    -1,    -1,    -1,
      18,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    27,
      28,    -1,    -1,    31,    32,    33,    34,    -1,     7,    37,
      38,    39,    11,    12,    13,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    27,    28,
      -1,    -1,    31,    -1,    33,    34,    -1,     7,    37,    38,
      39,    11,    12,    13,    -1,    -1,    -1,    -1,    18,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    27,    28,    -1,
      57,    -1,    -1,    33,    34,    62,    -1,    37,    38,    39,
      -1,    68,    -1,    70,    -1,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,
      87
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     0,     7,    11,    12,    13,    18,    23,    27,    28,
      31,    33,    34,    37,    38,    39,    41,    42,    43,    42,
      39,    18,    39,    42,    42,    43,    43,    42,    42,    42,
       0,     0,     3,     4,     5,     6,    10,    21,    30,    32,
      43,     8,    22,    39,    18,    19,    29,    35,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    20,    24,    25,
      26,    44,    22,    39,    42,    42,     9,    44,     5,    14,
      16,    44,    22,    19,    36,    42,    21,    44,    42,    44,
      19,    44,    15,    22,    19,    42,    44,    22,    17,    44,
      42,    17,    42
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    40,    41,    41,    42,    42,    42,    42,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    44,
      44,    44,    44,    44,    44
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     8,    10,    11,     5,     3,     3,     3,     3,
       3,     6,     5,     3,     3,     2,     3,     2,     3,     1,
       1,     1,     3,     3,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"eof\"", "error", "$undefined", "\"+\"", "\"-\"", "\"*\"", "\"/\"",
  "\"if\"", "\"then\"", "\"else\"", "\"<=\"", "\"let\"", "\"fun\"",
  "\"fix\"", "\"=\"", "\"in\"", "\"->\"", "\"|->\"", "\"(\"", "\")\"",
  "\"<\"", "\">\"", "\":\"", "\"()\"", "\"int\"", "\"bool\"", "\"unit\"",
  "\"fst\"", "\"snd\"", "\" . \"", "\";\"", "\"#\"", "\":=\"", "\"ref\"",
  "\"while\"", "\"do\"", "\"end\"", "\"vint\"", "\"vbool\"", "\"var\"",
  "$accept", "prog", "exp1", "exp", "typ", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    96,    96,    97,   101,   102,   103,   104,   107,   108,
     109,   110,   111,   114,   117,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   137,
     138,   139,   140,   141,   142
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1285 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:1167
#line 144 "src/lex-yacc-parser/parser.yy" // lalr1.cc:1168


// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const std::string &m) { driver.error(m); }
