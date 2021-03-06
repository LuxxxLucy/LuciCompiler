#include <stdlib.h>

#include "env.h"
#include "error_message.h"
#include "frame.h"
#include "tree.h"
#include "ppAST.h"
#include "semantic.h"
#include "translate.h"
#include "types.h"

static table_ptr  _venv;
static table_ptr  _tenv;


expr_type_ptr  expr_type(tr_expr_ptr  expr, type_ptr  type)
{
    expr_type_ptr  result;
    result.expr = expr;
    result.type = type;
    return result;
}

static tr_expr_ptr  trans_decl(tr_level_ptr  level, AST_decl_ptr  decl);
static expr_type_ptr  trans_expr(tr_level_ptr  level, AST_expr_ptr  expr);
static type_ptr  trans_type(AST_type_ptr  type);
static expr_type_ptr  trans_var(tr_level_ptr  level, AST_var_ptr  var);

#if 0 /* for debug only */
static void show_types(void *key, void *value)
{
    string_ptr  name = sym_name((symbol_ptr) key);
    type_ptr  type = value;
    printf("name: %s; type: ", name);
    ty_print(type);
    printf("\n");
}
#endif

static type_ptr  lookup_type(symbol_ptr  name, int pos)
{
    type_ptr  type = sym_lookup(_tenv, name);
    if (type)
        type = ty_actual(type);
    else
        em_error(pos, "undefined type '%s'", sym_name(name));
    return type;
}

static list_ptr  formal_type_list(list_ptr  params, int pos)
{
    list_ptr  p, q = NULL, r = NULL;

    for (p = params; p; p = p->next)
    {
        AST_field_ptr  field = p->data;
        type_ptr  type = lookup_type(field->type, pos);
        if (!type)
            type = ty_int();
        if (r)
        {
            r->next = list(type, NULL);
            r = r->next;
        }
        else
            q = r = list(type, NULL);
    }
    return q;
}

static list_ptr  formal_escape_list(list_ptr  params)
{
    list_ptr  p = params, q = NULL, r = NULL;
    for (; p; p = p->next)
    {
        list_ptr  bl = bool_list(((AST_field_ptr) p->data)->escape, NULL);
        if (r)
        {
            r->next = bl;
            r = r->next;
        }
        else
            q = r = bl;
    }
    return q;
}

static tr_expr_ptr  trans_funcs_decl(tr_level_ptr  level, AST_decl_ptr  decl)
{
    list_ptr  p, q;
    expr_type_ptr  result;

    /* Check for function redefinitions. */
    for (p = decl->u.funcs; p && p->next; p = p->next)
        for (q = p->next; q; q = q->next)
        {
            AST_func_ptr  func = q->data;
            if (((AST_func_ptr) p->data)->name == func->name)
                em_error(func->pos,
                         "function '%s' redefined",
                         sym_name(func->name));
        }

    /* Enter function prototypes into symbol table. */
    for (p = decl->u.funcs; p; p = p->next)
    {
        AST_func_ptr  func = p->data;
        list_ptr  formals = formal_type_list(func->params, decl->pos);
        list_ptr  escapes = formal_escape_list(func->params);
        type_ptr  result;
        tmp_label_ptr  label = tmp_label();

        if (func->result)
        {
            result = lookup_type(func->result, decl->pos);
            if (!result)
                result = ty_int();
        }
        else
            result = ty_void();
        sym_enter(_venv,
                  func->name,
                  E_FunEntry(tr_level(level, label, escapes),
                                 label,
                                 formals,
                                 result));
    }

    /* Translate the possibly mutually recursive functions. */
    for (p = decl->u.funcs; p; p = p->next)
    {
        AST_func_ptr  func = p->data;
        E_entry_ptr  entry = sym_lookup(_venv, func->name);
        list_ptr  q = func->params;
        list_ptr  r = entry->u.func.formals;
        list_ptr  s = tr_formals(entry->u.func.level)->next;

        sym_begin_scope(_venv);
        for (; q; q = q->next, r = r->next, s = s->next)
        {
            sym_enter(_venv,
                      ((AST_field_ptr) q->data)->name,
                      E_VarEntry(s->data, r->data, false));
        }
        assert(!q && !r);
        result = trans_expr(entry->u.func.level, func->body);
        if (!ty_match(result.type, entry->u.func.result))
            em_error(func->pos, "function body's type is incorrect");
        sym_end_scope(_venv);
    }

    fr_add_frag(fr_proc_frag(tree_move_stmt(tree_tmp_expr(fr_rv()),
                                          un_ex(result.expr)),
                             tr_level_frame(level)));
    return NULL;
}

