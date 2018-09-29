#define _TYPE_C
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>
#include  "common.h"
#include  "symtab.h"
# include  "error.h"

static int type_index = 0;

int stoi(char *s,int radix)
{
    char *p = s;
    int val = 0;

    if (radix == 8)
    {
        p++;
        while(*p)
        {
            val = val * radix + (*p - '0');
            p++;
        }
    }
    else if (radix == 16 )
    {
        p++;
        p++;

        while(*p)
        {
            if (isdigit(*p))
            {
                val = val * radix + (*p - '0');
            }
            else
            {
                val = val * radix + (tolower(*p) - 'a');
            }
            p++;
        }
    }
    else
    {
        while(*p)
        {
            val = val * radix + (*p -'0');
            p++;
        }
    }
    return val;
}

type *new_system_type(int base_type)
{
    type *pt;

    /* pt = (type *)malloc(sizeof(type)); */
    NEW0(pt, PERM);

    if (!pt)
        internal_error("Insufficient memory.");

    pt->type_id = base_type;
    pt->next = NULL;
    pt->first = pt->last = NULL;

    switch(base_type)
    {
    case TYPE_INTEGER:
        strcpy(pt->name, "integer");
        break;
    case TYPE_CHAR:
        strcpy(pt->name, "char");
        break;
    case TYPE_BOOLEAN:
        strcpy(pt->name, "boolean");
        break;
    case TYPE_REAL:
        strcpy(pt->name, "real");
        break;
    case TYPE_VOID:
        strcpy(pt->name, "void");
        break;
    case TYPE_UNKNOWN:
        strcpy(pt->name, "****");
        break;
    default:
        break;
    }
    return pt;
}

type *new_subrange_type(char *name,int element_type)
{
    type *pt;
    if (element_type != TYPE_INTEGER
            &&element_type != TYPE_CHAR)
        return NULL;

    /* pt = (type  *)malloc(sizeof(type)); */
    NEW0(pt, PERM);

    if (!pt)
        internal_error("Insufficient memory.");

    if (name[0]=='$')
        sprintf(pt->name, "$$$%d", ++type_index);
    else
        strncpy(pt->name,name,NAME_LEN);
    pt->next = NULL;

    pt->first = new_symbol("$$$", DEF_ELEMENT,
                           element_type);

    pt->last = new_symbol("$$$", DEF_ELEMENT,
                          element_type);

    if (!pt->first || !pt->last)
        internal_error("Insufficient memory.");

    pt->first->next = pt->last;
    pt->type_id = TYPE_SUBRANGE;
    return pt;
}

void set_subrange_bound(type *pt,int lower,int upper)
{
    if (!pt || !pt->first || !pt->last)
        return;

    if(lower > upper)
    {
        parse_error("Lower bound larger than upper bound",pt->name);
        return;
    }
    pt->first->v.i = lower;
    pt->last->v.i = upper;
    if (pt->first->type->type_id == TYPE_CHAR)
    {
        sprintf(pt->first->rname, "%c", lower);
        sprintf(pt->last->rname,"%c", upper);
    }
    else
    {
        sprintf(pt->first->rname, "0%xh", lower);
        sprintf(pt->last->rname,"0%xh", upper);
    }
    pt->num_ele = upper - lower + 1;
}

type *new_enum_type(char *name)
{
    type *pt;


    /* pt = (type *)malloc(sizeof(type)); */
    NEW0(pt, PERM);

    if (!pt)
    {
        internal_error("Insuficient memory.");
        return NULL;
    }

    if (name[0] == '$')
        sprintf(pt->name, "$$$%d", ++type_index);
    else
        strncpy(pt->name, name,NAME_LEN);

    pt->next = NULL;
    pt->type_id = TYPE_ENUM;
    return pt;
}


void add_enum_elements(type *pt, symbol *symlist)
{
    symbol *p;
    int n = 0;

    if (!p || !symlist)
        return;
    pt->first = symlist;

    for(p = pt->first;p->next;p = p->next)
    {
        p->defn = DEF_ELEMENT;
        p->type = find_type_by_id(TYPE_INTEGER);
        p->v.i = ++n;
        sprintf(p->rname, "0%xh",p->v.i);
    }

    p->defn = DEF_ELEMENT;
    p->type = find_type_by_id(TYPE_INTEGER);
    p->v.i = ++n;
    sprintf(p->rname, "0%xh",p->v.i);
    pt->last = p;
    pt->num_ele = n;
}

type *new_array_type(char *name, type *pindex,
                     type *pelement)
{
    type *pt;

    if (!pindex || !pelement)
        return NULL;
    if (!pindex->first
            || !pindex->last
            || pindex->first == pindex->last)
    {
        parse_error("index bound expcted", name);
        return NULL;
    }

    /* pt = (type *)malloc(sizeof(type)); */
    NEW0(pt, PERM);

    if (!pt)
    {
        internal_error("Insufficient memory.");
        return NULL;
    }

    strncpy(pt->name, name, NAME_LEN);
    pt->type_id = TYPE_ARRAY;
    pt->num_ele = pindex->last->v.i -
                  pindex->first->v.i + 1;

    pt->first = pindex->first;
    pt->last = new_symbol("$$$", DEF_ELEMENT,
                          pelement->type_id);
    sprintf(pt->last->rname, "ary_ele");
    if (!pt->last)
    {
        internal_error("Insufficient memory");
        return NULL;
    }
    return pt;
}

