/**
 * for backend without generate ast forest.
 */
#define  X86_DOS
#include  <stdio.h>
#include  "common.h"
#include  "symtab.h"
#include  "error.h"
#include  "x86.h"

#ifdef _MSDOS_
#include  <dos.h>
#elif defined __linux__
#include <time.h>
#endif

#include  _YTAB_H_
#define  MAX_LOOP_LEVEL  16
#define  STMT_STACK_SIZE 64
#define  MAX_CALL_LEVEL 16

#ifdef GENERATE_AST
#define STATIC static
#else
#define STATIC
#endif

/*
static Symbol	p;
static Symtab	ptab;
*/

static symtab *rtn =NULL;
static symbol *arg = NULL;

STATIC int sym_tos = MAX_LOOP_LEVEL-1;
STATIC int direc_stk[MAX_LOOP_LEVEL];
STATIC int dir_tos = MAX_LOOP_LEVEL-1;
STATIC int stmt_tos = STMT_STACK_SIZE - 1;
STATIC int stmt_stack[STMT_STACK_SIZE];
STATIC symbol *sym_stk[MAX_LOOP_LEVEL];
STATIC int stmt_index = 0;
STATIC int call_tos = MAX_CALL_LEVEL-1;
STATIC symbol *call_sym[MAX_CALL_LEVEL];
STATIC symtab *call_stk[MAX_CALL_LEVEL];

STATIC void emit_write1(int arg_type);
STATIC void emit_sqrt(int arg_type);
STATIC void emit_odd(int arg_type);
STATIC void emit_abs(int arg_type);
STATIC void emit_sqr(int arg_type);
STATIC void emit_read1(int arg_type);
STATIC void emit_writeln(int arg_type);

STATIC symbol *do_function_call(symtab *);
STATIC void emit_program_head();
STATIC void emit_program_prologue(symtab *);
STATIC void emit_program_epilogue(symtab *);
STATIC void emit_main_prologue(symtab *);
STATIC void emit_main_epilogue(symtab *);
STATIC void emit_routine_prologue(symtab *);
STATIC void emit_routine_epilogue(symtab *);
STATIC void emit_local_args(symtab *);
STATIC void emit_push_op(int);
STATIC void emit_load_value(symbol *);
STATIC void do_function_assign(symtab *,int);
STATIC void do_procedure_call(symtab *);
STATIC void do_assign(symbol *, int);
STATIC void do_if_test();
STATIC void do_if_caluse();
STATIC void do_if_exit();
STATIC void do_repeat_start();
STATIC void do_repeat_exit();
STATIC void do_while_start();
STATIC void do_while_expr();
STATIC void do_while_exit();
STATIC void do_for_start(symbol *);
STATIC void do_for_test(int);
STATIC void do_for_exit();
STATIC void do_expression(symbol *, int);
STATIC void do_negate(symbol *);
STATIC void do_expr(symbol *, int);
STATIC void do_term(symbol *, int);
STATIC void do_factor(symbol *);
STATIC void do_no_factor(symbol *);
STATIC void do_array_factor(symbol *);
STATIC void do_record_factor(symbol *, symbol *);
STATIC void do_first_arg(int);
STATIC void reset_args(symtab *);
STATIC void push_stmt_stack(int);
STATIC int pop_stmt_stack();
STATIC int top_stmt_stack();
STATIC int rout_index = 0;

STATIC void do_sys_routine(int routine_id, int arg_type)
{

    switch(routine_id)
    {
    case fABS:
        emit_abs(arg_type);
        break;
    case fODD:
        emit_odd(arg_type);
        break;
    case  fPRED:
        fprintf(codfp, "\t\tdec\tax\n");
        break;
    case  fSQR:
        emit_sqr(arg_type);
        break;
    case fSQRT:
        emit_sqrt(arg_type);
        break;
    case fSUCC:
        fprintf(codfp, "\t\tinc\tax\n");
        break;
    case pREAD:
        emit_read1(arg_type);
        break;
    case pREADLN:
        emit_read1(arg_type);
        break;
    case pWRITE:
        emit_write1(arg_type);
        break;
    case  pWRITELN:
        emit_writeln(arg_type);
        break;
    default:
        break;
    }
}

STATIC void emit_read1(int arg_type)
{
    fprintf(codfp, "\t\tpush\tax\n");
    fprintf(codfp, "\t\tpush\tbp\n");
    switch(arg_type)
    {
    case  TYPE_REAL:
        break;
    case  TYPE_INTEGER:
        fprintf(codfp, "\t\tcall\t_read_int\n");
        break;
    case TYPE_STRING:
        fprintf(codfp, "\t\tcall\t_read_string\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\tcall\t_read_char\n");
        break;
    case   TYPE_BOOLEAN:
    default:
        parse_error("operand type do not match operator.", "");
        break;
    }
}

STATIC void emit_write1(int arg_type)
{
    switch(arg_type)
    {
    case TYPE_INTEGER:
	case TYPE_BOOLEAN:
        fprintf(codfp, "\t\tpush\tax\n");
        fprintf(codfp, "\t\tpush\tbp\n");
        fprintf(codfp, "\t\tcall\t_write_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\tmov\tdl,al\n");
        fprintf(codfp, "\t\tmov\tah,2\n");
        fprintf(codfp, "\t\tint\t21h\n");
        break;
    case TYPE_STRING:
        fprintf(codfp, "\t\tpush\tax\n");
        fprintf(codfp, "\t\tpush\tbp\n");
        fprintf(codfp, "\t\tcall\t_write_string\n");
        break;
    default:
        break;
    }
}

STATIC void emit_writeln(int arg_type)
{
    switch(arg_type)
    {
    case TYPE_INTEGER:
	case TYPE_BOOLEAN:
        fprintf(codfp, "\t\tpush\tax\n");
        fprintf(codfp, "\t\tpush\tbp\n");
        fprintf(codfp, "\t\tcall\t_writeln_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\tmov\tdl,al\n");
        fprintf(codfp, "\t\tmov\tah,2\n");
        fprintf(codfp, "\t\tint\t21h\n");
        fprintf(codfp, "\t\tmov\tdl,13\n");
        fprintf(codfp, "\t\tint\t21h\n");
        fprintf(codfp, "\t\tmov\tdl,10\n");
        fprintf(codfp, "\t\tint\t21h\n");
        break;
    case  TYPE_STRING:
        fprintf(codfp, "\t\tpush\tax\n");
        fprintf(codfp, "\t\tpush\tbp\n");
        fprintf(codfp, "\t\tcall\t_writeln_string\n");
        break;
    default:
        break;
    }
}

STATIC void emit_abs(int arg_type)
{
    fprintf(codfp, "\t\tpush\tbp\n");
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tcall\t_abs_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\txor\tah,ah\n");
        fprintf(codfp, "\t\tcall\t_abs_int\n");
        break;
    default:
        break;
    }
}

