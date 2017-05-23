
%{
#include "heading.h"
#include "utility.h"
#include "symbol.h"
#include "abstract_syntax.h"
#include "error_message.h"
#include "prabsyn.h"
A_exp abstract_syntax_root;

int yyerror(char *s);
int yylex(void);

%}

%union {
	int pos;
	int ival;
	double dval;
	string sval;
	A_var var;
	A_exp exp;
	A_dec dec;
	A_ty ty;
	A_decList decList;
	A_expList expList;
	A_field field;
	A_fieldList fieldList;
	A_fundec fundec;
	A_fundecList fundecList;
	A_namety namety;
	A_nametyList nametyList;
	A_efield efield;
	A_efieldList efieldList;
	/* et cetera */
}

%type <exp> program primary_expression expression translation_unit postfix_expression assignment_expression unary_expression init_declarator direct_declarator declarator initializer

%type <expList> init_declarator_list

%type <decList> declaration

%type <ty> declaration_specifiers type_specifier


%token <sval> ID
%token <dval> CONSTANT
%token <sval> STRING_LITERAL
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


%start program

%%

program:
	| declaration {std::cout << "\nparsing okay! weaweaw" << std::endl;abstract_syntax_root=A_DecListExp(EM_tokPos,$1);
	pr_exp(stdout,$$,0);
	}
	| assignment_expression { abstract_syntax_root=$1; std::cout<< "assign exp" <<std::endl;}
	| translation_unit {std::cout << "\nparsing okay!" << std::endl; abstract_syntax_root=$1;}
	;

primary_expression
	: ID { $$=A_VarExp(EM_tokPos,A_SimpleVar(EM_tokPos,S_Symbol($1))); }
	| CONSTANT { $$=A_DoubleExp(EM_tokPos,yylval.dval);}
	| STRING_LITERAL { $$=A_StringExp(EM_tokPos,$1); }
	| LPAREN expression RPAREN { $$=$2; }
	;

postfix_expression
	: primary_expression {$$=$1;}
	| postfix_expression LBRACK expression RBRACK
	| postfix_expression LPAREN RPAREN
	| postfix_expression LPAREN argument_expression_list RPAREN
	| postfix_expression DOT ID
	| postfix_expression PTR_OP ID
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	| LPAREN type_name RPAREN LBRACE initializer_list RBRACE
	| LPAREN type_name RPAREN LBRACE initializer_list COMMA RBRACE
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list COMMA assignment_expression
	;

unary_expression
	: postfix_expression { $$=$1;}
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF LPAREN type_name RPAREN
	;

unary_operator
	: AMPERSAND
	| ASTERISK
	| PLUS
	| MINUS
	| TILDE
	| EXCLAMATION
	;

cast_expression
	: unary_expression
	| LPAREN type_name RPAREN cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression ASTERISK cast_expression
	| multiplicative_expression DIVIDE cast_expression
	| multiplicative_expression MOD cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression PLUS multiplicative_expression
	| additive_expression MINUS multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NEQ_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression AMPERSAND equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression POW and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression VERTICAL_BAR exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression QUESTION expression COLON conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	{
	switch($1->kind){
		case A_simpleVar:
			$$=A_AssignExp(EM_tokPos,$1->u.var,$3);
			break;
		default:
			printf("error");
		}
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
	| expression COMMA assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers SEMICOLON
	| declaration_specifiers init_declarator_list SEMICOLON
		{
			$$=NULL;
			for(;$2!=NULL;$2=$2->tail)
			$$=( A_VarDec(EM_tokPos,$2->head->u.assign.var->u.simple,$1->u.name,$2->head->u.assign.exp),$$);
		}
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier { $$=A_NameTy( EM_tokPos, S_symbol($1));}
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	| function_specifier
	| function_specifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	{
		$$=NULL;$$=A_ExpList($1,$$);
		pr_expList(stdout,$$,15);
	}
	| init_declarator_list COMMA init_declarator
	{
		$$=A_ExpList($3,$1);
		pr_expList(stdout,$$,4);
	}
	;

init_declarator
	: declarator {}
	| declarator ASSIGN initializer
	{
		$$=A_AssignExp(EM_tokPos,$1->u.var,$3);
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
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| BOOL
	| COMPLEX
	| IMAGINARY
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
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
	| direct_declarator { $$=$1;}
	;

direct_declarator
	: ID
		{
			$$ = A_VarExp(EM_tokPos,A_SimpleVar(EM_tokPos,S_Symbol(yylval.sval)));
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
	| direct_declarator LPAREN identifier_list RPAREN
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
	: parameter_list
	| parameter_list COMMA ELLIPSIS
	;

parameter_list
	: parameter_declaration
	| parameter_list COMMA parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
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
	| expression_statement
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
	;

block_item_list
	: block_item
	| block_item_list block_item
	;

block_item
	: declaration
	| statement
	;

expression_statement
	: SEMICOLON
	| expression SEMICOLON
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
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

%%

#include <stdio.h>


extern int column;

int yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}

int yyerror(std::string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c

  std::cerr << "ERROR: " << s << " at symbol \"" << yytext;
  std::cerr << "\" on line " << yylineno << std::endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(std::string(s));
}
