// 插入到parser源文件中包含了parser头文件之后的位置（确保yy::parser已声明）
%code{

extern int yylex(yy::parser::semantic_type *yylval);
extern int yylineno;
extern int yycolno;

}

// 会插入到parser头文件和源文件中。parser头文件中的部分声明依赖这些C++头
%code requires{
#include "Semantic.h"

// test
#include <cstdio>
}

%require "3.2"
%language "c++"   // 生成C++版parser

%define api.value.type variant  // 声明使用类而非union作为语义值
%defines  // 生成parser头文件


%token INT FLOAT VOID IF ELSE WHILE BREAK CONTINUE RETURN CONST
%token  EQ NE LE LT GE GT AND OR NOT
%token  IDENT INTCONST FLOATCONST

%left OR
%left AND
%left EQ NE
%left LE LT GE GT
%left '+' '-'
%left '*' '/' '%'
%right NOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%right UMINUS

%nterm Btype
%nterm CompUnit
%nterm Decl
%nterm ConstDecl

%nterm VarDecl
%nterm VarDeclItemList
%nterm VarDeclItem
%nterm ArrayAccessList
%nterm InitVal
%nterm InitValList

%nterm ConstDeclItemList
%nterm ConstDeclItem

%nterm FuncDef
%nterm FunctionHead
%nterm FuncFParamList
%nterm FuncFParam

%nterm Block
%nterm LB
%nterm RB
%nterm BlockItemList
%nterm BlockItem

%nterm Stmt

%nterm ArithExp
%nterm CondExp
%nterm Lval
%nterm FuncRParamList


%%

Start : CompUnit;

CompUnit :
/* empty */  {}
| CompUnit Decl  { /*printf("reduce a CompUnit with Decl.\n");*/ }
| CompUnit FuncDef  {}
;

Decl :
ConstDecl {}
| VarDecl { /*printf("reduce a Decl.\n");*/ }
;

VarDecl :
VarDeclItemList ';' { /*printf("reduce a varDecl.\n");*/ }
;

VarDeclItemList :
Btype VarDeclItem  { /*printf("reduce varDeclItemList.\n");*/ }
| VarDeclItemList ',' VarDeclItem {}
;

Btype :
VOID { /*printf("reduce void.\n");*/ }
| INT { /*printf("reduce int.\n");*/ }
| FLOAT {}
;

VarDeclItem :
IDENT ArrayAccessList { /*printf("reduce a varDeclItem.\n");*/ }
| IDENT ArrayAccessList '=' InitVal {}
;

ArrayAccessList :
/* empty */ { /*printf("reduce a empty accessList.\n");*/ }
| ArrayAccessList '[' ArithExp ']' {}
;

InitVal :
ArithExp {}
| '{' InitValList '}' {}

/* InitValList为空在语法上不好处理 */
| '{' '}' {}
;

InitValList :
InitVal {}
| InitValList ',' InitVal {}
;

ConstDecl :
CONST ConstDeclItemList ';' {}
;

ConstDeclItemList :
Btype ConstDeclItem {}
| ConstDeclItemList ',' ConstDeclItem {}
;

ConstDeclItem :
IDENT ArrayAccessList '=' InitVal {}
| IDENT ArrayAccessList {  /* 此处报错，更好的错误提示 */  }
;

FuncDef :
FunctionHead Block { /*printf("reduce FuncDef.\n");*/ }
;

FunctionHead:
Btype IDENT '(' ')' { /*printf("reduce function head void param.\n");*/ }
| Btype IDENT '(' FuncFParamList ')' {}
;

FuncFParamList:
FuncFParam {}
| FuncFParamList ',' FuncFParam {}
;

FuncFParam:
Btype IDENT {}
| Btype IDENT '[' ']' ArrayAccessList {}
;

Block :
LB BlockItemList RB {}
| LB RB {}
;

LB : '{'
;

RB : '}'
;

BlockItemList :
BlockItem {}
| BlockItemList BlockItem {}
;

BlockItem :
Decl {}
| Stmt {}
;

Stmt :
Lval '=' ArithExp ';' {}
| ';' {}
| ArithExp ';' {}
| Block {}
| IF '(' CondExp ')' Stmt  %prec LOWER_THAN_ELSE {}
| IF '(' CondExp ')' Stmt ELSE Stmt {}
| WHILE '(' CondExp ')' Stmt {}
| BREAK ';' {}
| CONTINUE ';' {}
| RETURN ';' {}
| RETURN ArithExp ';' {}
;

ArithExp :
ArithExp '+' ArithExp {}
| ArithExp '-' ArithExp {}
| ArithExp '*' ArithExp {}
| ArithExp '/' ArithExp {}
| ArithExp '%' ArithExp {}
| Lval {}
| '+' ArithExp %prec UMINUS {}
| '-' ArithExp %prec UMINUS {}
| IDENT '(' ')' {}
| IDENT '(' FuncRParamList ')' {}
| '(' ArithExp ')' {}
| INTCONST {}
| FLOATCONST {}
;

FuncRParamList :
ArithExp {}
| FuncRParamList ',' ArithExp {}
;

Lval :
IDENT ArrayAccessList {}
;

CondExp :
CondExp OR CondExp {}
| CondExp AND CondExp {}
| CondExp EQ CondExp {}
| CondExp NE CondExp {}
| CondExp LE CondExp {}
| CondExp LT CondExp {}
| CondExp GE CondExp {}
| CondExp GT CondExp {}
| ArithExp {}
| NOT CondExp {}
;

%%


namespace yy
{
  // Report an error to the user.
  auto parser::error (const std::string& msg) -> void
  {
    std::cerr << msg << '\n';
  }
}