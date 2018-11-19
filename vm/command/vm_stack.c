#include "../common.h"

/*  */
int vm_stack_deep = VM_STACK_DEEP;
unsigned char vm_stack[VM_STACK_DEEP];

void push_vm_stack_from_byte_sequence(int size)
{
	/*  */
	byte_sequence_index += 1;

  /*  */
  vm_stack_deep -= size;
  
	/*  */
  int i = 0;
  while(i < size)
  {
    vm_stack[vm_stack_deep + i] = byte_sequence[byte_sequence_index++];
    i++;
  }

  if(VM_STACK_DEBUG)
  {
    printf("push_vm_stack_from_byte_sequence\n");
    for(i = vm_stack_deep; i < VM_STACK_DEEP; i++)
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

void push_vm_stack_from_compute(int type, Value v)
{
  switch(type)
  {
    case TYPE_INTEGER:
    case TYPE_UINTEGER:
    case TYPE_BOOLEAN:
    {
      /*  */
      vm_stack_deep -= IR->intmetric.align;
    }
    break;
    case TYPE_REAL:
    {
      /*  */
      vm_stack_deep -= IR->floatmetric.align;
    }
    break;
    case TYPE_CHAR:
    case TYPE_UCHAR:
    {
      /*  */
      vm_stack_deep -= IR->charmetric.align;
    }
    break;
    default:
    {
      printf("unsupported type %d\n", type);
    }
  }

  assign_with_byte_unit(type, &vm_stack[vm_stack_deep], v);

  if(VM_STACK_DEBUG)
  {
    printf("push_vm_stack_from_compute\n");
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

void push_vm_stack(int size)
{
  vm_stack_deep -= size;
}

void pop_vm_stack(int size)
{
  vm_stack_deep += size;
}

int get_int_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_INTEGER, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->intmetric.size);

  return v.i;
}

unsigned int get_uint_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_UINTEGER, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->intmetric.size);

  return v.ui;
}

float get_real_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_REAL, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->floatmetric.size);

  return v.f;
}

boolean get_boolean_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_BOOLEAN, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->intmetric.size);

  return v.b;
}

char get_char_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_CHAR, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->charmetric.size);

  return v.c;
}

unsigned char get_uchar_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_UCHAR, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->charmetric.size);

  return v.uc;
}