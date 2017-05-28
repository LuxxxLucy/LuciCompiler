#include <assert.h>

#include "frame.h"
#include "tree.h"
#include "pptree.h"
#include "translate.h"

struct tr_access_s
{
    tr_level_t level;
    fr_access_t access;
};

static tr_access_t tr_access(tr_level_t level, fr_access_t access)
{
    tr_access_t p = checked_malloc(sizeof(*p));
    p->level = level;
    p->access = access;
    return p;
}

struct tr_level_s
{
    tr_level_t parent;
    frame_t frame;
    list_t formals;
    list_t locals;
};

static tr_level_t _outermost = NULL;

tr_level_t tr_outermost(void)
{
    if (!_outermost)
        _outermost = tr_level(NULL, tmp_label(), NULL);
    return _outermost;
}

tr_level_t tr_level(tr_level_t parent, tmp_label_t name, list_t formals)
{
    tr_level_t p = checked_malloc(sizeof(*p));
    list_t fr_formal, q = NULL;

    p->parent = parent;
    /* extra formal for static link */
    p->frame = frame(name, bool_list(true, formals));
    fr_formal = fr_formals(p->frame);
    for (; fr_formal; fr_formal = fr_formal->next)
    {
        tr_access_t access = tr_access(p, fr_formal->data);
        if (q)
        {
            q->next = list(access, NULL);
            q = q->next;
        }
        else
            p->formals = q = list(access, NULL);
    }
    p->locals = NULL;
    return p;
}

list_t tr_formals(tr_level_t level)
{
    return level->formals;
}

tr_access_t tr_alloc_local(tr_level_t level, booll escape)
{
    fr_access_t fr_access = fr_alloc_local(level->frame, escape);
    tr_access_t access = tr_access(level, fr_access);

    if (level->locals)
    {
        list_t p = level->locals;
        while (p->next)
            p = p->next;
        p->next = list(access, NULL);
    }
    else
        level->locals = list(access, NULL);
    return access;
}

frame_t tr_level_frame(tr_level_t level)
{
    return level->frame;
}

static tr_access_t tr_static_link(tr_level_t level)
{
    assert(level);
    return level->formals->data;
}

struct cx_s
{
    list_t trues;
    list_t falses;
    tree_stmt_t stmt;
};

struct tr_expr_s
{
    enum { TR_EX, TR_NX, TR_CX } kind;
    union
    {
        tree_expr_t ex;
        tree_stmt_t nx;
        cx_t cx;
    } u;
};

static tr_expr_t tr_ex(tree_expr_t expr)
{
    tr_expr_t p = checked_malloc(sizeof(*p));
    p->kind = TR_EX;
    p->u.ex = expr;
    return p;
}

static tr_expr_t tr_nx(tree_stmt_t stmt)
{
    tr_expr_t p = checked_malloc(sizeof(*p));
    p->kind = TR_NX;
    p->u.nx = stmt;
    return p;
}

static tr_expr_t tr_cx(list_t trues, list_t falses, tree_stmt_t stmt)
{
    tr_expr_t p = checked_malloc(sizeof(*p));
    p->kind = TR_CX;
    p->u.cx.trues = trues;
    p->u.cx.falses = falses;
    p->u.cx.stmt = stmt;
    return p;
}

static void fill_patch(list_t patchs, tmp_label_t label)
{
    list_t p = patchs;
    for (; p; p = p->next)
        *((tmp_label_t *) p->data) = label;
}

tree_expr_t un_ex(tr_expr_t expr)
{
    switch (expr->kind)
    {
        case TR_EX:
            return expr->u.ex;
        case TR_NX:
            return tree_eseq_expr(expr->u.nx, tree_const_expr(0));
        case TR_CX: {
            temp_t tmp = temp();
            tmp_label_t t = tmp_label();
            tmp_label_t f = tmp_label();
            fill_patch(expr->u.cx.trues, t);
            fill_patch(expr->u.cx.falses, f);
            return tree_eseq_expr(
              tree_seq_stmt(vlist(
                  5,
                  tree_move_stmt(tree_tmp_expr(tmp),
                               tree_const_expr(1)),
                  expr->u.cx.stmt,
                  tree_label_stmt(f),
                  tree_move_stmt(tree_tmp_expr(tmp),
                               tree_const_expr(0)),
                  tree_label_stmt(t))),
              tree_tmp_expr(tmp));
        }
    }

    assert(0);
    return NULL;
}

