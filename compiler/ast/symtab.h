#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#define SYMTAB_QUEUE_SIZE 128 /* 符号表队列长度 */
#define MAX_SYS_ROUTINE (24) /* 系统程序的最多个数 */
#define make_global_symtab() new_symtab(NULL)

/* 保存常量的值 */
union _value_ {
    char c;
    unsigned char uc;
    char *s;
    int i;
    unsigned int ui;
    float f;
    boolean b;

    long l;
    unsigned long u;
    long double d;
    
    void *p;
    void (*g)(void);
};

typedef union _value_ value;
typedef union _value_ *Value;

typedef struct _symbol_ symbol;
typedef struct _symbol_ *Symbol;

typedef struct _type_ type;
typedef struct _type_ *Type;

/* 实例标识类型符的表项 */
struct _symbol_
{
    /* 标识符名称 */
    char name[NAME_LEN]; 
    /* 标识符的属性 */
    int defn;
    /* 标识符类型 */
    Type type;
    /* 变量在堆栈中的偏移量 */
    int offset;
    /* 常量的值 */
    value v;
    /* 下一个symbol */
    struct _symbol_ *next;
    /* 二叉树组织 */
    struct _symbol_ *lchild, *rchild;
    /* 指向符号表的表头结构 */
    struct _symbol_head_ *tab;
    /* 同一种类型的下一个symbol */
    struct _type_ *type_link;
};

/* 标识类型符的表项 */
struct _type_
{
    /* 类型的名字 */
    char name[NAME_LEN];
    /* 类型的序号 */
    int type_id;
    /* 类型结构中元素的个数 */
    int num_ele;
    /* 类型的字节数 */
    int size;
    /* 对齐字节数 */
    int align;
    /* 结构类型中的第一个元素 */
    symbol *first;
    /* 结构类型中的最后一个元素 */
    symbol *last;
    /* 组织类型标识符的链表 */
    struct _type_ *next;
    /* 指向符号表的表头结构 */
    struct _symbol_head_ *tab;
};

/* 符号表的表头 */
struct _symbol_head_
{
    /* 符号表的名称 */
    char name[NAME_LEN];
    /* 过程或函数的序号 */
    int id;
    /* 嵌套深度 */
    int level;
    /* 属性值（PROG、FUNCT、PROC之一） */
    int defn;
    /* 过程或函数的返回值（过程返回TYPE-VOID） */
    Type type;
    /* 局部变量的总字节数 */
    int call_stack_size;
    /* 局部参数链表 */
    symbol *args;
    /* 局部符号表（变量和参数），二叉树的根 */
    symbol *localtab;
    /*  */
    symbol *return_sym;
    /* 类型链接 */
    type *type_link;
    /* 函数或者过程的数量 */
    int last_symtab;
    /* 函数或者过程 */
    struct _symbol_head_ *routine_queue[SYMTAB_QUEUE_SIZE];
    /* 链接上一层符号表，即父辈函数过程的定义 */
    struct _symbol_head_ *parent;
};

typedef struct _symbol_head_ symtab;
typedef struct _symbol_head_ *Symtab;

/* 全局符号表 */
symtab *Global_symtab;
/* 系统符号表 */
symtab *System_symtab[MAX_SYS_ROUTINE];

symtab *new_symtab(symtab *);
symtab *new_sys_symbol(KEYENTRY);
symtab *find_routine(symtab *, char *);
symtab *find_sys_routine(int);
symtab *pop_symtab_stack();
symtab *top_symtab_stack();
symbol *find_symbol(symtab *, char *);
symbol *find_field(symbol *, char *);
symbol *find_local_symbol(symtab *, char *);
symbol *new_symbol(char *, int , int);
symbol *clone_symbol(symbol *);
symbol *clone_symbol_list(symbol *);

void push_symtab_stack(symtab *);
void add_routine_to_table(symtab *, symtab *);
void add_symbol_to_table(symtab *, symbol *);
void add_local_to_table(symtab *, symbol *);
void add_args_to_table(symtab *, symbol *);
void add_var_to_localtab(symtab *, symbol *);
void add_enum_elements(type *, symbol *symlist);
void add_type_to_table(symtab *ptab, type *pt);
void set_subrange_bound(type *, int , int );
type *new_system_type(int);
type *new_subrange_type(char *, int);
type *new_enum_type(char *);
type *new_record_type(char *,symbol *);
type *clone_type(type *);
type *find_type_by_name(char *);
type *find_type_by_id(int);
type *find_local_type(char *);
int is_symbol(symbol *p, char *);
int get_symbol_align_size(symbol *);

int stoi(char *s,int radix);
void set_subrange_bound(type *pt,int lower,int upper);
void add_enum_elements(type *pt, symbol *symlist);
type *new_array_type(char *name,type *pindex, type *pelement);

void make_system_symtab();
symbol *reverse_parameters(symtab *);
#endif

