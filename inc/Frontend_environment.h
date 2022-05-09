#pragma once

#include "Sym_environment.h"
#include "TAC.h"
#include <cstdio>
#include <cstdarg>

extern int yylineno;
extern int yycolno;

class Frontend_util
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

    static void report_error(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        fprintf(stderr, "error at line: %d, column: %d\n", yylineno, yycolno);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
        exit(0);
    }
};