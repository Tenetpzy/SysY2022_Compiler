#pragma once

#include "Type.h"
#include <string>

enum class Sym_type
{
    Sym_int,
    Sym_float,
    Sym_object,
    Sym_function,
    Sym_label
};

class Symbol 
{
public:
    virtual Sym_type get_sym_type() const = 0;
    virtual std::string to_string() const = 0;
    virtual std::shared_ptr<Type> get_type() const = 0;
    virtual int get_env_tag() const = 0;  // 这个符号所在的作用域（环境）层级
    virtual bool is_literal_num_sym() const  // 是否为常量符号
    {
        return false;
    }

    static bool is_literal_num_sym_type(const Sym_type type)
    {
        return type == Sym_type::Sym_int || type == Sym_type::Sym_float;
    }
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
    Sym_function(const std::shared_ptr<Function_type> fun_type, std::string &&str) : func_type(fun_type), name(std::move(str)) {}
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

    int get_env_tag() const override
    {
        return 0;
    }
};

class Sym_label : public Symbol
{
private:
    std::string name;

public:
    Sym_label() = default;
    Sym_label(const std::string &str) : name(str) {}
    Sym_label(std::string &&str) : name(std::move(str)) {}
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

    int get_env_tag() const override
    {
        return 0;
    }
};

class Sym_object : public Symbol
{
protected:
    std::shared_ptr<Type> type;
    std::string name;
    int env_tag;
    // scope
    // addr

public:
    Sym_object(const std::shared_ptr<Type> t, int env) : type(t), env_tag(env) {}
    Sym_object(const std::shared_ptr<Type> t, const std::string &str, int env) : type(t), name(str), env_tag(env) {}
    Sym_object(const std::shared_ptr<Type> t, std::string &&str, int env) : type(t), name(std::move(str)), env_tag(env) {}
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
        std::string s;
        s.append("S").append(std::to_string(env_tag)).append("_").append(name);
        return s;
    }

    int get_env_tag() const override
    {
        return env_tag;
    }
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

    int get_env_tag() const override
    {
        return 0;
    }

    bool is_literal_num_sym() const override
    {
        return true;
    }

    int get_value() const
    {
        return value;
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

    int get_env_tag() const override
    {
        return 0;
    }

    bool is_literal_num_sym() const override
    {
        return true;
    }

    float get_value() const
    {
        return value;
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

