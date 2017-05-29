#ifndef INCLUDE__ERRMSG_H
#define INCLUDE__ERRMSG_H

#include "utils.h"

extern booll em_any_errors;
extern int em_tok_pos;

void em_newline(void);
void em_error(int pos, string_ptr  msg, ...);
/* void em_impossible(string_t, ...); */
void em_reset(string_ptr  file);

#endif
