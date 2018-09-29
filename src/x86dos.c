#define  X86_LINUX
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

static symtab *rtn =NULL;
static symbol *arg = NULL;
static Symbol	p;
static Symtab	ptab;

static void emit_dos_write1(int arg_type);
static void emit_dos_sqrt(int arg_type);
static void emit_dos_odd(int arg_type);
static void emit_dos_abs(int arg_type);
static void emit_dos_sqr(int arg_type);
static void emit_dos_read1(int arg_type);
static void emit_dos_writeln(int arg_type);

static int gen_level = 0;

static void emit_dos_program_head();
static void emit_dos_program_prologue(symtab *);
static void emit_dos_program_epilogue(symtab *);
static void emit_dos_main_prologue(symtab *);
static void emit_dos_main_epilogue(symtab *);
static void emit_dos_routine_prologue(symtab *);
static void emit_dos_routine_epilogue(symtab *);
static void emit_dos_local_args(symtab *);
static void emit_dos_dos_push_op(Type ptype);
static void emit_dos_load_value(symbol *);
static void do_dos_function_assign(symtab *,int);
static void do_dos_procedure_call(symtab *);
static void do_dos_assign(symbol *, int);
static void do_dos_expression(Type, int);
static void do_dos_negate(symbol *);
static void do_dos_expr(Type, int);
static void do_dos_term(Type, int);
static void do_dos_factor(symbol *);
static void do_dos_array_factor(symbol *);
static void do_dos_record_factor(symbol *, symbol *);
static void do_dos_first_arg(int);
static int emit_dos_address = 0;
#define MICROSOFT_MASM

static void do_dos_sys_routine(int routine_id, int arg_type)
{
    switch(routine_id)
    {
    case fABS:
        emit_dos_abs(arg_type);
        break;
    case fODD:
        emit_dos_odd(arg_type);
        break;
    case  fPRED:
        fprintf(codfp, "\t\tdec\tax\n");
        break;
    case  fSQR:
        emit_dos_sqr(arg_type);
        break;
    case fSQRT:
        emit_dos_sqrt(arg_type);
        break;
    case fSUCC:
        fprintf(codfp, "\t\tinc\tax\n");
        break;
    case pREAD:
        emit_dos_read1(arg_type);
        break;
    case pREADLN:
        emit_dos_read1(arg_type);
        break;
    case pWRITE:
        emit_dos_write1(arg_type);
        break;
    case  pWRITELN:
        emit_dos_writeln(arg_type);
        break;
    default:
        break;
    }
}

static void emit_dos_read1(int arg_type)
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

