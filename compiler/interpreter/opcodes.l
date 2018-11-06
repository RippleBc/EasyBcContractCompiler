%{
#include "../common.h"

#define YY_DECL int op_code_scan(void);
#define OP_CODE_MAX_NUM 512;

struct _op_code_ {
  int code;
  char name[NAME_LEN];
  int in;
  int out;
};

typedef struct _op_code_ *OpCode;

int op_code_index = 0;
OpCode opcodes[OP_CODE_MAX_NUM];
%}

%s out

%%
"0x"[a-z0-9]+ {
	NEW0(opcodes[op_code_index], PERM);

	opcodes[op_code_index]->code = stoi(yytext, 16)
}

'[A-Z]+' {
	strncpy(opcodes[op_code_index]->name, yytext, NAME_LEN);
}

[0-9]+ {
	opcodes[op_code_index]->in = stoi(yytext, 10);

	BEGIN(in);
}

<in>[0-9]+ {
	opcodes[op_code_index]->out = stoi(yytext, 10);

	BEGIN(INITIAL);
}
%%