#ifndef INCLUDE__PPAST_H
#define INCLUDE__PPAST_H

#include <stdio.h>

#include "abstract_syntax.h"


void pp_decl(FILE *fp, int d, AST_decl_ptr  decl);
void pp_expr(FILE *fp, int d, AST_expr_ptr  expr);
void pp_type(FILE *fp, int d, AST_type_ptr  type);
void pp_var(FILE *fp, int d, AST_var_ptr  var);

void pp_efield(FILE *fp, int d, AST_efield_ptr  efield);
void pp_field(FILE *fp, int d, AST_field_ptr  field);
void pp_func(FILE *fp, int d, AST_func_ptr  func);
void pp_nametype(FILE *fp, int d, AST_nametype_ptr  nametype);

#endif
