#include "../common.h"

#define STACK_DEEP 256

extern int byte_sequence_index;
extern unsigned char byte_sequence[];

/*  */
int vm_stack_deep = STACK_DEEP;
unsigned char vm_stack[STACK_DEEP];
int push_vm_stack_from_byte_sequence(int size)
{
  int i = 0;
  while(i < size)
  {
    vm_stack[--vm_stack_deep] = byte_sequence[byte_sequence_index++];
    i++;
  }
}

unsigned char *pop_vm_stack(int size)
{
  int origin_index = vm_stack_deep;

  vm_stack_deep += size;

  return vm_stack[origin_index];
}