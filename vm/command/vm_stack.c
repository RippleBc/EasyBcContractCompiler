#include "../common.h"

#define STACK_DEEP 256

extern int byte_sequence_index;
extern unsigned char byte_sequence[];

/*  */
int vm_stack_deep = STACK_DEEP;
unsigned char vm_stack[STACK_DEEP];
int push_vm_stack_from_byte_sequence(int size)
{
	/*  */
	byte_sequence_index += 1;

	/*  */
  int i = 0;
  while(i < size)
  {
    vm_stack[--vm_stack_deep] = byte_sequence[byte_sequence_index++];
    i++;
  }
}

void pop_vm_stack(int size)
{
  vm_stack_deep += size;
}

int get_int_from_vm_stack()
{
  printf("not support get int\n");
}

unsigned int get_uint_from_vm_stack()
{
  int i = 0;
  unsigned int val = 0;
  while(i < IR->intmetric.size)
  {
    val = val * (unsigned int)vm_stack[vm_stack_deep];
  }

  pop_vm_stack(IR->intmetric.size);

  return val;
}

int get_real_from_vm_stack()
{
  printf("not support get real\n");
}

unsigned int get_boolean_from_vm_stack()
{
  int i = 0;
  unsigned int val = 0;
  while(i < IR->intmetric.size)
  {
    val = val * (unsigned int)vm_stack[vm_stack_deep];
  }

  pop_vm_stack(IR->intmetric.size);

  return val;
}

char get_char_from_vm_stack()
{
  char c = (char)vm_stack[vm_stack_deep];

  pop_vm_stack(IR->charmetric.size);

  return c;
}

unsigned char get_uchar_from_vm_stack()
{
  unsigned char c = (unsigned char)vm_stack[vm_stack_deep];

  pop_vm_stack(IR->charmetric.size);

  return c;
}