static tr_expr_ptr  trans_types_decl(tr_level_ptr  level, AST_decl_ptr  decl)
{
    list_ptr  p, q;

    /* Check for type redefinitions. */
    for (p = decl->u.types; p && p->next; p = p->next)
        for (q = p->next; q; q = q->next)
        {
            AST_nametype_ptr  nt = q->data;
            if (((AST_nametype_ptr) p->data)->name == nt->name)
                em_error(decl->pos, "type '%s' redefined", sym_name(nt->name));
        }

    /* Enter type placeholder into symbol table. */
    for (p = decl->u.types; p; p = p->next)
    {
        AST_nametype_ptr  nametype = p->data;
        sym_enter(_tenv, nametype->name, ty_name(nametype->name, NULL));
    }

    /* Translate possibly mutually recursive types. */
    for (p = decl->u.types; p; p = p->next)
    {
        AST_nametype_ptr  nametype = p->data;
        type_ptr  type = sym_lookup(_tenv, nametype->name);
        type->u.name.type = trans_type(nametype->type);
    }

    /* Check for infinite recursive types. */
    for (p = decl->u.types; p; p = p->next)
    {
        AST_nametype_ptr  nametype = p->data;
        type_ptr  type = sym_lookup(_tenv, nametype->name);
        if (ty_actual(type) == type)
            em_error(decl->pos,
                     "infinite recursive type '%s'",
                     sym_name(nametype->name));
    }

    return NULL;
}

static tr_expr_ptr  trans_var_decl(tr_level_ptr  level, AST_decl_ptr  decl)
{
    expr_type_ptr  init = trans_expr(level, decl->u.var.init);
    type_ptr  type = init.type;
    tr_access_ptr  access = tr_alloc_local(level, decl->u.var.escape);

    if (decl->u.var.type)
    {
        type = lookup_type(decl->u.var.type, decl->pos);
        if (!type)
            type = ty_int();
        if (!ty_match(type, init.type))
            em_error(decl->pos,
                     "initializer has incorrect type");
    }
    else if (init.type->kind == TY_NIL)
        em_error(decl->pos, "don't know which record type to take");
    else if (init.type->kind == TY_VOID)
        em_error(decl->pos, "can't assign void value to a variable");
    sym_enter(_venv, decl->u.var.var, E_VarEntry(access, type, false));

    return tr_assign_expr(tr_simple_var(access, level), init.expr);
}

typedef tr_expr_ptr  (*trans_decl_func)(tr_level_ptr  level, AST_decl_ptr);
/* XXX Keep sync with AST_decl_t's declaration! */
static trans_decl_func _trans_decl_funcs[] =
{
    trans_funcs_decl,
    trans_types_decl,
    trans_var_decl,
};

static tr_expr_ptr  trans_decl(tr_level_ptr  level, AST_decl_ptr  decl)
{
    return _trans_decl_funcs[decl->kind](level, decl);
}

static expr_type_ptr  trans_nil_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    return expr_type(tr_num_expr(0), ty_nil());
}

static expr_type_ptr  trans_var_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    return trans_var(level, expr->u.var);
}

static expr_type_ptr  trans_num_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    return expr_type(tr_num_expr(expr->u.num), ty_int());
}

