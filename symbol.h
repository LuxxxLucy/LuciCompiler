#ifndef INCLUDE__SYMBOL_H
#define INCLUDE__SYMBOL_H

#include "table.h"
#include "utils.h"

typedef list_ptr  symbol_ptr  ;

symbol_ptr  symbol(string_ptr  name);
string_ptr  sym_name(symbol_ptr  sym);
table_ptr  sym_empty(void);
void sym_enter(table_ptr  tab, symbol_ptr  sym, void *value);
void *sym_lookup(table_ptr  tab, symbol_ptr  sym);
void sym_begin_scope(table_ptr  tab);
void sym_end_scope(table_ptr  tab);

#endif
