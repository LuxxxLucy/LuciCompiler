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
    if (em_any_errors)
    {
        print("error happend\n");
    }
    pp_expr(stdout,20,prog);
    print("abstract syntax tree okay\n");

    esc_find_escape(prog);
    // pp_expr(stdout, 0, prog);
    sem_trans_prog(prog);

    return 0;
}