static expr_type_ptr  trans_string_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    return expr_type(tr_string_expr(expr->u.str), ty_string());
}

static expr_type_ptr  trans_call_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    E_entry_ptr  entry = sym_lookup(_venv, expr->u.call.func);
    list_ptr  l_formals, l_args, l_args2 = NULL, l_next = NULL;
    int i;

    if (!entry)
    {
        em_error(expr->pos,
                 "undefined function '%s'",
                 sym_name(expr->u.call.func));
        return expr_type(NULL, ty_int());
    }
    else if (entry->kind != ENV_FUNC_ENTRY)
    {
        em_error(expr->pos,
                 "'%s' is not a function",
                 sym_name(expr->u.call.func));
        return expr_type(NULL, ty_int());
    }

    for (l_formals = entry->u.func.formals, l_args = expr->u.call.args, i = 1;
         l_formals && l_args;
         l_formals = l_formals->next, l_args = l_args->next, i++)
    {
        expr_type_ptr  et = trans_expr(level, (AST_expr_ptr) l_args->data);
        if (!ty_match(l_formals->data, et.type))
            em_error(expr->pos,
                     "passing argument %d of '%s' with wrong type",
                     i,
                     sym_name(expr->u.call.func));

        if (l_args2)
            l_next = l_next->next = list(et.expr, NULL);
        else
            l_args2 = l_next = list(et.expr, NULL);
    }
    if (l_formals)
        em_error(expr->pos, "expect more arguments");
    else if (l_args)
        em_error(expr->pos, "expect less arguments");

    return expr_type(tr_call_expr(entry->u.func.level,
                                  entry->u.func.label,
                                  l_args2),
                     ty_actual(entry->u.func.result));
}

static expr_type_ptr  trans_op_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    AST_binop_ptr  op = expr->u.op.op;
    expr_type_ptr  left = trans_expr(level, expr->u.op.left);
    expr_type_ptr  right = trans_expr(level, expr->u.op.right);

    switch (op) {
        case AST_PLUS:
        case AST_MINUS:
        case AST_TIMES:
        case AST_DIVIDE:
        case AST_MOD:
        case AST_AND:
        case AST_OR:
        case AST_XOR:
        case AST_LSHIFT:
        case AST_RSHIFT:
        case AST_ARSHIFT:
            if (left.type->kind != TY_INT)
                em_error(expr->u.op.left->pos, "integer requtreeed");
            if (right.type->kind != TY_INT)
                em_error(expr->u.op.right->pos, "integer requtreeed");
            return expr_type(
              tr_op_expr(op-AST_PLUS+IR_PLUS, left.expr, right.expr),
              ty_int());

        case AST_EQ:
        case AST_NEQ:
        {
            tr_expr_ptr  result = NULL;
            if (!ty_match(left.type, right.type))
                em_error(expr->pos,
                         "the type of two operands must be the same");
            else if (left.type->kind == TY_STRING)
                result = tr_string_rel_expr(
                  op-AST_EQ+IR_EQ, left.expr, right.expr);
            else
                result = tr_rel_expr(op-AST_EQ+IR_EQ, left.expr, right.expr);
            return expr_type(result, ty_int());
        }

        case AST_LT:
        case AST_LE:
        case AST_GT:
        case AST_GE: {
            tr_expr_ptr  result = NULL;
            if (!ty_match(left.type, right.type))
                em_error(expr->pos,
                         "the type of two operands must be the same");
            if (left.type->kind != TY_INT && left.type->kind != TY_STRING)
                em_error(expr->pos,
                         "the type of comparison's operand must be int or string");
            if (left.type->kind == TY_STRING)
                result = tr_string_rel_expr(
                  op-AST_LT+IR_LT, left.expr, right.expr);
            else
                result = tr_rel_expr(op-AST_LT+IR_LT, left.expr, right.expr);
            return expr_type(result, left.type);
        }
    }

    assert(0);
    return expr_type(NULL, NULL);
}

