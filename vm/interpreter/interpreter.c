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
    // printf("get_detail_by_op_code index %x code %x\n", byte_sequence_index, byte_sequence[byte_sequence_index]);

  	code_detail = get_detail_by_op_code(byte_sequence[byte_sequence_index]);
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
      }
      else
      {
        /* execute the next op code */
        byte_sequence_index++;
      }
    }
    else if(!strcmp(code_detail->name, "JUMP"))
    {
      int position = get_int_from_vm_stack();
      byte_sequence_index = position;
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

      /* basic arithmatical */
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
      else if(!strcmp(code_detail->name, "MOD"))
      {
        value result;
        result.i = get_int_from_vm_stack() / get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("MOD %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "IINCR"))
      {
        value result;
        result.i = get_int_from_vm_stack() + 1;

        if(TYPE_BYTE_DEBUG)
        {
          printf("IINCR %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_INTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "IDECR"))
      {
        value result;
        result.i = get_int_from_vm_stack() - 1;

        if(TYPE_BYTE_DEBUG)
        {
          printf("IDECR %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_INTEGER, &result);
      }
      
      /* judge */
      if(!strcmp(code_detail->name, "IEQ"))
      {
        value result;
        result.b = get_int_from_vm_stack() == get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IEQ %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      else if(!strcmp(code_detail->name, "INE"))
      {
        value result;
        result.b = get_int_from_vm_stack() != get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("INE %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      else if(!strcmp(code_detail->name, "IGE"))
      {
        value result;
        result.b = get_int_from_vm_stack() >= get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IGE %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      else if(!strcmp(code_detail->name, "IGT"))
      {
        value result;
        result.b = get_int_from_vm_stack() > get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IGT %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      else if(!strcmp(code_detail->name, "ILE"))
      {
        value result;
        result.b = get_int_from_vm_stack() <= get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("ILE %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      else if(!strcmp(code_detail->name, "ILT"))
      {
        value result;
        result.b = get_int_from_vm_stack() < get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("ILT %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
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

      if(!strcmp(code_detail->name, "READLN"))
      {
        
      }
      else if(!strcmp(code_detail->name, "WRITELN"))
      {
        int result = get_int_from_vm_stack();
        printf("result is %d\n", result);
      }

      byte_sequence_index++;
    }
  }
}