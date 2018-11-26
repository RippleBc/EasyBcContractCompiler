#include "../common.h"

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

  /*  */
  value v_code;

  while(byte_sequence_index < byte_sequence_size)
  {
    /*  */
    load_with_byte_unit(TYPE_INTEGER, &byte_sequence[byte_sequence_index], &v_code);

    /*  */
  	code_detail = get_detail_by_op_code(v_code.i);
    if(code_detail == NULL)
    {
      printf("*************get_detail_by_op_code error*************\n");
      exit(1);
    }

  	if(!strcmp(code_detail->name, "PUSH4"))
  	{
  		push_vm_stack_from_byte_sequence(4);
  	}
  	else if(!strcmp(code_detail->name, "PUSH8"))
  	{
  		push_vm_stack_from_byte_sequence(8);
  	}
    else if(!strcmp(code_detail->name, "COND"))
    {
      int position = get_int_from_vm_stack();
      boolean cond = get_boolean_from_vm_stack();
      boolean expression = get_boolean_from_vm_stack();
      
      if(cond == expression)
      {
        /* jump */
        byte_sequence_index = position;

        if(JUMP_DEBUG)
        {
          printf("COND JUMP to %x\n", byte_sequence_index);
        }
      }
      else
      {
        /* execute the next op code */
        byte_sequence_index += IR->intmetric.align;
      }

      continue;
    }
    else if(!strcmp(code_detail->name, "JUMP"))
    {
      int position = get_int_from_vm_stack();
      byte_sequence_index = position;

      if(JUMP_DEBUG)
      {
        printf("JUMP to %x\n", byte_sequence_index);
      }

      continue;
    }
    else
    {
      
      mathmatical_command(code_detail);
      
      logic_command(code_detail);
      
      sys_func(code_detail);
      
      /* global stack */
      if(!strcmp(code_detail->name, "ASSIGN_GLOBAL4"))
      {
        assign_global(4);
      }
      else if(!strcmp(code_detail->name, "LOAD_GLOBAL4"))
      {
        load_global(4);
      }
      else if(!strcmp(code_detail->name, "ASSIGN_GLOBAL8"))
      {
        assign_global(8);
      }
      else if(!strcmp(code_detail->name, "LOAD_GLOBAL8"))
      {
        load_global(8);
      }

      /* function stack */
      if(!strcmp(code_detail->name, "ASSIGN_CALL4"))
      {
        assign_call(4);
      }
      else if(!strcmp(code_detail->name, "LOAD_CALL4"))
      {
        load_call(4);
      }
      else if(!strcmp(code_detail->name, "ASSIGN_CALL8"))
      {
        assign_call(8);
      }
      else if(!strcmp(code_detail->name, "LOAD_CALL8"))
      {
        load_call(8);
      }
      else if(!strcmp(code_detail->name, "TOP_CALL"))
      {
        top_call();
      }
      else if(!strcmp(code_detail->name, "PUSH_CALL"))
      {
        push_call();
      }
      else if(!strcmp(code_detail->name, "POP_CALL"))
      {
        pop_call();
      }

      /*  */
      if(!strcmp(code_detail->name, "EXIT"))
      {
        printf("routine end\n");
        break;
      }

      byte_sequence_index += IR->intmetric.align;
    }
  }
}