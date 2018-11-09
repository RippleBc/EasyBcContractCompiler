#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

FILE *codfp, *errfp;

char codname[FILE_NAME_LEN];
char errname[FILE_NAME_LEN];

void clear();
void signup();

extern union header *arena[LASTARENA];

Interface x64_vm_interface = {
    {1, 4},     /* charmetric */
    {2, 4},     /* shortmetric */
    {4, 4},     /* intmetric */
    {4, 4},     /* floatmetric */
    {4, 8},     /* doublemetric */
    {4, 4},     /* pointermetric */
    {4, 4},     /* structmetric */
};

Interface *IR = &x64_vm_interface;

union {
    int number;
    char s;
} _host_byte_order_example_;
 
boolean testBigEndin() {
    _host_byte_order_example_.number = 0x01000002;
    return (_host_byte_order_example_.s == 0x01);
}

void prepare_file(char *fname)
{
    char *p;

    for (p = fname; *p; p++)
        *p = tolower(*p);

    if (strstr(fname, ".pas"))
    {
        for (; p > fname; p--)
        {
            if (*p == '.')
                break;

        }
        *p = '\0';
    }

    snprintf(codname, sizeof(codname), "%s.cod", fname);
    snprintf(errname, sizeof(errname), "%s.err", fname);
    
    codfp = fopen(codname, "wt");
    errfp = fopen(errname, "wt");

    if (!codfp || !errfp)
    {
        printf("File open error!\n");
        exit(1);
    }
}


int main(int argc, char **argv)
{
    int dargc;
    char **arg, **dargv;

    if (testBigEndin()) {
        g_is_big_endian = true;
    } else {
        g_is_big_endian = false;
    }

    if (argc == 1)
    {
        printf("\nUsage :%s [-d stad] filename[.pas]\n\n", argv[0]);
        return 1;
    }

    init_op_code();

    arg = argv + 1;
    dargc = 0;
    dargv = malloc(argc * sizeof(char *));

    /*
     * arguments not recognized by main is pased to 
     * target program_begin
     */
    while(arg)
    {
        if (**(arg) == '-')
        {
            switch(arg[0][1])
            {
            case 'd':
                {
                    char *p = arg[1];
                    while (*p)
                    {
                        switch(*p++)
                        {
                        case 's':
                            dump_source = 1;
                            break;
                        case 'a':
                            dump_ast = 1;
                            break;
                        case 't':
                            dump_token = 1;
                            break;
                        case 'd':
                            dump_dag = 1;
                            break;
                        default:
                            printf("Unkown dump option %c.\n", *(p - 1));
                            break;
                        }
                    }
                }
                arg++;
                arg++;
                break;
            default:
                dargv[dargc++] = *arg++;
                dargv[dargc++] = *arg++;
                break;
            }
        }
        else
        {
            prepare_file(arg[0]);
            break;
        }
    }

    
    clear();

    finalize();

    free(dargv);

    return 0;
}

void clear()
{
    fclose(codfp);
    fclose(errfp);
    unlink(codname);
    unlink(errname);
}

void signup()
{
    printf("\n");
    printf("Simple Pascal Language Vm Version %s\n", _PC_VER_);
}

