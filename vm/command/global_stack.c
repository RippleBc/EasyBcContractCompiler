#include "../common.h"

#define GLOBAL_AREA_MAX_SIZE 256

/*  */
static unsigned char global_area[GLOBAL_AREA_MAX_SIZE];
static unsigned int global_area_size;

void assign_global(int align)
{
  global_area_size += align;

  /*  */
  int address = get_int_from_vm_stack();

	for(int i = 0; i < align; i++)
	{
		global_area[address++] = vm_stack[vm_stack_deep + i];
	}
  
  if(GLOBAL_STACK_DEBUG)
  {
    printf("assign_global\n");
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
    vm_stack[vm_stack_deep + i] = global_area[address++];
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