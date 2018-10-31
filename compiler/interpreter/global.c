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

    Symbol sp = p->type_link->first;
    
    int i;
    for(i = 1; i < strlen(n->val.s) - 1; i++)
    {
      if(sp == NULL)
      {
        printf("assign_global array out of index %s\n", p->name);
        return;
      }

      global_queue[baseOffset + sp->offset].c = n->val.s[i]; 

      sp = sp->next;
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