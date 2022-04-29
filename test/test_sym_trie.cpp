#include "gtest/gtest.h"
#include "Sym_environment.h"
#include <string>
#include <cstdio>

// Test already passed.
class Symbol
{
public:
    std::string name;
    int tag;

    Symbol(const std::string& n, int t = 0) : name(n), tag(t) {}
    ~Symbol()
    {
        printf("symbol name = %s, tag = %d destroyed.\n", name.c_str(), tag);
    }
};

class test_sym_trie : public ::testing::Test
{
protected:
    Sym_environment_trie sym_env;

    test_sym_trie() = default;
    ~test_sym_trie()
    {
        printf("test environment destroy is begining.\n");
    }
};

TEST_F(test_sym_trie, trie_test)
{
    using namespace std;
    shared_ptr<Symbol> sym[4];
    string name[4] = {"ab", "bc", "ca", "ab"};
    sym[0] = make_shared<Symbol>("ab", 0);
    sym[1] = make_shared<Symbol>("bc", 1);
    sym[2] = make_shared<Symbol>("ca", 2);
    sym[3] = make_shared<Symbol>("ab", 3);

    for (int i = 0; i < 3; ++i)
        sym_env.add_symbol(name[i], make_shared<Symbol>(*sym[i]));
    
    for (int i = 0; i < 3; ++i)
    {
        auto ptr = sym_env.get_symbol(name[i]);
        bool flag = false;
        if (ptr)  flag = true;
        ASSERT_EQ(true, flag) << "get_symbol failed!\n";
        EXPECT_EQ(true, ptr->name == sym[i]->name) << "get_symbol name incorrect!\n";
        EXPECT_EQ(true, ptr->tag == sym[i]->tag) << "get_symbol object incorrect!\n";
    }

    sym_env.push_env();
    sym_env.add_symbol(name[3], make_shared<Symbol>(*sym[3]));  // 增加局部作用域中的"ab"

    for (int i = 1; i < 4; ++i)
    {
        auto ptr = sym_env.get_symbol(name[i]);
        bool flag = false;
        if (ptr)  flag = true;
        ASSERT_EQ(true, flag) << "get_symbol failed!\n";
        EXPECT_EQ(true, ptr->name == sym[i]->name) << "get_symbol name incorrect after changing scope!\n";
        EXPECT_EQ(true, ptr->tag == sym[i]->tag) << "get_symbol object incorrect after changing scope!\n";
    }

    sym_env.pop_env();
    printf("pop_env complete.\n");

    for (int i = 0; i < 3; ++i)
    {
        auto ptr = sym_env.get_symbol(name[i]);
        bool flag = false;
        if (ptr)  flag = true;
        ASSERT_EQ(true, flag) << "get_symbol failed!\n";
        EXPECT_EQ(true, ptr->name == sym[i]->name) << "get_symbol name incorrect after restore scope!\n";
        EXPECT_EQ(true, ptr->tag == sym[i]->tag) << "get_symbol object incorrect after restore scope!\n";
    }
}