static void emit_dos_write1(int arg_type)
{
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
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

static void emit_dos_writeln(int arg_type)
{
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
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

static void emit_dos_abs(int arg_type)
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

static void emit_dos_sqr(int arg_type)
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

static void emit_dos_odd(int arg_type)
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

static void emit_dos_sqrt(int arg_type)
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

static void emit_dos_program_prologue(symtab *ptab)
{

#ifndef MICROSOFT_MASM
    fprintf(codfp, " \n;alloc stack space\n");
    fprintf(codfp, " \t\tdb\t%xh dup(?)\n"
            ,STACK_SEG_SIZE);
    fprintf(codfp,"\n_DATA\t\tends");
#endif

    fprintf(codfp,"\n\n;---program %s ---",ptab->name);

#ifndef MICROSOFT_MASM

    fprintf(codfp,"\n\n_TEXT\t\tsegment\tpublic\n\n");
#else

    fprintf(codfp,"\n\n.CODE\n");
#endif

    fprintf(codfp,"\t\tinclude\tx86rtl.inc\n\n");
    fprintf(codfp,"%s\tequ\tword ptr [bp+04h]\n"
            ,LABEL_SLINK);
    fprintf(codfp,"%s\tequ\tword ptr [bp-04h]\n",
            LABEL_RETVAL);
    fprintf(codfp,"%s\tequ\tword ptr [bp-02h]\n",
            LABEL_HIRETVAL);
    emit_dos_program_head();

#ifndef MICROSOFT_MASM

    fprintf(datfp, " \n_DATA\t\tsegment\tpublic\n");
#else

    fprintf(datfp, " \n.DATA\n");
#endif

}

/* char datname[]; */
static void emit_dos_program_head()
{
#ifdef _MSDOS_
    struct dosdate_t d;
    struct dosdate_t t;
    _dos_getdate(&d);
    _dos_gettime(&t);
    fprintf(datfp,";%s\n:%02d:%02d:%02d/%d/%d/%d\n",
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
    fprintf(datfp,";\n");

#ifdef MICROSOFT_MASM

    fprintf(datfp,";small model\n");
    fprintf(datfp,".MODEL SMALL\n");
    fprintf(datfp,"\n;set stack size\n");
    fprintf(datfp,".STACK %xh\n", STACK_SEG_SIZE);
#endif

}

static void emit_dos_program_epilogue(symtab *ptab)
{
    symbol *p;

#ifndef MICROSOFT_MASM

    fprintf(codfp,"\n_TEXT\t\tends\n");
    fprintf(codfp,"\t\tend\tstart\n\n");
#else

    fprintf(codfp,"\n\n\t\t.STARTUP\n");
    fprintf(codfp,"\t\tcall _main\n");
    fprintf(codfp,"\n\n\t\t.EXIT\n");
    fprintf(codfp,"\t\tend\n\n");
#endif

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

static void emit_dos_main_prologue(symtab *ptab)
{
    fprintf(codfp,"\n\n; --- main routine ----\n");
#ifndef MICROSOFT_MASM

    fprintf(codfp,"_main\t\tproc\tfar\n");
    fprintf(codfp,"\t\tassume\tcs:_TEXT,ds:_DATA\n");
    fprintf(codfp,"start:\n");
    fprintf(codfp,"\t\tpush\tds\n");
    fprintf(codfp,"\t\tsub\tax,ax\n");
    fprintf(codfp,"\t\tpush\tax\n");
    fprintf(codfp,"\t\tmov\tax,_DATA\n");
    fprintf(codfp,"\t\tmov\tds,ax\n");
#else

    fprintf(codfp,"_main\t\tproc\tnear\n");
    fprintf(codfp,"\t\tassume\tcs:_TEXT,ds:_DATA\n");
    fprintf(codfp,"\t\tmov\tax,_DATA\n");
    fprintf(codfp,"\t\tmov\tds,ax\n");
#endif

}

static void emit_dos_main_epilogue(symtab *ptab)
{
    fprintf(codfp,"\t\tret\n");
    fprintf(codfp,"_main\t\tendp\n");
}

static void emit_dos_routine_prologue(symtab *ptab)
{
    if(ptab->defn == DEF_PROG)
        return;
    fprintf(codfp,"\n\n; routine : %s \n",ptab->name);
    emit_dos_local_args(ptab);
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

static void emit_dos_local_args(symtab *ptab)
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

    fprintf(codfp,";arguments in %s\n", ptab->name);
    for(p = ptab->args;p ;p = p->next)
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
                p->rname, tp, p->offset);
    }
}

static void emit_dos_routine_epilogue(symtab *ptab)
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

static void emit_dos_dos_push_op(Type ptype)
{
    switch(ptype->type_id)
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

static void emit_dos_load_value(symbol *p)
{
    if(p->defn == DEF_VARPARA)
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
            fprintf(codfp,"\t\tsub\tax, ax\n");
            fprintf(codfp,"\b\t\tmov\tal, byte  ptr %s\n"
                    ,p->rname);
            break;
        case  	TYPE_REAL:
            fprintf(codfp,"\t\t\tmov\tax, word ptr %s\n",p->rname);
            fprintf(codfp,"\t\t\tmov\tdx, word ptr %s+2\n",p->rname);
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

static void emit_dos_load_address(symbol *p)
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
        if(p->tab->level == 0
                || p->tab == top_symtab_stack())
        {
            /*
            fprintf(codfp, "\t\tmov\tax,word ptr %s\n",
            		p->rname);
            */
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
        fprintf(codfp, "\t\tlea\tax,word ptr %s\n",
                p->rname);
        break;
    default:
        break;
    }
}

static void emit_dos_load_field(symbol*p)
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

#if 0
static int pop_stmt_stack()
{
    if(stmt_tos==STMT_STACK_SIZE)
        internal_error("Satement stack underflow.\n");
    return stmt_stack[++stmt_tos];
}

static void push_stmt_stack(int index)
{
    if(stmt_tos==0)
        internal_error("Satement stack overflow.\n");
    stmt_stack[stmt_tos--] = index;
}

static int top_stmt_stack()
{
    return stmt_stack[stmt_tos + 1];
}
#endif

static void do_dos_function_assign(symtab *ptab, int srctype)
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

static void do_dos_procedure_call(symtab *ptab)
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
    if(callee->level == caller->level + 1)
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

#if 0
static void reset_args(symtab *ptab)
{
    rtn = ptab;
}
#endif

static void do_dos_first_arg(int ptype)
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
        if (ptype != TYPE_REAL)
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

static void do_dos_args(int ptype)
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
        fprintf(codfp,"\t\txor\tah, ah\n");
    case  TYPE_INTEGER:
    case  TYPE_BOOLEAN:
    default:
        fprintf(codfp,"\t\tpush\tax\n");
        break;
    }
}

static void do_dos_assign(symbol *p, int srctype)
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

    if((p->type->type_id == TYPE_ARRAY) 
		&& (srctype != p->type->first->type->type_id))
    {
        parse_error("operand type do not match operator.","");
        return;
    }

    if((p->type->type_id == TYPE_RECORD)) 
    {
        parse_error("operand type do not match operator.","");
        return;
    }

    switch(p->defn)
    {
    case DEF_VARPARA:
        fprintf(codfp,"\t\tpush\tax\n");
        fprintf(codfp,"\t\tmov\tax,word ptr %s\n",
                p->rname);
        break;
    case DEF_FIELD:
        fprintf(codfp,"\t\tpop\tbx\n");
        if(p->type->type_id == TYPE_INTEGER
                ||p->type->type_id == TYPE_BOOLEAN)
            fprintf(codfp,"\t\tmov\tword ptr [bx],ax\n");
        else if (p->type->type_id == TYPE_CHAR)
            fprintf(codfp,"\t\tmov\tbyte ptr [bx],al\n");
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
                ||p->type->type_id == TYPE_REAL)
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
        fprintf(codfp,"\t\rpush\tax\n");
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
        fprintf(codfp, "\t\tmov\tcx, %04xh\n",
                strlen(p->v.s));
        fprintf(codfp, "\t\tpop\tsi\n");
        fprintf(codfp, "\t\tpop\tdi\n");
        fprintf(codfp, "\t\tmov\tax,ds\n");
        fprintf(codfp, "\t\tmov\tes,ax\n");
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

static void do_dos_cond_jump(int true_or_false, Symbol label)
{
    fprintf(codfp, "\t\tcmp\tax,1\n");

    if (true_or_false)
        fprintf(codfp, "\t\tjge\t%s\n", label->name);
    else
        fprintf(codfp, "\t\tjl\t%s\n", label->name);
}

static void do_dos_jump(Symbol label)
{
    fprintf(codfp, "\t\tjmp %s\n", label->name);
}

static void do_dos_label(Symbol label)
{
    fprintf(codfp, "%s:\n", label->name);
}

static void do_dos_incr(Symbol sym)
{
    switch (sym->type->type_id)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tinc word ptr %s\n", sym->rname);
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\tinc byte ptr %s\n", sym->rname);
        break;
    default:
        parse_error("incr instruction only support char, boolean and int.", "");
        break;
    }
}

