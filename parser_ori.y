%{
#include <stdio.h>
#include <stdlib.h>

#include "abstract_syntax.h"
#include "error_message.h"
#include "symbol.h"
#include "utils.h"

int yylex(void);
void yyerror(char *msg);
%}

%union {
    int pos;
    int num;
    string_ptr  str;
    list_ptr  list;
    symbol_ptr  sym;
    AST_decl_ptr  decl;
    AST_expr_ptr  expr;
    AST_type_ptr  type;
    AST_var_ptr  var;
    AST_func_ptr  func;
}

%{
static void print_token_value(FILE *fp, int type, YYSTYPE value);
#define YYPRINT(fp, type, value) print_token_value(fp, type, value)

#define LIST_ACTION(target, prev, elem) \
    do \
    { \
        list_ptr  p, e = list((elem), NULL); \
        (target) = p = (prev); \
        if (p) \
        { \
            while (p->next) \
                p = p->next; \
            p->next = e; \
        } \
        else \
            (target) = e; \
    } \
    while (false)
#define LVALUE_ACTION(target, prev, elem) \
    do \
    { \
        AST_var_ptr  p, var = (elem); \
        (target) = p = (prev); \
        if (p) \
        { \
            while (p->u.field.var) \
                p = p->u.field.var; \
            p->u.field.var = var; \
        } \
        else \
            (target) = var; \
    } \
    while (false)

static AST_expr_ptr  _program;
%}

%debug

%token <str> ID STRING
%token <num> INT

%token <pos>
    COMMA COLON LPARAN RPARAN LBRACK RBRACK
    LBRACE RBRACE DOT
    ARRAY IF THEN ELSE WHILE FOR TO LET IN
    END OF BREAK NIL
    FUNCTION VAR TYPE

%left <pos> SEMICOLON
%nonassoc <pos> DO
%nonassoc <pos> ASSIGN
%left <pos> OR_OP
%left <pos> AND_OP
%nonassoc <pos> EQ_OP NEQ_OP LT_OP LE_OP GT_OP GE_OP
%left <pos> PLUS MINUS
%left <pos> TIMES DIVIDE
%left <pos> UMINUS

%type <decl> decl var_decl
%type <expr> program expr
%type <type> type
%type <var> lvalue lvalue_
%type <list> expr_seq arg_seq efield_seq decls funcs_decl types_decl fields
%type <list> field_seq
%type <func> func_decl
%type <sym> id

%start program

%%

program:
    expr
    { _program = $1; }

expr:
    lvalue
    { $$ = AST_var_expr($1->pos, $1); }
|   NIL
    { $$ = AST_nil_expr($1); }
|   expr expr_seq
    { $$ = AST_seq_expr($1->pos, list($1, $2)); }
|   LPAREN RPAREN
    { $$ = AST_seq_expr($1, NULL); }
|   LPAREN expr RPAREN
    { $$ = $2; }
|   INT
    { $$ = AST_num_expr(em_tok_pos, $1); }
|   STRING
    { $$ = AST_string_expr(em_tok_pos, $1); }
|   MINUS expr %prec UMINUS
    { $$ = AST_op_expr($1, AST_num_expr($1, 0), AST_MINUS, $2); }
|   id LPARAN RPARAN
    { $$ = AST_call_expr($2, $1, NULL); }
|   id LPARAN expr arg_seq RPARAN
    { $$ = AST_call_expr($2, $1, list($3, $4)); }
|   expr PLUS expr
    { $$ = AST_op_expr($2, $1, AST_PLUS, $3); }
|   expr MINUS expr
    { $$ = AST_op_expr($2, $1, AST_MINUS, $3); }
|   expr TIMES expr
    { $$ = AST_op_expr($2, $1, AST_TIMES, $3); }
|   expr DIVIDE expr
    { $$ = AST_op_expr($2, $1, AST_DIVIDE, $3); }
|   expr EQ_OP expr
    { $$ = AST_op_expr($2, $1, AST_EQ, $3); }
|   expr NEQ_OP expr
    { $$ = AST_op_expr($2, $1, AST_NEQ, $3); }
|   expr LT_OP expr
    { $$ = AST_op_expr($2, $1, AST_LT, $3); }
|   expr LE_OP expr
    { $$ = AST_op_expr($2, $1, AST_LE, $3); }
|   expr GT_OP expr
    { $$ = AST_op_expr($2, $1, AST_GT, $3); }
|   expr GE_OP expr
    { $$ = AST_op_expr($2, $1, AST_GE, $3); }
|   expr AND_OP expr
    { $$ = AST_if_expr($2, $1, $3, AST_num_expr($2, 0)); }
