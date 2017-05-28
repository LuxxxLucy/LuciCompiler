#include <stdio.h>
#include <stdlib.h>

#include "abstract_syntax.h"
#include "error_message.h"
#include "escape.h"
#include "parser-wrap.h"
#include "ppAST.h"
#include "semantic.h"
#include "utils.h"

int main(int argc, char **argv)
{
    AST_expr_t prog;

    print("parsing the code...\n");

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    /* yydebug = 1; */
    prog = parse(argv[1]);
    print("parsing okay!");
    if (em_any_errors)
    {
        print("error happend\n");
    }
    print("now start printing the abstract tree\n");
    pp_expr(stdout,0,prog);
    print("abstract syntax tree okay\n");

    print("finding escape,please wait\n");
    esc_find_escape(prog);
    print("finding escape okay\n");
    // pp_expr(stdout, 0, prog);
    print("translating\n");
    sem_trans_prog(prog);
    print("translated!\n");

    return 0;
}
