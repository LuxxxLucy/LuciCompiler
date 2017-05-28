D  [0-9]
L   [a-zA-Z_]
H   [a-fA-F0-9]
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%{

#define YY_NO_UNISTD_H

#include <ctype.h>
#include <string.h>
//#include <iostream>

#include "ast.h"
#include "errmsg.h"
#include "symbol.h"
#include "parser.h"
#include "utils.h"


//typedef union  { int pos; int ival; double dval; string_t sval; } YYSTYPE_CUSTOM;
//#define YYSTYPE YYSTYPE_CUSTOM
//#define YY_SKIP_YYWRAP

static int _char_pos = 1;

int yywrap(void);

#define ADJ \
do \
{ \
    em_tok_pos = yylval.pos = _char_pos; \
    _char_pos += yyleng; \
} \
while (0)

static int _comment_level = 0;

#define INIT_LEN 32
static string_t _str_buf;
static int _str_len;
static int _str_cap;
static void init_buf(void);
static void append_char(char ch);

int charPos=1;

int yywrap(void)
{
    charPos=1;
    return 1;
}

void adjust(void)
{
    em_tok_pos=charPos;
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
	em_error(charPos,"unterminated comment");
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
	//std::string s=std::string(yytext);
    yylval.str = (char*) checked_malloc( sizeof(char)*20);
    strcpy (yylval.str, yytext);
	return ID;
}


%}

%option nounput
%option never-interactive

%x COMMENT STRING

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
0[xX]{H}+{IS}?		{ count();yylval.dval=atof(yytext); return(CONSTANT); }
0[0-7]*{IS}?		{ count();yylval.dval=atof(yytext); return(CONSTANT); }
[1-9]{D}*{IS}?		{ count(); yylval.dval=atof(yytext);return(CONSTANT); }
L?'(\\.|[^\\'\n])+'	{ count();yylval.dval=atof(yytext); return(CONSTANT); }
{D}+{E}{FS}?		{ count();yylval.dval=atof(yytext); return(CONSTANT); }
{D}*"."{D}+{E}?{FS}?	{ count(); return(CONSTANT); }
{D}+"."{D}*{E}?{FS}?	{ count(); return(CONSTANT); }
0[xX]{H}+{P}{FS}?	{ count();yylval.dval=atof(yytext); return(CONSTANT); }
0[xX]{H}*"."{H}+{P}?{FS}?     { count();yylval.dval=atof(yytext); return(CONSTANT); }
0[xX]{H}+"."{H}*{P}?{FS}?     { count();yylval.dval=atof(yytext); return(CONSTANT); }
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
.			{ /* Add code to complain about unmatched characters */ em_error(em_tok_pos,"unmatched string!"); }

%%


static void init_buf(void)
{
    _str_buf = checked_malloc(INIT_LEN);
    _str_buf[0] = 0;
    _str_len = 0;
    _str_cap = INIT_LEN;
}

static void append_char(char ch)
{
    if (++_str_len == _str_cap)
    {
        char *p;

        _str_cap *= 2;
        p = checked_malloc(_str_cap);
        memcpy(p, _str_buf, _str_len);
        free(_str_buf);
        _str_buf = p;
    }
    _str_buf[_str_len - 1] = ch;
    _str_buf[_str_len] = 0;
}
