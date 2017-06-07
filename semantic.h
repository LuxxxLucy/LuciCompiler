#ifndef INCLUDE__SEMANTIC_H
#define INCLUDE__SEMANTIC_H

#include "abstract_syntax.h"

struct expr_type_
{
    tr_expr_ptr  expr;
    type_ptr  type;
};

typedef struct expr_type_ expr_type_ptr;

expr_type_ptr sem_trans_prog(AST_expr_ptr  prog);

#endif
