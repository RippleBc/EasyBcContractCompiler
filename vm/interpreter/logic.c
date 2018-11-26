#include "../common.h"

void logic_command(struct _op_code_ *code_detail)
{
  if(!strcmp(code_detail->name, "IEQ"))
  {
    value result;
    result.b = get_int_from_vm_stack() == get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
  }
  else if(!strcmp(code_detail->name, "INE"))
  {
    value result;
    result.b = get_int_from_vm_stack() != get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
  }
  if(!strcmp(code_detail->name, "UCEQ"))
  {
    value result;
    result.b = get_uchar_from_vm_stack() == get_uchar_from_vm_stack();

    push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
  }
  else if(!strcmp(code_detail->name, "UCNE"))
  {
    value result;
    result.b = get_uchar_from_vm_stack() != get_uchar_from_vm_stack();

    push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
  }
  else if(!strcmp(code_detail->name, "IGE"))
  {
    value result;
    result.b = get_int_from_vm_stack() >= get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
  }
  else if(!strcmp(code_detail->name, "IGT"))
  {
    value result;
    result.b = get_int_from_vm_stack() > get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
  }
  else if(!strcmp(code_detail->name, "ILE"))
  {
    value result;
    result.b = get_int_from_vm_stack() <= get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
  }
  else if(!strcmp(code_detail->name, "ILT"))
  {
    value result;
    result.b = get_int_from_vm_stack() < get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
  }
}
      