type *new_record_type(char *name, symbol *fields)
{
    type *pt;
    symbol *p;

    /* pt = (type *)malloc(sizeof(type)); */
    NEW0(pt, PERM);

    if (!pt)
    {
        internal_error("Insufficient memory.");
        return NULL;
    }

    strncpy(pt->name,name, NAME_LEN);
    pt->type_id = TYPE_RECORD;
    pt->next = NULL;
    pt->first = fields;
    pt->size = 0;
    pt->num_ele = 0;

    for(p = fields; p ; p = p->next)
    {
        p->defn = DEF_FIELD;
        p->offset = pt->size;
        pt->size += align(get_symbol_size(p));
        pt->num_ele++;
    }
    return pt;
}

void add_type_to_table(symtab *ptab,type *pt)
{
    type *qt;
    symbol *p;

    if (!ptab || !pt)
        return;
    for(qt = ptab->type_link; qt; qt = qt->next)
        if (!strcmp(qt->name, pt->name))
        {
            parse_error("Duplicate type name",pt->name);
            return;
        }

    pt->next = ptab->type_link;
    ptab->type_link = pt;
    if (pt->type_id == TYPE_ENUM
            || pt->type_id == TYPE_RECORD)
        for(p = pt->first; p; p = p->next)
            add_var_to_localtab(ptab, p);
}


type *find_local_type_by_name(char *name)
{
    type *pt;
    symtab *ptab;

    ptab = top_symtab_stack();
    if (!ptab)
        return NULL;

    for(pt = ptab->type_link; pt; pt = pt->next)
        if (!strcmp(name, pt->name))
            return pt;

    for(pt = System_symtab[0]->type_link;pt;
            pt = pt->next)
        if (!strcmp(name,pt->name))
            return pt;
    ptab = ptab->parent;
    while(ptab)
    {
        for(pt = ptab->type_link;pt;pt = pt->next)
            if (!strcmp(name, pt->name))
                return pt;
    }
    return NULL;
}

/*
 * find type by type name. 
 * 
 */
type *find_type_by_name(char *name)
{
    type *pt;
    symtab *ptab;

    ptab = top_symtab_stack();
    if (!ptab)
        return NULL;

    for (pt = ptab->type_link; pt; pt = pt->next)
        if (!strcmp(name, pt->name))
            return pt;

    for (pt = System_symtab[0]->type_link; pt; pt = pt->next)
        if (!strcmp(name, pt->name))
            return pt;

    ptab = ptab->parent;
    while(ptab)
    {
        for(pt = ptab->type_link; pt; pt = pt->next)
            if (!strcmp(name, pt->name))
                return pt;
        ptab = ptab->parent;
    }

    return NULL;
}

/*
 * find type by type id. 
 * 
 */
type *find_type_by_id(int id)
{
    type *pt;
    symtab *ptab;

    ptab = top_symtab_stack();
    if (!ptab)
        return NULL;

    for (pt = ptab->type_link; pt; pt = pt->next)
        if (id == pt->type_id)
            return pt;

    for (pt = System_symtab[0]->type_link; pt; pt = pt->next)
        if (id == pt->type_id)
            return pt;

    ptab = ptab->parent;
    while(ptab)
    {
        for(pt = ptab->type_link; pt; pt = pt->next)
            if (id == pt->type_id)
                return pt;
    }

    return NULL;
}

type *clone_type(type *src)
{
    type *pt;
    symbol *p;

    if (!src)
        return NULL;

    switch(src->type_id)
    {
    case TYPE_ENUM:
        pt = new_enum_type(src->name);
        pt->first = clone_symbol_list(src->first);
        for(p = pt->first; p->next; p = p->next)
            ;
        pt->last = p;
        break;
    case TYPE_SUBRANGE:
        pt = new_subrange_type(src->name,
                               src->first->type->type_id);
        pt->first = clone_symbol(src->first);
        pt->last = clone_symbol(src->last);
        pt->first->next = pt->last;
        break;
    case  TYPE_INTEGER:
    case  TYPE_CHAR:
    case  TYPE_BOOLEAN:
    case  TYPE_REAL:
        pt = new_system_type(src->type_id);
        break;
	default:
        pt = NULL;
        break;
    }
    return pt;
}

int get_type_size(type *pt)
{
    if (!pt)
        return 0;

    switch(pt->type_id)
    {
    case TYPE_ARRAY:
        return pt->num_ele*
               get_symbol_size(pt->first);
    case TYPE_RECORD:
        return pt->size;
    }
    return 0;
}

