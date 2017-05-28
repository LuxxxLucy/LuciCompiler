#ifndef INCLUDE__IR_H
#define INCLUDE__IR_H

#include "temp.h"
#include "utils.h"

typedef struct tree_stmt_s *tree_stmt_t;
typedef struct tree_expr_s *tree_expr_t;

typedef enum {
    IR_PLUS, IR_MINUS, IR_MUL, IR_DIV,
    IR_AND, IR_OR, IR_XOR,
    IR_LSHIFT, IR_RSHIFT, IR_ARSHIFT,
} tree_binop_t;

typedef enum {
    IR_EQ, IR_NE, IR_LT, IR_LE, IR_GT, IR_GE,
    IR_ULT, IR_ULE, IR_UGT, IR_UGE,
} tree_relop_t;

struct tree_stmt_s
{
    enum { IR_SEQ, IR_LABEL, IR_JUMP, IR_CJUMP, IR_MOVE, IR_EXPR } kind;
    union
    {
        list_t seq;
        tmp_label_t label;
        struct { tree_expr_t expr; list_t jumps; } jump;
        struct { tree_relop_t op; tree_expr_t left, right; tmp_label_t t, f; } cjump;
        struct { tree_expr_t dst, src; } move;
        tree_expr_t expr;
    } u;
};
tree_stmt_t tree_seq_stmt(list_t seq);
tree_stmt_t tree_label_stmt(tmp_label_t label);
tree_stmt_t tree_jump_stmt(tree_expr_t expr, list_t jumps);
tree_stmt_t tree_cjump_stmt(tree_relop_t op,
                        tree_expr_t left,
                        tree_expr_t right,
                        tmp_label_t t,
                        tmp_label_t f);
tree_stmt_t tree_move_stmt(tree_expr_t dst, tree_expr_t src);
tree_stmt_t tree_expr_stmt(tree_expr_t expr);

struct tree_expr_s
{
    enum { IR_BINOP, IR_MEM, IR_TMP, IR_ESEQ, IR_NAME, IR_CONST, IR_CALL } kind;
    union
    {
        struct { tree_binop_t op; tree_expr_t left, right; } binop;
        tree_expr_t mem;
        temp_t tmp;
        struct { tree_stmt_t stmt; tree_expr_t expr; } eseq;
        tmp_label_t name;
        int const_;
        struct { tree_expr_t func; list_t args; } call;
    } u;
};
tree_expr_t tree_binop_expr(tree_binop_t op, tree_expr_t left, tree_expr_t right);
tree_expr_t tree_mem_expr(tree_expr_t mem);
tree_expr_t tree_tmp_expr(temp_t tmp);
tree_expr_t tree_eseq_expr(tree_stmt_t stmt, tree_expr_t expr);
tree_expr_t tree_name_expr(tmp_label_t name);
tree_expr_t tree_const_expr(int const_);
tree_expr_t tree_call_expr(tree_expr_t func, list_t args);

#endif
