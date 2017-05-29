#ifndef INCLUDE__ENV_H
#define INCLUDE__ENV_H

#include "symbol.h"
#include "temp.h"
#include "translate.h"
#include "types.h"

typedef struct E_entry_ *E_entry_ptr  ;
struct E_entry_
{
    enum { ENV_VAR_ENTRY, ENV_FUNC_ENTRY } kind;
    union
    {
        struct
        {
            tr_access_ptr  access;
            type_ptr  type;
            booll for_;
        } var;

        struct
        {
            tr_level_ptr  level;
            tmp_label_ptr  label;
            list_ptr  formals;
            type_ptr  result;
        } func;
    } u;
};
E_entry_ptr  E_VarEntry(tr_access_ptr  access, type_ptr  type, booll for_);
E_entry_ptr  E_FunEntry(tr_level_ptr  level,
                           tmp_label_ptr  label,
                           list_ptr  formals,
                           type_ptr  result);

table_ptr  E_base_tenv(void);
table_ptr  E_base_venv(void);

#endif
