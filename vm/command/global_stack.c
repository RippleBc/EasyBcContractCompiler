#include "../common.h"

#define GLOBAL_LENGTH 256

/*  */
static unsigned char global_stack[GLOBAL_LENGTH];

void assign_global(int align)
{
  /*  */
  int address = get_int_from_vm_stack();

	for(int i = 0; i < align; i++)
	{
		global_stack[address++] = vm_stack[vm_stack_deep + i];
	}
  
  pop_vm_stack(align);
}

void load_global(int align)
{
  /*  */
  int address = get_int_from_vm_stack();

  /*  */
  push_vm_stack(align);

  /*  */
  for(int i = 0; i < align; i++)
  {
    vm_stack[vm_stack_deep + i] = global_stack[address++];
  }

  if(VM_STACK_DEBUG)
  {
    printf("load_global\n");
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

int get_int_from_global_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_INTEGER, &global_stack[index], &v);
  return v.i;
}

unsigned int get_uint_from_global_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_UINTEGER, &global_stack[index], &v);
  return v.ui;
}

float get_real_from_global_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_REAL, &global_stack[index], &v);
  return v.f;
}

boolean get_boolean_from_global_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_BOOLEAN, &global_stack[index], &v);
  return v.b;
}

char get_char_from_global_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_CHAR, &global_stack[index], &v);
  return v.c;
}

unsigned char get_uchar_from_global_stack(int index)
{
  value v;
  load_with_byte_unit(TYPE_UCHAR, &global_stack[index], &v);
  return v.uc;
}