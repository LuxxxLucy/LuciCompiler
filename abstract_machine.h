#ifndef INCLUDE__ABSMACHINE_H
#define INCLUDE__ABSMACHINE_H

#include <stdio.h>
#include "frame.h"
#include "tree.h"
#include "temp.h"
#include "translate.h"
#include "utils.h"

void make_stmts(string_ptr filename,tr_expr_ptr expr);

#endif
