#include "../common.h"

/*  */
int vm_stack_deep = VM_STACK_DEEP;
unsigned char vm_stack[VM_STACK_DEEP];

void push_vm_stack_from_byte_sequence(int align)
{
	/*  */
	byte_sequence_index += 1;

  if(vm_stack_deep - align < 0)
  {
    printf("*************vm stack is full*************\n");
    exit(1);
  }

  /*  */
  vm_stack_deep -= align;

	/*  */
  int i = 0;
  while(i < align)
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
      if(vm_stack_deep - IR->intmetric.align < 0)
      {
        printf("*************vm stack is full*************\n");
        exit(1);
      }
      /*  */
      vm_stack_deep -= IR->intmetric.align;
    }
    break;
    case TYPE_REAL:
    {
      if(vm_stack_deep - IR->floatmetric.align < 0)
      {
        printf("*************vm stack is full*************\n");
        exit(1);
      }
      /*  */
      vm_stack_deep -= IR->floatmetric.align;
    }
    break;
    case TYPE_CHAR:
    case TYPE_UCHAR:
    {
      if(vm_stack_deep - IR->charmetric.align < 0)
      {
        printf("*************vm stack is full*************\n");
        exit(1);
      }
      /*  */
      vm_stack_deep -= IR->charmetric.align;
    }
    break;
    default:
    {
      printf("*************unsupported type %d\n*************", type);
      exit(1);
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

void push_vm_stack(int align)
{
  if(vm_stack_deep - align < 0)
  {
    printf("*************vm stack is full*************\n");
    exit(1);
  }
  vm_stack_deep -= align;
}

void pop_vm_stack(int align)
{
  if(vm_stack_deep + align > VM_STACK_DEEP)
  {
    printf("*************vm stack is empty*************\n");
    exit(1);
  }
  vm_stack_deep += align;
}

int get_int_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_INTEGER, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->intmetric.align);

  return v.i;
}

unsigned int get_uint_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_UINTEGER, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->intmetric.align);

  return v.ui;
}

float get_real_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_REAL, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->floatmetric.align);

  return v.f;
}

boolean get_boolean_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_BOOLEAN, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->intmetric.align);

  return v.b;
}

char get_char_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_CHAR, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->charmetric.align);

  return v.c;
}

unsigned char get_uchar_from_vm_stack()
{
  value v;
  load_with_byte_unit(TYPE_UCHAR, &vm_stack[vm_stack_deep], &v);

  pop_vm_stack(IR->charmetric.align);

  return v.uc;
}