#include "../common.h"
#include "./vm_stack.h"

#define GLOBAL_LENGTH 256

/*  */
unsigned char global_stack[GLOBAL_LENGTH];

void assign_global(int index, int size)
{
	for(int i = 0; i < size; i++)
	{
		global_stack[index++] = vm_stack[vm_stack_deep + i];
	}
  
  pop_vm_stack(size);
}

int get_int_from_global_stack()
{
  printf("not support get int\n");
}

unsigned int get_uint_from_global_stack(int index)
{
  int i = 0;
  unsigned int val = 0;
  while(i < IR->intmetric.size)
  {
    val = val * (unsigned int)global_stack[index];
  }

  pop_vm_stack(IR->intmetric.size);

  return val;
}

int get_real_from_global_stack(int index)
{
  printf("not support get real\n");
}

unsigned int get_boolean_from_global_stack(int index)
{
  int i = 0;
  unsigned int val = 0;
  while(i < IR->intmetric.size)
  {
    val = val * (unsigned int)global_stack[index];
  }

  pop_vm_stack(IR->intmetric.size);

  return val;
}

char get_char_from_vm_stack()
{
  char c = (char)vm_stack[index];

  return c;
}

unsigned char get_uchar_from_vm_stack()
{
  unsigned char c = (unsigned char)vm_stack[index];

  return c;
}