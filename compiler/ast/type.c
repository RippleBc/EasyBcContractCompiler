#define _TYPE_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../common.h"
#include "symtab.h"
#include "../parser/error.h"

static int type_index = 0;

int stoi(char *s, int radix)
{
    char *p = s;
    int val = 0;
    int c_val = 0;

    if(radix == 8)
    {
        p++;
        while(*p)
        {
            c_val = *p -'0';
            if(c_val > 7)
            {
                parse_error("octal transform fail", c_val);
                return 0;
            }
            val = val * radix + c_val;
            p++;
        }
    }
    else if(radix == 16)
    {
        p++;
        p++;

        while(*p)
        {
            if(isdigit(*p))
            {
                val = val * radix + (*p - '0');
            }
            else
            {
                c_val = tolower(*p) -'a';
                if(c_val > 5)
                {
                    parse_error("hex transform fail", c_val);
                    return 0;
                }
                val = val * radix + c_val + 10;
            }
            p++;
        }
    }
    else
    {
        while(*p)
        {
            c_val = *p -'0';
            if(c_val > 9)
            {
                parse_error("decimal transform fail", c_val);
                return 0;
            }
            val = val * radix + c_val;
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

    if(!pt)
    {
        internal_error("insufficient memory");
    }

    pt->type_id = base_type; /* 初始化type_id */
    pt->next = NULL;
    pt->first = pt->last = NULL;
    /* 初始化类型符号的名称 */
    switch(base_type)
    {
        case TYPE_INTEGER:
        {
            strcpy(pt->name, "integer");
        }
            break;
        case TYPE_UINTEGER:
        {
            strcpy(pt->name, "uinteger");
        }
            break;
        case TYPE_CHAR:
        {
            strcpy(pt->name, "char");
        }
            break;
        case TYPE_UCHAR:
        {
            strcpy(pt->name, "uchar");
        }
            break;
        case TYPE_BOOLEAN:
        {
            strcpy(pt->name, "boolean");
        }
            break;
        case TYPE_REAL:
        {
            strcpy(pt->name, "real");
        }
            break;
        case TYPE_VOID:
        {
            strcpy(pt->name, "void");
        }
            break;
        case TYPE_STRING:
        {
            strcpy(pt->name, "string");
        }
            break;
        case TYPE_UNKNOWN:
        {
            strcpy(pt->name, "****");
        }
            break;
        default:
        {
            char c_str[MAX_ERR_STR_LEN];
            snprintf(c_str, MAX_ERR_STR_LEN, "new_system_type err, unsupported type %d", base_type);
            /*  */
            internal_error(c_str);
        }
    }
    return pt;
}

type *new_subrange_type(char *name, int element_type)
{
    type *pt;
    if(element_type != TYPE_INTEGER && element_type != TYPE_UINTEGER
            && element_type != TYPE_CHAR && element_type != TYPE_UCHAR)
    {
        char c_str[MAX_ERR_STR_LEN];
        snprintf(c_str, MAX_ERR_STR_LEN, "new_subrange_type err, unsupported element type %d", element_type);
        /*  */
        internal_error(c_str);
    }

    /* pt = (type*)malloc(sizeof(type)); */
    NEW0(pt, PERM);

    if (!pt)
    {
        internal_error("insufficient memory");
    }

    if (name[0]=='$')
    {
        sprintf(pt->name, "$$$%d", ++type_index);
    }
    else
    {
        strncpy(pt->name, name, NAME_LEN);
    }

    pt->next = NULL;

    /* 初始化下界symbol结构 */
    pt->first = new_symbol("$$$", DEF_SUBRANGE_ELEMENT, element_type);
    if (!pt->first)
    {
        internal_error("insufficient memory");
    }

    /* 初始化上界symbol结构 */
    pt->last = new_symbol("$$$", DEF_SUBRANGE_ELEMENT, element_type);
    if (!pt->last)
    {
        internal_error("insufficient memory");
    }

    /* 下界符号链接上界符号 */
    pt->first->next = pt->last;
    /* 初始化类型符号的类型 */
    pt->type_id = TYPE_SUBRANGE;
    return pt;
}

void set_subrange_bound(type *pt, int lower, int upper)
{
    if(lower > upper)
    {
        parse_error("lower bound larger than upper bound", pt->name);
        return;
    }

    /* 初始化上下界 */
    pt->first->v.i = lower;
    pt->last->v.i = upper;

    /* 初始化subrange的元素个数 */
    pt->num_ele = upper - lower + 1;
}

type *new_enum_type(char *name)
{
    type *pt;

    /* pt = (type *)malloc(sizeof(type)); */
    NEW0(pt, PERM);

    if (!pt)
    {
        internal_error("insuficient memory");
    }

    /* 初始化类型符号的名称 */
    if (name[0] == '$')
    {
        sprintf(pt->name, "$$$%d", ++type_index);
    }
    else
    {
        strncpy(pt->name, name, NAME_LEN);
    }

    pt->next = NULL;
    pt->type_id = TYPE_ENUM;
    return pt;
}

void add_enum_elements(type *pt, symbol *symlist)
{
    symbol *p;
    int n = 0;

    /* 初始化枚举类型的符号链表 */ 
    pt->first = symlist;

    /* 枚举类型的符号链表赋值 */
    for(p = pt->first; p->next; p = p->next)
    {
        p->defn = DEF_ENUM_ELEMENT; /* 符号大类 */
        p->type = find_system_type_by_id(TYPE_INTEGER); /* 符号类型 */
        p->v.i = ++n; /* 符号值 */
    }

    p->defn = DEF_ENUM_ELEMENT;
    p->type = find_system_type_by_id(TYPE_INTEGER);
    p->v.i = ++n;

    pt->last = p; /* 符号链表末尾 */
    pt->num_ele = n; /* 符号链表中符号数量 */
}

type *new_array_type(char *name, type *pindex, type *pelement)
{
    type *pt;

    /* 检查规定数组下界的first属性以及规定数组上界的last属性是否合法 */
    if (pindex->first >= pindex->last)
    {
        parse_error("lower bound larger than upper bound", name);
        return NULL;
    }

    NEW0(pt, PERM);

    if (!pt)
    {
        internal_error("insufficient memory");
    }
   
    strncpy(pt->name, name, NAME_LEN);  /* 类型名称 */
    
    pt->type_id = TYPE_ARRAY; /* 类型的类型 */
    pt->num_ele = pindex->last->v.i - pindex->first->v.i + 1; /* 类型中元素个数 */
    pt->first = pindex->first; /* 类型的下界 */
    pt->last = new_symbol("$$$", DEF_ARRAY_ELEMENT, pelement->type_id); /* 类型中的成员的类型 */

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
        internal_error("insufficient memory");
    }

    /* 初始化 */
    strncpy(pt->name, name, NAME_LEN);
    pt->type_id = TYPE_RECORD;
    pt->next = NULL;
    pt->first = fields;
    pt->size = 0;
    pt->num_ele = 0;

    for(p = fields; p ; p = p->next)
    {
        p->defn = DEF_FIELD;
        /* 计算符号在内存中的偏移量，位于record前面位置的属性偏移量小，往后依次增大 */
        p->offset = pt->size;
        /* 计算record类型占用的空间 */
        pt->size += get_symbol_align_size(p);
        /* 计算record类型的属性数量 */
        pt->num_ele++;
    }
    return pt;
}

void add_type_to_table(symtab *ptab, type *pt)
{
    type *qt;
    symbol *p;

    /* 检查是否有重复的自定义类型 */
    for(qt = ptab->type_link; qt; qt = qt->next)
    {
        if (!strcmp(qt->name, pt->name))
        {
            parse_error("duplicate type name", pt->name);
            return;
        }
    }

    /* specify the symtab which pt belong */
    pt->tab = ptab;

    /* 将新定义的类型插入类型链表头部 */
    pt->next = ptab->type_link;
    ptab->type_link = pt;
}

type *find_type_by_name(char *name)
{
    type *pt;
    symtab *ptab;

    ptab = top_symtab_stack();

    for (pt = ptab->type_link; pt; pt = pt->next)
    {
        if (!strcmp(name, pt->name))
        {
            return pt;
        }
    }

    for (pt = System_symtab[0]->type_link; pt; pt = pt->next)
    {
        if (!strcmp(name, pt->name))
        {
            return pt;
        }
    }

    ptab = ptab->parent;
    while(ptab)
    {
        for(pt = ptab->type_link; pt; pt = pt->next)
        {
            if (!strcmp(name, pt->name))
            {
                return pt;
            }
        }
        ptab = ptab->parent;
    }

    return NULL;
}

type *find_system_type_by_id(int id)
{
    Type pt;
    
    /* 从系统符号表中寻找类型 */
    for (pt = System_symtab[0]->type_link; pt; pt = pt->next)
    {
        if (id == pt->type_id)
        {
            return pt;
        }
    }


    return NULL;
}

int get_type_align_size(type *pt)
{ 
    if (!pt)
    {
        return 0;
    }

    switch(pt->type_id)
    {
    case TYPE_INTEGER:
    case TYPE_UINTEGER:
        return  IR->intmetric.align;
    case TYPE_CHAR:
    case TYPE_UCHAR:
    case TYPE_BOOLEAN:
        return  IR->charmetric.align;
    case TYPE_REAL:
        return  IR->floatmetric.align;
    case TYPE_STRING:
        /*  */
        return  IR->intmetric.align;
    case TYPE_ARRAY:
    {
        return pt->num_ele * get_symbol_align_size(pt->last);
    } 
    case TYPE_RECORD:
    {
        return pt->size;
    }
    case TYPE_UNKNOWN:
    {
        printf("TYPE_UNKNOWN %s\n", pt->name);
        internal_error("Unknown type.");
    }
    break;
    }
    return 0;
}