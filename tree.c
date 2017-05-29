#include "tree.h"

tree_stmt_ptr  tree_seq_stmt(list_ptr  seq)
{
    tree_stmt_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_SEQ;
    p->u.seq = seq;
    return p;
}

tree_stmt_ptr  tree_label_stmt(tmp_label_ptr  label)
{
    tree_stmt_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_LABEL;
    p->u.label = label;
    return p;
}

tree_stmt_ptr  tree_jump_stmt(tree_expr_ptr  expr, list_ptr  jumps)
{
    tree_stmt_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_JUMP;
    p->u.jump.expr = expr;
    p->u.jump.jumps = jumps;
    return p;
}

tree_stmt_ptr  tree_cjump_stmt(tree_relop_ptr  op,
                        tree_expr_ptr  left,
                        tree_expr_ptr  right,
                        tmp_label_ptr  t,
                        tmp_label_ptr  f)
{
    tree_stmt_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_CJUMP;
    p->u.cjump.op = op;
    p->u.cjump.left = left;
    p->u.cjump.right = right;
    p->u.cjump.t = t;
    p->u.cjump.f = f;
    return p;
}

tree_stmt_ptr  tree_move_stmt(tree_expr_ptr  dst, tree_expr_ptr  src)
{
    tree_stmt_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_MOVE;
    p->u.move.dst = dst;
    p->u.move.src = src;
    return p;
}

tree_stmt_ptr  tree_expr_stmt(tree_expr_ptr  expr)
{
    tree_stmt_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_EXPR;
    p->u.expr = expr;
    return p;
}

tree_expr_ptr  tree_binop_expr(tree_binop_ptr  op, tree_expr_ptr  left, tree_expr_ptr  right)
{
    tree_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_BINOP;
    p->u.binop.op = op;
    p->u.binop.left = left;
    p->u.binop.right = right;
    return p;
}

tree_expr_ptr  tree_mem_expr(tree_expr_ptr  mem)
{
    tree_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_MEM;
    p->u.mem = mem;
    return p;
}

tree_expr_ptr  tree_tmp_expr(temp_ptr  tmp)
{
    tree_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_TMP;
    p->u.tmp = tmp;
    return p;
}

tree_expr_ptr  tree_eseq_expr(tree_stmt_ptr  stmt, tree_expr_ptr  expr)
{
    tree_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_ESEQ;
    p->u.eseq.stmt = stmt;
    p->u.eseq.expr = expr;
    return p;
}

tree_expr_ptr  tree_name_expr(tmp_label_ptr  name)
{
    tree_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_NAME;
    p->u.name = name;
    return p;
}

tree_expr_ptr  tree_const_expr(int const_)
{
    tree_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_CONST;
    p->u.const_ = const_;
    return p;
}

tree_expr_ptr  tree_call_expr(tree_expr_ptr  func, list_ptr  args)
{
    tree_expr_ptr  p = checked_malloc(sizeof(*p));
    p->kind = IR_CALL;
    p->u.call.func = func;
    p->u.call.args = args;
    return p;
}
