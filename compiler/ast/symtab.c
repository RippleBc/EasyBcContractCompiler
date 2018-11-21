#define   SYMTABC
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>
#include  "../common.h"
#include  "symtab.h"
#include  "../parser/error.h"
#include  "../parser/rule.h"

int routine_id;

#define  SYMTAB_STACK_SIZE 64
int symtab_tos = SYMTAB_STACK_SIZE - 1;
symtab *symtab_stack[SYMTAB_STACK_SIZE]; /* 保存上下文（符号表） */

symtab *Global_symtab = NULL; /* 全局符号表 */
symtab *System_symtab[MAX_SYS_ROUTINE]; /* 系统符号表 */

extern int Keytable_size;

symtab *new_symtab(symtab *parent)
{
    symtab *p;

    /* p = (symtab *)malloc(sizeof(symtab));，然后把p所指向的内存空间的内容置为'0' */
    NEW0(p, PERM);

    if(!p)
    {
        internal_error("insufficient memory");
    }

    p->parent = parent; /* 链接父符号表 */
    p->args = NULL; /* 参数链表 */
    p->localtab = NULL; /* 局部符号二叉树表（参数和变量） */
    p->type_link = NULL; /* 用户自定义类型链表 */

    if(parent)
    {
        p->level = parent->level + 1;
    }
    else
    {
        routine_id = 0; /* 初始化routine id */
        Global_symtab = p; /* 初始化全局符号表 */
        p->level = 0; /* 初始化层级 */
    }
    p->defn = DEF_UNKNOWN; /* 符号所属大类 */
    p->type = find_system_type_by_id(TYPE_VOID); /* 过程或者函数返回值的类型（普通类型），默认为void */
    p->id = routine_id++; /* 过程或者函数的序号 */
    p->call_stack_size = 4; /* first index store return position, 局部变量的总字节数 */
    p->routine_index = 0;
    return p;
}

/* 创建一个symbol对象 */
symbol *new_symbol(char *name, int defn, int type_id)
{
    symbol *p;
    static int imp_index = 0;

    /* p = (symbol *)malloc(sizeof(symbol)); */
    NEW0(p, PERM);

    if(!p)
    {
        internal_error("insuffceent memory");
    }

    if(!strcmp(name,"$$$"))
        /* name == "$$$"，使用系统默认的命名规则*/
        sprintf(p->name, "z%d", ++imp_index);
    else
        strncpy(p->name, name, NAME_LEN);

    p->defn = defn; /* 定义符号所属大类 */
    p->type = find_system_type_by_id(type_id); /* 定义符号类型 */
    p->offset = 0; /* 在堆栈中的偏移量 */
    p->next = NULL; /* 用于局部变量链表以及参数链表 */
    p->lchild = p->rchild = NULL; /* 用于二叉树符号表（变量或者参数） */
    p->tab = NULL; /* 指向符号表的表头 */
    p->type_link = NULL; /* 同一种类型的下一个symbol */

    return p;
}

symbol *clone_symbol(symbol *origin)
{
    symbol *p;

    /* p = (symbol *)malloc(sizeof(symbol)); */
    NEW0(p, PERM);
    if(!p)
    {
        internal_error("insuffident memory");
    }

    strncpy(p->name, origin->name, NAME_LEN);
    p->defn = origin->defn;
    p->type = origin->type;
    p->offset = origin->offset;
    p->next = NULL;
    p->tab = NULL;

    /* symbol类型为字符串 */
    if (p->type->type_id == TYPE_STRING)
        p->v.s = strdup(origin->v.s);
    else
        p->v.f = origin->v.f;
    return p;
}

symbol *clone_symbol_list(symbol *head)
{
    symbol *new_list;
    symbol *p;
    symbol *q = head;

    /* 拷贝链表头 */
    new_list = p = clone_symbol(q);

    /* 遍历拷贝链表 */
    q = q->next;
    while(q)
    {
        p->next = clone_symbol(q);
        p = p->next;
        q = q->next;
    }

    return new_list;
}

/* 参数链表反转 */
symbol *reverse_parameters(symtab *ptab)
{
    symbol *p,*q;
    symbol *new_list = NULL;

    for(p = ptab->args;p;)
    {
        q = p;
        p = p->next;
        q->next = new_list;
        new_list = q;
    }

    ptab->args = new_list;
    return ptab->args;
}

void add_routine_to_table(symtab *tab, symtab *routine)
{
    if (tab->routine_index < SYMTAB_QUEUE_SIZE)
    {
        tab->routine_queue[tab->routine_index++] = routine;
    }
}

