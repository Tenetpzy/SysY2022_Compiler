#include "parser.hh"
#include "Frontend_util.h"
#include "TAC.h"
#include <cstdio>

int main(int argc, char **argv)
{
    if (argc == 2)
        freopen(argv[1], "r", stdin);
    yy::parser parse;
    parse();

    auto &ls = Frontend_env::get_glob_var_decl_list();
    for (auto &tac : ls)
    {
        tac->print();
        printf("\n");
    }

    return 0;
}