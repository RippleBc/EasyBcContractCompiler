#include "../common.h"

void vm_assign_global(Type v_type, Value v, Symbol p)
{
  char command_name[NAME_LEN];

  if(v != NULL && p != NULL)
  {
    value s_index;
    /*  */
    value s_val;

    /*  */
    int baseOffset = p->offset;
    /*  */
    int ele_size = get_symbol_align_size(p->type->last);

    /*  */
    snprintf(command_name, NAME_LEN, "ASSIGN_GLOBAL%d", IR->charmetric.align);

    /*  */
    for(int i = 0; i < strlen(v->s); i++)
    {
      if(i > p->type->num_ele - 1)
      {
        parse_error("assign_global array out of index", p->name);
        return;
      }

      /* val */
      s_val.c = v->s[i];
      push_data(find_system_type_by_id(TYPE_CHAR), &s_val);
      /* address */
      s_index.i = baseOffset + i * ele_size;
      push_data(find_system_type_by_id(TYPE_INTEGER), &s_index);
      /*  */
      int code = get_op_code_by_name(command_name);
      push_command(code);
    }
  }
  else
  {
    snprintf(command_name, NAME_LEN, "ASSIGN_GLOBAL%d", get_type_align_size(v_type));
    /*  */
    int code = get_op_code_by_name(command_name);
    push_command(code);
  }
}
void vm_load_global(Type t)
{
  char command_name[NAME_LEN];
  snprintf(command_name, NAME_LEN, "LOAD_GLOBAL%d", get_type_align_size(t));
  /*  */
  int code = get_op_code_by_name(command_name);
  push_command(code);
}