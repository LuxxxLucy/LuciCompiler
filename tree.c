#include "tree.h"

tree_stmt_t tree_seq_stmt(list_t seq)
{
    tree_stmt_t p = checked_malloc(sizeof(*p));
    p->kind = IR_SEQ;
    p->u.seq = seq;
    return p;
}

tree_stmt_t tree_label_stmt(tmp_label_t label)
{
    tree_stmt_t p = checked_malloc(sizeof(*p));
    p->kind = IR_LABEL;
    p->u.label = label;
    return p;
}

tree_stmt_t tree_jump_stmt(tree_expr_t expr, list_t jumps)
{
    tree_stmt_t p = checked_malloc(sizeof(*p));
    p->kind = IR_JUMP;
    p->u.jump.expr = expr;
    p->u.jump.jumps = jumps;
    return p;
}

tree_stmt_t tree_cjump_stmt(tree_relop_t op,
                        tree_expr_t left,
                        tree_expr_t right,
                        tmp_label_t t,
                        tmp_label_t f)
{
    tree_stmt_t p = checked_malloc(sizeof(*p));
    p->kind = IR_CJUMP;
    p->u.cjump.op = op;
    p->u.cjump.left = left;
    p->u.cjump.right = right;
    p->u.cjump.t = t;
    p->u.cjump.f = f;
    return p;
}

tree_stmt_t tree_move_stmt(tree_expr_t dst, tree_expr_t src)
{
    tree_stmt_t p = checked_malloc(sizeof(*p));
    p->kind = IR_MOVE;
    p->u.move.dst = dst;
    p->u.move.src = src;
    return p;
}

tree_stmt_t tree_expr_stmt(tree_expr_t expr)
{
    tree_stmt_t p = checked_malloc(sizeof(*p));
    p->kind = IR_EXPR;
    p->u.expr = expr;
    return p;
}

tree_expr_t tree_binop_expr(tree_binop_t op, tree_expr_t left, tree_expr_t right)
{
    tree_expr_t p = checked_malloc(sizeof(*p));
    p->kind = IR_BINOP;
    p->u.binop.op = op;
    p->u.binop.left = left;
    p->u.binop.right = right;
    return p;
}

tree_expr_t tree_mem_expr(tree_expr_t mem)
{
    tree_expr_t p = checked_malloc(sizeof(*p));
    p->kind = IR_MEM;
    p->u.mem = mem;
    return p;
}

tree_expr_t tree_tmp_expr(temp_t tmp)
{
    tree_expr_t p = checked_malloc(sizeof(*p));
    p->kind = IR_TMP;
    p->u.tmp = tmp;
    return p;
}

tree_expr_t tree_eseq_expr(tree_stmt_t stmt, tree_expr_t expr)
{
    tree_expr_t p = checked_malloc(sizeof(*p));
    p->kind = IR_ESEQ;
    p->u.eseq.stmt = stmt;
    p->u.eseq.expr = expr;
    return p;
}

tree_expr_t tree_name_expr(tmp_label_t name)
{
    tree_expr_t p = checked_malloc(sizeof(*p));
    p->kind = IR_NAME;
    p->u.name = name;
    return p;
}

tree_expr_t tree_const_expr(int const_)
{
    tree_expr_t p = checked_malloc(sizeof(*p));
    p->kind = IR_CONST;
    p->u.const_ = const_;
    return p;
}

tree_expr_t tree_call_expr(tree_expr_t func, list_t args)
{
    tree_expr_t p = checked_malloc(sizeof(*p));
    p->kind = IR_CALL;
    p->u.call.func = func;
    p->u.call.args = args;
    return p;
}
