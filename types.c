/*
 * types.c -
 *
 * All types and functions declared in this header file begin with "Ty_"
 * Linked list types end with "..list"
 */
#include <assert.h>
#include <stdio.h>
#include "utility.h"
#include "symbol.h"
#include "types.h"

static struct Ty_ty_ _ty_nil = { TY_NIL };
Ty_ty ty_nil(void)
{
 return &_ty_nil;
}

static struct Ty_ty_ _ty_int = { TY_INT };
Ty_ty Ty_Int(void)
{
 return &_ty_int;
}

static struct Ty_ty_ _ty_string = { TY_STRING };
Ty_ty Ty_String(void)
{
 return &_ty_string;
}

static struct Ty_ty_ _ty_void = { TY_VOID };
Ty_ty Ty_Void(void)
{
 return &_ty_void;
}

Ty_ty Ty_Record(Ty_fieldList fields)
{
 Ty_ty p = (Ty_ty) checked_malloc(sizeof(*p));
 p->kind = TY_RECORD;
 p->u.record = fields;
 return p;
}

Ty_ty Ty_Array(Ty_ty type)
{
 Ty_ty p = (Ty_ty) checked_malloc(sizeof(*p));
 p->kind = TY_ARRAY;
 p->u.array = type;
 return p;
}

Ty_ty Ty_Name(S_symbol name, Ty_ty type)
{
 Ty_ty p = (Ty_ty) checked_malloc(sizeof(*p));
 p->kind = TY_NAME;
 p->u.name.name = name;
 p->u.name.type = type;
 return p;
}

Ty_field Ty_Field(S_symbol name, Ty_ty type)
{
 Ty_field p = (Ty_field) checked_malloc(sizeof(*p));
 p->name = name;
 p->type = type;
 return p;
}

Ty_ty Ty_Actual(Ty_ty type)
{
 Ty_ty origin = type;
 int counter = 0;

 assert(type);
 while (type->kind == TY_NAME)
 {
     type = type->u.name.type;
     if (++counter > 4096)
         return origin;
 }
 return type;
}

bool ty_match(Ty_ty type1, Ty_ty type2)
{
 type1 = Ty_Actual(type1);
 type2 = Ty_Actual(type2);
 if (type1 == type2)
     return true;
 if (type1->kind == TY_RECORD && type2->kind == TY_NIL)
     return true;
 if (type1->kind == TY_NIL && type2->kind == TY_RECORD)
     return true;
 return false;
}

static char _Ty_ty_trs[][12] = {
 "ty_record", "ty_nil", "ty_int", "ty_string",
 "ty_array", "ty_name", "ty_void",
};

void Ty_print(Ty_ty type)
{
 if (type == NULL)
     printf("null");
 else
 {
     printf("%s", _Ty_ty_trs[type->kind]);
     if (type->kind == TY_NAME)
         printf(", %s", S_name(type->u.name.name));
 }
}

void TyList_print(Ty_tyList types)
{
 if (types == NULL)
     printf("null");
 else
 {
     printf("ty_list(");
     Ty_print(types->head);
     printf(", ");
     TyList_print(types->tail);
     printf(")");
 }
}
