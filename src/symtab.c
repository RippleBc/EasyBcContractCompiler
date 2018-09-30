#define   SYMTABC
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>
#include  "common.h"
#include  "error.h"
#include  "symtab.h"

#include  _YTAB_H_
#define  SYMTAB_QUEUE_SIZE 128 /* 符号表队列长度 */
#define  SYMTAB_STACK_SIZE 64 /* 符号表栈深度 */

int const_index;
int var_index;
int arg_index;

int cur_level;
int routine_id;
int align(int);
int symtab_tos = SYMTAB_STACK_SIZE - 1;

int last_symtab = 0;
symtab *symtab_queue[SYMTAB_QUEUE_SIZE]; /* 存放已经处理完毕的symtab */

symtab *symtab_stack[SYMTAB_STACK_SIZE]; /* 存放还未处理的symtab，处理完毕之后，放入symtab_queue中 */

symtab *Global_symtab; /* 全局符号表 */
symtab *System_symtab[MAX_SYS_ROUTINE]; /* 系统符号表 */

extern int Keytable_size;

/* 用于对齐，符号的字节大小必须是偶数 */
int align(int bytes)
{
    while (bytes % 2)
        bytes++;
    return bytes;
}

/* 将处理完毕的symtab放入symtab_queue中 */
void enter_symtab_queue(symtab *tab)
{
    if (last_symtab < SYMTAB_QUEUE_SIZE)
        symtab_queue[last_symtab ++] = tab;
}

/* 创建一个未初始化的symtab对象 */
symtab *new_symtab(symtab *parent)
{
    symtab *p;

    /* p = (symtab *)malloc(sizeof(symtab));，然后把p所指向的内存空间的内容置为'0' */
    NEW0(p, PERM);

    if(!p)
        internal_error("insufficient memory.");

    p->parent = parent;
    p->args_size = 0; /* 参数的总字节数 */
    p->args = NULL; /* 参数链表 */
    p->localtab = NULL; /* 局部符号表（参数和变量），二叉树 */
    p->locals = NULL; /* 局部变量链表 */
    p->type_link = NULL; /* 过程或者函数返回值的类型链接 */
    if(parent)
    {
        p->level = parent->level + 1;
    }
    else
    {
        routine_id = 0;
        Global_symtab = p;
        Cur_level = 0;
        p->level = 0;
    }
    p->defn = DEF_UNKNOWN; /* 是PROC、FUNCT或者PROG */
    p->type = find_type_by_id(TYPE_VOID); /* 过程或者函数返回值的类型（普通类型） */
    p->id = routine_id++; /* 过程或者函数的序号 */
    p->local_size = 0; /* 局部变量的总字节数 */
    enter_symtab_queue(p);
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
        internal_error("insuffceent memory.");

    if(!strcmp(name,"$$$"))
        /* name == "$$$" */
        sprintf(p->name,"z%d",++imp_index);
    else
        strncpy(p->name, name, NAME_LEN);

    p->rname[0]= '\0'; /* 汇编阶段赋值 */
    p->defn = defn; /* 属性 */
    p->type = find_type_by_id(type_id); /* symbol的类型 */
    p->offset = 0; /* 在堆栈中的偏移量 */
    p->next = NULL; /* 用于局部变量链表以及参数链表 */
    p->lchild = p->rchild = NULL; /* 用于符号表（变量或者参数），二叉树 */
    p->tab = NULL; /* 指向符号表的表头 */
    p->type_link = NULL; /* 过程或者函数返回值的类型链接 */

    return p;

}

/* 克隆name、rname、defn、type以及v（表示具体数值，与type组合使用）字段 */
symbol *clone_symbol(symbol *origin)
{
    symbol *p;
    if(!origin)
        return NULL;

    /* p = (symbol *)malloc(sizeof(symbol)); */
    NEW0(p, PERM);
    if(!p)
        internal_error("insuffident memory.");

    strncpy(p->name, origin->name, NAME_LEN);
    strncpy(p->rname, origin->rname, LABEL_LEN);
    p->defn = origin->defn;
    p->type = origin->type;
    p->offset = 0;
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
    symbol *q;

    if(!head)
        return NULL;
    q = head;

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

/* 参数链表反转（采用跟随法，无需重新分配内存） */
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

void add_symbol_to_table(symtab*tab, symbol *sym)
{
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
        /* 值参（一个常量）、变参（一个变量） */
        add_args_to_table(tab,sym);
        break;
    case DEF_PROG:
    default:
        break;
    }
}

void add_var_to_localtab(symtab *tab, symbol *sym)
{
    symbol *p;
    int i;

    if (!tab || !sym)
        return;

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
            parse_error("Duplicate identifier.", sym->name);
            break;
        }
    }
}

