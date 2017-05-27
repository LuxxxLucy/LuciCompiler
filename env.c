#include <stdlib.h>

#include "env.h"

E_enventry E_VarEntry(Ty_ty type)
{
    E_enventry p = (E_enventry) checked_malloc(sizeof(*p));
    p->kind = E_varEntry;
    p->u.var.type = type;
    return p;
}

E_enventry E_FunEntry( Ty_tyList formals,
                           Ty_ty result)
{
    E_enventry p = (E_enventry) checked_malloc(sizeof(*p));
    p->kind = E_funEntry;
    p->u.fun.formals = formals;
    p->u.fun.result = result;
    return p;
}

TAB_table E_base_tenv(void)
{
    TAB_table tab = TAB_empty();
    TAB_enter(tab, S_Symbol("INT"), Ty_Int());
    TAB_enter(tab, S_Symbol("STRING"), Ty_String());
    return tab;
}

TAB_table E_base_venv(void)
{
    TAB_table tab = TAB_empty();
    TAB_enter(tab, S_Symbol("getchar"),
              E_FunEntry(NULL, Ty_String()));
    //sym_enter(tab, symbol("ord"), env_func_entry(list(Ty_String(), NULL), ty_int()));
    TAB_enter(tab, S_Symbol("print"),
              E_FunEntry(NULL,
                             Ty_Void()));
     return tab;
}
