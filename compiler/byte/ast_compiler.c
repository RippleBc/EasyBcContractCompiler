#include  <stdio.h>
#include  "../common.h"
#include  "../ast/symtab.h"
#include  "../parser/error.h"
#include  "../parser/rule.h"

List g_cp;
List g_routine;
List g_routine_forest;

static int sys_id;

#define GLOBAL_AREA_MARK 1
#define FUNCTION_CALL_STACK_MARK 2
#define CODE_MAX_NUM 1024 * 48

int code_byte_index = 0;
unsigned char code_byte_sequence[CODE_MAX_NUM];
void push_data(Type t, Value v)
{
  /*  */
  int data_size = get_type_align_size(t);

  /*  */
  if(code_byte_index + data_size >= CODE_MAX_NUM)
  {
    printf("code_byte_sequence is full, max size is %d\n", CODE_MAX_NUM);
    exit(1);
  }

  /*  */
  char command[NAME_LEN];
  snprintf(command, NAME_LEN, "PUSH%d", data_size);
  int code = get_op_code_by_name(command);
  push_command(code);

  /*  */
  assign_with_byte_unit(t->type_id, &code_byte_sequence[code_byte_index], v);

  if(BYTE_DEBUG)
  {
    switch(t->type_id)
    {
      case TYPE_INTEGER:
      {
        printf("byte index %d, size %d, data %x\n", code_byte_index, data_size, v->i);
      }
      break;
      case TYPE_UINTEGER:
      {
        printf("byte index %d, size %d, data %x\n", code_byte_index, data_size, v->ui);
      }
      break;
      case TYPE_REAL:
      {
        printf("byte index %d, size %d, data %x\n", code_byte_index, data_size, v->f);
      }
      break;
      case TYPE_BOOLEAN:
      {
        printf("byte index %d, size %d, data %x\n", code_byte_index, data_size, v->b);
      }
      break;
      case TYPE_CHAR:
      {
        printf("byte index %d, size %d, data %x\n", code_byte_index, data_size, v->c);
      }
      break;
      case TYPE_UCHAR:
      {
        printf("byte index %d, size %d, data %x\n", code_byte_index, data_size, v->uc);
      }
      break;
      default:
      {
        printf("push_data err, unsupported type %\n", t->name);
        exit(1);
      }
    }
  }

  /*  */
  code_byte_index += data_size;
}

void push_command(int code)
{
  if(BYTE_DEBUG)
  {
    char *name = get_name_by_op_code(code);
    printf("byte index %d, op code %x, op name %s\n", code_byte_index, code, name);
  }

  /*  */
  if(code_byte_index >= CODE_MAX_NUM)
  {
    printf("code_byte_sequence overflow\n");
    exit(1);
  }

  /*  */
  code_byte_sequence[code_byte_index++] = code;
}

/*  */
typedef struct _label_detail_ *LabelDetail;
struct _label_detail_
{
  int code_index;
  char name[NAME_LEN];
};
static int label_detail_index = 0;
static LabelDetail label_detail_sequence[CODE_MAX_NUM];
static void push_label(char *name, int code_index)
{
  NEW0(label_detail_sequence[label_detail_index], PERM);
  if(!label_detail_sequence[label_detail_index])
  {
    printf("insufficient memory\n");
    exit(1);
  }
  /*  */
  label_detail_sequence[label_detail_index]->code_index = code_index;
  strncpy(label_detail_sequence[label_detail_index]->name, name, NAME_LEN);

  label_detail_index ++;
}
static int get_label_index(char *name)
{
  int i = 0;
  while(i < label_detail_index)
  {
    if(!strcmp(label_detail_sequence[i]->name, name))
    {
      return label_detail_sequence[i]->code_index;
    }

    i++;
  }
  
  printf("label is not exist %s\n", name);
  exit(1);
}

/*  */
typedef struct _function_detail_ *FunctionDetail;
struct _function_detail_
{
  int code_index;
  Symtab ptab;
};
static int function_detail_index = 0;
static FunctionDetail function_detail_sequence[CODE_MAX_NUM];
static void push_function(Symtab ptab, int code_index)
{
  NEW0(function_detail_sequence[function_detail_index], PERM);
  if(!function_detail_sequence[function_detail_index])
  {
    printf("insufficient memory\n");
    exit(1);
  }
  /*  */
  function_detail_sequence[function_detail_index]->code_index = code_index;
  function_detail_sequence[function_detail_index]->ptab = ptab;

  function_detail_index ++;
}
static int get_function_index(Symtab ptab)
{
  int i = 0;
  while(i < function_detail_index)
  {
    if(function_detail_sequence[i]->ptab == ptab)
    {
      return function_detail_sequence[i]->code_index;
    }

    i++;
  }
  
  printf("function is not exist %s\n", ptab->name);
  exit(1);
}

