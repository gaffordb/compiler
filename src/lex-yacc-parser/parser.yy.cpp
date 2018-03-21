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
#line 35 "src/lex-yacc-parser/parser.yy" // lalr1.cc:413

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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


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
#line 146 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:479

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
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 54: // exp1
      case 55: // exp
        value.move<  shared_ptr<Exp>  > (that.value);
        break;

      case 56: // typ
        value.move<  shared_ptr<Typ>  > (that.value);
        break;

      case 50: // "vbool"
        value.move< bool > (that.value);
        break;

      case 51: // "var"
        value.move< const char* > (that.value);
        break;

      case 49: // "vint"
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
      case 54: // exp1
      case 55: // exp
        value.copy<  shared_ptr<Exp>  > (that.value);
        break;

      case 56: // typ
        value.copy<  shared_ptr<Typ>  > (that.value);
        break;

      case 50: // "vbool"
        value.copy< bool > (that.value);
        break;

      case 51: // "var"
        value.copy< const char* > (that.value);
        break;

      case 49: // "vint"
        value.copy< int > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
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
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
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

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 28 "src/lex-yacc-parser/parser.yy" // lalr1.cc:745
{
  //empty
}

#line 462 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:745

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
      case 54: // exp1
      case 55: // exp
        yylhs.value.build<  shared_ptr<Exp>  > ();
        break;

      case 56: // typ
        yylhs.value.build<  shared_ptr<Typ>  > ();
        break;

      case 50: // "vbool"
        yylhs.value.build< bool > ();
        break;

      case 51: // "var"
        yylhs.value.build< const char* > ();
        break;

      case 49: // "vint"
        yylhs.value.build< int > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 116 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { *ret = yystack_[1].value.as<  shared_ptr<Exp>  > (); }
#line 593 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 3:
#line 117 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { }
#line 599 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 4:
#line 121 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EApp>(yystack_[1].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 605 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 5:
#line 122 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EFst>(yystack_[0].value.as<  shared_ptr<Exp>  > ());        }
#line 611 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 6:
#line 123 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ESnd>(yystack_[0].value.as<  shared_ptr<Exp>  > ());        }
#line 617 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 7:
#line 124 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { std::swap (yylhs.value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());                }
#line 623 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 8:
#line 127 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EVar>(yystack_[0].value.as< const char* > ());        }
#line 629 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 9:
#line 128 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ELit>(yystack_[0].value.as< int > ());        }
#line 635 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 10:
#line 129 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ELit>(yystack_[0].value.as< bool > ());        }
#line 641 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 11:
#line 130 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EUnit>();         }
#line 647 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 12:
#line 132 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ELet>(make_shared<EVar>(yystack_[6].value.as< const char* > ()), yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > (), yystack_[4].value.as<  shared_ptr<Typ>  > ());
                                     yylhs.value.as<  shared_ptr<Exp>  > ()->ctx.insert({yystack_[6].value.as< const char* > (), yystack_[4].value.as<  shared_ptr<Typ>  > ()});          }
#line 654 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 13:
#line 135 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EFun>(make_shared<EVar>(yystack_[7].value.as< const char* > ()), yystack_[0].value.as<  shared_ptr<Exp>  > (), yystack_[5].value.as<  shared_ptr<Typ>  > (), yystack_[2].value.as<  shared_ptr<Typ>  > ());
                                     yylhs.value.as<  shared_ptr<Exp>  > ()->ctx.insert({yystack_[7].value.as< const char* > (), yystack_[5].value.as<  shared_ptr<Typ>  > ()});          }
#line 661 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 14:
#line 138 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EFix>(yystack_[9].value.as< const char* > (), make_shared<EVar>(yystack_[7].value.as< const char* > ()), yystack_[0].value.as<  shared_ptr<Exp>  > (), yystack_[5].value.as<  shared_ptr<Typ>  > (), yystack_[2].value.as<  shared_ptr<Typ>  > ());
                                     yylhs.value.as<  shared_ptr<Exp>  > ()->ctx.insert({yystack_[9].value.as< const char* > (), make_shared<TFun>(yystack_[5].value.as<  shared_ptr<Typ>  > (), yystack_[2].value.as<  shared_ptr<Typ>  > ())});            //ctx for f
                                     yylhs.value.as<  shared_ptr<Exp>  > ()->ctx.insert({yystack_[7].value.as< const char* > (), yystack_[5].value.as<  shared_ptr<Typ>  > ()});          }
