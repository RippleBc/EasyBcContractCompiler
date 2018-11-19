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

  while(byte_sequence_index < byte_sequence_size)
  {
  	code_detail = get_detail_by_op_code(byte_sequence[byte_sequence_index]);
    if(code_detail == NULL)
    {
      return;
    }
    else
    {
      // printf("get_detail_by_op_code %s\n", code_detail->name);
    }

  	if(!strcmp(code_detail->name, "PUSH4"))
  	{
  		push_vm_stack_from_byte_sequence(4);
  	}
  	else if(!strcmp(code_detail->name, "PUSH8"))
  	{
  		push_vm_stack_from_byte_sequence(8);
  	}
    else
    {
      /*  */
      if(!strcmp(code_detail->name, "ILSH"))
      {
        value result;
        result.i = get_int_from_vm_stack() <<  get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IRSH %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_INTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "IRSH"))
      {
        value result;
        result.i = get_int_from_vm_stack() >>  get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IRSH %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_INTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "UILSH"))
      {
        value result;
        result.ui = get_uint_from_vm_stack() <<  get_uint_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("UILSH %d result %d\n", result.ui);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "UIRSH"))
      {
        value result;
        result.ui = get_uint_from_vm_stack() >>  get_uint_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("UIRSH %d result %d\n", result.ui);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }

      /*  */
      if(!strcmp(code_detail->name, "IADD"))
      {
        value result;
        result.i = get_int_from_vm_stack() + get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IADD %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "ISUB"))
      {
        value result;
        result.i = get_int_from_vm_stack() - get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("ISUB %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      if(!strcmp(code_detail->name, "IMUL"))
      {
        value result;
        result.i = get_int_from_vm_stack() * get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IMUL %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "IDIV"))
      {
        value result;
        result.i = get_int_from_vm_stack() / get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IDIV %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }

      /*  */
      if(!strcmp(code_detail->name, "MOD"))
      {
        value result;
        result.i = get_int_from_vm_stack() / get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("MOD %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }

      
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
        load_call( 4);
      }
      else if(!strcmp(code_detail->name, "ASSIGN_CALL8"))
      {
        assign_call(8);
      }
      else if(!strcmp(code_detail->name, "LOAD_CALL8"))
      {
        load_call(8);
      }

      if(!strcmp(code_detail->name, "READLN"))
      {
        
      }
      else if(!strcmp(code_detail->name, "WRITELN"))
      {
        int result = get_int_from_vm_stack();
        printf("%d\n", result);
      }

      byte_sequence_index++;
    }
  }
}