#include <assert.h>

typedef char *string;
typedef char Bool;

#define TRUE 1
#define FALSE 0

typedef union  {
	int pos;
	int ival;
	string sval;
} YYSTYPE_CUSTOM;

#define YYSTYPE YYSTYPE_CUSTOM
#define YY_SKIP_YYWRAP

// this is used to malloc memory
void *checked_malloc(int);

// a wrapper interface for string literal
string String(char *);

typedef struct U_boolList_ *U_boolList;
struct U_boolList_ {Bool head; U_boolList tail;};
U_boolList U_BoolList(Bool head, U_boolList tail);
