#include "Frontend_util.h"

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