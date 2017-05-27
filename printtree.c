/*
 * printtree.c - functions to print out intermediate representation (IR) trees.
 *
 */
#include <stdio.h>
#include "utility.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "printtree.h"

/* local function prototype */
void pr_tree_exp(FILE *out, T_exp exp, int d);

static void indent(FILE *out, int d) {
 int i;
 for (i = 0; i <= d; i++) fprintf(out, " ");
}

static char bin_oper[][12] = {
   "PLUS", "MINUS", "TIMES", "DIVIDE",
   "AND", "OR", "LSHIFT", "RSHIFT", "ARSHIFT", "XOR"};

static char rel_oper[][12] = {
  "EQ", "NE", "LT", "GT", "LE", "GE", "ULT", "ULE", "UGT", "UGE"};

void pr_stm(FILE *out, T_stm stm, int d)
{
  switch (stm->kind) {
  case T_SEQ:
        list_t p;
        indent(out, d);
        fprintf(out, "SEQ(\n");
        for (p = stm->u.seq; p; p = p->next)
        {
            pr_stm(out,(T_stm)p->data,d+1);
        }
        indent(out, d);
        fprintf(out, ")\n");
        break;
  case T_LABEL:
    indent(out,d); fprintf(out, "LABEL %s", S_name(stm->u.label));
    break;
  case T_JUMP:
    indent(out,d); fprintf(out, "JUMP(\n"); pr_tree_exp(out, stm->u.jump.exp,d+1);
    fprintf(out, ")");
    break;
  case T_CJUMP:
    indent(out,d); fprintf(out, "CJUMP(%s,\n", rel_oper[stm->u.cjump.op]);
    pr_tree_exp(out, stm->u.cjump.left,d+1); fprintf(out, ",\n");
    pr_tree_exp(out, stm->u.cjump.right,d+1); fprintf(out, ",\n");
    indent(out,d+1); fprintf(out, "%s,", S_name(stm->u.cjump.truee));
    fprintf(out, "%s", S_name(stm->u.cjump.falsee)); fprintf(out, ")");
    break;
  case T_MOVE:
    indent(out,d); fprintf(out, "MOVE(\n"); pr_tree_exp(out, stm->u.move.dst,d+1);
    fprintf(out, ",\n");
    pr_tree_exp(out, stm->u.move.src,d+1); fprintf(out, ")");
    break;
  case T_EXP:
    indent(out,d); fprintf(out, "EXP(\n"); pr_tree_exp(out, stm->u.exp,d+1);
    fprintf(out, ")");
    break;
  }
}

void pr_tree_exp(FILE *out, T_exp exp, int d)
{
  switch (exp->kind) {
  case T_BINOP:
    indent(out,d); fprintf(out, "BINOP(%s,\n", bin_oper[exp->u.binop.op]);
    pr_tree_exp(out, exp->u.binop.left,d+1); fprintf(out, ",\n");
    pr_tree_exp(out, exp->u.binop.right,d+1); fprintf(out, ")");
    break;
  case T_MEM:
    indent(out,d); fprintf(out, "MEM");
    fprintf(out, "(\n"); pr_tree_exp(out, exp->u.mem,d+1); fprintf(out, ")");
    break;
  case T_TEMP:
    indent(out,d); fprintf(out, "TEMP t%s",
			   Temp_look(Temp_name(), exp->u.tmp));
    break;
  case T_ESEQ:
    indent(out,d); fprintf(out, "ESEQ(\n"); pr_stm(out, exp->u.eseq.stm,d+1);
    fprintf(out, ",\n");
    pr_tree_exp(out, exp->u.eseq.exp,d+1); fprintf(out, ")");
    break;
  case T_NAME:
    indent(out,d); fprintf(out, "NAME %s", S_name(exp->u.name));
    break;
  case T_CONST:
    indent(out,d); fprintf(out, "CONST %d", exp->u.const_);
    break;
  case T_CALL:
    {
    list_t p;

    indent(out, d);
    fprintf(out, "CALL(\n");
    pr_tree_exp(out, exp->u.call.fun,d+1);
    for (p = exp->u.call.args; p; p = p->next)
    {
        pr_tree_exp(out,(T_exp) p->data,d+1);
    }
    indent(out, d);
    fprintf(out, ")\n");
    break;

   }
  } /* end of switch */
}

void printStmList (FILE *out, T_stmList stmList)
{
  for (; stmList; stmList=stmList->tail) {
    pr_stm(out, stmList->head,0); fprintf(out, "\n");
  }
}
