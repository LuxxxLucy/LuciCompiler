#include "abstract_machine.h"
#include <assert.h>
#include "tree.h"
#include "frame.h"
#include "translate.h"
#include "temp.h"
#include "utils.h"


// extern list_ptr  _string_frags = NULL;
// extern list_ptr  _proc_frags = NULL;

static int temps[100];

static void pp_expr(FILE *out, int d, tree_expr_ptr  expr);
static string_ptr func_name(string_ptr func);

static void indent(FILE *out, int d)
{
    int i;

    for (i = 0; i <= d; ++i)
    {
        fprintf(out, "    ");
    }
}

static char const* binops[] = {
    "+",
    "-",
    "*",
    "/",
    "&",
    "|",
    "^",
    "<<",
    ">>",
    "ARSHIFT",
};

static char const* relops[] = {
    "==",
    "!=",
    ">",
    ">=",
    ">",
    ">=",
    "ULT",
    "ULE",
    "UGT",
    "UGE",
};

static void pp_stmt(FILE *out, int d, tree_stmt_ptr  stmt)
{
    switch (stmt->kind)
    {
        case IR_SEQ:
        {
            list_ptr  p;
            for (p = stmt->u.seq; p; p = p->next)
            {
                indent(out,0);
                pp_stmt(out, d + 1, p->data);
                fprintf(out, ";\n");
            }
            break;
        }

        case IR_LABEL:
            fprintf(out, "LABEL %s\n", tmp_name(stmt->u.label));
            break;

        case IR_JUMP:
            fprintf(out, "JUMP(\n");
            pp_expr(out, d + 1, stmt->u.jump.expr);
            fprintf(out, ")\n");
            break;

        case IR_CJUMP:
            fprintf(out, "(");
            pp_expr(out, d + 1, stmt->u.cjump.left);
            fprintf(out, "%s", relops[stmt->u.cjump.op]);
            pp_expr(out, d + 1, stmt->u.cjump.right);
            fprintf(out, ")?\n");
            fprintf(out, "(%s) : (%s)\n",
                    tmp_name(stmt->u.cjump.t),
                    tmp_name(stmt->u.cjump.f));
            break;

        case IR_MOVE:
            pp_expr(out, d + 1, stmt->u.move.dst);
            fprintf(out, "=");
            pp_expr(out, d + 1, stmt->u.move.src);
            break;

        case IR_EXPR:
            pp_expr(out, d + 1, stmt->u.expr);
            break;

        default:
            assert(false);
    }
}

void pp_expr(FILE *out, int d, tree_expr_ptr  expr)
{
    string_ptr name=checked_malloc(sizeof(*name)*100);
    switch (expr->kind)
    {
        case IR_BINOP:
            pp_expr(out, d + 1, expr->u.binop.left);
            fprintf(out, " %s ", binops[expr->u.binop.op]);
            pp_expr(out, d + 1, expr->u.binop.right);
            break;

        case IR_MEM:
            pp_expr(out, d + 1, expr->u.mem);
            break;
        case IR_TMP:
            strcpy(name,func_name(tmp_lookup(tmp_map(),expr->u.tmp)));
            fprintf(out, "temp[%s]", name);
            // fprintf(out, "Abstract_Register t%s", tmp_lookup(tmp_map(), expr->u.tmp));
            break;

        case IR_ESEQ:
            pp_stmt(out, d + 1, expr->u.eseq.stmt);
            pp_expr(out, d + 1, expr->u.eseq.expr);
            break;

        case IR_NAME:
            strcpy(name,func_name(tmp_name(expr->u.name)+1));
            fprintf(out, "%s",name );
            break;

        case IR_CONST:
            fprintf(out, "%d", expr->u.const_);
            break;

        case IR_CALL:
        {
            list_ptr  p;
            pp_expr(out, d + 1, expr->u.call.func);
            fprintf(out, "(");
            for (p=expr->u.call.args; p; p = p->next)
            {
                pp_expr(out, d + 1, p->data);
                if(p->next!=NULL)
                    fprintf(out, ",");
            }
            fprintf(out, ")");
            break;
        }

        default:
            assert(false);
    }
}

string_ptr func_name(string_ptr func)
{
    if(strcmp(func,"L3")==0)
    {
        return "simple_print_str";
    }
    else if(strcmp(func,"L4")==0)
    {
        return "simple_print_int";
    }
    else
    {
        return func;
    }
}

static void print_base_env(FILE *out)
{
    fprintf(out, "#include \"lucy_utility.h\"\n");
    // fprintf(out, "#include <iostream>\n");
    // fprintf(out, "#include <string>\n");
    fprintf(out, "int main(){\n");
    fprintf(out, "Abstract_Register temp[Abstract_Register_Size];\n");
}

void make_stmts(string_ptr filename,tr_expr_ptr  expr)
{
        list_ptr stmts=list(un_nx(expr),NULL);
        FILE *fp;
        if((fp=fopen(filename,"w+"))==NULL){
            printf("\nCannot open file strike any key exit!");
            return;
        }
        print("translating to abstract machine code\n");
        print_base_env(fp);
        fr_pp_frags_abstract_machine(fp);
        stmts=stmts->data;
        // pp_stmt(fp, 0, stmts->data);
        for (stmts = stmts->next; ((tree_expr_ptr)stmts->data)->kind!=IR_SEQ; stmts = stmts->next)
        {
            pp_stmt(fp, 0, stmts->data);
            fprintf(fp,";\n");
        }
        for (; stmts; stmts = stmts->next)
        {
            pp_stmt(fp, 0, stmts->data);
        }

        fprintf(fp, "}\n");
        fclose(fp);

        string_ptr cmd= checked_malloc(sizeof(*cmd)*100);
        strcpy (cmd,"gcc lucy_utility.c ");
        strcat (cmd,filename);
        strcat (cmd," -o out\n");
        print(cmd);
        system(cmd);
}
