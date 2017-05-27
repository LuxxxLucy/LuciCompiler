/*
 * env.c and env.h
 *
 * implementing the enviroment
 */

#include "frame.h"
#include "types.h"
#include "translate.h"
typedef TAB_table S_table;

typedef struct E_enventry_ *E_enventry;

typedef enum { E_varEntry, E_funEntry} envKind;

struct E_enventry_ {
    envKind kind;
    union
    {
        struct { Ty_ty type;tr_access_t access;} var;
        struct { Ty_tyList formals; Ty_ty result;tr_level_t level;Temp_label label; } fun;
    } u;
};

E_enventry E_VarEntry(Ty_ty ty);
E_enventry E_FunEntry(Ty_tyList formals, Ty_ty result);

S_table E_base_tenv(void); /*Ty_ty environment*/
S_table E_base_venv(void); /*E-enventry environment*/
