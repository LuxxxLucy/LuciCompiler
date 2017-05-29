#ifndef INCLUDE__IR_H
#define INCLUDE__IR_H

#include "temp.h"
#include "utils.h"

typedef struct tree_stmt_ *tree_stmt_ptr  ;
typedef struct tree_expr_ *tree_expr_ptr  ;

typedef enum {
    IR_PLUS, IR_MINUS, IR_MUL, IR_DIV,
    IR_AND, IR_OR, IR_XOR,
    IR_LSHIFT, IR_RSHIFT, IR_ARSHIFT,
} tree_binop_ptr  ;

typedef enum {
    IR_EQ, IR_NE, IR_LT, IR_LE, IR_GT, IR_GE,
    IR_ULT, IR_ULE, IR_UGT, IR_UGE,
} tree_relop_ptr  ;

struct tree_stmt_
{
    enum { IR_SEQ, IR_LABEL, IR_JUMP, IR_CJUMP, IR_MOVE, IR_EXPR } kind;
    union
    {
        list_ptr  seq;
        tmp_label_ptr  label;
        struct { tree_expr_ptr  expr; list_ptr  jumps; } jump;
        struct { tree_relop_ptr  op; tree_expr_ptr  left, right; tmp_label_ptr  t, f; } cjump;
        struct { tree_expr_ptr  dst, src; } move;
        tree_expr_ptr  expr;
    } u;
};
tree_stmt_ptr  tree_seq_stmt(list_ptr  seq);
tree_stmt_ptr  tree_label_stmt(tmp_label_ptr  label);
tree_stmt_ptr  tree_jump_stmt(tree_expr_ptr  expr, list_ptr  jumps);
tree_stmt_ptr  tree_cjump_stmt(tree_relop_ptr  op,
                        tree_expr_ptr  left,
                        tree_expr_ptr  right,
                        tmp_label_ptr  t,
                        tmp_label_ptr  f);
tree_stmt_ptr  tree_move_stmt(tree_expr_ptr  dst, tree_expr_ptr  src);
tree_stmt_ptr  tree_expr_stmt(tree_expr_ptr  expr);

struct tree_expr_
{
    enum { IR_BINOP, IR_MEM, IR_TMP, IR_ESEQ, IR_NAME, IR_CONST, IR_CALL } kind;
    union
    {
        struct { tree_binop_ptr  op; tree_expr_ptr  left, right; } binop;
        tree_expr_ptr  mem;
        temp_ptr  tmp;
        struct { tree_stmt_ptr  stmt; tree_expr_ptr  expr; } eseq;
        tmp_label_ptr  name;
        int const_;
        struct { tree_expr_ptr  func; list_ptr  args; } call;
    } u;
};
tree_expr_ptr  tree_binop_expr(tree_binop_ptr  op, tree_expr_ptr  left, tree_expr_ptr  right);
tree_expr_ptr  tree_mem_expr(tree_expr_ptr  mem);
tree_expr_ptr  tree_tmp_expr(temp_ptr  tmp);
tree_expr_ptr  tree_eseq_expr(tree_stmt_ptr  stmt, tree_expr_ptr  expr);
tree_expr_ptr  tree_name_expr(tmp_label_ptr  name);
tree_expr_ptr  tree_const_expr(int const_);
tree_expr_ptr  tree_call_expr(tree_expr_ptr  func, list_ptr  args);

#endif
