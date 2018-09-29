#define   _ERROR_C
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <ctype.h>
#include "common.h"
#define  MAX_ERR  (8)

int error_count = 0;
int warn_count = 0;

int line_no;
int line_pos;
char line_buf[MAX_LINE_LENGTH];

void clear ();
FILE *errfp;
char *pasname;
static char ebuf[MAX_ERR][64];

void print_result(char *fname)
{
    printf("\n%s : %d lines,%d errors.\n",
           fname, line_no, error_count);

    if (!error_count)
        printf("OK!\n\n");
}

int err_occur( )
{
    return error_count;
}

void internal_error(char *info)
{

    sprintf(ebuf[error_count++], "Internal Error %s\n", info);
    fprintf(errfp, "Internal Error (%d): %s\n", line_no, info);

    if (error_count >= MAX_ERR)
    {
        clear();
        print_result(pasname);
        exit(0);
    }
}

static void print_pos(FILE *fp)
{
    int i;

    for (i = 0; i < line_pos; i++)
    {
        if (line_buf[i] == '\t')
            fprintf(fp, "\t");
        else
            fprintf(fp, " ");
    }

    fprintf(fp, "^");
}

void parse_error(char *info, char *name)
{

    fprintf(errfp, "\nError at line %d:\n", line_no);
    fprintf(errfp, "%s\n", line_buf);
    print_pos(errfp);

    fprintf(stderr, "\nError at line %d:\n", line_no);
    fprintf(stderr, "%s\n", line_buf);
    print_pos(stderr);

    if (*name)
    {
        fprintf(errfp, " : %s %s", info, name);
        fprintf(stderr, " : %s %s", info, name);

        snprintf(ebuf[error_count++], sizeof(ebuf[error_count++]) - 1, "\nError (%d) : %s '%s'",
                 line_no, info, name);
    }
    else
    {
        fprintf(errfp, " : %s \n", info);
        fprintf(stderr, " : %s \n", info);

        snprintf(ebuf[error_count++],  sizeof(ebuf[error_count++]) - 1 ,"Error (%d) : %s\n",
                 line_no, info);
    }

    if (error_count >= MAX_ERR)
    {
        clear();
        print_result(pasname);
        exit(1);
    }
}

void lex_error(char *info)
{

    fprintf(errfp, "\nError at line %d:\n", line_no);
    fprintf(errfp, "%s\n", line_buf);
    print_pos(errfp);

    fprintf(stderr, "\nError at line %d:\n", line_no);
    fprintf(stderr, "%s\n", line_buf);
    print_pos(stderr);

    snprintf(ebuf[error_count++], sizeof(ebuf[error_count++]) - 1, ": %s", info);
    fprintf(errfp, "\nError (%d) : %s", line_no, info);
    fprintf(stderr, "\nError (%d) : %s", line_no, info);
}

void yyerror(char *info)
{
    parse_error(info,"");
}

