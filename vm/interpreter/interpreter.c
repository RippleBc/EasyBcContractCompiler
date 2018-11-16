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
        
      }
      else if(!strcmp(code_detail->name, "IRSH"))
      {
        
      }
      else if(!strcmp(code_detail->name, "UILSH"))
      {
        unsigned int result = get_uint_from_vm_stack() <<  get_uint_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, &result);
      }
      else if(!strcmp(code_detail->name, "UIRSH"))
      {
        unsigned int result = get_uint_from_vm_stack() >>  get_uint_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, &result);
      }

      /*  */
      if(!strcmp(code_detail->name, "IADD"))
      {
        int result = get_int_from_vm_stack() + get_int_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, &result);
      }
      else if(!strcmp(code_detail->name, "ISUB"))
      {
        int result = get_int_from_vm_stack() - get_int_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, &result);
      }
      if(!strcmp(code_detail->name, "IMUL"))
      {
        int result = get_int_from_vm_stack() * get_int_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, &result);
      }
      else if(!strcmp(code_detail->name, "IDIV"))
      {
        int result = get_int_from_vm_stack() / get_int_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, &result);
      }

      /*  */
      if(!strcmp(code_detail->name, "IADD"))
      {
        
      }
      else if(!strcmp(code_detail->name, "ISUB"))
      {
        
      }
      if(!strcmp(code_detail->name, "IMUL"))
      {
        
      }
      else if(!strcmp(code_detail->name, "IDIV"))
      {
        
      }

      /*  */
      if(!strcmp(code_detail->name, "IADD"))
      {
        
      }
      else if(!strcmp(code_detail->name, "ISUB"))
      {
        
      }
      if(!strcmp(code_detail->name, "IMUL"))
      {
        
      }
      else if(!strcmp(code_detail->name, "IDIV"))
      {
        
      }

      /*  */
      if(!strcmp(code_detail->name, "IADD"))
      {
        
      }
      else if(!strcmp(code_detail->name, "ISUB"))
      {
        
      }
      if(!strcmp(code_detail->name, "IMUL"))
      {
        
      }
      else if(!strcmp(code_detail->name, "IDIV"))
      {
        
      }

      /*  */
      if(!strcmp(code_detail->name, "MOD"))
      {
        int result = get_int_from_vm_stack() / get_int_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, &result);
      }

      
      if(!strcmp(code_detail->name, "GLOBAL_ASSIGN4"))
      {
        int address = get_uint_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, 4);
      }
      else if(!strcmp(code_detail->name, "GLOBAL_LOAD4"))
      {
        int result = get_int_from_vm_stack() / get_int_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, &result);
      }
      else if(!strcmp(code_detail->name, "GLOBAL_ASSIGN8"))
      {
        int result = get_int_from_vm_stack() / get_int_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, &result);
      }
      else if(!strcmp(code_detail->name, "GLOBAL_LOAD8"))
      {
        int result = get_int_from_vm_stack() / get_int_from_vm_stack();
        push_vm_stack_from_compute(IR->intmetric, &result);
      }


      if(!strcmp(code_detail->name, "READLN"))
      {

      }
      else if(!strcmp(code_detail->name, "WRITELN"))
      {
        
      }

      byte_sequence_index++;
    }
  }
}