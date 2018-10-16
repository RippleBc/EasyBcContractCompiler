#define  X86_LINUX
#include  <stdio.h>
#include  "common.h"
#include  "symtab.h"
#include  "error.h"
#include  "x86.h"
#include  _YTAB_H_
#define  MAX_CALL_LEVEL 16

static symtab *rtn =NULL;
static symbol *arg = NULL;
static Symbol	p;
static Symtab	ptab;

static void emit_linux_write1(int arg_type);
static void emit_linux_sqrt(int arg_type);
static void emit_linux_odd(int arg_type);
static void emit_linux_abs(int arg_type);
static void emit_linux_sqr(int arg_type);
static void emit_linux_read1(int arg_type);
static void emit_linux_writeln(int arg_type);

static int gen_level = 0;

static void emit_linux_program_head();
static void emit_linux_program_prologue(symtab *);
static void emit_linux_program_epilogue(symtab *);
static void emit_linux_main_prologue(symtab *);
static void emit_linux_main_epilogue(symtab *);
static void emit_linux_routine_prologue(symtab *);
static void emit_linux_routine_epilogue(symtab *);
static void emit_linux_local_args(symtab *);
static void emit_linux_dos_push_op(Type ptype);
static void emit_linux_load_value(symbol *);
static void do_linux_function_assign(symtab *,int);
static void do_linux_procedure_call(symtab *);
static void do_linux_assign(symbol *, int);
static void do_linux_expression(Type, int);
static void do_linux_negate(symbol *);
static void do_linux_expr(Type, int);
static void do_linux_term(Type, int);
static void do_linux_factor(symbol *);
static void do_linux_array_factor(symbol *);
static void do_linux_record_factor(symbol *, symbol *);
static void do_linux_first_arg(int);
static int emit_linux_address = 0;

extern char datname[FILE_NAME_LEN];

#ifdef LABEL_RETVAL
#undef LABEL_RETVAL
#define LABEL_RETVAL "-4(%ebp)"
#endif


#ifdef LABEL_SLINK
#undef LABEL_SLINK
#define LABEL_SLINK	"8(%ebp)"
#endif

static void do_linux_sys_routine(int routine_id, int arg_type)
{
    switch(routine_id)
    {
    case fABS:
        emit_linux_abs(arg_type);
        break;
    case fODD:
        emit_linux_odd(arg_type);
        break;
    case  fPRED:
        fprintf(codfp, "\t\tdecl\t%%eax\n");
        break;
    case  fSQR:
        emit_linux_sqr(arg_type);
        break;
    case fSQRT:
        emit_linux_sqrt(arg_type);
        break;
    case fSUCC:
        fprintf(codfp, "\t\tincl\t%%eax\n");
        break;
    case pREAD:
        emit_linux_read1(arg_type);
        break;
    case pREADLN:
        emit_linux_read1(arg_type);
        break;
    case pWRITE:
        emit_linux_write1(arg_type);
        break;
    case  pWRITELN:
        emit_linux_writeln(arg_type);
        break;
    default:
        break;
    }
}

static void emit_linux_read1(int arg_type)
{
    fprintf(codfp, "\t\tpushl\t%%eax\n");
    fprintf(codfp, "\t\tpushl\t%%ebp\n");
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
	fprintf(codfp, "\t\taddl\t$8, %%esp\n");
}

static void emit_linux_write1(int arg_type)
{
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tpushl\t%%eax\n");
        fprintf(codfp, "\t\tpushl\t%%ebp\n");
        fprintf(codfp, "\t\tcall\t_write_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\tpushl\t%%eax\n");
        fprintf(codfp, "\t\tpushl\t%%ebp\n");
        fprintf(codfp, "\t\tcall\t_write_char\n");
        break;
    case TYPE_STRING:
        fprintf(codfp, "\t\tpushl\t%%eax\n");
        fprintf(codfp, "\t\tpushl\t%%ebp\n");
        fprintf(codfp, "\t\tcall\t_write_string\n");
        break;
    default:
        break;
    }
	fprintf(codfp, "\t\taddl\t$8, %%esp\n");
}

static void emit_linux_writeln(int arg_type)
{
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tpushl\t%%eax\n");
        fprintf(codfp, "\t\tpushl\t%%ebp\n");
        fprintf(codfp, "\t\tcall\t_writeln_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\tpushl\t%%eax\n");
        fprintf(codfp, "\t\tpushl\t%%ebp\n");
        fprintf(codfp, "\t\tcall\t_writeln_char\n");
        break;
    case  TYPE_STRING:
        fprintf(codfp, "\t\tpushl\t%%eax\n");
        fprintf(codfp, "\t\tpushl\t%%ebp\n");
        fprintf(codfp, "\t\tcall\t_writeln_string\n");
        break;
    default:
        break;
    }
	fprintf(codfp, "\t\taddl\t$8, %%esp\n");
}

static void emit_linux_abs(int arg_type)
{
    fprintf(codfp, "\t\tpushl\t%%ebp\n");
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tcall\t_abs_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\txorb\t%%ah,%%ah\n");
        fprintf(codfp, "\t\tcall\t_abs_int\n");
        break;
    default:
        break;
    }
	fprintf(codfp, "\t\taddl\t$8, %%esp\n");
}

static void emit_linux_sqr(int arg_type)
{
    fprintf(codfp, "\t\tpushl\t%%bp\n");
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tcall\t_sqr_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\txorb\t%%ah,%%ah\n");
        fprintf(codfp, "\t\tcall\t_sqr_int\n");
        break;
    default:
        break;
    }
	fprintf(codfp, "\t\taddl\t$8, %%esp\n");
}

