#include "Type.h"
#include "Semantic.h"
#include "Frontend_util.h"

Type_class Void_type::get_type_class() const
{
    return Type_class::T_void;
}

int Void_type::get_size() const
{
    return 0;
}

std::string Void_type::to_string() const
{
    return std::string("void");
}


Reference_type::Reference_type(const std::shared_ptr<Type> p) : base_type(p)
{
}

Type_class Reference_type::get_type_class() const
{
    return Type_class::T_reference;
}

int Reference_type::get_size() const
{
    return 4;
}

std::string Reference_type::to_string() const
{
    return base_type->to_string() + "&";
}

std::shared_ptr<Type> Reference_type::get_base_type() const
{
    return base_type;
}


void Array_type::init_size()
{
    unsigned long long siz = 1;
    for (auto e : dim)
        siz *= e;
    siz *= base_type->get_size();
    if (siz > INT32_MAX)
        Frontend_util::report_error("数组过大");
    size = (int)siz;

    element_size.resize(dim.size());
    element_size[dim.size() - 1] = base_type->get_size();
    for (auto i = dim.size() - 1; i > 0; --i)
        element_size[i - 1] = element_size[i] * dim[i];
}

Array_type::Array_type(const std::shared_ptr<Type> p, const std::vector<int> &d) : base_type(p), dim(d)
{
    init_size();
}

Array_type::Array_type(const std::shared_ptr<Type> p, std::vector<int> &&d) : base_type(p), dim(std::move(d))
{
    init_size();
}

Type_class Array_type::get_type_class() const
{
    return Type_class::T_array;
}

int Array_type::get_size() const
{
    return size;
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

// pos：访问下标列表的大小
std::shared_ptr<Type> Array_type::get_access_element_type(const size_t pos) const
{
    if (pos > dim.size())
        Frontend_util::report_internal_error("get_access_element_type overflow");
    else if (pos == dim.size())  // 访问到数组元素
        return base_type;
    else  // 访问到子数组名
    {
        std::vector<int> sub;
        for (size_t i = pos; i < dim.size(); ++i)
            sub.push_back(dim[i]);
        return std::make_shared<Array_type>(base_type, std::move(sub));
    }
}

int Array_type::get_access_element_size(const size_t pos) const
{
    return element_size[pos];
}

size_t Array_type::get_dim_size() const
{
    return dim.size();
}

Function_type::Function_type(const std::shared_ptr<Type> rtp, const std::vector<std::shared_ptr<Type>> &ptl) : return_type(rtp), param_type_list(ptl)
{
}

Function_type::Function_type(const std::shared_ptr<Type> rtp, std::vector<std::shared_ptr<Type>> &&ptl) : return_type(rtp), param_type_list(std::move(ptl))
{
}

Type_class Function_type::get_type_class() const
{
    return Type_class::T_function;
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

int Function_type::get_size() const
{
    return 0;
}


int Int_type::get_size() const
{
    return 4;
}

Type_class Int_type::get_type_class() const
{
    return Type_class::T_int;
}

std::string Int_type::to_string() const
{
    return std::string("int");
}


int Float_type::get_size() const
{
    return 4;
}

Type_class Float_type::get_type_class() const
{
    return Type_class::T_float;
}

std::string Float_type::to_string() const
{
    return std::string("float");
}



std::shared_ptr<Type> Type::type_max(std::shared_ptr<Type> t1, std::shared_ptr<Type> t2)
{
    if (t1->get_type_class() == Type_class::T_float || t2->get_type_class() == Type_class::T_float)
        return std::make_shared<Float_type>();
    else
        return std::make_shared<Int_type>();
}

bool Type::is_base_var_type(const std::shared_ptr<Type> type)
{
    return type->get_type_class() == Type_class::T_int || type->get_type_class() == Type_class::T_float;
}