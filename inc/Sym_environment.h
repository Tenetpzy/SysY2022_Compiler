#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

class Symbol;

class Sym_environment
{
public:
    virtual void push_env() = 0;
    virtual void pop_env() = 0;

    // 查找名字为name的符号。不存在时返回指向空的指针
    virtual std::shared_ptr<Symbol> get_symbol(const std::string &name) const = 0;
    virtual void add_symbol(const std::string &name, const std::shared_ptr<Symbol> sym) = 0;
};

class Sym_trie_node;
class Sym_environment_trie;

class trie_node_next
{
    std::shared_ptr<Sym_trie_node> nxt;
    uint8_t persistent_flag;

public:
    trie_node_next()
    {
        persistent_flag = 1;
    }
    trie_node_next(const std::shared_ptr<Sym_trie_node> ptr)
    {
        nxt = ptr;
        persistent_flag = 1;
    }
    ~trie_node_next() = default;

    trie_node_next(const trie_node_next &n)
    {
        nxt = n.nxt;
        persistent_flag = 0;
    }

    trie_node_next &operator=(const trie_node_next &n) = delete;

    friend class Sym_trie_node;
    friend class Sym_environment_trie;
};

class Sym_trie_node
{
    std::shared_ptr<Symbol> sym;
    std::unordered_map<char, trie_node_next> next_map;

    friend class Sym_environment_trie;
};

class Sym_environment_trie : public Sym_environment
{
public:
    Sym_environment_trie();
    ~Sym_environment_trie() = default;

    void push_env() override;
    void pop_env() override;
    std::shared_ptr<Symbol> get_symbol(const std::string &name) const override;
    void add_symbol(const std::string &name, const std::shared_ptr<Symbol> sym) override;

private:
    std::vector<std::unique_ptr<Sym_trie_node>> env_list; // 环境列表
};