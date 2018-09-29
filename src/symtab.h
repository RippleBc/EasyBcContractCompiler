#ifndef		_SYMTAB_H
#define 	_SYMTAB_H

//#include "common.h"
//#include "type.h"

union _value_ {
    char c;
    char *s;
    int i;
    float f;
    boolean b;
    long l;
    unsigned long u;
    long double d;
    void *p;
    void (*g)(void);
};

typedef union _value_ value;
typedef union _value_ * Value;

typedef struct _symbol_ symbol;
typedef struct _symbol_ * Symbol;

typedef struct _type_ type;
typedef struct _type_ * Type;

struct _symbol_
{
    char name[NAME_LEN];
    char rname[LABEL_LEN];
    int defn;			/* defined in. */
    /* int type; */
    Type type;			/* data type. */
    int offset;
    value v;
    struct _symbol_ *next;
    struct _symbol_ *lchild, *rchild;
    struct _symbol_head_ *tab;
    struct _type_	*type_link;
};

struct _type_
{
    char name[NAME_LEN];
    int type_id;
    int num_ele;
    int size;
    int align;
    symbol *first;
    symbol *last;
    struct _type_ *next;
};


struct _symbol_head_
{
    char name[NAME_LEN];
    char rname[LABEL_LEN];
    int id;
    int level;
    int defn;
    /* int type; */
    Type type;
    int local_size;
    int args_size;
    symbol *args;
    symbol *localtab;
    symbol *locals;
    type *type_link;
    struct _symbol_head_ *parent;
};

typedef struct _symbol_head_ symtab;
typedef struct _symbol_head_ * Symtab;

#define make_global_symtab() new_symtab(NULL)

#define MAX_SYS_ROUTINE		(24)

int Cur_level;
int Routing_id;

symtab *Global_symtab;
symtab *System_symtab[MAX_SYS_ROUTINE];
symtab *new_symtab(symtab *);
symtab *make_system_table();
symtab *new_sys_symbol(KEYENTRY);
symtab *find_routine(char *);
symtab *find_sys_routine(int);
symtab *pop_symtab_stack();
symtab *top_symtab_stack();
symbol *find_symbol(symtab *, char *);
symbol *find_element(symtab *, char *);
symbol *find_field(symbol *, char *);
symbol *find_local_symbol(symtab *, char *);
symbol *new_symbol(char *, int , int );
symbol *clone_symbol(symbol *);
symbol *clone_symbol_list(symbol *);

void push_symtab_stack(symtab *);
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
int get_symbol_size(symbol *);
int get_type_size(type *);

int stoi(char *s,int radix);
void set_subrange_bound(type *pt,int lower,int upper);
void add_enum_elements(type *pt, symbol *symlist);
type *new_array_type(char *name,type *pindex, type *pelement);
type *find_local_type_by_name(char *name);

int align(int);
void make_system_symtab();
symbol *reverse_parameters(symtab *);

#endif

