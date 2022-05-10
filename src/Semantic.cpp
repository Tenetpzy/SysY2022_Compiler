#include "Semantic.h"
#include "Frontend_util.h"
#include <cstdio>
#include <unordered_map>



Binary_arith_expr::Binary_arith_expr(const Op_type _op, const std::shared_ptr<Expr> e1, const std::shared_ptr<Expr> e2) : op(_op), exp({e1, e2})
{
    // 语义检查, 子表达式必须具有算术类型
    for (auto &e : exp)
    {
        if (e->value_type()->is_base_var_type() == false)
            Frontend_util::report_error("表达式 %s 必须具有算术类型，而它的类型为 %s", e->to_string().c_str(), e->value_type_name().c_str());
    }

    // 合并两个子表达式的TAC
    for (auto &e : exp)
    {
        reduce_tac.splice(reduce_tac.end(), e->reduce_tac_list());
        reduce_tac.splice(reduce_tac.end(), e->gen_value_tac_list());
    }
    
    // 得到表达式值类型（可能做类型提升）
    auto res_type = Type::type_max(exp[0]->value_type(), exp[1]->value_type());
    std::shared_ptr<Sym_operand> operands[2]{exp[0]->get_value(), exp[1]->get_value()};
    
    for (int i = 0; i < 2; ++i)
    {
        // 子表达式的值需要做类型转换后再参与运算
        if (exp[i]->value_type_class() != res_type->get_type_class())
        {
            auto conv = Type_converter::convert(exp[i]->value_type_class(), res_type->get_type_class(), exp[i]->get_value());
            operands[i] = conv.first;  // 更换操作数为类型转换后的操作数
            reduce_tac.splice(reduce_tac.end(), conv.second);  // 合并类型转换的TAC码
        }
    }

    // 得到一个临时变量
    value = Tmp_symbol_generator::gen_expr_sym_object(res_type);
    
    // 生成对应op的三地址码
    std::shared_ptr<TAC> code;
    switch (op)
    {
    case '+':
        code = std::make_shared<TAC_add>(value, operands[0], operands[1]);
        break;

    case '-':
        code = std::make_shared<TAC_sub>(value, operands[0], operands[1]);
        break;

    case '*':
        code = std::make_shared<TAC_mul>(value, operands[0], operands[1]);
        break;

    case '/':
        code = std::make_shared<TAC_div>(value, operands[0], operands[1]);
        break;

    case '%':
        
        code = std::make_shared<TAC_mod>(value, operands[0], operands[1]);
        break;
    
    default:
        Frontend_util::report_error("未识别的算术运算符：%c", op);
        break;
    }

    reduce_tac.push_back(code);
}

Unary_arith_expr::Unary_arith_expr(const Op_type _op, const std::shared_ptr<Expr> expr) : op(_op), exp(expr)
{
    if (exp->value_type()->is_base_var_type() == false)
        Frontend_util::report_error("表达式 %s 必须具有算术类型，而它的类型为 %s", exp->to_string().c_str(), exp->value_type_name().c_str());
    
    reduce_tac.splice(reduce_tac.end(), exp->reduce_tac_list());
    reduce_tac.splice(reduce_tac.end(), exp->gen_value_tac_list());

    auto res_type = exp->value_type();
    auto operand = exp->get_value();

    switch (op)
    {
        // + exp，不用做额外的工作
    case '+':
        value = operand;
        break;
    
    case '-':
        value = Tmp_symbol_generator::gen_expr_sym_object(res_type);
        reduce_tac.push_back(std::make_shared<TAC_neg>(value, operand));
        break;

    default:
        Frontend_util::report_error("未识别的算术运算符：%c", op);
        break;
    }
}

Ident_ref_expr::Ident_ref_expr(const std::shared_ptr<Sym_object> ptr) : pointer(ptr)
{
    /* debug */
    auto ref_type = ptr->get_type();
    if (ref_type->get_type_class() != Type_class::T_reference)
        Frontend_util::report_internal_error("变量引用表达式传入了非引用符号.");
    if (ref_type->is_base_var_type() == false)
        Frontend_util::report_internal_error("变量引用表达式传入了非变量引用符号.");
    /* debug */

    std::shared_ptr<Object_type> ref_base_type;
    if (std::shared_ptr<Reference_type> p = std::dynamic_pointer_cast<Reference_type>(ref_type))
        ref_base_type = p->get_base_type();
    else
        Frontend_util::report_internal_error("强制转换为指向Reference_type时出错.");
    

}