STATIC void emit_sqr(int arg_type)
{
    fprintf(codfp, "\t\tpush\tbp\n");
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tcall\t_sqr_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\txor\tah,ah\n");
        fprintf(codfp, "\t\tcall\t_sqr_int\n");
        break;
    default:
        break;
    }
}

STATIC void emit_odd(int arg_type)
{
    fprintf(codfp, "\t\tpush\tbp\n");
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tcall\t_odd_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\txor\tah,ah\n");
        fprintf(codfp, "\t\tcall\t_odd_int\n");
        break;
    default:
        break;
    }
}

STATIC void emit_sqrt(int arg_type)
{
    fprintf(codfp, "\t\tpush\tbp\n");
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tcall\t_sqrt_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\txor\tah,ah\n");
        fprintf(codfp, "\t\tcall\t_sqrt_int\n");
        break;
    default:
        break;
    }
}

STATIC void emit_program_prologue(symtab *ptab)
{
    fprintf(codfp, " \n;alloc stack space\n");
    fprintf(codfp, " \t\tdb\t0%xh dup(?)\n"
            ,STACK_SEG_SIZE);
    fprintf(codfp,"\n_DATA\t\tends");
    fprintf(codfp,"\n\n;---program %s ---",ptab->name);
    fprintf(codfp,"\n\n_TEXT\t\tsegment\tpublic\n\n");
    fprintf(codfp,"\t\tinclude\tx86rtl.inc\n\n");
    fprintf(codfp,"%s\tequ\tword ptr [bp+04h]\n"
            ,LABEL_SLINK);
    fprintf(codfp,"%s\tequ\tword ptr [bp-04h]\n",
            LABEL_RETVAL);
    fprintf(codfp,"%s\tequ\tword ptr [bp-02h]\n",
            LABEL_HIRETVAL);
    emit_program_head();
    fprintf(datfp, " \n_DATA\t\tsegment\tpublic\n");
}

/* char datname[]; */
STATIC void emit_program_head()
{
#ifdef _MSDOS_
    struct dosdate_t d;
    struct dosdate_t t;
    _dos_getdate(&d);
    _dos_gettime(&t);
    fprintf(datfp,";%s\n;%02d:%02d:%02d/%d/%d/%d\n",
            t.hour,t.minute,t.second,d.month,d.day,d.year);
#elif defined __linux__

    time_t now;
    struct tm *tv;

    time(&now);
    tv = gmtime(&now);

    fprintf(datfp, ";%04d/%02d/%02d\n;%02d:%02d:%02d\n",
            tv->tm_year + 100, tv->tm_mon, tv->tm_mday,
            tv->tm_hour, tv->tm_min, tv->tm_sec);
#endif

    fprintf(datfp,";\n");
    fprintf(datfp,";SPL Compiler Ver %s\n",_PC_VER_);
	fprintf(datfp, "\n\n.MODEL SMALL\n");
}

STATIC void emit_program_epilogue(symtab *ptab)
{
    symbol *p;
    fprintf(codfp,"\n_TEXT\t\tends\n");
    fprintf(codfp,"\t\tend\tstart\n\n");

    fprintf(datfp,"\n;global variables\n");

    for(p = ptab->locals; p; p = p->next)
    {
        switch (p->type->type_id)
        {
        case 	TYPE_CHAR:
            fprintf(datfp,"%s\t\tdb\t",p->rname);
            break;
		case	TYPE_BOOLEAN:
        case 	TYPE_INTEGER:
            fprintf(datfp,"%s\t\tdw\t",p->rname);
            break;
        case 	TYPE_REAL:
            fprintf(datfp,"%s\t\tdd\t",p->rname);
            break;
        case 	TYPE_STRING:
            fprintf(datfp,"%s\t\tdb\t%s\n",p->rname,
                    p->v.s);
            fprintf(datfp,"\t\tdb\t'$'\n");
            break;
        case TYPE_ARRAY:
            if(p->type_link->last->type->type_id == TYPE_INTEGER
                    || p->type_link->last->type->type_id == TYPE_BOOLEAN)
                fprintf(datfp,"%s\t\tdw\t0%xh dup (?)\n"
                    ,p->rname,p->type_link->num_ele);
            else if(p->type_link->last->type->type_id ==
                    TYPE_CHAR)
                fprintf(datfp,"%s\t\tdb\t0%xh dup (?)\n"
                    ,p->rname,p->type_link->num_ele);
            else
                parse_error("complex array element not supported","");
            if(p->defn != DEF_CONST)
                continue;
            break;
        case   TYPE_RECORD:
            fprintf(datfp,"%s\t\tdb\t0%xh dup (?)\n"
                    ,p->rname,p->type_link->size);
            continue;
        default:
            break;
        }

        if (p->defn == DEF_CONST)
        {
            switch(p->type->type_id)
            {
            case TYPE_CHAR:
                fprintf(datfp,"'%c'\n",p->v.c);
                break;
            case TYPE_INTEGER:
                if (p->v.i >= 0)
                    fprintf(datfp, "0%xh\n", p->v.i);
                break;
            case TYPE_REAL:
                fprintf(datfp, "%g\n", p->v.f);
                break;
            case TYPE_STRING:
                break;
            default:
                fprintf(datfp,"?\n");
            }
        }
        else
            fprintf(datfp,"?\n");
    }
}

STATIC void emit_main_prologue(symtab *ptab)
{
    fprintf(codfp,"\n\n; --- main routine ----\n");
    fprintf(codfp,"_main\t\tproc\tfar\n");
    fprintf(codfp,"\t\tassume\tcs:_TEXT,ds:_DATA\n");
    fprintf(codfp,"start:\n");
    fprintf(codfp,"\t\tpush\tds\n");
    fprintf(codfp,"\t\tsub\tax,ax\n");
    fprintf(codfp,"\t\tpush\tax\n");
    fprintf(codfp,"\t\tmov\tax,_DATA\n");
    fprintf(codfp,"\t\tmov\tds,ax\n");
}

STATIC void emit_main_epilogue(symtab *ptab)
{
    fprintf(codfp,"\t\tret\n");
    fprintf(codfp,"_main\t\tendp\n");
}

STATIC void emit_routine_prologue(symtab *ptab)
{
    if(ptab->defn == DEF_PROG)
        return;
    fprintf(codfp,"\n\n; routine : %s \n",ptab->name);
    emit_local_args(ptab);
    fprintf(codfp,";routine code\n");
    fprintf(codfp,"%s\t\tproc\n", ptab->rname);
    fprintf(codfp,"\t\tassume\tcs:_TEXT,ds:_DATA\n");
    fprintf(codfp,"\t\tmov\tax,_DATA\n");
    fprintf(codfp,"\t\tmov\tds,ax\n");
    fprintf(codfp,"\t\tpush\tbp\n");
    fprintf(codfp,"\t\tmov\tbp,sp\n");
    if(ptab->defn == DEF_FUNCT)
        fprintf(codfp,"\t\tsub\tsp, 4\n");
    fprintf(codfp,"\t\tsub\tsp,%04xh\n",ptab->local_size);
}

