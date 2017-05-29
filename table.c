#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "table.h"
#include "utils.h"

typedef struct binder_ *binder_ptr  ;
struct binder_
{
    void *key;
    void *value;
    binder_ptr  prev;
};

struct table_
{
    list_ptr  table[HT_SIZE];
    binder_ptr  top;
};

static binder_ptr  binder(void *key, void *value, binder_ptr  prev)
{
    binder_ptr  p = checked_malloc(sizeof(*p));
    p->key = key;
    p->value = value;
    p->prev = prev;
    return p;
}

table_ptr  TAB_empty(void)
{
    table_ptr  p = checked_malloc(sizeof(*p));
    int i;

    p->top = NULL;
    for (i = 0; i < HT_SIZE; i++)
        p->table[i] = NULL;
    return p;
}

void TAB_enter(table_ptr  tab, void *key, void *value)
{
    int index;

    assert(tab && key);
    index = ((int) key) % HT_SIZE;
    tab->table[index] = list(binder(key, value, tab->top), tab->table[index]);
    tab->top = tab->table[index]->data;
}

void *TAB_lookup(table_ptr  tab, void *key)
{
    int index;
    list_ptr  p;

    assert(tab && key);
    index = ((int) key) % HT_SIZE;
    for (p = tab->table[index]; p; p = p->next)
        if (((binder_ptr) p->data)->key == key)
            return ((binder_ptr) p->data)->value;
    return NULL;
}

void *TAB_pop(table_ptr  tab)
{
    binder_ptr  bind;
    list_ptr  p;
    int index;

    assert(tab);
    bind = tab->top;
    assert(bind);
    index = ((int) bind->key) % HT_SIZE;
    p = tab->table[index];
    assert(p);
    tab->table[index] = p->next;
    tab->top = bind->prev;
    return bind->key;
}

void TAB_dump(table_ptr  tab, TAB_dump_func_ptr  show)
{
    binder_ptr  bind = tab->top;

    for (; bind; bind = bind->prev)
        show(bind->key, bind->value);
}
