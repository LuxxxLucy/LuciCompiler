#include <stdio.h>
#include "utility.h"
#include "error_message.h"
#include "symbol.h"
#include "abstract_syntax.h"
#include "tokens.h"



YYSTYPE yylval;

int yylex(void); /* prototype for the lexing function */

string toknames[] = {
  "ID",
  "CONSTANT",
  "STRING_LITERAL",
  "SIZEOF",
  "PTR_OP",
  "INC_OP",
  "DEC_OP",
  "LEFT_OP",
  "RIGHT_OP",
  "LE_OP",
  "LT_OP",
  "GE_OP",
  "GT_OP",
  "EQ_OP",
  "NEQ_OP",
  "ASSIGN",
  "AND_OP",
  "OR_OP",
  "MUL_ASSIGN",
  "DIV_ASSIGN",
  "MOD_ASSIGN",
  "ADD_ASSIGN",
  "SUB_ASSIGN",
  "LEFT_ASSIGN",
  "RIGHT_ASSIGN",
  "AND_ASSIGN",
  "XOR_ASSIGN",
  "OR_ASSIGN",
  "TYPE_NAME",
  "TYPEDEF",
  "EXTERN",
  "STATIC",
  "AUTO",
  "REGISTER",
  "INLINE",
  "RESTRICT",
  "CHAR",
  "SHORT",
  "INT",
  "LONG",
  "SIGNED",
  "UNSIGNED",
  "FLOAT",
  "DOUBLE",
  "CONST",
  "VOLATILE",
  "VOID",
  "BOOL",
  "COMPLEX",
  "IMAGINARY",
  "STRUCT",
  "UNION",
  "ENUM",
  "ELLIPSIS",
  "CASE",
  "DEFAULT",
  "IF",
  "ELSE",
  "SWITCH",
  "WHILE",
  "DO",
  "FOR",
  "GOTO",
  "CONTINUE",
  "BREAK",
  "RETURN",
  "LBRACK",
  "RBRACK",
  "LBRACE",
  "RBRACE",
  "LPAREN",
  "RPAREN",
  "COMMA",
  "SEMICOLON",
  "COLON",
  "PLUS",
  "TIMES",
  "MINUS",
  "DIVIDE",
  "EXCLAMATION",
  "QUESTION",
  "VERTICAL_BAR",
  "TILDE",
  "MOD",
  "POW",
  "AMPERSAND",
  "ASTERISK",
  "DOT"
};


string tokname(int tok) {
  return tok<258 || tok>345 ? String("BAD_TOKEN") : toknames[tok-258];
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
            case ID: case STRING_LITERAL:
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