static void emit_linux_odd(int arg_type)
{
    fprintf(codfp, "\t\tpushl\t%%bp\n");
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tcall\t_odd_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\txorb\t%%ah,%%ah\n");
        fprintf(codfp, "\t\tcall\t_odd_int\n");
        break;
    default:
        break;
    }
	fprintf(codfp, "\t\taddl\t$8, %%esp\n");
}

static void emit_linux_sqrt(int arg_type)
{
    fprintf(codfp, "\t\tpushl\t%%ebp\n");
    switch(arg_type)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tcall\t_sqrt_int\n");
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\txorb\t%%ah,%%ah\n");
        fprintf(codfp, "\t\tcall\t_sqrt_int\n");
        break;
    default:
        break;
    }
	fprintf(codfp, "\t\taddl\t$8, %%esp\n");
}

static void emit_linux_program_prologue(symtab *ptab)
{

    fprintf(codfp,"\n\n#---program %s ---",ptab->name);
    emit_linux_program_head();

}

/* char datname[]; */
static void emit_linux_program_head()
{
    fprintf(datfp, "#\n");
    fprintf(datfp, "#SPL Compiler Ver %s\n",_PC_VER_);
    fprintf(datfp, "#\n");
    fprintf(datfp, ".file \"%s\"\n\n", datname);
	fprintf(datfp, "sys_call_id = 0x80\n");
	fprintf(datfp, "exit_syscall = 0x1\n\n");
}

static void emit_linux_program_epilogue(symtab *ptab)
{
    symbol *p;

	fprintf(codfp, "\n\n.globl _start\n");
	fprintf(codfp, "_start:\n");
	fprintf(codfp, "\t\tcall _main\n");
	fprintf(codfp, "\t\tmovl $0, %%ebx\n");
	fprintf(codfp, "\t\tmovl $exit_syscall, %%eax\n");
	fprintf(codfp, "\t\tint  $sys_call_id\n");
	fprintf(codfp, ".ident	\"SPL: 0.1.5\"\n");

    fprintf(codfp, "\n#.bss variables\n");

    for(p = ptab->locals; p; p = p->next)
    {
        if (p->defn != DEF_CONST)
        {
				switch (p->type->type_id)
				{
				case 	TYPE_CHAR:
					fprintf(codfp, "\t\t.comm %s,%d,%d\n", p->rname, IR->charmetric.size, IR->intmetric.align);
					break;
				case	TYPE_BOOLEAN:
				case 	TYPE_INTEGER:
					fprintf(codfp, "\t\t.comm %s,%d,%d\n", p->rname, IR->intmetric.size, IR->intmetric.align);
					break;
				case 	TYPE_REAL:
					break;
				case 	TYPE_STRING:
					break;
				case TYPE_ARRAY:
					if(p->type_link->last->type->type_id == TYPE_INTEGER
							|| p->type_link->last->type->type_id == TYPE_BOOLEAN)
							/*
						fprintf(datfp,"%s\t\tdw\t0%xh dup (?)\n"
								,p->rname,p->type_link->num_ele);
								*/
						fprintf(codfp,"\t\t.comm %s, %d, %d\n"
								,p->rname, p->type_link->num_ele * IR->intmetric.size, 
								IR->intmetric.align);
					else if(p->type_link->last->type->type_id ==
							TYPE_CHAR)
							/*
						fprintf(datfp,"%s\t\tdb\t0%xh dup (?)\n"
								,p->rname,p->type_link->num_ele);
								*/
						fprintf(codfp,"\t\t.comm %s, %d, %d\n"
								,p->rname,p->type_link->num_ele,
								IR->intmetric.align);

					else
						parse_error("complex array element not supported","");
					if(p->defn != DEF_CONST)
						continue;
					break;
				case   TYPE_RECORD:
					/*
					fprintf(datfp,"%s\t\tdb\t0%xh dup (?)\n"
							,p->rname,p->type_link->size);
							*/
					fprintf(codfp,"\t\t.comm %s, %d, %d\n"
							,p->rname, p->type_link->size,
							IR->intmetric.align);
					continue;
				default:
					break;
				}
		}
    }

	/* global variable as .data */
	fprintf(datfp, ".data\n");

    for(p = ptab->locals; p; p = p->next)
    {
        if (p->defn == DEF_CONST)
        {
				switch (p->type->type_id)
				{
				case 	TYPE_CHAR:
					fprintf(datfp, ".globl %s\n", p->rname);
					/* fprintf(datfp, "\t\t.align %d\n", IR->charmetric.align); */
					fprintf(datfp, "\t\t.type %s @object\n", p->rname);
					fprintf(datfp, "\t\t.size %s, %d\n", p->rname, IR->charmetric.size);
					fprintf(datfp, "%s:\n", p->rname);
					fprintf(datfp, "\t\t.byte %d\n", p->v.c);
					break;
				case	TYPE_BOOLEAN:
				case 	TYPE_INTEGER:
					fprintf(datfp, ".globl %s\n", p->rname);
					fprintf(datfp, "\t\t.align %d\n", IR->intmetric.align);
					fprintf(datfp, "\t\t.type %s @object\n", p->rname);
					fprintf(datfp, "\t\t.size %s, %d\n", p->rname, IR->intmetric.size);
					fprintf(datfp, "%s:\n", p->rname);
					fprintf(datfp, "\t\t.long %d\n", p->v.i);
					break;
				case 	TYPE_REAL:
					break;
				case 	TYPE_STRING:
					fprintf(datfp, ".globl %s\n", p->rname);
					fprintf(datfp, "\t\t.section .rodata\n");
					fprintf(datfp, "\t\t.align %d\n", IR->pointermetric.align);

					fprintf(datfp, ".LC%s:\n", p->rname);
					if ((p->v.s[0] == '\'') && (p->v.s[strlen(p->v.s) - 1] == '\''))
					{
						p->v.s[strlen(p->v.s) - 1] = '\0';
						fprintf(datfp, "\t\t.string \"%s\"\n", p->v.s + 1);
					}
					else
						fprintf(datfp, "\t\t.string \"%s\"\n", p->v.s);
					fprintf(datfp, "\t\t.data\n");
					fprintf(datfp, "\t\t.align %d\n", IR->pointermetric.align);
					fprintf(datfp, "\t\t.type %s @object\n", p->rname);
					fprintf(datfp, "\t\t.size %s, %d\n", p->rname, IR->pointermetric.size);
					fprintf(datfp, "%s:\n", p->rname);
					fprintf(datfp, "\t\t.long .LC%s\n", p->rname);
					break;
				case TYPE_ARRAY:
					break;
				case TYPE_RECORD:
					break;
				default:
					break;
				}
		}
    }
}

