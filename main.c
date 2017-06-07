#include <stdio.h>
#include <stdlib.h>

#include "abstract_syntax.h"
#include "error_message.h"
#include "escape.h"
#include "parser-wrap.h"
#include "ppAST.h"
#include "frame.h"
#include "tree.h"
#include "types.h"
#include "translate.h"
#include "semantic.h"
#include "abstract_machine.h"
#include "utils.h"

int main(int argc, char **argv)
{
    // initial a abstract syntax tree
    AST_expr_ptr  prog;
    expr_type_ptr IR_tree_result;

    print("now parsing the code...\n");

    if (argc != 2)
    {
        fprintf(stderr, "Usage Error: %s filename\n", argv[0]);
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
    IR_tree_result=sem_trans_prog(prog);
    print("translated okay!\n");

    print("FRAGMENTS:");
    fr_pp_frags(stdout);
    fprintf(stdout, "MAIN PROGRAM:\n");
    print("MAIN PROGRAM:\n");
    tr_pp_expr(IR_tree_result.expr);

    print("now making abstract machine code\n");
    make_stmts("./abstract_machine_code.c",IR_tree_result.expr);


    return 0;
}
