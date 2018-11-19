#include "../common.h"

/*  */
static int function_call_stack_deep = FUNCTION_CALL_STACK_DEEP;
static unsigned char function_call_stack[FUNCTION_CALL_STACK_DEEP];

int push_call(int size)
{
  if(function_call_stack_deep < size)
  {
    return -1;
  }
  function_call_stack_deep -= size;
  return 1;
}

void pop_call(int size)
{
  function_call_stack_deep += size;
}

void assign_call(int size)
{
  /*  */
  int address = get_int_from_vm_stack();

	for(int i = 0; i < size; i++)
	{
		function_call_stack[function_call_stack_deep + address++] = vm_stack[vm_stack_deep + i];
	}
  
  pop_vm_stack(size);
}

void load_call(int size)
{
  /*  */
  int address = get_int_from_vm_stack();

  /*  */
  push_vm_stack(size);

  /*  */
  for(int i = 0; i < size; i++)
  {
    vm_stack[vm_stack_deep + i] = function_call_stack[function_call_stack_deep + address++];
  }

  if(VM_STACK_DEBUG)
  {
    printf("load_call\n");
    for(int i = vm_stack_deep; i < VM_STACK_DEEP; i++)
    {
      printf("%x ", vm_stack[i]);
      if((i + 1) % 4 == 0)
      {
        printf("| ");
      }
    }
    printf("\n\n\n");
  }
}

int top_call()
{
	return function_call_stack_deep;
}

int get_int_from_function_call_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_INTEGER, &function_call_stack[function_call_stack_deep + index], &v);
  return v.i;
}

unsigned int get_uint_from_function_call_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_UINTEGER, &function_call_stack[function_call_stack_deep + index], &v);
  return v.ui;
}

float get_real_from_function_call_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_REAL, &function_call_stack[function_call_stack_deep + index], &v);
  return v.f;
}

boolean get_boolean_from_function_call_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_BOOLEAN, &function_call_stack[function_call_stack_deep + index], &v);
  return v.b;
}

char get_char_from_function_call_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_CHAR, &function_call_stack[function_call_stack_deep + index], &v);
  return v.c;
}

unsigned char get_uchar_from_function_call_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_UCHAR, &function_call_stack[function_call_stack_deep + index], &v);
  return v.uc;
}