STATIC void emit_local_args(symtab *ptab)
{
    symbol *p;
    char tp[10];
    fprintf(codfp,";local variables in %s\n",ptab->name);
    for(p = ptab->locals; p->next; p = p->next)
    {
        switch(p->type->type_id)
        {
        case TYPE_CHAR:
            sprintf(tp, "byte  ptr");
            break;
        case TYPE_INTEGER:
        case TYPE_BOOLEAN:
            sprintf(tp, "word  ptr");
            break;
        case TYPE_REAL:
            sprintf(tp, "dword  ptr");
            break;
        case TYPE_ARRAY:
            if(p->type_link->last->type->type_id ==
                    TYPE_INTEGER
                    || p->type_link->last->type->type_id ==
                    TYPE_BOOLEAN)
                sprintf(tp, "word	ptr");
            else if (p->type_link->last->type->type_id == TYPE_CHAR)
                sprintf(tp, "byte	ptr");
            break;
        case TYPE_RECORD:
            sprintf(tp, "byte  ptr");
            break;
        default:
            break;
        }
        fprintf(codfp,"	%s\t\tequ\t%s	[bp-%04xh]\n",
                p->rname,tp,p->offset);
    }

    fprintf(codfp,"; arguments in %s\n", ptab->name);
    for(p =ptab->args;p ;p = p->next)
    {
        switch(p->type->type_id)
        {
        case    TYPE_CHAR:
            sprintf(tp, "byte  ptr");
            break;
        case    TYPE_INTEGER:
        case    TYPE_BOOLEAN:
            sprintf(tp, "word  ptr");
            break;
        case    TYPE_REAL:
            sprintf(tp, "dword  ptr");
            break;
        default:
            break;
        }
        fprintf(codfp,"%s\t\tequ\t%s	[bp+%04xh]\n",
                p->rname,tp,p->offset);
    }
}

STATIC void emit_routine_epilogue(symtab *ptab)
{
    if(ptab->defn == DEF_PROG)
        return;
    if(ptab->defn == DEF_FUNCT)
    {
        switch(ptab->type->type_id)
        {
        case  TYPE_INTEGER:
        case  TYPE_BOOLEAN:
            fprintf(codfp,"\n\t\tmov\tax, word ptr %s\n",LABEL_RETVAL);
            break;
        case  TYPE_CHAR:
            fprintf(codfp,"\n\t\tmov\tah, 0\n");
            fprintf(codfp,"\n\t\tmov\tax, byte  ptr %s\n",
                    LABEL_RETVAL);
            break;
        case  TYPE_REAL:
            fprintf(codfp,"\n\t\tmov\tax,%s\n",
                    LABEL_RETVAL);
            fprintf(codfp,"\n\t\tmov\tdx,%s\n",
                    LABEL_HIRETVAL);
            break;
        }
    }
    fprintf(codfp,"\t\tmov\tsp,bp\n");
    fprintf(codfp,"\t\tpop\tbp\n");
    fprintf(codfp,"\t\tret\t%04xh\n",ptab->args_size + 2);
    fprintf(codfp,"\n%s\t\tendp\n",ptab->rname);
}

STATIC void emit_push_op(int ptype)
{
    switch(ptype)
    {
    case  TYPE_CHAR:
    case  TYPE_BOOLEAN:
    case  TYPE_INTEGER:
        fprintf(codfp,"\t\tpush\tax\n");
        break;
    case  TYPE_REAL:
        fprintf(codfp,"\t\tpush\tdx\n");
        fprintf(codfp,"\t\tpush\tax\n");
        break;
    }
}

STATIC void emit_load_value(symbol *p)
{
    if(p->defn==DEF_VARPARA)
    {
        fprintf(codfp,"\t\tmov\tbx,word ptr [bp+4]\n");
        switch(p->type->type_id)
        {
        case  TYPE_CHAR:
            fprintf(codfp,"\t\txor\tah, ah\n");
            fprintf(codfp,"\t\tmov\tal, byte ptr [bx]\n");
            break;
        case TYPE_REAL:
            fprintf(codfp,"\t\tmov\tax,word ptr [bx]\n");
            fprintf(codfp,"\t\tmov\tdx,word ptr [bx+2]\n");
            break;
        case  TYPE_INTEGER:
        case  TYPE_BOOLEAN:
            fprintf(codfp,"\t\tmov\tax,word ptr [bx]\n");
            break;
        }
    }
    else if (p->tab->level==0
             ||p->tab==top_symtab_stack())
    {
        switch(p->type->type_id)
        {
        case  TYPE_CHAR:
            fprintf(codfp,"\t\tsub\tax.ax\n");
            fprintf(codfp,"\b\t\tmov\tal, byte  ptr %s\n"
                    ,p->rname);
            break;
        case  	TYPE_REAL:
            fprintf(codfp,"\t\t\tmov\tax, word ptr %s\n",p->rname);
            fprintf(datfp,"\t\t\tmov\tdx, word ptr %s+2\n",p->rname);
            break;
        case  	TYPE_INTEGER:
        case  	TYPE_BOOLEAN:
            fprintf(codfp,"\t\t\tmov\tax, word ptr %s\n",p->rname);
            break;
        case  	TYPE_ARRAY:
            fprintf(codfp,"\t\tpop\tbx\n");
            if(p->type_link->last->type->type_id ==
                    TYPE_INTEGER
                    ||p->type_link->last->type->type_id ==
                    TYPE_BOOLEAN)
                fprintf(codfp, "\t\tmov\tax,word ptr [bx]\n");
            else if (p->type_link->last->type->type_id ==
                     TYPE_CHAR)
                fprintf(codfp, "\t\tmov\tal,byte ptr [bx]\n");
            break;
        default:
            break;
        }
    }
}

STATIC void emit_load_address(symbol *p)
{
    symtab *ptab;
    int  n,i;
    switch(p->defn)
    {
    case DEF_VARPARA:
        fprintf(codfp, "\t\tmov\tax,word ptr %s\n",
                p->rname);
        break;

    case DEF_VAR:
        if(p->tab->level==0
                || p->tab==top_symtab_stack())
        {
            fprintf(codfp, "\t\tlea\tax,word ptr %s\n",
                    p->rname);
        }
        else
        {
            ptab = top_symtab_stack();
            n = p->tab->level - ptab->level + 1;
            fprintf(codfp,"\t\tmov\tbx,bp\n");
            for (i = 0; i < n; i++)
                fprintf(codfp, "\t\tmov\tbp,%s\n",
                        LABEL_SLINK);
            fprintf(codfp, "\t\tlea\tax,word ptr %s\n",
                    p->rname);
            fprintf(codfp,"\t\tmov\tbp,bx\n");
        }
        break;
    case DEF_VALPARA:
        fprintf(codfp, "\t\tmov\tax,word ptr %s\n",
                p->rname);
        break;
    default:
        break;
    }
}

