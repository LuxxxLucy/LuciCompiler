#include <stdarg.h>
#include <stdlib.h>
#include "stdio.h"
#include <string.h>

#include "utils.h"

string_ptr  string(const char *str)
{
    string_ptr  p = checked_malloc(strlen(str) + 1);
    strcpy(p, str);
    return p;
}

void *checked_malloc(int size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

list_ptr  list(void *data, list_ptr  next)
{
    list_ptr  p = checked_malloc(sizeof(*p));
    p->data = data;
    p->next = next;
    return p;
}

list_ptr  vlist(int count, ...)
{
    list_ptr  result = NULL, next = NULL;
    va_list ap;

    va_start(ap, count);
    for (; count > 0; count--)
    {
        void *data = va_arg(ap, void *);
        list_ptr  p = list(data, NULL);
        if (result)
            next = next->next = p;
        else
            result = next = p;
    }
    return result;
}

list_ptr  int_list(int i, list_ptr  next)
{
    list_ptr  p = checked_malloc(sizeof(*p));
    p->i = i;
    p->next = next;
    return p;
}

list_ptr  bool_list(booll b, list_ptr  next)
{
    list_ptr  p = checked_malloc(sizeof(*p));
    p->b = b;
    p->next = next;
    return p;
}

list_ptr  join_list(list_ptr  list1, list_ptr  list2)
{
    list_ptr  p = list1;
    if (!p)
        return list2;
    while (p->next)
        p = p->next;
    p->next = list2;
    return list1;
}

list_ptr  list_append(list_ptr  list1, void *data)
{
    return join_list(list1, list(data, NULL));
}

void print(string_ptr  msg)
{
    fprintf(stdout, "%s",msg );
}

void simple_print(int i,string_ptr  msg)
{
    fprintf(stdout, "%s",msg );
}
