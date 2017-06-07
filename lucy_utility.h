#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef char *string_ptr  ;
string_ptr  string(const char *);

#define true 1
#define false 0

#define Abstract_Register_Size 1000
typedef int Abstract_Register;

void* memory_malloc(int);
void simple_print_str(int i,string_ptr msg);
void simple_print_int(int i,Abstract_Register msg);