STATIC void emit_load_element()
{
    fprintf(codfp, "\t\tmov\tcx,ax\n");
    fprintf(codfp, "\t\tpop\tax\n");
    fprintf(codfp, "\t\tadd\tax,cx\n");
}

STATIC void emit_load_field(symbol*p)
{
    if(!p)
        return;
    fprintf(codfp, "\t\tpop\tbx\n");
    switch(p->type->type_id)
    {
    case  TYPE_INTEGER:
    case  TYPE_BOOLEAN:
        fprintf(codfp,"\t\tmov\tax,word ptr [bx]\n");
        break;
    case  TYPE_CHAR:
        fprintf(codfp,"\t\tmov\tal,byte ptr [bx]\n");
        break;
    default:
        break;
    }
}

STATIC int pop_stmt_stack()
{
    if(stmt_tos==STMT_STACK_SIZE)
        internal_error("Satement stack underflow.\n");
    return stmt_stack[++stmt_tos];
}

STATIC void push_stmt_stack(int index)
{
    if(stmt_tos==0)
        internal_error("Satement stack overflow.\n");
    stmt_stack[stmt_tos--] = index;
}

STATIC int top_stmt_stack()
{
    return stmt_stack[stmt_tos + 1];
}

STATIC void do_function_assign(symtab *ptab, int srctype)
{
    if(!ptab)
        return;

    if(ptab->type->type_id != srctype)
    {
        parse_error("operand type to not match operator.", "");
        return;
    }
    switch(ptab->type->type_id)
    {
    case  TYPE_CHAR:
        fprintf(codfp,"\t\txor\tah,ah\n");
        fprintf(codfp,"\t\tmov\tbyte ptr %s,al\n",
                LABEL_RETVAL);
        break;
    case  TYPE_BOOLEAN:
    case  TYPE_INTEGER:
        fprintf(codfp,"\t\tmov\tword ptr %s,ax\n",
                LABEL_RETVAL);
        break;
    case  TYPE_REAL:
        fprintf(codfp,"\t\tmov\tword ptr %s,ax\n",
                LABEL_RETVAL);
        fprintf(codfp,"\t\tmov\tword ptr %s,ax\n",
                LABEL_HIRETVAL);
        break;
    default:
        break;
    }
}

STATIC symbol *do_function_call(symtab *ptab)
{
    int i,n;
    symbol *p;
    symtab *caller;
    symtab *callee;

    caller = top_symtab_stack();
    callee = ptab;
    if(callee->defn != DEF_FUNCT)
    {
        parse_error("Undeclared function", callee->name);
        return NULL;
    }
    else if (callee->level == caller->level + 1)
    {
        fprintf(codfp,"\t\tpush\tbp\n");
    }
    else if (callee->level == caller->level)
    {
        fprintf(codfp,"\t\tpush\t%s\n",LABEL_SLINK);
    }
    else if (callee->level < caller->level)
    {
        fprintf(codfp,"\t\tmov\tbx,bp\n");
        n = caller->level - callee->level + 1;
        for(i =0; i<n; i++)
            fprintf(codfp, "\t\tmov\tbp,%s\n",
                    LABEL_SLINK);

        fprintf(codfp,"\t\tpush\tbp\n");
        fprintf(codfp,"\t\tmov\tbp,bx\n");
    }
    else
        return NULL;
    fprintf(codfp,"\t\tcall rtn%03d\n", callee->id);
    for(p = ptab->locals; p->next; p = p->next)
        ;
    return p;
}

STATIC void do_procedure_call(symtab *ptab)
{
    symtab *caller = top_symtab_stack();
    symtab *callee = ptab;
    int n ;
    int i ;

    if(!caller || !callee)
    {
        parse_error("Undeclared procedure","");
        return;
    }
    n = (callee->level) -(caller->level) + 1;
    if(callee->level==caller->level+1)
    {
        fprintf(codfp,"\t\tpush\tbp\n");
    }
    else if (callee->level == caller->level)
    {
        fprintf(codfp, "\t\tpush\t%s\n",
                LABEL_SLINK);
    }
    else if(callee->level < caller->level)
    {
        fprintf(codfp,"\t\tmov\tbx,bp\n");
        for(i = 0; i < n; i++)
            fprintf(codfp,"\t\tmov\tbp,%s\n",
                    LABEL_SLINK);
        fprintf(codfp,"\t\tpush\tbp\n");
        fprintf(codfp,"\t\tmov\tbp,bx\n");
    }
    else
        return;
    fprintf(codfp,"\t\tcall\t%s\n", ptab->rname);
}

STATIC void reset_args(symtab *ptab)
{
    rtn = ptab;
}

STATIC void do_first_arg(int ptype)
{
    rtn = top_call_stack();
    if(rtn)
        arg = rtn->args;
    else
        return;
    if(!arg)
        return;
    switch(arg->type->type_id)
    {
    case  TYPE_REAL:
        if (ptype!=TYPE_REAL)
            fprintf(codfp,"\t\txor\tdx,dx\n");
        fprintf(codfp,"\t\tpush\tdx\n");
        fprintf(codfp,"\t\tpush\tax\n");
        break;
    case  TYPE_CHAR:
        fprintf(codfp,"\t\txor\tah,ah\n");
    case  TYPE_INTEGER:
    case  TYPE_BOOLEAN:
    default:
        fprintf(codfp,"\t\tpush\tax\n");
        break;
    }
}