void add_symbol_to_table(symtab *tab, symbol *sym)
{
    /* specify the symtab which sym is belong */
    sym->tab = tab;

    /*  */
    switch(sym->defn)
    {
        case DEF_FUNCT:
        case DEF_PROC:
        case DEF_VAR:
        case DEF_CONST:
            /* 函数标识、过程标识、普通变量标识、常量标识 */
            add_local_to_table(tab, sym);
            break;
        case DEF_VARPARA:
        case DEF_VALPARA:
            /* 变参（一个变量）、值参（一个常量） */
            add_args_to_table(tab, sym);
            break;
        default:
        {
            char c_err[MAX_ERR_STR_LEN];
            snprintf(c_err, MAX_ERR_STR_LEN, "add_symbol_to_table err, unsupported symbol def %s %d", sym->name, sym->defn);
            /*  */
            internal_error(c_err);
        }
    }
}

void add_var_to_localtab(symtab *tab, symbol *sym)
{
    symbol *p;
    int i;

    if(!tab->localtab)
    {
        tab->localtab = sym;
        return;
    }

    /* 将局部symbol插入局部符号表 */
    p = tab->localtab;
    while(1)
    {
        i = strcmp(sym->name, p->name);
        if(i > 0)
        {
            if(p->rchild)
                p = p->rchild;
            else
            {
                p->rchild = sym;
                break;
            }
        }
        else if (i < 0)
        {
            if (p->lchild)
                p = p->lchild;
            else
            {
                p->lchild = sym;
                break;
            }
        }
        else
        {
            parse_error("duplicate identifier", sym->name);
            break;
        }
    }
}

/* 添加局部变量到symtab中 */
void add_local_to_table(symtab *tab, symbol *sym)
{
    /* 计算symtab中参数所占用的空间 */
    int var_size = get_symbol_align_size(sym);
    /* symtab为函数，记录局部变量在symtab中偏移量 */
    sym->offset = tab->call_stack_size;
    /* 计算symtab中局部变量所占用的空间 */
    tab->call_stack_size += var_size;

    /*  */
    if(sym->defn == DEF_FUNCT)
    { 
        tab->return_sym = sym;
    }

    /* 将局部变量插入局部符号表中 */
    add_var_to_localtab(tab, sym);
}

void add_args_to_table(symtab *tab, symbol *sym)
{
    /* 计算symtab中参数所占用的空间 */
    int var_size = get_symbol_align_size(sym);

    /* 计算局部变量在symtab中的偏移量 */
    sym->offset = tab->call_stack_size;
    tab->call_stack_size += var_size;

    /* 添加sym到局部参数链表中，从头部插入 */
    sym->next = tab->args;
    tab->args = sym;
    sym->tab = tab;

    /* 将局部参数插入局部符号表中 */
    add_var_to_localtab(tab, sym);
}

extern KEYENTRY Keytable[];

/* 初始化系统符号表 */
void make_system_symtab()
{
    int i;
    symtab *ptab;
    type *pt;

    for(i = 0; i < MAX_SYS_ROUTINE; i++)
    {
        System_symtab[i] = NULL;
    }


    /* ptab = (symtab*)malloc(sizeof(symtab)); */
    NEW0(ptab, PERM);
    if(!ptab)
    {
        internal_error("insuflicent memory");
    }

    System_symtab[0] = ptab;

    /* 系统符号表命名 */
    sprintf(ptab->name,"system_table");

    /* 基础类型 */
    ptab->type_link = new_system_type(TYPE_INTEGER);
    pt = ptab->type_link;
    pt->next = new_system_type(TYPE_UINTEGER);
    pt = pt->next;
    pt->next = new_system_type(TYPE_CHAR);
    pt = pt->next;
    pt->next = new_system_type(TYPE_UCHAR);
    pt = pt->next;
    pt->next = new_system_type(TYPE_BOOLEAN);
    pt = pt->next;
    pt->next = new_system_type(TYPE_REAL);
    pt = pt->next;
    pt->next = new_system_type(TYPE_VOID);
    pt = pt->next;
    pt->next = new_system_type(TYPE_STRING);
    pt = pt->next;
    pt->next = new_system_type(TYPE_UNKNOWN);
    pt = pt->next;

    ptab->id = -1;
    ptab->level = -1;
    ptab->defn = DEF_UNKNOWN; /* 属性值 */
    ptab->type = TYPE_UNKNOWN; /* 符号表类型 */ 
    ptab->call_stack_size = 0;
    ptab->args = NULL;
    ptab->parent = NULL;

    /* 系统函数 */
    int n = 1;
    for(i = 0 ; i < Keytable_size; i++)
    {
        if(Keytable[i].key == SYS_FUNCT || Keytable[i].key == SYS_PROC )
        {
            System_symtab[n] = new_sys_symbol(Keytable[i]);
            n++;
        }
        else if (Keytable[i].key == LAST_ENTRY)
            break;
    }
    
    /* 系统函数个数 */
    ptab->call_stack_size = n;
}

