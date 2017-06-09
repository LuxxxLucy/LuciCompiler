%{
#include <stdio.h>
#include <stdlib.h>

#include "abstract_syntax.h"
#include "ppAST.h"
#include "error_message.h"
#include "symbol.h"
#include "utils.h"

int yylex(void);
void yyerror(char *msg);
%}

%union {
    int pos;
    int num;
    double dval;
    string_ptr  str;
    list_ptr  list;
    symbol_ptr  sym;
    AST_decl_ptr  dec;
    AST_expr_ptr  exp;
    AST_type_ptr  ty;
    AST_var_ptr  var;
    AST_func_ptr  fun;
    AST_binop_ptr  op;
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

%type <exp> program

%type <exp> dec_block_item block_item translation_unit statement expression_statement

%type <exp>  direct_declarator declarator initializer
%type <dec> init_declarator


%type <exp> primary_expression expression postfix_expression assignment_expression unary_expression additive_expression multiplicative_expression cast_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression conditional_expression compound_statement jump_statement selection_statement iteration_statement


%type <list>  init_declarator_list dec_block_item_list block_item_list

%type <list> declaration declaration_list

%type <list> parameter_type_list parameter_list argument_expression_list

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


%start program

%%

program:
	| dec_block_item_list block_item_list
    {
        print("all statements\n");
        _program=AST_let_expr(em_tok_pos,$1,AST_seq_expr(em_tok_pos,$2) );
    }
	;

primary_expression
	: ID
	{
        fprintf(stdout,"exp: a id %s\n",$1);
        $$ = AST_var_expr(em_tok_pos, AST_simple_var(em_tok_pos, symbol($1) ));
        pp_expr(stdout,0,$$);
	}
	| CONSTANT
	{
        fprintf(stdout,"exp: a constant value %f\n",$1);
		$$=AST_num_expr(em_tok_pos,$1);
        pp_expr(stdout,0,$$);
	}
	| STRING_LITERAL
	{
        print("find a string\n");
        print($1);
        $$=AST_string_expr(em_tok_pos,$1);
	}
	| LPAREN expression RPAREN
    {
        $$=$2;
    }
	;

postfix_expression
	: primary_expression { $$=$1;}
	| postfix_expression LBRACK expression RBRACK
	{
        //$$=AST_sub_var(em_tok_pos, $1->u.var, $3r);
	}
	| postfix_expression LPAREN RPAREN
    {
        $$ = AST_call_expr(em_tok_pos, $1->u.var->u.simple, NULL);
    }
	| postfix_expression LPAREN argument_expression_list RPAREN
    {
        $$ = AST_call_expr(em_tok_pos, $1->u.var->u.simple, $3);
    }
	| postfix_expression DOT ID
	| postfix_expression PTR_OP ID
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	| LPAREN type_name RPAREN LBRACE initializer_list RBRACE
	| LPAREN type_name RPAREN LBRACE initializer_list COMMA RBRACE
	;

argument_expression_list
	: assignment_expression
	{
		LIST_ACTION($$,NULL,$1);
	}
	| argument_expression_list COMMA assignment_expression
	{
		LIST_ACTION($$,$1,$3);
	}
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
	| TILDE {}
	| EXCLAMATION {}
	;

cast_expression
	: unary_expression { $$=$1; }
	| LPAREN type_name RPAREN cast_expression
    { fprintf(stdout,"cast(not done yet)"); }
	;

multiplicative_expression
	: cast_expression { $$=$1; }
	| multiplicative_expression ASTERISK cast_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_TIMES, $3);
	}
	| multiplicative_expression DIVIDE cast_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_DIVIDE, $3);
	}
	| multiplicative_expression MOD cast_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_MOD, $3);
	}
	;

additive_expression
	: multiplicative_expression { $$=$1; }
	| additive_expression PLUS multiplicative_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_PLUS, $3);
	}
	| additive_expression MINUS multiplicative_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_MINUS, $3);
	}
	;

shift_expression
	: additive_expression { $$=$1; }
	| shift_expression LEFT_OP additive_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_LSHIFT, $3);
	}
	| shift_expression RIGHT_OP additive_expression
    {
        $$ = AST_op_expr(em_tok_pos, $1, AST_RSHIFT, $3);
    }
	;

relational_expression
	: shift_expression { $$=$1; }
	| relational_expression LT_OP shift_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_LT, $3);
	}
	| relational_expression GT_OP shift_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_GT, $3);
	}
	| relational_expression LE_OP shift_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_LE, $3);
	}
	| relational_expression GE_OP shift_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_GE, $3);
	}
	;

equality_expression
	: relational_expression { $$=$1; }
	| equality_expression EQ_OP relational_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_EQ, $3);
	}
	| equality_expression NEQ_OP relational_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_NEQ, $3);
	}
	;

and_expression
	: equality_expression { $$=$1; }
	| and_expression AMPERSAND equality_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_AND, $3);
	}
	;

exclusive_or_expression
	: and_expression { $$=$1; }
	| exclusive_or_expression POW and_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_XOR, $3);
	}
	;

inclusive_or_expression
	: exclusive_or_expression { $$=$1; }
	| inclusive_or_expression VERTICAL_BAR exclusive_or_expression
	{
        $$ = AST_op_expr(em_tok_pos, $1, AST_OR, $3);
	}
	;

