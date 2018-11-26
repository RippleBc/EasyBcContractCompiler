#include "../common.h"

void mathmatical_command(struct _op_code_ *code_detail)
{
  /*  */
  if(!strcmp(code_detail->name, "ILSH"))
  {
    value result;
    result.i = get_int_from_vm_stack() <<  get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "IRSH"))
  {
    value result;
    result.i = get_int_from_vm_stack() >>  get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "UILSH"))
  {
    value result;
    result.ui = get_uint_from_vm_stack() <<  get_uint_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "UIRSH"))
  {
    value result;
    result.ui = get_uint_from_vm_stack() >>  get_uint_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "RLSH"))
  {
    value result;
    result.i = get_int_from_vm_stack() <<  get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "RRSH"))
  {
    value result;
    result.i = get_int_from_vm_stack() >>  get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "UCLSH"))
  {
    value result;
    result.i = get_int_from_vm_stack() <<  get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "UCRSH"))
  {
    value result;
    result.i = get_int_from_vm_stack() >>  get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }
  /* basic arithmatical */
  if(!strcmp(code_detail->name, "IADD"))
  {
    value result;
    result.i = get_int_from_vm_stack() + get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "ISUB"))
  {
    value result;
    result.i = get_int_from_vm_stack() - get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  if(!strcmp(code_detail->name, "IMUL"))
  {
    value result;
    result.i = get_int_from_vm_stack() * get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "IDIV"))
  {
    value result;
    result.i = get_int_from_vm_stack() / get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  if(!strcmp(code_detail->name, "RADD"))
  {
    value result;
    result.f = get_real_from_vm_stack() + get_real_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "RSUB"))
  {
    value result;
    result.f = get_real_from_vm_stack() - get_real_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  if(!strcmp(code_detail->name, "RMUL"))
  {
    value result;
    result.f = get_real_from_vm_stack() * get_real_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "RDIV"))
  {
    value result;
    result.f = get_real_from_vm_stack() / get_real_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "MOD"))
  {
    value result;
    result.i = get_int_from_vm_stack() % get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "IINCR"))
  {
    value result;
    result.i = get_int_from_vm_stack() + 1;

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "IDECR"))
  {
    value result;
    result.i = get_int_from_vm_stack() - 1;

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }


  /*  */
  else if(!strcmp(code_detail->name, "ICVF"))
  {
    value result;
    result.f = (float)get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_REAL, &result);
  }
  else if(!strcmp(code_detail->name, "ICVI") || !strcmp(code_detail->name, "ICVB"))
  {
    
  }
  else if(!strcmp(code_detail->name, "ICVUI"))
  {
    value result;
    result.ui = (unsigned int)get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "ICVUC"))
  {
    value result;
    result.uc = (unsigned char)get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UCHAR, &result);
  }
  else if(!strcmp(code_detail->name, "ICVC"))
  {
    value result;
    result.c = (char)get_int_from_vm_stack();

    push_vm_stack_from_compute(TYPE_CHAR, &result);
  }
  /*  */
  else if(!strcmp(code_detail->name, "UICVF"))
  {
    value result;
    result.f = (float)get_uint_from_vm_stack();

    push_vm_stack_from_compute(TYPE_REAL, &result);
  }
  else if(!strcmp(code_detail->name, "UICVB") || !strcmp(code_detail->name, "UICVUI"))
  {
    
  }
  else if(!strcmp(code_detail->name, "UICVI"))
  {
    value result;
    result.i = (int)get_uint_from_vm_stack();

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "UICVUC"))
  {
    value result;
    result.uc = (unsigned char)get_uint_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UCHAR, &result);
  }
  else if(!strcmp(code_detail->name, "UICVC"))
  {
    value result;
    result.c = (char)get_uint_from_vm_stack();

    push_vm_stack_from_compute(TYPE_CHAR, &result);
  }
  /*  */
  else if(!strcmp(code_detail->name, "RCVF"))
  {
    
  }
  else if(!strcmp(code_detail->name, "RCVI") || !strcmp(code_detail->name, "RCVB"))
  {
    value result;
    result.i = (int)get_real_from_vm_stack();

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "RCVUI"))
  {
    value result;
    result.ui = (unsigned int)get_real_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "RCVUC"))
  {
    value result;
    result.uc = (unsigned char)get_real_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UCHAR, &result);
  }
  else if(!strcmp(code_detail->name, "RCVC"))
  {
    value result;
    result.c = (char)get_real_from_vm_stack();

    push_vm_stack_from_compute(TYPE_CHAR, &result);
  }
  /*  */
  else if(!strcmp(code_detail->name, "UCCVF"))
  {
    value result;
    result.f = (float)get_uchar_from_vm_stack();

    push_vm_stack_from_compute(TYPE_REAL, &result);
  }
  else if(!strcmp(code_detail->name, "UCCVI") || !strcmp(code_detail->name, "UCCVB"))
  {
    value result;
    result.i = (int)get_uchar_from_vm_stack();

    push_vm_stack_from_compute(TYPE_INTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "UCCVUI"))
  {
    value result;
    result.ui = (unsigned int)get_uchar_from_vm_stack();

    push_vm_stack_from_compute(TYPE_UINTEGER, &result);
  }
  else if(!strcmp(code_detail->name, "UCCVUC"))
  {
    
  }
  else if(!strcmp(code_detail->name, "UCCVC"))
  {
    value result;
    result.c = (char)get_uchar_from_vm_stack();

    push_vm_stack_from_compute(TYPE_CHAR, &result);
  }
}