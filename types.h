/*
 * types.h -
 *
 * All types and functions declared in this header file begin with "Ty_"
 * Linked list types end with "..list"
 *
 */

typedef struct Ty_ty_ *Ty_ty;
typedef struct Ty_tyList_ *Ty_tyList;
typedef struct Ty_field_ *Ty_field;
typedef struct Ty_fieldList_ *Ty_fieldList;

typedef enum
{
	TY_RECORD, TY_NIL, TY_INT,
	TY_STRING, TY_ARRAY,
	TY_NAME, TY_VOID
} TyKind;

struct Ty_ty_
{
	TyKind kind;
	union
	{
		Ty_fieldList record;
		Ty_ty array;
		struct { S_symbol name; Ty_ty type;} name;
	} u;
};

struct Ty_tyList_ { Ty_ty head; Ty_tyList tail;};
struct Ty_field_ { S_symbol name; Ty_ty type;};
struct Ty_fieldList_ { Ty_field head; Ty_fieldList tail;};

Ty_ty Ty_Nil(void);
Ty_ty Ty_Int(void);
Ty_ty Ty_String(void);
Ty_ty Ty_Void(void);

Ty_ty Ty_Record( Ty_fieldList fields);
Ty_ty Ty_Array( Ty_ty ty);
Ty_ty Ty_Name( S_symbol sym, Ty_ty ty);

Ty_tyList Ty_TyList( Ty_ty head, Ty_tyList tail);
Ty_field Ty_Field( S_symbol name, Ty_ty ty);
Ty_fieldList Ty_FieldList( Ty_field head, Ty_fieldList tail);
Ty_ty Ty_Actual(Ty_ty type);

void Ty_print( Ty_ty t);
void TyList_print( Ty_tyList list);