STATIC void do_args(int ptype)
{
    arg = top_call_symbol();

    if(arg->next)
        arg = arg->next;
    else
        return;
    set_call_stack_top(arg);
    switch(arg->type->type_id)
    {
    case  TYPE_REAL:
        if (ptype!=TYPE_REAL)
            fprintf(codfp,"\t\txor\tdx,dx\n");
        fprintf(codfp,"\t\tpush\tdx\n");
        fprintf(codfp,"\t\tpush\tax\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp,"\t\txor\tah.ah\n");
    case  TYPE_INTEGER:
    case  TYPE_BOOLEAN:
    default:
        fprintf(codfp,"\t\tpush\tax\n");
        break;
    }
}

STATIC void do_assign(symbol *p, int srctype)
{
    symtab *ptab;
    int  n,i;
    if (!p)
        return;

	if ((p->type->type_id != TYPE_ARRAY) 
			&& (p->type->type_id != TYPE_RECORD)
			&& (p->type->type_id != srctype))
    {
        parse_error("operand type do not match operator.","");
        return;
    }

    switch(p->defn)
    {
    case DEF_VARPARA:
        fprintf(codfp,"\t\tpush\tax\nn");
        fprintf(codfp,"\t\tmov\tax,word ptr %s\n",
                p->rname);
        break;
    case DEF_FIELD:
        fprintf(codfp,"\t\tpop\tbx\n");
        if(p->type->type_id==TYPE_INTEGER
                ||p->type->type_id==TYPE_BOOLEAN)
            fprintf(codfp,"\t\tmov\tword ptr [bx],ax\n");
        else if (p->type->type_id==TYPE_BOOLEAN)
            fprintf(codfp,"\t\tmov\tbyte ptr [bx],ax\n");
        return;
    case DEF_VAR:
    case DEF_CONST:
    case DEF_ELEMENT:
        if(p->type->type_id==TYPE_ARRAY)
        {
            fprintf(codfp,"\t\tpush\tax\n");
            break;
        }
        if(p->tab->level == 0
                ||p->type->type_id==TYPE_REAL)
            break;
        else if( p->tab->level
                 && p->tab == top_symtab_stack())
        {
            fprintf(codfp,"\t\tpush\tax\n");
            fprintf(codfp,"\t\tlea\tax,word ptr %s\n",
                    p->rname);
            fprintf(codfp,"\t\tpush\tax\n");
            break;
        }
        else
        {
            ptab = top_symtab_stack();
            n = ptab->level - p->tab->level;
            fprintf(codfp,"\t\tpush\tax\n");
            fprintf(codfp,"\t\tmov\tbx,bp\n");
            for(i =0;i<n;i++)
                fprintf(codfp,"\t\tmov\tbp,%s\n",
                        LABEL_SLINK);
            fprintf(codfp,"\t\tlea\tax,word ptr %s\n",
                    p->rname);
            fprintf(codfp,"\t\tmov\tbp,bx\n");
            fprintf(codfp,"\t\tpush\tax\n");
        }
        break;
    case DEF_VALPARA:
        if(p->tab->level==0
                || p->tab==top_symtab_stack())
            fprintf(codfp,"\t\tpush\tax\n");
        fprintf(codfp,"\t\tlea\tax,word ptr %s\n",
                p->rname);
        fprintf(codfp,"\t\tpush\tax\n");
        break;
    default:
        parse_error("lvalue expected.","");
        break;
    }

    switch(p->type->type_id)
    {
    case TYPE_CHAR:
        if(p->tab->level)
        {
            fprintf(codfp,"\t\tpop\tbx\n");
            fprintf(codfp,"\t\tpop\tax\n");
            fprintf(codfp,"\tmov\tbyte ptr [bx],al\n");
        }
        else
            fprintf(codfp,"\t\tmov\tbyte ptr %s,al\n",
                    p->rname);

        break;
    case TYPE_INTEGER:
    case TYPE_BOOLEAN:
        if (p->tab->level)
        {
            fprintf(codfp, "\t\tpop\tbx\n");
            fprintf(codfp, "\t\tpop\tax\n");
            fprintf(codfp, "\t\tmov\tword  ptr [bx],ax\n");
        }
        else
            fprintf(codfp, "\t\tmov\tword  ptr %s, ax\n",p->rname);
        break;

    case TYPE_STRING:
        fprintf(codfp, "\t\tmov\tex, %04xh\n",
                strlen(p->v.s));
        fprintf(codfp, "\t\tpop\tpop\tsi\n");
        fprintf(codfp, "\t\tpop\tdi\n");
        fprintf(codfp, "\t\tmov\tax,ds");
        fprintf(codfp, "\t\tmov\tes,ax");
        fprintf(codfp, "\t\tcld\n");
        fprintf(codfp, "\t\trep\tmovsb\n");
        break;
    case TYPE_REAL:
        fprintf(codfp, "\t\tmov\tax,%s\n",p->rname);
        fprintf(codfp, "\t\tmov\tdx,%s+2n",p->rname);
        break;
    case TYPE_ARRAY:
        if (p->type_link->last->type->type_id == TYPE_INTEGER
                ||p->type_link->last->type->type_id == TYPE_BOOLEAN )
        {
            fprintf(codfp, "\t\tpop\tax\n");
            fprintf(codfp, "\t\tpop\tbx\n");
            fprintf(codfp, "\t\tmov\tword ptr [bx],ax\n");
        }
        else if (p->type_link->last->type->type_id ==
                 TYPE_CHAR)
        {
            fprintf(codfp, "\t\tpop\tax\n");
            fprintf(codfp, "\t\tpop\tbx\n");
            fprintf(codfp, "\t\tmov\tbyte ptr [bx],al\n");
        }
        break;
    default:
        break;
    }
}

STATIC void do_cond_jump(int true_or_false, Symbol label)
{
    fprintf(codfp, "\t\tcmp\tax,1\n");

    if (true_or_false)
        fprintf(codfp, "\t\tjge\t%s\n", label->name);
    else
        fprintf(codfp, "\t\tjl\t%s\n", label->name);
}

STATIC void do_jump(Symbol label)
{
    fprintf(codfp, "\t\tjmp %s\n", label->name);
}

STATIC void do_label(Symbol label)
{
    fprintf(codfp, "%s:\n", label->name);
}

STATIC void do_incr(Symbol sym)
{
    switch (sym->type->type_id)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "inc word ptr %s\n", sym->rname);
        break;
    case TYPE_CHAR:
        fprintf(codfp, "inc byte ptr %s\n", sym->rname);
        break;
    default:
        parse_error("incr instruction only support char, boolean and int.", "");
        break;
    }
}

STATIC void do_decr(Symbol sym)
{
    switch (sym->type->type_id)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "dec word ptr %s\n", sym->rname);
        break;
    case TYPE_CHAR:
        fprintf(codfp, "dec byte ptr %s\n", sym->rname);
        break;
    default:
        parse_error("incr instruction only support char, boolean and int.", "");
        break;
    }
}

STATIC void do_if_test()
{
    push_stmt_stack(new_index(stmt));
    fprintf(codfp, "\t\tcmp\tax,1\n");
    fprintf(codfp, "\t\tje\tif_t%04xh\n",top_stmt_stack( ));
    fprintf(codfp, "\t\tjmp\tif_f%04xh\n",
            top_stmt_stack());
    fprintf(codfp, "if_t%04xh:\n",top_stmt_stack());
}

STATIC void do_if_clause( )
{
    fprintf(codfp, "\t\tjmp\tif_x%04xh\n",
            top_stmt_stack( ));
    fprintf(codfp, "if_f%04xh:\n",top_stmt_stack( ));
}

