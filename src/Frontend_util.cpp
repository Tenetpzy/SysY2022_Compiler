#include "Frontend_util.h"
#include "Sym_environment.h"
#include "Semantic.h"
#include "Type.h"
#include "Symbol.h"

Sym_environment* Frontend_util::sym_env = nullptr;

std::unordered_map<Op_type, std::string> Frontend_util::op_expr_str = {
    {Op_type::add, "+"},
    {Op_type::sub, "-"},
    {Op_type::mul, "*"},
    {Op_type::div, "/"},
    {Op_type::mod, "%"},
    {Op_type::le, "<"},
    {Op_type::leq, "<="},
    {Op_type::ge, ">"},
    {Op_type::geq, ">="},
    {Op_type::eq, "=="},
    {Op_type::neq, "!="},
    {Op_type::L_and, "&&"},
    {Op_type::L_or, "||"},
    {Op_type::L_not, "!"}
};

Sym_environment* Frontend_util::generate_sym_env()
{
    return new Sym_environment_trie();
}

bool Frontend_util::is_arith_op(const Op_type op)
{
    return op <= Op_type::mod;
}

bool Frontend_util::is_rel_op(const Op_type op)
{
    return op >= Op_type::le && op <= Op_type::neq;
}

bool Frontend_util::is_logic_op(const Op_type op)
{
    return op >= Op_type::L_and;
}


Type_converter::Type_converter_ret_type Type_converter::convert(const Type_class sourceType, const Type_class TargetType, const std::shared_ptr<Symbol> sourceSym)
{
    // auto it = convert_handler.find(std::make_pair(sourceType, sourceType));

    // // 没有找到类型转化器，直接返回该Symbol与空的TAC list
    // if (it == convert_handler.end())
    //     return std::make_pair(sourceSym, std::list<std::shared_ptr<TAC>>());
    
    // // 否则，调用对应的类型转化器
    // return it->second(sourceSym);


    // 简单点的做法
    if (sourceType == Type_class::T_int && TargetType == Type_class::T_float)
        return convert_int_to_float(sourceSym);
    else if (sourceType == Type_class::T_float && TargetType == Type_class::T_int)
        return convert_float_to_int(sourceSym);
    else
        return std::make_pair(sourceSym, std::list<std::shared_ptr<TAC>>());
}

std::shared_ptr<Symbol> Tmp_symbol_generator::gen_expr_sym_object(std::shared_ptr<Type> type)
{
    std::string name = "t" + std::to_string(++var_counter);
    return std::make_shared<Sym_object>(type, std::move(name));
}