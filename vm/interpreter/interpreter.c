#include "../common.h"
#include "./op_codes.h"

#define MAX_CODE_NUM 10 * 1024

int byte_sequence_size = 0;
unsigned char byte_sequence[MAX_CODE_NUM];

int byte_sequence_index = 0;

void interpret()
{
  /*  */
	struct _op_code_ *code_detail;

  /*  */
  unsigned char* cp;

  while(byte_sequence_index < byte_sequence_size)
  {
  	code_detail = get_detail_by_op_code(byte_sequence[byte_sequence_index]);
    if(code_detail == NULL)
    {
      return;
    }
    else
    {
      printf("get_detail_by_op_code %s\n", code_detail->name);
    }
    // cp = pop_byte_code_stack(code_detail->in);

  	if(!strcmp(code_detail->name, "PUSH4"))
  	{
  		push_vm_stack_from_byte_sequence(4);
  	}
  	else if(!strcmp(code_detail->name, "PUSH8"))
  	{
  		push_vm_stack_from_byte_sequence(8);
  	}
   //  else if(!strcmp(code_detail->name, 'JUMP'))
   //  {
      
   //  }
   //  else if(!strcmp(code_detail->name, 'COND'))
   //  {
      
   //  }
    else
    {
      byte_sequence_index++;
    }
  }
}