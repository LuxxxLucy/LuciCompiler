#include <stdarg.h>
#include <stdlib.h>
#include "stdio.h"
#include <string.h>

#include "lucy_utility.h"

void *memory_malloc(int size)
{
    void *p = malloc(size);
    assert(p);
    return p;
}

string_ptr  string(const char *str)
{
    string_ptr  p = memory_malloc(strlen(str) + 1);
    strcpy(p, str);
    return p;
}

void simple_print_str(int i,string_ptr  msg)
{
    fprintf(stdout, "%s",msg );
}

void simple_print_int(int i,Abstract_Register  temp)
{
    fprintf(stdout, "%d",temp);
}
