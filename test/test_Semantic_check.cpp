#include "gtest/gtest.h"
//#include "Semantic_check.h"

// TEST(Test_bin_exp_check, all_int_var_sub_exp)
// {
//     using namespace std;
//     shared_ptr<Sym_object> sym1 = make_shared<Sym_object>(make_shared<Int_type>());
//     shared_ptr<Sym_object> sym2 = make_shared<Sym_object>(make_shared<Int_type>());

//     shared_ptr<Expr> exp1 = make_shared<Lval_expr>(sym1, make_shared<string>("a"), NEED_SEMANTIC_CHECK);
//     shared_ptr<Expr> exp2 = make_shared<Lval_expr>(sym2, make_shared<string>("b"), NEED_SEMANTIC_CHECK);

//     Binary_expr_checker checker(exp1, exp2, Op_type::add);
//     checker.check();
// }

// TEST(Test_bin_exp_check, var_const_sub_exp)
// {
//     using namespace std;
//     shared_ptr<Sym_object> sym1 = make_shared<Sym_object>(make_shared<Int_type>());
//     shared_ptr<Sym_object> sym2 = make_shared<Sym_object>(make_shared<Int_type>());

//     shared_ptr<Expr> exp1 = make_shared<Lval_expr>(sym1, make_shared<string>("a"), NEED_SEMANTIC_CHECK);
//     shared_ptr<Expr> exp2 = make_shared<Const_int_expr>(1, make_shared<string>("b"), NEED_SEMANTIC_CHECK);

//     Binary_expr_checker checker(exp1, exp2, Op_type::add);
//     checker.check();
// }

// TEST(Test_bin_exp_check, var_refvar_sub_exp)
// {
//     using namespace std;
//     shared_ptr<Sym_object> sym1 = make_shared<Sym_object>(make_shared<Int_type>());
//     shared_ptr<Sym_object> sym2 = make_shared<Sym_object>(make_shared<Reference_type>(make_shared<Int_type>()));

//     shared_ptr<Expr> exp1 = make_shared<Lval_expr>(sym1, make_shared<string>("a"), NEED_SEMANTIC_CHECK);
//     shared_ptr<Expr> exp2 = make_shared<Lval_expr>(sym2, make_shared<string>("b"), NEED_SEMANTIC_CHECK);

//     Binary_expr_checker checker(exp1, exp2, Op_type::add);
//     checker.check();
// }

// TEST(Test_bin_exp_check, var_refarr_sub_exp)
// {
//     using namespace std;
//     shared_ptr<Sym_object> sym1 = make_shared<Sym_object>(make_shared<Int_type>());

//     shared_ptr<Array_type> arr_type = make_shared<Array_type>(make_shared<Int_type>(), vector<int>({1}));
//     shared_ptr<Sym_object> sym2 = make_shared<Sym_object>(make_shared<Reference_type>(arr_type));

//     shared_ptr<Expr> exp1 = make_shared<Lval_expr>(sym1, make_shared<string>("a"), NEED_SEMANTIC_CHECK);
//     shared_ptr<Expr> exp2 = make_shared<Rval_expr>(sym2, make_shared<string>("b[0]"), NEED_SEMANTIC_CHECK);

//     Binary_expr_checker checker(exp1, exp2, Op_type::add);
//     checker.check();
// }