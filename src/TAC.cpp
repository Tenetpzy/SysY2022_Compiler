#include "TAC.h"
#include "Symbol.h"
#include "Semantic.h"
#include "Frontend_util.h"
#include <cstdio>

void TAC_bin_arith::print() const
{
    printf("%s = %s %s %s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str(), Frontend_util::op_to_expr_str(op).c_str(), operands[2]->to_string().c_str());
}

void TAC_bin_rel::print() const
{
    printf("%s = %s %s %s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str(), Frontend_util::op_to_expr_str(op).c_str(), operands[2]->to_string().c_str());
}

void TAC_mod::print() const
{
    printf("%s = %s %s %s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str(), "%", operands[2]->to_string().c_str());
}

void TAC_load_offset::print() const
{
    printf("%s = %s[%s]", operands[0]->to_string().c_str(), operands[1]->to_string().c_str(), operands[2]->to_string().c_str());
}

void TAC_store_offset::print() const
{
    printf("%s[%s] = %s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str(), operands[2]->to_string().c_str());
}

void TAC_neg::print() const
{
    printf("%s = -%s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str());
}

void TAC_copy::print() const
{
    printf("%s = %s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str());
}

void TAC_lea::print() const
{
    printf("%s = &%s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str());
}

void TAC_load::print() const
{
    printf("%s = *%s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str());
}

void TAC_store::print() const
{
    printf("*%s = %s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str());
}

void TAC_goto::print() const
{
    printf("goto %s", operands[0]->to_string().c_str());
}

void TAC_if::print() const
{
    printf("if %s goto %s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str());
}

void TAC_ifz::print() const
{
    printf("ifz %s goto %s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str());
}

void TAC_label::print() const
{
    printf("label %s", operands[0]->to_string().c_str());
}

void TAC_var_decl::print() const
{
    printf("var %s %s", operands[0]->get_type()->to_string().c_str(), operands[0]->to_string().c_str());
}

void TAC_formal_decl::print() const
{
    printf("formal %s %s", operands[0]->get_type()->to_string().c_str(), operands[0]->to_string().c_str());
}

void TAC_actual_decl::print() const
{
    printf("actual %s", operands[0]->to_string().c_str());
}

void TAC_call_ret::print() const
{
    printf("%s = call %s", operands[0]->to_string().c_str(), operands[1]->to_string().c_str());
}

void TAC_call_noret::print() const
{
    printf("call %s", operands[0]->to_string().c_str());
}

void TAC_return::print() const
{
    printf("return %s", operands[0]->to_string().c_str());
}

void TAC_fun_begin::print() const
{
    printf("begin");
}

void TAC_fun_end::print() const
{
    printf("end");
}