STATIC void do_if_exit()
{
    fprintf(codfp, "if_x%04xh:\n", pop_stmt_stack());
}

STATIC void do_repeat_start( )
{
    push_stmt_stack(new_index(stmt));
    fprintf(codfp, "rep_%04xh:\n",top_stmt_stack( ));
}

STATIC void do_repeat_exit( )
{
    fprintf(codfp, "\t\tcmp\tax,1\n");
    fprintf(codfp, "\t\tje\trep_x%04xh\n",
            top_stmt_stack());
    fprintf(codfp, "\t\tjmp\trep_%04xh\n",
            top_stmt_stack());
    fprintf(codfp, "\t\trep_x%04xh:\n",
            pop_stmt_stack( ));
}

STATIC void do_while_start( )
{
    push_stmt_stack (new_index(stmt));
    fprintf(codfp, "wl_tst%04xh:\n",top_stmt_stack());
}

STATIC void do_while_expr( )
{
    fprintf(codfp, "\t\tcmp\tax,1\n");
    fprintf(codfp, "\t\tje\twl%04xh\n",
            top_stmt_stack());
    fprintf(codfp, "\t\tjmp\twl_x%04xh\n",
            top_stmt_stack());
    fprintf(codfp, "wl%04xh:\n",top_stmt_stack());
}

STATIC void do_while_exit( )
{
    fprintf(codfp, "\t\tjmp\twl_tst%04xh\n",
            top_stmt_stack());
    fprintf(codfp, "wl_x%04xh:\n",
            pop_stmt_stack());
}

void push_call_stack(symtab *p)
{
    call_stk[call_tos] = p;
    call_sym[call_tos] = p->args;
    rtn = p;
    call_tos--;
    if (call_tos == -1)
        internal_error("call stack overflow.");
}

symtab *pop_call_stack()
{
    call_tos++;
    if (call_tos == MAX_CALL_LEVEL)
        internal_error("call stack underflow.");
    rtn = call_stk[call_tos];
    arg = call_sym[call_tos];
    return call_stk[call_tos];
}

symtab *top_call_stack( )
{
    return call_stk[call_tos + 1];
}

void set_call_stack_top(symbol *p)
{
    call_sym[call_tos + 1] = p;
}

symbol *top_call_symbol( )
{
    return call_sym[call_tos + 1];
}

STATIC void do_for_start(symbol *p)
{
    sym_stk[sym_tos] = p;
    sym_tos--;
    switch(p->type->type_id)
    {
    case TYPE_CHAR:
        fprintf(codfp, "\t\tmov\tbyte ptr %s,al\n",
                p->rname);
        break;
    case TYPE_INTEGER:
    case TYPE_BOOLEAN:
    default:
        fprintf(codfp, "\t\tmov\tword ptr %s,ax\n",
                p->rname);
        break;
    }

    push_stmt_stack(new_index(stmt));
    fprintf(codfp, "for_tst%04xh:\n",top_stmt_stack());
}

STATIC void do_for_test(int dir)
{
    symbol *p = sym_stk[sym_tos+1];
    direc_stk[dir_tos] = dir;


    dir_tos--;
    switch(p->type->type_id)
    {
    case TYPE_CHAR:
        fprintf(codfp, "\t\tcmp\tbyte ptr %s,al\n",
                p->rname);
        break;
    case TYPE_INTEGER:
    case TYPE_BOOLEAN:
    default:
        fprintf(codfp, "\t\tcmp\tword ptr %s,ax\n",
                p->rname);
        break;
    }
    if (dir == kDOWNTO)
        fprintf(codfp, "\t\tjge\tfor%04xh\n",
                top_stmt_stack());
    else
        fprintf(codfp, "\t\tjle\tfor%04xh\n",
                top_stmt_stack());
    fprintf(codfp, "\t\tjmp\tfor_x%04xh\n",
            top_stmt_stack());
    fprintf(codfp, "for%04xh:\n",top_stmt_stack());
}

STATIC void do_for_exit()
{

    symbol *p = sym_stk[sym_tos + 1];

    switch(p->type->type_id)
    {
    case TYPE_CHAR:
        if (direc_stk[dir_tos + 1] == kTO)
            fprintf(codfp, "\t\tinc\tbyte ptr %s\n",
                    p->rname);

        else
            fprintf (codfp,"\t\tdec\tbyte ptr %s\n",
                     p->rname);
        break;
    case TYPE_INTEGER:
    case TYPE_BOOLEAN:
    default:
        if ((direc_stk[dir_tos + 1] == kTO))
            fprintf(codfp, "\t\tinc\tword ptr %s\n",
                    p->rname);
        else
            fprintf (codfp, "\t\tdec\tword ptr %s\n",
                     p->rname);
        break;
    }

    fprintf (codfp, "\t\tjmp\tfor_tst%04xh\n",
             top_stmt_stack());
    fprintf(codfp, "for_x%04xh:\n", pop_stmt_stack());

    switch(p->type->type_id)
    {
    case TYPE_CHAR:
        if (direc_stk[dir_tos+1] == kTO)
            fprintf(codfp, "\t\tdec\tbyte ptr %s\n",
                    p->rname);
        else
            fprintf(codfp, "\t\tinc\tbyte ptr %s\n",
                    p->rname);
        break;
    case TYPE_INTEGER:
    case TYPE_BOOLEAN:
    default:
        if (direc_stk[dir_tos+1] == kTO)
            fprintf(codfp, "\t\tdec\tword ptr %s\n",
                    p->rname);
        else
            fprintf(codfp, "\t\tinc\tword ptr %s\n",
                    p->rname);
        break;
    }
    sym_tos++;
    dir_tos++;
}

#define    MAX_CASE_LEVEL    8
STATIC int case_list_stk[MAX_CASE_LEVEL];
STATIC int case_list_tos = MAX_CASE_LEVEL-1;
#define  MAX_CASE_ENTRY   32
STATIC symbol *case_con_queue[MAX_CASE_ENTRY];
STATIC int last_con = 0;
STATIC int case_act_index = 1;

STATIC void push_case_stack(int new_list)
{
    if (case_list_tos==-1)
        internal_error( "case stack overflow.");
    else
        case_list_stk[case_list_tos--] = new_list;
}

STATIC int pop_case_stack()
{
    if (case_list_tos==MAX_CASE_LEVEL-1)
    {
        internal_error("case stack underflow.");
        return -1;
    }

    return case_list_stk[++case_list_tos];
}
STATIC int top_case_stack()
{
    if (case_list_tos==MAX_CASE_LEVEL-1)
        return -1;
    return case_list_stk[case_list_tos+1];
}

