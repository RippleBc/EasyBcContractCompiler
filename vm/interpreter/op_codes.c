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

int stoi(char *s,int radix)
{
    char *p = s;
    int val = 0;
    int c_val = 0;

    if (radix == 8)
    {
        p++;
        while(*p)
        {
            c_val = *p -'0';
            if(c_val > 7)
            {
                printf("octal transform fail %d", c_val);
                return -1;
            }
            val = val * radix + c_val;
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
                c_val = tolower(*p) -'a';
                if(c_val > 5)
                {
                    printf("hex transform fail %d", c_val);
                    return -1;
                }
                val = val * radix + c_val + 10;
            }
            p++;
        }
    }
    else
    {
        while(*p)
        {
            c_val = *p -'0';
            if(c_val > 9)
            {
                printf("decimal transform fail %d", c_val);
                return -1;
            }
            val = val * radix + c_val;
            p++;
        }
    }
    return val;
}

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
					printf("tmp op code %s %d\n", tmp, op_codes[op_code_index]->code);
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

struct _op_code_ *get_detail_by_op_code(int op_code)
{
	for(int i = 0; i < op_code_index; i++)
	{
		if(op_codes[i]->code == op_code)
		{
			return op_codes[i];
		}
	}

	printf("get_op_code_by_name code not exist %x\n", op_code);
	return NULL;
}