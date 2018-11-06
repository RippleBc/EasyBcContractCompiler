#include "../common.h"

#define MAX_OP_CODES_NUM 512

struct _op_code_ {
    int code;
    char name[NAME_LEN];
    int in;
    int out;
};
int op_code_index = 0;
struct _op_code_ *op_codes[MAX_OP_CODES_NUM];