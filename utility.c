/*
 * utility.c - commonly used utility functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heading.h"
#include "utility.h"

void *checked_malloc(int len)
{
    void *p = malloc(len);
    if (!p) {
    fprintf(stderr,"\nRan out of memory!\n");
    exit(1);
    }
    return p;
}

string String(char *s)
{
    string p = (string)checked_malloc(strlen(s)+1);
    strcpy(p,s);
    return p;
}

U_boolList U_BoolList(bool head, U_boolList tail)
{
    U_boolList list = (U_boolList) checked_malloc(sizeof(*list));
    list->head = head;
    list->tail = tail;
    return list;
}

void print(std::string text)
{
    std::cout<<text<<std::endl;
}

void print(string text)
{
    fprintf(stdout, "%s", text);
}


list_t list(void *data, list_t next)
{
    list_t p = (list_t) checked_malloc(sizeof(*p));
    p->data = data;
    p->next = next;
    return p;
}

list_t vlist(int count, ...)
{
    list_t result = NULL, next = NULL;
    va_list ap;

    va_start(ap, count);
    for (; count > 0; count--)
    {
        void *data = va_arg(ap, void *);
        list_t p = list(data, NULL);
        if (result)
            next = next->next = p;
        else
            result = next = p;
    }
    return result;
}

list_t int_list(int i, list_t next)
{
    list_t p = (list_t) checked_malloc(sizeof(*p));
    p->i = i;
    p->next = next;
    return p;
}

list_t bool_list(bool b, list_t next)
{
    list_t p = (list_t) checked_malloc(sizeof(*p));
    p->b = b;
    p->next = next;
    return p;
}

list_t join_list(list_t list1, list_t list2)
{
    list_t p = list1;
    if (!p)
        return list2;
    while (p->next)
        p = p->next;
    p->next = list2;
    return list1;
}

list_t list_append(list_t list1, void *data)
{
    return join_list(list1, list(data, NULL));
}
