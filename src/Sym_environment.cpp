#include "Sym_environment.h"
#include <string>
#include <bitset>

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
    if (env_list.size() > 1) // 禁止删除全局的符号环境
        env_list.pop_back();
}

std::shared_ptr<Symbol> Sym_environment_trie::get_symbol(const std::string &name) const
{
    Sym_trie_node *node = env_list.back().get(); // 不规范，但单线程下安全
    size_t len = name.length();
    size_t name_index = 0;

    for (; name_index < len; ++name_index)
    {
        auto it = node->next_map.find(name[name_index]);
        if (it == node->next_map.end())
            break;
        node = it->second.nxt.get();
    }

    if (name_index == len)
        return node->sym;
    else
        return std::shared_ptr<Symbol>();
}

void Sym_environment_trie::add_symbol(const std::string &name, const std::shared_ptr<Symbol> symbol)
{
    Sym_trie_node *node = env_list.back().get();

    for (auto ch : name)
    {
        auto it = node->next_map.find(ch);
        if (it == node->next_map.end()) // 不存在前缀，插入新结点保存前缀
            it = node->next_map.insert(std::make_pair(ch, trie_node_next(std::make_shared<Sym_trie_node>()))).first;
        else
        {
            auto &nxt_node = it->second;
            if (nxt_node.persistent_flag == 0) // 指向老版本，拷贝一份并让其指向拷贝版本
            {
                nxt_node.nxt = std::make_shared<Sym_trie_node>(*(nxt_node.nxt));
                nxt_node.persistent_flag = 1;
            }
        }
        node = it->second.nxt.get();
    }

    node->sym = symbol;
}