static void emit_linux_main_prologue(symtab *ptab)
{
    fprintf(codfp,"\n\n# --- main routine ----\n");

	fprintf(codfp, "\t\t.text\n");
	fprintf(codfp, ".globl _main\n");
	fprintf(codfp, "\t\t.type _main, @function\n");
	fprintf(codfp, "_main:\n");
	fprintf(codfp, "\t\tpushl\t%%ebp\n");
	fprintf(codfp, "\t\tmovl\t%%esp, %%ebp\n");

}

static void emit_linux_main_epilogue(symtab *ptab)
{
	fprintf(codfp,"\t\tleave\n");
    fprintf(codfp,"\t\tret\n");
	fprintf(codfp,".size _main, .-main\n");
}

static void emit_linux_routine_prologue(symtab *ptab)
{
    if(ptab->defn == DEF_PROG)
        return;
    fprintf(codfp,"\n\n# routine : %s \n",ptab->name);
    emit_linux_local_args(ptab);
	fprintf(codfp, "\t\t.text\n");
	fprintf(codfp, ".globl %s\n", ptab->rname);
	fprintf(codfp, "\t\t.type %s, @function\n", ptab->rname);
	fprintf(codfp, "%s:\n", ptab->rname);
	fprintf(codfp, "\t\tpushl\t%%ebp\n");
	fprintf(codfp, "\t\tmovl\t%%esp, %%ebp\n");
    if(ptab->defn == DEF_FUNCT)
        fprintf(codfp,"\t\tsubl\t$8, %%esp\n");
    fprintf(codfp,"\t\tsubl\t$%d, %%esp\n",ptab->local_size);
}

static void emit_linux_local_args(symtab *ptab)
{
    symbol *p;
    char tp[10];

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

        snprintf(p->rname, sizeof(p->rname) - 1, "-%d(%%ebp)",
                p->offset);
    }

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

        snprintf(p->rname,sizeof(p->rname) - 1,"%d(%%ebp)",
                p->offset);
    }
}

static void emit_linux_routine_epilogue(symtab *ptab)
{
    if(ptab->defn == DEF_PROG)
        return;

    if(ptab->defn == DEF_FUNCT)
    {
        switch(ptab->type->type_id)
        {
        case  TYPE_INTEGER:
        case  TYPE_BOOLEAN:
            /* fprintf(codfp,"\n\t\tmovl\t%s, %%eax\n", LABEL_RETVAL); */
            fprintf(codfp,"\n\t\tmovl\t%s, %%eax\n", LABEL_RETVAL); 
            break;
        case  TYPE_CHAR:
            fprintf(codfp,"\n\t\txorb\t%%ah, %%ah\n");
            fprintf(codfp,"\n\t\tmovl\t%s, %%eax\n",
							LABEL_RETVAL); 
			/*
            fprintf(codfp,"\n\t\tmovl\t%s, %%eax\n",
                    LABEL_RETVAL);
			*/
            break;
        case  TYPE_REAL:
            break;
        }
    }
	/*
    fprintf(codfp,"\t\tmov\tsp,bp\n");
    fprintf(codfp,"\t\tpop\tbp\n");
	*/
	fprintf(codfp, "\t\tleave\n");
	/*
    fprintf(codfp,"\t\tret\t%04xh\n",ptab->args_size + 2);
    fprintf(codfp,"\n%s\t\tendp\n",ptab->rname);
	*/
	fprintf(codfp, "\t\tret\n");
	fprintf(codfp, "\t\t.size %s, .-%s\n",
			ptab->rname, ptab->rname);
}

static void emit_linux_dos_push_op(Type ptype)
{
    switch(ptype->type_id)
    {
    case  TYPE_CHAR:
    case  TYPE_BOOLEAN:
    case  TYPE_INTEGER:
        fprintf(codfp,"\t\tpushl\t%%eax\n");
        break;
    case  TYPE_REAL:
        fprintf(codfp,"\t\tpushl\t%%edx\n");
        fprintf(codfp,"\t\tpushl\t%%eax\n");
        break;
    }
}

