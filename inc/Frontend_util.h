#pragma once

#include <cstdio>
#include <cstdarg>
#include <utility>
#include <list>
#include <unordered_map>
#include <memory>

extern int yylineno;
extern int yycolno;

// forward declarations

class Sym_environment;
enum class Op_type;
enum class Type_class;
class Symbol;
class TAC;
class Type;

class Frontend_util
{
private:
    static Sym_environment *sym_env;
    static std::unordered_map<Op_type, std::string> op_expr_str;

private:
    static Sym_environment* generate_sym_env();

public:
    static Sym_environment& get_sym_env()
    {
        if (sym_env == nullptr)
            sym_env = generate_sym_env();
        return *sym_env;
    }

    static const std::string& op_to_expr_str(const Op_type op)
    {
        return op_expr_str[op];
    }

    static bool is_arith_op(const Op_type op);

    static bool is_rel_op(const Op_type op);

    static bool is_logic_op(const Op_type op);

    // 语义错误
    static void report_error(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        fprintf(stderr, "error at line: %d, column: %d\n", yylineno, yycolno);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
        exit(0);
    }

    // 编译器内部逻辑错误时使用
    static void report_internal_error(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        fprintf(stderr, "internal error:\n");
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
        exit(0);
    }

};



// template<>
// struct std::hash<std::pair<Type_class, Type_class>>
// {
//     std::size_t operator()(const std::pair<Type_class, Type_class> &Tp_pair) const
//     {
//         return std::hash<Type_class>()(Tp_pair.first) ^ (std::hash<Type_class>()(Tp_pair.second) << 1);
//     }
// };

// template<>
// struct std::equal_to<std::pair<Type_class, Type_class>>
// {
//     bool operator()(const std::pair<Type_class, Type_class> &lhs, const std::pair<Type_class, Type_class> &rhs) const
//     {
//         return lhs.first == rhs.first && lhs.second == rhs.second;
//     }
// };

class Type_converter
{
public:
    using Type_converter_ret_type = std::pair<std::shared_ptr<Symbol>, std::list<std::shared_ptr<TAC>>>;

private:
    static Type_converter_ret_type convert_int_to_float(const std::shared_ptr<Symbol> source)
    {
        // 暂不实现
        Frontend_util::report_internal_error("暂时不支持浮点运算。");
    }

    static Type_converter_ret_type convert_float_to_int(const std::shared_ptr<Symbol> source)
    {
        // 暂不实现
        Frontend_util::report_internal_error("暂时不支持浮点运算。");
    }



public: 
//    using Convert_handler_type = std::unordered_map<std::pair<Type_class, Type_class>, std::function<Type_converter_ret_type(const std::shared_ptr<Symbol>)>>;

private:
    // 把原类型和目标类型的pair映射到相应转化器
//    static Convert_handler_type convert_handler;

public:

    static Type_converter_ret_type convert(const Type_class sourceType, const Type_class TargetType, const std::shared_ptr<Symbol> sourceSym);
};



class Tmp_symbol_generator
{
private:
    static unsigned long long var_counter;
    static unsigned long long label_counter;

public:
    static std::shared_ptr<Symbol> gen_expr_sym_object(std::shared_ptr<Type> type);
};