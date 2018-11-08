#include "../common.h"

#define GLOBAL_LENGTH 256

/*  */
int global_length = GLOBAL_LENGTH;
void assign_global(Node n, Symbol p, Symbol q)
{
  int baseOffset = 0;
  value s_index;

  if(p->type->type_id == TYPE_ARRAY)
  {
    value s_val;

    baseOffset = p->offset;

    int eleOffset = get_symbol_align_size(p->type_link->last);

    for(int i = 0; i < strlen(n->val.s); i++)
    {
      if(i > p->type_link->num_ele - 1)
      {
        parse_error("assign_global array out of index", p->name);
        return;
      }

      /*  */
      int command_push_code = get_op_code_by_name("ASSIGN_GLOBAL");
      push_command(command_push_code);
      /*  */
      s_index.i = baseOffset + i * eleOffset;
      push_data(find_type_by_id(TYPE_INTEGER), &s_index);
      /*  */
      s_val.c = n->val.s[i];
      push_data(find_type_by_id(TYPE_CHAR), &s_val);
    }
  }
  else
  {
    if(q != NULL)
    {
      baseOffset = q->offset;
    }
    
    /*  */
    int command_push_code = get_op_code_by_name("ASSIGN_GLOBAL");
    push_command(command_push_code);
    /*  */
    s_index.i = baseOffset + p->offset;
    push_data(find_type_by_id(TYPE_INTEGER), &s_index);
    /*  */
    push_data(p->type, &(n->val));
  }
}
void load_global(Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }
  
  /*  */
  int command_push_code = get_op_code_by_name("LOAD_GLOBAL");
  push_command(command_push_code);
  /*  */
  value s_index;
  s_index.i = baseOffset + p->offset;
  push_data(find_type_by_id(TYPE_INTEGER), &s_index);
}

#define STACK_DEEP 256

/*  */
int function_call_stack_deep = STACK_DEEP;
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
  value s_index;

  if(p->type->type_id == TYPE_ARRAY)
  {
    value s_val;

    baseOffset = p->offset;

    int eleOffset = get_symbol_align_size(p->type_link->last);

    for(int i = 0; i < strlen(n->val.s); i++)
    {
      if(i > p->type_link->num_ele - 1)
      {
        parse_error("assign_local array out of index", p->name);
        return;
      }

      /*  */
      int command_push_code = get_op_code_by_name("ASSIGN_FUNCTION_CALL_STACK_VAL");
      push_command(command_push_code);
      /*  */
      s_index.i = function_call_stack_deep + baseOffset + i * eleOffset;
      push_data(find_type_by_id(TYPE_INTEGER), &s_index);
      /*  */
      s_val.c = n->val.s[i];
      push_data(find_type_by_id(TYPE_CHAR), &s_val);
    }
  }
  else
  {
    if(q != NULL)
    {
      baseOffset = q->offset;
    }

    /*  */
    int command_push_code = get_op_code_by_name("ASSIGN_FUNCTION_CALL_STACK_VAL");
    push_command(command_push_code);
    /*  */
    s_index.i = function_call_stack_deep + baseOffset + p->offset;
    push_data(find_type_by_id(TYPE_INTEGER), &s_index);
    /*  */
    push_data(p->type, &(n->val));
  }
  
}
void load_function_call_stack_val(Symbol p, Symbol q)
{
  int baseOffset = 0;
  if(q != NULL)
  {
    baseOffset = q->offset;
  }

  /*  */
  int command_push_code = get_op_code_by_name("LOAD_FUNCTION_CALL_STACK_VAL");
  push_command(command_push_code);
  /*  */
  value s_index;
  s_index.i = function_call_stack_deep + baseOffset + p->offset;
  push_data(find_type_by_id(TYPE_INTEGER), &s_index);
}

void set_return_index(int index)
{
  /*  */
  int command_push_code = get_op_code_by_name("ASSIGN_FUNCTION_CALL_STACK_VAL");
  push_command(command_push_code);
  /*  */
  value s_index;
  s_index.i = function_call_stack_deep;
  push_data(find_type_by_id(TYPE_INTEGER), &s_index);
  /*  */
  value s_return_index;
  s_return_index.i = index;
  push_data(find_type_by_id(TYPE_INTEGER), &s_return_index);
}

void get_return_index()
{
  /*  */
  int command_push_code = get_op_code_by_name("LOAD_FUNCTION_CALL_STACK_VAL");
  push_command(command_push_code);
  /*  */
  value s_index;
  s_index.i = function_call_stack_deep;
  push_data(find_type_by_id(TYPE_INTEGER), &s_index);
}