static void emit_linux_load_value(symbol *p)
{
    if(p->defn == DEF_VARPARA)
    {
        /* fprintf(codfp,"\t\tmov\tbx,word ptr [bp+4]\n"); */
        fprintf(codfp,"\t\tmovl\t4(%%ebp), %%ebx\n");
        switch(p->type->type_id)
        {
        case  TYPE_CHAR:
			/*
            fprintf(codfp,"\t\txor\tah, ah\n");
            fprintf(codfp,"\t\tmov\tal, byte ptr [bx]\n");
			*/
            fprintf(codfp,"\t\txorl\t%%eax, %%eax\n");
            fprintf(codfp,"\t\tmovb\t(%%ebx), %%al\n");
            break;
        case TYPE_REAL:
			/*
            fprintf(codfp,"\t\tmov\tax,word ptr [bx]\n");
            fprintf(codfp,"\t\tmov\tdx,word ptr [bx+2]\n");
			*/
            fprintf(codfp,"\t\tmovl\t(%%ebx), %%eax\n");
			fprintf(codfp, "\t\tmovl\t4(%%ebx), %%edx\n");
            break;
        case  TYPE_INTEGER:
        case  TYPE_BOOLEAN:
            /* fprintf(codfp,"\t\tmov\tax,word ptr [bx]\n"); */
            fprintf(codfp,"\t\tmovl\t(%%ebx), %%eax\n");
            break;
        }
    }
    else if (p->tab->level==0
             ||p->tab==top_symtab_stack())
    {
        switch(p->type->type_id)
        {
        case  TYPE_CHAR:
				/*
            fprintf(codfp,"\t\tsub\tax.ax\n");
            fprintf(codfp,"\b\t\tmov\tal, byte  ptr %s\n"
                    ,p->rname);
					*/
            fprintf(codfp,"\t\tsubl\t%%eax, %%eax\n");
            fprintf(codfp,"\b\t\tmovb\t%s, %%al\n"
                    ,p->rname);
            break;
        case  	TYPE_REAL:
            break;
        case  	TYPE_INTEGER:
        case  	TYPE_BOOLEAN:
            /* fprintf(codfp,"\t\t\tmov\tax, word ptr %s\n",p->rname); */
            fprintf(codfp,"\t\t\tmovl\t%s, %%eax\n",p->rname);
            break;
        case 	TYPE_ARRAY:
            fprintf(codfp,"\t\tpopl\t%%ebx\n");
            if(p->type_link->last->type->type_id ==
                    TYPE_INTEGER
                    ||p->type_link->last->type->type_id ==
                    TYPE_BOOLEAN)
                fprintf(codfp, "\t\tmovl\t(%%ebx), %%eax\n");
            else if (p->type_link->last->type->type_id ==
                     TYPE_CHAR)
                fprintf(codfp, "\t\tmovb\t(%%ebx), %%al\n");
            break;
        default:
            break;
        }
    }
}

static void emit_linux_load_address(symbol *p)
{
    symtab *ptab;
    int  n,i;

    switch(p->defn)
    {
    case DEF_VARPARA:
        fprintf(codfp, "\t\tmovl\t%s, %%eax\n",
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
            fprintf(codfp, "\t\tleal\t%s, %%eax\n",
                    p->rname);
        }
        else
        {
            ptab = top_symtab_stack();
            n = p->tab->level - ptab->level + 1;
            fprintf(codfp,"\t\tmovl\t%%ebp, %%ebx\n");
            for (i = 0; i < n; i++)
                fprintf(codfp, "\t\tmovl\t%s, %%ebp\n",
                        LABEL_SLINK);
            fprintf(codfp, "\t\tleal\t%s, %%eax\n",
                    p->rname);
            fprintf(codfp,"\t\tmovl\t%%ebx, %%ebp\n");
        }
        break;
    case DEF_VALPARA:
        fprintf(codfp, "\t\tleal\t%s, %%eax\n",
                p->rname);
        break;
    default:
        break;
    }
}

static void emit_linux_load_field(symbol*p)
{
    if(!p)
        return;
    fprintf(codfp, "\t\tpopl\t%%ebx\n");
    switch(p->type->type_id)
    {
    case  TYPE_INTEGER:
    case  TYPE_BOOLEAN:
        fprintf(codfp,"\t\tmovl\t(%%ebx), %%eax\n");
        break;
    case  TYPE_CHAR:
        fprintf(codfp,"\t\tmovb\t(%%ebx), %%al\n");
        break;
    default:
        break;
    }
}

static void do_linux_function_assign(symtab *ptab, int srctype)
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
		fprintf(codfp, "\t\txorb\t%%ah, %%ah\n");
		fprintf(codfp, "\t\tmovl\t%%eax, %s\n",
						LABEL_RETVAL);
		/*
        fprintf(codfp,"\t\txorb\t%%ah, %%ah\n");
        fprintf(codfp,"\t\tmovl\t%%al, %s\n",
                LABEL_RETVAL);
		*/
        break;
    case  TYPE_BOOLEAN:
    case  TYPE_INTEGER:
		fprintf(codfp, "\t\tmovl\t%%eax, %s\n",
				LABEL_RETVAL);
		/*
        fprintf(codfp,"\t\tmovl\t%%eax, %s\n",
                LABEL_RETVAL);
		*/
        break;
    case  TYPE_REAL:
        break;
    default:
        break;
    }
}

static void do_linux_procedure_call(symtab *ptab)
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
        fprintf(codfp,"\t\tpushl\t%%ebp\n");
    }
    else if (callee->level == caller->level)
    {
        fprintf(codfp, "\t\tpushl\t%s\n",
                LABEL_SLINK);
    }
    else if(callee->level < caller->level)
    {
        fprintf(codfp,"\t\tmovl\t%%ebp, %%ebx\n");
        for(i = 0; i < n; i++)
            fprintf(codfp,"\t\tmovl\t%s, %%ebp\n",
                    LABEL_SLINK);
        fprintf(codfp,"\t\tpushl\t%%ebp\n");
        fprintf(codfp,"\t\tmovl\t%%ebx, %%ebp\n");
    }
    else
        return;
    fprintf(codfp,"\t\tcall\t%s\n", ptab->rname);
	fprintf(codfp, "\t\taddl\t$%d, %%esp\n", ptab->args_size + IR->intmetric.size);

}

static void do_linux_first_arg(int ptype)
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
        break;
    case  TYPE_CHAR:
        fprintf(codfp,"\t\txorb\t%%ah, %%ah\n");
    case  TYPE_INTEGER:
    case  TYPE_BOOLEAN:
    default:
        fprintf(codfp,"\t\tpushl\t%%eax\n");
        break;
    }
}