/*  */
struct _jump_detail_
{
  int code_index;
  char name[NAME_LEN]; /* normal label */
  Symtab ptab; /* function label */
};
typedef struct _jump_detail_ *JumpDetail;
static int jump_detail_index = 0;
static JumpDetail jump_detail_sequence[CODE_MAX_NUM];
static void push_jump_detail(char *name, int index, Symtab ptab)
{
  NEW0(jump_detail_sequence[jump_detail_index], PERM);
  if(!jump_detail_sequence[jump_detail_index])
  {
    printf("insufficient memory\n");
    exit(1);
  }

  jump_detail_sequence[jump_detail_index]->code_index = index;

  if(name)
  {
    strncpy(jump_detail_sequence[jump_detail_index]->name, name, NAME_LEN);
  }
  else
  {
    jump_detail_sequence[jump_detail_index]->ptab = ptab;
  }

  jump_detail_index++;
}

/*  */
void ast_compile(List routine_forest, List dag)
{
  printf("\n********************\nbegin compiler to code bytes\n********************\n");

  g_routine_forest = routine_forest;

  /* 将全局符号表压入符号表栈中 */
  push_symtab_stack(Global_symtab);
  
  /*  */
  for(g_cp = dag->link; g_cp != NULL; g_cp = g_cp->link)
  {
    node_compile((Node)(g_cp->x));
  }

  /*  */
  for(g_cp = g_routine_forest->link; g_cp != NULL; g_cp = g_cp->link)
  {
    /*  */
    for(g_routine = (List)(g_cp->x); g_routine != NULL; g_routine = g_routine->link)
    {
      /*  */
      node_compile((Node)(g_routine->x));
    }
  }

  /*  */
  int i = 0;
  int label_or_function_index;
  int jump_index;
  while(i < jump_detail_index)
  {
    if(jump_detail_sequence[i]->ptab == NULL)
    {
      /*  */
      char *label_name = jump_detail_sequence[i]->name;
      /*  */
      label_or_function_index = get_label_index(label_name);
    }
    else
    {
      Symtab ptab = jump_detail_sequence[i]->ptab;
      /*  */
      label_or_function_index = get_function_index(ptab);
    }

    jump_index = jump_detail_sequence[i]->code_index;

    /*  */
    value v_jump_code;
    v_jump_code.i = label_or_function_index;
    assign_with_byte_unit(TYPE_INTEGER, &code_byte_sequence[jump_index], &v_jump_code);


    if(BYTE_DEBUG)
    {
      printf("position function call index, byte index %d, function or label index %d\n", jump_index, label_or_function_index);
    }

    i++;
  }

  code_byte_sequence[code_byte_index] = '\0';
}