tree_stmt_t un_nx(tr_expr_t expr)
{
    switch (expr->kind)
    {
        case TR_EX:
            return tree_expr_stmt(expr->u.ex);
        case TR_NX:
            return expr->u.nx;
        case TR_CX: {
            tmp_label_t label = tmp_label();
            fill_patch(expr->u.cx.trues, label);
            fill_patch(expr->u.cx.falses, label);
            return tree_seq_stmt(list(expr->u.cx.stmt,
                                    list(tree_label_stmt(label), NULL)));
        }
    }

    assert(0);
    return NULL;
}

cx_t un_cx(tr_expr_t expr)
{
    cx_t cx = { 0 };

    switch (expr->kind)
    {
        case TR_EX:
            cx.stmt = tree_cjump_stmt(
              IR_EQ, expr->u.ex, tree_const_expr(0), NULL, NULL);
            cx.trues = list(&(cx.stmt->u.cjump.t), NULL);
            cx.falses = list(&(cx.stmt->u.cjump.f), NULL);
            return cx;

        case TR_NX:
            assert(0);

        case TR_CX:
            return expr->u.cx;
    }

    assert(0);
    return cx;
}

tr_expr_t tr_num_expr(int num)
{
    return tr_ex(tree_const_expr(num));
}

tr_expr_t tr_string_expr(string_t str)
{
    tmp_label_t label = tmp_label();
    fr_frag_t frag = fr_string_frag(label, str);
    fr_add_frag(frag);
    return tr_ex(tree_name_expr(label));
}

tr_expr_t tr_call_expr(tr_level_t level, tmp_label_t label, list_t args)
{
    tree_expr_t func = tree_name_expr(label);
    tree_expr_t fp = tree_const_expr(fr_offset(
        tr_static_link(level)->access));
    list_t l_args = list(fp, NULL);
    list_t l_next = l_args;
    for (; args; args = args->next)
        l_next = l_next->next = list(un_ex(args->data), NULL);
    return tr_ex(tree_call_expr(func, l_args));
}

tr_expr_t tr_op_expr(int op, tr_expr_t left, tr_expr_t right)
{
    tree_expr_t l = un_ex(left);
    tree_expr_t r = un_ex(right);
    return tr_ex(tree_binop_expr(op, l, r));
}

tr_expr_t tr_rel_expr(int op, tr_expr_t left, tr_expr_t right)
{
    tree_stmt_t stmt = tree_cjump_stmt(op, un_ex(left), un_ex(right), NULL, NULL);
    return tr_cx(list(&stmt->u.cjump.t, NULL),
                 list(&stmt->u.cjump.f, NULL),
                 stmt);
}

tr_expr_t tr_string_rel_expr(int op, tr_expr_t left, tr_expr_t right)
{
    tree_expr_t expr = fr_external_call("_CompareString",
                                      list(left, list(right, NULL)));
    tree_stmt_t stmt = tree_cjump_stmt(op, expr, tree_const_expr(0), NULL, NULL);
    return tr_cx(list(&stmt->u.cjump.t, NULL),
                 list(&stmt->u.cjump.f, NULL),
                 stmt);
}

tr_expr_t tr_record_expr(list_t fields, int size)
{
    tree_expr_t addr = tree_tmp_expr(temp());
    tree_expr_t alloc = fr_external_call(
      "_Alloc", list(tree_const_expr(size * FR_WORD_SIZE), NULL));
    list_t p, q = NULL, r = NULL;
    int i;

    for (p = fields, i = 0; p; p = p->next, i++)
    {
        tr_expr_t field = p->data;
        tree_expr_t offset = tree_binop_expr(IR_PLUS, addr,
                                         tree_const_expr(FR_WORD_SIZE * i));
        tree_stmt_t stmt = tree_move_stmt(tree_mem_expr(offset), un_ex(field));
        list_t next = list(stmt, NULL);
        if (q)
        {
            r->next = next;
            r = next;
        }
        else
            q = r = next;
    }
    return tr_ex(
      tree_eseq_expr(
        tree_seq_stmt(list(tree_move_stmt(addr, alloc), q)),
        addr));
}

tr_expr_t tr_array_expr(tr_expr_t size, tr_expr_t init)
{
    return tr_ex(fr_external_call(
        "_InitArray", list(un_ex(size), list(un_ex(init), NULL))));
}

