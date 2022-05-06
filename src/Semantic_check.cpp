#include "Semantic_check.h"

#include <cstdio>

void Binary_expr_checker::check()
{
    for (int i = 0; i < 2; ++i)
    {
        if (exp[i]->need_semantic_check() == false)
            continue;
            
        if (exp[i]->value_type()->is_arith_type() == false)
        {
            printf("表达式 %s 必须具有算术类型\n", exp[i]->get_name().c_str());
            break;
        }
    }
}