#include "temp.h"

struct temp_
{
    int num;
};

string_ptr  tmp_name(tmp_label_ptr  label)
{
    return sym_name(label);
}

static int _labels = 0;

tmp_label_ptr  tmp_label(void)
{
    char buf[16];
    snprintf(buf, sizeof(buf), ".L%d", _labels++);
    return tmp_named_label(string(buf));
}

tmp_label_ptr  tmp_named_label(string_ptr  str)
{
    return symbol(str);
}

static int _temps = 100;

temp_ptr  temp(void)
{
    temp_ptr  p = checked_malloc(sizeof(*p));
    p->num = _temps++;
    {
        char buf[16];
        snprintf(buf, sizeof(buf), "%d", p->num);
        tmp_enter(tmp_map(), p, string(buf));
    }
    return p;
}

struct tmp_map_
{
    table_ptr  table;
    tmp_map_ptr  under;
};

tmp_map_ptr  tmp_map(void)
{
    static tmp_map_ptr  map = NULL;
    if (!map)
        map = tmp_empty();
    return map;
}

static tmp_map_ptr  new_map(table_ptr  tab, tmp_map_ptr  under)
{
    tmp_map_ptr  p = checked_malloc(sizeof(*p));
    p->table = tab;
    p->under = under;
    return p;
}

tmp_map_ptr  tmp_empty(void)
{
    return new_map(TAB_empty(), NULL);
}

tmp_map_ptr  tmp_layer_map(tmp_map_ptr  over, tmp_map_ptr  under)
{
    if (over == NULL)
        return under;
    else
        return new_map(over->table, tmp_layer_map(over->under, under));
}

void tmp_enter(tmp_map_ptr  map, temp_ptr  tmp, string_ptr  str)
{
    assert(map && map->table);
    TAB_enter(map->table, tmp, str);
}

string_ptr  tmp_lookup(tmp_map_ptr  map, temp_ptr  tmp)
{
    string_ptr  str;

    assert(map && map->table);
    str = TAB_lookup(map->table, tmp);
    if (str)
        return str;
    else if (map->under)
        return tmp_lookup(map->under, tmp);
    else
        return NULL;
}

static FILE *_fp;

static void show(temp_ptr  tmp, string_ptr  str)
{
    fprintf(_fp, "t%d ->%s\n", tmp->num, str);
}

void tmp_dump_map(FILE *fp, tmp_map_ptr  map)
{
    _fp = fp;
    TAB_dump(map->table, (TAB_dump_func_ptr) show);
    if (map->under)
    {
        fprintf(fp, "-------\n");
        tmp_dump_map(fp, map->under);
    }
}
