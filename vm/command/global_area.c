#include "../common.h"

#define GLOBAL_AREA_MAX_SIZE 1024 * 10

/*  */
static unsigned char global_area[GLOBAL_AREA_MAX_SIZE];

void assign_global(int align)
{
  /*  */
  int address = get_int_from_vm_stack();

  /*  */
  if(address + align -1 >= GLOBAL_AREA_MAX_SIZE)
  {
    printf("*************global area is full*************\n");
    exit(1);
  }

	for(int i = 0; i < align; i++)
	{
		global_area[address++] = vm_stack[vm_stack_deep + i];
	}

  pop_vm_stack(align);

  if(GLOBAL_AREA_DEBUG)
  {
    printf("assign_global, address %d, byte sequence ", address - align);
    for(int i = address - align; i < address; i++)
    {
      printf("%x ", global_area[i]);
      if((i + 1) % 4 == 0)
      {
        printf("| ");
      }
    }
    printf("\n\n\n");
  }
  
  if(VM_STACK_DEBUG)
  {
    printf("assign_global, vm stack byte sequence\n");
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


  if(GLOBAL_AREA_DEBUG)
  {
    printf("load_global offset %d \n", address - align);
    for(int i = address - align; i < address; i++)
    {
      printf("%x ", global_area[i]);
      if((i + 1) % 4 == 0)
      {
        printf("| ");
      }
    }
    printf("\n\n\n");
  }

  if(VM_STACK_DEBUG)
  {
    printf("load_global, vm stack byte sequence\n");
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