static void do_linux_args(int ptype)
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
        break;
    case TYPE_CHAR:
        fprintf(codfp,"\t\txorb\t%%ah, %%ah\n");
    case  TYPE_INTEGER:
    case  TYPE_BOOLEAN:
    default:
        fprintf(codfp,"\t\tpushl\t%%eax\n");
        break;
    }
}

static void do_linux_assign(symbol *p, int srctype)
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
        fprintf(codfp,"\t\tpushl\t%%eax\n");
        fprintf(codfp,"\t\tmovl\t%s, %%eax\n",
                p->rname);
        break;
    case DEF_FIELD:
        fprintf(codfp,"\t\tpopl\t%%ebx\n");
        if(p->type->type_id == TYPE_INTEGER
                ||p->type->type_id == TYPE_BOOLEAN)
            fprintf(codfp,"\t\tmovl\t%%eax, (%%ebx)\n");
        else if (p->type->type_id == TYPE_CHAR)
            fprintf(codfp,"\t\tmovb\t%%al, (%%ebx)\n");
        return;
    case DEF_VAR:
    case DEF_CONST:
    case DEF_ELEMENT:
        if(p->type->type_id == TYPE_ARRAY)
        {
            fprintf(codfp,"\t\tpushl\t%%eax\n");
            break;
        }
        if(p->tab->level == 0
                ||p->type->type_id == TYPE_REAL)
            break;
        else if( p->tab->level
                 && p->tab == top_symtab_stack())
        {
            fprintf(codfp,"\t\tpushl\t%%eax\n");
            fprintf(codfp,"\t\tleal\t%s, %%eax\n",
                    p->rname);
            fprintf(codfp,"\t\tpushl\t%%eax\n");
            break;
        }
        else
        {
            ptab = top_symtab_stack();
            n = ptab->level - p->tab->level;
            fprintf(codfp,"\t\tpushl\t%%eax\n");
            fprintf(codfp,"\t\tmovl\t%%ebp, %%ebx\n");
            for(i =0;i<n;i++)
                fprintf(codfp,"\t\tmovl\t%s,%%ebp\n",
                        LABEL_SLINK);
            fprintf(codfp,"\t\tleal\t%s, %%eax\n",
                    p->rname);
            fprintf(codfp,"\t\tmovl\t%%ebx, %%ebp\n");
            fprintf(codfp,"\t\tpushl\t%%eax\n");
        }
        break;
    case DEF_VALPARA:
        if(p->tab->level==0
                || p->tab==top_symtab_stack())
            fprintf(codfp,"\t\tpushl\t%%eax\n");
        fprintf(codfp,"\t\tleal\t%s, %%eax\n",
                p->rname);
        fprintf(codfp,"\t\rpushl\t%%eax\n");
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
            fprintf(codfp,"\t\tpopl\t%%bx\n");
            fprintf(codfp,"\t\tpopl\t%%ax\n");
            fprintf(codfp,"\tmovb\t%%al, (%%bx)\n");
        }
        else
            fprintf(codfp,"\t\tmovb\t%%al,%s\n",
                    p->rname);

        break;
    case TYPE_INTEGER:
    case TYPE_BOOLEAN:
        if (p->tab->level)
        {
            fprintf(codfp, "\t\tpopl\t%%ebx\n");
            fprintf(codfp, "\t\tpopl\t%%eax\n");
            fprintf(codfp, "\t\tmovl\t%%eax, (%%ebx)\n");
        }
        else
            fprintf(codfp, "\t\tmovl\t%%eax, %s\n",p->rname);
        break;

    case TYPE_STRING:
        fprintf(codfp, "\t\tmovl\t$%d, %%cx\n",
                strlen(p->v.s));
        fprintf(codfp, "\t\tpopl\tesi\n");
        fprintf(codfp, "\t\tpopl\tedi\n");
        fprintf(codfp, "\t\tmovl\t%%ds, %%eax\n");
        fprintf(codfp, "\t\tmovl\t%%eax, %%es\n");
        fprintf(codfp, "\t\tcld\n");
        fprintf(codfp, "\t\trep\tmovsb\n");
        break;
    case TYPE_REAL:
        break;
    case TYPE_ARRAY:
        if (p->type_link->last->type->type_id == TYPE_INTEGER
                ||p->type_link->last->type->type_id == TYPE_BOOLEAN )
        {
			/*
            fprintf(codfp, "\t\tpop\tax\n");
            fprintf(codfp, "\t\tpop\tbx\n");
            fprintf(codfp, "\t\tmov\tword ptr [bx],ax\n");
			*/
            fprintf(codfp, "\t\tpopl\t%%eax\n");
            fprintf(codfp, "\t\tpopl\t%%ebx\n");
            fprintf(codfp, "\t\tmovl\t%%eax, (%%ebx)\n");

        }
        else if (p->type_link->last->type->type_id ==
                 TYPE_CHAR)
        {
			/*
            fprintf(codfp, "\t\tpop\tax\n");
            fprintf(codfp, "\t\tpop\tbx\n");
            fprintf(codfp, "\t\tmov\tbyte ptr [bx],al\n");
			*/
            fprintf(codfp, "\t\tpopl\t%%eax\n");
            fprintf(codfp, "\t\tpopl\t%%ebx\n");
            fprintf(codfp, "\t\tmovb\t%%al, (%%ebx)\n");
        }
        break;
    default:
        break;
    }
}

static void do_linux_cond_jump(int true_or_false, Symbol label)
{
    fprintf(codfp, "\t\tcmpl\t$1, %%eax\n");

    if (true_or_false)
        fprintf(codfp, "\t\tjge\t%s\n", label->name);
    else
        fprintf(codfp, "\t\tjl\t%s\n", label->name);
}

