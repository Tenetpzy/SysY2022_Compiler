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
    virtual bool is_base_var_type() const = 0;
    virtual std::string to_string() const = 0;  // 编译器输出信息使用

    // 得到t1, t2的最大类型(目前为int提升为float)
    static std::shared_ptr<Object_type> type_max(std::shared_ptr<Object_type> t1, std::shared_ptr<Object_type> t2);
};

class Object_type : public Type
{
public:
    virtual size_t get_size() const = 0;
};

// 兼容返回void的函数调用表达式，将void类型视为特殊的对象类型
class Void_type : public Object_type
{
public:
    Void_type() = default;
    ~Void_type() = default;
    Type_class get_type_class() const override;
    size_t get_size() const override;
    bool is_base_var_type() const override;
    std::string to_string() const override;
};

class Reference_type : public Object_type
{
private:
    std::shared_ptr<Object_type> base_type;

public:
    Reference_type(const std::shared_ptr<Object_type> p);
    ~Reference_type() = default;
    Type_class get_type_class() const override;
    size_t get_size() const override;  // 使用指针实现引用，则为平台上指针的大小
    bool is_base_var_type() const override;
    std::string to_string() const override;

    std::shared_ptr<Object_type> get_base_type() const;
    // something more...
    // get_base_type
    // get_base_type_class
};

class Array_type : public Object_type
{
private:
    std::shared_ptr<Object_type> base_type;
    size_t size;
    std::vector<int> dim; // 每一维度的大小

    void init_size();

public:
    Array_type(const std::shared_ptr<Object_type> p, const std::vector<int> &d);
    Array_type(const std::shared_ptr<Object_type> p, std::vector<int> &&d);
    ~Array_type() = default;

    Type_class get_type_class() const override;
    size_t get_size() const override;
    bool is_base_var_type() const override;
    std::string to_string() const override;

    // something more...
    // get_base_type
    // get_base_type_class
};

class Function_type : public Type
{
private:
    std::shared_ptr<Object_type> return_type;
    std::vector<std::shared_ptr<Object_type>> param_type_list;

public:
    Function_type(const std::shared_ptr<Object_type> rtp, const std::vector<std::shared_ptr<Object_type>> &ptl);
    Function_type(const std::shared_ptr<Object_type> rtp, std::vector<std::shared_ptr<Object_type>> &&ptl);
    ~Function_type() = default;

    Type_class get_type_class() const override;
    bool is_base_var_type() const override;
    std::string to_string() const override;

    // something more...
};

class Int_type : public Object_type
{
public:
    Int_type() = default;
    ~Int_type() = default;

    size_t get_size() const override;
    Type_class get_type_class() const override;
    bool is_base_var_type() const override;
    std::string to_string() const override;
};

class Float_type : public Object_type
{
public:
    Float_type() = default;
    ~Float_type() = default;

    size_t get_size() const override;
    Type_class get_type_class() const override;
    bool is_base_var_type() const override;
    std::string to_string() const override;
};