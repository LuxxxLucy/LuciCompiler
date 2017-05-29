#ifndef INCLUDE__TYPES_H
#define INCLUDE__TYPES_H

#include "symbol.h"

typedef struct type_ *type_ptr  ;
typedef struct ty_field_ *ty_field_ptr  ;

struct type_
{
    enum { TY_RECORD, TY_NIL, TY_INT, TY_STRING, TY_ARRAY, TY_NAME, TY_VOID } kind;
    union
    {
        list_ptr  record;
        type_ptr  array;
        struct { symbol_ptr  name; type_ptr  type; } name;
    } u;
};
type_ptr  ty_nil(void);
type_ptr  ty_int(void);
type_ptr  ty_string(void);
type_ptr  ty_void(void);
type_ptr  ty_record(list_ptr  fields);
type_ptr  ty_array(type_ptr  type);
type_ptr  ty_name(symbol_ptr  name, type_ptr  type);

struct ty_field_
{
    symbol_ptr  name;
    type_ptr  type;
};
ty_field_ptr  ty_field(symbol_ptr  name, type_ptr  type);

type_ptr  ty_actual(type_ptr  type);
booll ty_match(type_ptr  type1, type_ptr  type2);

void ty_print(type_ptr  type);
void ty_print_types(list_ptr  types);

#endif
