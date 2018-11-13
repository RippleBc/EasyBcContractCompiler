#include "../common.h"

ops_entry ops_table[] = {
	{"CNST", CNST},
	{"ARG", ARG},
	{"ASGN", ASGN},
	{"INDIR", INDIR},
	{"SYS", SYS},
	{"CVC", CVC},
	{"CVF", CVF},
	{"CVI", CVI},
	{"CVUC", CVUC},
	{"CVUI", CVUI},
	{"CVB", CVB},
	{"NEG", NEG},
	{"CALL", CALL},
	{"LOAD", LOAD},
	{"ADDRG", ADDRG},
	{"ADD", ADD},
	{"SUB", SUB},
	{"LSH", LSH},
	{"MOD", MOD},
	{"RSH", RSH},
	{"BAND", BAND},
	{"BCOM", BCOM},
	{"BOR", BOR},
	{"BXOR", BXOR},
	{"DIV", DIV},
	{"MUL", MUL},
	{"EQ", EQ},
	{"GE", GE},
	{"GT", GT},
	{"LE", LE},
	{"LT", LT},
	{"NE", NE},
	{"JUMP", JUMP},
	{"LABEL", LABEL},
	{"AND", AND},
	{"NOT", NOT},
	{"OR", OR},
	{"COND", COND},
	{"RIGHT", RIGHT},
	{"FIELD", FIELD},
	{"INCR", INCR},
	{"DECR", DECR},
	{"ARRAY", ARRAY},
	{"HEADER", HEADER},
	{"TAIL	", TAIL	},
	{"BLOCKBEG", BLOCKBEG},
	{"BLOCKEND", BLOCKEND},
	{"LASTOP", LASTOP}
};

char *get_op_name(int op)
{
  int left = 0, right;
  int middle;

  right = sizeof(ops_table) / sizeof(ops_entry);
  while (left <= right)
  {
      middle = (right + left) / 2;
      if (ops_table[middle].op < op)
      {
          left = middle + 1;
      }
      else if (ops_table[middle].op == op)
      {
          return ops_table[middle].name;
      }
      else
      {
          right = middle - 1;
      }
  }
	return "Unknown op";
}

int get_op(char *name)
{
    int i;

    for (i = 0; i < sizeof(ops_table) / sizeof(ops_entry); i++)
    {
        if (strcasecmp(name, ops_table[i].name) == 0)
            return ops_table[i].op;
    }

    return LASTOP;
}