tr_expr_t tr_seq_expr(list_t stmts)
{
    list_t result = NULL, next = NULL;
    list_t p = stmts;
    for (; p; p = p->next)
    {
        tree_stmt_t expr = un_nx(p->data);
        if (result)
            next = next->next = list(expr, NULL);
        else
            result = next = list(expr, NULL);
    }
    return tr_nx(tree_seq_stmt(result));
}

tr_expr_t tr_if_expr(tr_expr_t cond, tr_expr_t then, tr_expr_t else_)
{
    tmp_label_t t = tmp_label();
    tmp_label_t f = tmp_label();
    tmp_label_t done = tmp_label();
    cx_t cx = un_cx(cond);
    tree_expr_t result = tree_tmp_expr(temp());

    fill_patch(cx.trues, t);
    fill_patch(cx.falses, f);
    if (else_)
    {
        return tr_ex(tree_eseq_expr(tree_seq_stmt(vlist(
                7,
                cx.stmt,
                tree_label_stmt(t),
                tree_move_stmt(tree_mem_expr(result), un_ex(then)),
                tree_jump_stmt(tree_name_expr(done), list(done, NULL)),
                tree_label_stmt(f),
                tree_move_stmt(tree_mem_expr(result), un_ex(else_)),
                tree_label_stmt(done))),
            result));
    }
    else
    {
        return tr_nx(tree_seq_stmt(vlist(
              4,
              cx.stmt,
              tree_label_stmt(t),
              un_nx(then),
              tree_label_stmt(f))));
    }
    return NULL;
}

tr_expr_t tr_while_expr(tr_expr_t cond, tr_expr_t body)
{
    tmp_label_t start = tmp_label();
    tmp_label_t loop = tmp_label();
    tmp_label_t done = tmp_label();
    cx_t cx = un_cx(cond);

    fill_patch(cx.trues, loop);
    fill_patch(cx.falses, done);
    return tr_nx(tree_seq_stmt(vlist(
          6,
          tree_label_stmt(start),
          cx.stmt,
          tree_label_stmt(loop),
          un_nx(body),
          tree_jump_stmt(tree_name_expr(start), list(start, NULL)),
          tree_label_stmt(done))));
}

tr_expr_t tr_for_expr(tr_access_t access,
                      tr_expr_t low,
                      tr_expr_t high,
                      tr_expr_t body)
{
    tree_expr_t var = fr_expr(access->access, tree_tmp_expr(fr_fp()));
    tmp_label_t start = tmp_label();
    tmp_label_t loop = tmp_label();
    tmp_label_t done = tmp_label();
    tree_stmt_t cond = tree_cjump_stmt(IR_LE, var, un_ex(high), loop, done);
    return tr_nx(tree_seq_stmt(vlist(
          7,
          tree_move_stmt(var, un_ex(low)),
          tree_label_stmt(start),
          cond,
          tree_label_stmt(loop),
          un_nx(body),
          tree_move_stmt(var, tree_binop_expr(IR_PLUS, var, tree_const_expr(1))),
          tree_label_stmt(done))));
}

tr_expr_t tr_assign_expr(tr_expr_t lhs, tr_expr_t rhs)
{
    return tr_nx(tree_move_stmt(un_ex(lhs), un_ex(rhs)));
}

tr_expr_t tr_simple_var(tr_access_t access, tr_level_t level)
{
    tree_expr_t fp = tree_tmp_expr(fr_fp());

    return tr_ex(fr_expr(access->access, fp));

#if 0
    while (level != access->level)
    {
        fr_access_t fr_access = tr_static_link(level)->access;
        fp = tree_mem_expr(tree_binop_expr(
            IR_PLUS, fp,
            tree_const_expr(fr_offset(fr_access))));
        level = level->parent;
    }
    return tr_ex(tree_mem_expr(tree_binop_expr(
          IR_PLUS, fp,
          tree_const_expr(fr_offset(access->access)))));
#endif
}

tr_expr_t tr_field_var(tr_expr_t record, int index)
{
    return tr_ex(tree_mem_expr(tree_binop_expr(
          IR_PLUS,
          un_ex(record),
          tree_binop_expr(IR_MUL,
                        tree_const_expr(index),
                        tree_const_expr(FR_WORD_SIZE)))));
}

void tr_pp_expr(tr_expr_t expr)
{
    pp_stmts(stdout, list(un_nx(expr), NULL));
}
