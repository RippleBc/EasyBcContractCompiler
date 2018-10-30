#include "../common.h"

#define GLOBAL_LENGTH 256

/*  */
int global_length = GLOBAL_LENGTH;
value global_queue[GLOBAL_LENGTH];

void assign_global(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  int baseSize = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
    baseSize = get_symbol_align_size(q);
  }

  printf("assign_global ****************** %d\n", global_length -1 + baseOffset - baseSize + p->offset - get_symbol_align_size(p));
  global_queue[global_length - 1 + baseOffset - baseSize + p->offset - get_symbol_align_size(p)] = n->val; 
  printf("assign_global ################## %d\n", global_queue[global_length -1 + baseOffset - baseSize + p->offset - get_symbol_align_size(p)]);
}

void load_global(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  int baseSize = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
    baseSize = get_symbol_align_size(q);
  }
  
  printf("load_global ****************** %d\n", global_length - 1 + baseOffset - baseSize + p->offset - get_symbol_align_size(p));
  printf("load_global ################## %d\n", global_queue[global_length - 1 + baseOffset - baseSize + p->offset - get_symbol_align_size(p)]);
  n->val = global_queue[global_length - 1 + baseOffset - baseSize + p->offset - get_symbol_align_size(p)];
}