static void do_linux_jump(Symbol label)
{
    fprintf(codfp, "\t\tjmp %s\n", label->name);
}

static void do_linux_label(Symbol label)
{
    fprintf(codfp, "%s:\n", label->name);
}

static void do_linux_incr(Symbol sym)
{
    switch (sym->type->type_id)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "\t\tincl %s\n", sym->rname);
        break;
    case TYPE_CHAR:
        fprintf(codfp, "\t\tincb %s\n", sym->rname);
        break;
    default:
        parse_error("incr instruction only support char, boolean and int.", "");
        break;
    }
}

static void do_linux_decr(Symbol sym)
{
    switch (sym->type->type_id)
    {
    case TYPE_BOOLEAN:
    case TYPE_INTEGER:
        fprintf(codfp, "decl %s\n", sym->rname);
        break;
    case TYPE_CHAR:
        fprintf(codfp, "decb %s\n", sym->rname);
        break;
    default:
        parse_error("incr instruction only support char, boolean and int.", "");
        break;
    }
}

static int jump_index = 0;

static void do_linux_expression(Type type, int op)
{

    if (type == NULL)
    {
        return;
    }

    if (type->type_id == TYPE_INTEGER
            || type->type_id == TYPE_BOOLEAN)
    {
        fprintf(codfp, "\t\tpopl\t%%edx\n");
        fprintf(codfp, "\t\tcmpl\t%%eax, %%edx\n");
    }
    else if(type->type_id == TYPE_CHAR)
    {
        fprintf(codfp, "\t\tpopl\t%%edx\n");
        fprintf(codfp, "\t\tcmpb\t%%al, %%dl\n");
    }
    else if (type->type_id == TYPE_STRING)
    {
        fprintf(codfp,"\t\tpopl\t%%edi\n");
        fprintf(codfp, "\t\tpopl\t%%esi\n");
        fprintf(codfp, "\t\tmovl\t%%ds, %%eax\n");
        fprintf(codfp, "\t\tmovl\t%%eax, %%es\n");
        fprintf(codfp, "\t\tcld\n");
        fprintf(codfp, "\t\tmovl\t$%d, %%ecx\n",strlen(p->v.s));
        fprintf(codfp, "\t\trepe\t\tcmpsb\n");
    }
    else
    {
        parse_error("standard type expected.", "");
        return;
    }

    fprintf(codfp, "\t\tmovl\t$1, %%eax\n");

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

    fprintf(codfp, "\t\txorl\t%%eax, %%eax\n");
    fprintf(codfp, "j_%03d:\n", jump_index);
}

static void do_linux_negate(symbol *p)
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
        fprintf(codfp, "\t\tnegl\t%%eax\n");
        break;
    default:
        parse_error("operand type do not match operator.", "");
        break;
    }
}

static void do_linux_expr(Type type, int op)
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
            fprintf(codfp,"\t\tpopl\t%%edx\n");
            fprintf(codfp, "\t\taddl\t%%edx, %%eax\n");
        }
        else
            parse_error("integer or real type expected.","");
        break;
    case SUB:
        if (type->type_id == TYPE_REAL)
        {}
        else if (type->type_id==TYPE_INTEGER)
        {
            fprintf(codfp, "\t\tpopl\t%%edx\n");
            fprintf(codfp, "\t\tsubl\t%%eax, %%edx\n");
            fprintf(codfp, "\t\tmovl\t%%edx, %%eax\n");
        }
        else
            parse_error("integer or real type expected.", "");
        break;
    case OR:
        if (type->type_id == TYPE_BOOLEAN)
        {
            fprintf(codfp, "\t\tpopl\t%%edx\n");
            fprintf(codfp, "\t\torl\t%%edx, %%eax\n");
        }
        else
            parse_error("boolean type expected.", "");
        break;
    default:
        break;
    }
}

static void do_linux_term(Type type, int op)
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
            fprintf(codfp, "\t\tpopl\t%%edx\n");
            fprintf(codfp, "\t\timul\t%%edx\n");
        }
        else if (type->type_id == TYPE_REAL)
        {}
        else
            parse_error("integer or real type expected.", "");
        break;
    case DIV:
        if (type->type_id == TYPE_INTEGER)
        {
            fprintf(codfp,"\t\tmovl\t%%eax, %%ecx\n");
            fprintf(codfp, "\t\tpopl\t%%eax\n");
            fprintf(codfp, "\t\tsubl\t%%edx,%%edx\n");
            fprintf(codfp, "\t\tidiv\t%%ecx\n");
        }
        else
            parse_error("integer type expected.", "");
        break;
    case MOD:
        if (type->type_id == TYPE_INTEGER)
        {
            fprintf(codfp, "\t\tmovl\t%%eax, %%ecx\n");
            fprintf(codfp, "\t\tpopl\t%%eax\n");
            fprintf(codfp, "\t\tsubl\t%%edx,%%edx\n");
            fprintf(codfp, "\t\tidiv\t%%ecx\n");
            fprintf(codfp, "\t\tmovl\t%%edx, %%eax\n");
        }
        else
            parse_error("integer type expected.","");
        break;
    case AND:
        if (type->type_id != TYPE_BOOLEAN)
            parse_error("boolean type expected.","");
        else
        {
            fprintf(codfp, "\t\tpopl\t%%edx\n");
            fprintf(codfp, "\t\tandl\t%%edx, %%eax\n");
        }
        break;
    default:
        break;
    }
}

