#include "abstract_syntax.h"

AST_var_ptr  AST_simple_var(int pos, symbol_ptr  simple)
{
    AST_var_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_SIMPLE_VAR;
    p->pos = pos;
    p->u.simple = simple;
    return p;
}

AST_var_ptr  AST_field_var(int pos, AST_var_ptr  var, symbol_ptr  field)
{
    AST_var_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_FIELD_VAR;
    p->pos = pos;
    p->u.field.var = var;
    p->u.field.field = field;
    return p;
}

AST_var_ptr  AST_sub_var(int pos, AST_var_ptr  var, AST_expr_ptr  sub)
{
    AST_var_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_SUB_VAR;
    p->pos = pos;
    p->u.sub.var = var;
    p->u.sub.sub = sub;
    return p;
}

AST_decl_ptr  AST_funcs_decl(int pos, list_ptr  funcs)
{
    AST_decl_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_FUNCS_DECL;
    p->pos = pos;
    p->u.funcs = funcs;
    return p;
}

AST_decl_ptr  AST_types_decl(int pos, list_ptr  types)
{
    AST_decl_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_TYPES_DECL;
    p->pos = pos;
    p->u.types = types;
    return p;
}

AST_decl_ptr  AST_var_decl(int pos, symbol_ptr  var, symbol_ptr  type, AST_expr_ptr  init)
{
    AST_decl_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_VAR_DECL;
    p->pos = pos;
    p->u.var.var = var;
    p->u.var.type = type;
    p->u.var.init = init;
    p->u.var.escape = false;
    return p;
}

AST_expr_ptr  AST_nil_expr(int pos)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_NIL_EXPR;
    p->pos = pos;
    return p;
}

AST_expr_ptr  AST_var_expr(int pos, AST_var_ptr  var)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_VAR_EXPR;
    p->pos = pos;
    p->u.var = var;
    return p;
}

AST_expr_ptr  AST_num_expr(int pos, int num)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_NUM_EXPR;
    p->pos = pos;
    p->u.num = num;
    return p;
}

AST_expr_ptr  AST_string_expr(int pos, string_ptr  str)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_STRING_EXPR;
    p->pos = pos;
    p->u.str = str;
    return p;
}

AST_expr_ptr  AST_call_expr(int pos, symbol_ptr  func, list_ptr  args)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_CALL_EXPR;
    p->pos = pos;
    p->u.call.func = func;
    p->u.call.args = args;
    return p;
}

AST_expr_ptr  AST_op_expr(int pos, AST_expr_ptr  left, AST_binop_ptr  op, AST_expr_ptr  right)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_OP_EXPR;
    p->pos = pos;
    p->u.op.left = left;
    p->u.op.op = op;
    p->u.op.right = right;
    return p;
}

AST_expr_ptr  AST_record_expr(int pos, symbol_ptr  type, list_ptr  efields)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_RECORD_EXPR;
    p->pos = pos;
    p->u.record.type = type;
    p->u.record.efields = efields;
    return p;
}

AST_expr_ptr  AST_array_expr(int pos, symbol_ptr  type, AST_expr_ptr  size, AST_expr_ptr  init)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_ARRAY_EXPR;
    p->pos = pos;
    p->u.array.type = type;
    p->u.array.size = size;
    p->u.array.init = init;
    return p;
}

AST_expr_ptr  AST_seq_expr(int pos, list_ptr  seq)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_SEQ_EXPR;
    p->pos = pos;
    p->u.seq = seq;
    return p;
}

AST_expr_ptr  AST_if_expr(int pos, AST_expr_ptr  cond, AST_expr_ptr  then, AST_expr_ptr  else_)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_IF_EXPR;
    p->pos = pos;
    p->u.if_.cond = cond;
    p->u.if_.then = then;
    p->u.if_.else_ = else_;
    return p;
}

AST_expr_ptr  AST_while_expr(int pos, AST_expr_ptr  cond, AST_expr_ptr  body)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_WHILE_EXPR;
    p->pos = pos;
    p->u.while_.cond = cond;
    p->u.while_.body = body;
    return p;
}

AST_expr_ptr  AST_for_expr(int pos, symbol_ptr  var, AST_expr_ptr  lo, AST_expr_ptr  hi, AST_expr_ptr  body)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_FOR_EXPR;
    p->pos = pos;
    p->u.for_.var = var;
    p->u.for_.lo = lo;
    p->u.for_.hi = hi;
    p->u.for_.body = body;
    p->u.for_.escape = false;
    return p;
}

AST_expr_ptr  AST_break_expr(int pos)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_BREAK_EXPR;
    p->pos = pos;
    return p;
}

AST_expr_ptr  AST_let_expr(int pos, list_ptr  decls, AST_expr_ptr  body)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_LET_EXPR;
    p->pos = pos;
    p->u.let.decls = decls;
    p->u.let.body = body;
    return p;
}

AST_expr_ptr  AST_assign_expr(int pos, AST_var_ptr  var, AST_expr_ptr  expr)
{
    AST_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_ASSIGN_EXPR;
    p->pos = pos;
    p->u.assign.var = var;
    p->u.assign.expr = expr;
    return p;
}

AST_type_ptr  AST_name_type(int pos, symbol_ptr  name)
{
    AST_type_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_NAME_TYPE;
    p->pos = pos;
    p->u.name = name;
    return p;
}

AST_type_ptr  AST_record_type(int pos, list_ptr  record)
{
    AST_type_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_RECORD_TYPE;
    p->pos = pos;
    p->u.record = record;
    return p;
}

AST_type_ptr  AST_array_type(int pos, symbol_ptr  array)
{
    AST_type_ptr  p = checked_malloc(sizeof(*p));
    p->kind = AST_ARRAY_TYPE;
    p->pos = pos;
    p->u.array = array;
    return p;
}

AST_efield_ptr  AST_efield(int pos, symbol_ptr  name, AST_expr_ptr  expr)
{
    AST_efield_ptr  p = checked_malloc(sizeof(*p));
    p->pos = pos;
    p->name = name;
    p->expr = expr;
    return p;
}

AST_field_ptr  AST_field(symbol_ptr  name, symbol_ptr  type)
{
    AST_field_ptr  p = checked_malloc(sizeof(*p));
    p->name = name;
    p->type = type;
    p->escape = false;
    return p;
}

AST_func_ptr  AST_func(int pos, symbol_ptr  name, list_ptr  params, symbol_ptr  result, AST_expr_ptr  body)
{
    AST_func_ptr  p = checked_malloc(sizeof(*p));
    p->pos = pos;
    p->name = name;
    p->params = params;
    p->result = result;
    p->body = body;
    return p;
}

AST_nametype_ptr  AST_nametype(symbol_ptr  name, AST_type_ptr  type)
{
    AST_nametype_ptr  p = checked_malloc(sizeof(*p));
    p->name = name;
    p->type = type;
    return p;
}
