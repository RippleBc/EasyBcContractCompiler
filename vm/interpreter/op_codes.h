#ifndef _OP_CODES_H_
#define _OP_CODES_H_

extern struct _op_code_ {
    int code;
    char name[NAME_LEN];
    int in;
    int out;
};

#endif