static void do_linux_factor(symbol *p)
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
            fprintf(codfp, "\t\tmovl\t$%d, %%eax\n",p->v.b);
            break;
        case TYPE_INTEGER:
            if (p->defn == DEF_ELEMENT)
			{
                fprintf(codfp, "\t\tmovl\t$%d, %%eax\n",
                        p->v.i);
			}
            else
			{
				short tvi = (short)p->v.i;

                fprintf(codfp, "\t\tmovl\t$%d, %%eax\n",
                        tvi);
			}
            break;
        case TYPE_CHAR:
            fprintf(codfp, "\t\tmovb\t$%d,%%al\n",p->v.c);
            break;
        case TYPE_REAL:
            break;
        case TYPE_STRING:
            fprintf(codfp, "\t\tmovl\t%s, %%eax\n",p->rname);
            break;
        default:
            break;
        }
    }
    else if (p->defn == DEF_VARPARA)
    {
        fprintf(codfp, "\t\tmovl\t%s, %%ebx\n",
                p->rname);
        fprintf(codfp, "\t\tmovl\t(%%ebx), %%eax\n");
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
                fprintf(codfp, "\t\tsubl\t%%eax,%%eax\n");
                fprintf(codfp, "\t\tmovb\t%s, %%al\n",p->rname);
                break;
            case TYPE_BOOLEAN:
            case TYPE_INTEGER:
                fprintf(codfp, "\t\tmovl\t%s, %%eax\n",p->rname);
                break;
            case TYPE_REAL:
                break;
            }
        }
        if (p->defn == DEF_VAR)
        {
            ptab = top_symtab_stack();
            n = ptab->level - p->tab->level;
            if (n <= 0)
                return;
            fprintf(codfp, "\t\tmovl\t%%ebx,%%ebp\n");
            for(i = 0; i<n; i++)
                fprintf(codfp, "\t\tmovl\t%s, %%ebp\n",
                        LABEL_SLINK);
            switch(p->type->type_id)
            {
            case TYPE_INTEGER:
            case TYPE_BOOLEAN:
                fprintf(codfp, "\t\tmovl\t%s, %%eax\n",p->rname);
                break;
            case TYPE_CHAR:
                fprintf(codfp, "\t\tmovb\t%s, %%al\n",p->rname);
                break;
            default:
                break;
            }
            fprintf(codfp,"\t\tmovl\t%%ebx, %%ebp\n");
        }
    }
}

static void do_linux_not_factor(symbol *p)
{
    if (!p)
        return;
    if (p->type->type_id!= TYPE_BOOLEAN)
        parse_error("Boolean type expected. ","");

    do_linux_factor(p);

    fprintf(codfp, "\t\tandl\t$1, %%eax\n");
    fprintf(codfp, "\t\txorl\t$1, %%eax\n");
}

static void do_linux_array_factor(symbol *p)
{
    if (p->type_link->first->v.i >= 0)
        fprintf(codfp, "\t\tsubl\t$%d, %%eax\n",
                p->type_link->first->v.i);
    else
        fprintf(codfp, "\t\tsubl\t$-%d, %%eax\n",
                -(p->type_link->first->v.i));
    fprintf(codfp, "\t\tmovl\t$%d, %%ecx\n",
            get_symbol_size(p->type_link->last));
    fprintf(codfp, "\t\timul\t%%ecx\n");
    fprintf(codfp, "\t\tpopl\t%%edx\n");
    if (p->tab->level)
        fprintf(codfp, "\t\tsubl\t%%eax, %%edx\n");
    else
        fprintf(codfp, "\t\taddl\t%%eax, %%edx\n");

    fprintf(codfp, "\t\tpushl\t%%edx\n");
}

static void do_linux_record_factor(symbol *var, symbol *p)
{
    if (!var || !p || p->defn != DEF_FIELD)
        return;
    fprintf(codfp, "\t\tpopl\t%%eax\n");
    fprintf(codfp, "\t\tmovl\t$%d, %%edx\n",p->offset);
    if (var->tab->level)
        fprintf(codfp, "\t\tsubl\t%%edx, %%eax\n");
    else
        fprintf(codfp, "\t\taddl\t%%edx, %%eax\n");
    fprintf(codfp, "\t\tpushl\t%%eax\n");
}

static int programbegin(Env *global)
{
    emit_linux_program_prologue(global->u.program.tab);
    return 0;
}

static int programend(Env *global)
{
    emit_linux_program_epilogue(global->u.program.tab);
    return 0;
}

static int mainbegin(Env *main)
{
    emit_linux_main_prologue(main->u.main.tab);
    return 0;
}