#line 669 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 15:
#line 141 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EPair>(yystack_[3].value.as<  shared_ptr<Exp>  > (), yystack_[1].value.as<  shared_ptr<Exp>  > ());   }
#line 675 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 16:
#line 142 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { std::swap (yylhs.value.as<  shared_ptr<Exp>  > (), yystack_[1].value.as<  shared_ptr<Exp>  > ());                }
#line 681 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 17:
#line 143 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EMult>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());   }
#line 687 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 18:
#line 144 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EDiv>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 693 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 19:
#line 145 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EMinus>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());  }
#line 699 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 20:
#line 146 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EPlus>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());   }
#line 705 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 21:
#line 147 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EIf>(yystack_[4].value.as<  shared_ptr<Exp>  > (), yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 711 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 22:
#line 148 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EWhile>(yystack_[3].value.as<  shared_ptr<Exp>  > (), yystack_[1].value.as<  shared_ptr<Exp>  > ());  }
#line 717 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 23:
#line 149 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ELeq>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 723 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 24:
#line 150 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EBigger>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ()); }
#line 729 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 25:
#line 151 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EGeq>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 735 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 26:
#line 152 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ESmaller>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());}
#line 741 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 27:
#line 153 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ERef>(yystack_[0].value.as<  shared_ptr<Exp>  > ());        }
#line 747 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 28:
#line 154 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ESet>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 753 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 29:
#line 155 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EDeref>(yystack_[0].value.as<  shared_ptr<Exp>  > ());      }
#line 759 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 30:
#line 156 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ESeq>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());    }
#line 765 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 31:
#line 157 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EArrRef>(yystack_[1].value.as<  shared_ptr<Exp>  > (), yystack_[3].value.as<  shared_ptr<Typ>  > ()); }
#line 771 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 32:
#line 158 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EArrGet>(yystack_[3].value.as<  shared_ptr<Exp>  > (), yystack_[1].value.as<  shared_ptr<Exp>  > ()); }
#line 777 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 33:
#line 159 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EList>(yystack_[0].value.as<  shared_ptr<Typ>  > ());        }
#line 783 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 34:
#line 160 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ECons>(yystack_[2].value.as<  shared_ptr<Exp>  > (), yystack_[0].value.as<  shared_ptr<Exp>  > ());   }
#line 789 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 35:
#line 161 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ECar>(yystack_[0].value.as<  shared_ptr<Exp>  > ());        }
#line 795 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 36:
#line 162 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<ECdr>(yystack_[0].value.as<  shared_ptr<Exp>  > ());        }
#line 801 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 37:
#line 163 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Exp>  > () = make_shared<EEmpty>(yystack_[0].value.as<  shared_ptr<Exp>  > ());      }
#line 807 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 38:
#line 166 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TInt>();        }
#line 813 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 39:
#line 167 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TBool>();       }
#line 819 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 40:
#line 168 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TUnit>();       }
#line 825 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 41:
#line 169 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TFun>(yystack_[2].value.as<  shared_ptr<Typ>  > (), yystack_[0].value.as<  shared_ptr<Typ>  > ());  }
#line 831 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 42:
#line 170 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TPair>(yystack_[2].value.as<  shared_ptr<Typ>  > (), yystack_[0].value.as<  shared_ptr<Typ>  > ()); }
#line 837 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 43:
#line 171 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TRef>(yystack_[1].value.as<  shared_ptr<Typ>  > ());      }
#line 843 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 44:
#line 172 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TArray>(yystack_[1].value.as<  shared_ptr<Typ>  > ());    }
#line 849 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;

  case 45:
#line 173 "src/lex-yacc-parser/parser.yy" // lalr1.cc:859
    { yylhs.value.as<  shared_ptr<Typ>  > () = make_shared<TList>(yystack_[1].value.as<  shared_ptr<Typ>  > ());     }
#line 855 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
    break;


