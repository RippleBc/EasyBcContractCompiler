#define _TYPE_C
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>
#include  "../common.h"
#include  "symtab.h"
# include  "../parser/error.h"

static int type_index = 0;

/* 字符串转化为10进制数字 */
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

    pt->type_id = base_type; /* 初始化type_id */
    pt->next = NULL;
    pt->first = pt->last = NULL;

    /* 初始化类型符号的名称 */
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

type *new_subrange_type(char *name, int element_type)
{
    type *pt;
    if (element_type != TYPE_INTEGER
            &&element_type != TYPE_CHAR)
        return NULL;

    /* pt = (type*)malloc(sizeof(type)); */
    NEW0(pt, PERM);

    if (!pt)
        internal_error("Insufficient memory.");

    if (name[0]=='$')
        sprintf(pt->name, "$$$%d", ++type_index);
    else
        strncpy(pt->name, name, NAME_LEN);
    pt->next = NULL;

    /* 初始化下界symbol结构 */
    pt->first = new_symbol("$$$", DEF_ELEMENT,
                           element_type);

    /* 初始化上界symbol结构 */
    pt->last = new_symbol("$$$", DEF_ELEMENT,
                          element_type);

    if (!pt->first || !pt->last)
        internal_error("Insufficient memory.");

    /* 下界符号链接上界符号 */
    pt->first->next = pt->last;
    /* 初始化类型符号的类型 */
    pt->type_id = TYPE_SUBRANGE;
    return pt;
}

void set_subrange_bound(type *pt, int lower, int upper)
{
    if (!pt || !pt->first || !pt->last)
        return;

    if(lower > upper)
    {
        parse_error("Lower bound larger than upper bound",pt->name);
        return;
    }

    /* 初始化上下界 */
    pt->first->v.i = lower;
    pt->last->v.i = upper;

    /* 初始化表示上下界符号的汇编名称 */
    if (pt->first->type->type_id == TYPE_CHAR)
    {
        /* 接受char类型 */
        sprintf(pt->first->rname, "%c", lower);
        sprintf(pt->last->rname,"%c", upper);
    }
    else
    {
        /* 接受integer类型 */
        sprintf(pt->first->rname, "0%xh", lower);
        sprintf(pt->last->rname,"0%xh", upper);
    }

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
        internal_error("Insuficient memory.");
        return NULL;
    }

    /* 初始化类型符号的名称 */
    if (name[0] == '$')
        sprintf(pt->name, "$$$%d", ++type_index);
    else
        strncpy(pt->name, name, NAME_LEN);

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

    /* 初始化枚举类型的符号链表 */ 
    pt->first = symlist;

    /* 枚举类型的符号链表赋值 */
    for(p = pt->first; p->next; p = p->next)
    {
        p->defn = DEF_ELEMENT; /* 符号大类 */
        p->type = find_type_by_id(TYPE_INTEGER); /* 符号类型 */
        p->v.i = ++n; /* 符号值 */
        sprintf(p->rname, "0%xh", p->v.i); /* 符号汇编名称 */
    }

    p->defn = DEF_ELEMENT;
    p->type = find_type_by_id(TYPE_INTEGER);
    p->v.i = ++n;
    sprintf(p->rname, "0%xh", p->v.i);

    pt->last = p; /* 符号链表末尾 */
    pt->num_ele = n; /* 符号链表中符号数量 */
}

type *new_array_type(char *name, type *pindex, type *pelement)
{
    type *pt;

    /* 其中pindex必须是枚举类型或者子范围类型，pelement类可以是任意类型。 */
    if (!pindex || !pelement)
    {
        parse_error("need index or type", name);
        return NULL;
    }
    /* 检查规定数组下界的first属性以及规定数组上界的last属性是否合法 */
    if (!pindex->first || !pindex->last || pindex->first == pindex->last)
    {
        parse_error("index bound expcted", name);
        return NULL;
    }

    NEW0(pt, PERM);

    if (!pt)
    {
        internal_error("Insufficient memory.");
        return NULL;
    }
    /* 类型名称 */
    strncpy(pt->name, name, NAME_LEN);
    /* 类型的类型 */
    pt->type_id = TYPE_ARRAY;
    /* 类型中元素个数 */
    pt->num_ele = pindex->last->v.i -
                  pindex->first->v.i + 1;
    /* 类型的下界 */
    pt->first = pindex->first;
    /* 类型中的成员的类型 */
    pt->last = new_symbol("$$$", DEF_ELEMENT, pelement->type_id);
    /* 类型中的成员的类型的名称 */
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
        pt->size += align(get_symbol_size(p));
        /* 计算record类型的属性数量 */
        pt->num_ele++;
    }
    return pt;
}