static int mainend(Env *main)
{
    emit_linux_main_epilogue(main->u.main.tab);
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

static int gen_linux_code(Node rootnode)
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

        gen_linux_code(rootnode->kids[0]);
        do_linux_first_arg(rootnode->kids[0]->type->type_id);

        pnode = rootnode->kids[1];
        while(pnode)
        {
            if (!pnode->kids[0])
                break;

            gen_linux_code(pnode->kids[0]);
            do_linux_args(pnode->kids[0]->type->type_id);

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
            ret = gen_linux_code(rootnode->kids[0]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        emit_linux_dos_push_op(rootnode->kids[0]->type);
        if (rootnode->kids[1])
        {
            ret = gen_linux_code(rootnode->kids[1]);
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
            ret = gen_linux_code(rootnode->kids[0]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        emit_linux_dos_push_op(rootnode->kids[0]->type);
        if (rootnode->kids[1])
        {
            ret = gen_linux_code(rootnode->kids[1]);
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
            ret = gen_linux_code(rootnode->kids[0]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        emit_linux_dos_push_op(rootnode->kids[0]->type);
        if (rootnode->kids[1])
        {
            ret = gen_linux_code(rootnode->kids[1]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }
        break;
    case ARRAY:
        emit_linux_load_address(rootnode->syms[0]);
        emit_linux_dos_push_op(find_type_by_id(TYPE_INTEGER));
        if (rootnode->kids[0])
        {
            ret = gen_linux_code(rootnode->kids[0]);
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
        		emit_linux_load_address(rootnode->kids[0]->syms[0]);
        		emit_linux_dos_push_op(TYPE_INTEGER);
        	}
        	else if (generic(rootnode->kids[0]->op) == FIELD)
        	{
        		emit_linux_load_address(rootnode->syms[0]);
        		emit_linux_dos_push_op(TYPE_INTEGER);
        		do_linux_record_factor(rootnode->syms[0], rootnode->syms[1]);
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
            ret = gen_linux_code(rootnode->kids[0]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }

        if (rootnode->kids[1])
        {
            ret = gen_linux_code(rootnode->kids[1]);
            if (ret < 0)
            {
                gen_level --;
                return ret;
            }
        }

        if (rootnode->kids[2])
        {
            ret = gen_linux_code(rootnode->kids[2]);
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
        do_linux_array_factor(rootnode->syms[0]);
        break;
    case CNST:
        do_linux_factor(rootnode->syms[0]);
        break;
    case FIELD:
        emit_linux_load_address(rootnode->syms[0]);
        emit_linux_dos_push_op(find_type_by_id(TYPE_INTEGER));
        do_linux_record_factor(rootnode->syms[0], rootnode->syms[1]);
        /* emit_linux_load_field(rootnode->syms[1]); */
        break;
    case HEADER:
        emit_linux_routine_prologue(rootnode->symtab);
        break;
    case TAIL:
        emit_linux_routine_epilogue(rootnode->symtab);
        break;
    case NOT:
        do_linux_not_factor(rootnode->kids[0]->syms[0]);
        break;
    case NEG:
        do_linux_negate(rootnode->kids[0]->syms[0]);
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
                    do_linux_function_assign(ptab, rootnode->kids[0]->type->type_id);
                else
                {
                    parse_error("Undeclared identifier.", p->name);
                    gen_level --;
                    return ERROR_UNDECLARE;
                }
            }
            else
            {
                do_linux_assign(p, rootnode->kids[0]->type->type_id);
            }
        }
        break;
    case CALL:
        do_linux_procedure_call(rootnode->symtab);
        pop_call_stack();
        break;
    case SYS:

        emit_linux_address = 1;		/* signal the ADDRG to generate address. */
        if ((rootnode->kids[0] == NULL) ||
                (rootnode->kids[0]->kids[0] == NULL) ||
                (rootnode->kids[0]->kids[1] == NULL))
        {
            /* do system call without args, or with only one arg. */
            if (rootnode->kids[0])
			{
                if (rootnode->kids[0]->kids[0])
                    gen_linux_code(rootnode->kids[0]->kids[0]);
                else
                    gen_linux_code(rootnode->kids[0]);
			}
            do_linux_sys_routine(rootnode->u.sys_id, rootnode->kids[0]->type->type_id);
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
                gen_linux_code(rootnode->kids[0]->kids[0]);
                do_linux_sys_routine(rootnode->u.sys_id, rootnode->kids[0]->kids[0]->type->type_id);

                pnode = rootnode->kids[0]->kids[1];
                while(pnode)
                {
                    if (!pnode->kids[0])
                        break;

                    gen_linux_code(pnode->kids[0]);
                    do_linux_sys_routine(rootnode->u.sys_id, pnode->kids[0]->type->type_id);
                    pnode = pnode->kids[1];
                }

                break;
            }
        }
        emit_linux_address = 0;		/* clear signal */
        break;
    case COND:
        do_linux_cond_jump(rootnode->u.cond.true_or_false, rootnode->u.cond.label);
        break;
    case JUMP:
        do_linux_jump(rootnode->syms[0]);
        break;
    case LABEL:
        do_linux_label(rootnode->syms[0]);
        break;
    case INCR:
        /*
         * variable is in first child of INCR node.
         * generally an ADDRG node.
         */
        assert(rootnode->kids[0]->syms[0]);
        do_linux_incr(rootnode->kids[0]->syms[0]);
        break;
    case DECR:
        /*
         * variable is in first child of DECR node.
         * generally an ADDRG node.
         */
        assert(rootnode->kids[0]->syms[0]);
        do_linux_decr(rootnode->kids[0]->syms[0]);
        break;
    case LOAD:
        if (rootnode->kids[0] == NULL)
        {
            /* simple const or id. */
            do_linux_factor(rootnode->syms[0]);
        }
        else if (generic(rootnode->kids[0]->op) == ARRAY)
        {
            emit_linux_load_value(rootnode->kids[0]->syms[0]);
        }
        else
        {
            emit_linux_load_field(rootnode->kids[0]->syms[1]);
        }
        break;
    case EQ:
    case NE:
    case GT:
    case GE:
    case LE:
    case LT:
        do_linux_expression(rootnode->kids[1]->type, rootnode->op);
        break;
    case ADD:
    case SUB:
    case OR:
        do_linux_expr(rootnode->kids[1]->type, rootnode->op);
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
        	ret = gen_linux_code(rootnode->kids[0]);
        	if (ret < 0) {
        		gen_level --;
        		return ret;
        	}
        }
        */
        do_linux_term(rootnode->kids[1]->type, rootnode->op);
        break;
    case BLOCKBEG:
    case BLOCKEND:
        break;
    case ADDRG:
        if (emit_linux_address)
            emit_linux_load_address(rootnode->syms[0]);
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
        if ((ret = gen_linux_code((Node)(cp->x))) < 0)
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

Interface x86_linux_interface = {
		/* type interface */
		{1, 1},		/* charmetric */
		{2, 2},		/* shortmetric */
		{4, 4},		/* intmetric */
		{4, 4},		/* floatmetric */
		{8, 8},		/* doublemetric */
		{4, 4},		/* pointermetric */
		{4, 4},		/* structmetric */

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
		gen_linux_code,
		functionprocess,
		defexport,
		defimport,
};

