#ifndef INCLUDE__AST_H
#define INCLUDE__AST_H

#include "symbol.h"
#include "utils.h"

typedef struct AST_decl_s *AST_decl_t;
typedef struct AST_expr_s *AST_expr_t;
typedef struct AST_type_s *AST_type_t;
typedef struct AST_var_s *AST_var_t;

typedef struct AST_efield_s *AST_efield_t;
typedef struct AST_field_s *AST_field_t;
typedef struct AST_func_s *AST_func_t;
typedef struct AST_nametype_s *AST_nametype_t;

typedef enum AST_binop_e
{
    AST_PLUS, AST_MINUS, AST_TIMES, AST_DIVIDE,
    AST_EQ, AST_NEQ, AST_LT, AST_LE, AST_GT, AST_GE,
}AST_binop_t ;

typedef enum { AST_FUNCS_DECL, AST_TYPES_DECL, AST_VAR_DECL, } decKind;
struct AST_decl_s
{
    decKind kind;
    int pos;
    union
    {
        list_t funcs;
        list_t types;
        struct { symbol_t var; symbol_t type; AST_expr_t init; booll escape; } var;
    } u;
};
AST_decl_t AST_funcs_decl(int pos, list_t funcs);
AST_decl_t AST_types_decl(int pos, list_t types);
AST_decl_t AST_var_decl(int pos, symbol_t var, symbol_t type, AST_expr_t init);

typedef enum
    {
        AST_NIL_EXPR, AST_VAR_EXPR, AST_NUM_EXPR, AST_STRING_EXPR,
        AST_CALL_EXPR, AST_OP_EXPR, AST_RECORD_EXPR, AST_ARRAY_EXPR,
        AST_SEQ_EXPR, AST_IF_EXPR, AST_WHILE_EXPR, AST_FOR_EXPR,
        AST_BREAK_EXPR, AST_LET_EXPR, AST_ASSIGN_EXPR,
    } expKind;
struct AST_expr_s
{
    expKind kind;
    int pos;
    union
    {
        /* nil; */
        AST_var_t var;
        int num;
        string_t str;
        struct { symbol_t func; list_t args; } call;
        struct { AST_expr_t left; AST_binop_t op; AST_expr_t right; } op;
        struct { symbol_t type; list_t efields; } record;
        struct { symbol_t type; AST_expr_t size, init; } array;
        list_t seq;
        struct { AST_expr_t cond, then, else_; } if_;
        struct { AST_expr_t cond, body; } while_;
        struct { symbol_t var; AST_expr_t lo, hi, body; booll escape; } for_;
        /* break; */
        struct { list_t decls; AST_expr_t body; } let;
        struct { AST_var_t var; AST_expr_t expr; } assign;
    } u;
};
AST_expr_t AST_nil_expr(int pos);
AST_expr_t AST_var_expr(int pos, AST_var_t var);
AST_expr_t AST_num_expr(int pos, int num);
AST_expr_t AST_string_expr(int pos, string_t str);
AST_expr_t AST_call_expr(int pos, symbol_t func, list_t args);
AST_expr_t AST_op_expr(int pos, AST_expr_t left, AST_binop_t op, AST_expr_t right);
AST_expr_t AST_record_expr(int pos, symbol_t type, list_t efields);
AST_expr_t AST_array_expr(int pos, symbol_t type, AST_expr_t size, AST_expr_t init);
AST_expr_t AST_seq_expr(int pos, list_t seq);
AST_expr_t AST_if_expr(int pos, AST_expr_t cond, AST_expr_t then, AST_expr_t else_);
AST_expr_t AST_while_expr(int pos, AST_expr_t cond, AST_expr_t body);
AST_expr_t AST_for_expr(int pos, symbol_t var, AST_expr_t lo, AST_expr_t hi, AST_expr_t body);
AST_expr_t AST_break_expr(int pos);
AST_expr_t AST_let_expr(int pos, list_t decls, AST_expr_t body);
AST_expr_t AST_assign_expr(int pos, AST_var_t var, AST_expr_t expr);

typedef enum { AST_NAME_TYPE, AST_RECORD_TYPE, AST_ARRAY_TYPE } tyKind;
struct AST_type_s
{
    tyKind kind;
    int pos;
    union
    {
        symbol_t name;
        list_t record;
        symbol_t array;
    } u;
};
AST_type_t AST_name_type(int pos, symbol_t name);
AST_type_t AST_record_type(int pos, list_t record);
AST_type_t AST_array_type(int pos, symbol_t array);

typedef enum { AST_SIMPLE_VAR, AST_FIELD_VAR, AST_SUB_VAR } varKind;
struct AST_var_s
{
    varKind kind;
    int pos;
    union
    {
        symbol_t simple;
        /* var must be the ftreest field to simplify the parser implementation. */
        struct { AST_var_t var; symbol_t field; } field;
        struct { AST_var_t var; AST_expr_t sub; } sub;
    } u;
};
AST_var_t AST_simple_var(int pos, symbol_t simple);
AST_var_t AST_field_var(int pos, AST_var_t var, symbol_t field);
AST_var_t AST_sub_var(int pos, AST_var_t var, AST_expr_t sub);

struct AST_efield_s { int pos; symbol_t name; AST_expr_t expr; };
AST_efield_t AST_efield(int pos, symbol_t name, AST_expr_t expr);
struct AST_field_s { symbol_t name, type; booll escape; };
AST_field_t AST_field(symbol_t name, symbol_t type);
struct AST_func_s { int pos; symbol_t name; list_t params; symbol_t result; AST_expr_t body; };
AST_func_t AST_func(int pos, symbol_t name, list_t params, symbol_t result, AST_expr_t body);
struct AST_nametype_s { symbol_t name; AST_type_t type; };
AST_nametype_t AST_nametype(symbol_t name, AST_type_t type);

#endif