#line 859 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:859
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
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
    yyerror_range[1].location = yystack_[yylen - 1].location;
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

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

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
    error (yyexc.location, yyexc.what());
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


  const signed char parser::yypact_ninf_ = -49;

  const signed char parser::yytable_ninf_ = -1;

  const short int
  parser::yypact_[] =
  {
     201,   -49,   930,   -48,   -15,   -46,   930,   -49,   930,   930,
     930,   930,   930,    -7,   -16,   930,   930,   930,   -49,   -49,
     -49,    21,   149,   -49,   299,    -1,   -28,     5,   250,   691,
     -49,   -49,  1020,   740,   348,    -7,   -49,   -49,   -49,     4,
      -7,    28,    -7,   691,   691,   691,   -49,   -49,   930,   930,
     930,   930,   930,   930,   930,   930,   930,   930,   930,   930,
     -49,   930,    -7,     6,   -24,   -49,   930,   930,    81,    -7,
      -4,    -7,    -7,   930,   108,   885,   885,   975,   975,   838,
     838,   838,   838,   691,   789,   397,   691,   446,    55,    -7,
       7,   495,   544,   -49,    89,   -49,    23,   108,   593,   -49,
     930,   930,    90,    -7,   -49,   -49,   -49,   -49,   691,   642,
      39,   100,   930,    -7,    40,   691,    29,    -7,   930,    91,
     691,   930,   691
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     3,     0,     0,     0,     0,     0,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     9,    10,
       8,     0,     0,     7,     0,     0,     0,     0,     0,     0,
       5,     6,    29,    27,     0,     0,    38,    39,    40,     0,
       0,     0,     0,    35,    36,    37,     1,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       4,     0,     0,     0,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,    33,    20,    19,    17,    18,    23,
      25,    26,    24,    30,    28,     0,    34,     0,     0,     0,
       0,     0,     0,    43,     0,    45,    42,    41,     0,    32,
       0,     0,     0,     0,    15,    22,    44,    31,    21,     0,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
      13,     0,    14
  };

  const signed char
  parser::yypgoto_[] =
  {
     -49,   -49,    26,     0,    62
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    21,    29,    60,    41
  };

  const unsigned char
  parser::yytable_[] =
  {
      23,    71,    23,    25,    26,    27,    23,    42,    30,    31,
      23,    23,    23,    72,    35,    23,    23,    23,    36,    37,
      38,    46,    62,    63,    64,    69,    22,    90,    24,    89,
     103,    39,    28,    71,    71,    40,    32,    33,    34,    95,
      72,    43,    44,    45,     0,    72,    72,   118,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      71,    23,   113,   117,     0,     0,    23,    23,    73,     0,
     101,     0,    72,    23,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    71,    87,     0,     0,
       0,     0,    91,    92,    71,    71,    71,    68,    72,    98,
      23,    23,    70,    93,    74,    71,    72,    72,    72,   121,
     110,   106,    23,    71,     0,     0,     0,    72,    23,     0,
     114,    23,     0,     0,    88,    72,   108,   109,     0,     0,
       0,    94,     0,    96,    97,     0,     0,     0,   115,     0,
       0,     0,     0,     0,   120,     0,     0,   122,     0,    47,
       0,   102,    48,    49,    50,    51,     2,     0,     0,    52,
      53,     3,     4,     5,     0,   111,     0,     0,     6,     0,
      54,    55,     0,     7,     0,   116,     0,     8,     9,   119,
      56,    10,    57,    11,    12,     0,     0,     0,    13,    58,
       0,     0,     0,    14,    59,    15,    16,    17,    18,    19,
      20,     1,     0,     0,     0,     0,     0,     0,     2,     0,
       0,     0,     0,     3,     4,     5,     0,     0,     0,     0,
       6,     0,     0,     0,     0,     7,     0,     0,     0,     8,
       9,     0,     0,    10,     0,    11,    12,     0,     0,     0,
      13,     0,     0,     0,     0,    14,     0,    15,    16,    17,
      18,    19,    20,    48,    49,    50,    51,     2,     0,     0,
      52,    53,     3,     4,     5,     0,     0,     0,     0,     6,
      65,    54,    55,     0,     7,     0,     0,     0,     8,     9,
      66,    56,    10,    57,    11,    12,     0,     0,     0,    13,
      58,     0,     0,     0,    14,    59,    15,    16,    17,    18,
      19,    20,    48,    49,    50,    51,     2,    61,     0,    52,
      53,     3,     4,     5,     0,     0,     0,     0,     6,     0,
      54,    55,     0,     7,     0,     0,     0,     8,     9,     0,
      56,    10,    57,    11,    12,     0,     0,     0,    13,    58,
       0,     0,     0,    14,    59,    15,    16,    17,    18,    19,
      20,    48,    49,    50,    51,     2,     0,     0,    52,    53,
       3,     4,     5,     0,     0,     0,     0,     6,     0,    54,
      55,     0,     7,     0,     0,     0,     8,     9,     0,    56,
      10,    57,    11,    12,    67,     0,     0,    13,    58,     0,
       0,     0,    14,    59,    15,    16,    17,    18,    19,    20,
      48,    49,    50,    51,     2,     0,     0,    52,    53,     3,
       4,     5,     0,     0,     0,     0,     6,     0,    54,    55,
       0,     7,     0,     0,     0,     8,     9,     0,    56,    10,
      57,    11,    12,     0,     0,     0,    13,    58,    99,     0,
       0,    14,    59,    15,    16,    17,    18,    19,    20,    48,
      49,    50,    51,     2,     0,   100,    52,    53,     3,     4,
       5,     0,     0,     0,     0,     6,     0,    54,    55,     0,
       7,     0,     0,     0,     8,     9,     0,    56,    10,    57,
      11,    12,     0,     0,     0,    13,    58,     0,     0,     0,
      14,    59,    15,    16,    17,    18,    19,    20,    48,    49,
      50,    51,     2,     0,     0,    52,    53,     3,     4,     5,
       0,     0,     0,     0,     6,   104,    54,    55,     0,     7,
       0,     0,     0,     8,     9,     0,    56,    10,    57,    11,
      12,     0,     0,     0,    13,    58,     0,     0,     0,    14,
      59,    15,    16,    17,    18,    19,    20,    48,    49,    50,
      51,     2,     0,     0,    52,    53,     3,     4,     5,     0,
       0,     0,     0,     6,     0,    54,    55,     0,     7,     0,
       0,     0,     8,     9,     0,    56,    10,    57,    11,    12,
       0,   105,     0,    13,    58,     0,     0,     0,    14,    59,
      15,    16,    17,    18,    19,    20,    48,    49,    50,    51,
       2,     0,     0,    52,    53,     3,     4,     5,     0,     0,
       0,     0,     6,     0,    54,    55,     0,     7,     0,     0,
       0,     8,     9,     0,    56,    10,    57,    11,    12,     0,
       0,     0,    13,    58,   107,     0,     0,    14,    59,    15,
      16,    17,    18,    19,    20,    48,    49,    50,    51,     2,
       0,     0,    52,    53,     3,     4,     5,     0,   112,     0,
       0,     6,     0,    54,    55,     0,     7,     0,     0,     0,
       8,     9,     0,    56,    10,    57,    11,    12,     0,     0,
       0,    13,    58,     0,     0,     0,    14,    59,    15,    16,
      17,    18,    19,    20,    48,    49,    50,    51,     2,     0,
       0,    52,    53,     3,     4,     5,     0,     0,     0,     0,
       6,     0,    54,    55,     0,     7,     0,     0,     0,     8,
       9,     0,    56,    10,    57,    11,    12,     0,     0,     0,
      13,    58,     0,     0,     0,    14,    59,    15,    16,    17,
      18,    19,    20,    48,    49,    50,    51,     2,     0,     0,
      52,    53,     3,     4,     5,     0,     0,     0,     0,     6,
       0,    54,    55,     0,     7,     0,     0,     0,     0,     0,
       0,     0,    10,    57,     0,    12,     0,     0,     0,    13,
      58,     0,     0,     0,    14,    59,    15,    16,    17,    18,
      19,    20,    48,    49,    50,    51,     2,     0,     0,    52,
      53,     3,     4,     5,     0,     0,     0,     0,     6,     0,
      54,    55,     0,     7,     0,     0,     0,     0,     0,     0,
       0,    10,     0,     0,    12,     0,     0,     0,    13,    58,
       0,     0,     0,    14,    59,    15,    16,    17,    18,    19,
      20,    48,    49,    50,    51,     2,     0,     0,     0,     0,
       3,     4,     5,     0,     0,     0,     0,     6,     0,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
      10,     0,     0,    12,     0,     0,     0,    13,    58,     0,
       0,     0,    14,    59,    15,    16,    17,    18,    19,    20,
      50,    51,     2,     0,     0,     0,     0,     3,     4,     5,
       0,     0,     0,     0,     6,     0,     0,     0,     0,     7,
       0,     0,     0,     0,     0,     0,     0,    10,     0,     0,
      12,     0,     0,     0,    13,    58,     0,     0,     0,    14,
      59,    15,    16,    17,    18,    19,    20,     2,     0,     0,
       0,     0,     3,     4,     5,     0,     0,     0,     0,     6,
       0,     0,     0,     0,     7,     0,     0,     0,     8,     9,
       0,     0,    10,     0,    11,    12,     0,     0,     0,    13,
       0,     0,     0,     0,    14,     0,    15,    16,    17,    18,
      19,    20,     2,     0,     0,     0,     0,     3,     4,     5,
       0,     0,     0,     0,     6,     0,     0,     0,     0,     7,
       0,     0,     0,     0,     0,     0,     0,    10,     0,     0,
      12,     0,     0,     0,    13,    58,     0,     0,     0,    14,
      59,    15,    16,    17,    18,    19,    20,     2,     0,     0,
       0,     0,     3,     4,     5,     0,     0,     0,     0,     6,
       0,     0,     0,     0,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     0,     0,    13,
      58,     0,     0,     0,    14,    59,    15,    16,    17,    18,
      19,    20
  };

  const signed char
  parser::yycheck_[] =
  {
       0,     5,     2,    51,    19,    51,     6,    23,     8,     9,
      10,    11,    12,    17,    21,    15,    16,    17,    25,    26,
      27,     0,    23,    51,    19,    21,     0,    51,     2,    23,
      23,    38,     6,     5,     5,    42,    10,    11,    12,    43,
      17,    15,    16,    17,    -1,    17,    17,    18,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
       5,    61,    23,    23,    -1,    -1,    66,    67,    40,    -1,
      15,    -1,    17,    73,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     5,    61,    -1,    -1,
      -1,    -1,    66,    67,     5,     5,     5,    35,    17,    73,
     100,   101,    40,    22,    42,     5,    17,    17,    17,    18,
      20,    22,   112,     5,    -1,    -1,    -1,    17,   118,    -1,
      20,   121,    -1,    -1,    62,    17,   100,   101,    -1,    -1,
      -1,    69,    -1,    71,    72,    -1,    -1,    -1,   112,    -1,
      -1,    -1,    -1,    -1,   118,    -1,    -1,   121,    -1,     0,
      -1,    89,     3,     4,     5,     6,     7,    -1,    -1,    10,
      11,    12,    13,    14,    -1,   103,    -1,    -1,    19,    -1,
      21,    22,    -1,    24,    -1,   113,    -1,    28,    29,   117,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    39,    40,
      -1,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      51,     0,    -1,    -1,    -1,    -1,    -1,    -1,     7,    -1,
      -1,    -1,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,
      19,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    28,
      29,    -1,    -1,    32,    -1,    34,    35,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    44,    -1,    46,    47,    48,
      49,    50,    51,     3,     4,     5,     6,     7,    -1,    -1,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    -1,    24,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    39,
      40,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,     3,     4,     5,     6,     7,     8,    -1,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    19,    -1,
      21,    22,    -1,    24,    -1,    -1,    -1,    28,    29,    -1,
      31,    32,    33,    34,    35,    -1,    -1,    -1,    39,    40,
      -1,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      51,     3,     4,     5,     6,     7,    -1,    -1,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    -1,    21,
      22,    -1,    24,    -1,    -1,    -1,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    40,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
       3,     4,     5,     6,     7,    -1,    -1,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    19,    -1,    21,    22,
      -1,    24,    -1,    -1,    -1,    28,    29,    -1,    31,    32,
      33,    34,    35,    -1,    -1,    -1,    39,    40,    41,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    19,    -1,    21,    22,    -1,
      24,    -1,    -1,    -1,    28,    29,    -1,    31,    32,    33,
      34,    35,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    51,     3,     4,
       5,     6,     7,    -1,    -1,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    -1,    24,
      -1,    -1,    -1,    28,    29,    -1,    31,    32,    33,    34,
      35,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,     3,     4,     5,
       6,     7,    -1,    -1,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    19,    -1,    21,    22,    -1,    24,    -1,
      -1,    -1,    28,    29,    -1,    31,    32,    33,    34,    35,
      -1,    37,    -1,    39,    40,    -1,    -1,    -1,    44,    45,
      46,    47,    48,    49,    50,    51,     3,     4,     5,     6,
       7,    -1,    -1,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    19,    -1,    21,    22,    -1,    24,    -1,    -1,
      -1,    28,    29,    -1,    31,    32,    33,    34,    35,    -1,
      -1,    -1,    39,    40,    41,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    51,     3,     4,     5,     6,     7,
      -1,    -1,    10,    11,    12,    13,    14,    -1,    16,    -1,
      -1,    19,    -1,    21,    22,    -1,    24,    -1,    -1,    -1,
      28,    29,    -1,    31,    32,    33,    34,    35,    -1,    -1,
      -1,    39,    40,    -1,    -1,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,     3,     4,     5,     6,     7,    -1,
      -1,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      19,    -1,    21,    22,    -1,    24,    -1,    -1,    -1,    28,
      29,    -1,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      39,    40,    -1,    -1,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,     3,     4,     5,     6,     7,    -1,    -1,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    19,
      -1,    21,    22,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    -1,    35,    -1,    -1,    -1,    39,
      40,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,     3,     4,     5,     6,     7,    -1,    -1,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    19,    -1,
      21,    22,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    -1,    35,    -1,    -1,    -1,    39,    40,
      -1,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      51,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    -1,    -1,    35,    -1,    -1,    -1,    39,    40,    -1,
      -1,    -1,    44,    45,    46,    47,    48,    49,    50,    51,
       5,     6,     7,    -1,    -1,    -1,    -1,    12,    13,    14,
      -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,
      35,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,     7,    -1,    -1,
      -1,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,    19,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    28,    29,
      -1,    -1,    32,    -1,    34,    35,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    44,    -1,    46,    47,    48,    49,
      50,    51,     7,    -1,    -1,    -1,    -1,    12,    13,    14,
      -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,
      35,    -1,    -1,    -1,    39,    40,    -1,    -1,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,     7,    -1,    -1,
      -1,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,    19,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    39,
      40,    -1,    -1,    -1,    44,    45,    46,    47,    48,    49,
      50,    51
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     0,     7,    12,    13,    14,    19,    24,    28,    29,
      32,    34,    35,    39,    44,    46,    47,    48,    49,    50,
      51,    53,    54,    55,    54,    51,    19,    51,    54,    54,
      55,    55,    54,    54,    54,    21,    25,    26,    27,    38,
      42,    56,    23,    54,    54,    54,     0,     0,     3,     4,
       5,     6,    10,    11,    21,    22,    31,    33,    40,    45,
      55,     8,    23,    51,    19,    20,    30,    36,    56,    21,
      56,     5,    17,    40,    56,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    56,    23,
      51,    54,    54,    22,    56,    43,    56,    56,    54,    41,
       9,    15,    56,    23,    20,    37,    22,    41,    54,    54,
      20,    56,    16,    23,    20,    54,    56,    23,    18,    56,
      54,    18,    54
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    52,    53,    53,    54,    54,    54,    54,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    56,    56,
      56,    56,    56,    56,    56,    56
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     8,    10,    11,     5,     3,     3,     3,     3,
       3,     6,     5,     3,     3,     3,     3,     2,     3,     2,
       3,     5,     4,     3,     3,     2,     2,     2,     1,     1,
       1,     3,     3,     3,     4,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"eof\"", "error", "$undefined", "\"+\"", "\"-\"", "\"*\"", "\"/\"",
  "\"if\"", "\"then\"", "\"else\"", "\"<=\"", "\">=\"", "\"let\"",
  "\"fun\"", "\"fix\"", "\"=\"", "\"in\"", "\"->\"", "\"|->\"", "\"(\"",
  "\")\"", "\"<\"", "\">\"", "\":\"", "\"()\"", "\"int\"", "\"bool\"",
  "\"unit\"", "\"fst\"", "\"snd\"", "\" . \"", "\";\"", "\"#\"", "\":=\"",
  "\"ref\"", "\"while\"", "\"do\"", "\"end\"", "\"array\"", "\"new\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"{}\"", "\"::\"", "\"car\"",
  "\"cdr\"", "\"empty?\"", "\"vint\"", "\"vbool\"", "\"var\"", "$accept",
  "prog", "exp1", "exp", "typ", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   116,   116,   117,   121,   122,   123,   124,   127,   128,
     129,   130,   131,   134,   137,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   166,   167,
     168,   169,   170,   171,   172,   173
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
#line 1491 "src/lex-yacc-parser/parser.yy.cpp" // lalr1.cc:1167
#line 175 "src/lex-yacc-parser/parser.yy" // lalr1.cc:1168


// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const yy::parser::location_type& l, const std::string &m) { driver.error(l, m); }
