/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     CONSTANT = 259,
     STRING_LITERAL = 260,
     SIZEOF = 261,
     PTR_OP = 262,
     INC_OP = 263,
     DEC_OP = 264,
     LEFT_OP = 265,
     RIGHT_OP = 266,
     LE_OP = 267,
     LT_OP = 268,
     GE_OP = 269,
     GT_OP = 270,
     EQ_OP = 271,
     NEQ_OP = 272,
     ASSIGN = 273,
     AND_OP = 274,
     OR_OP = 275,
     MUL_ASSIGN = 276,
     DIV_ASSIGN = 277,
     MOD_ASSIGN = 278,
     ADD_ASSIGN = 279,
     SUB_ASSIGN = 280,
     LEFT_ASSIGN = 281,
     RIGHT_ASSIGN = 282,
     AND_ASSIGN = 283,
     XOR_ASSIGN = 284,
     OR_ASSIGN = 285,
     TYPE_NAME = 286,
     TYPEDEF = 287,
     EXTERN = 288,
     STATIC = 289,
     AUTO = 290,
     REGISTER = 291,
     INLINE = 292,
     RESTRICT = 293,
     CHAR = 294,
     SHORT = 295,
     INT = 296,
     LONG = 297,
     SIGNED = 298,
     UNSIGNED = 299,
     FLOAT = 300,
     DOUBLE = 301,
     CONST = 302,
     VOLATILE = 303,
     VOID = 304,
     BOOL = 305,
     COMPLEX = 306,
     IMAGINARY = 307,
     STRUCT = 308,
     UNION = 309,
     ENUM = 310,
     ELLIPSIS = 311,
     CASE = 312,
     DEFAULT = 313,
     IF = 314,
     ELSE = 315,
     SWITCH = 316,
     WHILE = 317,
     DO = 318,
     FOR = 319,
     GOTO = 320,
     CONTINUE = 321,
     BREAK = 322,
     RETURN = 323,
     LBRACK = 324,
     RBRACK = 325,
     LBRACE = 326,
     RBRACE = 327,
     LPAREN = 328,
     RPAREN = 329,
     COMMA = 330,
     SEMICOLON = 331,
     COLON = 332,
     PLUS = 333,
     TIMES = 334,
     MINUS = 335,
     DIVIDE = 336,
     EXCLAMATION = 337,
     QUESTION = 338,
     VERTICAL_BAR = 339,
     TILDE = 340,
     MOD = 341,
     POW = 342,
     AMPERSAND = 343,
     ASTERISK = 344,
     DOT = 345
   };
#endif
/* Tokens.  */
#define ID 258
#define CONSTANT 259
#define STRING_LITERAL 260
#define SIZEOF 261
#define PTR_OP 262
#define INC_OP 263
#define DEC_OP 264
#define LEFT_OP 265
#define RIGHT_OP 266
#define LE_OP 267
#define LT_OP 268
#define GE_OP 269
#define GT_OP 270
#define EQ_OP 271
#define NEQ_OP 272
#define ASSIGN 273
#define AND_OP 274
#define OR_OP 275
#define MUL_ASSIGN 276
#define DIV_ASSIGN 277
#define MOD_ASSIGN 278
#define ADD_ASSIGN 279
#define SUB_ASSIGN 280
#define LEFT_ASSIGN 281
#define RIGHT_ASSIGN 282
#define AND_ASSIGN 283
#define XOR_ASSIGN 284
#define OR_ASSIGN 285
#define TYPE_NAME 286
#define TYPEDEF 287
#define EXTERN 288
#define STATIC 289
#define AUTO 290
#define REGISTER 291
#define INLINE 292
#define RESTRICT 293
#define CHAR 294
#define SHORT 295
#define INT 296
#define LONG 297
#define SIGNED 298
#define UNSIGNED 299
#define FLOAT 300
#define DOUBLE 301
#define CONST 302
#define VOLATILE 303
#define VOID 304
#define BOOL 305
#define COMPLEX 306
#define IMAGINARY 307
#define STRUCT 308
#define UNION 309
#define ENUM 310
#define ELLIPSIS 311
#define CASE 312
#define DEFAULT 313
#define IF 314
#define ELSE 315
#define SWITCH 316
#define WHILE 317
#define DO 318
#define FOR 319
#define GOTO 320
#define CONTINUE 321
#define BREAK 322
#define RETURN 323
#define LBRACK 324
#define RBRACK 325
#define LBRACE 326
#define RBRACE 327
#define LPAREN 328
#define RPAREN 329
#define COMMA 330
#define SEMICOLON 331
#define COLON 332
#define PLUS 333
#define TIMES 334
#define MINUS 335
#define DIVIDE 336
#define EXCLAMATION 337
#define QUESTION 338
#define VERTICAL_BAR 339
#define TILDE 340
#define MOD 341
#define POW 342
#define AMPERSAND 343
#define ASTERISK 344
#define DOT 345




/* Copy the first part of user declarations.  */
#line 2 "grammar.y"

#include "heading.h"
#include "utility.h"
#include "symbol.h"
#include "abstract_syntax.h"
#include "error_message.h"
A_exp abstract_syntax_root;

