#pragma once

#include <memory>
#include "Symbol.h"
#include "Type.h"



enum class Expr_type
{
    Lval_expr,
    Const_expr,
    Rval_expr
};

#define NEED_SEMANTIC_CHECK true

class Expr
{
protected:
    std::shared_ptr<std::string> name;
    bool is_need_semantic_check_;

public:
    Expr(bool semantic_check_flag = false) : is_need_semantic_check_(semantic_check_flag) {}
    Expr(const std::shared_ptr<std::string> &str, bool semantic_check_flag = false) : name(str), is_need_semantic_check_(semantic_check_flag) {}
    ~Expr() = default;

    virtual std::shared_ptr<Type> value_type() const = 0;   // 表达式值类型
    virtual Expr_type expr_type() const = 0;   // 表达式值类别

    const std::string& get_name() const    // 用于编译器输出
    {
        return *name;
    }

    bool need_semantic_check() const
    {
        return is_need_semantic_check_;
    }
};


class Lval_expr : public Expr
{
private:
    std::shared_ptr<Sym_object> lval;

public:
    Lval_expr(const std::shared_ptr<Sym_object> &val, bool semantic_check_flag = false) : lval(val), Expr(semantic_check_flag) {}
    Lval_expr(const std::shared_ptr<Sym_object> &val, const std::shared_ptr<std::string> &str, bool semantic_check_flag = false) : lval(val), Expr(str, semantic_check_flag) {}
    ~Lval_expr() = default;

    std::shared_ptr<Type> value_type() const override
    {
        return lval->get_type();
    }

    Expr_type expr_type() const override
    {
        return Expr_type::Lval_expr;
    }
};


// 实现接口expr_type()
class Const_expr : public Expr
{
public:
    Const_expr(bool semantic_check_flag = false) : Expr(semantic_check_flag) {}
    Const_expr(const std::shared_ptr<std::string> &str, bool semantic_check_flag = false) : Expr(str, semantic_check_flag) {}
    ~Const_expr() = default;

    Expr_type expr_type() const override
    {
        return Expr_type::Rval_expr;
    }
};

class Const_int_expr : public Const_expr
{
private:
    int value;

public:
    Const_int_expr(int val, bool semantic_check_flag = false) : value(val), Const_expr(semantic_check_flag) {}
    Const_int_expr(int val, const std::shared_ptr<std::string> &str, bool semantic_check_flag = false) : value(val), Const_expr(str, semantic_check_flag) {}
    ~Const_int_expr() = default;

    std::shared_ptr<Type> value_type() const override
    {
        return std::make_shared<Int_type>();
    }
};


class Rval_expr : public Expr
{
private:
    std::shared_ptr<Sym_object> value;

public:
    Rval_expr(const std::shared_ptr<Sym_object> &val, bool semantic_check_flag = false) : value(val), Expr(semantic_check_flag) {}
    Rval_expr(const std::shared_ptr<Sym_object> &val, const std::shared_ptr<std::string> &str, bool semantic_check_flag = false) : value(val), Expr(str, semantic_check_flag) {}

    Expr_type expr_type() const override
    {
        return Expr_type::Rval_expr;
    }

    std::shared_ptr<Type> value_type() const override
    {
        return value->get_type();
    }
};


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