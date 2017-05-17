/*
 *  this program is used to test the paring result
 *  usage. shell command " parse_test.out filename "
 */

#include <stdio.h>
#include "utility.h"
#include "error_message.h"

// extern int yyparse(void);
int yyparse(void);

void parse(string fname)
{
    EM_reset(fname);
    if (yyparse() == 0)
        /* parsing worked */
        fprintf(stderr,"Parsing successful!\n");
    else
        fprintf(stderr,"Parsing failed\n");
}


int main(int argc, char **argv) {

    if (argc!=2)
    {
        fprintf(stderr,"usage: parse_test.out filename\n");
        exit(1);
    }

    parse(argv[1]);
    return 0;
}