/* 创建系统符号 */
symtab* new_sys_symbol(KEYENTRY entry)
{
    symtab *ptab;
    symbol *p;

    /* ptab = (symtab*)malloc(sizeof(symtab)); */
    NEW0(ptab, PERM);

    if(!ptab)
    {
        internal_error("insufticent memory.");
    }

    /* 初始化符号名称 */
    strcpy(ptab->name, entry.name);

    /* 初始化系统符号表 */
    ptab->id = -entry.attr; /* 注意，系统符号的ID为attr的负值 */
    ptab->level = -1;
    ptab->defn = DEF_FUNCT; /* 系统函数的大类统一为DEF_FUNCT */
    ptab->type = NULL;
    ptab->call_stack_size = 0;
    ptab->args = NULL;
    ptab->localtab = NULL;
    ptab->parent = System_symtab[0]; /* 父节点为定义了内置基础类型的符号表 */

    return ptab;
}

int is_symbol(symbol *p, char *name)
{
    if(strcmp(p->name, name))
    {
        return  0;
    }
    return 1;
}

int get_symbol_align_size(symbol *sym)
{
    return get_type_align_size(sym->type);
}

symtab *pop_symtab_stack()
{
    if(symtab_tos == SYMTAB_STACK_SIZE)
    {
        internal_error("symtab stack is empty");
    }
    return symtab_stack[++symtab_tos];
}

void push_symtab_stack(symtab *tab)
{
    if(symtab_tos == -1)
    {
        internal_error("symtab stack is full");
    }
    else
    {
        symtab_stack[symtab_tos--] = tab;
    }
}

symtab *top_symtab_stack()
{
    return symtab_stack[symtab_tos + 1];
}

/* 寻找自定义函数或者过程 */
symtab *find_routine(symtab *tab, char *name)
{
    int i;
    symtab *routine;

    /* 内部调用函数或者过程（递归调用） */
    if(!strcmp(tab->name, name)) 
    {
        return tab;
    }

    /*  */
    while(tab)
    {
        /* 外部调用函数或者过程 */
        for(i = 0; i < tab->routine_index; i++)
        {
            routine = tab->routine_queue[i];
            if(!strcmp(routine->name, name))
            {
                return routine;
            }
        }

        tab = tab->parent;
    }  
    
    return NULL;
}

/* 寻找系统符号表 */
symtab *find_sys_routine(int routine_id)
{
    int i;
    for(i = 1; i < System_symtab[0]->call_stack_size; i++)
    {
        if(System_symtab[i]->id == -routine_id)
        {
            return System_symtab[i];
        }
    }
    return NULL;
}

/* 从类型符号表中寻找RECORD中对应的field */
symbol *find_field(symbol *p, char *name)
{
    symbol *q;   

    if(p->type->type_id != TYPE_RECORD)
    {
        return NULL;
    }
   
    /* 遍历符号类型 */
    for(q = p->type->first; q; q = q->next)
    {
        if(is_symbol(q, name))
        {
            return q;
        }
    }

    return NULL;
}

symbol *find_symbol(symtab *tab, char *name)
{
    symbol *p;
    type *pt;

    while(tab)
    {   
        /* 寻找指定的实例符号 */
        p = find_local_symbol(tab, name);
        if(p)
        {
            return p;
        }

        /* enum, record field */
        for(pt = tab->type_link; pt; pt = pt->next)
        {
            for(p = pt->first; p; p = p->next)
            {
                if(is_symbol(p, name))
                {
                    return p;
                }
            }
        }
        tab = tab->parent;
    }
    return NULL;
}

symbol *find_local_symbol(symtab *tab, char *name)
{
    int i;
   
    symbol *p = tab->localtab;
    /* 从实例符号表中寻找指定的实例符号 */
    while(p)
    {
        i = strcmp(name, p->name);
        if(i > 0)
            p = p->rchild;
        else if(i < 0)
            p = p->lchild;
        else
            return p;
    }
    return NULL;
}