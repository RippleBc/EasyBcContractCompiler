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
  if(p->type->type_id == TYPE_ARRAY)
  {
    baseOffset = p->offset;

    int eleOffset = get_symbol_align_size(p->type_link->last);

    int i;
    for(i = 1; i < strlen(n->val.s) - 1; i++)
    {
      if(i > p->type_link->num_ele)
      {
        printf("assign_local array out of index %s\n", p->name);
        return;
      }
      local_stack[local_deep + baseOffset + (i - 1) * eleOffset].c = n->val.s[i]; 
    }
  }
  else
  {
    if(q != NULL)
    {
      baseOffset = q->offset;
    }

    local_stack[local_deep + baseOffset + p->offset] = n->val; 
    // printf("assign_local %s offset:%d val:%d\n", p->name, local_deep + baseOffset + p->offset, local_stack[local_deep + baseOffset + p->offset].i);
  }
  
}

void load_local(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }

  // printf("load_local %s offset:%d val:%d\n", p->name, local_deep + baseOffset + p->offset, local_stack[local_deep + baseOffset + p->offset].i);
  n->val = local_stack[local_deep + baseOffset + p->offset];
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

  if(p->type->type_id == TYPE_ARRAY)
  {
    printf("assign_arg array assign %s string %s\n", p->name, n->val.s);
    baseOffset = p->offset;

    Symbol sp = p->type->first;
    
    int i;
    for(i = 0; i < strlen(n->val.s); i++)
    {
      if(sp == NULL)
      {
        printf("assign_arg array out of index %s\n", p->name);
        return;
      }
      local_stack[local_deep + baseOffset + sp->offset].c = n->val.s[i]; 
    }
  }
  else
  {
    if(q != NULL)
    {
      baseOffset = q->offset;
    }

    args_stack[args_deep + baseOffset + p->offset] = n->val;
    // printf("assign_arg %s offset:%d val:%d\n", p->name, args_deep + baseOffset + p->offset, args_stack[args_deep + baseOffset + p->offset].i);
  }
}


void load_arg(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }

  // printf("load_arg %s offset:%d val:%d\n", p->name, args_deep + baseOffset + p->offset, args_stack[args_deep + baseOffset + p->offset].i);
  n->val = args_stack[args_deep + baseOffset + p->offset];
}