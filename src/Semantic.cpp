#include "Semantic.h"
#include "Frontend_util.h"
#include "TAC.h"
#include <cstdio>
#include <unordered_map>

Binary_arith_rel_expr::Binary_arith_rel_expr(const Op_type _op, const std::shared_ptr<Expr> e1, const std::shared_ptr<Expr> e2) : op(_op), exp({e1, e2})
{
    // 语义检查
    if (op == Op_type::mod)
    {
        for (auto &e : exp)
            if (e->value_type_class() != Type_class::T_int)
                Frontend_util::report_error("表达式 %s 必须具有整数类型，而它的类型为 %s", e->to_string().c_str(), e->value_type_name().c_str());
    }
    else
    {
        for (auto &e : exp)
            if (Type::is_base_var_type(e->value_type()) == false)
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
    std::shared_ptr<Symbol> operands[2]{exp[0]->get_value(), exp[1]->get_value()};
    
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

    // 得到一个临时变量作为value
    value = Tmp_symbol_generator::gen_expr_sym_object(res_type);
    reduce_tac.push_back(std::make_shared<TAC_var_decl>(value));
    
    // 生成对应op的三地址码
    std::shared_ptr<TAC> code;
    if (op == Op_type::mod)
        code = std::make_shared<TAC_mod>(value, operands[0], operands[1]);
    else if (Frontend_util::is_arith_op(op))
        code = std::make_shared<TAC_bin_arith>(op, value, operands[0], operands[1]);
    else
        code = std::make_shared<TAC_bin_rel>(op, value, operands[0], operands[1]);

    reduce_tac.push_back(code);
}

std::string Binary_arith_rel_expr::to_string() const
{
    return exp[0]->to_string() + Frontend_util::op_to_expr_str(op) + exp[1]->to_string();
}

Unary_arith_expr::Unary_arith_expr(const Op_type _op, const std::shared_ptr<Expr> expr) : op(_op), exp(expr)
{
    if (Type::is_base_var_type(exp->value_type()) == false)
        Frontend_util::report_error("表达式 %s 必须具有算术类型，而它的类型为 %s", exp->to_string().c_str(), exp->value_type_name().c_str());
    
    reduce_tac.splice(reduce_tac.end(), exp->reduce_tac_list());
    reduce_tac.splice(reduce_tac.end(), exp->gen_value_tac_list());

    auto res_type = exp->value_type();
    auto operand = exp->get_value();

    switch (op)
    {
        // + exp，不用做额外的工作
    case Op_type::add:
        value = operand;
        break;
    
    case Op_type::sub:
        value = Tmp_symbol_generator::gen_expr_sym_object(res_type);
        reduce_tac.push_back(std::make_shared<TAC_var_decl>(value));
        reduce_tac.push_back(std::make_shared<TAC_neg>(value, operand));
        break;

    default:
        Frontend_util::report_error("未识别的算术运算符：%c", op);
        break;
    }
}

std::string Unary_arith_expr::to_string() const
{
    return std::string() + Frontend_util::op_to_expr_str(op) + exp->to_string(); 
}

Ident_ref_expr::Ident_ref_expr(const std::shared_ptr<Symbol> ptr) : pointer(ptr)
{   
    std::shared_ptr<Type> base_type;

    // 符号ptr的type应是一个引用type
    if (auto rt = std::dynamic_pointer_cast<Reference_type>(pointer->get_type()))
        base_type = rt->get_base_type();  // 得到引用的基类型
    
    // debug used
    else
        Frontend_util::report_internal_error("runtime error: Ident_ref_expr constructor.");


    // 表达式值是引用对象值的拷贝
    value = Tmp_symbol_generator::gen_expr_sym_object(base_type);
    gen_val_tac.push_back(std::make_shared<TAC_var_decl>(value));

    // value = *ptr
    // 引用表达式作为右值使用时，创建一个临时对象(即此处的表达式值value)，并拷贝对象的值到value
    gen_val_tac.push_back(std::make_shared<TAC_load>(value, pointer));
}

void Access_array_expr::init()
{
    // 下标表达式语义检查
    auto &access_expr_list = arr_access_list.get_list();
    for (auto &expr : access_expr_list)
    {
        if (expr->value_type_class() != Type_class::T_int)
            Frontend_util::report_error("作为数组下标的表达式必须为整型，而表达式 %s 的类型为 %s", expr->to_string().c_str(), expr->value_type_name().c_str());
    }


    // 初始化数组首地址变量与访问的数组的类型
    std::shared_ptr<Type> array_type;
    // array本身就是到数组的引用，用其初始化array_addr即可
    if (array->get_type()->get_type_class() == Type_class::T_reference)
    {
        array_addr = array;
        array_type = std::dynamic_pointer_cast<Reference_type>(array->get_type())->get_base_type();
    }
    // array直接指代数组，则为array_addr创建一个引用类型对象
    else
    {
        array_type = array->get_type();

        std::shared_ptr<Type> array_addr_type = std::make_shared<Reference_type>(array_type);
        array_addr = Tmp_symbol_generator::gen_expr_sym_object(array_addr_type);
        reduce_tac.push_back(std::make_shared<TAC_var_decl>(array_addr));

        // array_addr = &array
        reduce_tac.push_back(std::make_shared<TAC_lea>(array_addr, array));
    }
    // 将array_type转为指向数组类型的指针，方便后续使用
    std::shared_ptr<Array_type> arr_type = std::dynamic_pointer_cast<Array_type>(array_type);


    // 得到访问的元素的类型（子数组或数组元素）
    if (access_expr_list.size() > arr_type->get_dim_size())
        Frontend_util::report_error("非法的数组元素访问。其中数组类型为 %s，表达式类型为 %s", arr_type->to_string().c_str(), arr_access_list.to_string().c_str());

    std::shared_ptr<Type> access_element_type = arr_type->get_access_element_type(access_expr_list.size());
    

    // 得到数组访问的三地址码
    // 对下标表达式依序求值
    // 计算出地址偏移量，最终结果在offset中
    if (access_expr_list.size() > 0)
    {
        std::shared_ptr<Type> offset_type = std::make_shared<Int_type>();

        // 对expr0求值，得到值 i0
        // var t0
        // t0 = i0 * element_size[0](constant)
        auto &expr0 = access_expr_list[0];
        reduce_tac.splice(reduce_tac.end(), expr0->reduce_tac_list());
        reduce_tac.splice(reduce_tac.end(), expr0->gen_value_tac_list());

        offset = Tmp_symbol_generator::gen_expr_sym_object(offset_type);
        reduce_tac.push_back(std::make_shared<TAC_var_decl>(offset));

        reduce_tac.push_back(std::make_shared<TAC_bin_arith>(Op_type::mul, offset, expr0->get_value(), std::make_shared<Sym_int>(arr_type->get_access_element_size(0))));

        // var ti, tj
        std::shared_ptr<Symbol> offset_i, offset_j;
        if (access_expr_list.size() > 1)
        {
            offset_i = Tmp_symbol_generator::gen_expr_sym_object(offset_type);
            reduce_tac.push_back(std::make_shared<TAC_var_decl>(offset_i));
            offset_j = Tmp_symbol_generator::gen_expr_sym_object(offset_type);
            reduce_tac.push_back(std::make_shared<TAC_var_decl>(offset_j));
        }

        for (size_t i = 1; i < access_expr_list.size(); ++i)
        {
            auto &expr = access_expr_list[i];

            // 对expr求值，得到值 i
            reduce_tac.splice(reduce_tac.end(), expr->reduce_tac_list());
            reduce_tac.splice(reduce_tac.end(), expr->gen_value_tac_list());

            // ti = i * element_size[i]
            int element_size = arr_type->get_access_element_size(i);
            reduce_tac.push_back(std::make_shared<TAC_bin_arith>(Op_type::mul, offset, expr->get_value(), std::make_shared<Sym_int>(element_size)));

            // tj = ti-1(offset) + ti
            reduce_tac.push_back(std::make_shared<TAC_bin_arith>(Op_type::add, offset_j, offset, offset_i));

            // offset = tj(复用，暂不考虑SSA)
            reduce_tac.push_back(std::make_shared<TAC_copy>(offset, offset_j));
        }
    }


    // 得到计算下标表达式返回值的TAC

    // 如果数组访问表达式为子数组的名字(int a[2][2], 表达式a, a[1])
    // 表达式值隐式转换为指针(对于TAC层，引用类型的Symbol视作一个指针)
    if (access_element_type->get_type_class() == Type_class::T_array)
    {
        if (offset)
        {
            value = Tmp_symbol_generator::gen_expr_sym_object(std::make_shared<Reference_type>(access_element_type));
            gen_val_tac.push_back(std::make_shared<TAC_var_decl>(value));
            gen_val_tac.push_back(std::make_shared<TAC_bin_arith>(Op_type::add, value, array_addr, offset));
        }
        else
            value = array_addr;
    }
    // 数组表达式访问到数组元素(int a[2][2], a[1][1])
    // tmp = array_addr + offset
    // value = *tmp
    else
    {
        auto tmp = Tmp_symbol_generator::gen_expr_sym_object(std::make_shared<Reference_type>(access_element_type));
        gen_val_tac.push_back(std::make_shared<TAC_var_decl>(tmp));
        gen_val_tac.push_back(std::make_shared<TAC_bin_arith>(Op_type::add, tmp, array_addr, offset));

        value = Tmp_symbol_generator::gen_expr_sym_object(access_element_type);
        gen_val_tac.push_back(std::make_shared<TAC_var_decl>(value));
        gen_val_tac.push_back(std::make_shared<TAC_load>(value, tmp));
    }
}

