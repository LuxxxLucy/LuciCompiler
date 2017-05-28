%{
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "ppast.h"
#include "errmsg.h"
#include "symbol.h"
#include "utils.h"

int yylex(void);
void yyerror(char *msg);
%}

%union {
    int pos;
    int num;
    double dval;
    string_t str;
    list_t list;
    symbol_t sym;
    ast_decl_t dec;
    ast_expr_t exp;
    ast_type_t ty;
    ast_var_t var;
    ast_func_t fun;
    ast_binop_t op;
}

%{
static void print_token_value(FILE *fp, int type, YYSTYPE value);
#define YYPRINT(fp, type, value) print_token_value(fp, type, value)

#define LIST_ACTION(target, prev, elem) \
    do \
    { \
        list_t p, e = list((elem), NULL); \
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
        ast_var_t p, var = (elem); \
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

static ast_expr_t _program;
%}

%type <exp> _program

%type <exp> block_item translation_unit statement expression_statement

%type <exp>  direct_declarator declarator initializer
%type <dec> init_declarator


%type <exp> primary_expression expression postfix_expression assignment_expression unary_expression additive_expression multiplicative_expression cast_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression conditional_expression compound_statement jump_statement

%type <list>  init_declarator_list block_item_list

%type <list> declaration declaration_list

%type <list> parameter_type_list parameter_list

%type <fun> function_definition

%type <sym> type_specifier declaration_specifiers

//%type <op> unary_operator



%token <str> ID
%token <dval> CONSTANT
%token <str> STRING_LITERAL
%token SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP LT_OP GE_OP GT_OP EQ_OP NEQ_OP ASSIGN
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token BOOL COMPLEX IMAGINARY
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN
%token LBRACK RBRACK LBRACE RBRACE LPAREN RPAREN
%token COMMA SEMICOLON COLON
%token PLUS TIMES MINUS DIVIDE
%token EXCLAMATION QUESTION VERTICAL_BAR TILDE MOD POW AMPERSAND ASTERISK DOT
%token THEN TO IN NIL


%start _program

%%

_program:
	block_item_list
	{
		fprintf(stdout,"\n*************************\nparsing okay! a block item_list\n*************************\n");


        _program=ast_seq_expr(em_tok_pos,$1);
		fprintf(stdout,"\n*************************\nparsing okay! a block item_list\n*************************\n");
	}
	;

primary_expression
	: ID
	{
        fprintf(stdout,"exp: a id %s\n",$1);
        pp_var(stdout,20,$$);
        $$ = ast_var_expr(em_tok_pos, ast_simple_var(em_tok_pos, $1));
	}
	| CONSTANT
	{
        fprintf(stdout,"exp: a constant %f\n",$1);
		$$=ast_num_expr(em_tok_pos,$1);
	}
	| STRING_LITERAL
	{
	}
	| LPAREN expression RPAREN { $$=$2; }
	;

postfix_expression
	: primary_expression { $$=$1;}
	| postfix_expression LBRACK expression RBRACK
	{
	}
	| postfix_expression LPAREN RPAREN
	| postfix_expression LPAREN argument_expression_list RPAREN
	| postfix_expression DOT ID
	{
	}
	| postfix_expression PTR_OP ID
	{
	}
	| postfix_expression INC_OP
    {

    }
	| postfix_expression DEC_OP
	| LPAREN type_name RPAREN LBRACE initializer_list RBRACE
	| LPAREN type_name RPAREN LBRACE initializer_list COMMA RBRACE
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list COMMA assignment_expression
	;

unary_expression
	: postfix_expression
	{
		$$=$1;
	}
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF LPAREN type_name RPAREN
	;

unary_operator
	: AMPERSAND {}
	| ASTERISK {}
	| PLUS {}
	| MINUS {}
	| TILDE
	| EXCLAMATION
	;

cast_expression
	: unary_expression { $$=$1; }
	| LPAREN type_name RPAREN cast_expression { fprintf(stdout,"cast(not done yet)"); }
	;

multiplicative_expression
	: cast_expression { $$=$1; }
	| multiplicative_expression ASTERISK cast_expression
	{
	}
	| multiplicative_expression DIVIDE cast_expression
	{
	}
	| multiplicative_expression MOD cast_expression
	{
	}
	;

additive_expression
	: multiplicative_expression { $$=$1; }
	| additive_expression PLUS multiplicative_expression
	{
	}
	| additive_expression MINUS multiplicative_expression
	{
	}
	;

shift_expression
	: additive_expression { $$=$1; }
	| shift_expression LEFT_OP additive_expression
	{
	}
	| shift_expression RIGHT_OP additive_expression
	{
	}
	;

relational_expression
	: shift_expression { $$=$1; }
	| relational_expression LT_OP shift_expression
	{
	}
	| relational_expression GT_OP shift_expression
	{
	}
	| relational_expression LE_OP shift_expression
	{
	}
	| relational_expression GE_OP shift_expression
	{
	}
	;

equality_expression
	: relational_expression { $$=$1; }
	| equality_expression EQ_OP relational_expression
	{
	}
	| equality_expression NEQ_OP relational_expression
	{
	}
	;

and_expression
	: equality_expression { $$=$1; }
	| and_expression AMPERSAND equality_expression
	{
	}
	;

exclusive_or_expression
	: and_expression { $$=$1; }
	| exclusive_or_expression POW and_expression
	{
	}
	;

inclusive_or_expression
	: exclusive_or_expression { $$=$1; }
	| inclusive_or_expression VERTICAL_BAR exclusive_or_expression
	{
	}
	;

logical_and_expression
	: inclusive_or_expression { $$=$1; }
	| logical_and_expression AND_OP inclusive_or_expression
	{
	}
	;

logical_or_expression
	: logical_and_expression { $$=$1; }
	| logical_or_expression OR_OP logical_and_expression
	{
	}
	;

conditional_expression
	: logical_or_expression { $$=$1; }
	| logical_or_expression QUESTION expression COLON conditional_expression
	{
	}
	;

assignment_expression
	: conditional_expression { $$=$1; }
	| unary_expression assignment_operator assignment_expression
	{
	}
	;

assignment_operator
	: ASSIGN
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	{
		$$=$1;
	}
	| expression COMMA assignment_expression
	{
	}
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers SEMICOLON
    {
        //$$ = ast_var_decl(em_tok_pos, $1->id, $1->ty, NULL);
        print("null declaratior");
    }
	| declaration_specifiers init_declarator_list SEMICOLON
	{
        // dec_specifier is a symbol
        // init dec list is a list of dec(type symbol of the dec is not determined yet )

        //pp_decl(stdout,20, (ast_decl_t) $2->data);

        print("declaratior with initial\n");

        list_t p=$2;
        ast_decl_t q;
        for(;p;p=p->next)
        {
            q=(ast_decl_t) p->data;
            q->u.var.type=$1;
        }
        $$=$2;
	}
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	{
        fprintf(stdout,"a type specifier:%s\n",sym_name($1));
        $$=$1;
	}
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	| function_specifier
	| function_specifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	{
		LIST_ACTION($$,NULL,$1);
	}
	| init_declarator_list COMMA init_declarator
	{
        print("another declarator\n");
		LIST_ACTION($$,$1,$3);
	}
	;

init_declarator
	: declarator
	{
        print("A pure declarator\n");
        $$ = ast_var_decl(em_tok_pos, $1, NULL, NULL);
        pp_decl(stdout,20,$$);
	}
	| declarator ASSIGN initializer
	{
        $$ = ast_var_decl(em_tok_pos, $1->u.var->u.simple, NULL, $3);
	}
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	{
	 	$$=symbol("VOID");
		//fprintf(stdout, "Type name(%s) not done yet", S_name($$));
	}
	| CHAR
	{
		$$=symbol("CHAR");
		//fprintf(stdout, "Type name(%s) not done yet", S_name($$));
	}
	| SHORT
	{
	}
	| INT
	{
		$$=symbol("INT");
	}
	| LONG
	{
	}
	| FLOAT
	{
	}
	| DOUBLE
	{
	}
	| SIGNED
	{
	}
	| UNSIGNED
	{
	}
	| BOOL
	{
	}
	| COMPLEX
	{
	}
	| IMAGINARY
	{
	}
	| struct_or_union_specifier
	{
	}
	| enum_specifier
	{
	}
	| TYPE_NAME
	{
	}
	;

struct_or_union_specifier
	: struct_or_union ID LBRACE struct_declaration_list RBRACE
	| struct_or_union LBRACE struct_declaration_list RBRACE
	| struct_or_union ID
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list COMMA struct_declarator
	;

struct_declarator
	: declarator
	| COLON constant_expression
	| declarator COLON constant_expression
	;

enum_specifier
	: ENUM LBRACE enumerator_list RBRACE
	| ENUM ID LBRACE enumerator_list RBRACE
	| ENUM LBRACE enumerator_list COMMA RBRACE
	| ENUM ID LBRACE enumerator_list COMMA RBRACE
	| ENUM ID
	;

enumerator_list
	: enumerator
	| enumerator_list COMMA enumerator
	;

enumerator
	: ID
	| ID ASSIGN constant_expression
	;

type_qualifier
	: CONST
	| RESTRICT
	| VOLATILE
	;

function_specifier
	: INLINE
	;

declarator
	: pointer direct_declarator
	| direct_declarator
		{
			$$=$1;
		}
	;

direct_declarator
	: ID
	{
        fprintf(stdout,"exp: a id %s\n",$1);
        $$ = ast_var_expr(em_tok_pos, ast_simple_var(em_tok_pos, symbol($1)));
	}
	| LPAREN declarator RPAREN
	| direct_declarator LBRACK type_qualifier_list assignment_expression RBRACK
	| direct_declarator LBRACK type_qualifier_list RBRACK
	| direct_declarator LBRACK assignment_expression RBRACK
	| direct_declarator LBRACK STATIC type_qualifier_list assignment_expression RBRACK
	| direct_declarator LBRACK type_qualifier_list STATIC assignment_expression RBRACK
	| direct_declarator LBRACK type_qualifier_list ASTERISK RBRACK
	| direct_declarator LBRACK ASTERISK RBRACK
	| direct_declarator LBRACK RBRACK
	| direct_declarator LPAREN parameter_type_list RPAREN
	{
	}
	| direct_declarator LPAREN identifier_list RPAREN
	{
	}
	| direct_declarator LPAREN RPAREN
	;

pointer
	: ASTERISK
	| ASTERISK type_qualifier_list
	| ASTERISK pointer
	| ASTERISK type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_type_list
	: parameter_list { $$=$1; }
	| parameter_list COMMA ELLIPSIS
	;

parameter_list
	: parameter_declaration
	{
	}
	| parameter_list COMMA parameter_declaration
	{
	}
	;

parameter_declaration
	: declaration_specifiers declarator
	{
	}
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: ID
	| identifier_list COMMA ID
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: LPAREN abstract_declarator RPAREN
	| LBRACK RBRACK
	| LBRACK assignment_expression RBRACK
	| direct_abstract_declarator LBRACK RBRACK
	| direct_abstract_declarator LBRACK assignment_expression RBRACK
	| LBRACK ASTERISK RBRACK
	| direct_abstract_declarator LBRACK ASTERISK RBRACK
	| LPAREN RPAREN
	| LPAREN parameter_type_list RPAREN
	| direct_abstract_declarator LPAREN RPAREN
	| direct_abstract_declarator LPAREN parameter_type_list RPAREN
	;

initializer
	: assignment_expression { $$=$1; }
	| LBRACE initializer_list RBRACE
	| LBRACE initializer_list COMMA RBRACE
	;

initializer_list
	: initializer
	| designation initializer
	| initializer_list COMMA initializer
	| initializer_list COMMA designation initializer
	;

designation
	: designator_list ASSIGN
	;

designator_list
	: designator
	| designator_list designator
	;

designator
	: LBRACK constant_expression RBRACK
	| DOT ID
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement { $$=$1;}
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: ID COLON statement
	| CASE constant_expression COLON statement
	| DEFAULT COLON statement
	;

compound_statement
	: LBRACE RBRACE
	| LBRACE block_item_list RBRACE
	{
        $$=ast_seq_expr(em_tok_pos,$2);
	}
	;

block_item_list
	: block_item
	{
		LIST_ACTION($$,NULL,$1);
	}
	| block_item_list block_item
	{
		LIST_ACTION($$,$1,$2);
	}
	;

block_item
	: declaration
	{
		print("\n*************************\na declaration\n");


	}
	| function_definition
	{
		print("\n*************************\na function definition\n");
	}
	| statement
	{
		$$=$1;
	}
	;

expression_statement
	: SEMICOLON
	| expression SEMICOLON
	{
		$$=$1;
	}
	;

selection_statement
	: IF LPAREN expression RPAREN statement
	| IF LPAREN expression RPAREN statement ELSE statement
	| SWITCH LPAREN expression RPAREN statement
	;

iteration_statement
	: WHILE LPAREN expression RPAREN statement
	| DO statement WHILE LPAREN expression RPAREN SEMICOLON
	| FOR LPAREN expression_statement expression_statement RPAREN statement
	| FOR LPAREN expression_statement expression_statement expression RPAREN statement
	| FOR LPAREN declaration expression_statement RPAREN statement
	| FOR LPAREN declaration expression_statement expression RPAREN statement
	;

jump_statement
	: GOTO ID SEMICOLON
	| CONTINUE SEMICOLON
	| BREAK SEMICOLON
	| RETURN SEMICOLON
	| RETURN expression SEMICOLON
	{
		$$=$2;
	}
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	{
	}
	;

declaration_list
	: declaration
    {
        $$=$1;
    }
	| declaration_list declaration
    {
        list_t p = $2;
        ast_decl_t q;
        for(;p;p=p->next)
        {
            q= (ast_decl_t) p->data;
            LIST_ACTION($1,$1,q);
        }
    }
	;

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
        case STRING_LITERAL:
            fprintf(fp, "%s", value.str);
            break;
        case CONSTANT:
            fprintf(fp, "%d", value.num);
            break;
    }
}

ast_expr_t parse(string_t filename)
{
    em_reset(filename);
    if (yyparse() == 0)
        return _program;
    else
        return NULL;
}
