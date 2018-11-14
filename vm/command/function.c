#include "../common.h"

#define STACK_DEEP 256

/*  */
int function_call_stack_deep = STACK_DEEP;
unsigned char function_call_stack[STACK_DEEP];
int PUSH_CALL(int size)
{
  if(function_call_stack_deep < size)
  {
    return -1;
  }
  function_call_stack_deep -= size;
  return 1;
}
void POP_CALL(int size)
{
  function_call_stack_deep += size;
}
void ASSIGN_CALL(int index, unsigned char *val, int size)
{
	for(int i = 0; i < size; i++)
	{
		function_call_stack[i] = *val;
	}
}
unsigned char *LOAD_CALL(int index)
{
  return &function_call_stack[index];
}

int TOP_CALL()
{
	return function_call_stack_deep;
}