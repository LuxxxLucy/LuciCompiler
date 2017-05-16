#include <stdio.h>
#include "utility.h"
#include "error_message.h"
#include "tokens.h"

YYSTYPE yylval;

int yylex(void); /* prototype for the lexing function */

string toknames[] = {
"ID",
"STRING",
"INT",
"COMMA",
"COLON",
"SEMICOLON",
"LPAREN",
"RPAREN",
"BRACK",
"RBRACK",
"LBRACE",
"RBRACE",
"DOT",
"PLUS",
"MINUS",
"TIMES",
"DIVIDE",
"EQ_OP",
"NEQ_OP",
"LT_OP",
"LE_OP",
"GT_OP",
"GE_OP",
"AND",
"OR",
"ASSIGN",
"ARRAY",
"IF",
"THEN",
"ELSE",
"WHILE",
"FOR",
"TO",
"DO",
"LET",
"IN",
"END",
"OF",
"BREAK",
"NIL",
"FUNCTION",
"VAR",
"TYPE",
"CASE",
"CHAR",
"CONST",
"CONTINUE",
"DEFAULT",
"DOUBLE",
"FLOAT",
"GOTO",
"LONG",
"RETURN",
"SIZEOF",
"STATIC",
"STRUCT",
"SWITCH",
"CONSTANT",
"VOID",
"TYPEDEF",
"ADD_ASSIGN",
"SUB_ASSIGN",
"MUL_ASSIGN",
"DIV_ASSIGN",
"MOD_ASSIGN",
"AND_ASSIGN",
"XOR_ASSIGN",
"OR_ASSIGN",
"RIGHT_OP",
"LEFT_OP",
"INC_OP",
"DEC_OP",
"PTR_OP",
"AND_OP",
"OR_OP"
};


string tokname(tok) {
  return tok<257 || tok>331 ? "BAD_TOKEN" : toknames[tok-257];
}

int main(int argc, char **argv) {
    string fname; int tok;
    if (argc!=2) {
        fprintf(stderr,"usage: a.out filename\n");
        exit(1);
    }
    fname=argv[1];
    EM_reset(fname);
    for(;;) {
        tok=yylex();
        if (tok==0) break;
        switch(tok)
        {
            case ID: case STRING:
                printf("%10s %4d %s\n",tokname(tok),EM_tokPos,yylval.sval);
                break;
            case CONSTANT:
                printf("%10s %4d %d\n",tokname(tok),EM_tokPos,yylval.ival);
                break;
            default:
                printf("%10s %4d\n",tokname(tok),EM_tokPos);
        }
    }
    return 0;
}
