#include <stdio.h>

// #include "utility.h"
// #include "symbol.h"
// #include "table.h"
// #include "types.h"

#include "env.h"
#include "abstract_syntax.h"
#include "error_message.h"
#include "tokens.h"
#include "temp.h"
#include "tree.h" /* needed by frame.h */
#include "frame.h"
#include "printtree.h"
#include "translate.h"
#include "semant.h"


static TAB_table _tenv,_venv;

struct expTy_ { Tr_exp exp;Ty_ty ty;};
typedef struct expTy_ expTy;

expTy ExpTy(Tr_exp exp,Ty_ty ty)
{
    expTy e;
    e.exp=exp;e.ty=ty;
    return e;
}



T_exp translateExp(A_exp abs_tree)
{
    return T_Const(1);
}

T_exp translate(A_exp root)
{
    print("translating the abstract tree");
    expTy result;

    _venv = E_base_venv();
    _tenv = E_base_tenv();
    //result = trans_expr(tr_outermost(), root);

    //fr_pp_frags(stdout);
    fprintf(stdout, "MAIN PROGRAM:\n");
    //tr_pp_expr(result.expr);

    return translateExp(root);
}
