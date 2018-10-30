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
value return_val_stack[STACK_DEEP];

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

void assign_return_val(Node n, Symbol p)
{
  return_val_stack[return_val_deep + p->offset - get_symbol_align_size(p)] = n->val;
}


void load_return_val(Node n, Symbol p)
{
  n->val = return_val_stack[return_val_deep + p->offset - get_symbol_align_size(p)];
}

/*  */
int local_deep = STACK_DEEP;
value local_stack[STACK_DEEP];

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

void assign_local(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }

  local_stack[local_deep - baseOffset + p->offset - get_symbol_align_size(p)] = n->val; 
  // printf("assign_local %s offset:%d val:%d\n", p->name, local_deep + p->offset - get_symbol_align_size(p), local_stack[local_deep + p->offset - get_symbol_align_size(p)]);
}

void load_local(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }

  // printf("load_local %s offset:%d val:%d\n", p->name, local_deep + p->offset - get_symbol_align_size(p), local_stack[local_deep + p->offset - get_symbol_align_size(p)]);
  n->val = local_stack[local_deep - baseOffset + p->offset - get_symbol_align_size(p)];
}


/*  */
int args_deep = STACK_DEEP;
value args_stack[STACK_DEEP];

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

void assign_arg(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }

  args_stack[args_deep + baseOffset + p->offset - get_symbol_align_size(p)] = n->val;
  // printf("assign_arg %s offset:%d val:%d\n", p->name, args_deep + p->offset - get_symbol_align_size(p), args_stack[args_deep + p->offset - get_symbol_align_size(p)]);
}


void load_arg(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }

  // printf("load_arg %s offset:%d val:%d\n", p->name, args_deep + p->offset - get_symbol_align_size(p), args_stack[args_deep + p->offset - get_symbol_align_size(p)]);
  n->val = args_stack[args_deep + baseOffset+ p->offset - get_symbol_align_size(p)];
}