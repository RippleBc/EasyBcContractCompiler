#include "../common.h"

#define FUNCTION_CALL_STACK_DEEP 256

/*  */
static int function_call_stack_deep = FUNCTION_CALL_STACK_DEEP;
static unsigned char function_call_stack[FUNCTION_CALL_STACK_DEEP];

void push_call()
{
  int align = get_int_from_vm_stack();

  if(function_call_stack_deep < align)
  {
    printf("*************function call stack is full*************\n");
    exit(1);
  }
  function_call_stack_deep -= align;
}

void pop_call()
{
  int align = get_int_from_vm_stack();

  if(function_call_stack_deep + align > FUNCTION_CALL_STACK_DEEP)
  {
    printf("*************function call stack is empty*************\n");
    exit(1);
  }

  function_call_stack_deep += align;
}

void assign_call(int align)
{
  if(VM_FUNCTION_DEBUG)
  {
    printf("assign_call before\n");
    for(int i = function_call_stack_deep; i < FUNCTION_CALL_STACK_DEEP; i++)
    {
      printf("%x ", function_call_stack[i]);
      if((i + 1) % 4 == 0)
      {
        printf("| ");
      }
    }
    printf("\n\n\n");
  }

  /*  */
  int address = get_int_from_vm_stack();

	for(int i = 0; i < align; i++)
	{
		function_call_stack[function_call_stack_deep + address++] = vm_stack[vm_stack_deep + i];
	}
  
  if(VM_FUNCTION_DEBUG)
  {
    printf("assign_call after\n");
    for(int i = function_call_stack_deep; i < FUNCTION_CALL_STACK_DEEP; i++)
    {
      printf("%x ", function_call_stack[i]);
      if((i + 1) % 4 == 0)
      {
        printf("| ");
      }
    }
    printf("\n\n\n");
  }

  pop_vm_stack(align);
}

void load_call(int align)
{
  if(VM_STACK_DEBUG)
  {
    printf("load_call before, vm stack byte sequence\n");
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

  /*  */
  int address = get_int_from_vm_stack();

  /*  */
  push_vm_stack(align);

  /*  */
  for(int i = 0; i < align; i++)
  {
    vm_stack[vm_stack_deep + i] = function_call_stack[function_call_stack_deep + address++];
  }

  if(VM_STACK_DEBUG)
  {
    printf("load_call after, vm stack byte sequence\n");
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
  if(VM_STACK_DEBUG)
  {
    printf("top_call before, vm stack byte sequence\n");
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

  /*  */
  value address;
  address.i = function_call_stack_deep;

  /*  */
  push_vm_stack(IR->intmetric.align);

  /*  */
  assign_with_byte_unit(TYPE_INTEGER, &vm_stack[vm_stack_deep], &address);

  if(VM_STACK_DEBUG)
  {
    printf("top_call after, vm stack byte sequence\n");
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