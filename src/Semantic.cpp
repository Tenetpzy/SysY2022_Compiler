#include "Semantic.h"
#include "Frontend_environment.h"
#include <cstdio>

Binary_arith_expr::Binary_arith_expr(const char _op, const std::shared_ptr<Expr> &e1, const std::shared_ptr<Expr> &e2) : op(_op), exp({e1, e2})
{
    // 语义检查, 子表达式必须具有算术类型
    for (auto &e : exp)
    {
        if (e->value_type()->is_arith_type() == false)
            Frontend_util::report_error("表达式 %s 必须具有算术类型，而它的类型为 %s", e->to_string().c_str(), e->value_type_name().c_str());
    }

    // 合并两个子表达式的TAC
    for (auto &e : exp)
    {
        reduce_tac.splice(reduce_tac.end(), e->reduce_tac_list());
        reduce_tac.splice(reduce_tac.end(), e->cal_value_tac_list());
    }
    
    // 得到表达式值类型（可能做类型提升）
    Type_name res_type = Type::type_max(exp[0]->value_type_class(), exp[1]->value_type_class());
    
}