#include "Sym_environment.h"
#include <string>
#include <bitset>

class Sym_trie_node
{
    std::shared_ptr<Symbol> sym;
    std::shared_ptr<Sym_trie_node> next[62];

    // 持久化标记，对应每一个next指针
    // 若为0，则在add时需要拷贝指向的对象
    std::bitset<62> persistent_flag;

public:
    Sym_trie_node()
    {
        persistent_flag.set();
    }

    ~Sym_trie_node() = default;

    Sym_trie_node(const Sym_trie_node& node)
    {
        sym = node.sym;
        for (int i = 0; i < 62; ++i)
            next[i] = node.next[i];
        persistent_flag.reset();
    }

    Sym_trie_node& operator=(const Sym_trie_node&) = delete;

    static size_t mapping(int ch) noexcept
    {
        if (isupper(ch))
            return ch - 'A';
        else if (islower(ch))
            return ch - 'a' + 26;
        else
            return ch + 52;
    }

    friend class Sym_environment_trie;
};

Sym_environment_trie::Sym_environment_trie()
{
    env_list.push_back(std::unique_ptr<Sym_trie_node>(new Sym_trie_node()));
}

void Sym_environment_trie::push_env()
{
    auto &lst = env_list.back();
    env_list.push_back(std::unique_ptr<Sym_trie_node>(new Sym_trie_node(*lst)));
}

void Sym_environment_trie::pop_env()
{
    if (env_list.size() > 1)  // 禁止删除全局的符号环境
        env_list.pop_back();
}

std::shared_ptr<Symbol> Sym_environment_trie::get_symbol(const std::string& name) const
{
    auto index = env_list.size() - 1;  // 保证index有效

    Sym_trie_node *node = env_list[index].get();
    size_t len = name.length();
    size_t name_index = 0;

    for (; name_index < len; ++name_index)
    {
        int idx = Sym_trie_node::mapping(name[name_index]);
        if (!node->next[idx])
            break;
        node = node->next[idx].get();
    }

    if (name_index == len)
        return node->sym;
    else
        return std::shared_ptr<Symbol>();
}

void Sym_environment_trie::add_symbol(const std::string& name, const std::shared_ptr<Symbol>& symbol)
{
    auto index = env_list.size() - 1;

    Sym_trie_node *node = env_list[index].get();
    for (auto ch : name)
    {
        int idx = Sym_trie_node::mapping(ch);
        if (!node->next[idx])
        {
            node->next[idx] = std::make_shared<Sym_trie_node>();
            node->persistent_flag[idx] = 1;
        }
        else if (!node->persistent_flag[idx])   // 指向了老版本，需指向拷贝后的新版本
        {
            std::shared_ptr<Sym_trie_node> tmp(new Sym_trie_node(*(node->next[idx])));
            node->next[idx] = tmp;
            node->persistent_flag[idx] = 1;
        }
        node = node->next[idx].get();
    }

    node->sym = symbol;
}

int main()
{
    Sym_environment_trie x;
    return 0;
}