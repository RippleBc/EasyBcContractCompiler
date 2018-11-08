#include  <stdio.h>
#include  "../common.h"
#include  "../ast/symtab.h"
#include  "../parser/error.h"
#include  "../parser/rule.h"

static void record_command_data_sequence(int size);

List g_cp;
List g_routine_forest;

/*  */
#define CODE_MAX_NUM 2048
int code_byte_index = 0;
unsigned char code_byte_sequence[CODE_MAX_NUM];
int push_data(Type t, Value v)
{
  /*  */
  assign_with_byte_unit(t->type_id, &code_byte_sequence[code_byte_index], v);

  /*  */
  int data_size = get_type_align_size(t);
  code_byte_index += data_size;

  /*  */
  record_command_data_sequence(data_size);

  /*  */
  if(code_byte_index >= CODE_MAX_NUM)
  {
    printf("code_byte_sequence overflow\n");
    return 0;
  }
  return 1;
}
int push_command(int code)
{
  /*  */
  if(code_byte_index >= CODE_MAX_NUM)
  {
    printf("code_byte_sequence overflow\n");
    return 0;
  }

  /*  */
  code_byte_sequence[code_byte_index++] = code;
  
  /*  */
  record_command_data_sequence(1);

  return 1;
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
  return -1;
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
  return -1;
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
static void push_jump_detail(char *name, int index)
{
  NEW0(jump_detail_sequence[jump_detail_index], PERM);

  strncpy(jump_detail_sequence[jump_detail_index]->name, name, NAME_LEN);
  jump_detail_sequence[jump_detail_index]->code_index = index;
  
  jump_detail_index++;
}

/*  */
static int command_data_trace = 0;
static void record_command_data_sequence(int size)
{
  command_data_trace += size;
}
static void recover_command_data_sequence()
{
  code_byte_index -= command_data_trace;
  command_data_trace = 0;
}
static void reset_command_data_sequence()
{
  command_data_trace = 0;
}

/*  */
void ast_compile(List routine_forest, List dag)
{
  printf("\n\n\n\n");

  g_routine_forest = routine_forest;

  /*  */
  push_symtab_stack(Global_symtab);

  /*  */
  for(g_cp = dag->link; g_cp != NULL; g_cp = g_cp->link)
  {
    node_compile((Node)(g_cp->x));

    if(g_cp == NULL)
    {
      break;
    }
  }

  /*  */
  push_symtab_stack(Global_symtab);
  /*  */
  int i = 0;
  int label_index;
  int jump_index;
  while(i < jump_detail_index)
  {
    if(jump_detail_sequence[i]->ptab == NULL)
    {
      /*  */
      char *label_name = jump_detail_sequence[i]->name;
      /*  */
      label_index = get_label_index(label_name);
    }
    else
    {
      Symtab ptab = jump_detail_sequence[i]->ptab;
      /*  */
      label_index = get_function_index(ptab);
    }

    jump_index = jump_detail_sequence[i]->code_index;

    /*  */
    value v_jump_code;
    v_jump_code.i = label_index;

    assign_with_byte_unit(TYPE_INTEGER, &code_byte_sequence[jump_index], &v_jump_code);

    i++;
  }

  /*  */
  i = 0;
  while(i < code_byte_index)
  {
    printf("%x ", code_byte_sequence[i]);
    i++;
  }
}

void node_compile(Node node)
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

    /*  */
    int command_push_code = get_op_code_by_name("PUSH");
    push_command(command_push_code);
    /* record the jump position */
    push_jump_detail(p->name, code_byte_index);
    /*  */
    value jump_position;
    jump_position.i = -1;
    push_data(find_type_by_id(TYPE_INTEGER), &jump_position);
    /*  */
    int jump_code = get_op_code_by_name("JUMP");
    push_command(jump_code);
  }
  break;
  case COND:
  {
    node_compile(node->kids[0]);

    switch(node->kids[0]->type->type_id)
    {
    case TYPE_INTEGER:
    case TYPE_BOOLEAN:
    {
      /*  */
      int command_push_code = get_op_code_by_name("PUSH");
      push_command(command_push_code);

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
      push_data(find_type_by_id(TYPE_BOOLEAN), &cond);
    }
    break;
    case TYPE_CHAR:
    {
      parse_error("COND expression can not be char", "");
    }
    break;
    case TYPE_REAL:
    {
      parse_error("COND expression can not be real", "");
    }
    break;
    case TYPE_STRING:
    {
      parse_error("COND expression can not be string", "");
    }
    break;
    }

    /* record the jump position */
    Symbol p = node->u.cond.label;
    push_jump_detail(p->name, code_byte_index);

    /*  */
    int command_push_code = get_op_code_by_name("PUSH");
    push_command(command_push_code);
    /*  */
    value jump_position;
    jump_position.i = -1;
    push_data(find_type_by_id(TYPE_INTEGER), &jump_position);

    /*  */
    int jump_code = get_op_code_by_name("JUMP");
    push_command(jump_code);
  }
  break;
  }

  /* 函数调用相关 */
  switch (generic(node->op))
  {
  case SYS:
  {
    /*  */
    node_compile(node->kids[0]);

    int command_function_code = 0;
    switch (node->u.sys_id)
    {
      case pREAD:
      {
        /*  */
        command_function_code = get_op_code_by_name("READ");
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
    push_function_call_stack(node->symtab);

    /* 记录返回地址 */
    set_return_index(code_byte_index);

    /* 实参 */
    if (node->kids[0] != NULL)
    {
      node_compile(node->kids[0]);
    }
    
    /* 符号表压栈 */
    push_symtab_stack(node->symtab);

    /* 实参赋值 */
    Symbol p;
    Node tmpNode;
    int i = 0, j = 0;;
    for(p = node->symtab->args; p != NULL; p = p->next)
    {
      i++;
      j = 0;
      for(tmpNode = node->kids[0]; tmpNode != NULL; tmpNode = tmpNode->kids[1])
      {
        j++;
        if(i == j)
        {
          assign_function_call_stack_val(tmpNode, p, NULL);
          break;
        }
      }
    }

    /*  */
    int command_push_code = get_op_code_by_name("PUSH");
    push_command(command_push_code);

    /*  */
    value function_index;
    function_index.i = -1;
    push_data(find_type_by_id(TYPE_INTEGER), &function_index);

    /*  */
    int jump_code = get_op_code_by_name("JUMP");
    push_command(jump_code);
  }
  break;
  case RIGHT:
  {
    /* 计算表达式AST节点对应的值 */
    if(node->kids[0] != NULL)
    {
      node_compile(node->kids[0]);
    }

    node->val = node->kids[0]->val;

    /* 计算其余参数的值 */
    if(node->kids[1] != NULL)
    {
      node_compile(node->kids[1]);
    }
  }
  break;
  case ARG:
  {
    /* 计算参数的值 */
    if(node->kids[0] != NULL)
    {
      node_compile(node->kids[0]);
    }

    /* 参数赋值 */
    node->val = node->kids[0]->val;

    /* 计算其余参数的值 */
    if(node->kids[1] != NULL)
    {
      node_compile(node->kids[1]);
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
      node->val = p->v;

      /*  */
      int code = get_op_code_by_name("PUSH");
      /*  */
      push_command(code);
      /*  */
      push_data(p->type, &(p->v));
    }
    break;
    case FIELD:
    {
      
    }
    break;
    case ARRAY:
    {
      Symbol p = NULL;
      char eleName[NAME_LEN];

      /* 数组下标 */
      node_compile(node->kids[0]);

      int index = node->kids[0]->val.i;

      int startIndex = node->syms[0]->type_link->first->v.i;

      if(index < startIndex || index > startIndex + node->syms[0]->type_link->num_ele - 1)
      {
        parse_error("array index out of bound", "");
        return;
      }

      p = node->syms[0]->type_link->last;
      while(p != NULL)
      {
        snprintf(eleName, NAME_LEN, "%s_%d", node->syms[0]->name, index);

        if(!strcmp(eleName, p->name))
        {
          break;
        }
        p = p->next;
      }

      if(p == NULL)
      {
        /*  */
        p = clone_symbol(node->syms[0]->type_link->last);
        p->offset = (index - startIndex) * get_symbol_align_size(p);

        /*  */
        snprintf(p->name, NAME_LEN, "%s_%d", node->syms[0]->name, index);

        p->next = node->syms[0]->type_link->last;
        node->syms[0]->type_link->last = p;
      }
      

      node->syms[1] = p;

      /*  */
      recover_command_data_sequence();
    }
    break;
    case ADDRG:
    {

    }
    break;
    case LOAD:
    {
      Symbol p;
      Symbol q = NULL;
      if(node->kids[0])
      {
        /* 地址节点 */
        node_compile(node->kids[0]);
        /* syms[0]表示数组或者记录，syms[1]表示数组成员或者属性，node->kids[0]表示ARRAY或者FIELD节点 */
        p = node->kids[0]->syms[1];
        q = node->kids[0]->syms[0];
      }
      else
      {
        p = node->syms[0];
      }

      /* 全局变量 */
      if(top_symtab_stack()->level == 0)
      {
        if(p->defn == DEF_ENUM_ELEMENT)
        {
          node->val = p->v;
          /*  */
          int code = get_op_code_by_name("PUSH");
          /*  */
          push_command(code);
          /*  */
          push_data(p->type, &(node->val));
        }
        else
        {
          load_global(node, p, q);
        }
      }
      else
      {
        if(p->defn == DEF_ENUM_ELEMENT)
        {
          node->val = p->v;
          /*  */
          int code = get_op_code_by_name("PUSH");
          /*  */
          push_command(code);
          /*  */
          push_data(p->type, &(node->val));
        }
        else {
          /* 普通局部变量，从栈取值 */
          load_function_call_stack_val(p, q);
        }
      }
    }
    break;
    case ASGN:
    {
      Symbol p;
      Symbol q = NULL;

      if(node->kids[0])
      {
        /* 地址节点 */
        node_compile(node->kids[0]);
      }

      if(generic(node->kids[0]->op) == ARRAY || generic(node->kids[0]->op) == FIELD)
      {
        /* syms[0]表示数组或者记录，syms[1]表示数组成员或者属性，node->kids[0]表示ARRAY或者FIELD节点 */
        p = node->kids[0]->syms[1];
        q = node->kids[0]->syms[0];
      }
      else
      {
        /* node->kids[0]表示ADDRG节点 */
        p = node->kids[0]->syms[0];
      }

      /* 表达式AST节点 */
      node_compile(node->kids[1]);

      if(top_symtab_stack()->level == 0)
      {
        /*  */
        assign_global(node->kids[1], p, q);
      }
      else
      {
        if(p->defn == DEF_PROC)
        {
          parse_error("proc can not have return val", p->name);
          g_cp = NULL;
        }
        else
        {
          /* 局部变量赋值 */
          assign_function_call_stack_val(p, q);
        }
      }

      reset_command_data_sequence();
    }
    break;
  }

  /* 二元数学运算 */
  switch (generic(node->op))
  {
    case BAND:
    case BOR:
    case BXOR:
    {

    }
    case LSH:
    case RSH:
    {

    }
    case ADD:
    case SUB:
    case MUL:
    case DIV:
    case MOD:
    {

    }
    case AND:
    case OR:
    {

    }
    case EQ:
    case NE:
    {

    }
    case GE:
    case GT:
    case LE:
    case LT:
    {
      /* 计算左表达式AST节点对应的值 */
      if(node->kids[0] != NULL)
      {
        node_compile(node->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(node->kids[1] != NULL)
      {
        node_compile(node->kids[1]);
      }

      /*  */
      char *code_name = get_op_name(generic(node->op));
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
    case BCOM:
    case NOT:
    case CVF:
    case CVI:
    case NEG:
    {
      node_compile(node->kids[0]);

      /*  */
      char *code_name = get_op_name(generic(node->op));
      /*  */
      int code = get_op_code_by_name(code_name);
      /*  */
      push_command(code);
    }
    case INCR:
    case DECR:
    {
      Symbol p;

      /*  */
      node_compile(node->kids[0]);

      /*  */
      Node addr = node->kids[0];
      p = addr->syms[0];
      if(top_symtab_stack()->level == 0)
      {
        load_global(p, NULL);
      }
      else
      {
        load_function_call_stack_val(p, NULL);
      }

      /*  */
      char *code_name = get_op_name(generic(node->op));
      /*  */
      int code = get_op_code_by_name(code_name);
      /*  */
      push_command(code);

      /*  */
      if(top_symtab_stack()->level == 0)
      {
        assign_global(node, p, NULL);
      }
      else
      {
        assign_function_call_stack_val(node, p, NULL);
      }
    }
    break;
  }

  /* 代码块标记 */
  switch (generic(node->op))
  {
    case HEADER: /* 表示过程以及函数定义的开始 */  
    {
      /*  */
      push_function(node->symtab, code_byte_index);
    }
    break;
    case TAIL: /* 表示过程以及函数定义的结束 */
    {
      /*  */
      get_return_index();

      /*  */
      Symtab ptab = pop_symtab_stack();
      /*  */
      pop_function_call_stack(ptab);

      /*  */
      int jump_code = get_op_code_by_name("JUMP");
      push_command(jump_code);

      
    }
    break;
    case BLOCKBEG:
    case BLOCKEND:
        break;
  }
}