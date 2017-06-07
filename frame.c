#include "frame.h"

#define K 4
const int FR_WORD_SIZE = 4;


static list_ptr  _string_frags = NULL;
static list_ptr  _proc_frags = NULL;
static fr_access_ptr  in_frame(int offset)
{
    fr_access_ptr  p = checked_malloc(sizeof(*p));
    p->kind = FR_IN_FRAME;
    p->u.offset = offset;
    return p;
}

static fr_access_ptr  in_reg(temp_ptr  reg)
{
    fr_access_ptr  p = checked_malloc(sizeof(*p));
    p->kind = FR_IN_REG;
    p->u.reg = reg;
    return p;
}

frame_ptr  frame(tmp_label_ptr  name, list_ptr  formals)
{
    frame_ptr  p = checked_malloc(sizeof(*p));
    list_ptr  formal = formals, q = NULL;
    int i = 0;

    p->name = name;
    p->locals = NULL;
    p->local_count = 0;
    for (; formal; formal = formal->next, i++)
    {
        fr_access_ptr  access;
        if (formal->b || i >= K)
            access = in_frame(i * FR_WORD_SIZE);
        else
            access = in_reg(temp());
        if (q)
        {
            q->next = list(access, NULL);
            q = q->next;
        }
        else
            p->formals = q = list(access, NULL);
    }
    return p;
}

tmp_label_ptr  fr_name(frame_ptr  fr)
{
    return fr->name;
}

list_ptr  fr_formals(frame_ptr  fr)
{
    return fr->formals;
}

fr_access_ptr  fr_alloc_local(frame_ptr  fr, booll escape)
{
    fr_access_ptr  access;

    if (escape)
    {
        fr->local_count++;
        /* -2 for the the return address and frame pointer. */
        access = in_frame(FR_WORD_SIZE * (-2 - fr->local_count));
    }
    else
        access = in_reg(temp());
    if (fr->locals)
    {
        list_ptr  p = fr->locals;
        while (p->next)
            p = p->next;
        p->next = list(access, NULL);
    }
    else
        fr->locals = list(access, NULL);
    return access;
}

int fr_offset(fr_access_ptr  access)
{
    assert(access && access->kind == FR_IN_FRAME);
    return access->u.offset;
}

fr_frag_ptr  fr_string_frag(tmp_label_ptr  label, string_ptr  string)
{
    fr_frag_ptr  p = checked_malloc(sizeof(*p));
    p->kind = FR_STRING_FRAG;
    p->u.string.label = label;
    p->u.string.string = string;
    return p;
}

fr_frag_ptr  fr_proc_frag(tree_stmt_ptr  stmt, frame_ptr  frame)
{
    fr_frag_ptr  p = checked_malloc(sizeof(*p));
    p->kind = FR_PROC_FRAG;
    p->u.proc.stmt = stmt;
    p->u.proc.frame = frame;
    return p;
}


void fr_add_frag(fr_frag_ptr  frag)
{
    switch (frag->kind)
    {
        case FR_STRING_FRAG:
            _string_frags = list_append(_string_frags, frag);
            break;
        case FR_PROC_FRAG:
            _proc_frags = list_append(_proc_frags, frag);
            break;
        default:
            assert(false);
    }
}

temp_ptr  fr_fp(void)
{
    static temp_ptr  _fp = NULL;

    if (!_fp)
        _fp = temp();
    return _fp;
}

temp_ptr  fr_rv(void)
{
    static temp_ptr  _rv = NULL;

    if (!_rv)
    {
        _rv = temp();
    }
    return _rv;
}

tree_expr_ptr  fr_expr(fr_access_ptr  access, tree_expr_ptr  frame_ptr  )
{
    switch (access->kind)
    {
        case FR_IN_FRAME:
            return tree_mem_expr(tree_binop_expr(
                IR_PLUS,
                tree_const_expr(access->u.offset),
                frame_ptr  ));

        case FR_IN_REG:
            return tree_tmp_expr(access->u.reg);
    }

    assert(0);
    return NULL;
}

tree_expr_ptr  fr_external_call(string_ptr  name, list_ptr  args)
{
    return tree_call_expr(tree_name_expr(tmp_named_label(name)), args);
}

void fr_pp_frags(FILE *out)
{
    list_ptr  p;

    fprintf(out, "STRING FRAGMENTS:\n");
    for (p = _string_frags; p; p = p->next)
    {
        fr_frag_ptr  frag = p->data;
        fprintf(out, "    %s: \"%s\"\n",
                tmp_name(frag->u.string.label),
                frag->u.string.string);
    }
    fprintf(out, "\n");

    fprintf(out, "FUNCTION FRAGMENTS:\n");
    for (p = _proc_frags; p; p = p->next)
    {
        fr_frag_ptr  frag = p->data;
        fprintf(out, "    %s:\n", tmp_name(frag->u.proc.frame->name));
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}

void fr_pp_frags_abstract_machine(FILE *out)
{
    list_ptr  p;

    fprintf(out, "    // STRING FRAGMENTS as follows:\n");
    for (p = _string_frags; p; p = p->next)
    {
        fr_frag_ptr  frag = p->data;
        fprintf(out, "    string_ptr %s = (string_ptr) memory_malloc(sizeof(char)*100);\n    strcpy(%s,%s);\n",
                tmp_name(frag->u.string.label)+1,
                tmp_name(frag->u.string.label)+1,
                frag->u.string.string);
    }
    fprintf(out, "\n");

    fprintf(out, "    // FUNCTION FRAGMENTS:\n");
    for (p = _proc_frags; p; p = p->next)
    {
        fr_frag_ptr  frag = p->data;
        fprintf(out, "    %s:\n", tmp_name(frag->u.proc.frame->name));
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
}

tree_stmt_ptr  fr_proc_entry_exit_1(frame_ptr  fr, tree_stmt_ptr  stmt)
{
    return stmt;
}
