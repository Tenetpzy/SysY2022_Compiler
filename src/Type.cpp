#include "Type.h"

Type_name Void_type::get_type_name() const
{
    return Type_name::T_void;
}

size_t Void_type::get_size() const
{
    return 0;
}

bool Void_type::is_arith_type() const
{
    return false;
}

std::string Void_type::to_string() const
{
    return std::string("void");
}


Reference_type::Reference_type(const std::shared_ptr<Type> &p) : base_type(p)
{
}

Type_name Reference_type::get_type_name() const
{
    return Type_name::T_reference;
}

size_t Reference_type::get_size() const
{
    return 4;
}

bool Reference_type::is_arith_type() const
{
    return base_type->is_arith_type();
}

std::string Reference_type::to_string() const
{
    return base_type->to_string();
}


void Array_type::init_size()
{
    size = 1;
    for (auto e : dim)
        size *= e;
    size *= base_type->get_size();
}

Array_type::Array_type(const std::shared_ptr<Object_type> &p, const std::vector<int> &d) : base_type(p), dim(d)
{
    init_size();
}

Array_type::Array_type(const std::shared_ptr<Object_type> &p, std::vector<int> &&d) : base_type(p), dim(std::move(d))
{
    init_size();
}

Type_name Array_type::get_type_name() const
{
    return Type_name::T_array;
}

size_t Array_type::get_size() const
{
    return size;
}

bool Array_type::is_arith_type() const
{
    return false;
}

std::string Array_type::to_string() const
{
    std::string s = base_type->to_string();
    s += " [";
    if (dim[0] != 0)
        s += std::to_string(dim[0]);
    s += ']';
    size_t dimlen = dim.size();
    for (size_t i = 1; i < dimlen; ++i)
    {
        s += '[';
        s += std::to_string(dim[i]);
        s += ']';
    }
    return s;
}


Function_type::Function_type(const std::shared_ptr<Type> &rtp, const std::vector<std::shared_ptr<Type>> &ptl) : return_type(rtp), param_type_list(ptl)
{
}

Function_type::Function_type(const std::shared_ptr<Type> &rtp, std::vector<std::shared_ptr<Type>> &&ptl) : return_type(rtp), param_type_list(std::move(ptl))
{
}

Type_name Function_type::get_type_name() const
{
    return Type_name::T_function;
}

bool Function_type::is_arith_type() const
{
    return false;
}

std::string Function_type::to_string() const
{
    std::string s = return_type->to_string();
    s += " (";
    for (auto &pt : param_type_list)
    {
        s += pt->to_string();
        s += ", ";
    }
    if (param_type_list.size() != 0)
        s.pop_back(), s.pop_back();
    s += ')';
    return s;
}


size_t Int_type::get_size() const
{
    return 4;
}

Type_name Int_type::get_type_name() const
{
    return Type_name::T_int;
}

bool Int_type::is_arith_type() const
{
    return true;
}

std::string Int_type::to_string() const
{
    return std::string("int");
}


size_t Float_type::get_size() const
{
    return 4;
}

Type_name Float_type::get_type_name() const
{
    return Type_name::T_float;
}

bool Float_type::is_arith_type() const
{
    return true;
}

std::string Float_type::to_string() const
{
    return std::string("float");
}