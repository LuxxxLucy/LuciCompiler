D  [0-9]
L   [a-zA-Z_]
H   [a-fA-F0-9]
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%{
#include <stdio.h>
#include <string.h>
#include "utility.h"


#include "symbol.h"
#include "abstract_syntax.h"
#include "error_message.h"

typedef union  {
	int pos;
	int ival;
	double dval;
	string sval;
	A_var var;
	A_exp exp;
} YYSTYPE_CUSTOM;

#define YYSTYPE YYSTYPE_CUSTOM
#define YY_SKIP_YYWRAP

#include "tokens.h"


int charPos=1;

int yywrap(void)
{
    charPos=1;
    return 1;
}

void adjust(void)
{
    EM_tokPos=charPos;
    charPos+=yyleng;
}

void comment(void)
{
	char c, prev = 0;
	while ((c = getchar()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	EM_error(charPos,"unterminated comment");
}

int column = 0;

void count(void)
{
	int i;
	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;
	// ECHO;
    adjust();
    return;
}

// TODO:this should be done to check type in lexical analysis part

int check_type(void)
{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return TYPE_NAME;
*
*	return IDENTIFIER;
*/
/*
*	it actually will only return IDENTIFIER
*/
    yylval.sval=yytext;
	return ID;
}

%}

%%

"/*"			{ comment(); }
"//"[^\n]*      { /* consume //-comment */ }
"break"			{ count(); return(BREAK); }
"case"			{ count(); return(CASE); }
"char"			{ count(); return(CHAR); }
"const"			{ count(); return(CONST); }
"continue"		{ count(); return(CONTINUE); }
"default"		{ count(); return(DEFAULT); }
"do"			{ count(); return(DO); }
"double"		{ count(); return(DOUBLE); }
"else"			{ count(); return(ELSE); }
"float"			{ count(); return(FLOAT); }
"for"			{ count(); return(FOR); }
"goto"			{ count(); return(GOTO); }
"if"			{ count(); return(IF); }
"int"			{ count(); return(INT); }
"long"			{ count(); return(LONG); }
"return"		{ count(); return(RETURN); }
"sizeof"		{ count(); return(SIZEOF); }
"static"		{ count(); return(STATIC); }
"struct"		{ count(); return(STRUCT); }
"switch"		{ count(); return(SWITCH); }
"typedef"		{ count(); return(TYPEDEF); }
"void"			{ count(); return(VOID); }
"while"			{ count(); return(WHILE); }

{L}({L}|{D})*		{ count(); return(check_type()); }
0[xX]{H}+{IS}?		{ count(); return(CONSTANT); }
0[0-7]*{IS}?		{ count(); return(CONSTANT); }
[1-9]{D}*{IS}?		{ count(); yylval.ival=atoi(yytext);return(CONSTANT); }
L?'(\\.|[^\\'\n])+'	{ count(); return(CONSTANT); }
{D}+{E}{FS}?		{ count(); return(CONSTANT); }
{D}*"."{D}+{E}?{FS}?	{ count(); return(CONSTANT); }
{D}+"."{D}*{E}?{FS}?	{ count(); return(CONSTANT); }
0[xX]{H}+{P}{FS}?	{ count(); return(CONSTANT); }
0[xX]{H}*"."{H}+{P}?{FS}?     { count(); return(CONSTANT); }
0[xX]{H}+"."{H}*{P}?{FS}?     { count(); return(CONSTANT); }
L?\"(\\.|[^\\"\n])*\"	{ count(); return(STRING_LITERAL); }

"+="			{ count(); return(ADD_ASSIGN); }
"-="			{ count(); return(SUB_ASSIGN); }
"*="			{ count(); return(MUL_ASSIGN); }
"/="			{ count(); return(DIV_ASSIGN); }
"%="			{ count(); return(MOD_ASSIGN); }
"&="			{ count(); return(AND_ASSIGN); }
"^="			{ count(); return(XOR_ASSIGN); }
"|="			{ count(); return(OR_ASSIGN); }
">>"			{ count(); return(RIGHT_OP); }
"<<"			{ count(); return(LEFT_OP); }
"++"			{ count(); return(INC_OP); }
"--"			{ count(); return(DEC_OP); }
"->"			{ count(); return(PTR_OP); }
"&&"			{ count(); return(AND_OP); }
"||"			{ count(); return(OR_OP); }
"<="			{ count(); return(LE_OP); }
">="			{ count(); return(GE_OP); }
"=="			{ count(); return(EQ_OP); }
"!="			{ count(); return(NEQ_OP); }
";"			{ count(); return(SEMICOLON); }
("{"|"<%")		{ count(); return(LBRACE); }
("}"|"%>")		{ count(); return(RBRACE); }
","			{ count(); return(COMMA); }
":"			{ count(); return(COLON); }
"<-"			{ count(); return(ASSIGN); }
":="			{ count(); return(ASSIGN); }
"="			{ count(); return(ASSIGN); }
"("			{ count(); return(LPAREN); }
")"			{ count(); return(RPAREN); }
("["|"<:")		{ count(); return(LBRACK); }
("]"|":>")		{ count(); return(RBRACK); }
"."			{ count(); return(DOT); }
"&"			{ count(); return(AMPERSAND); }
"!"			{ count(); return(EXCLAMATION); }
"~"			{ count(); return(TILDE); }
"-"			{ count(); return(MINUS); }
"+"			{ count(); return(PLUS); }
"*"			{ count(); return(ASTERISK); }
"/"			{ count(); return(DIVIDE); }
"%"			{ count(); return(MOD); }
"<"			{ count(); return(LT_OP); }
">"			{ count(); return(GT_OP); }
"^"			{ count(); return(POW); }
"|"			{ count(); return(VERTICAL_BAR); }
"?"			{ count(); return(QUESTION); }
[\n]		{ count();yylineno++; }
[ \t\v\f]		{ count();}
.			{ /* Add code to complain about unmatched characters */ EM_error(EM_tokPos,"unmatched string!"); }
%%