static expr_type_ptr  trans_record_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    type_ptr  type = lookup_type(expr->u.record.type, expr->pos);
    list_ptr  p, q;
    list_ptr  fields = NULL, next = NULL;
    int size = 0;

    if (!type)
        return expr_type(NULL, ty_nil());
    if (type->kind != TY_RECORD)
        em_error(expr->pos,
                 "'%s' is not a record type",
                 sym_name(expr->u.record.type));
    for (p = type->u.record, q = expr->u.record.efields;
         p && q;
         p = p->next, q = q->next, size++)
    {
        AST_efield_ptr  efield = q->data;
        expr_type_ptr  et = trans_expr(level, efield->expr);
        if (!ty_match(((ty_field_ptr) p->data)->type, et.type))
            em_error(efield->pos, "wrong field type");
        if (fields)
            next = next->next = list(et.expr, NULL);
        else
            fields = next = list(et.expr, NULL);
    }
    if (p || q)
        em_error(expr->pos, "wrong field number");
    return expr_type(tr_record_expr(fields, size), type);
}

static expr_type_ptr  trans_array_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    type_ptr  type = lookup_type(expr->u.array.type, expr->pos);
    expr_type_ptr  size = trans_expr(level, expr->u.array.size);
    expr_type_ptr  init = trans_expr(level, expr->u.array.init);

    if (!type)
        return expr_type(NULL, ty_int());
    if (type->kind != TY_ARRAY)
        em_error(expr->pos,
                 "'%s' is not an array type",
                 sym_name(expr->u.array.type));
    if (size.type->kind != TY_INT)
        em_error(expr->pos, "array's size must be the int type");
    if (!ty_match(type->u.array, init.type))
        em_error(expr->pos, "initializer has incorrect type");
    return expr_type(tr_array_expr(size.expr, init.expr), type);
}

static expr_type_ptr  trans_seq_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    list_ptr  p = expr->u.seq;
    list_ptr  stmts = NULL, next = NULL;

    for (; p; p = p->next)
    {
        expr_type_ptr  et = trans_expr(level, (AST_expr_ptr) p->data);
        if (stmts)
            next = next->next = list(et.expr, NULL);
        else
            stmts = next = list(et.expr, NULL);
        if (!p->next)
            return expr_type(tr_seq_expr(stmts), et.type);
    }
    return expr_type(tr_num_expr(0), ty_void());
}

static expr_type_ptr  trans_if_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    expr_type_ptr  cond = trans_expr(level, expr->u.if_.cond);
    expr_type_ptr  then = trans_expr(level, expr->u.if_.then);

    if (cond.type->kind != TY_INT)
        em_error(expr->pos,
                 "condition's type must be integer");
    if (expr->u.if_.else_)
    {
        expr_type_ptr  else_ = trans_expr(level, expr->u.if_.else_);
        if (!ty_match(then.type, else_.type))
            em_error(expr->pos, "types of then and else differ");
        return expr_type(tr_if_expr(cond.expr, then.expr, else_.expr),
                         then.type);
    }
    else if (then.type->kind != TY_VOID)
        em_error(expr->pos, "if-then should return nothing");
    return expr_type(tr_if_expr(cond.expr, then.expr, NULL), ty_void());
}

static expr_type_ptr  trans_while_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    expr_type_ptr  cond = trans_expr(level, expr->u.while_.cond);
    expr_type_ptr  body = trans_expr(level, expr->u.while_.body);
    if (cond.type->kind != TY_INT)
        em_error(expr->pos, "condition's type must be integer");
    if (body.type->kind != TY_VOID)
        em_error(expr->pos, "while should return nothing");
    return expr_type(tr_while_expr(cond.expr, body.expr), ty_void());
}

