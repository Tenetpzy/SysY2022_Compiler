#pragma once

#include <list>
#include "Symbol.h"

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
    eq,  // ==
    neq, // !=

    L_and, // &&
    L_or,  // ||
    L_not  // !
};

enum class Expr_type
{
    Binary_arith_rel_expr,  // ok
    Binary_logic_expr,
    Unary_arith_expr,  // ok
    Unary_logic_expr,
    Primary_expr,  // ok
    Ident_ref_expr,   // ok
    Access_array_expr,  // ok
    Call_expr
};

class Expr
{
protected:
    std::shared_ptr<Symbol> value;   // 表达式值

public:

    // 得到表达式值类型
    std::shared_ptr<Type> value_type() const
    {
        return value->get_type();
    }

    // 表达式值类型名
    std::string value_type_name() const
    {
        return value->get_type()->to_string();
    }

    Type_class value_type_class() const
    {
        return value->get_type()->get_type_class();
    }

    // 得到表达式值
    std::shared_ptr<Symbol> get_value()
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
    virtual std::list<std::shared_ptr<TAC>> gen_value_tac_list() const
    {
        return std::list<std::shared_ptr<TAC>>();
    }

    virtual std::string to_string() const = 0;  // 编译器输出使用
};

class Binary_arith_rel_expr : public Expr
{
private:
    std::list<std::shared_ptr<TAC>> reduce_tac;
    std::shared_ptr<Expr> exp[2];
    Op_type op;

public:
    // 构造函数中负责语义检查，reduce_tac和value的构造
    Binary_arith_rel_expr(const Op_type _op, const std::shared_ptr<Expr> e1, const std::shared_ptr<Expr> e2);
    ~Binary_arith_rel_expr() = default;

    std::list<std::shared_ptr<TAC>> reduce_tac_list() const override
    {
        return reduce_tac;
    }

    // binary_arith_expr 不需要额外的指令即可获得值

    std::string to_string() const override;
};

class Unary_arith_expr : public Expr
{
private:
    std::list<std::shared_ptr<TAC>> reduce_tac;
    std::shared_ptr<Expr> exp;
    Op_type op;

public:
    Unary_arith_expr(const Op_type _op, const std::shared_ptr<Expr> exp);
    ~Unary_arith_expr() = default;

    std::list<std::shared_ptr<TAC>> reduce_tac_list() const override
    {
        return reduce_tac;
    }

    std::string to_string() const override;
};

// 表达式为一个变量或立即数
class Primary_expr : public Expr
{
public:

    // Exp --> Number
    // Exp --> Ident

    // Ident的语义检查由归约器实现
    // 因为识别到一个Ident时，无法区别它是引用还是变量
    // 而处理引用和变量的表达式类型不同
    Primary_expr(const std::shared_ptr<Symbol> sym)
    {
        value = sym;
    }

    ~Primary_expr() = default;

    // 初等表达式，没有计算过程
    std::list<std::shared_ptr<TAC>> reduce_tac_list() const override
    {
        return std::list<std::shared_ptr<TAC>>();
    }

    std::string to_string() const override
    {
        return value->to_string();
    }
};

// 变量引用表达式
// 在函数内部，对声明为形如int &x的形参x的引用
class Ident_ref_expr : public Expr
{
private:

    // 引用使用指针实现，这个符号代表的变量应该是一个基本类型的引用
    std::shared_ptr<Symbol> pointer;

    std::list<std::shared_ptr<TAC>> gen_val_tac;

public:
    Ident_ref_expr(const std::shared_ptr<Symbol> ptr);
    ~Ident_ref_expr() = default;

    std::list<std::shared_ptr<TAC>> reduce_tac_list() const override
    {
        return std::list<std::shared_ptr<TAC>>();
    }

    // 在语言层面封装了引用，得到引用表达式的值需要对指针解引用这一额外操作
    std::list<std::shared_ptr<TAC>> gen_value_tac_list() const override
    {
        return gen_val_tac;
    }

    std::string to_string() const override
    {
        return pointer->to_string();
    }
};

class Array_access_list
{
private:
    std::vector<std::shared_ptr<Expr>> access_list;

public:
    Array_access_list(const std::vector<std::shared_ptr<Expr>> &v) : access_list(v) {}
    Array_access_list(std::vector<std::shared_ptr<Expr>> &&v) : access_list(v) {}
    // default destructor, assign, move construct, move assign

    const std::vector<std::shared_ptr<Expr>>& get_list() const
    {
        return access_list;
    }

    std::string to_string() const
    {
        std::string s;
        for (auto &x : access_list)
        {
            s.push_back('[');
            s.append(x->to_string());
            s.push_back(']');
        }
        return s;
    }
};

// 数组访问表达式, 如声明int a[2][2], 表达式为a，a[1]，a[i][j]
// 如果是一个子数组，该表达式不可以作为左值
// 否则，由数组是否为const变量决定它是否可作为左值
class Access_array_expr : public Expr
{
private:
    std::shared_ptr<Symbol> array;  // 访问的数组

    std::shared_ptr<Symbol> array_addr;  // 数组地址
    Array_access_list arr_access_list;

    // 访问偏移量
    // 当offset为空时，表达式直接引用了数组名
    std::shared_ptr<Symbol> offset;

    // 负责计算array_addr和offset
    std::list<std::shared_ptr<TAC>> reduce_tac;

    // 负责计算value
    std::list<std::shared_ptr<TAC>> gen_val_tac;

    // 进行数组访问表达式本身的合法性检查
    void init();

public:

    // 传入的array要么是直接指代数组的符号，要么是数组的引用
    Access_array_expr(std::shared_ptr<Symbol> arr, Array_access_list &&access) : array(arr), arr_access_list(access) { init(); }
    Access_array_expr(std::shared_ptr<Symbol> arr, const Array_access_list &access) : array(arr), arr_access_list(access) { init(); }
    ~Access_array_expr() = default;

    std::list<std::shared_ptr<TAC>> reduce_tac_list() const override
    {
        return reduce_tac;
    }

    std::list<std::shared_ptr<TAC>> gen_value_tac_list() const override
    {
        return gen_val_tac;
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