#include "../common.h"

#define GLOBAL_LENGTH 256

/*  */
int global_length = GLOBAL_LENGTH;
value global_queue[GLOBAL_LENGTH];

void assign_global(Node n, Symbol p, Symbol q)
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
        parse_error("assign_global array out of index", p->name);
        return;
      }
      global_queue[baseOffset + (i - 1) * eleOffset].c = n->val.s[i]; 
    }
  }
  else
  {
    if(q != NULL)
    {
      baseOffset = q->offset;
      // printf("assign_global baseOffset %d\n", baseOffset);
    }

    global_queue[baseOffset + p->offset] = n->val; 
    // printf("assign_global ################## %d %s %d\n", baseOffset + p->offset, p->name, global_queue[baseOffset + p->offset].i);
  }
  
}

void load_global(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
    // printf("load_global baseOffset %d\n", baseOffset);
  }
  
  // printf("load_global ################## %d %s %d\n", baseOffset + p->offset, p->name, global_queue[baseOffset + p->offset].i);
  n->val = global_queue[baseOffset + p->offset];
}