#ifndef INCLUDE__FRAME_H
#define INCLUDE__FRAME_H

#include "tree.h"
#include "temp.h"
#include "utils.h"

typedef struct frame_ *frame_ptr  ;
typedef struct fr_access_ *fr_access_ptr  ;

frame_ptr  frame(tmp_label_ptr  name, list_ptr  formals);
tmp_label_ptr  fr_name(frame_ptr  fr);
list_ptr  fr_formals(frame_ptr  fr);
fr_access_ptr  fr_alloc_local(frame_ptr  fr, booll escape);
int fr_offset(fr_access_ptr  access);

typedef struct fr_frag_ *fr_frag_ptr  ;
struct fr_frag_
{
    enum { FR_STRING_FRAG, FR_PROC_FRAG, } kind;
    union
    {
        struct { tmp_label_ptr  label; string_ptr  string; } string;
        struct { tree_stmt_ptr  stmt; frame_ptr  frame; } proc;
    } u;
};
fr_frag_ptr  fr_string_frag(tmp_label_ptr  label, string_ptr  string);
fr_frag_ptr  fr_proc_frag(tree_stmt_ptr  stmt, frame_ptr  frame);
void fr_add_frag(fr_frag_ptr  frag);

extern const int FR_WORD_SIZE;
temp_ptr  fr_fp(void);
temp_ptr  fr_rv(void);

tree_expr_ptr  fr_expr(fr_access_ptr  access, tree_expr_ptr  frame_ptr  );
tree_expr_ptr  fr_external_call(string_ptr  name, list_ptr  args);

tree_stmt_ptr  fr_proc_entry_exit_1(frame_ptr  fr, tree_stmt_ptr  stmt);

void fr_pp_frags(FILE *out);

#endif
