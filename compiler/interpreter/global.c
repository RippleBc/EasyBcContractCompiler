#include "../common.h"

#define GLOBAL_AREA_SIZE 256

/*  */
value global_area[GLOBAL_AREA_SIZE];

void assign_global(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(p->type->type_id == TYPE_ARRAY)
  {
    value tmp;

    baseOffset = p->offset;

    int eleOffset = get_symbol_align_size(p->type->last);

    if(baseOffset + get_symbol_align_size(p) >=  GLOBAL_AREA_SIZE)
    {
      printf("global area is overflow\n");
      exit(1);
    }

    int i;
    for(i = 0; i < strlen(n->val.s); i++)
    {
      if(i > p->type->num_ele - 1)
      {
        printf("assign_global array out of index", p->name);
        exit(1);
      }

      tmp.c = n->val.s[i];
      assign_with_byte_unit(TYPE_CHAR, &global_area[baseOffset + i * eleOffset], &tmp);
    }
  }
  else
  {
    if(q != NULL)
    {
      baseOffset = q->offset;

      if(baseOffset + get_symbol_align_size(q) >= GLOBAL_AREA_SIZE)
      {
        printf("global area is overflow\n");
        exit(1);
      }
    }
    else
    {
      if(baseOffset + get_symbol_align_size(p) >= GLOBAL_AREA_SIZE)
      {
        printf("global area is overflow\n");
        exit(1);
      }
    }

    assign_with_byte_unit(p->type->type_id, &global_area[baseOffset + p->offset], &(n->val)); 
  }
  
}

void load_global(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;

    if(baseOffset + get_symbol_align_size(q) >= GLOBAL_AREA_SIZE)
    {
      printf("global area is overflow\n");
      exit(1);
    }
  }
  else
  {
    if(baseOffset + get_symbol_align_size(p) >= GLOBAL_AREA_SIZE)
    {
      printf("global area is overflow\n");
      exit(1);
    }
  }
  

  load_with_byte_unit(p->type->type_id, &global_area[baseOffset + p->offset], &(n->val));
}