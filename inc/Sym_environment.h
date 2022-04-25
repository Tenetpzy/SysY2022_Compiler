#pragma once

#include <vector>
#include <string>
#include <memory>

class Symbol;

class Sym_environment
{
public:
    virtual void push_env() = 0;
    virtual void pop_env() = 0;
    virtual std::shared_ptr<Symbol> get_symbol(const std::string& name) const = 0;
    virtual void add_symbol(const std::string& name, const std::shared_ptr<Symbol>& sym) = 0;
};


class Sym_trie_node;
class Sym_environment_trie : public Sym_environment
{
public:
    Sym_environment_trie();
    ~Sym_environment_trie() = default;

    void push_env() override;
    void pop_env() override;
    std::shared_ptr<Symbol> get_symbol(const std::string& name) const override;
    void add_symbol(const std::string& name, const std::shared_ptr<Symbol>& sym) override;

private:
    std::vector<std::unique_ptr<Sym_trie_node>> env_list;  // 环境列表
};