void add_type_to_table(symtab *ptab, type *pt)
{
    type *qt;
    symbol *p;

    if (!ptab || !pt)
        return;

    /* 检查是否有重复的自定义类型 */
    for(qt = ptab->type_link; qt; qt = qt->next)
        if (!strcmp(qt->name, pt->name))
        {
            parse_error("Duplicate type name", pt->name);
            return;
        }

    /* 将新定义的类型插入类型链表头部 */
    pt->next = ptab->type_link;
    ptab->type_link = pt;
}

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

type *find_type_by_id(int id)
{
    type *pt;
    symtab *ptab;

    ptab = top_symtab_stack();
    if (!ptab)
        return NULL;

    /* 从当前块的符号表中寻找类型 */
    for (pt = ptab->type_link; pt; pt = pt->next)
        if (id == pt->type_id)
            return pt;

    /* 从系统符号表中寻找类型 */
    for (pt = System_symtab[0]->type_link; pt; pt = pt->next)
        if (id == pt->type_id)
            return pt;

    /* 从父级块的符号表中寻找类型 */
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
    case TYPE_INTEGER:
    case TYPE_CHAR:
    case TYPE_BOOLEAN:
    case TYPE_REAL:
        pt = new_system_type(src->type_id);
        break;
    case TYPE_ARRAY:
    {
        /*  */
        type* subrange_p = new_subrange_type("$$$", TYPE_INTEGER);
        set_subrange_bound(subrange_p, src->first->v.i, src->num_ele);

        /*  */
        type* ele_type = clone_type(src->last->type);

        /*  */
        pt = new_array_type(src->name, subrange_p, ele_type);
    }
    break;
    case TYPE_RECORD:
    {
        symbol *first = NULL, *p = NULL, *q = NULL, *temp = NULL;

        /*  */
        temp = src->first;

        for(temp; temp != NULL; temp = temp->next)
        {
            q = clone_symbol(temp);

            if(p == NULL)
            {
                first = p = q;
            }
            else
            {
                p->next = q;
                p = p->next;
            }
        }

        /* */
        pt = new_record_type(src->name, first);
    }
    break;
	default:
        pt = NULL;
        break;
    }
    return pt;
}

type *init_type_link(type *src)
{
    int i;
    type *new_type;

    switch(src->type_id)
    {
        case TYPE_ARRAY:
        {
            src = clone_type(src);

            symbol *p = NULL, *q = NULL;
            int i = 1;

            /*  */
            while(i <= src->num_ele)
            {
                q = new_symbol("$$$", src->last->defn, src->last->type->type_id);

                snprintf(q->name, sizeof(q->name), "%d", i);
                
                q->type_link = init_type_link(src->last->type);

                if(p == NULL)
                {
                    src->first = p = q;
                }
                else
                {
                    p->next = q;
                    p = p->next;
                }

                i++;
            }
            
            src->last = p;

            return src;
        }
        break;
        case TYPE_RECORD:
        {
            src = clone_type(src);

            /*  */
            symbol *p = NULL, *q = NULL, *temp = NULL;
            
            for(temp = src->first; temp != NULL; temp = temp->next)
            {

                q = clone_symbol(temp);
                q->type_link = init_type_link(q->type);

                if(p == NULL)
                {
                    src->first = p = q;
                }
                else
                {
                    p->next = q;
                    p = p->next;

                    /* */
                    if(p->next == NULL)
                    {
                        src->last = p;
                    }
                }
            }

            return src;
        }
        break;
        default:
        {
            return src;
        }
        break;
    }
}

int get_type_size(type *pt)
{ 
    if (!pt)
        return 0;

    switch(pt->type_id)
    {
    case TYPE_ARRAY:
        return pt->num_ele * get_symbol_size(pt->first);
    case TYPE_RECORD:
        return pt->size;
    }
    return 0;
}