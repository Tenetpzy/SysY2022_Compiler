#pragma once

#include <vector>
#include <memory>

enum class Var_type
{
    T_int,
    T_float
};

enum class Function_return_type
{
    T_int,
    T_float,
    T_void
};

class Array_type_info
{
    Var_type element_type;
    std::vector<int> dim_vector;

    friend class Symbol_array;
};

class Symbol;

class Function_type_info
{
    Function_return_type return_type;
    std::vector<std::shared_ptr<Symbol>> param_list;

    friend class Symbol_function;
};