|   expr OR_OP expr
    { $$ = AST_if_expr($2, $1, AST_num_expr($2, 1), $3); }
|   id LBRACE RBRACE
    { $$ = AST_record_expr($2, $1, NULL); }
|   id LBRACE id EQ_OP expr efield_seq RBRACE
    { $$ = AST_record_expr($2, $1, list(AST_efield($4, $3, $5), $6)); }
|   id LBRACK expr RBRACK OF expr
    { $$ = AST_array_expr($2, $1, $3, $6); }
|   lvalue ASSIGN expr
    { $$ = AST_assign_expr($2, $1, $3); }
|   IF expr THEN expr
    { $$ = AST_if_expr($1, $2, $4, NULL); }
|   IF expr THEN expr ELSE expr
    { $$ = AST_if_expr($1, $2, $4, $6); }
|   WHILE expr DO expr
    { $$ = AST_while_expr($1, $2, $4); }
|   FOR id ASSIGN expr TO expr DO expr
    { $$ = AST_for_expr($1, $2, $4, $6, $8); }
|   BREAK
    { $$ = AST_break_expr($1); }
|   LET decls IN expr END
    { $$ = AST_let_expr($1, $2, $4); }

decls:
    /* empty */
    { $$ = NULL; }
|   decls decl
    { LIST_ACTION($$, $1, $2); }

decl:
    types_decl
    { $$ = AST_types_decl(((AST_type_ptr) $1->data)->pos, $1); }
|   var_decl
|   funcs_decl
    { $$ = AST_funcs_decl(((AST_func_ptr) $1->data)->pos, $1); }

types_decl:
    TYPE id EQ_OP type
    { $$ = list(AST_nametype($2, $4), NULL); }
|   types_decl TYPE id EQ_OP type
    { LIST_ACTION($$, $1, AST_nametype($3, $5)); }

type:
    id
    { $$ = AST_name_type(em_tok_pos, $1); }
|   LBRACE fields RBRACE
    { $$ = AST_record_type($1, $2); }
|   ARRAY OF id
    { $$ = AST_array_type($1, $3); }

fields:
    /* empty */
    { $$ = NULL; }
|   id COLON id field_seq
    { $$ = list(AST_field($1, $3), $4); }

var_decl:
    VAR id ASSIGN expr
    { $$ = AST_var_decl($1, $2, NULL, $4); }
|   VAR id COLON id ASSIGN expr
    { $$ = AST_var_decl($1, $2, $4, $6); }

funcs_decl:
    func_decl
    { $$ = list($1, NULL); }
|   funcs_decl func_decl
    { LIST_ACTION($$, $1, $2); }

func_decl:
    FUNCTION id LPARAN fields RPARAN EQ_OP expr
    { $$ = AST_func($1, $2, $4, NULL, $7); }
|   FUNCTION id LPARAN fields RPARAN COLON id EQ_OP expr
    { $$ = AST_func($1, $2, $4, $7, $9); }

expr_seq:
    SEMICOLON expr
    { $$ = list($2, NULL); }
|   expr_seq SEMICOLON expr
    { LIST_ACTION($$, $1, $3); }

arg_seq:
    /* empty */
    { $$ = NULL; }
|   arg_seq COMMA expr
    { LIST_ACTION($$, $1, $3); }

efield_seq:
    /* empty */
    { $$ = NULL; }
|   efield_seq COMMA id EQ_OP expr
    { LIST_ACTION($$, $1, AST_efield($4, $3, $5)); }

field_seq:
    /* empty */
    { $$ = NULL; }
|   field_seq COMMA id COLON id
    { LIST_ACTION($$, $1, AST_field($3, $5)); }

lvalue:
    id lvalue_
    { LVALUE_ACTION($$, $2, AST_simple_var(em_tok_pos, $1)); }

lvalue_:
    /* empty */
    { $$ = NULL; }
|   DOT id lvalue_
    { LVALUE_ACTION($$, $3, AST_field_var($1, NULL, $2)); }
|   LBRACK expr RBRACK lvalue_
    { LVALUE_ACTION($$, $4, AST_sub_var($1, NULL, $2)); }

id:
    ID
    { $$ = symbol($1); }

%%

void yyerror(char *msg)
{
    em_error(em_tok_pos, "%s", msg);
}

static void print_token_value(FILE *fp, int type, YYSTYPE value)
{
    switch (type)
    {
        case ID:
        case STRING:
            fprintf(fp, "%s", value.str);
            break;
        case INT:
            fprintf(fp, "%d", value.num);
            break;
    }
}

AST_expr_ptr  parse(string_ptr  filename)
{
    em_reset(filename);
    if (yyparse() == 0)
        return _program;
    else
        return NULL;
}
