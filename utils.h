#ifndef INCLUDE__UTILS_H
#define INCLUDE__UTILS_H

#include <assert.h>

typedef char *string_ptr  ;
string_ptr  string(const char *);

typedef char booll;
#define true 1
#define false 0

#define HT_SIZE 773

void *checked_malloc(int);

typedef struct list_ *list_ptr  ;
struct list_
{
    union {
        int i;
        booll b;
        void *data;
    };
    struct list_ *next;
};
list_ptr  list(void *data, list_ptr  next);
list_ptr  vlist(int count, ...);
list_ptr  int_list(int i, list_ptr  next);
list_ptr  bool_list(booll b, list_ptr  next);

list_ptr  join_list(list_ptr  list1, list_ptr  list2);
list_ptr  list_append(list_ptr  list1, void *data);

void print(string_ptr  msg);

#endif
