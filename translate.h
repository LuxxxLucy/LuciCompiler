#ifndef INCLUDE__TRANSLATE_H
#define INCLUDE__TRANSLATE_H

#include "frame.h"
#include "tree.h"
#include "temp.h"
#include "utils.h"

typedef struct tr_access_ *tr_access_ptr  ;
typedef struct tr_level_ *tr_level_ptr  ;

tr_level_ptr  tr_outermost(void);
tr_level_ptr  tr_level(tr_level_ptr  parent, tmp_label_ptr  name, list_ptr  formals);
list_ptr  tr_formals(tr_level_ptr  level);
tr_access_ptr  tr_alloc_local(tr_level_ptr  level, booll escape);
frame_ptr  tr_level_frame(tr_level_ptr  level);

typedef struct tr_expr_ *tr_expr_ptr  ;

tr_expr_ptr  tr_num_expr(int num);
tr_expr_ptr  tr_string_expr(string_ptr  str);
tr_expr_ptr  tr_call_expr(tr_level_ptr  level, tmp_label_ptr  label, list_ptr  args);
tr_expr_ptr  tr_op_expr(int op, tr_expr_ptr  left, tr_expr_ptr  right);
tr_expr_ptr  tr_rel_expr(int op, tr_expr_ptr  left, tr_expr_ptr  right);
tr_expr_ptr  tr_string_rel_expr(int op, tr_expr_ptr  left, tr_expr_ptr  right);
tr_expr_ptr  tr_record_expr(list_ptr  fields, int size);
tr_expr_ptr  tr_array_expr(tr_expr_ptr  size, tr_expr_ptr  init);
tr_expr_ptr  tr_seq_expr(list_ptr  stmts);
tr_expr_ptr  tr_if_expr(tr_expr_ptr  cond, tr_expr_ptr  then, tr_expr_ptr  else_);
tr_expr_ptr  tr_while_expr(tr_expr_ptr  cond, tr_expr_ptr  body);
tr_expr_ptr  tr_for_expr(tr_access_ptr  access,
                      tr_expr_ptr  low,
                      tr_expr_ptr  high,
                      tr_expr_ptr  body);
tr_expr_ptr  tr_assign_expr(tr_expr_ptr  lhs, tr_expr_ptr  rhs);

tr_expr_ptr  tr_simple_var(tr_access_ptr  access, tr_level_ptr  level);
tr_expr_ptr  tr_field_var(tr_expr_ptr  record, int index);

void tr_pp_expr(tr_expr_ptr  expr);
typedef struct cx_ cx_ptr  ;
cx_ptr  un_cx(tr_expr_ptr  expr);
tree_stmt_ptr  un_nx(tr_expr_ptr  expr);
tree_expr_ptr  un_ex(tr_expr_ptr  expr);

#endif
