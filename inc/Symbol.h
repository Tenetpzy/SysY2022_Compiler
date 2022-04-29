#pragma once

#include <string>
#include "type_info.h"

enum class Symbol_type_class
{
    Sym_var,
    Sym_function,
    Sym_array,
    Sym_label
};

class Symbol
{
private:
    Symbol_type_class type_class;
    std::string name;

public:
    Symbol(Symbol_type_class t, const std::string &s) : type_class(t), name(s) {}
    ~Symbol() = default;

    Symbol_type_class get_sym_type_class() const
    {
        return type_class;
    }

    const std::string &get_sym_name() const
    {
        return name;
    }
};

class Symbol_var : public Symbol
{
private:
    bool const_flag;
    Var_type type;

public:
    Symbol_var(const std::string &s, bool is_const, Var_type ty) : Symbol(Symbol_type_class::Sym_var, s), const_flag(is_const), type(ty) {}
    ~Symbol_var() = default;

    bool is_const() const
    {
        return const_flag;
    }

    Var_type get_type() const
    {
        return type;
    }
};

class Symbol_array : public Symbol
{
private:
    bool const_flag;
    Array_type_info info;

public:
    Symbol_array(const std::string &s, bool is_const, const Array_type_info &arr_info) : Symbol(Symbol_type_class::Sym_array, s), const_flag(is_const), info(arr_info) {}
    ~Symbol_array() = default;

    bool is_const() const
    {
        return const_flag;
    }

    // 得到数组维度
    size_t get_dim_number() const
    {
        return info.dim_vector.size();
    }

    // 得到第i维大小
    int get_dim(size_t i) const
    {
        if (i < 0 || i >= get_dim_number())
            throw std::runtime_error("array index out of range.");
        return info.dim_vector[i];
    }
};

class Symbol_function : public Symbol
{
private:
    Function_type_info info;

public:
    Symbol_function(const std::string &s, const Function_type_info &fun_info) : Symbol(Symbol_type_class::Sym_function, s), info(fun_info) {}
    ~Symbol_function() = default;

    Function_return_type get_return_type() const
    {
        return info.return_type;
    }

    size_t get_param_number() const
    {
        return info.param_list.size();
    }

    Symbol &get_param(size_t i) const
    {
        if (i < 0 || i >= get_param_number())
            throw std::runtime_error("array index out of range.");
        return *(info.param_list[i]);
    }
};

class Symbol_label : public Symbol
{
public:
    Symbol_label(const std::string &s) : Symbol(Symbol_type_class::Sym_label, s) {}
    ~Symbol_label() = default;
};