logical_and_expression
	: inclusive_or_expression { $$=$1; }
	| logical_and_expression AND_OP inclusive_or_expression
	{
        $$ = AST_if_expr(em_tok_pos, $1, $3, AST_num_expr(em_tok_pos, 0));
	}
	;

logical_or_expression
	: logical_and_expression { $$=$1; }
	| logical_or_expression OR_OP logical_and_expression
	{
        $$ = AST_if_expr(em_tok_pos, $1,  AST_num_expr(em_tok_pos, 1),$3);
	}
	;

conditional_expression
	: logical_or_expression { $$=$1; }
	| logical_or_expression QUESTION expression COLON conditional_expression
	{
        //TODO:? operator
        $$ = AST_if_expr(em_tok_pos, $1, $3, $5);
	}
	;

assignment_expression
	: conditional_expression { $$=$1; }
	| unary_expression assignment_operator assignment_expression
	{
        $$=AST_assign_expr(em_tok_pos,$1->u.var,$3);
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
        $$ = AST_seq_expr(em_tok_pos, list($3, $1->u.seq));
	}
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers SEMICOLON
    {
        //$$ = AST_var_decl(em_tok_pos, $1->id, $1->ty, NULL);
        print("null declaratior");
    }
	| declaration_specifiers init_declarator_list SEMICOLON
	{
        // dec_specifier is a symbol
        // init dec list is a list of dec(type symbol of the dec is not determined yet )
        print("declaratior with initial\n");

        list_ptr  p=$2;
        AST_decl_ptr  q;
        for(;p;p=p->next)
        {
            q=(AST_decl_ptr) p->data;
            q->u.var.type=$1;
            //pp_decl(stdout,20, q);
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
        pp_decl(stdout,20, $1);
	}
	| init_declarator_list COMMA init_declarator
	{
        pp_decl(stdout,20,  $3);
        print("another declarator\n");
		LIST_ACTION($$,$1,$3);
	}
	;

init_declarator
	: declarator
	{
        print("A pure declarator\n");
        $$ = AST_var_decl(em_tok_pos, $1->u.var->u.simple, NULL, NULL);
	}
	| declarator ASSIGN initializer
	{
        $$ = AST_var_decl(em_tok_pos, $1->u.var->u.simple, NULL, $3);
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
        $$ = AST_var_expr(em_tok_pos, AST_simple_var(em_tok_pos, symbol($1)));
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
        //$$ = AST_func(em_tok_pos, $1->u.var->u.simple, $4, NULL, $7);
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
	| dtreeect_abstract_declarator
	| pointer dtreeect_abstract_declarator
	;

dtreeect_abstract_declarator
	: LPAREN abstract_declarator RPAREN
	| LBRACK RBRACK
	| LBRACK assignment_expression RBRACK
	| dtreeect_abstract_declarator LBRACK RBRACK
	| dtreeect_abstract_declarator LBRACK assignment_expression RBRACK
	| LBRACK ASTERISK RBRACK
	| dtreeect_abstract_declarator LBRACK ASTERISK RBRACK
	| LPAREN RPAREN
	| LPAREN parameter_type_list RPAREN
	| dtreeect_abstract_declarator LPAREN RPAREN
	| dtreeect_abstract_declarator LPAREN parameter_type_list RPAREN
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
	| expression_statement { $$=$1;  pp_expr(stdout,0,$$);}
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
	| LBRACE dec_block_item_list RBRACE
	{
        $$=AST_seq_expr(em_tok_pos,$2);
	}
	| LBRACE block_item_list RBRACE
	{
        $$=AST_seq_expr(em_tok_pos,$2);
        print("a expression")
	}
	;

dec_block_item_list
	: dec_block_item
	{
		LIST_ACTION($$,NULL,$1);
	}
	| dec_block_item_list dec_block_item
	{
		LIST_ACTION($$,$1,$2);
	}
	;

dec_block_item
	: declaration
	{
        pp_decl(stdout,20,$1->data);
        $$=$1->data;
        //$$=AST_seq_expr(em_tok_pos,$1);
        //$$=$1->data;
	}
	| function_definition
	{
		print("\n*************************\na function definition\n");
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

block_item:
    statement {$$=$1;}
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
    {
        $$ = AST_if_expr(em_tok_pos, $3, $5, NULL);
    }
	| IF LPAREN expression RPAREN statement ELSE statement
    {
        $$ = AST_if_expr(em_tok_pos, $3, $5, $7);
    }
	| SWITCH LPAREN expression RPAREN statement
	;

iteration_statement
	: WHILE LPAREN expression RPAREN statement
    {
        $$ = AST_while_expr(em_tok_pos, $3, $5);
    }
	| DO statement WHILE LPAREN expression RPAREN SEMICOLON
    {
        $$ = AST_while_expr(em_tok_pos, $5, $2);
    }
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
        list_ptr  p = $2;
        AST_decl_ptr  q;
        for(;p;p=p->next)
        {
            q= (AST_decl_ptr) p->data;
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

AST_expr_ptr  parse(string_ptr  filename)
{
    em_reset(filename);
    if (yyparse() == 0)
    {
        print("no parsing error\n");
        return _program;
    }
    else
    {
        print("parsing error\n");
        return NULL;
    }
}
