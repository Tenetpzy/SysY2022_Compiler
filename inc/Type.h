#pragma once

#include <vector>
#include <memory>

enum class Type_class
{
    T_int,
    T_float,
    T_reference,
    T_array,
    T_function,
    T_void,
};

class Type
{
public:
    virtual Type_class get_type_class() const = 0;
    virtual int get_size() const = 0;
    virtual std::string to_string() const = 0;  // 编译器输出信息使用
    virtual bool is_base_var_type() const
    {
        return false;
    }

    virtual bool is_const_type() const
    {
        return false;
    }

    // 得到t1, t2的最大类型(目前为int提升为float)
    static std::shared_ptr<Type> type_max(std::shared_ptr<Type> t1, std::shared_ptr<Type> t2);
};

// 兼容返回void的函数调用表达式，将void类型视为特殊的对象类型
class Void_type : public Type
{
public:
    Void_type() = default;
    ~Void_type() = default;
    Type_class get_type_class() const override;
    int get_size() const override;
    std::string to_string() const override;
};

class Reference_type : public Type
{
private:
    std::shared_ptr<Type> base_type;

public:
    Reference_type(const std::shared_ptr<Type> p);
    ~Reference_type() = default;
    Type_class get_type_class() const override;
    int get_size() const override;  // 使用指针实现引用，则为平台上指针的大小
    std::string to_string() const override;

    std::shared_ptr<Type> get_base_type() const;
    // something more...
    // get_base_type
    // get_base_type_class
};

class Array_type : public Type
{
private:
    std::shared_ptr<Type> base_type;
    int size;
    std::vector<int> dim; // 每一维度的大小
    std::vector<int> element_size;  // 维度大小 后缀积

    void init_size();

public:
    Array_type(const std::shared_ptr<Type> p, const std::vector<int> &d);
    Array_type(const std::shared_ptr<Type> p, std::vector<int> &&d);
    ~Array_type() = default;

    Type_class get_type_class() const override;
    int get_size() const override;
    std::string to_string() const override;

    // 当访问列表作用于数组时，得到访问的元素类型
    std::shared_ptr<Type> get_access_element_type(const size_t pos) const;
    int get_access_element_size(const size_t pos) const;
    size_t get_dim_size() const;

    // something more...
    // get_base_type
    // get_base_type_class
};

class Function_type : public Type
{
private:
    std::shared_ptr<Type> return_type;
    std::vector<std::shared_ptr<Type>> param_type_list;

public:
    Function_type(const std::shared_ptr<Type> rtp, const std::vector<std::shared_ptr<Type>> &ptl);
    Function_type(const std::shared_ptr<Type> rtp, std::vector<std::shared_ptr<Type>> &&ptl);
    ~Function_type() = default;

    Type_class get_type_class() const override;
    int get_size() const override;
    std::string to_string() const override;

    // something more...
};

class Int_type : public Type
{
public:
    Int_type() = default;
    ~Int_type() = default;

    int get_size() const override;
    Type_class get_type_class() const override;
    std::string to_string() const override;

    bool is_base_var_type() const override
    {
        return true;
    }
};

class Float_type : public Type
{
public:
    Float_type() = default;
    ~Float_type() = default;

    int get_size() const override;
    Type_class get_type_class() const override;
    std::string to_string() const override;

    bool is_base_var_type() const override
    {
        return true;
    }
};

class Const_type : public Type
{
private:
    std::shared_ptr<Type> base_type;  // const 修饰的类型

public:
    Const_type(const std::shared_ptr<Type> baseType);
    ~Const_type() = default;

    int get_size() const override;
    Type_class get_type_class() const override;
    std::string to_string() const override;

    bool is_base_var_type() const override
    {
        return base_type->is_base_var_type();
    }

    bool is_const_type() const override
    {
        return true;
    }
};