static expr_type_ptr  trans_for_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    expr_type_ptr  lo = trans_expr(level, expr->u.for_.lo);
    expr_type_ptr  hi = trans_expr(level, expr->u.for_.hi);
    expr_type_ptr  body;
    tr_access_ptr  access = tr_alloc_local(level, expr->u.for_.escape);

    if (lo.type->kind != TY_INT)
        em_error(expr->pos, "lo expression should be int type");
    if (hi.type->kind != TY_INT)
        em_error(expr->pos, "hi expression should be int type");
    sym_begin_scope(_venv);
    sym_enter(_venv, expr->u.for_.var, E_VarEntry(access, ty_int(), true));
    /* TODO Check assignment to the variable. */
    body = trans_expr(level, expr->u.for_.body);
    if (body.type->kind != TY_VOID)
        em_error(expr->pos, "for should return nothing");
    sym_end_scope(_venv);
    return expr_type(tr_for_expr(access, lo.expr, hi.expr, body.expr),
                     ty_void());
}

static expr_type_ptr  trans_break_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    /* TODO Check for outer for or while statement. */
    return expr_type(NULL, ty_void());
}

static expr_type_ptr  trans_let_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    expr_type_ptr  result;
    list_ptr  p;
    list_ptr  tr_exprs = NULL;

    sym_begin_scope(_venv);
    sym_begin_scope(_tenv);

    for (p = expr->u.let.decls; p; p = p->next)
    {
        tr_expr_ptr  tr_expr = trans_decl(level, p->data);
        if (tr_expr)
        {
            tr_exprs = join_list(tr_exprs, list(tr_expr, NULL));
        }
    }

    result = trans_expr(level, expr->u.let.body);
    tr_exprs = join_list(tr_exprs, list(result.expr, NULL));
    result.expr = tr_seq_expr(tr_exprs);

    sym_end_scope(_venv);
    sym_end_scope(_tenv);

    return result;
}

static expr_type_ptr  trans_assign_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    expr_type_ptr  var = trans_var(level, expr->u.assign.var);
    expr_type_ptr  et = trans_expr(level, expr->u.assign.expr);

    if (!ty_match(var.type, et.type))
        em_error(expr->pos, "type mismatch");

    if (expr->u.assign.var->kind == AST_SIMPLE_VAR && var.type->kind == TY_INT)
    {
        /* Check for the assignment to the for variable. */
        AST_var_ptr  v = expr->u.assign.var;
        E_entry_ptr  entry = sym_lookup(_venv, v->u.simple);
        if (entry && entry->kind == ENV_VAR_ENTRY && entry->u.var.for_)
            em_error(expr->pos, "assigning to the for variable");
    }

    return expr_type(tr_assign_expr(var.expr, et.expr), ty_void());
}

typedef expr_type_ptr  (*trans_expr_func)(tr_level_ptr  level, AST_expr_ptr);
static trans_expr_func _trans_expr_funcs[] =
{
    trans_nil_expr,
    trans_var_expr,
    trans_num_expr,
    trans_string_expr,
    trans_call_expr,
    trans_op_expr,
    trans_record_expr,
    trans_array_expr,
    trans_seq_expr,
    trans_if_expr,
    trans_while_expr,
    trans_for_expr,
    trans_break_expr,
    trans_let_expr,
    trans_assign_expr,
};

static expr_type_ptr  trans_expr(tr_level_ptr  level, AST_expr_ptr  expr)
{
    return _trans_expr_funcs[expr->kind](level, expr);
}

static type_ptr  trans_name_type(AST_type_ptr  type)
{
    type_ptr  t = sym_lookup(_tenv, type->u.name);
    if (!t)
    {
        em_error(type->pos, "undefined type '%s'", sym_name(type->u.name));
        t = ty_int();
    }
    return t;
}

