#include "../common.h"

#define STACK_DEEP 256

int return_position_deep = STACK_DEEP;
List return_position_stack[STACK_DEEP];

int push_return_position_stack(List l)
{
  if(return_position_deep < 1)
  {
    return 0;
  }
  return_position_stack[--return_position_deep] = l;
  return 1;
}

List pop_return_position_stack()
{
  return return_position_stack[return_position_deep++];
}

List top_return_position_stack()
{
  return return_position_stack[return_position_deep];
}

/*  */
int return_val_deep = STACK_DEEP;
int return_val_stack[STACK_DEEP];

int push_return_val_stack(Symbol p)
{
  if(return_val_deep < get_symbol_align_size(p))
  {
    return 0;
  }
  return_val_deep -= get_symbol_align_size(p);
  return 1;
}

void pop_return_val_stack(Symbol p)
{
  return_val_deep += get_symbol_align_size(p);
}

void assign_return_val(Symbol p, int val)
{
  return_val_stack[return_val_deep + p->offset - get_symbol_align_size(p)] = val;
}


int load_return_val(Symbol p)
{
  return return_val_stack[return_val_deep + p->offset - get_symbol_align_size(p)];
}

/*  */
int local_deep = STACK_DEEP;
int local_stack[STACK_DEEP];

int push_local_stack(Symtab tab)
{
  if(local_deep < tab->local_size)
  {
    return 0;
  }
  local_deep -= tab->local_size;
  return 1;
}

void pop_local_stack(Symtab tab)
{
  local_deep += tab->local_size;
}

void assign_local(Symbol p, int val)
{
  /*  */
  local_stack[local_deep + p->offset - get_symbol_align_size(p)] = val;
  printf("assign_local %s offset:%d val:%d\n", p->name, local_deep + p->offset - get_symbol_align_size(p), local_stack[local_deep + p->offset - get_symbol_align_size(p)]);
}

int load_local(Symbol p)
{
  printf("load_local %s offset:%d val:%d\n", p->name, local_deep + p->offset - get_symbol_align_size(p), local_stack[local_deep + p->offset - get_symbol_align_size(p)]);
  return local_stack[local_deep + p->offset - get_symbol_align_size(p)];
}


/*  */
int args_deep = STACK_DEEP;
int args_stack[STACK_DEEP];

int push_args_stack(Symtab tab)
{
  if(args_deep < tab->args_size)
  {
    return 0;
  }
  args_deep -= tab->args_size;
  return 1;
}

void pop_args_stack(Symtab tab)
{
  args_deep += tab->args_size;
}

void assign_arg(Symbol p, int val)
{
  /*  */
  args_stack[args_deep + p->offset - get_symbol_align_size(p)] = val;
  printf("assign_arg %s offset:%d val:%d\n", p->name, args_deep + p->offset - get_symbol_align_size(p), args_stack[args_deep + p->offset - get_symbol_align_size(p)]);
}


int load_arg(Symbol p)
{
  printf("load_arg %s offset:%d val:%d\n", p->name, args_deep + p->offset - get_symbol_align_size(p), args_stack[args_deep + p->offset - get_symbol_align_size(p)]);
  return args_stack[args_deep + p->offset - get_symbol_align_size(p)];
}