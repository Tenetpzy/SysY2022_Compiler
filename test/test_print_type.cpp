#include "gtest/gtest.h"
#include "Type.h"

TEST(Type_name_print, all)
{
    using namespace std;

    vector<shared_ptr<Type>> list;

    shared_ptr<Int_type> T_int = make_shared<Int_type>();
    shared_ptr<Float_type> T_float = make_shared<Float_type>();
    shared_ptr<Void_type> T_void = make_shared<Void_type>();

    list.push_back(T_int);
    list.push_back(T_float);
    list.push_back(T_void);

    list.push_back(make_shared<Reference_type>(T_int));

    vector<int> dim1{6, 6, 6};
    vector<int> dim2{0, 6, 6};

    list.push_back(make_shared<Array_type>(T_int, dim1));
    list.push_back(make_shared<Array_type>(T_float, dim2));
    list.push_back(make_shared<Reference_type>(make_shared<Array_type>(T_float, dim2)));

    vector<shared_ptr<Type>> param_ls{T_int, T_float, T_void};
    list.push_back(make_shared<Function_type>(T_int, param_ls));

    for (auto &e : list)
        printf("%s\n", e->to_string().c_str());
}