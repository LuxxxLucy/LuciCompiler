#ifndef INCLUDE__PARSER_WRAP_H
#define INCLUDE__PARSER_WRAP_H

#include "abstract_syntax.h"
#include "parser.h"
#include "symbol.h"
#include "utils.h"

extern int yydebug;

AST_expr_ptr  parse(string_ptr  filename);

#endif
