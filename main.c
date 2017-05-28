#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "errmsg.h"
#include "escape.h"
#include "parser-wrap.h"
#include "ppast.h"
#include "semantic.h"
#include "utils.h"

int main(int argc, char **argv)
{
    ast_expr_t prog;

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
