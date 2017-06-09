#include "lucy_utility.h"
int main(){
Abstract_Register temp[Abstract_Register_Size];
    // STRING FRAGMENTS as follows:
    string_ptr L9 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L9,"hello world\n");
    string_ptr L10 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L10,"这个世界的基本事实\n");
    string_ptr L11 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L11,"1+1=");
    string_ptr L12 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L12,"\n");
    string_ptr L13 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L13,"能年玲奈==世界之光\n");

    // FUNCTION FRAGMENTS:

temp[100]=1;
temp[102]=1;
    temp[102]=ESEQ(
    CJUMP(==
temp[100]1.L6, .L7)
;
    LABEL .L6
;
    MEM(
temp[103])
=temp[100] + 1;
    JUMP(
L8)
;
    LABEL .L7
;
    MEM(
temp[103])
=1;
    LABEL .L8
;
temp[103];
    simple_print_str(0,L9);
    simple_print_str(0,L10);
    simple_print_str(0,L11);
    simple_print_int(0,temp[102]);
    simple_print_str(0,L12);
    simple_print_str(0,L13);
}
