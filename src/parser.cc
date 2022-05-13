// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.hh"


// Unqualified %code blocks.
#line 2 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"


extern int yylex(yy::parser::semantic_type *yylval);
extern int yylineno;
extern int yycolno;


#line 53 "parser.cc"


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

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



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
      *yycdebug_ << '\n';                       \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 125 "parser.cc"


  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
  {
    switch (this->type_get ())
    {
      default:
        break;
    }

  }
#endif

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->type_get ())
    {
      default:
        break;
    }

  }



  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      default:
        break;
    }

  }

  // by_type.
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.type_get ())
    {
      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.type_get ())
    {
      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
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
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
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

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

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
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 3:
#line 79 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
             {}
#line 587 "parser.cc"
    break;

  case 4:
#line 80 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                 { /*printf("reduce a CompUnit with Decl.\n");*/ }
#line 593 "parser.cc"
    break;

  case 5:
#line 81 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                    {}
#line 599 "parser.cc"
    break;

  case 6:
#line 85 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
          {}
#line 605 "parser.cc"
    break;

  case 7:
#line 86 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
          { /*printf("reduce a Decl.\n");*/ }
#line 611 "parser.cc"
    break;

  case 8:
#line 90 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                    { /*printf("reduce a varDecl.\n");*/ }
#line 617 "parser.cc"
    break;

  case 9:
#line 94 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                   { /*printf("reduce varDeclItemList.\n");*/ }
#line 623 "parser.cc"
    break;

  case 10:
#line 95 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                                  {}
#line 629 "parser.cc"
    break;

  case 11:
#line 99 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
     { /*printf("reduce void.\n");*/ }
#line 635 "parser.cc"
    break;

  case 12:
#line 100 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
      { /*printf("reduce int.\n");*/ }
#line 641 "parser.cc"
    break;

  case 13:
#line 101 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
        {}
#line 647 "parser.cc"
    break;

  case 14:
#line 105 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                      { /*printf("reduce a varDeclItem.\n");*/ }
#line 653 "parser.cc"
    break;

  case 15:
#line 106 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                                    {}
#line 659 "parser.cc"
    break;

  case 16:
#line 110 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
            { /*printf("reduce a empty accessList.\n");*/ }
#line 665 "parser.cc"
    break;

  case 17:
#line 111 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                                   {}
#line 671 "parser.cc"
    break;

  case 18:
#line 115 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
         {}
#line 677 "parser.cc"
    break;

  case 19:
#line 116 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                      {}
#line 683 "parser.cc"
    break;

  case 20:
#line 119 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
          {}
#line 689 "parser.cc"
    break;

  case 21:
#line 123 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
        {}
#line 695 "parser.cc"
    break;

  case 22:
#line 124 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                          {}
#line 701 "parser.cc"
    break;

  case 23:
#line 128 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                            {}
#line 707 "parser.cc"
    break;

  case 24:
#line 132 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                    {}
#line 713 "parser.cc"
    break;

  case 25:
#line 133 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                                      {}
#line 719 "parser.cc"
    break;

  case 26:
#line 137 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                                  {}
#line 725 "parser.cc"
    break;

  case 27:
#line 138 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                        {  /* 此处报错，更好的错误提示 */  }
#line 731 "parser.cc"
    break;

  case 28:
#line 142 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                   { /*printf("reduce FuncDef.\n");*/ }
#line 737 "parser.cc"
    break;

  case 29:
#line 146 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                    { /*printf("reduce function head void param.\n");*/ }
#line 743 "parser.cc"
    break;

  case 30:
#line 147 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                                     {}
#line 749 "parser.cc"
    break;

  case 31:
#line 151 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
           {}
#line 755 "parser.cc"
    break;

  case 32:
#line 152 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                                {}
#line 761 "parser.cc"
    break;

  case 33:
#line 156 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
            {}
#line 767 "parser.cc"
    break;

  case 34:
#line 157 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                                      {}
#line 773 "parser.cc"
    break;

  case 35:
#line 161 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                    {}
#line 779 "parser.cc"
    break;

  case 36:
#line 162 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
        {}
#line 785 "parser.cc"
    break;

  case 39:
#line 172 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
          {}
#line 791 "parser.cc"
    break;

  case 40:
#line 173 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                          {}
#line 797 "parser.cc"
    break;

  case 41:
#line 177 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
     {}
#line 803 "parser.cc"
    break;

  case 42:
#line 178 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
       {}
#line 809 "parser.cc"
    break;

  case 43:
#line 182 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                      {}
#line 815 "parser.cc"
    break;

  case 44:
#line 183 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
      {}
#line 821 "parser.cc"
    break;

  case 45:
#line 184 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
               {}
#line 827 "parser.cc"
    break;

  case 46:
#line 185 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
        {}
#line 833 "parser.cc"
    break;

  case 47:
#line 186 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                                                 {}
#line 839 "parser.cc"
    break;

  case 48:
#line 187 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                                    {}
#line 845 "parser.cc"
    break;

  case 49:
#line 188 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                             {}
#line 851 "parser.cc"
    break;

  case 50:
#line 189 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
            {}
#line 857 "parser.cc"
    break;

  case 51:
#line 190 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
               {}
#line 863 "parser.cc"
    break;

  case 52:
#line 191 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
             {}
#line 869 "parser.cc"
    break;

  case 53:
#line 192 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                      {}
#line 875 "parser.cc"
    break;

  case 54:
#line 196 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                      {}
#line 881 "parser.cc"
    break;

  case 55:
#line 197 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                        {}
#line 887 "parser.cc"
    break;

  case 56:
#line 198 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                        {}
#line 893 "parser.cc"
    break;

  case 57:
#line 199 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                        {}
#line 899 "parser.cc"
    break;

  case 58:
#line 200 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                        {}
#line 905 "parser.cc"
    break;

  case 59:
#line 201 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
       {}
#line 911 "parser.cc"
    break;

  case 60:
#line 202 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                            {}
#line 917 "parser.cc"
    break;

  case 61:
#line 203 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                            {}
#line 923 "parser.cc"
    break;

  case 62:
#line 204 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                {}
#line 929 "parser.cc"
    break;

  case 63:
#line 205 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                               {}
#line 935 "parser.cc"
    break;

  case 64:
#line 206 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                   {}
#line 941 "parser.cc"
    break;

  case 65:
#line 207 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
           {}
#line 947 "parser.cc"
    break;

  case 66:
#line 208 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
             {}
#line 953 "parser.cc"
    break;

  case 67:
#line 212 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
         {}
#line 959 "parser.cc"
    break;

  case 68:
#line 213 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                              {}
#line 965 "parser.cc"
    break;

  case 69:
#line 217 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                      {}
#line 971 "parser.cc"
    break;

  case 70:
#line 221 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                   {}
#line 977 "parser.cc"
    break;

  case 71:
#line 222 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                      {}
#line 983 "parser.cc"
    break;

  case 72:
#line 223 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                     {}
#line 989 "parser.cc"
    break;

  case 73:
#line 224 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                     {}
#line 995 "parser.cc"
    break;

  case 74:
#line 225 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                     {}
#line 1001 "parser.cc"
    break;

  case 75:
#line 226 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                     {}
#line 1007 "parser.cc"
    break;

  case 76:
#line 227 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                     {}
#line 1013 "parser.cc"
    break;

  case 77:
#line 228 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
                     {}
#line 1019 "parser.cc"
    break;

  case 78:
#line 229 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
           {}
#line 1025 "parser.cc"
    break;

  case 79:
#line 230 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"
              {}
#line 1031 "parser.cc"
    break;


#line 1035 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

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
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
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
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
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
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -122;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
    -122,   201,    16,  -122,  -122,  -122,    40,   -12,  -122,  -122,
    -122,    -9,  -122,    -7,  -122,    29,    -5,    19,  -122,  -122,
      53,  -122,  -122,   107,  -122,  -122,  -122,    29,    36,    13,
    -122,  -122,    46,    47,    55,    74,   127,    69,  -122,  -122,
     168,   168,  -122,  -122,   168,    53,  -122,  -122,  -122,   107,
    -122,  -122,   189,    87,    39,  -122,  -122,    92,   -28,  -122,
     163,   168,    68,    68,  -122,  -122,  -122,   199,  -122,    10,
     101,  -122,  -122,   183,  -122,  -122,   168,   168,   168,   168,
     168,  -122,   168,   163,   102,    40,  -122,   158,  -122,   228,
      99,    68,   228,    64,   159,  -122,  -122,   228,   -25,  -122,
      34,    34,  -122,  -122,  -122,   207,  -122,    86,  -122,  -122,
    -122,   -13,  -122,  -122,    68,    68,    68,    68,    68,    68,
      68,    68,   132,   132,   168,  -122,  -122,  -122,   163,  -122,
      80,    80,  -122,  -122,  -122,  -122,   234,   227,   140,  -122,
     228,   101,  -122,   132,  -122
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     2,     0,    12,    13,    11,     0,     0,     4,     6,
       7,     0,     5,     0,     1,     0,     0,    16,     9,     8,
       0,    37,    28,     0,    16,    24,    23,     0,     0,    14,
      16,    10,     0,     0,     0,     0,     0,    16,    65,    66,
       0,     0,    44,    38,     0,     0,    41,    46,    36,     0,
      39,    42,     0,    59,    27,    25,    29,     0,     0,    31,
       0,     0,     0,     0,    50,    51,    52,     0,    59,     0,
      69,    60,    61,     0,    35,    40,     0,     0,     0,     0,
       0,    45,     0,     0,    33,     0,    30,     0,    15,    18,
       0,     0,    78,     0,     0,    53,    62,    67,     0,    64,
      54,    55,    56,    57,    58,     0,    26,     0,    32,    20,
      21,     0,    17,    79,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    63,    43,    16,     0,    19,
      72,    73,    74,    75,    76,    77,    71,    70,    47,    49,
      68,    34,    22,     0,    48
  };

  const short
  parser::yypgoto_[] =
  {
    -122,     3,  -122,   133,  -122,  -122,  -122,   128,   -18,   -76,
    -122,  -122,   134,  -122,  -122,  -122,    75,   149,  -122,   114,
    -122,   116,  -121,   -23,   -49,   -20,  -122,  -122
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    45,     1,    46,     9,    10,    11,    18,    29,    88,
     111,    16,    25,    12,    13,    58,    59,    47,    23,    48,
      49,    50,    51,    92,    93,    68,    98,     2
  };

  const unsigned char
  parser::yytable_[] =
  {
      52,   138,   139,    53,     7,    85,    54,   106,   124,    15,
      17,   110,    86,    67,    94,   125,    14,    71,    72,    70,
     128,    73,   144,    19,    20,   129,    52,    26,    27,    53,
      21,    57,    37,    38,    39,    40,    41,    89,    90,     3,
       4,     5,   113,     3,     4,     5,    97,    60,    61,    44,
      96,    24,   142,   100,   101,   102,   103,   104,    28,   105,
      89,    78,    79,    80,    89,   130,   131,   132,   133,   134,
     135,   136,   137,    83,    61,    30,    56,   114,   115,   116,
     117,   118,   119,   120,   121,    62,    63,    64,    57,    91,
      37,    38,    39,    40,    41,   116,   117,   118,   119,    52,
      52,   140,    53,    53,   122,    89,    65,    44,    69,   141,
       3,     4,     5,    32,    84,    33,    34,    35,    36,     6,
      52,    82,   127,    53,    76,    77,    78,    79,    80,    37,
      38,    39,    40,    41,     8,   112,    61,   107,    32,    42,
      33,    34,    35,    36,    21,    43,    44,   143,    31,    37,
      38,    39,    40,    41,    37,    38,    39,    40,    41,    66,
     108,    55,    22,    74,    42,    75,    44,     0,     0,    21,
       0,    44,   114,   115,   116,   117,   118,   119,   120,   121,
      37,    38,    39,    40,    41,    37,    38,    39,    40,    41,
      37,    38,    39,    40,    41,    87,   109,    44,     0,   123,
      87,     0,    44,     0,     3,     4,     5,    44,    76,    77,
      78,    79,    80,     6,    76,    77,    78,    79,    80,     0,
       0,    81,     0,    99,    76,    77,    78,    79,    80,     0,
       0,    95,    76,    77,    78,    79,    80,     0,     0,   126,
     114,   115,   116,   117,   118,   119,   120,   114,   115,   116,
     117,   118,   119,    76,    77,    78,    79,    80
  };

  const short
  parser::yycheck_[] =
  {
      23,   122,   123,    23,     1,    33,    24,    83,    33,     6,
      22,    87,    40,    36,    63,    40,     0,    40,    41,    37,
      33,    44,   143,    32,    33,    38,    49,    32,    33,    49,
      37,    28,    22,    23,    24,    25,    26,    60,    61,     3,
       4,     5,    91,     3,     4,     5,    69,    34,    35,    39,
      40,    22,   128,    76,    77,    78,    79,    80,    39,    82,
      83,    27,    28,    29,    87,   114,   115,   116,   117,   118,
     119,   120,   121,    34,    35,    22,    40,    13,    14,    15,
      16,    17,    18,    19,    20,    39,    39,    32,    85,    21,
      22,    23,    24,    25,    26,    15,    16,    17,    18,   122,
     123,   124,   122,   123,    40,   128,    32,    39,    39,   127,
       3,     4,     5,     6,    22,     8,     9,    10,    11,    12,
     143,    34,    36,   143,    25,    26,    27,    28,    29,    22,
      23,    24,    25,    26,     1,    36,    35,    35,     6,    32,
       8,     9,    10,    11,    37,    38,    39,     7,    20,    22,
      23,    24,    25,    26,    22,    23,    24,    25,    26,    32,
      85,    27,    13,    49,    32,    49,    39,    -1,    -1,    37,
      -1,    39,    13,    14,    15,    16,    17,    18,    19,    20,
      22,    23,    24,    25,    26,    22,    23,    24,    25,    26,
      22,    23,    24,    25,    26,    37,    38,    39,    -1,    40,
      37,    -1,    39,    -1,     3,     4,     5,    39,    25,    26,
      27,    28,    29,    12,    25,    26,    27,    28,    29,    -1,
      -1,    32,    -1,    40,    25,    26,    27,    28,    29,    -1,
      -1,    32,    25,    26,    27,    28,    29,    -1,    -1,    32,
      13,    14,    15,    16,    17,    18,    19,    13,    14,    15,
      16,    17,    18,    25,    26,    27,    28,    29
  };

  const signed char
  parser::yystos_[] =
  {
       0,    43,    68,     3,     4,     5,    12,    42,    44,    45,
      46,    47,    54,    55,     0,    42,    52,    22,    48,    32,
      33,    37,    58,    59,    22,    53,    32,    33,    39,    49,
      22,    48,     6,     8,     9,    10,    11,    22,    23,    24,
      25,    26,    32,    38,    39,    42,    44,    58,    60,    61,
      62,    63,    64,    66,    49,    53,    40,    42,    56,    57,
      34,    35,    39,    39,    32,    32,    32,    64,    66,    39,
      49,    64,    64,    64,    60,    62,    25,    26,    27,    28,
      29,    32,    34,    34,    22,    33,    40,    37,    50,    64,
      64,    21,    64,    65,    65,    32,    40,    64,    67,    40,
      64,    64,    64,    64,    64,    64,    50,    35,    57,    38,
      50,    51,    36,    65,    13,    14,    15,    16,    17,    18,
      19,    20,    40,    40,    33,    40,    32,    36,    33,    38,
      65,    65,    65,    65,    65,    65,    65,    65,    63,    63,
      64,    49,    50,     7,    63
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    41,    68,    43,    43,    43,    44,    44,    46,    47,
      47,    42,    42,    42,    48,    48,    49,    49,    50,    50,
      50,    51,    51,    45,    52,    52,    53,    53,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    59,    60,    61,
      61,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    67,    67,    66,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     1,     1,     2,     2,
       3,     1,     1,     1,     2,     4,     0,     4,     1,     3,
       2,     1,     3,     3,     2,     3,     4,     2,     2,     4,
       5,     1,     3,     2,     5,     3,     2,     1,     1,     1,
       2,     1,     1,     4,     1,     2,     1,     5,     7,     5,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     1,
       2,     2,     3,     4,     3,     1,     1,     1,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     2
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "INT", "FLOAT", "VOID", "IF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "RETURN", "CONST", "EQ", "NE", "LE", "LT",
  "GE", "GT", "AND", "OR", "NOT", "IDENT", "INTCONST", "FLOATCONST", "'+'",
  "'-'", "'*'", "'/'", "'%'", "LOWER_THAN_ELSE", "UMINUS", "';'", "','",
  "'='", "'['", "']'", "'{'", "'}'", "'('", "')'", "$accept", "Btype",
  "CompUnit", "Decl", "ConstDecl", "VarDecl", "VarDeclItemList",
  "VarDeclItem", "ArrayAccessList", "InitVal", "InitValList",
  "ConstDeclItemList", "ConstDeclItem", "FuncDef", "FunctionHead",
  "FuncFParamList", "FuncFParam", "Block", "LB", "RB", "BlockItemList",
  "BlockItem", "Stmt", "ArithExp", "CondExp", "Lval", "FuncRParamList",
  "Start", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    76,    76,    79,    80,    81,    85,    86,    90,    94,
      95,    99,   100,   101,   105,   106,   110,   111,   115,   116,
     119,   123,   124,   128,   132,   133,   137,   138,   142,   146,
     147,   151,   152,   156,   157,   161,   162,   165,   168,   172,
     173,   177,   178,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   212,   213,   217,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230
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
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    29,     2,     2,
      39,    40,    27,    25,    33,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
       2,    34,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      30,    31
    };
    const int user_token_number_max_ = 281;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

} // yy
#line 1493 "parser.cc"

#line 233 "/home/pzy/SysY2022/SysY2022_Compiler/frontend_src/parser.yy"



namespace yy
{
  // Report an error to the user.
  auto parser::error (const std::string& msg) -> void
  {
    std::cerr << msg << '\n';
  }
}
