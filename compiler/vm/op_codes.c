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

void init_op_code()
{	
	/*  */
	char buffer[NAME_LEN];

	/*  */
	int tmp_index = 0;
	char tmp[NAME_LEN];

	FILE *pFile;
	pFile = fopen("../opcodes.txt", "rt");
	if(pFile == NULL)
	{
		printf("file opcodes.txt not exit\n");
		return;
	}

	char c;
	int field_mark;
	while((fgets(buffer, NAME_LEN, pFile)) != NULL)
	{
		field_mark = 0;
		tmp_index = 0;
		/*  */
		for(int i = 0; i < strlen(buffer); i++)
		{
			c = buffer[i];

			/*  */
			if(c == '\t' || c == ' ' || c == '\n' || c == '\'')
			{
				continue;
			}

			/*  */
			if(c == ',')
			{
				/*  */
				tmp[tmp_index] = '\0';

				/*  */
				if(field_mark == 0)
				{
					NEW0(op_codes[op_code_index], PERM);
					op_codes[op_code_index]->code = stoi(tmp, 16);
				}
				else
				{
					if(field_mark == 1)
					{
						strncpy(op_codes[op_code_index]->name, tmp, NAME_LEN);
					}	
					else if(field_mark == 2)
					{
						op_codes[op_code_index]->in = stoi(tmp, 10);
					}
					else
					{
						op_codes[op_code_index]->out = stoi(tmp, 10);
					}
				}

				/*  */
				tmp_index = 0;
				field_mark++;
			}
			else
			{
				tmp[tmp_index++] = c;
			}
		}

		/*  */
		if(op_codes[op_code_index] != NULL)
		{
			op_code_index++;
		}
	}
}

int get_op_code_by_name(char *name)
{
	for(int i = 0; i < op_code_index; i++)
	{
		if(!strcmp(op_codes[i]->name, name))
		{
			return op_codes[i]->code;
		}
	}

	return -1;
}

int get_type_related_op_code_by_name(Type t, char *name)
{
	char op_name[MAX_OP_CODES_NUM];
	if(t->type_id == TYPE_INTEGER)
	{
		snprintf(op_name, MAX_OP_CODES_NUM, "%c%s", 'I', name);
		return get_op_code_by_name(op_name);
	}
	else if(t->type_id == TYPE_REAL)
	{
		snprintf(op_name, MAX_OP_CODES_NUM, "%c%s", 'R', name);
		return get_op_code_by_name(op_name);
	}
	else if(t->type_id == TYPE_BOOLEAN)
	{
		snprintf(op_name, MAX_OP_CODES_NUM, "%c%s", 'B', name);
		return get_op_code_by_name(op_name);
	}
	else
	{
		return -1;
	}
}