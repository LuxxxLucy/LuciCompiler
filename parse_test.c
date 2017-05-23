/*
 *  this program is used to test the paring result
 *  usage. shell command " parse_test.out filename "
 */

#include <stdio.h>
#include "utility.h"
#include "error_message.h"
#include "symbol.h"
#include "abstract_syntax.h"
#include "prabsyn.h"

// extern int yyparse(void);
int yyparse(void);
extern A_exp abstract_syntax_root;

A_exp parse(string fname)
{
    EM_reset(fname);
    if (yyparse() == 0)
    {
        /* parsing worked */
        fprintf(stderr,"Parsing successful!\n");
        /* return the root of abstrac syntax tree */
        return abstract_syntax_root;
    }
    else
        fprintf(stderr,"Parsing failed\n");
}


int main(int argc, char **argv) {

    if (argc!=2)
    {
        fprintf(stderr,"usage: parse_test filename\n");
        exit(1);
    }

    A_exp result_tree=parse(argv[1]);
    pr_exp(stdout,abstract_syntax_root,1);
    return 0;
}