int yyerror(char *s);
int yylex(void);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "grammar.y"
{
	int pos;
	int ival;
	double dval;
	string sval;
	A_var var;
	A_exp exp;
	/* et cetera */
}
/* Line 193 of yacc.c.  */
#line 299 "grammar.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 312 "grammar.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1521

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  240
/* YYNRULES -- Number of states.  */
#define YYNSTATES  401

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   345

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      91,     2,    92,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    10,    12,    16,    18,
      23,    27,    32,    36,    40,    43,    46,    53,    61,    63,
      67,    69,    72,    75,    78,    81,    86,    88,    90,    92,
      94,    96,    98,   100,   105,   107,   111,   115,   119,   121,
     125,   129,   131,   135,   139,   141,   145,   149,   153,   157,
     159,   163,   167,   169,   173,   175,   179,   181,   185,   187,
     191,   193,   197,   199,   205,   207,   211,   213,   215,   217,
     219,   221,   223,   225,   227,   229,   231,   233,   235,   239,
     241,   244,   248,   250,   253,   255,   258,   260,   263,   265,
     268,   270,   274,   276,   280,   282,   284,   286,   288,   290,
     292,   294,   296,   298,   300,   302,   304,   306,   308,   310,
     312,   314,   316,   318,   320,   326,   331,   334,   336,   338,
     340,   343,   347,   350,   352,   355,   357,   359,   363,   365,
     368,   372,   377,   383,   389,   396,   399,   401,   405,   407,
     411,   413,   415,   417,   419,   422,   424,   426,   430,   436,
     441,   446,   453,   460,   466,   471,   475,   480,   485,   489,
     491,   494,   497,   501,   503,   506,   508,   512,   514,   518,
     521,   524,   526,   528,   532,   534,   537,   539,   541,   544,
     548,   551,   555,   559,   564,   568,   573,   576,   580,   584,
     589,   591,   595,   600,   602,   605,   609,   614,   617,   619,
     622,   626,   629,   631,   633,   635,   637,   639,   641,   645,
     650,   654,   657,   661,   663,   666,   668,   670,   672,   675,
     681,   689,   695,   701,   709,   716,   724,   731,   739,   743,
     746,   749,   752,   756,   758,   761,   763,   765,   770,   774,
     776
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      94,     0,    -1,    -1,   159,    -1,     3,    -1,     4,    -1,
       5,    -1,    73,   114,    74,    -1,    95,    -1,    96,    69,
     114,    70,    -1,    96,    73,    74,    -1,    96,    73,    97,
      74,    -1,    96,    90,     3,    -1,    96,     7,     3,    -1,
      96,     8,    -1,    96,     9,    -1,    73,   142,    74,    71,
     146,    72,    -1,    73,   142,    74,    71,   146,    75,    72,
      -1,   112,    -1,    97,    75,   112,    -1,    96,    -1,     8,
      98,    -1,     9,    98,    -1,    99,   100,    -1,     6,    98,
      -1,     6,    73,   142,    74,    -1,    88,    -1,    89,    -1,
      78,    -1,    80,    -1,    85,    -1,    82,    -1,    98,    -1,
      73,   142,    74,   100,    -1,   100,    -1,   101,    89,   100,
      -1,   101,    81,   100,    -1,   101,    86,   100,    -1,   101,
      -1,   102,    78,   101,    -1,   102,    80,   101,    -1,   102,
      -1,   103,    10,   102,    -1,   103,    11,   102,    -1,   103,
      -1,   104,    91,   103,    -1,   104,    92,   103,    -1,   104,
      12,   103,    -1,   104,    14,   103,    -1,   104,    -1,   105,
      16,   104,    -1,   105,    17,   104,    -1,   105,    -1,   106,
      88,   105,    -1,   106,    -1,   107,    87,   106,    -1,   107,
      -1,   108,    84,   107,    -1,   108,    -1,   109,    19,   108,
      -1,   109,    -1,   110,    20,   109,    -1,   110,    -1,   110,
      83,   114,    77,   111,    -1,   111,    -1,    98,   113,   112,
      -1,    18,    -1,    21,    -1,    22,    -1,    23,    -1,    24,
      -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,    29,
      -1,    30,    -1,   112,    -1,   114,    75,   112,    -1,   111,
      -1,   117,    76,    -1,   117,   118,    76,    -1,   120,    -1,
     120,   117,    -1,   121,    -1,   121,   117,    -1,   132,    -1,
     132,   117,    -1,   133,    -1,   133,   117,    -1,   119,    -1,
     118,    75,   119,    -1,   134,    -1,   134,    18,   145,    -1,
      32,    -1,    33,    -1,    34,    -1,    35,    -1,    36,    -1,
      49,    -1,    39,    -1,    40,    -1,    41,    -1,    42,    -1,
      45,    -1,    46,    -1,    43,    -1,    44,    -1,    50,    -1,
      51,    -1,    52,    -1,   122,    -1,   129,    -1,    31,    -1,
     123,     3,    71,   124,    72,    -1,   123,    71,   124,    72,
      -1,   123,     3,    -1,    53,    -1,    54,    -1,   125,    -1,
     124,   125,    -1,   126,   127,    76,    -1,   121,   126,    -1,
     121,    -1,   132,   126,    -1,   132,    -1,   128,    -1,   127,
      75,   128,    -1,   134,    -1,    77,   115,    -1,   134,    77,
     115,    -1,    55,    71,   130,    72,    -1,    55,     3,    71,
     130,    72,    -1,    55,    71,   130,    75,    72,    -1,    55,
       3,    71,   130,    75,    72,    -1,    55,     3,    -1,   131,
      -1,   130,    75,   131,    -1,     3,    -1,     3,    18,   115,
      -1,    47,    -1,    38,    -1,    48,    -1,    37,    -1,   136,
     135,    -1,   135,    -1,     3,    -1,    73,   134,    74,    -1,
     135,    69,   137,   112,    70,    -1,   135,    69,   137,    70,
      -1,   135,    69,   112,    70,    -1,   135,    69,    34,   137,
     112,    70,    -1,   135,    69,   137,    34,   112,    70,    -1,
     135,    69,   137,    89,    70,    -1,   135,    69,    89,    70,
      -1,   135,    69,    70,    -1,   135,    73,   138,    74,    -1,
     135,    73,   141,    74,    -1,   135,    73,    74,    -1,    89,
      -1,    89,   137,    -1,    89,   136,    -1,    89,   137,   136,
      -1,   132,    -1,   137,   132,    -1,   139,    -1,   139,    75,
      56,    -1,   140,    -1,   139,    75,   140,    -1,   117,   134,
      -1,   117,   143,    -1,   117,    -1,     3,    -1,   141,    75,
       3,    -1,   126,    -1,   126,   143,    -1,   136,    -1,   144,
      -1,   136,   144,    -1,    73,   143,    74,    -1,    69,    70,
      -1,    69,   112,    70,    -1,   144,    69,    70,    -1,   144,
      69,   112,    70,    -1,    69,    89,    70,    -1,   144,    69,
      89,    70,    -1,    73,    74,    -1,    73,   138,    74,    -1,
     144,    73,    74,    -1,   144,    73,   138,    74,    -1,   112,
      -1,    71,   146,    72,    -1,    71,   146,    75,    72,    -1,
     145,    -1,   147,   145,    -1,   146,    75,   145,    -1,   146,
      75,   147,   145,    -1,   148,    18,    -1,   149,    -1,   148,
     149,    -1,    69,   115,    70,    -1,    90,     3,    -1,   151,
      -1,   152,    -1,   155,    -1,   156,    -1,   157,    -1,   158,
      -1,     3,    77,   150,    -1,    57,   115,    77,   150,    -1,
      58,    77,   150,    -1,    71,    72,    -1,    71,   153,    72,
      -1,   154,    -1,   153,   154,    -1,   116,    -1,   150,    -1,
      76,    -1,   114,    76,    -1,    59,    73,   114,    74,   150,
      -1,    59,    73,   114,    74,   150,    60,   150,    -1,    61,
      73,   114,    74,   150,    -1,    62,    73,   114,    74,   150,
      -1,    63,   150,    62,    73,   114,    74,    76,    -1,    64,
      73,   155,   155,    74,   150,    -1,    64,    73,   155,   155,
     114,    74,   150,    -1,    64,    73,   116,   155,    74,   150,
      -1,    64,    73,   116,   155,   114,    74,   150,    -1,    65,
       3,    76,    -1,    66,    76,    -1,    67,    76,    -1,    68,
      76,    -1,    68,   114,    76,    -1,   160,    -1,   159,   160,
      -1,   161,    -1,   116,    -1,   117,   134,   162,   152,    -1,
     117,   134,   152,    -1,   116,    -1,   162,   116,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    50,    50,    51,    55,    56,    57,    58,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    75,    76,
      80,    81,    82,    83,    84,    85,    89,    90,    91,    92,
      93,    94,    98,    99,   103,   104,   105,   106,   110,   111,
     112,   116,   117,   118,   122,   123,   124,   125,   126,   130,
     131,   132,   136,   137,   141,   142,   146,   147,   151,   152,
     156,   157,   161,   162,   166,   167,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   185,   186,   190,
     194,   195,   199,   200,   201,   202,   203,   204,   205,   206,
     210,   211,   215,   216,   220,   221,   222,   223,   224,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   246,   247,   248,   252,   253,   257,
     258,   262,   266,   267,   268,   269,   273,   274,   278,   279,
     280,   284,   285,   286,   287,   288,   292,   293,   297,   298,
     302,   303,   304,   308,   312,   313,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   333,
     334,   335,   336,   340,   341,   345,   346,   350,   351,   355,
     356,   357,   360,   361,   365,   366,   370,   371,   372,   376,
     377,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     390,   391,   392,   396,   397,   398,   399,   403,   407,   408,
     412,   413,   417,   418,   419,   420,   421,   422,   426,   427,
     428,   432,   433,   437,   438,   442,   443,   447,   448,   452,
     453,   454,   458,   459,   460,   461,   462,   463,   467,   468,
     469,   470,   471,   475,   476,   480,   481,   485,   486,   490,
     491
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CONSTANT", "STRING_LITERAL",
  "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP",
  "LT_OP", "GE_OP", "GT_OP", "EQ_OP", "NEQ_OP", "ASSIGN", "AND_OP",
  "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "TYPE_NAME", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "INLINE", "RESTRICT", "CHAR", "SHORT", "INT", "LONG",
  "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID",
  "BOOL", "COMPLEX", "IMAGINARY", "STRUCT", "UNION", "ENUM", "ELLIPSIS",
  "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO",
  "CONTINUE", "BREAK", "RETURN", "LBRACK", "RBRACK", "LBRACE", "RBRACE",
  "LPAREN", "RPAREN", "COMMA", "SEMICOLON", "COLON", "PLUS", "TIMES",
  "MINUS", "DIVIDE", "EXCLAMATION", "QUESTION", "VERTICAL_BAR", "TILDE",
  "MOD", "POW", "AMPERSAND", "ASTERISK", "DOT", "'<'", "'>'", "$accept",
  "program", "primary_expression", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "function_specifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "designation", "designator_list", "designator", "statement",
  "labeled_statement", "compound_statement", "block_item_list",
  "block_item", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "declaration_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,    60,    62
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    93,    94,    94,    95,    95,    95,    95,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    97,    97,
      98,    98,    98,    98,    98,    98,    99,    99,    99,    99,
      99,    99,   100,   100,   101,   101,   101,   101,   102,   102,
     102,   103,   103,   103,   104,   104,   104,   104,   104,   105,
     105,   105,   106,   106,   107,   107,   108,   108,   109,   109,
     110,   110,   111,   111,   112,   112,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   114,   114,   115,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   119,   119,   120,   120,   120,   120,   120,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   122,   122,   122,   123,   123,   124,
     124,   125,   126,   126,   126,   126,   127,   127,   128,   128,
     128,   129,   129,   129,   129,   129,   130,   130,   131,   131,
     132,   132,   132,   133,   134,   134,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   136,
     136,   136,   136,   137,   137,   138,   138,   139,   139,   140,
     140,   140,   141,   141,   142,   142,   143,   143,   143,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     145,   145,   145,   146,   146,   146,   146,   147,   148,   148,
     149,   149,   150,   150,   150,   150,   150,   150,   151,   151,
     151,   152,   152,   153,   153,   154,   154,   155,   155,   156,
     156,   156,   157,   157,   157,   157,   157,   157,   158,   158,
     158,   158,   158,   159,   159,   160,   160,   161,   161,   162,
     162
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     1,     1,     3,     1,     4,
       3,     4,     3,     3,     2,     2,     6,     7,     1,     3,
       1,     2,     2,     2,     2,     4,     1,     1,     1,     1,
       1,     1,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     3,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     4,     2,     1,     1,     1,
       2,     3,     2,     1,     2,     1,     1,     3,     1,     2,
       3,     4,     5,     5,     6,     2,     1,     3,     1,     3,
       1,     1,     1,     1,     2,     1,     1,     3,     5,     4,
       4,     6,     6,     5,     4,     3,     4,     4,     3,     1,
       2,     2,     3,     1,     2,     1,     3,     1,     3,     2,
       2,     1,     1,     3,     1,     2,     1,     1,     2,     3,
       2,     3,     3,     4,     3,     4,     2,     3,     3,     4,
       1,     3,     4,     1,     2,     3,     4,     2,     1,     2,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     4,
       3,     2,     3,     1,     2,     1,     1,     1,     2,     5,
       7,     5,     5,     7,     6,     7,     6,     7,     3,     2,
       2,     2,     3,     1,     2,     1,     1,     4,     3,     1,
       2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,   113,    94,    95,    96,    97,    98,   143,   141,   100,
     101,   102,   103,   106,   107,   104,   105,   140,   142,    99,
     108,   109,   110,   117,   118,     0,     0,   236,     0,    82,
      84,   111,     0,   112,    86,    88,     3,   233,   235,   135,
       0,     1,   146,     0,    80,   159,     0,    90,    92,   145,
       0,    83,    85,   116,     0,    87,    89,   234,     0,   138,
       0,   136,     0,   163,   161,   160,     0,    81,     0,     0,
     239,     0,   238,     0,     0,     0,   144,     0,   123,     0,
     119,     0,   125,     0,     0,   131,     0,   147,   164,   162,
      91,    92,     4,     5,     6,     0,     0,     0,     0,     0,
      28,    29,    31,    30,    26,    27,     8,    20,    32,     0,
      34,    38,    41,    44,    49,    52,    54,    56,    58,    60,
      62,    64,   190,    93,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   211,   217,    77,     0,
     215,   216,   202,   203,     0,   213,   204,   205,   206,   207,
     240,   237,     0,   155,    27,     0,     0,   172,   158,   171,
       0,   165,   167,     0,     0,   122,   115,   120,     0,     0,
     126,   128,   124,   132,     0,    32,    79,   139,   133,   137,
       0,    24,     0,    21,    22,     0,     0,   193,     0,     0,
       0,   198,     0,   174,     0,     0,    14,    15,     0,     0,
       0,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,     0,    23,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   229,   230,   231,     0,     0,   218,   212,   214,
       0,   154,   150,     0,   149,    27,     0,     0,     0,   169,
     176,   170,   177,   156,     0,   157,     0,   114,   129,     0,
     121,     0,   134,     0,     0,     0,   201,   191,     0,   194,
     197,   199,     7,     0,   176,   175,     0,    13,     0,    10,
       0,    18,    12,    65,    36,    37,    35,    39,    40,    42,
      43,    47,    48,    45,    46,    50,    51,    53,    55,    57,
      59,    61,     0,   208,     0,   210,     0,     0,     0,     0,
       0,     0,   228,   232,    78,     0,     0,   153,   148,   180,
      27,     0,   186,     0,     0,   178,     0,     0,   166,   168,
     173,   127,   130,    25,     0,   200,   192,   195,     0,     0,
      33,     9,    11,     0,     0,   209,     0,     0,     0,     0,
       0,     0,   151,   152,   184,   181,   187,   179,   182,    27,
       0,   188,     0,   196,     0,    19,    63,   219,   221,   222,
       0,     0,     0,     0,     0,   185,   183,   189,    16,     0,
       0,     0,   226,     0,   224,     0,    17,   220,   223,   227,
     225
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,   106,   107,   290,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   138,
     212,   139,   177,    27,    71,    46,    47,    29,    30,    31,
      32,    79,    80,    81,   169,   170,    33,    60,    61,    34,
      35,    62,    49,    50,    65,   333,   161,   162,   163,   194,
     334,   262,   187,   188,   189,   190,   191,   141,   142,   143,
     144,   145,   146,   147,   148,   149,    36,    37,    38,    73
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -267
static const yytype_int16 yypact[] =
{
    1441,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,    43,    15,  -267,    60,  1441,
    1441,  -267,    57,  -267,  1441,  1441,  1441,  -267,  -267,   -29,
      74,  -267,  -267,    53,  -267,   137,    -6,  -267,  1219,    68,
      17,  -267,  -267,    31,  1466,  -267,  -267,  -267,    74,   102,
     -50,  -267,    65,  -267,  -267,   137,    53,  -267,   850,   433,
    -267,    60,  -267,  1374,   749,  1097,    68,  1466,  1466,  1297,
    -267,     8,  1466,   -17,  1038,  -267,    29,  -267,  -267,  -267,
    -267,   136,  -267,  -267,  -267,  1088,  1101,  1101,   345,   660,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,    10,   317,  1038,
    -267,   113,    75,   198,    52,   231,   124,    61,   109,   199,
      41,  -267,  -267,  -267,   159,  1038,   163,   170,   172,   180,
     713,   182,   254,   173,   189,   454,  -267,  -267,  -267,   176,
    -267,  -267,  -267,  -267,   520,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,   150,  -267,   200,   210,   801,  -267,  -267,    18,
     211,   220,  -267,   185,  1332,  -267,  -267,  -267,  1038,   186,
    -267,   222,  -267,  -267,    37,  -267,  -267,  -267,  -267,  -267,
     660,  -267,   660,  -267,  -267,  1038,   294,  -267,   105,   850,
     -10,  -267,   202,     3,   232,   300,  -267,  -267,  1038,   888,
     327,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  1038,  -267,  1038,  1038,  1038,  1038,  1038,  1038,
    1038,  1038,  1038,  1038,  1038,  1038,  1038,  1038,  1038,  1038,
    1038,  1038,  1038,   713,   275,   713,  1038,  1038,  1038,   295,
     607,   282,  -267,  -267,  -267,   203,  1038,  -267,  -267,  -267,
     837,  -267,  -267,  1038,  -267,   289,   290,   864,   333,  -267,
      42,  -267,   123,  -267,  1415,  -267,   358,  -267,  -267,     8,
    -267,  1038,  -267,   288,   315,   293,  -267,  -267,   229,  -267,
    -267,  -267,  -267,  1160,   131,  -267,   951,  -267,    -2,  -267,
     213,  -267,  -267,  -267,  -267,  -267,  -267,   113,   113,    75,
      75,   198,   198,   198,   198,    52,    52,   231,   124,    61,
     109,   199,   164,  -267,   713,  -267,   216,   219,   230,   318,
     541,   541,  -267,  -267,  -267,   320,   328,  -267,  -267,  -267,
     329,   330,  -267,   319,   335,   123,   975,  1260,  -267,  -267,
    -267,  -267,  -267,   326,   326,  -267,  -267,  -267,   850,   345,
    -267,  -267,  -267,  1038,  1038,  -267,   713,   713,   713,  1038,
     988,  1001,  -267,  -267,  -267,  -267,  -267,  -267,  -267,   334,
     340,  -267,   341,  -267,   145,  -267,  -267,   357,  -267,  -267,
     238,   713,   241,   713,   246,  -267,  -267,  -267,  -267,   323,
     713,   343,  -267,   713,  -267,   713,  -267,  -267,  -267,  -267,
    -267
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -267,  -267,  -267,  -267,  -267,   -58,  -267,   -85,   106,   114,
       1,   130,   193,   196,   192,   201,   195,  -267,   -82,   -67,
    -267,   -86,   -97,   -25,     0,  -267,   362,  -267,   128,  -267,
    -267,   352,   -65,    -4,  -267,   171,  -267,   374,   -76,    39,
    -267,   -19,   -44,   -12,   -47,   -70,  -267,   179,  -267,    62,
    -143,  -219,   -64,    95,  -266,  -267,   255,  -127,  -267,     9,
    -267,   302,  -186,  -267,  -267,  -267,  -267,   411,  -267,  -267
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      28,   122,   176,   239,   123,   160,    76,   155,   280,    48,
     179,    42,   348,   192,   167,    41,   261,   195,   196,   197,
      42,    42,    85,    70,   213,    86,   175,   156,   234,    51,
      52,   122,    59,    64,    55,    56,    28,   181,   183,   184,
      59,   335,    58,   176,   140,    42,    39,    91,   150,   245,
     285,   175,    91,    89,   321,   173,    42,    72,   174,   185,
      53,   231,   171,    42,   221,   335,   222,   175,   351,    66,
      67,   268,   257,   246,   165,   159,   283,    59,   172,   198,
     186,    43,   151,   199,    63,   168,   176,   257,   275,   256,
      43,   258,    45,    82,   192,   193,   192,    45,   179,   167,
     200,   178,    77,   176,    88,   250,   313,    45,   315,   272,
     175,   257,   288,    63,    40,   258,    82,    82,    82,   140,
      84,    82,   122,   348,   232,   279,    43,   175,    54,   294,
     295,   296,   291,    43,   360,   361,    44,    74,    82,    87,
     259,    75,    45,   223,   224,   293,   312,   260,   228,    45,
     316,   317,   318,   217,    68,   218,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   342,     8,   193,   277,   193,   324,
     278,   284,    78,   325,    17,    18,   326,   355,     8,   176,
     331,    63,   336,   229,   214,    88,   337,    17,    18,   215,
     257,   350,   216,    82,   283,    78,    78,    78,   219,   220,
      78,   122,   227,   175,   347,   320,    76,   388,   230,    82,
     389,    82,   301,   302,   303,   304,    45,    78,   175,   377,
     378,   379,    92,    93,    94,    95,   233,    96,    97,   246,
     235,   354,   273,   236,   274,   237,   260,   225,   226,   242,
     171,   246,   247,   238,   392,   240,   394,   241,   159,   265,
     266,   269,   270,   397,   159,   243,   399,   372,   400,   370,
     251,   284,   376,   380,   382,   384,   282,   246,   246,   323,
     252,   122,   122,   159,   373,   263,   375,   352,   353,    88,
     356,   246,    78,   357,   246,   264,   175,   276,   185,   271,
      98,   346,    99,   287,   358,   246,   286,   100,    78,   101,
      78,   102,   391,   246,   103,   393,   246,   104,   105,   186,
     395,   246,   122,   297,   298,   347,    92,    93,    94,    95,
     292,    96,    97,   299,   300,   201,    42,   159,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,    92,    93,
      94,    95,   314,    96,    97,   305,   306,   319,   322,   327,
     328,   340,   343,   345,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,   344,
     362,   359,   185,   366,    98,   396,    99,   349,   363,   364,
     365,   100,   257,   101,   385,   102,   258,   332,   103,   367,
     386,   104,   105,   186,   185,   387,    98,   390,    99,   398,
     307,   309,    45,   100,   308,   101,   311,   102,    90,   164,
     103,   310,    83,   104,   105,   186,   124,    93,    94,    95,
     341,    96,    97,   339,   374,   281,   249,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,    93,    94,
      95,     0,    96,    97,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     0,
     125,   126,   127,     0,   128,   129,   130,   131,   132,   133,
     134,   135,     0,     0,    69,   136,    99,     0,     0,   137,
       0,   100,     0,   101,     0,   102,     0,     0,   103,     0,
       0,   104,   105,   124,    93,    94,    95,    99,    96,    97,
     244,     0,   100,     0,   101,     0,   102,     0,     0,   103,
       0,     0,   104,   105,    92,    93,    94,    95,     0,    96,
      97,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     0,   125,   126,   127,
       0,   128,   129,   130,   131,   132,   133,   134,   135,     0,
       0,    69,   248,    99,     0,     0,   137,     0,   100,     0,
     101,     0,   102,     0,     0,   103,     0,     0,   104,   105,
      92,    93,    94,    95,    99,    96,    97,   137,     0,   100,
       0,   101,     0,   102,     0,     0,   103,     0,     0,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    92,    93,    94,    95,     0,    96,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      99,     0,     0,   137,     0,   100,     0,   101,     0,   102,
       0,     1,   103,     0,     0,   104,   105,     0,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,   124,    93,    94,    95,
       0,    96,    97,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,     0,     0,     0,   100,     0,
     101,     0,   102,     0,     0,   103,     0,     0,   104,   105,
       0,     0,    92,    93,    94,    95,     0,    96,    97,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     125,   126,   127,     0,   128,   129,   130,   131,   132,   133,
     134,   135,     0,   152,    69,     0,    99,     8,     0,   137,
       0,   100,     0,   101,     0,   102,    17,    18,   103,     0,
       0,   104,   105,     0,    92,    93,    94,    95,     0,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,   153,
       0,     0,    99,     0,     0,     0,     0,   100,     0,   101,
       0,   102,     0,     0,   103,   253,     0,   104,   154,     8,
      92,    93,    94,    95,     0,    96,    97,     0,    17,    18,
       0,     0,     0,    92,    93,    94,    95,     0,    96,    97,
       0,     0,     0,     0,     0,     0,     0,    92,    93,    94,
      95,   254,    96,    97,    99,     8,     0,     0,     0,   100,
       0,   101,     0,   102,    17,    18,   103,     0,     0,   104,
     255,    92,    93,    94,    95,     0,    96,    97,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      99,     0,     0,     0,     0,   100,     0,   101,     0,   102,
       0,    98,   103,    99,     0,   104,   105,     0,   100,     0,
     101,     0,   102,     0,   329,   103,     0,    99,   104,   105,
       0,     0,   100,     0,   101,     0,   102,     0,     0,   103,
       0,     0,   104,   330,    92,    93,    94,    95,     0,    96,
      97,    99,   289,     0,     0,     0,   100,     0,   101,     0,
     102,     0,     0,   103,     0,     0,   104,   105,    92,    93,
      94,    95,     0,    96,    97,     0,     0,     0,     0,     0,
       0,    92,    93,    94,    95,     0,    96,    97,     0,     0,
       0,     0,     0,     0,    92,    93,    94,    95,     0,    96,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   349,     0,    99,     0,     0,     0,     0,   100,
       0,   101,     0,   102,     0,     0,   103,     0,     0,   104,
     105,    92,    93,    94,    95,   368,    96,    97,    99,     0,
       0,     0,     0,   100,     0,   101,     0,   102,     0,     0,
     103,    99,   381,   104,   369,     0,   100,     0,   101,     0,
     102,     0,     0,   103,    99,   383,   104,   105,     0,   100,
       0,   101,     0,   102,     0,     0,   103,     0,     0,   104,
     105,    92,    93,    94,    95,     0,    96,    97,     0,     0,
     157,     0,     0,     0,    92,    93,    94,    95,     0,    96,
      97,    99,     0,     0,     0,     0,   100,     0,   101,     0,
     102,     0,     0,   103,     0,     0,   104,   105,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,   180,     0,     0,     0,     0,   100,     0,   101,     0,
     102,   158,     0,   103,   182,     0,   104,   105,     0,   100,
       0,   101,     0,   102,     0,     0,   103,     0,     0,   104,
     105,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   257,
       0,     0,     0,   283,   332,     0,     0,    68,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      69,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     0,
       0,     0,     0,     0,   371,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,     0,     0,     0,     0,   166,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   267,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    69,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,   338,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     1,     0,     0,
       0,     0,     0,     0,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25
};

