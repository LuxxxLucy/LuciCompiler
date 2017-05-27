/*
 * env.c and env.h
 *
 * implementing the enviroment
 */

#include "table.h"
typedef TAB_table S_table;

typedef struct E_enventry_ *E_enventry

typedef enum { E_varEntry, E_funEntry} envKind;

Struct E_enventry_ {
    envKind kind;
    union
    {
        struct { Ty_ty ty;} var;
        struct { Ty_tyList formals; Ty_ty result;} fun;
    } u;
}

E_enventry E_VarEntry(Ty_ty ty);
E_enventry E_FunEntry(Ty_tyList formals, Ty_ty result);

S_table E_base_tenv(void); /*Ty_ty environment*/
S_table E_base_venv(void); /*E-enventry environment*/