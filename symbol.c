#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "symbol.h"

static symbol_ptr  _symbols[HT_SIZE];

static symbol_ptr  mk_symbol(string_ptr  name, symbol_ptr  next)
{
    symbol_ptr  sym = checked_malloc(sizeof(*sym));
    sym->data = name;
    sym->next = next;
    return sym;
}

static unsigned int hash(string_ptr  str)
{
    unsigned int h = 0;
    char *p;

    for (p = str; *p; p++)
        h = 65599 * h + *p;
    return h;
}

symbol_ptr  symbol(string_ptr  name)
{
    int index = hash(name) % HT_SIZE;
    symbol_ptr  p;

    for (p = _symbols[index]; p; p = p->next)
        if (strcmp((string_ptr) p->data, name) == 0)
            return p;
    p = mk_symbol(name, _symbols[index]);
    _symbols[index] = p;
    return p;
}

string_ptr  sym_name(symbol_ptr  sym)
{
    return (string_ptr) sym->data;
}

table_ptr  sym_empty(void)
{
    return TAB_empty();
}

void sym_enter(table_ptr  tab, symbol_ptr  sym, void *value)
{
    TAB_enter(tab, sym, value);
}

void *sym_lookup(table_ptr  tab, symbol_ptr  sym)
{
    return TAB_lookup(tab, sym);
}

static symbol_ptr  _mark_sym = NULL;

void sym_begin_scope(table_ptr  tab)
{
    if (!_mark_sym)
    {
        _mark_sym = checked_malloc(sizeof(*_mark_sym));
        _mark_sym->data = "<mark>";
        _mark_sym->next = NULL;
    }
    sym_enter(tab, _mark_sym, NULL);
}

void sym_end_scope(table_ptr  tab)
{
    symbol_ptr  sym;

    do
        sym = TAB_pop(tab);
    while (sym != _mark_sym);
}
