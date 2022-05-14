#include "Semantic.h"
#include "Frontend_util.h"
#include "Sym_environment.h"
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
            if (e->value_type()->is_base_var_type() == false)
                Frontend_util::report_error("表达式 %s 必须具有算术类型，而它的类型为 %s", e->to_string().c_str(), e->value_type_name().c_str());
    }

    // 编译时常量传播
    if (exp[0]->is_literal_num_expr() && exp[1]->is_literal_num_expr())
    {
        Frontend_util::report_internal_error("暂不支持常量传播");
    }

    else 
    {
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
}

std::string Binary_arith_rel_expr::to_string() const
{
    return exp[0]->to_string() + Frontend_util::op_to_expr_str(op) + exp[1]->to_string();
}

Unary_arith_expr::Unary_arith_expr(const Op_type _op, const std::shared_ptr<Expr> expr) : op(_op), exp(expr)
{
    if (exp->value_type()->is_base_var_type() == false)
        Frontend_util::report_error("表达式 %s 必须具有算术类型，而它的类型为 %s", exp->to_string().c_str(), exp->value_type_name().c_str());
    
    // 编译时常量传播
    if (exp->is_literal_num_expr())
    {
        Frontend_util::report_internal_error("暂不支持常量传播");
    }

    else
    {
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
}

std::string Unary_arith_expr::to_string() const
{
    return std::string() + Frontend_util::op_to_expr_str(op) + exp->to_string(); 
}

// 编译器正确运行时，不会进入包含report_internal_error的分支
Primary_expr::Primary_expr(const std::string &ident, const Sym_type sym_type)
{
    // 表达式为字面常量：一个字符串形式的整数或浮点数
    // 值为代表该常量的Symbol
    // 得到值时无需额外计算
    if (Symbol::is_literal_num_sym_type(sym_type))
        value = sym = Tmp_symbol_generator::gen_sym_literal_num(sym_type, ident);
    
    // 表达式为标识符
    else if (sym_type == Sym_type::Sym_object)
    {
        // 在符号表中查找标识符
        auto &sym_env = Frontend_env::get_var_env();
        sym = sym_env.get_symbol(ident);

        if (!sym)
            Frontend_util::report_error("未定义标识符 %s", ident.c_str());

        switch (sym->get_sym_type())
        {
        // 标识符为一个函数  变量环境不会出现
        // case Sym_type::Sym_function:
        //     Frontend_util::report_error("表达式不允许使用函数名。\n%s 为函数类型 %s", ident.c_str(), sym->get_type()->to_string().c_str());
        //     break;
        
        // 标识符为一个变量名
        case Sym_type::Sym_object:
        {   // case 中定义局部变量，需要限制作用域

            // 得到变量名的类型对象
            std::shared_ptr<Type> var_type = sym->get_type();

            // 变量为基本类型变量(int/float)
            if (var_type->is_base_var_type())
            {
                // 变量被声明为const
                // 编译时常量传播，表达式的值为直接包含常量值的Sym_int或Sym_float...
                if (var_type->is_const_type())
                {
                    Frontend_util::report_internal_error("暂不支持常量传播");
                }

                // 普通变量(int x)
                // 表达式的值为该变量符号本身
                else
                    value = sym;
            }

            // 变量为一个数组，此时表达式指代数组名
            else if (var_type->get_type_class() == Type_class::T_array)
            {
                // 表达式的值为数组的引用（数组的首地址）
                // 得到表达式值的tac:
                // var pointer t0
                // t0 = &sym
                auto val_type = std::make_shared<Reference_type>(var_type);
                value = Tmp_symbol_generator::gen_expr_sym_object(val_type);
                gen_val_tac.push_back(std::make_shared<TAC_var_decl>(value));
                gen_val_tac.push_back(std::make_shared<TAC_lea>(value, sym));
            }

            // 变量为一个指针（引用）
            // 在SysY2022中，只可能是作为函数的数组类型参数
            else if (var_type->get_type_class() == Type_class::T_reference)
            {
                auto ref_type = std::dynamic_pointer_cast<Reference_type>(var_type);
                if (ref_type->get_base_type()->get_type_class() != Type_class::T_array)
                    Frontend_util::report_internal_error("变量 %s 为非数组的引用，引用类型为 %s", ident.c_str(), ref_type->get_base_type()->to_string().c_str());

                // 表达式的值为数组的地址，即Sym本身
                value = sym;
            }

            else
                Frontend_util::report_internal_error("变量 %s 的类型 %s 非法", ident.c_str(), var_type->to_string().c_str());

            break;
        }

        // 标识符既不是函数，也不是变量名
        default:
            Frontend_util::report_internal_error("环境中包含了非法符号 %s，类型编号为 %d", ident.c_str(), int(sym->get_sym_type()));
            break;
        }
    }
}


void Access_array_expr::init(const std::string &ident)
{
    // ident语义检查
    auto &sym_env = Frontend_env::get_var_env();
    array = sym_env.get_symbol(ident);

    if (!array)
        Frontend_util::report_error("未定义标识符 %s", ident.c_str());
    
    std::shared_ptr<Type> array_type;   // 临时保存数组类型
    switch (array->get_type()->get_type_class())
    {

    // array为一个数组变量，则为array_addr创建一个引用类型对象，作为array首地址
    case Type_class::T_array: 
    {
        array_type = array->get_type();

        std::shared_ptr<Type> array_addr_type = std::make_shared<Reference_type>(array_type);
        array_addr = Tmp_symbol_generator::gen_expr_sym_object(array_addr_type);
        reduce_tac.push_back(std::make_shared<TAC_var_decl>(array_addr));

        // array_addr = &array
        reduce_tac.push_back(std::make_shared<TAC_lea>(array_addr, array));
        break;
    }

    // array本身就是到数组的引用，用其初始化array_addr即可
    case Type_class::T_reference:
        array_addr = array;
        array_type = std::dynamic_pointer_cast<Reference_type>(array->get_type())->get_base_type();
        break;

    // 否则，array不是数组类型
    default:
        Frontend_util::report_error("标识符 %s 的类型为 %s，不能转换为数组类型", ident.c_str(), array->get_type()->to_string().c_str());
        break;
    }

    // 下标表达式语义检查
    auto &access_expr_list = arr_access_list.get_list();
    for (auto &expr : access_expr_list)
    {
        if (expr->value_type_class() != Type_class::T_int)
            Frontend_util::report_error("作为数组下标的表达式必须为整型，而表达式 %s 的类型为 %s", expr->to_string().c_str(), expr->value_type_name().c_str());
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

    // 如果数组访问表达式为子数组的名字(int a[2][2], 表达式a[1])
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



Var_decl::Var_decl(const std::shared_ptr<Type> basetype, Var_decl_item &item) : base_type(basetype) 
{ 
    if (base_type->get_type_class() == Type_class::T_void)
        Frontend_util::report_error("变量不能定义为void类型");
    do_new_decl(item); 
}

Var_decl::Var_decl(Var_decl &pre, Var_decl_item &item) : decl_tac_list(std::move(pre.decl_tac_list)), base_type(pre.base_type) 
{ 
    do_new_decl(item); 
}

std::list<std::shared_ptr<TAC_var_decl>>& Var_decl::get_decl_tac_list()
{
    return decl_tac_list;
}

void Var_decl::do_new_decl(Var_decl_item &item)
{
    auto &var_env = Frontend_env::get_var_env();
    auto sym = var_env.get_sym_in_current_env(item.name);

    if (sym)
        Frontend_util::report_error("标识符 %s 已声明，类型为 %s", item.name.c_str(), sym->get_type()->to_string().c_str());
    
    std::shared_ptr<Type> var_type;

    // 声明一个变量
    if (item.access_list.empty())
        var_type = base_type;

    // 声明一个数组
    else
    {
        std::vector<int> dim;
        for (auto &expr : item.access_list)
        {
            if (expr->get_value()->get_sym_type() != Sym_type::Sym_int)
                Frontend_util::report_error("数组维度长度必须为非负整数");
            auto sym_int = std::dynamic_pointer_cast<Sym_int>(expr->get_value());
            int val = sym_int->get_value();
            if (val <= 0)
                Frontend_util::report_error("数组维度长度必须为非负整数");
            dim.push_back(val);
        }
        var_type = std::make_shared<Array_type>(base_type, std::move(dim));
    }

    sym = std::make_shared<Sym_object>(var_type, item.name, var_env.current_env_tag());
    var_env.add_symbol(item.name, sym);

    decl_tac_list.push_back(std::make_shared<TAC_var_decl>(sym));
}




// Ident_ref_expr::Ident_ref_expr(const std::shared_ptr<Symbol> ptr) : pointer(ptr)
// {   
//     std::shared_ptr<Type> base_type;

//     // 符号ptr的type应是一个引用type
//     if (auto rt = std::dynamic_pointer_cast<Reference_type>(pointer->get_type()))
//         base_type = rt->get_base_type();  // 得到引用的基类型
    
//     // debug used
//     else
//         Frontend_util::report_internal_error("runtime error: Ident_ref_expr constructor.");


//     // 表达式值是引用对象值的拷贝
//     value = Tmp_symbol_generator::gen_expr_sym_object(base_type);
//     gen_val_tac.push_back(std::make_shared<TAC_var_decl>(value));

//     // value = *ptr
//     // 引用表达式作为右值使用时，创建一个临时对象(即此处的表达式值value)，并拷贝对象的值到value
//     gen_val_tac.push_back(std::make_shared<TAC_load>(value, pointer));
// }