/* 添加局部变量到symtab中 */
void add_local_to_table(symtab *tab, symbol *sym)
{
    if(!tab || !sym)
        return;

    if(sym->defn == DEF_CONST)
        /* 计算rname，rname的形式为 c+name+'_'+const_index（cN_000、cN_001）。
         %03d表示右边对齐，左边不足3位的用0进行填充。 */
        sprintf(sym->rname, "c%c_%03d", sym->name[0], new_index(const));
    else
        sprintf(sym->rname, "v%c_%03d", sym->name[0], new_index(var));

    if(tab->level)
    {
        if(tab->defn == DEF_FUNCT
                && sym->defn != DEF_FUNCT)
        {
            /* symtab为函数，记录局部变量在symtab中偏移量 */
            sym->offset = tab->local_size + 3 * IR->intmetric.size;
            /* 计算symtab中局部变量所占用的空间 */
            tab->local_size += align(get_symbol_size(sym));
        }
        else if (tab->defn == DEF_PROC
                 && sym->defn != DEF_PROC)
        {
            sym->offset = tab->local_size + IR->intmetric.size;
            tab->local_size += align(get_symbol_size(sym));
        }
    }

    /* 添加sym到局部变量链表中，从头部插入 */
    sym->next = tab->locals;
    tab->locals = sym;
    sym->tab = tab;

    /* 将局部变量插入局部符号表中 */
    add_var_to_localtab(tab, sym);
}

void add_args_to_table(symtab *tab, symbol *sym)
{
    symbol *p;
    int var_size;
    if(!tab || !sym)
        return;

    /* 添加sym到局部参数链表中，从头部插入 */
    sym->next = tab->args;
    tab->args = sym;
    sym->tab = tab;

    /* 计算局部变量在symtab中的偏移量 */
    sym->offset = 3 * IR->intmetric.size;
    /* 计算rname，形式为aN_000、aN_001 */
    sprintf(sym->rname, "a%c_%03d", sym->name[0], new_index(arg));
    /* 计算symtab中参数所占用的空间 */
    var_size = align(get_symbol_size(sym));
    tab->args_size += var_size;

    /* 重新计算其他参数在symtab中的偏移量 */
    for(p = tab->args->next; p; p = p->next)
        p->offset += var_size;

    /* 将局部参数插入局部符号表中 */
    add_var_to_localtab(tab, sym);
}

extern KEYENTRY Keytable[];

void make_system_symtab()
{
    int i;
    symtab *ptab;
    type *pt;

    for(i = 0; i < MAX_SYS_ROUTINE; i++)
        System_symtab[i] = NULL;


    /* ptab = (symtab*)malloc(sizeof(symtab)); */
    NEW0(ptab, PERM);
    if(!ptab)
        internal_error("Insuflicent memory. ");

    System_symtab[0] = ptab;

    sprintf(ptab->name,"system_table");
    sprintf(ptab->rname, "null");

    /* 初始化类型符号表 */
    ptab->type_link = new_system_type(TYPE_INTEGER);
    pt = ptab->type_link;
    pt->next = new_system_type(TYPE_CHAR);
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

    push_symtab_stack(ptab);

    ptab->id = -1;
    ptab->level = -1;
    ptab->defn = DEF_UNKNOWN; /* 属性值 */
    ptab->type = TYPE_UNKNOWN; /* 函数或者过程的返回类型 */ 
    ptab->local_size = 0;
    ptab->args_size = 0;
    ptab->args = NULL;
    ptab->parent = NULL;
    ptab->locals = new_symbol("", DEF_UNKNOWN, TYPE_UNKNOWN);

    /* 初始化系统函数以及系统过程调用 */
    int n = 1;
    for(i = 0 ; i < Keytable_size; i++)
    {
        if(Keytable[i].key == SYS_FUNCT ||
                Keytable[i].key == SYS_PROC )
        {
            System_symtab[n]=
                new_sys_symbol(Keytable[i]);
            n++;
        }
        else if (Keytable[i].key == LAST_ENTRY)
            break;
    }

    pop_symtab_stack();
    
    ptab->local_size = n;
}

