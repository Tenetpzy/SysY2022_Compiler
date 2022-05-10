#include "Type.h"

Type_class Void_type::get_type_class() const
{
    return Type_class::T_void;
}

size_t Void_type::get_size() const
{
    return 0;
}

bool Void_type::is_base_var_type() const
{
    return false;
}

std::string Void_type::to_string() const
{
    return std::string("void");
}


Reference_type::Reference_type(const std::shared_ptr<Object_type> p) : base_type(p)
{
}

Type_class Reference_type::get_type_class() const
{
    return Type_class::T_reference;
}

size_t Reference_type::get_size() const
{
    return 4;
}

bool Reference_type::is_base_var_type() const
{
    return base_type->is_base_var_type();
}

std::string Reference_type::to_string() const
{
    return base_type->to_string();
}

std::shared_ptr<Object_type> Reference_type::get_base_type() const
{
    return base_type;
}


void Array_type::init_size()
{
    size = 1;
    for (auto e : dim)
        size *= e;
    size *= base_type->get_size();
}

Array_type::Array_type(const std::shared_ptr<Object_type> p, const std::vector<int> &d) : base_type(p), dim(d)
{
    init_size();
}

Array_type::Array_type(const std::shared_ptr<Object_type> p, std::vector<int> &&d) : base_type(p), dim(std::move(d))
{
    init_size();
}

Type_class Array_type::get_type_class() const
{
    return Type_class::T_array;
}

size_t Array_type::get_size() const
{
    return size;
}

bool Array_type::is_base_var_type() const
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


Function_type::Function_type(const std::shared_ptr<Object_type> rtp, const std::vector<std::shared_ptr<Object_type>> &ptl) : return_type(rtp), param_type_list(ptl)
{
}

Function_type::Function_type(const std::shared_ptr<Object_type> rtp, std::vector<std::shared_ptr<Object_type>> &&ptl) : return_type(rtp), param_type_list(std::move(ptl))
{
}

Type_class Function_type::get_type_class() const
{
    return Type_class::T_function;
}

bool Function_type::is_base_var_type() const
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

Type_class Int_type::get_type_class() const
{
    return Type_class::T_int;
}

bool Int_type::is_base_var_type() const
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

Type_class Float_type::get_type_class() const
{
    return Type_class::T_float;
}

bool Float_type::is_base_var_type() const
{
    return true;
}

std::string Float_type::to_string() const
{
    return std::string("float");
}



std::shared_ptr<Object_type> Type::type_max(std::shared_ptr<Object_type> t1, std::shared_ptr<Object_type> t2)
{
    if (t1->get_type_class() == Type_class::T_float || t2->get_type_class() == Type_class::T_float)
        return std::make_shared<Float_type>();
    else
        return std::make_shared<Int_type>();
}