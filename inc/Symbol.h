#pragma once

#include "Type.h"

enum class Sym_type
{
    Sym_object,
    Sym_const_object,
    Sym_function,
    Sym_label
};

class Symbol 
{
public:
    virtual Sym_type get_sym_type() const = 0;
};

class Sym_function : public Symbol
{
private:
    std::shared_ptr<Function_type> func_type;
    // addr

public:
    Sym_function(const std::shared_ptr<Function_type> &fun_type) : func_type(fun_type) {}
    ~Sym_function() = default;

    Sym_type get_sym_type() const override
    {
        return Sym_type::Sym_function;
    }
};

class Sym_label : public Symbol
{
public:
    Sym_label() = default;
    ~Sym_label() = default;

    Sym_type get_sym_type() const override
    {
        return Sym_type::Sym_label;
    }
};

class Sym_object : public Symbol
{
protected:
    std::shared_ptr<Object_type> type;
    // scope
    // addr

public:
    Sym_object(const std::shared_ptr<Object_type> &t) : type(t) {}
    ~Sym_object() = default;

    std::shared_ptr<Object_type> get_type() const
    {
        return type;
    }

    Type_name get_type_name() const
    {
        return type->get_type_name();
    }

    Sym_type get_sym_type() const override
    {
        return Sym_type::Sym_object;
    }
};

class Sym_const_object : public Sym_object
{
};


// template <typename T>
// class Sym_imm : public Symbol
// {
// private:
//     const T value;

// public:
//     Sym_imm(const std::shared_ptr<Type> &type, const T val);
//     ~Sym_imm() = default;

//     const T get_value() const;
// };

// class Sym_void : public Symbol
// {
// public:
//     Sym_void();
//     ~Sym_void();
// };



// class Sym_var : public Symbol
// {
// protected:
//     // scope
//     // addr
//     std::string name;

// public:
//     Sym_var(const std::shared_ptr<Type> &type, const std::string &str);
//     Sym_var(const std::shared_ptr<Type> &type);
//     ~Sym_var() = default;
// };



// #define MAKE_CONST true

// class Sym_reference : public Symbol
// {
// private:
//     bool const_flag;
//     std::string name;
//     // scope
//     // addr

// public:
//     Sym_reference(const std::shared_ptr<Reference_type> &base_type, bool is_const = false);
//     Sym_reference(const std::shared_ptr<Reference_type> &base_type, const std::string &str, bool is_const = false);
//     ~Sym_reference() = default;

//     bool is_const() const;
// };



// class Sym_array : public Symbol
// {
// protected:
//     std::string name;
//     // scope
//     // addr

// public:
//     Sym_array(const std::shared_ptr<Array_type> &arr_type, const std::string &str);
//     Sym_array(const std::shared_ptr<Array_type> &arr_type);
//     ~Sym_array();
// };