STATIC void enter_case_queue(symbol *p)
{
    int i;
    if (last_con == MAX_CASE_ENTRY)
        internal_error("case queue overflow.");
    else
    {
        if (last_con == 0)
        {
            for(i = 0; i<MAX_CASE_ENTRY; i++)
                case_con_queue[i] = NULL;
        }
        case_con_queue[last_con] = p;
        last_con++;
    }
}

STATIC void do_case_start( )
{
    push_stmt_stack(new_index(stmt));
    fprintf(codfp, "\t\tpush\tcx\n");
    fprintf(codfp, "\t\tmov\tcx,ax\n");
    fprintf(codfp, "\t\tjmp\tcs%d_tst\n", top_stmt_stack());
    push_case_stack(last_con);
}

STATIC void do_case_test()
{
    symbol *p;
    int i;
    fprintf (codfp, "cs%d_tst:\n",top_stmt_stack( ));
    i = top_case_stack();
    for(;i<last_con;i++)
    {
        p = case_con_queue[i];
        switch(p->type->type_id)
        {
        case TYPE_BOOLEAN:
        case TYPE_INTEGER:
            if (p->defn==DEF_ELEMENT)
                fprintf(codfp, "\t\tmov\tax,%s\n",
                        p->rname);
            else
                if (p->v.i>=0)
                    fprintf(codfp, "\t\tmov\tax,0%xh\n",p->v.i);
                else
                    fprintf(codfp, "\t\tmov\tax,-0%xh\n",-p->v.i);
            break;
        case TYPE_CHAR:
            fprintf(codfp, "\t\tmov\tal,%c,\n",p->v.c);
            break;
        case TYPE_REAL:
            fprintf(codfp, "\t\tmov\tax,word ptr %s\n",p->rname);
            fprintf(codfp, "\t\tmov\tdx,word ptr %s+2\n",p->rname);
            break;
        case TYPE_STRING:
            fprintf(codfp, "\t\tlea\tax,%s\n",p->rname);
            break;
        default:
            break;
        }

        if (p->type->type_id == TYPE_INTEGER
                || p->type->type_id == TYPE_BOOLEAN)
            fprintf(codfp, "\t\tcmp\tcx,ax\n");
        else if (p->type->type_id == TYPE_CHAR)
            fprintf(codfp, "\t\tcmp\tcl,al\n");
        fprintf(codfp, "\t\tjne\tcs%dn_0%xh\n",
                top_stmt_stack(),i-top_case_stack()+1);
        fprintf(codfp, "\t\tjmp\tcs%da_%04xh\n",
                top_stmt_stack(),i-top_case_stack()+1);
        fprintf(codfp, "cs%dn_0%xh:\n",top_stmt_stack()
                ,i-top_case_stack()+1);
        case_con_queue[i] = NULL;
    }
    fprintf(codfp, "cs%d_x:\n",pop_stmt_stack());
    fprintf(codfp, "\t\tpop\tcx\n");
    last_con = pop_case_stack( );
}

STATIC void add_case_const(symbol *p)
{
    case_act_index = last_con - top_case_stack() + 1;
    enter_case_queue(p);
    fprintf(codfp, "cs%da_%04xh:\n",top_stmt_stack(),
            case_act_index);
}

STATIC void do_case_jump()
{
    fprintf(codfp,"\t\tjmp\tcs%d_x\n",top_stmt_stack());
}

STATIC int jump_index = 0;

STATIC void do_expression(symbol *p, int op)
{
    if (p->type->type_id == TYPE_INTEGER
            || p->type->type_id == TYPE_BOOLEAN)
    {
        fprintf(codfp, "\t\tpop\tdx\n");
        fprintf(codfp, "\t\tcmp\tdx,ax\n");
    }
    else if(p->type->type_id == TYPE_CHAR)
    {
        fprintf(codfp, "\t\tpop\tdx\n");
        fprintf(codfp, "\t\tcmp\tdl,al\n");
    }
    else if (p->type->type_id == TYPE_STRING)
    {
        fprintf(codfp,"\t\tpop\tdi\n");
        fprintf(codfp, "\t\tpop\tsi\n");
        fprintf(codfp, "\t\tmov\tax,ds\n");
        fprintf(codfp, "\t\tmov\tes,ax\n");
        fprintf(codfp, "\t\tcld\n");
        fprintf(codfp, "\t\tmov\tcx,0%xh\n",strlen(p->v.s));
        fprintf(codfp, "\t\trepe\t\tcmpsb\n");
    }
    else
    {
        parse_error("standard type expected.", "");
        return;
    }

    fprintf(codfp, "\t\tmov\tax,1\n");

    switch(op)
    {
    case oGE:
        fprintf(codfp, "\t\tjge\tj_%03d\n",
                new_index(jump));
        break;
    case oLE:
        fprintf(codfp, "\t\tjle\tj_%03d\n",
                new_index(jump));
        break;
    case oGT:
        fprintf(codfp, "\t\tjg\tj_%03d\n",
                new_index(jump));
        break;
    case oLT:
        fprintf(codfp, "\t\tjl\tj_%03d\n",
                new_index(jump));
        break;
    case oEQUAL:
        fprintf(codfp, "\t\tje\tj_%03d\n",
                new_index(jump));
        break;
    case oUNEQU:
        fprintf(codfp, "\t\tjne\tj_%03d\n",
                new_index(jump));
        break;
    }

    fprintf(codfp, "\t\tsub\tax,ax\n");
    fprintf(codfp, "j_%03d:\n", jump_index);
}

STATIC void do_negate(symbol *p)
{
    if (!p)
        return;
    if (p->defn != DEF_VAR
            && p->defn != DEF_VALPARA
            && p->defn != DEF_VARPARA
            && p->defn != DEF_CONST)
    {
        parse_error("variable required.", "");
        return;
    }
    switch(p->type->type_id)
    {
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tneg\tax\n");
        break;
    default:
        parse_error("operand type do not match operator.", "");
        break;
    }
}

STATIC void do_expr(symbol *p, int op)
{
    if (!p)
        return;
    switch(op)
    {
    case oPLUS:
        if (p->type->type_id == TYPE_REAL)
        {}
        else if (p->type->type_id == TYPE_INTEGER)
        {
            fprintf(codfp,"\t\tpop\tdx\n");
            fprintf(codfp, "\t\tadd\tax,dx\n");
        }
        else
            parse_error("integer or real type expected.","");
        break;
    case oMINUS:
        if (p->type->type_id == TYPE_REAL)
        {}
        else if (p->type->type_id==TYPE_INTEGER)
        {
            fprintf(codfp, "\t\tpop\tdx\n");
            fprintf(codfp, "\t\tsub\tdx,ax\n");
            fprintf(codfp, "\t\tmov\tax,dx\n");
        }
        else
            parse_error("integer or real type expected.", "");
		break;
    case kOR:
        if (p->type->type_id == TYPE_BOOLEAN)
        {
            fprintf(codfp, "\t\tpop\tdx\n");
            fprintf(codfp, "\t\tor\tax,dx\n");
        }
        else
            parse_error("boolean type expected.", "");
        break;
    default:
        break;
    }
}

