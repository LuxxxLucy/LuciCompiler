typedef union  {
	int pos;
	int ival;
	string sval;
	} YYSTYPE;
extern YYSTYPE yylval;

# define ID 257
# define STRING 258
# define INT 259
# define COMMA 260
# define COLON 261
# define SEMICOLON 262
# define LPAREN 263
# define RPAREN 264
# define LBRACK 265
# define RBRACK 266
# define LBRACE 267
# define RBRACE 268
# define DOT 269
# define PLUS 270
# define MINUS 271
# define TIMES 272
# define DIVIDE 273
# define EQ_OP 274
# define NEQ_OP 275
# define LT_OP 276
# define LE_OP 277
# define GT_OP 278
# define GE_OP 279
# define AND 280
# define OR 281
# define ASSIGN 282
# define ARRAY 283
# define IF 284
# define THEN 285
# define ELSE 286
# define WHILE 287
# define FOR 288
# define TO 289
# define DO 290
# define LET 291
# define IN 292
# define END 293
# define OF 294
# define BREAK 295
# define NIL 296
# define FUNCTION 297
# define VAR 298
# define TYPE 299
# define CASE 300
# define CHAR 301
# define CONST 302
# define CONTINUE 303
# define DEFAULT 304
# define DOUBLE 305
# define FLOAT 306
# define GOTO 307
# define LONG 308
# define RETURN 309
# define SIZEOF 310
# define STATIC 311
# define STRUCT 312
# define SWITCH 313
# define CONSTANT 314
# define VOID 315
# define TYPEDEF 316
# define ADD_ASSIGN 317
# define SUB_ASSIGN 318
# define MUL_ASSIGN 319
# define DIV_ASSIGN 320
# define MOD_ASSIGN 321
# define AND_ASSIGN 322
# define XOR_ASSIGN 323
# define OR_ASSIGN 324
# define RIGHT_OP 325
# define LEFT_OP 326
# define INC_OP 327
# define DEC_OP 328
# define PTR_OP 329
# define AND_OP 330
# define OR_OP 331
