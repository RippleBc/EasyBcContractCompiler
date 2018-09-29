#define   _X86LIB_C
#include  "common.h"
#include  "symtab.h"
#include  "x86lib.h"
#include   _YTAB_H_

int rout_index = 0;

void do_sys_routine(int routine_id, int arg_type)
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

void emit_read1(int arg_type)
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
        parse_error("operand type do not match operator.");
        break;
    }
}

void emit_write1(int arg_type)
{
    switch(arg_type)
    {
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

void emit_writeln(int arg_type)
{
    switch(arg_type)
    {
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
        fprintf(codfp, "\t\tcall\t_write_string\n");
        break;
    default:
        break;
    }
}

void emit_abs(int arg_type)
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

void emit_sqr(int arg_type)
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

void emit_odd(int arg_type)
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

void emit_sqrt(int arg_type)
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
