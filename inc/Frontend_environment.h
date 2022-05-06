#pragma once

#include "Sym_environment.h"

class Frontend_env
{
private:
    static Sym_environment *sym_env;

private:
    static Sym_environment* generate_sym_env()
    {
        return new Sym_environment_trie();
    }

public:
    static Sym_environment& get_sym_env()
    {
        if (sym_env == nullptr)
            sym_env = generate_sym_env();
        return *sym_env;
    }
};