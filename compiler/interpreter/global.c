#include "../common.h"

#define STACK_DEEP 256

/*  */
int global_deep = STACK_DEEP;
value global_queue[STACK_DEEP];

void assign_global(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }

  global_queue[global_deep - baseOffset + p->offset - get_symbol_align_size(p)] = n->val; 
}

void load_global(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }

  n->val = global_queue[global_deep - baseOffset + p->offset - get_symbol_align_size(p)];
}