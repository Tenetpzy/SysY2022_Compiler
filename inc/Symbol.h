#pragma once

#include "Type.h"
#include <string>

enum class Sym_type
{
    Sym_int,
    Sym_float,
    Sym_object,
    Sym_const_object,
    Sym_function,
    Sym_label
};

class Symbol 
{
public:
    virtual Sym_type get_sym_type() const = 0;
    virtual std::string to_string() const = 0;
    virtual std::shared_ptr<Type> get_type() const = 0;
};

class Sym_function : public Symbol
{
private:
    std::shared_ptr<Function_type> func_type;
    std::string name;
    // addr

public:
    Sym_function(const std::shared_ptr<Function_type> fun_type) : func_type(fun_type) {}
    Sym_function(const std::shared_ptr<Function_type> fun_type, const std::string &str) : func_type(fun_type), name(str) {}
    Sym_function(const std::shared_ptr<Function_type> fun_type, std::string &&str) : func_type(fun_type), name(str) {}
    ~Sym_function() = default;

    Sym_type get_sym_type() const override
    {
        return Sym_type::Sym_function;
    }

    std::string to_string() const override
    {
        return name;
    }

    std::shared_ptr<Type> get_type() const override
    {
        return func_type;
    }
};

class Sym_label : public Symbol
{
private:
    std::string name;

public:
    Sym_label() = default;
    Sym_label(const std::string &str) : name(str) {}
    Sym_label(std::string &&str) : name(str) {}
    ~Sym_label() = default;

    Sym_type get_sym_type() const override
    {
        return Sym_type::Sym_label;
    }

    std::string to_string() const override
    {
        return name;
    }

    // not used
    std::shared_ptr<Type> get_type() const override;
};

class Sym_object : public Symbol
{
protected:
    std::shared_ptr<Type> type;
    std::string name;
    // scope
    // addr

public:
    Sym_object(const std::shared_ptr<Type> t) : type(t) {}
    Sym_object(const std::shared_ptr<Type> t, const std::string &str) : type(t), name(str) {}
    Sym_object(const std::shared_ptr<Type> t, std::string &&str) : type(t), name(str) {}
    ~Sym_object() = default;

    std::shared_ptr<Type> get_type() const override
    {
        return type;
    }

    // Type_name get_type_name() const
    // {
    //     return type->get_type_name();
    // }

    Sym_type get_sym_type() const override
    {
        return Sym_type::Sym_object;
    }

    std::string to_string() const override
    {
        return name;
    }
};

class Sym_const_object : public Sym_object
{
};

class Sym_int : public Symbol
{
private:
    int value;

public:
    Sym_int(const int val) : value(val) {}
    ~Sym_int() = default;

    Sym_type get_sym_type() const override
    {
        return Sym_type::Sym_int;
    }

    std::shared_ptr<Type> get_type() const override
    {
        return std::make_shared<Int_type>();
    }

    std::string to_string() const override
    {
        return std::string("#") + std::to_string(value);
    }
};

class Sym_float : public Symbol
{
private:
    float value;

public:
    Sym_float(const float val) : value(val) {}
    ~Sym_float() = default;

    Sym_type get_sym_type() const override
    {
        return Sym_type::Sym_float;
    }

    std::shared_ptr<Type> get_type() const override
    {
        return std::make_shared<Float_type>();
    }

    std::string to_string() const override
    {
        return std::string("#") + std::to_string(value);
    }
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

