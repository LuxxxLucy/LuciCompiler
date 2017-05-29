#ifndef INCLUDE__TABLE_H
#define INCLUDE__TABLE_H

typedef struct table_ *table_ptr  ;

table_ptr  TAB_empty(void);
void TAB_enter(table_ptr  tab, void *key, void *value);
void *TAB_lookup(table_ptr  tab, void *key);
void *TAB_pop(table_ptr  tab);

typedef void (*TAB_dump_func_ptr)(void *key, void *value);
void TAB_dump(table_ptr  tab, TAB_dump_func_ptr  show);

#endif