static const yytype_int16 yycheck[] =
{
       0,    68,    84,   130,    68,    75,    50,    74,    18,    28,
      86,     3,   278,    99,    79,     0,   159,     7,     8,     9,
       3,     3,    72,    48,   109,    75,    84,    74,   125,    29,
      30,    98,     3,    45,    34,    35,    36,    95,    96,    97,
       3,   260,    71,   125,    69,     3,     3,    66,    73,   135,
     193,   109,    71,    65,   240,    72,     3,    48,    75,    69,
       3,    20,    81,     3,    12,   284,    14,   125,    70,    75,
      76,   168,    69,    75,    78,    75,    73,     3,    82,    69,
      90,    73,    73,    73,    45,    77,   168,    69,   185,   156,
      73,    73,    89,    54,   180,    99,   182,    89,   174,   164,
      90,    72,    71,   185,    65,   152,   233,    89,   235,    72,
     168,    69,   198,    74,    71,    73,    77,    78,    79,   144,
      18,    82,   189,   389,    83,   189,    73,   185,    71,   214,
     215,   216,   199,    73,   320,   321,    76,    69,    99,    74,
     159,    73,    89,    91,    92,   212,   232,   159,    87,    89,
     236,   237,   238,    78,    18,    80,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   271,    38,   180,    72,   182,   246,
      75,   193,    54,   250,    47,    48,   253,   314,    38,   271,
     257,   152,    69,    84,    81,   156,    73,    47,    48,    86,
      69,   286,    89,   164,    73,    77,    78,    79,    10,    11,
      82,   278,    88,   271,   278,   240,   260,    72,    19,   180,
      75,   182,   221,   222,   223,   224,    89,    99,   286,   356,
     357,   358,     3,     4,     5,     6,    77,     8,     9,    75,
      77,    77,   180,    73,   182,    73,   258,    16,    17,    76,
     269,    75,    76,    73,   381,    73,   383,     3,   258,    74,
      75,    75,    76,   390,   264,    76,   393,   337,   395,   336,
      70,   283,   354,   359,   360,   361,    74,    75,    75,    76,
      70,   348,   349,   283,   348,    74,   353,    74,    75,   250,
      74,    75,   164,    74,    75,    75,   354,     3,    69,    77,
      71,    72,    73,     3,    74,    75,    74,    78,   180,    80,
     182,    82,    74,    75,    85,    74,    75,    88,    89,    90,
      74,    75,   389,   217,   218,   389,     3,     4,     5,     6,
       3,     8,     9,   219,   220,    18,     3,   337,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     3,     4,
       5,     6,    77,     8,     9,   225,   226,    62,    76,    70,
      70,     3,    74,    70,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    74,
      70,    73,    69,    74,    71,    72,    73,    71,    70,    70,
      70,    78,    69,    80,    70,    82,    73,    74,    85,    74,
      70,    88,    89,    90,    69,    74,    71,    60,    73,    76,
     227,   229,    89,    78,   228,    80,   231,    82,    66,    77,
      85,   230,    58,    88,    89,    90,     3,     4,     5,     6,
     269,     8,     9,   264,   349,   190,   144,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      57,    58,    59,    -1,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    -1,    71,    72,    73,    -1,    -1,    76,
      -1,    78,    -1,    80,    -1,    82,    -1,    -1,    85,    -1,
      -1,    88,    89,     3,     4,     5,     6,    73,     8,     9,
      76,    -1,    78,    -1,    80,    -1,    82,    -1,    -1,    85,
      -1,    -1,    88,    89,     3,     4,     5,     6,    -1,     8,
       9,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    57,    58,    59,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    -1,
      -1,    71,    72,    73,    -1,    -1,    76,    -1,    78,    -1,
      80,    -1,    82,    -1,    -1,    85,    -1,    -1,    88,    89,
       3,     4,     5,     6,    73,     8,     9,    76,    -1,    78,
      -1,    80,    -1,    82,    -1,    -1,    85,    -1,    -1,    88,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    -1,    -1,    76,    -1,    78,    -1,    80,    -1,    82,
      -1,    31,    85,    -1,    -1,    88,    89,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,     3,     4,     5,     6,
      -1,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    -1,    -1,    -1,    -1,    78,    -1,
      80,    -1,    82,    -1,    -1,    85,    -1,    -1,    88,    89,
      -1,    -1,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    -1,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    34,    71,    -1,    73,    38,    -1,    76,
      -1,    78,    -1,    80,    -1,    82,    47,    48,    85,    -1,
      -1,    88,    89,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    -1,    73,    -1,    -1,    -1,    -1,    78,    -1,    80,
      -1,    82,    -1,    -1,    85,    34,    -1,    88,    89,    38,
       3,     4,     5,     6,    -1,     8,     9,    -1,    47,    48,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    70,     8,     9,    73,    38,    -1,    -1,    -1,    78,
      -1,    80,    -1,    82,    47,    48,    85,    -1,    -1,    88,
      89,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    -1,    -1,    -1,    -1,    78,    -1,    80,    -1,    82,
      -1,    71,    85,    73,    -1,    88,    89,    -1,    78,    -1,
      80,    -1,    82,    -1,    70,    85,    -1,    73,    88,    89,
      -1,    -1,    78,    -1,    80,    -1,    82,    -1,    -1,    85,
      -1,    -1,    88,    89,     3,     4,     5,     6,    -1,     8,
       9,    73,    74,    -1,    -1,    -1,    78,    -1,    80,    -1,
      82,    -1,    -1,    85,    -1,    -1,    88,    89,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    73,    -1,    -1,    -1,    -1,    78,
      -1,    80,    -1,    82,    -1,    -1,    85,    -1,    -1,    88,
      89,     3,     4,     5,     6,    70,     8,     9,    73,    -1,
      -1,    -1,    -1,    78,    -1,    80,    -1,    82,    -1,    -1,
      85,    73,    74,    88,    89,    -1,    78,    -1,    80,    -1,
      82,    -1,    -1,    85,    73,    74,    88,    89,    -1,    78,
      -1,    80,    -1,    82,    -1,    -1,    85,    -1,    -1,    88,
      89,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
       3,    -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    73,    -1,    -1,    -1,    -1,    78,    -1,    80,    -1,
      82,    -1,    -1,    85,    -1,    -1,    88,    89,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    -1,    -1,    -1,    -1,    78,    -1,    80,    -1,
      82,    74,    -1,    85,    73,    -1,    88,    89,    -1,    78,
      -1,    80,    -1,    82,    -1,    -1,    85,    -1,    -1,    88,
      89,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    73,    74,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    74,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    72,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    94,   116,   117,   120,
     121,   122,   123,   129,   132,   133,   159,   160,   161,     3,
      71,     0,     3,    73,    76,    89,   118,   119,   134,   135,
     136,   117,   117,     3,    71,   117,   117,   160,    71,     3,
     130,   131,   134,   132,   136,   137,    75,    76,    18,    71,
     116,   117,   152,   162,    69,    73,   135,    71,   121,   124,
     125,   126,   132,   130,    18,    72,    75,    74,   132,   136,
     119,   134,     3,     4,     5,     6,     8,     9,    71,    73,
      78,    80,    82,    85,    88,    89,    95,    96,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   145,     3,    57,    58,    59,    61,    62,
      63,    64,    65,    66,    67,    68,    72,    76,   112,   114,
     116,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     116,   152,    34,    70,    89,   112,   137,     3,    74,   117,
     138,   139,   140,   141,   124,   126,    72,   125,    77,   127,
     128,   134,   126,    72,    75,    98,   111,   115,    72,   131,
      73,    98,    73,    98,    98,    69,    90,   145,   146,   147,
     148,   149,   114,   126,   142,     7,     8,     9,    69,    73,
      90,    18,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,   113,   100,    81,    86,    89,    78,    80,    10,
      11,    12,    14,    91,    92,    16,    17,    88,    87,    84,
      19,    20,    83,    77,   115,    77,    73,    73,    73,   150,
      73,     3,    76,    76,    76,   114,    75,    76,    72,   154,
     137,    70,    70,    34,    70,    89,   112,    69,    73,   134,
     136,   143,   144,    74,    75,    74,    75,    72,   115,    75,
      76,    77,    72,   142,   142,   115,     3,    72,    75,   145,
      18,   149,    74,    73,   136,   143,    74,     3,   114,    74,
      97,   112,     3,   112,   100,   100,   100,   101,   101,   102,
     102,   103,   103,   103,   103,   104,   104,   105,   106,   107,
     108,   109,   114,   150,    77,   150,   114,   114,   114,    62,
     116,   155,    76,    76,   112,   112,   112,    70,    70,    70,
      89,   112,    74,   138,   143,   144,    69,    73,    56,   140,
       3,   128,   115,    74,    74,    70,    72,   145,   147,    71,
     100,    70,    74,    75,    77,   150,    74,    74,    74,    73,
     155,   155,    70,    70,    70,    70,    74,    74,    70,    89,
     112,    74,   138,   145,   146,   112,   111,   150,   150,   150,
     114,    74,   114,    74,   114,    70,    70,    74,    72,    75,
      60,    74,   150,    74,   150,    74,    72,   150,    76,   150,
     150
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 51 "grammar.y"
    { printf("parsing okay");;}
    break;

  case 4:
#line 55 "grammar.y"
    { printf("dasda1\n"); ;}
    break;

  case 5:
#line 56 "grammar.y"
    { std::cout<<" a contant value" <<   (yyvsp[(1) - (1)].dval) <<std::endl; ;}
    break;

  case 6:
#line 57 "grammar.y"
    { printf("dasda3\n"); ;}
    break;

  case 7:
#line 58 "grammar.y"
    { printf("dasda4\n"); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2178 "grammar.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 494 "grammar.y"


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

