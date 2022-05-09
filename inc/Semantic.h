#pragma once

#include <memory>
#include <list>
#include "Symbol.h"
#include "Type.h"

class TAC;

enum class Op_type
{
    add,
    sub,
    mul,
    div,
    mod,

    le,  // <
    leq, // <=
    ge,  // >
    geq, // >=
    eq,  // =
    neq, // !=
    L_and, // &&
    L_or,  // ||
    L_not  // !
};

enum class Expr_type
{
    Binary_arith_expr,
    Binary_logic_expr,
    Unary_arith_expr,
    Unary_logic_expr,
    Const_expr,
    Ident_expr,
    Ident_ref_expr,
    Access_array_expr,
    Access_element_expr,
    Call_ret_expr,
    Call_noret_expr
};


class Expr
{
protected:
    std::shared_ptr<Sym_expr_value> value;   // 表达式值

public:

    // 得到表达式值类型
    std::shared_ptr<Type> value_type() const
    {
        return value->get_expr_value_type();
    }

    // 表达式值类型名
    std::string value_type_name() const
    {
        return value->get_expr_value_type()->to_string();
    }

    Type_name value_type_class() const
    {
        return value->get_expr_value_type()->get_type_name();
    }

    // 得到表达式值
    std::shared_ptr<Sym_expr_value> get_value()
    {
        return value;
    }

//    virtual Expr_type expr_type() const = 0;   // 表达式值类别

    // 返回 完成Expr所进行的计算所需的TAC序列
    // 对于算术逻辑等表达式，完成Expr所进行的计算能直接得到值
    // 对于数组访问表达式，完成计算得到一个偏移量，不直接得到表达式的值
    // ...
    virtual std::list<std::shared_ptr<TAC>> reduce_tac_list() const = 0;

    // 返回 得到Expr的值所需的额外TAC
    // 当Expr为引用，或为数组访问时具有额外TAC
    // 默认不需要额外TAC
    virtual std::list<std::shared_ptr<TAC>> cal_value_tac_list() const
    {
        return std::list<std::shared_ptr<TAC>>();
    }

    virtual std::string to_string() const = 0;  // 编译器输出使用
};

class Binary_arith_expr : public Expr
{
private:
    std::list<std::shared_ptr<TAC>> reduce_tac;
    std::shared_ptr<Expr> exp[2];
    char op;

public:
    // 构造函数中负责语义检查，reduce_tac和value的构造
    Binary_arith_expr(const char _op, const std::shared_ptr<Expr> &e1, const std::shared_ptr<Expr> &e2);
    ~Binary_arith_expr() = default;

    std::list<std::shared_ptr<TAC>> reduce_tac_list() const override
    {
        return reduce_tac;
    }

    // binary_arith_expr 不需要额外的指令即可获得值

    std::string to_string() const override
    {
        return exp[0]->to_string() + op + exp[1]->to_string();
    }
};


// class Lval_expr : public Expr
// {
// private:
//     std::shared_ptr<Sym_object> lval;

// public:
//     Lval_expr(const std::shared_ptr<Sym_object> &val, bool semantic_check_flag = false) : lval(val), Expr(semantic_check_flag) {}
//     Lval_expr(const std::shared_ptr<Sym_object> &val, const std::shared_ptr<std::string> &str, bool semantic_check_flag = false) : lval(val), Expr(str, semantic_check_flag) {}
//     ~Lval_expr() = default;

//     std::shared_ptr<Type> value_type() const override
//     {
//         return lval->get_type();
//     }

//     Expr_type expr_type() const override
//     {
//         return Expr_type::Lval_expr;
//     }
// };


// // 实现接口expr_type()
// class Const_expr : public Expr
// {
// public:
//     Const_expr(bool semantic_check_flag = false) : Expr(semantic_check_flag) {}
//     Const_expr(const std::shared_ptr<std::string> &str, bool semantic_check_flag = false) : Expr(str, semantic_check_flag) {}
//     ~Const_expr() = default;

//     Expr_type expr_type() const override
//     {
//         return Expr_type::Rval_expr;
//     }
// };

// class Const_int_expr : public Const_expr
// {
// private:
//     int value;

// public:
//     Const_int_expr(int val, bool semantic_check_flag = false) : value(val), Const_expr(semantic_check_flag) {}
//     Const_int_expr(int val, const std::shared_ptr<std::string> &str, bool semantic_check_flag = false) : value(val), Const_expr(str, semantic_check_flag) {}
//     ~Const_int_expr() = default;

//     std::shared_ptr<Type> value_type() const override
//     {
//         return std::make_shared<Int_type>();
//     }
// };


// class Rval_expr : public Expr
// {
// private:
//     std::shared_ptr<Sym_object> value;

// public:
//     Rval_expr(const std::shared_ptr<Sym_object> &val, bool semantic_check_flag = false) : value(val), Expr(semantic_check_flag) {}
//     Rval_expr(const std::shared_ptr<Sym_object> &val, const std::shared_ptr<std::string> &str, bool semantic_check_flag = false) : value(val), Expr(str, semantic_check_flag) {}

//     Expr_type expr_type() const override
//     {
//         return Expr_type::Rval_expr;
//     }

//     std::shared_ptr<Type> value_type() const override
//     {
//         return value->get_type();
//     }
// };