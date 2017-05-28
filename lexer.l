%{

#define YY_NO_UNISTD_H

#include <ctype.h>
#include <string.h>

#include "ast.h"
#include "errmsg.h"
#include "symbol.h"
#include "parser.h"
#include "utils.h"

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

%}

%option nounput
%option never-interactive

%x COMMENT STRING

%%

[ \t\f\v\r]             { ADJ; }
\n                      { ADJ; em_newline(); }

"/*"                    { ADJ; _comment_level = 1; BEGIN(COMMENT); }
<COMMENT>[^*/\n]*       { ADJ; }
<COMMENT>"*"+[^*/\n]*   { ADJ; }
<COMMENT>"/"+[^*/\n]*   { ADJ; }
<COMMENT>\n             { ADJ; em_newline(); }
<COMMENT>"/"+"*"        { ADJ; _comment_level++; }
<COMMENT>"*"+"/"        {
    ADJ;
    _comment_level--;
    if (_comment_level <= 0)
        BEGIN(INITIAL);
}

","                     { ADJ; return COMMA; }
":"                     { ADJ; return COLON; }
";"                     { ADJ; return SEMICOLON; }
"("                     { ADJ; return LPAREN; }
")"                     { ADJ; return RPAREN; }
"["                     { ADJ; return LBRACK; }
"]"                     { ADJ; return RBRACK; }
"{"                     { ADJ; return LBRACE; }
"}"                     { ADJ; return RBRACE; }
"."                     { ADJ; return DOT; }
"+"                     { ADJ; return PLUS; }
"-"                     { ADJ; return MINUS; }
"*"                     { ADJ; return TIMES; }
"/"                     { ADJ; return DIVIDE; }
"=="                     { ADJ; return EQ_OP; }
"!="                    { ADJ; return NEQ_OP; }
"<"                     { ADJ; return LT_OP; }
"<="                    { ADJ; return LE_OP; }
">"                     { ADJ; return GT_OP; }
">="                    { ADJ; return GE_OP; }
"&&"                     { ADJ; return AND_OP; }
"||"                     { ADJ; return OR_OP; }
":="                    { ADJ; return ASSIGN; }

if                      { ADJ; return IF; }
then                    { ADJ; return THEN; }
else                    { ADJ; return ELSE; }
while                   { ADJ; return WHILE; }
for                     { ADJ; return FOR; }
to                      { ADJ; return TO; }
do                      { ADJ; return DO; }
in                      { ADJ; return IN; }
break                   { ADJ; return BREAK; }
NULL                     { ADJ; return NIL; }

[0-9]+                  { ADJ; yylval.num = atoi(yytext); return INT; }
[_a-zA-Z][_a-zA-Z0-9]*  { ADJ; yylval.str = string(yytext); return ID; }

\"                      { ADJ; init_buf(); BEGIN(STRING); }
<STRING>\"              {
    ADJ;
    BEGIN(INITIAL);
    yylval.str = _str_buf;
    return STRING;
}
<STRING>\n              { ADJ; em_newline(); }
<STRING>\\[0-9]{3}      {
    int result;

    ADJ;
    sscanf(yytext + 1, "%d", &result);
    if (result > 0xFF)
        em_error(em_tok_pos, "character out of range");
    append_char(result);
}
<STRING>\\n             { ADJ; append_char('\n'); }
<STRING>\\t             { ADJ; append_char('\t'); }
<STRING>\\\"            { ADJ; append_char('\"'); }
<STRING>\\\\            { ADJ; append_char('\\'); }
<STRING>\\(.|\n)        { ADJ; append_char(yytext[1]); }
<STRING>[^\\\n\"]+      {
    char *p = yytext;

    ADJ;
    while (*p)
        append_char(*p++);
}

.                       { ADJ; em_error(em_tok_pos, "illegal token"); }

%%

int yywrap(void)
{
    _char_pos = 1;
    return 1;
}

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
