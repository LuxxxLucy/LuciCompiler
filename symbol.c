#include <stdio.h>
#include <string.h>
#include "heading.h"
#include "utility.h"
#include "symbol.h"
#include "table.h"

struct S_symbol_
{
    string name; S_symbol next;
};

static S_symbol mksymbol(string name, S_symbol next){
    S_symbol s= (S_symbol) checked_malloc(sizeof(*s));
    std::string temp_s=std::string(name);
    s->name= new char [temp_s.length()+1];
    std::strcpy (s->name, temp_s.c_str());
    s->next=next;
    return s;
}

#define SIZE 109  /* should be prime */

/* symbols with the same hash value shares the same symbol hash table */
static S_symbol hashtable[SIZE];

static unsigned int hash(char *s0){
    /* simple hash function */
    unsigned int h=0;
    char *s;
    for(s=s0; *s; s++)
       h = h*65599 + *s;
    return h;
}

static int streq(std::string a, std::string b){
    return a==b;
}

S_symbol S_Symbol(string name){
    int index= hash(name) % SIZE;
    S_symbol syms = hashtable[index], sym;
    for(sym=syms; sym; sym=sym->next)
        if (streq(sym->name,std::string(name) ) )
            return sym;
    sym = mksymbol(name,syms);
    hashtable[index]=sym;
    return sym;
}

string S_name(S_symbol sym){
    std::string temp_s=std::string(sym->name);
    char * c = new char [temp_s.length()+1];
    std::strcpy (c, temp_s.c_str());
    return c;
}

S_table S_empty(void){
    return TAB_empty();
}

void S_enter(S_table t, S_symbol sym, void *value){
    TAB_enter(t,sym,value);
}

void *S_look(S_table t, S_symbol sym) {
  return TAB_look(t,sym);
}

static struct S_symbol_ marksym = {"<mark>",0};

void S_beginScope(S_table t){
    S_enter(t,&marksym,NULL);
}

void S_endScope(S_table t){
    S_symbol s;
    do s= (S_symbol) TAB_pop(t);
    while (s != &marksym);
}

void S_dump(S_table t, void (*show)(S_symbol sym, void *binding)) {
  TAB_dump(t, (void (*)(void *, void *)) show);
}