static type_ptr  trans_record_type(AST_type_ptr  type)
{
    list_ptr  p = type->u.record;
    list_ptr  q = NULL, r = NULL;

    for (; p; p = p->next)
    {
        AST_field_ptr  field = p->data;
        type_ptr  t = sym_lookup(_tenv, field->type);

        if (!t)
        {
            em_error(type->pos, "undefined type '%s'", sym_name(field->type));
            t = ty_int();
        }
        if (r)
        {
            r->next = list(ty_field(field->name, t), NULL);
            r = r->next;
        }
        else
            q = r = list(ty_field(field->name, t), NULL);
    }
    return ty_record(q);
}

static type_ptr  trans_array_type(AST_type_ptr  type)
{
    type_ptr  t = sym_lookup(_tenv, type->u.array);
    if (!t)
    {
        em_error(type->pos, "undefined type '%s'", type->u.array);
        t = ty_int();
    }
    return ty_array(t);
}

typedef type_ptr  (*trans_type_func)(AST_type_ptr);
static trans_type_func _trans_type_funcs[] =
{
    trans_name_type,
    trans_record_type,
    trans_array_type,
};

static type_ptr  trans_type(AST_type_ptr  type)
{
    return _trans_type_funcs[type->kind](type);
}

static expr_type_ptr  trans_simple_var(tr_level_ptr  level, AST_var_ptr  var)
{
    E_entry_ptr  entry = sym_lookup(_venv, var->u.simple);

    if (!entry)
    {
        em_error(var->pos, "undefined variable '%s'", sym_name(var->u.simple));
        return expr_type(tr_num_expr(0), ty_int());
    }
    else if (entry->kind != ENV_VAR_ENTRY)
    {
        em_error(var->pos,
                 "expected '%s' to be a variable, not a function",
                 sym_name(var->u.simple));
        return expr_type(tr_num_expr(0), ty_int());
    }

    return expr_type(tr_simple_var(entry->u.var.access, level),
                     ty_actual(entry->u.var.type));
}

static expr_type_ptr  trans_field_var(tr_level_ptr  level, AST_var_ptr  var)
{
    expr_type_ptr  et = trans_var(level, var->u.field.var);
    list_ptr  p;
    int i;

    if (et.type->kind != TY_RECORD)
    {
        em_error(var->pos, "expected record type variable");
        return expr_type(tr_num_expr(0), ty_int());
    }

    for (p = et.type->u.record, i = 0; p; p = p->next, ++i)
    {
        ty_field_ptr  field = p->data;
        if (field->name == var->u.field.field)
        {
            return expr_type(tr_field_var(et.expr, i),
                             ty_actual(field->type));
        }
    }

    em_error(var->pos,
             "there is no field named '%s'",
             sym_name(var->u.field.field));
    return expr_type(tr_num_expr(0), ty_int());
}

static expr_type_ptr  trans_sub_var(tr_level_ptr  level, AST_var_ptr  var)
{
    expr_type_ptr  et = trans_var(level, var->u.sub.var);
    expr_type_ptr  sub = trans_expr(level, var->u.sub.sub);

    if (et.type->kind != TY_ARRAY)
    {
        em_error(var->pos, "expected array type variable");
        return expr_type(NULL, ty_int());
    }
    if (sub.type->kind != TY_INT)
        em_error(var->pos, "expected integer type subscript");
    return expr_type(NULL, ty_actual(et.type->u.array));
}

typedef expr_type_ptr  (*trans_var_func)(tr_level_ptr  level, AST_var_ptr);
static trans_var_func _trans_var_funcs[] =
{
    trans_simple_var,
    trans_field_var,
    trans_sub_var,
};

static expr_type_ptr  trans_var(tr_level_ptr  level, AST_var_ptr  var)
{
    return _trans_var_funcs[var->kind](level, var);
}

expr_type_ptr sem_trans_prog(AST_expr_ptr  prog)
{
    expr_type_ptr  result;

    _venv = E_base_venv();
    _tenv = E_base_tenv();
    result = trans_expr(tr_outermost(), prog);
    if (em_any_errors)
    {
        exit(1);
    }


    return result;
}
