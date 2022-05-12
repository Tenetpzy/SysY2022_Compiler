%{
#include "parser.hh"

// C++版parser要求yylex的声明如下（不启用位置信息）
// yylval包含token的语义值信息，读到token后将语义值写入yylval
#define YY_DECL int yylex(yy::parser::semantic_type *yylval)

typedef yy::parser::token_type token;

int yycolumn = 1;
int yycolno;  // 当前token的列号

#define YY_USER_ACTION yycolno = yycolumn; yycolumn += yyleng;

%}

%option yylineno