int node_compile(Node node)
{
  /* 流程控制相关 */
  switch (generic(node->op))
  {
  case LABEL:
  {
    Symbol p = node->syms[0];

    /*  */
    push_label(p->name, code_byte_index);
  }
  break;
  case JUMP:
  {
    Symbol p = node->syms[0];

    /* record the jump position */
    push_jump_detail(p->name, code_byte_index + 1, NULL);
    /* jump position */
    value jump_position;
    jump_position.i = -1;
    push_data(find_system_type_by_id(TYPE_INTEGER), &jump_position);
    /*  */
    int jump_code = get_op_code_by_name("JUMP");
    push_command(jump_code);
  }
  break;
  case COND:
  {
    /* test val */
    node_compile(node->kids[0]);

    /*  */
    switch(node->kids[0]->type->type_id)
    {
    case TYPE_INTEGER:
    case TYPE_BOOLEAN:
    {
      /*  */
      value cond;
      if(node->u.cond.true_or_false == true)
      {
        /*  */
        cond.b = true;
      }
      else
      {
        /*  */
        cond.b = false;
      }

      /*  */
      push_data(find_system_type_by_id(TYPE_BOOLEAN), &cond);
    }
    break;
    case TYPE_CHAR:
    {
      printf("COND expression can not be char");
      exit(1);
    }
    break;
    case TYPE_REAL:
    {
      printf("COND expression can not be real");
      exit(1);
    }
    break;
    case TYPE_STRING:
    {
      printf("COND expression can not be string");
      exit(1);
    }
    break;
    }

    /* record the jump position */
    Symbol p = node->u.cond.label;
    push_jump_detail(p->name, code_byte_index + 1, NULL);
    /* jump position */
    value jump_position;
    jump_position.i = -1;
    push_data(find_system_type_by_id(TYPE_INTEGER), &jump_position);
    /*  */
    int jump_code = get_op_code_by_name("COND");
    push_command(jump_code);
  }
  break;
  }

  /* 函数调用相关 */
  switch (generic(node->op))
  {
  case SYS:
  {
    sys_id = node->u.sys_id;

    /*  */
    node_compile(node->kids[0]);

    int command_function_code = 0;
    switch (node->u.sys_id)
    {
      case pREADLN:
      {
        /*  */
        command_function_code = get_op_code_by_name("READLN");
      }
      break;
      case pWRITELN:
      {
        /*  */
        command_function_code = get_op_code_by_name("WRITELN");
      }
      break;
    }

    push_command(command_function_code);
  }
  break;
  case CALL:
  {
    /*  */
    vm_push_function_call_stack(node->symtab);

    /* 实参 */
    if (node->kids[0] != NULL)
    {
      node_compile(node->kids[0]);
    }

    /* set return index */
    int return_index = code_byte_index + 1 + IR->intmetric.align + 1 + 1 + 1 + IR->intmetric.align + 1;
    vm_set_return_index(return_index);

    /*  */
    push_jump_detail(NULL, code_byte_index + 1, node->symtab);

    /*  */
    value function_index;
    function_index.i = -1;
    push_data(find_system_type_by_id(TYPE_INTEGER), &function_index);
    /*  */
    int jump_code = get_op_code_by_name("JUMP");
    push_command(jump_code);
  }
  break;
  case RIGHT:
  case ARG:
  {
    /* 计算其余参数的值 */
    if(node->kids[1] != NULL)
    {
      node_compile(node->kids[1]);
    }

    /*  */
    Symbol arg = node->syms[0];

    if(arg)
    {
      if(arg->type->type_id == TYPE_ARRAY)
      {
        vm_assign_function_call_stack_val(NULL, &(node->kids[0]->syms[0]->v), arg);
      }
      else
      {
        /* val */
        node_compile(node->kids[0]);

        /* address */
        value s_offset;
        s_offset.i = arg->offset;
        push_data(find_system_type_by_id(TYPE_INTEGER), &s_offset);

        /*  */
        vm_assign_function_call_stack_val(node->kids[0]->type, NULL, NULL);
      }
    }
    else
    {
      /* writeln format string*/
      if(generic(node->kids[0]->op) == CNST && node->kids[0]->syms[0]->type->type_id == TYPE_STRING)
      {
        value v;
        char *p_c = node->kids[0]->syms[0]->v.s;
        int string_len = strlen(p_c);

        /* data */
        for(int i = string_len - 1; i >= 0 ; i--)
        {
          v.c = p_c[i];
          push_data(find_system_type_by_id(TYPE_CHAR), &v);
        }

        /* data size */
        v.i = string_len;
        push_data(find_system_type_by_id(TYPE_INTEGER), &v);
      }
      else
      {

        /* val or address(syscall, no symtab, no arg sym) */
        node_compile(node->kids[0]);

        /*  */
        if(sys_id == pREADLN)
        {
          /* size */
          value v_size;
          v_size.i = get_type_align_size(node->kids[0]->type);
          push_data(find_system_type_by_id(TYPE_INTEGER), &v_size);

          /* global or function call */
          value v_p_mark;
          Symbol p = node->kids[0]->syms[0];
          if(p->tab == Global_symtab)
          {
            v_p_mark.i = GLOBAL_AREA_MARK;
          }
          else
          {
            v_p_mark.i = FUNCTION_CALL_STACK_MARK;
          }
          push_data(find_system_type_by_id(TYPE_INTEGER), &v_p_mark);
        }
      }
    }
  }
  break;
  }

  /* 取值赋值相关 */
  switch (generic(node->op))
  {
    case CNST:
    {
      Symbol p = node->syms[0];

      if(p->type->type_id != TYPE_STRING)
      {
        /*  */
        push_data(p->type, &(p->v));
      }
    }
    break;
    case FIELD:
    {
      Symbol record = node->syms[0];
      Symbol field = node->syms[1];
      
      /* compute field offset base on record */
      value filed_offset;
      filed_offset.i = field->offset;
      push_data(find_system_type_by_id(TYPE_INTEGER), &filed_offset);

      /* compute record offset base on stack*/
      value record_offset;
      record_offset.i = record->offset;
      push_data(find_system_type_by_id(TYPE_INTEGER), &record_offset);

      /* compute field offset base on stack */
      int code = get_op_code_by_name("IADD");
      push_command(code);
    }
    break;
    case ARRAY:
    {
      Symbol array = node->syms[0];

      /* array min index */
      value startIndex;
      startIndex.i = array->type->first->v.i;
      push_data(find_system_type_by_id(TYPE_INTEGER), &startIndex);

      /* 数组下标 */
      node_compile(node->kids[0]);

      /* compute element offset base on array */
      int code = get_op_code_by_name("ISUB");
      push_command(code);
      /*  */
      value ele_size;
      ele_size.i = get_symbol_align_size(array->type->last);
      push_data(find_system_type_by_id(TYPE_INTEGER), &ele_size);
      /*  */
      code = get_op_code_by_name("IMUL");
      push_command(code);

      /* compute array offset base on stack */
      value base_offset;
      base_offset.i = array->offset;
      push_data(find_system_type_by_id(TYPE_INTEGER), &base_offset);

      /* compute element offset base on stack*/
      code = get_op_code_by_name("IADD");
      push_command(code);
    }
    break;
    case ADDRG:
    {
      Symbol sym = node->syms[0];
      
      if(sym->type->type_id != TYPE_ARRAY)
      {
        /* address */
        value sym_offset;
        sym_offset.i = sym->offset;
        push_data(find_system_type_by_id(TYPE_INTEGER), &sym_offset);
      }
    }
    break;
    case LOAD:
    {
      Symbol p = node->syms[0];
      Symbol s_mixedType = NULL;

      if(node->kids[0])
      {
        /* 地址节点 */
        node_compile(node->kids[0]);
        /* syms[0]表示数组或者记录，syms[1]表示数组成员或者属性，node->kids[0]表示ARRAY或者FIELD节点 */
        s_mixedType = node->kids[0]->syms[0];
      }

      if(p && p->defn == DEF_ENUM_ELEMENT)
      {
        /*  */
        push_data(p->type, &(p->v));
      }
      else
      {
        /* 全局变量 */
        if((s_mixedType && s_mixedType->tab == Global_symtab) || (p && p->tab == Global_symtab))
        {
          if(p)
          {
            /* address */
            value sym_offset;
            sym_offset.i = p->offset;
            push_data(find_system_type_by_id(TYPE_INTEGER), &sym_offset);
          }

          /*  */
          vm_load_global(node->type);
        }
        else
        {
          if(p)
          {
            /* address */
            value sym_offset;
            sym_offset.i = p->offset;
            push_data(find_system_type_by_id(TYPE_INTEGER), &sym_offset);
          }

          /*  */
          vm_load_function_call_stack_val(node->type);
        }
      }
    }
    break;
    case ASGN:
    {
      Symbol p = node->kids[0]->syms[0];
      Symbol s_mixedType = NULL;
      Symbol s_array = NULL;
      
      if(generic(node->kids[0]->op) != ADDRG)
      {
        /* array or record */
        s_mixedType = node->kids[0]->syms[0];
      }

      if(generic(node->kids[0]->op) == ADDRG && node->kids[0]->syms[0]->type->type_id == TYPE_ARRAY)
      {
        s_array = node->kids[0]->syms[0];
      }

      /* val */
      node_compile(node->kids[1]);

      /* address */
      node_compile(node->kids[0]);

      if((s_mixedType && s_mixedType->tab == Global_symtab) || (p && p->tab == Global_symtab))
      {
        if(s_array)
        {
          /*  */
          vm_assign_global(NULL, &(node->kids[1]->syms[0]->v), s_array);
        }
        else
        {
          /*  */
          vm_assign_global(node->kids[1]->type, NULL, NULL);
        }
      }
      else
      {
        if(s_array)
        {
          /* 局部变量赋值 */
          vm_assign_function_call_stack_val(NULL, &(node->kids[1]->syms[0]->v), s_array);
        }
        else
        {
          /*  */
          vm_assign_function_call_stack_val(node->kids[1]->type, NULL, NULL);
        }
      }
    }
    break;
  }

  /* 二元数学运算 */
  switch (generic(node->op))
  {
    case MOD:
    {
      /* 计算右表达式AST节点对应的值 */
      if(node->kids[1] != NULL)
      {
        node_compile(node->kids[1]);
      }

      /* 计算左表达式AST节点对应的值 */
      if(node->kids[0] != NULL)
      {
        node_compile(node->kids[0]);
      }

      /*  */
      char *code_name = get_op_name(generic(node->op));
      if(code_name == NULL)
      {
        printf("op name not exist, op code %d\n", node->op);
        exit(1);
      }
      /*  */
      int code = get_op_code_by_name(code_name);
      /*  */
      push_command(code);
    }
    break;
    case LSH:
    case RSH:
    case BAND:
    case BOR:
    case BXOR:
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case EQ:
    case NE:
    case GE:
    case GT:
    case LE:
    case LT:
    {
      /* 计算右表达式AST节点对应的值 */
      if(node->kids[1] != NULL)
      {
        node_compile(node->kids[1]);
      }

      /* 计算左表达式AST节点对应的值 */
      if(node->kids[0] != NULL)
      {
        node_compile(node->kids[0]);
      }

      /*  */
      char *code_name = get_op_name(generic(node->op));
      if(code_name == NULL)
      {
        printf("op name not exist, op code %d\n", node->op);
        exit(1);
      }
      /*  */
      int code = get_type_related_op_code_by_name(node->kids[0]->type, code_name);
      /*  */
      push_command(code);
    }
    break;
    case AND:
    case OR:
    {
      /* 计算右表达式AST节点对应的值 */
      if(node->kids[1] != NULL)
      {
        node_compile(node->kids[1]);
      }

      /* 计算左表达式AST节点对应的值 */
      if(node->kids[0] != NULL)
      {
        node_compile(node->kids[0]);
      }

      /*  */
      char *code_name = get_op_name(generic(node->op));
      if(code_name == NULL)
      {
        printf("op name not exist, op code %d\n", node->op);
        exit(1);
      }
      /*  */
      int code = get_op_code_by_name(code_name);
      /*  */
      push_command(code);
    }
    break;
  }

  /* 一元数学元算 */
  switch (generic(node->op))
  {
    case NOT:
    {
      node_compile(node->kids[0]);

      /*  */
      char *code_name = get_op_name(generic(node->op));
      if(code_name == NULL)
      {
        printf("op name not exist, op code %d\n", node->op);
        exit(1);
      }
      /*  */
      int code = get_op_code_by_name(code_name);
      /*  */
      push_command(code);
    }
    break;
    case BCOM:
    case CVC:
    case CVUC:
    case CVF:
    case CVI:
    case CVB:
    case CVUI:
    case NEG:
    {
      node_compile(node->kids[0]);

      /*  */
      char *code_name = get_op_name(generic(node->op));
      if(code_name == NULL)
      {
        printf("op name not exist, op code %d\n", node->op);
        exit(1);
      }
      /*  */
      int code = get_type_related_op_code_by_name(node->kids[0]->type, code_name);
      /*  */
      push_command(code);
    }
    break;
    case INCR:
    case DECR:
    {
      Symbol p = node->kids[0]->syms[0];

      /* address used by binaray operation */
      node_compile(node->kids[0]);

      /*  */
      if(p->tab == Global_symtab)
      {
        vm_load_global(node->type, NULL, NULL);
      }
      else
      {
        vm_load_function_call_stack_val(node->type, NULL, NULL);
      }

      /*  */
      char *code_name = get_op_name(generic(node->op));
      if(code_name == NULL)
      {
        printf("op name not exist, op code %d\n", node->op);
        exit(1);
      }
      /*  */
      int code = get_type_related_op_code_by_name(node->type, code_name);
      /*  */
      push_command(code);

      /* address use by assignment */
      node_compile(node->kids[0]);

      /*  */
      if(p->tab == Global_symtab)
      {
        vm_assign_global(node->type, NULL, NULL);
      }
      else
      {
        vm_assign_function_call_stack_val(node->type, NULL, NULL);
      }
    }
    break;
  }

  /* 代码块标记 */
  switch (generic(node->op))
  {
    case HEADER: /* 表示过程以及函数定义的开始 */  
    {
       /* 符号表压栈 */
      push_symtab_stack(node->symtab);
      
      /* record function */
      push_function(node->symtab, code_byte_index);
    }
    break;
    case TAIL: /* 表示过程以及函数定义的结束 */
    {
      Symtab ptab = top_symtab_stack();

      /* function call, return origin position */
      if(ptab != Global_symtab)
      {
        /* return val */
        vm_set_return_val(ptab);

        /* get return position */
        vm_get_return_index();
       
        /* pop function stack */
        vm_pop_function_call_stack(ptab);

        /*  */
        pop_symtab_stack();

        /* jump to return position */
        int jump_code = get_op_code_by_name("JUMP");
        push_command(jump_code);
      }
      else
      {
        int exit_code = get_op_code_by_name("EXIT");
        push_command(exit_code);
      }
    }
    break;
    case BLOCKBEG:
    case BLOCKEND:
        break;
  }
}