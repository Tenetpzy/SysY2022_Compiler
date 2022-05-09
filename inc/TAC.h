#pragma once

#include <memory>
#include <vector>
#include <initializer_list>
#include "Type.h"

class Symbol;

enum class TAC_type
{
    add,
    sub,
    mul,
    div,
    eq,
    ne,
    lt,
    le,
    gt,
    ge,
    load_offset,
    store_offset,
    neg,
    copy,
    lea,
    load,
    store,
    goto_,
    if_,
    ifz,
    label,
    var_decl,
    formal_decl,
    auctual_decl,
    call_ret,
    call_noret,
    return_,
    fun_begin,
    fun_end
};

class TAC
{
protected:
    std::vector<std::shared_ptr<Symbol>> operands;

public:
    TAC(std::initializer_list<std::shared_ptr<Symbol>> l) : operands(l) {}
    TAC() = default;
    ~TAC() = default;

    virtual TAC_type tac_type() const = 0;
};

// a = b + c
// operands: a b c
class TAC_add : public TAC
{
public:
    TAC_add(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_add() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::add;
    }
};

// a = b - c
// operands: a b c
class TAC_sub : public TAC
{
public:
    TAC_sub(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_sub() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::sub;
    }
};

// a = b * c
// operands: a b c
class TAC_mul : public TAC
{
public:
    TAC_mul(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_mul() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::mul;
    }
};

// a = b * c
// operands: a b c
class TAC_div : public TAC
{
public:
    TAC_div(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_div() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::div;
    }
};

// a = (b == c)
// operands: a b c
class TAC_eq : public TAC
{
public:
    TAC_eq(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_eq() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::eq;
    }
};

// a = (b != c)
// operands: a b c
class TAC_ne : public TAC
{
public:
    TAC_ne(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_ne() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::ne;
    }
};

// a = (b < c)
// operands: a b c
class TAC_lt : public TAC
{
public:
    TAC_lt(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_lt() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::lt;
    }
};

// a = (b <= c)
// operands: a b c
class TAC_le : public TAC
{
public:
    TAC_le(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_le() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::le;
    }
};

// a = (b > c)
// operands: a b c
class TAC_gt : public TAC
{
public:
    TAC_gt(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_gt() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::gt;
    }
};

// a = (b >= c)
// operands: a b c
class TAC_ge : public TAC
{
public:
    TAC_ge(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_ge() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::ge;
    }
};

// a = b[c]
// operands: a b c
class TAC_load_offset : public TAC
{
public:
    TAC_load_offset(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_load_offset() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::load_offset;
    }
};

// a[b] = c
// operands: a b c
class TAC_store_offset : public TAC
{
public:
    TAC_store_offset(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b, const std::shared_ptr<Symbol> &c) :
        TAC({a, b, c}) { }
    ~TAC_store_offset() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::store_offset;
    }
};

// a = -b
// operands: a b
class TAC_neg : public TAC
{
public:
    TAC_neg(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b) :
        TAC({a, b}) { }
    ~TAC_neg() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::neg;
    }
};

// a = b
// operands: a b
class TAC_copy : public TAC
{
public:
    TAC_copy(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b) :
        TAC({a, b}) { }
    ~TAC_copy() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::copy;
    }
};

// a = &b
// operands: a b
class TAC_lea : public TAC
{
public:
    TAC_lea(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b) :
        TAC({a, b}) { }
    ~TAC_lea() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::lea;
    }
};

// a = *b
// operands: a b
class TAC_load : public TAC
{
public:
    TAC_load(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b) :
        TAC({a, b}) { }
    ~TAC_load() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::load;
    }
};

// *a = b
// operands: a b
class TAC_store : public TAC
{
public:
    TAC_store(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b) :
        TAC({a, b}) { }
    ~TAC_store() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::store;
    }
};

// goto a
// operands: a
class TAC_goto : public TAC
{
public:
    TAC_goto(const std::shared_ptr<Symbol> &a) :
        TAC({a}) { }
    ~TAC_goto() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::goto_;
    }
};

// if a goto b
// operands: a b
class TAC_if : public TAC
{
public:
    TAC_if(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b) :
        TAC({a, b}) { }
    ~TAC_if() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::if_;
    }
};

// ifz a goto b
// operands: a b
class TAC_ifz : public TAC
{
public:
    TAC_ifz(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b) :
        TAC({a, b}) { }
    ~TAC_ifz() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::ifz;
    }
};

// label a
// operands: a
class TAC_label : public TAC
{
public:
    TAC_label(const std::shared_ptr<Symbol> &a) :
        TAC({a}) { }
    ~TAC_label() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::label;
    }
};

// declare int, float, or array
class TAC_var_decl : public TAC
{
public:
    TAC_var_decl(const std::shared_ptr<Symbol> &a) : 
        TAC({a}){ }
    ~TAC_var_decl() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::var_decl;
    }
};

// formal int, float, or array
class TAC_formal_decl : public TAC
{
public:
    TAC_formal_decl(const std::shared_ptr<Symbol> &a) : 
        TAC({a}) { }
    ~TAC_formal_decl() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::formal_decl;
    }
};

// actual int, float, or array
class TAC_actual_decl : public TAC
{
public:
    TAC_actual_decl(const std::shared_ptr<Symbol> &a) : 
        TAC({a}){ }
    ~TAC_actual_decl() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::auctual_decl;
    }
};

// a = call b
class TAC_call_ret : public TAC
{
public:
    TAC_call_ret(const std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b) : 
        TAC({a, b}) { }
    ~TAC_call_ret() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::call_ret;
    }
};

// call a
class TAC_call_noret : public TAC
{
public:
    TAC_call_noret(const std::shared_ptr<Symbol> &a) : 
        TAC({a}) { }
    ~TAC_call_noret() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::call_noret;
    }
};

// return a
class TAC_return : public TAC
{
public:
    TAC_return(const std::shared_ptr<Symbol> &a) : 
        TAC({a}) { }
    ~TAC_return() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::return_;
    }
};

// begin
class TAC_fun_begin : public TAC
{
public:
    TAC_fun_begin() = default;
    ~TAC_fun_begin() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::fun_begin;
    }
};

// end
class TAC_fun_end : public TAC
{
public:
    TAC_fun_end() = default;
    ~TAC_fun_end() = default;

    TAC_type tac_type() const override
    {
        return TAC_type::fun_end;
    }
};