#include <assert.h>
#include "heading.h"

typedef char *string;
typedef char Bool;

#define TRUE 1
#define FALSE 0


// this is used to malloc memory
void *checked_malloc(int);

// a wrapper interface for string literal
string String(char *);

typedef struct U_boolList_ *U_boolList;
struct U_boolList_ {Bool head; U_boolList tail;};
U_boolList U_BoolList(Bool head, U_boolList tail);

void print(std::string text);
void print(string text);

typedef struct list_s *list_t;
struct list_s
{
    union {
        int i;
        bool b;
        void *data;
    };
    struct list_s *next;
};
list_t list(void *data, list_t next);
list_t vlist(int count, ...);
list_t int_list(int i, list_t next);
list_t bool_list(bool b, list_t next);

list_t join_list(list_t list1, list_t list2);
list_t list_append(list_t list1, void *data);
