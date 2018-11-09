#include "../common.h"

/*  */
void vm_push_function_call_stack(Symtab tab)
{
  int code = get_op_code_by_name("PUSH");
  push_command(code);
  value s_add;
  s_add.i = tab->call_stack_size;
  push_data(find_type_by_id(TYPE_INTEGER), &s_add);
  /*  */
  code = get_op_code_by_name("PUSH_CALL");
  push_command(code);
  
}
void vm_pop_function_call_stack(Symtab tab)
{
  int code = get_op_code_by_name("PUSH");
  push_command(code);
  value s_sub;
  s_sub.i = tab->call_stack_size;
  push_data(find_type_by_id(TYPE_INTEGER), &s_sub);
  /*  */
  code = get_op_code_by_name("POP_CALL");
  push_command(code);
}
void vm_assign_function_call_stack_val(Value v, Symbol p)
{
  if(v != NULL && p != NULL)
  {
    /*  */
    value s_index;
    /*  */
    value s_val;

    /*  */
    int baseOffset = p->offset;
    /*  */
    int ele_size = get_symbol_align_size(p->type_link->last);

    /*  */
    for(int i = 0; i < strlen(v->s); i++)
    {
      if(i > p->type_link->num_ele - 1)
      {
        parse_error("assign_local array out of index", p->name);
        return;
      }

      /* address */
      int code = get_op_code_by_name("PUSH");
      push_command(code);
      value s_offset;
      s_offset.i = baseOffset + i * ele_size;
      push_data(find_type_by_id(TYPE_INTEGER), &s_offset);
      /* val */
      code = get_op_code_by_name("PUSH");
      push_command(code);
      s_val.c = v->s[i];
      push_data(find_type_by_id(TYPE_CHAR), &s_val);
      /*  */
      code = get_op_code_by_name("ASSIGN_CALL");
      push_command(code);
    }
  }
  else
  {
    /*  */
    int code = get_op_code_by_name("ASSIGN_CALL");
    push_command(code);
  }
}
void vm_load_function_call_stack_val(Symbol p, Symbol q)
{
  /*  */
  int code = get_op_code_by_name("LOAD_CALL");
  push_command(code);
}

void vm_set_return_index(int index)
{
  /* address*/
  int code = get_op_code_by_name("TOP_CALL");
  push_command(code);
  /* val */
  value s_return_index;
  s_return_index.i = index;
  push_data(find_type_by_id(TYPE_INTEGER), &s_return_index);
  /*  */
  code = get_op_code_by_name("ASSIGN_CALL");
  push_command(code);
}

void vm_get_return_index()
{
  /* address*/
  int code = get_op_code_by_name("TOP_CALL");
  push_command(code);
  /*  */
  code = get_op_code_by_name("LOAD_CALL");
  push_command(code);
}