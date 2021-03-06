#include <stdlib.h>

#include "env.h"

E_entry_ptr  E_VarEntry(tr_access_ptr  access, type_ptr  type, booll for_)
{
    E_entry_ptr  p = checked_malloc(sizeof(*p));
    p->kind = ENV_VAR_ENTRY;
    p->u.var.access = access;
    p->u.var.type = type;
    p->u.var.for_ = for_;
    return p;
}

E_entry_ptr  E_FunEntry(tr_level_ptr  level,
                           tmp_label_ptr  label,
                           list_ptr  formals,
                           type_ptr  result)
{
    E_entry_ptr  p = checked_malloc(sizeof(*p));
    p->kind = ENV_FUNC_ENTRY;
    p->u.func.level = level;
    p->u.func.label = label;
    p->u.func.formals = formals;
    p->u.func.result = result;
    return p;
}

table_ptr  E_base_tenv(void)
{
    table_ptr  tab = sym_empty();
    sym_enter(tab, symbol("INT"), ty_int());
    sym_enter(tab, symbol("STRING"), ty_string());
    return tab;
}

table_ptr  E_base_venv(void)
{
    table_ptr  tab = sym_empty();
    sym_enter(tab, symbol("getchar"),
              E_FunEntry(tr_outermost(), tmp_label(), NULL, ty_string()));
    sym_enter(tab, symbol("ord"),
              E_FunEntry(tr_outermost(),
                             tmp_label(),
                             list(ty_string(), NULL),
                             ty_int()));
    sym_enter(tab, symbol("print"),
              E_FunEntry(tr_outermost(),
                             tmp_label(),
                             list(ty_string(), NULL),
                             ty_void()));
    sym_enter(tab, symbol("printint"),
              E_FunEntry(tr_outermost(),
                             tmp_label(),
                             list(ty_int(), NULL),
                             ty_void()));
    sym_enter(tab, symbol("chr"),
              E_FunEntry(tr_outermost(),
                             tmp_label(),
                             list(ty_int(), NULL),
                             ty_string()));
    return tab;
}
