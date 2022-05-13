%{
#include "parser.hh"

// C++版parser要求yylex的声明如下（不启用位置信息）
// yylval包含token的语义值信息，读到token后将语义值写入yylval
#define YY_DECL int yylex(yy::parser::semantic_type *yylval)

typedef yy::parser::token_type TOKEN;

int yycolumn = 1;
int yycolno;  // 当前token的列号

#define YY_USER_ACTION yycolno = yycolumn; yycolumn += yyleng;

%}

%option yylineno

%%

"int"  { return TOKEN::INT; }
"float"  { return TOKEN::FLOAT; }
"void"  { return TOKEN::VOID; }
"if"  { return TOKEN::IF; }
"else"  { return TOKEN::ELSE; }
"while"  { return TOKEN::WHILE; }
"break"  { return TOKEN::BREAK; }
"continue"  { return TOKEN::CONTINUE; }
"return"  { return TOKEN::RETURN; }
"const"  { return TOKEN::CONST; }

"=="  { return TOKEN::EQ; }
"!="  { return TOKEN::NE; }
"<"  { return TOKEN::LT; }
"<="  { return TOKEN::LE; }
">"  { return TOKEN::GT; }
">="  { return TOKEN::GE; }
"&&"  { return TOKEN::AND; }
"||"  { return TOKEN::OR; }
"!"  { return TOKEN::NOT; }

[_A-Za-z]([_A-Za-z]|[0-9])* { return TOKEN::IDENT; }
[0-9]* { return TOKEN::INTCONST; }

"\n" { yycolumn = 1; }
[ \t\r]  {}

"//"[^\n]* {}

.  { return *yytext; }

%%

int yywrap()
{
    return 1;
}
