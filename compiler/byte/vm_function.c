#include "../common.h"

/*  */
void vm_push_function_call_stack(Symtab tab)
{
  value s_add;
  s_add.i = tab->call_stack_size;
  push_data(find_system_type_by_id(TYPE_INTEGER), &s_add);
  /*  */
  int code = get_op_code_by_name("PUSH_CALL");
  push_command(code);
  
}
void vm_pop_function_call_stack(Symtab tab)
{
  value s_sub;
  s_sub.i = tab->call_stack_size;
  push_data(find_system_type_by_id(TYPE_INTEGER), &s_sub);
  /*  */
  int code = get_op_code_by_name("POP_CALL");
  push_command(code);
}
void vm_assign_function_call_stack_val(Type v_type, Value v, Symbol p)
{
  char command_name[NAME_LEN];

  if(v != NULL && p != NULL)
  {
    /*  */
    value s_index;
    /*  */
    value s_val;

    /*  */
    int baseOffset = p->offset;
    /*  */
    int ele_size = get_symbol_align_size(p->type->last);

    /*  */
    snprintf(command_name, NAME_LEN, "ASSIGN_CALL%d", IR->charmetric.align);

    /*  */
    for(int i = 0; i < strlen(v->s); i++)
    {
      if(i > p->type->num_ele - 1)
      {
        printf("assign_local array out of index", p->name);
        exit(1);
      }

      /* val */
      s_val.c = v->s[i];
      push_data(find_system_type_by_id(TYPE_CHAR), &s_val);
      /* address */
      value s_offset;
      s_offset.i = baseOffset + i * ele_size;
      push_data(find_system_type_by_id(TYPE_INTEGER), &s_offset);
      /*  */
      int code = get_op_code_by_name(command_name);
      push_command(code);
    }
  }
  else
  {
    snprintf(command_name, NAME_LEN, "ASSIGN_CALL%d", get_type_align_size(v_type));
    /*  */
    int code = get_op_code_by_name(command_name);
    push_command(code);
  }
}
void vm_load_function_call_stack_val(Type t)
{
  char command_name[NAME_LEN];
  snprintf(command_name, NAME_LEN, "LOAD_CALL%d", get_type_align_size(t));
  /*  */
  int code = get_op_code_by_name(command_name);
  push_command(code);
}

void vm_set_return_val(Symtab ptab)
{
  /*  */
  Symbol return_sym = ptab->return_sym;

  /* return val address */
  value v_address;
  v_address.i = return_sym->offset;
  push_data(return_sym->type, &v_address);

  /*  */
  char command_name[NAME_LEN];
  snprintf(command_name, NAME_LEN, "LOAD_CALL%d", get_type_align_size(return_sym->type));
  int code = get_op_code_by_name(command_name);
  push_command(code);
}

void vm_set_return_index(int index)
{
  char command_name[NAME_LEN];

  /* val */
  value s_return_position;
  s_return_position.i = index;
  push_data(find_system_type_by_id(TYPE_INTEGER), &s_return_position);
  /* address*/
  value s_return_address;
  s_return_address.i = 0;
  push_data(find_system_type_by_id(TYPE_INTEGER), &s_return_address);
  /*  */
  snprintf(command_name, NAME_LEN, "ASSIGN_CALL%d", IR->intmetric.align);
  int code = get_op_code_by_name(command_name);
  push_command(code);
}

void vm_get_return_index()
{
  char command_name[NAME_LEN];

  /* address*/
  value s_return_address;
  s_return_address.i = 0;
  push_data(find_system_type_by_id(TYPE_INTEGER), &s_return_address);
  /*  */
  snprintf(command_name, NAME_LEN, "LOAD_CALL%d", IR->intmetric.align);
  int code = get_op_code_by_name(command_name);
  push_command(code);
}