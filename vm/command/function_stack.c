#include "../common.h"

#define STACK_DEEP 256

/*  */
int function_call_stack_deep = STACK_DEEP;
unsigned char function_call_stack[STACK_DEEP];
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

void assign_call(int index, unsigned char val)
{
	function_call_stack[index] = val;
}

int top_call()
{
	return function_call_stack_deep;
}