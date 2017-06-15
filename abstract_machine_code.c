#include "lucy_utility.h"
int main(){
Abstract_Register temp[Abstract_Register_Size];
    // STRING FRAGMENTS as follows:
    string_ptr L15 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L15,"hello world\n");
    string_ptr L16 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L16,"这个世界的基本事实\n");
    string_ptr L17 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L17,"1+1=");
    string_ptr L18 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L18,"\n");
    string_ptr L19 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L19,"能年玲奈==世界之光\n");

    // FUNCTION FRAGMENTS:

temp[100]=1;
temp[102]=1;
    temp[102]=    (temp[100]==1)?
(.L6) : (.L7)
;
    LABEL .L6
;
    temp[103]=temp[100] + 1;
    JUMP(
L8)
;
    LABEL .L7
;
    temp[103]=1;
    LABEL .L8
;
temp[103];
        LABEL .L12
;
    (temp[102]>0)?
(.L13) : (.L14)
;
    LABEL .L13
;
            (temp[102]==8)?
(.L9) : (.L10)
;
    LABEL .L9
;
    temp[104]=    temp[102]=temp[102] * 1;
0;
    JUMP(
L11)
;
    LABEL .L10
;
    temp[104]=temp[102]=temp[102] + 20;
    LABEL .L11
;
temp[104];
;
    JUMP(
L12)
;
    LABEL .L14
;
;
    simple_print_str(0,L15);
    simple_print_str(0,L16);
    simple_print_str(0,L17);
    simple_print_int(0,temp[102]);
    simple_print_str(0,L18);
    simple_print_str(0,L19);
}