static void do_dos_decr(Symbol sym)
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

static int jump_index = 0;

static void do_dos_expression(Type type, int op)
{

    if (type == NULL)
    {
        return;
    }

    if (type->type_id == TYPE_INTEGER
            || type->type_id == TYPE_BOOLEAN)
    {
        fprintf(codfp, "\t\tpop\tdx\n");
        fprintf(codfp, "\t\tcmp\tdx,ax\n");
    }
    else if(type->type_id == TYPE_CHAR)
    {
        fprintf(codfp, "\t\tpop\tdx\n");
        fprintf(codfp, "\t\tcmp\tdl,al\n");
    }
    else if (type->type_id == TYPE_STRING)
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

    switch(generic(op))
    {
    case GE:
        fprintf(codfp, "\t\tjge\tj_%03d\n",
                new_index(jump));
        break;
    case LE:
        fprintf(codfp, "\t\tjle\tj_%03d\n",
                new_index(jump));
        break;
    case GT:
        fprintf(codfp, "\t\tjg\tj_%03d\n",
                new_index(jump));
        break;
    case LT:
        fprintf(codfp, "\t\tjl\tj_%03d\n",
                new_index(jump));
        break;
    case EQ:
        fprintf(codfp, "\t\tje\tj_%03d\n",
                new_index(jump));
        break;
    case NE:
        fprintf(codfp, "\t\tjne\tj_%03d\n",
                new_index(jump));
        break;
    }

    fprintf(codfp, "\t\tsub\tax,ax\n");
    fprintf(codfp, "j_%03d:\n", jump_index);
}

