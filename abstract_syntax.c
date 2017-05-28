#include "abstract_syntax.h"

AST_decl_t AST_funcs_decl(int pos, list_t funcs)
{
    AST_decl_t p = checked_malloc(sizeof(*p));
    p->kind = AST_FUNCS_DECL;
    p->pos = pos;
    p->u.funcs = funcs;
    return p;
}

AST_decl_t AST_types_decl(int pos, list_t types)
{
    AST_decl_t p = checked_malloc(sizeof(*p));
    p->kind = AST_TYPES_DECL;
    p->pos = pos;
    p->u.types = types;
    return p;
}

AST_decl_t AST_var_decl(int pos, symbol_t var, symbol_t type, AST_expr_t init)
{
    AST_decl_t p = checked_malloc(sizeof(*p));
    p->kind = AST_VAR_DECL;
    p->pos = pos;
    p->u.var.var = var;
    p->u.var.type = type;
    p->u.var.init = init;
    p->u.var.escape = false;
    return p;
}

AST_expr_t AST_nil_expr(int pos)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_NIL_EXPR;
    p->pos = pos;
    return p;
}

AST_expr_t AST_var_expr(int pos, AST_var_t var)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_VAR_EXPR;
    p->pos = pos;
    p->u.var = var;
    return p;
}

AST_expr_t AST_num_expr(int pos, int num)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_NUM_EXPR;
    p->pos = pos;
    p->u.num = num;
    return p;
}

AST_expr_t AST_string_expr(int pos, string_t str)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_STRING_EXPR;
    p->pos = pos;
    p->u.str = str;
    return p;
}

AST_expr_t AST_call_expr(int pos, symbol_t func, list_t args)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_CALL_EXPR;
    p->pos = pos;
    p->u.call.func = func;
    p->u.call.args = args;
    return p;
}

AST_expr_t AST_op_expr(int pos, AST_expr_t left, AST_binop_t op, AST_expr_t right)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_OP_EXPR;
    p->pos = pos;
    p->u.op.left = left;
    p->u.op.op = op;
    p->u.op.right = right;
    return p;
}

AST_expr_t AST_record_expr(int pos, symbol_t type, list_t efields)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_RECORD_EXPR;
    p->pos = pos;
    p->u.record.type = type;
    p->u.record.efields = efields;
    return p;
}

AST_expr_t AST_array_expr(int pos, symbol_t type, AST_expr_t size, AST_expr_t init)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_ARRAY_EXPR;
    p->pos = pos;
    p->u.array.type = type;
    p->u.array.size = size;
    p->u.array.init = init;
    return p;
}

AST_expr_t AST_seq_expr(int pos, list_t seq)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_SEQ_EXPR;
    p->pos = pos;
    p->u.seq = seq;
    return p;
}

AST_expr_t AST_if_expr(int pos, AST_expr_t cond, AST_expr_t then, AST_expr_t else_)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_IF_EXPR;
    p->pos = pos;
    p->u.if_.cond = cond;
    p->u.if_.then = then;
    p->u.if_.else_ = else_;
    return p;
}

AST_expr_t AST_while_expr(int pos, AST_expr_t cond, AST_expr_t body)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_WHILE_EXPR;
    p->pos = pos;
    p->u.while_.cond = cond;
    p->u.while_.body = body;
    return p;
}

AST_expr_t AST_for_expr(int pos, symbol_t var, AST_expr_t lo, AST_expr_t hi, AST_expr_t body)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_FOR_EXPR;
    p->pos = pos;
    p->u.for_.var = var;
    p->u.for_.lo = lo;
    p->u.for_.hi = hi;
    p->u.for_.body = body;
    p->u.for_.escape = false;
    return p;
}

AST_expr_t AST_break_expr(int pos)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_BREAK_EXPR;
    p->pos = pos;
    return p;
}

AST_expr_t AST_let_expr(int pos, list_t decls, AST_expr_t body)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_LET_EXPR;
    p->pos = pos;
    p->u.let.decls = decls;
    p->u.let.body = body;
    return p;
}

AST_expr_t AST_assign_expr(int pos, AST_var_t var, AST_expr_t expr)
{
    AST_expr_t p = checked_malloc(sizeof(*p));
    p->kind = AST_ASSIGN_EXPR;
    p->pos = pos;
    p->u.assign.var = var;
    p->u.assign.expr = expr;
    return p;
}

AST_type_t AST_name_type(int pos, symbol_t name)
{
    AST_type_t p = checked_malloc(sizeof(*p));
    p->kind = AST_NAME_TYPE;
    p->pos = pos;
    p->u.name = name;
    return p;
}

AST_type_t AST_record_type(int pos, list_t record)
{
    AST_type_t p = checked_malloc(sizeof(*p));
    p->kind = AST_RECORD_TYPE;
    p->pos = pos;
    p->u.record = record;
    return p;
}

AST_type_t AST_array_type(int pos, symbol_t array)
{
    AST_type_t p = checked_malloc(sizeof(*p));
    p->kind = AST_ARRAY_TYPE;
    p->pos = pos;
    p->u.array = array;
    return p;
}

AST_var_t AST_simple_var(int pos, symbol_t simple)
{
    AST_var_t p = checked_malloc(sizeof(*p));
    p->kind = AST_SIMPLE_VAR;
    p->pos = pos;
    p->u.simple = simple;
    return p;
}

AST_var_t AST_field_var(int pos, AST_var_t var, symbol_t field)
{
    AST_var_t p = checked_malloc(sizeof(*p));
    p->kind = AST_FIELD_VAR;
    p->pos = pos;
    p->u.field.var = var;
    p->u.field.field = field;
    return p;
}

AST_var_t AST_sub_var(int pos, AST_var_t var, AST_expr_t sub)
{
    AST_var_t p = checked_malloc(sizeof(*p));
    p->kind = AST_SUB_VAR;
    p->pos = pos;
    p->u.sub.var = var;
    p->u.sub.sub = sub;
    return p;
}

AST_efield_t AST_efield(int pos, symbol_t name, AST_expr_t expr)
{
    AST_efield_t p = checked_malloc(sizeof(*p));
    p->pos = pos;
    p->name = name;
    p->expr = expr;
    return p;
}

AST_field_t AST_field(symbol_t name, symbol_t type)
{
    AST_field_t p = checked_malloc(sizeof(*p));
    p->name = name;
    p->type = type;
    p->escape = false;
    return p;
}

AST_func_t AST_func(int pos, symbol_t name, list_t params, symbol_t result, AST_expr_t body)
{
    AST_func_t p = checked_malloc(sizeof(*p));
    p->pos = pos;
    p->name = name;
    p->params = params;
    p->result = result;
    p->body = body;
    return p;
}

AST_nametype_t AST_nametype(symbol_t name, AST_type_t type)
{
    AST_nametype_t p = checked_malloc(sizeof(*p));
    p->name = name;
    p->type = type;
    return p;
}