STATIC void do_term(symbol *p, int op)
{
    if (!p)
        return;


    switch(op)
    {
    case oMUL:
        if (p->type->type_id == TYPE_INTEGER)
        {
            fprintf(codfp, "\t\tpop\tdx\n");
            fprintf(codfp, "\t\timul\tdx\n");
        }
        else if (p->type->type_id == TYPE_REAL)
        {}
        else
            parse_error("integer or real type expected.", "");
        break;
    case kDIV:
    case oDIV:
        if (p->type->type_id == TYPE_INTEGER)
        {
            fprintf(codfp,"\t\tmov\tcx,ax\n");
            fprintf(codfp, "\t\tpop\tax\n");
            fprintf(codfp, "\t\tsub\tdx,dx\n");
            fprintf(codfp, "\t\tidiv\tcx\n");
        }
        else
            parse_error("integer type expected.", "");
        break;
    case kMOD:
        if (p->type->type_id == TYPE_INTEGER)
        {
            fprintf(codfp, "\t\tmov\tcx,ax\n");
            fprintf(codfp, "\t\tpop\tax\n");
            fprintf(codfp, "\t\tsub\tdx,dx\n");
            fprintf(codfp, "\t\tidiv\tcx\n");
            fprintf(codfp, "\t\tmov\tax,dx\n");
        }
        else
            parse_error("integer type expected.","");
        break;
    case kAND:
        if (p->type->type_id != TYPE_BOOLEAN)
            parse_error("boolean type expected.","");
        else
        {
            fprintf(codfp, "\t\tpop\tdx\n");
            fprintf(codfp, "\t\tand\tax,dx\n");
        }
        break;
    default:
        break;
    }
}

STATIC void do_factor(symbol *p)
{
    symtab *ptab;
    int i;
    int n;

    if (!p)
        return;

    if (p->type->type_id == TYPE_ARRAY)
    {
        parse_error("array element expected","");
        return;
    }
    if (p->defn == DEF_CONST || p->defn == DEF_ELEMENT)
    {
        switch(p->type->type_id)
        {
        case TYPE_BOOLEAN:
            fprintf(codfp, "\t\tmov\tax,%d\n",p->v.b);
            break;
        case TYPE_INTEGER:
            if (p->defn == DEF_ELEMENT)
                fprintf(codfp, "\t\tmov\tax,%s\n",
                        p->rname);
            else
                fprintf(codfp, "\t\tmov\tax,0%0xh\n",
                        p->v.i);
            break;
        case TYPE_CHAR:
            fprintf(codfp, "\t\tmov\tal,'%c'\n",p->v.c);
            break;
        case TYPE_REAL:
            fprintf(codfp, "\t\tmov\tax,word ptr %s\n",p->rname);
            fprintf(codfp, "\t\tmov\tdx,word ptr %s+2\n",p->rname);
            break;
        case TYPE_STRING:
            fprintf(codfp, "\t\tlea\tax,%s\n",p->rname);
            break;
        default:
            break;
        }
    }
    else if (p->defn == DEF_VARPARA)
    {
        fprintf(codfp, "\t\tmov\tbx,word ptr %s\n",
                p->rname);
        fprintf(codfp, "\t\tmov\tax,word ptr [bx]\n");
    }
    else if (p->defn == DEF_VAR
             ||p->defn == DEF_VALPARA)

    {
        if (p->tab == top_symtab_stack()
                || p->tab->level == 0)
        {
            switch(p->type->type_id)
            {
            case TYPE_CHAR:
                fprintf(codfp, "\t\tsub\tax,ax\n");
                fprintf(codfp, "\t\tmov\tal,byte ptr %s\n",p->rname);
				break;
            case TYPE_INTEGER:
			case TYPE_BOOLEAN:
                fprintf(codfp, "\t\tmov\tax,word ptr %s\n",p->rname);
                break;
            case TYPE_REAL:
                fprintf(codfp, "\t\tmov\tax,word ptr %s\n",p->rname);
                fprintf(codfp, "\t\tmov\tdx,word ptr %s+2n",p->rname);
                break;
            }
        }
        if (p->defn == DEF_VAR)
        {
            ptab = top_symtab_stack();
            n = ptab->level - p->tab->level;
            if (n <= 0)
                return;
            fprintf(codfp, "\t\tmov\tbx,bp\n");
            for(i = 0; i<n; i++)
                fprintf(codfp, "\t\tmov\tbp,%s\n",
                        LABEL_SLINK);
            switch(p->type->type_id)
            {
            case TYPE_INTEGER:
            case TYPE_BOOLEAN:
                fprintf(codfp, "\t\tmov\tax,word ptr %s\n",p->rname);
                break;
            case TYPE_CHAR:
                fprintf(codfp, "\t\tmov\tal,byte ptr %s\n",p->rname);
                break;
            default:
                break;
            }
            fprintf(codfp,"\t\tmov\tbp,bx\n");
        }
    }
}

STATIC void do_not_factor(symbol *p)
{
    if (!p)
        return;
    if (p->type->type_id!= TYPE_BOOLEAN)
        parse_error("Boolean type expected. ","");
    do_factor(p);

    fprintf(codfp, "\t\tand\tax, 1\n");
    fprintf(codfp, "\t\txor\tax, 1\n");
}

STATIC void do_array_factor(symbol *p)
{
    if (p->type_link->first->v.i >= 0)
        fprintf(codfp, "\t\tsub\tax,0%xh\n",
                p->type_link->first->v.i);
    else
        fprintf(codfp, "\t\tsub\tax,-0%xh\n",
                -(p->type_link->first->v.i));
    fprintf(codfp, "\t\tmov\tcx,0%xh\n",
            get_symbol_size(p->type_link->last));
    fprintf(codfp, "\t\timul\tcx\n");
    fprintf(codfp, "\t\tpop\tdx\n");
    if (p->tab->level)
        fprintf(codfp, "\t\tsub\tdx,ax\n");
    else
        fprintf(codfp, "\t\tadd\tdx,ax\n");

    fprintf(codfp, "\t\tpush\tdx\n");
}

STATIC void do_record_factor(symbol *var, symbol *p)
{
    if (!var || !p || p->defn != DEF_FIELD)
        return;
    fprintf(codfp, "\t\tpop\tax\n");
    fprintf(codfp, "\t\tmov\tdx,0%xh\n",p->offset);
    if (var->tab->level)
        fprintf(codfp, "\t\tsub\tax,dx\n");
    else
        fprintf(codfp, "\t\tadd\tax,dx\n");
    fprintf(codfp, "\t\tpush\tax\n");
}

