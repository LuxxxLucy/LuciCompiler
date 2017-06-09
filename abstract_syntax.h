#ifndef INCLUDE__AST_H
#define INCLUDE__AST_H

#include "symbol.h"
#include "utils.h"

typedef struct AST_decl_ *AST_decl_ptr  ;
typedef struct AST_expr_ *AST_expr_ptr  ;
typedef struct AST_type_ *AST_type_ptr  ;
typedef struct AST_var_ *AST_var_ptr  ;

typedef struct AST_efield_ *AST_efield_ptr  ;
typedef struct AST_field_ *AST_field_ptr  ;
typedef struct AST_func_ *AST_func_ptr  ;
typedef struct AST_nametype_ *AST_nametype_ptr  ;

struct AST_efield_ { int pos; symbol_ptr  name; AST_expr_ptr  expr; };
AST_efield_ptr  AST_efield(int pos, symbol_ptr  name, AST_expr_ptr  expr);
struct AST_field_ { symbol_ptr  name, type; booll escape; };
AST_field_ptr  AST_field(symbol_ptr  name, symbol_ptr  type);
struct AST_func_ { int pos; symbol_ptr  name; list_ptr  params; symbol_ptr  result; AST_expr_ptr  body; };
AST_func_ptr  AST_func(int pos, symbol_ptr  name, list_ptr  params, symbol_ptr  result, AST_expr_ptr  body);
struct AST_nametype_ { symbol_ptr  name; AST_type_ptr  type; };
AST_nametype_ptr  AST_nametype(symbol_ptr  name, AST_type_ptr  type);

typedef enum { AST_SIMPLE_VAR, AST_FIELD_VAR, AST_SUB_VAR } varKind;
struct AST_var_
{
    varKind kind;
    int pos;
    union
    {
        symbol_ptr  simple;
        /* var must be the ftreest field to simplify the parser implementation. */
        struct { AST_var_ptr  var; symbol_ptr  field; } field;
        struct { AST_var_ptr  var; AST_expr_ptr  sub; } sub;
    } u;
};

typedef enum AST_binop_e
{
    AST_PLUS, AST_MINUS, AST_TIMES, AST_DIVIDE,AST_MOD,
    AST_AND,AST_XOR,AST_OR,
    AST_LSHIFT,AST_RSHIFT,AST_ARSHIFT,
    AST_EQ, AST_NEQ, AST_LT, AST_LE, AST_GT, AST_GE
}AST_binop_ptr  ;

typedef enum { AST_FUNCS_DECL, AST_TYPES_DECL, AST_VAR_DECL, } decKind;
struct AST_decl_
{
    decKind kind;
    int pos;
    union
    {
        list_ptr  funcs;
        list_ptr  types;
        struct { symbol_ptr  var; symbol_ptr  type; AST_expr_ptr  init; booll escape; } var;
    } u;
};

typedef enum
    {
        AST_NIL_EXPR, AST_VAR_EXPR, AST_NUM_EXPR, AST_STRING_EXPR,
        AST_CALL_EXPR, AST_OP_EXPR, AST_RECORD_EXPR, AST_ARRAY_EXPR,
        AST_SEQ_EXPR, AST_IF_EXPR, AST_WHILE_EXPR, AST_FOR_EXPR,
        AST_BREAK_EXPR, AST_LET_EXPR, AST_ASSIGN_EXPR,
    } expKind;
struct AST_expr_
{
    expKind kind;
    int pos;
    union
    {
        /* nil; */
        AST_var_ptr  var;
        int num;
        string_ptr  str;
        struct { symbol_ptr  func; list_ptr  args; } call;
        struct { AST_expr_ptr  left; AST_binop_ptr  op; AST_expr_ptr  right; } op;
        struct { symbol_ptr  type; list_ptr  efields; } record;
        struct { symbol_ptr  type; AST_expr_ptr  size, init; } array;
        list_ptr  seq;
        struct { AST_expr_ptr  cond, then, else_; } if_;
        struct { AST_expr_ptr  cond, body; } while_;
        struct { symbol_ptr  var; AST_expr_ptr  lo, hi, body; booll escape; } for_;
        /* break; */
        struct { list_ptr  decls; AST_expr_ptr  body; } let;
        struct { AST_var_ptr  var; AST_expr_ptr  expr; } assign;
    } u;
};

typedef enum { AST_NAME_TYPE, AST_RECORD_TYPE, AST_ARRAY_TYPE } tyKind;
struct AST_type_
{
    tyKind kind;
    int pos;
    union
    {
        symbol_ptr  name;
        list_ptr  record;
        symbol_ptr  array;
    } u;
};


// abstract syntax function for varibales
AST_var_ptr  AST_simple_var(int pos, symbol_ptr  simple);
AST_var_ptr  AST_field_var(int pos, AST_var_ptr  var, symbol_ptr  field);
AST_var_ptr  AST_sub_var(int pos, AST_var_ptr  var, AST_expr_ptr  sub);

// abstract syntax function for declarations
AST_decl_ptr  AST_funcs_decl(int pos, list_ptr  funcs);
AST_decl_ptr  AST_types_decl(int pos, list_ptr  types);
AST_decl_ptr  AST_var_decl(int pos, symbol_ptr  var, symbol_ptr  type, AST_expr_ptr  init);

// abstract syntax function for expressions
AST_expr_ptr  AST_nil_expr(int pos);
AST_expr_ptr  AST_var_expr(int pos, AST_var_ptr  var);
AST_expr_ptr  AST_num_expr(int pos, int num);
AST_expr_ptr  AST_string_expr(int pos, string_ptr  str);
AST_expr_ptr  AST_call_expr(int pos, symbol_ptr  func, list_ptr  args);
AST_expr_ptr  AST_op_expr(int pos, AST_expr_ptr  left, AST_binop_ptr  op, AST_expr_ptr  right);
AST_expr_ptr  AST_record_expr(int pos, symbol_ptr  type, list_ptr  efields);
AST_expr_ptr  AST_array_expr(int pos, symbol_ptr  type, AST_expr_ptr  size, AST_expr_ptr  init);
AST_expr_ptr  AST_seq_expr(int pos, list_ptr  seq);
AST_expr_ptr  AST_if_expr(int pos, AST_expr_ptr  cond, AST_expr_ptr  then, AST_expr_ptr  else_);
AST_expr_ptr  AST_while_expr(int pos, AST_expr_ptr  cond, AST_expr_ptr  body);
AST_expr_ptr  AST_for_expr(int pos, symbol_ptr  var, AST_expr_ptr  lo, AST_expr_ptr  hi, AST_expr_ptr  body);
AST_expr_ptr  AST_break_expr(int pos);
AST_expr_ptr  AST_let_expr(int pos, list_ptr  decls, AST_expr_ptr  body);
AST_expr_ptr  AST_assign_expr(int pos, AST_var_ptr  var, AST_expr_ptr  expr);
AST_type_ptr  AST_name_type(int pos, symbol_ptr  name);
AST_type_ptr  AST_record_type(int pos, list_ptr  record);
AST_type_ptr  AST_array_type(int pos, symbol_ptr  array);

// abstract syntax function for expressions

#endif
