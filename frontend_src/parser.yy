// 插入到parser源文件中包含了parser头文件之后的位置（确保yy::parser已声明）
%code{

extern int yylex(yy::parser::semantic_type *yylval);
extern int yylineno;
extern int yycolno;

}

// 会插入到parser头文件和源文件中。parser头文件中的部分声明依赖这些C++头
%code requires{
#include "Semantic.h"
#include "Type.h"
#include "Frontend_util.h"
#include "Symbol.h"

// test
#include <cstdio>
}

%require "3.2"
%language "c++"   // 生成C++版parser

%define api.value.type variant  // 声明使用类而非union作为语义值
%defines  // 生成parser头文件


%token INT FLOAT VOID IF ELSE WHILE BREAK CONTINUE RETURN CONST
%token EQ NE LE LT GE GT AND OR NOT
%token <std::string> IDENT INTCONST FLOATCONST

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

%nterm <std::shared_ptr<Type>> Btype
%nterm CompUnit
%nterm Decl
%nterm ConstDecl

%nterm VarDecl
%nterm <Var_decl> VarDeclItemList
%nterm <Var_decl_item> VarDeclItem
%nterm <std::vector<std::shared_ptr<Expr>>> ArrayAccessList
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

%nterm <std::shared_ptr<Expr>> ArithExp Lval
%nterm CondExp
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
| VarDecl {  }
;

VarDecl :
VarDeclItemList ';' { Frontend_env::append_glob_var_decl($1.get_decl_tac_list()); }
;

/* Var_decl */
VarDeclItemList :
Btype VarDeclItem  { $$ = Var_decl($1, $2); }
| VarDeclItemList ',' VarDeclItem { $$ = std::move(Var_decl($1, $3)); }
;

/* <std::shared_ptr<Type>> */
Btype :
VOID { $$ = std::make_shared<Void_type>(); }
| INT { $$ = std::make_shared<Int_type>(); }
| FLOAT { $$ = std::make_shared<Float_type>(); }
;

/* Var_decl_item */
VarDeclItem :
IDENT ArrayAccessList { $$ = Var_decl_item(std::move($1), std::move($2)); }
| IDENT ArrayAccessList '=' InitVal {}
;

/* std::vector<std::shared_ptr<Expr>> */
ArrayAccessList :
/* empty */ { /*printf("reduce a empty accessList.\n");*/ }
| ArrayAccessList '[' ArithExp ']' { $$ = std::move($1); $$.push_back($3); }
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

/* std::shared_ptr<Expr> */
ArithExp :
ArithExp '+' ArithExp {}
| ArithExp '-' ArithExp {}
| ArithExp '*' ArithExp {}
| ArithExp '/' ArithExp {}
| ArithExp '%' ArithExp {}
| Lval { $$ = $1; }
| '+' ArithExp %prec UMINUS {}
| '-' ArithExp %prec UMINUS {}
| IDENT '(' ')' {}
| IDENT '(' FuncRParamList ')' {}
| '(' ArithExp ')' {}
| INTCONST { $$ = std::make_shared<Primary_expr>($1, Sym_type::Sym_int); }
| FLOATCONST { $$ = std::make_shared<Primary_expr>($1, Sym_type::Sym_float); }
;

FuncRParamList :
ArithExp {}
| FuncRParamList ',' ArithExp {}
;

Lval :
IDENT ArrayAccessList
{
	if ($2.empty())
	{
		$$ = std::make_shared<Primary_expr>($1, Sym_type::Sym_object);
	}
	else
	{
		$$ = std::make_shared<Access_array_expr>($1, Array_access_list(std::move($2)));
	}
}
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
| NOT CondExp %prec UMINUS {}
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