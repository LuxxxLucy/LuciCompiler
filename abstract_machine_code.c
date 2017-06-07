#include "lucy_utility.h"
int main(){
Abstract_Register temp[Abstract_Register_Size];
    // STRING FRAGMENTS as follows:
    string_ptr L6 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L6,"hello world\n");
    string_ptr L7 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L7,"这个世界的基本事实\n");
    string_ptr L8 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L8,"1+1=");
    string_ptr L9 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L9,"\n");
    string_ptr L10 = (string_ptr) memory_malloc(sizeof(char)*100);
    strcpy(L10,"能年玲奈==世界之光\n");

    // FUNCTION FRAGMENTS:

temp[100]=1;
temp[102]=1;
    temp[102]=temp[100] + 1;
    simple_print_str(0,L6);
    simple_print_str(0,L7);
    simple_print_str(0,L8);
    simple_print_int(0,temp[102]);
    simple_print_str(0,L9);
    simple_print_str(0,L10);
}