static void do_dos_negate(symbol *p)
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

static void do_dos_expr(Type type, int op)
{
    if (type == NULL)
    {
        return;
    }

    switch(generic(op))
    {
    case ADD:
        if (type->type_id == TYPE_REAL)
        {}
        else if (type->type_id == TYPE_INTEGER)
        {
            fprintf(codfp,"\t\tpop\tdx\n");
            fprintf(codfp, "\t\tadd\tax,dx\n");
        }
        else
            parse_error("integer or real type expected.","");
        break;
    case SUB:
        if (type->type_id == TYPE_REAL)
        {}
        else if (type->type_id==TYPE_INTEGER)
        {
            fprintf(codfp, "\t\tpop\tdx\n");
            fprintf(codfp, "\t\tsub\tdx,ax\n");
            fprintf(codfp, "\t\tmov\tax,dx\n");
        }
        else
            parse_error("integer or real type expected.", "");
        break;
    case OR:
        if (type->type_id == TYPE_BOOLEAN)
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

static void do_dos_term(Type type, int op)
{
    if (type == NULL)
    {
        return;
    }
    switch(generic(op))
    {
    case MUL:
        if (type->type_id == TYPE_INTEGER)
        {
            fprintf(codfp, "\t\tpop\tdx\n");
            fprintf(codfp, "\t\timul\tdx\n");
        }
        else if (type->type_id == TYPE_REAL)
        {}
        else
            parse_error("integer or real type expected.", "");
        break;
    case DIV:
        if (type->type_id == TYPE_INTEGER)
        {
            fprintf(codfp,"\t\tmov\tcx,ax\n");
            fprintf(codfp, "\t\tpop\tax\n");
            fprintf(codfp, "\t\tsub\tdx,dx\n");
            fprintf(codfp, "\t\tidiv\tcx\n");
        }
        else
            parse_error("integer type expected.", "");
        break;
    case MOD:
        if (type->type_id == TYPE_INTEGER)
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
    case AND:
        if (type->type_id != TYPE_BOOLEAN)
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

static void do_dos_factor(symbol *p)
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
			{
				short tvi = (short)p->v.i;

                fprintf(codfp, "\t\tmov\tax,0%xh\n",
                        tvi);
			}
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
            case TYPE_BOOLEAN:
            case TYPE_INTEGER:
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

static void do_dos_not_factor(symbol *p)
{
    if (!p)
        return;
    if (p->type->type_id!= TYPE_BOOLEAN)
        parse_error("Boolean type expected. ","");

    do_dos_factor(p);

    fprintf(codfp, "\t\tand\tax, 1\n");
    fprintf(codfp, "\t\txor\tax, 1\n");
}

static void do_dos_array_factor(symbol *p)
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

static void do_dos_record_factor(symbol *var, symbol *p)
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

static int programbegin(Env *global)
{
    emit_dos_program_prologue(global->u.program.tab);
    return 0;
}

static int programend(Env *global)
{
    emit_dos_program_epilogue(global->u.program.tab);
    return 0;
}

static int mainbegin(Env *main)
{
    emit_dos_main_prologue(main->u.main.tab);
    return 0;
}

static int mainend(Env *main)
{
    emit_dos_main_epilogue(main->u.main.tab);
    return 0;
}

static int globalvariable(Symbol symbol)
{
    return 0;
}

static int localvariable(Symbol symbol)
{
    return 0;
}

static int deflabel(Symbol symbol)
{
    return 0;
}

static int defaddress(Symbol p, Symbol q, long n)
{
    return 0;
}

static int defconst(int type, Value value)
{
    return 0;
}

static int allocspace(int n)
{
    return n;
}

static int marknode(Node rootnode)
{
    return 0;
}

static int gen_dos_code(Node rootnode)
{
    int ret = 0;
    Node pnode;

    gen_level++;

    switch (generic(rootnode->op))
    {
    case ARG:
        if (!rootnode->kids[0])
        {
            return ERROR_SUCCESS;
        }

        gen_dos_code(rootnode->kids[0]);
        do_dos_first_arg(rootnode->kids[0]->type->type_id);

        pnode = rootnode->kids[1];
        while(pnode)
        {
            if (!pnode->kids[0])
                break;

            gen_dos_code(pnode->kids[0]);
            do_dos_args(pnode->kids[0]->type->type_id);

            pnode = pnode->kids[1];
        }

        gen_level --;
        return ERROR_SUCCESS;
    case AND:
    case OR:
    case EQ:
    case NE:
    case GT:
    case GE:
    case LE:
    case LT:
        if (rootnode->kids[0])
        {
            ret = gen_dos_code(rootnode->kids[0]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        emit_dos_dos_push_op(rootnode->kids[0]->type);
        if (rootnode->kids[1])
        {
            ret = gen_dos_code(rootnode->kids[1]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        break;
    case BOR:
    case BAND:
    case BXOR:
    case ADD:
    case SUB:
        if (rootnode->kids[0])
        {
            ret = gen_dos_code(rootnode->kids[0]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        emit_dos_dos_push_op(rootnode->kids[0]->type);
        if (rootnode->kids[1])
        {
            ret = gen_dos_code(rootnode->kids[1]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        break;
    case RSH:
    case LSH:
    case DIV:
    case MUL:
    case MOD:
        if (rootnode->kids[0])
        {
            ret = gen_dos_code(rootnode->kids[0]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        emit_dos_dos_push_op(rootnode->kids[0]->type);
        if (rootnode->kids[1])
        {
            ret = gen_dos_code(rootnode->kids[1]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        break;
    case ARRAY:
        emit_dos_load_address(rootnode->syms[0]);
        emit_dos_dos_push_op(find_type_by_id(TYPE_INTEGER));
        if (rootnode->kids[0])
        {
            ret = gen_dos_code(rootnode->kids[0]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        break;
        /*
        case ADDRG:
        if (rootnode->kids[0] != NULL)
        {
        	if (generic(rootnode->kids[0]->op) == ARRAY)
        	{
        		emit_dos_load_address(rootnode->kids[0]->syms[0]);
        		emit_dos_dos_push_op(TYPE_INTEGER);
        	}
        	else if (generic(rootnode->kids[0]->op) == FIELD)
        	{
        		emit_dos_load_address(rootnode->syms[0]);
        		emit_dos_dos_push_op(TYPE_INTEGER);
        		do_dos_record_factor(rootnode->syms[0], rootnode->syms[1]);
        	}
        }
        break;
        */
    case SYS:
        /* for sys call, all childnodes will be processed in next switch. */
        break;
    case CALL:
        push_call_stack(rootnode->symtab);

    default:
        if (rootnode->kids[0])
        {
            ret = gen_dos_code(rootnode->kids[0]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }

        if (rootnode->kids[1])
        {
            ret = gen_dos_code(rootnode->kids[1]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }

        if (rootnode->kids[2])
        {
            ret = gen_dos_code(rootnode->kids[2]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        break;
    }

    switch (generic(rootnode->op))
    {
    case ARRAY:
        do_dos_array_factor(rootnode->syms[0]);
        break;
    case CNST:
        do_dos_factor(rootnode->syms[0]);
        break;
    case FIELD:
        emit_dos_load_address(rootnode->syms[0]);
        emit_dos_dos_push_op(find_type_by_id(TYPE_INTEGER));
        do_dos_record_factor(rootnode->syms[0], rootnode->syms[1]);
        /* emit_dos_load_field(rootnode->syms[1]); */
        break;
    case HEADER:
        emit_dos_routine_prologue(rootnode->symtab);
        break;
    case TAIL:
        emit_dos_routine_epilogue(rootnode->symtab);
        break;
    case NOT:
        do_dos_not_factor(rootnode->kids[0]->syms[0]);
        break;
    case NEG:
        do_dos_negate(rootnode->kids[0]->syms[0]);
        break;
    case ASGN:
        {
            p = rootnode->kids[0]->syms[0];
            if (!p)
                assert(0);

            if (p->defn == DEF_FUNCT)
            {
                ptab = find_routine(p->name);

                if(ptab)
                    do_dos_function_assign(ptab, rootnode->kids[0]->type->type_id);
                else
                {
                    parse_error("Undeclared identifier.", p->name);
                    gen_level --;
                    return ERROR_UNDECLARE;
                }
            }
            else
            {
                do_dos_assign(p, rootnode->kids[0]->type->type_id);
            }
        }
        break;
    case CALL:
        do_dos_procedure_call(rootnode->symtab);
        pop_call_stack();
        break;
    case SYS:

        emit_dos_address = 1;		/* signal the ADDRG to generate address. */
        if ((rootnode->kids[0] == NULL) ||
                (rootnode->kids[0]->kids[0] == NULL) ||
                (rootnode->kids[0]->kids[1] == NULL))
        {
            /* do system call without args, or with only one arg. */
            if (rootnode->kids[0])
			{
                if (rootnode->kids[0]->kids[0])
                    gen_dos_code(rootnode->kids[0]->kids[0]);
                else
                    gen_dos_code(rootnode->kids[0]);
			}
            do_dos_sys_routine(rootnode->u.sys_id, rootnode->kids[0]->type->type_id);
        }
        else
        {
#if DEBUG & SYSTEM_CALL_DEBUG
            {
                Symtab systab = find_sys_routine(rootnode->u.sys_id);
                printf("do system call %s with more than one arg.\n", systab->name);
            }
#endif
            switch (rootnode->u.sys_id)
            {
            case pREAD:
            case pREADLN:
            case pWRITE:
            case pWRITELN:
            default:
                gen_dos_code(rootnode->kids[0]->kids[0]);
                do_dos_sys_routine(rootnode->u.sys_id, rootnode->kids[0]->kids[0]->type->type_id);

                pnode = rootnode->kids[0]->kids[1];
                while(pnode)
                {
                    if (!pnode->kids[0])
                        break;

                    gen_dos_code(pnode->kids[0]);
                    do_dos_sys_routine(rootnode->u.sys_id, pnode->kids[0]->type->type_id);
                    pnode = pnode->kids[1];
                }

                break;
            }
        }
        emit_dos_address = 0;		/* clear signal */
        break;
    case COND:
        do_dos_cond_jump(rootnode->u.cond.true_or_false, rootnode->u.cond.label);
        break;
    case JUMP:
        do_dos_jump(rootnode->syms[0]);
        break;
    case LABEL:
        do_dos_label(rootnode->syms[0]);
        break;
    case INCR:
        /*
         * variable is in first child of INCR node.
         * generally an ADDRG node.
         */
        assert(rootnode->kids[0]->syms[0]);
        do_dos_incr(rootnode->kids[0]->syms[0]);
        break;
    case DECR:
        /*
         * variable is in first child of DECR node.
         * generally an ADDRG node.
         */
        assert(rootnode->kids[0]->syms[0]);
        do_dos_decr(rootnode->kids[0]->syms[0]);
        break;
    case LOAD:
        if (rootnode->kids[0] == NULL)
        {
            /* simple const or id. */
            do_dos_factor(rootnode->syms[0]);
        }
        else if (generic(rootnode->kids[0]->op) == ARRAY)
        {
            emit_dos_load_value(rootnode->kids[0]->syms[0]);
        }
        else
        {
            emit_dos_load_field(rootnode->kids[0]->syms[1]);
        }
        break;
    case EQ:
    case NE:
    case GT:
    case GE:
    case LE:
    case LT:
        do_dos_expression(rootnode->kids[1]->type, rootnode->op);
        break;
    case ADD:
    case SUB:
    case OR:
        do_dos_expr(rootnode->kids[1]->type, rootnode->op);
        break;
    case AND:
    case RSH:
    case LSH:
    case BOR:
    case BAND:
    case BXOR:
    case DIV:
    case MUL:
    case MOD:
        /*
        if (rootnode->kids[0])
        {
        	ret = gen_dos_code(rootnode->kids[0]);
        	if (ret < 0) {
        		gen_level --;
        		return ret;
        	}
        }
        */
        do_dos_term(rootnode->kids[1]->type, rootnode->op);
        break;
    case BLOCKBEG:
    case BLOCKEND:
        break;
    case ADDRG:
        if (emit_dos_address)
            emit_dos_load_address(rootnode->syms[0]);
        break;
    default:
        assert(0);
        break;

    }

    gen_level --;
    return ret;
}


static int functionprocess(List dags)
{
    List cp = dags->link;
    int ret = 0;

    for (; cp; cp = cp->link)
    {
        if ((ret = gen_dos_code((Node)(cp->x))) < 0)
        {
            parse_error("Error generating code.","");
            return ret;
        }
    }
    return ret;
}

static int blockbegin(BlockContext *context)
{
    return 0;
}

static int blockend(BlockContext *context)
{
    return 0;
}

static void defexport(Symbol sym)
{}

static void defimport(Symbol sym)
{}

Interface x86_dos_interface = {
  /* type interface */
  {1, 1, 0},		/* charmetric */
  {2, 2, 0},		/* shortmetric */
  {2, 2, 0},		/* intmetric */
  {4, 4, 0},		/* floatmetric */
  {8, 8, 0},		/* doublemetric */
  {4, 4, 0},		/* pointermetric */
  {4, 4, 0},		/* structmetric */

  /* function interface. */
  programbegin,
  programend,
  mainbegin,
  mainend,
  defaddress,
  blockbegin,
  blockend,
  globalvariable,
  localvariable,
  deflabel,
  defconst,
  allocspace,
  marknode,
  gen_dos_code,
  functionprocess,
  defexport,
  defimport,
};

