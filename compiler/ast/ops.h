#ifndef _OPS_TPC_H
#define _OPS_TPC_H

/* system routine and functions. */
enum {
    SYS_ABS = 1,
    SYS_SQR,
    SYS_SQRT,
    SYS_READLN,
    SYS_WRITELN
};

enum {
    /* node and tree operations . */
    CNST = 1 << 4,
    ARG = 2 << 4,
    ASGN = 3 << 4,
    INDIR = 4 << 4,
    SYS = 5 << 4, /* for sys routine. */
    CVC = 6 << 4,
    CVF = 7 << 4,
    CVI = 8 << 4,
    CVUC = 9 << 4,
    CVUI = 10 << 4,
    CVB = 11 << 4,
    NEG = 12 << 4,
    CALL = 13 << 4,
    LOAD = 14 << 4,
    ADDRG = 15 << 4,
    ADD = 16 << 4,
    SUB = 17 << 4,
    LSH = 18 << 4,
    MOD = 19 << 4,
    RSH = 20 << 4,
    BAND = 21 << 4,
    BCOM = 22 << 4,
    BOR = 23 << 4,
    BXOR = 24 << 4,
    DIV = 25 << 4,
    MUL = 26 << 4,
    EQ = 27 << 4,
    GE = 28 << 4,
    GT = 29 << 4,
    LE = 30 << 4,
    LT = 31 << 4,
    NE = 32 << 4,
    JUMP = 33 << 4,
    LABEL = 34 << 4,
    AND = 35 << 4,
    NOT = 36 << 4,
    OR = 37 << 4,
    COND = 38 << 4,
    RIGHT = 39 << 4,
    FIELD = 40 << 4,
    INCR = 41 << 4,
    DECR = 42 << 4,
    ARRAY = 43 << 4,
    /* operations only appear in trees. */
    HEADER = 44 << 4, /* function header tree. */
    TAIL = 45 << 4, /* function end tree. */
    BLOCKBEG = 46 << 4, /* block begin. */
    BLOCKEND = 47 << 4, /* block end. */
    /* last */
    LASTOP
};

typedef struct _ops_entry
{
    char *name;
    int	op;
}
ops_entry;

char *get_op_name(int op);
int get_op(char *name);

#endif
