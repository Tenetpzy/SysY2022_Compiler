#include "parser.hh"
#include <cstdio>

int main(int argc, char **argv)
{
    if (argc == 2)
        freopen(argv[1], "r", stdin);
    yy::parser parse;
    return parse();
}