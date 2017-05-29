#ifndef INCLUDE__TEMP_H
#define INCLUDE__TEMP_H

#include <stdio.h>

#include "symbol.h"
#include "utils.h"

typedef struct temp_ *temp_ptr  ;
temp_ptr  temp(void);

typedef symbol_ptr  tmp_label_ptr  ;
tmp_label_ptr  tmp_label(void);
tmp_label_ptr  tmp_named_label(string_ptr  name);
string_ptr  tmp_name(tmp_label_ptr  label);

typedef struct tmp_map_ *tmp_map_ptr  ;
tmp_map_ptr  tmp_empty(void);
tmp_map_ptr  tmp_layer_map(tmp_map_ptr  over, tmp_map_ptr  under);
void tmp_enter(tmp_map_ptr  map, temp_ptr  tmp, string_ptr  str);
string_ptr  tmp_lookup(tmp_map_ptr  map, temp_ptr  tmp);
void tmp_dump_map(FILE *fp, tmp_map_ptr  map);

tmp_map_ptr  tmp_map(void);

#endif
