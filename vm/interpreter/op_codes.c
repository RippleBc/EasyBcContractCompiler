#include "../common.h"

#define MAX_OP_CODES_NUM 512

/* 字符串转化为10进制数字 */
int stoi(char *s,int radix)
{
    char *p = s;
    int val = 0;

    if (radix == 8)
    {
        p++;
        while(*p)
        {
            val = val * radix + (*p - '0');
            p++;
        }
    }
    else if (radix == 16 )
    {
        p++;
        p++;

        while(*p)
        {
            if (isdigit(*p))
            {
                val = val * radix + (*p - '0');
            }
            else
            {
                val = val * radix + (tolower(*p) - 'a');
            }
            p++;
        }
    }
    else
    {
        while(*p)
        {
            val = val * radix + (*p -'0');
            p++;
        }
    }
    return val;
}

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

	printf("get_op_code_by_name code not exist %s\n", name);
	return -1;
}