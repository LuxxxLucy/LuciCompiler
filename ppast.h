#ifndef INCLUDE__PPAST_H
#define INCLUDE__PPAST_H

#include <stdio.h>

#include "abstract_syntax.h"


void pp_decl(FILE *fp, int d, AST_decl_t decl);
void pp_expr(FILE *fp, int d, AST_expr_t expr);
void pp_type(FILE *fp, int d, AST_type_t type);
void pp_var(FILE *fp, int d, AST_var_t var);

void pp_efield(FILE *fp, int d, AST_efield_t efield);
void pp_field(FILE *fp, int d, AST_field_t field);
void pp_func(FILE *fp, int d, AST_func_t func);
void pp_nametype(FILE *fp, int d, AST_nametype_t nametype);

#endif
