#include "../common.h"

#define STACK_DEEP 256

/*  */
int function_call_stack_deep = STACK_DEEP;
unsigned char function_call_stack[STACK_DEEP];
int push_function_call_stack(Symtab tab)
{
  if(function_call_stack_deep < tab->call_stack_size)
  {
    return 0;
  }
  function_call_stack_deep -= tab->call_stack_size;
  return 1;
}
void pop_function_call_stack(Symtab tab)
{
  function_call_stack_deep += tab->call_stack_size;
}
void assign_function_call_stack_val(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  value tmp;

  if(p->type->type_id == TYPE_ARRAY)
  {
    baseOffset = p->offset;

    int eleOffset = get_symbol_align_size(p->type_link->last);

    int i;
    for(i = 0; i < strlen(n->val.s); i++)
    {
      if(i > p->type_link->num_ele - 1)
      {
        parse_error("assign_local array out of index", p->name);
        return;
      }

      tmp.c = n->val.s[i];
      assign_with_byte_unit(TYPE_CHAR, &function_call_stack[function_call_stack_deep + baseOffset + i * eleOffset], &tmp); 
    }
  }
  else
  {
    if(q != NULL)
    {
      baseOffset = q->offset;
    }

    assign_with_byte_unit(p->type->type_id, &function_call_stack[function_call_stack_deep + baseOffset + p->offset], &(n->val)); 
  }
  
}
void load_function_call_stack_val(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }

  load_with_byte_unit(p->type->type_id, &function_call_stack[function_call_stack_deep + baseOffset + p->offset], &(n->val));
}