symtab* new_sys_symbol(KEYENTRY entry)
{
    symtab *ptab;
    symbol *p;

    /* ptab = (symtab*)malloc(sizeof(symtab)); */
    NEW0(ptab, PERM);

    if(!ptab)
        internal_error("Insufticent  memoy.");

    strcpy(ptab->name, entry.name);

    sprintf(ptab->rname, "_f_%s", entry.name);

    ptab->id = -entry.attr;
    ptab->level = -1;
    ptab->defn = DEF_FUNCT;
    ptab->type = find_type_by_id(entry.ret_type);
    ptab->local_size = 0;
    ptab->args_size = 0;
    ptab->args = NULL;
    ptab->localtab = NULL;
    ptab->locals = NULL;
    ptab->parent = System_symtab[0];

    /* p = (symbol*)malloc(sizeof(symbol)); */
    NEW0(p, PERM);

    if(!p)
        internal_error("Insufticent memory.");

    strcpy(p->name, ptab->name);
    strcpy(p->rname, ptab->rname);
    p->defn = DEF_FUNCT;
    p->type = find_type_by_id(entry.ret_type);
    p->offset = 0;
    p->next = NULL;
    p->tab = ptab;
    p->type_link = NULL;
    ptab->locals = p;
    if(entry.arg_type)
    {
        /* p = (symbol*)malloc(sizeof(symbol)); */
        NEW0(p, PERM);

        if(!p)
            internal_error("Insufficent memory.");
        strcpy(p->name, "arg");
        p->defn =DEF_VALPARA;
        p->type = find_type_by_id(entry.arg_type);
        add_args_to_table(ptab,p);
    }
    return ptab;
}

int is_symbol(symbol*p,char*name)
{
    if(strcmp(p->name,name))
        return  0;
    return 1;
}

int get_symbol_size(symbol *sym)
{
    switch(sym->type->type_id)
    {
    case TYPE_INTEGER:
        return  IR->intmetric.size;
    case TYPE_CHAR:
        return  IR->charmetric.size;
    case TYPE_BOOLEAN:
        return  IR->intmetric.size;
    case TYPE_REAL:
        return  IR->floatmetric.size;
    case TYPE_STRING:
        return size(CHAR) * (strlen(sym->v.s) + 1);
    case TYPE_ARRAY:
        /* 用户自定义类型，需要从_type_链表中寻找 */
        return  get_type_size(sym->type_link);
    case TYPE_RECORD:
        /* 用户自定义类型，需要从_type_链表中寻找 */
        return get_type_size(sym->type_link);
    case TYPE_UNKNOWN:
        internal_error("Unknown type.");
        break;
    default:
        break;
    }
    return 0;
}

symtab *pop_symtab_stack()
{
    if(symtab_tos == SYMTAB_STACK_SIZE)
        internal_error("Symtab stack underflow.");
    return symtab_stack[++symtab_tos];
}
void push_symtab_stack (symtab *tab)
{
    if(symtab_tos == -1)
        internal_error("Symtab stack overflow.");
    else
        symtab_stack[symtab_tos--] = tab;
}

symtab *top_symtab_stack()
{
    return symtab_stack[symtab_tos + 1];
}

symtab *find_routine(char *name)
{
    int i;
    symtab *ptab;
    for(i=0;i<last_symtab;i++)
    {
        ptab = symtab_queue[i];
        if(!strcmp(ptab->name,name))
            return ptab;
    }
    return NULL;
}

symtab *find_sys_routine(int routine_id)
{
    int i;
    for(i = 1; i < System_symtab[0]->local_size; i++)
        if(System_symtab[i]->id == -routine_id)
            return System_symtab[i];
    return NULL;
}

symbol *find_element(symtab *tab,char *name)
{
    symbol *p;
    symtab *ptab = tab;
    type *pt;
    while(ptab)
    {
        for(pt = ptab->type_link; pt; pt = pt->next)
            for(p = pt->first; p; p = p->next)
                if(is_symbol(p,name))
                    return p;
        ptab = ptab->parent;
    }
    return NULL;
}

symbol *find_field(symbol *p,char *name)
{
    type *pt;
    symbol *q;

    if(!p || p->type->type_id != TYPE_RECORD)
        return NULL;
    pt = p->type_link;
    for(q = pt->first; q; q = q->next)
        if(is_symbol(q, name))
            return q;

    return NULL;
}

symbol *find_symbol(symtab *tab,char *name)
{
    symbol *p;
    symtab *ptab = tab;
    type *pt;

    if(!ptab)
    {
        p = System_symtab[0]->locals;
        p->type = TYPE_UNKNOWN;
        return p;
    }
    while(ptab)
    {
        p = find_local_symbol(ptab,name);
        if(p)
            return p;
        for(pt = ptab->type_link; pt; pt=pt->next)
            for(p = pt->first; p; p = p->next)
                if(is_symbol(p,name))
                    return p;
        ptab = ptab->parent;
    }
    return NULL;
}
symbol *find_local_symbol(symtab *tab, char *name)
{
    symbol *p;
    symtab *ptab = tab;
    int i;
    if(!ptab)
        return NULL;
    if(!ptab->localtab)
        return NULL;
    p = ptab->localtab;
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

