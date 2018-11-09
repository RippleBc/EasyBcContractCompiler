#include "../common.h"

void vm_assign_global(Node n, Symbol p)
{
  if(n != NULL && p != NULL)
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
    for(int i = 0; i < strlen(n->val.s); i++)
    {
      if(i > p->type_link->num_ele - 1)
      {
        parse_error("assign_global array out of index", p->name);
        return;
      }

      /* address */
      int code = get_op_code_by_name("PUSH");
      push_command(code);
      s_index.i = baseOffset + i * ele_size;
      push_data(find_type_by_id(TYPE_INTEGER), &s_index);
      /* val */
      code = get_op_code_by_name("PUSH");
      push_command(code);
      s_val.c = n->val.s[i];
      push_data(find_type_by_id(TYPE_CHAR), &s_val);
      /*  */
      code = get_op_code_by_name("ASSIGN_GLOBAL");
      push_command(code);
    }
  }
  else
  {
    /*  */
    int code = get_op_code_by_name("ASSIGN_GLOBAL");
    push_command(code);
  }
}
void vm_load_global()
{
  /*  */
  int code = get_op_code_by_name("LOAD_GLOBAL");
  push_command(code);
}