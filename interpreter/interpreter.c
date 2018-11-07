#include  <stdio.h>
#include  "../common.h"
#include  "../ast/symtab.h"
#include  "../parser/error.h"
#include  "../parser/rule.h"

List g_cp;
List g_routine_forest;

#define CODE_MAX_NUM 512
static int code_byte_index = 0;
unsigned char code_byte_sequence[CODE_MAX_NUM];
static int push_data(Type t, Value v)
{
  /*  */
  assign_with_byte_unit(t, code_byte_sequence[code_byte_index], v);

  /*  */
  code_byte_index += get_type_align_size(t);

  /*  */
  if(code_byte_index >= CODE_MAX_NUM)
  {
    // printf("code_byte_sequence overflow\n");
    return 0;
  }

  return 1;
}

static int push_code(int code)
{
  /*  */
  if(code_byte_index >= CODE_MAX_NUM)
  {
    // printf("code_byte_sequence overflow\n");
    return 0;
  }

  /*  */
  code_byte_sequence[code_byte_index++] = code;

  return 1;
}


typedef struct _label_detail_ *LabelDetail;
struct _label_detail_
{
  int code_index;
  char name[NAME_LEN];
};
static int label_sequence_index = 0;
static LabelDetail label_sequence[CODE_MAX_NUM];
static void push_label(char *name, int code_index)
{
  NEW0(label_sequence[label_sequence_index], PERM);

  /*  */
  label_sequence[label_sequence_index]->code_index = code_index;
  strncpy(label_sequence[label_sequence_index]->name, name, NAME_LEN);
}

static int get_label_code_index(char *name)
{
  int i = 0;
  while(i < CODE_MAX_NUM && label_sequence[i] != NULL)
  {
    if(!strcmp(label_sequence[i]->name, name))
    {
      return label_sequence[i]->code_index;
    }
    return -1;
  }
}

/*  */
void interpret(List routine_forest, List dag)
{
  g_routine_forest = routine_forest;

  Node n;

  LabelQueue label_queue;

  /*  */
  push_symtab_stack(Global_symtab);

  /*  */
  NEW0(label_queue, PERM);
  label_queue->label_node_index = 0;

  for(g_cp = dag->link; g_cp != NULL; g_cp = g_cp->link)
  {
    n = (Node)(g_cp->x);
    /*  */
    g_cp->label_queue = label_queue;
    /*  */
    if(generic(n->op) == LABEL)
    {
      label_queue->label_node_queue[label_queue->label_node_index++] = g_cp;
    }
  }

  List cpTmp;
  for(g_cp = g_routine_forest->link; g_cp != NULL; g_cp = g_cp->link)
  {
    NEW0(label_queue, PERM);
    label_queue->label_node_index = 0;
    /*  */
    for(cpTmp = (List)(g_cp->x); cpTmp != NULL; cpTmp = cpTmp->link)
    {
      n = (Node)(cpTmp->x);
      /*  */
      cpTmp->label_queue = label_queue;
      /*  */
      if(generic(n->op) == LABEL)
      {
        label_queue->label_node_queue[label_queue->label_node_index++] = cpTmp;
      }
    }
  }


  /*  */
  for(g_cp = dag->link; g_cp != NULL; g_cp = g_cp->link)
  {
    node_process((Node)(g_cp->x));

    if(g_cp == NULL)
    {
      break;
    }
  }

  /*  */
  // int i = 0;
  // while(i < CODE_MAX_NUM && code_byte_sequence[i] != NULL)
  // {
  //   printf("%x ", code_byte_sequence[i]);
  //   i++;
  // }
}

List find_routine_forest(Symtab ptab)
{
  List cpTmp1, cpTmp2;
  Node n;
  for(cpTmp1 = g_routine_forest->link; cpTmp1 != NULL; cpTmp1 = cpTmp1->link)
  {
    for(cpTmp2 = (List)(cpTmp1->x); cpTmp2 != NULL; cpTmp2 = cpTmp2->link)
    {
      n = (Node)(cpTmp2->x);
      /*  */
      if(n->symtab == ptab && generic(n->op) == HEADER)
      {
        return cpTmp2;
      }
    }
  }

  if(cpTmp2 == NULL)
  {
    parse_error("routine not exist", ptab->name);
    return NULL;
  }
}

void jump_to_label(List l, Symbol label)
{
  LabelQueue label_queue = l->label_queue;
  /*  */
  int i = label_queue->label_node_index - 1;
  while(i >= 0)
  {
    Node label_node = (Node)(label_queue->label_node_queue[i]->x);
    if(!strcmp(label_node->syms[0]->name, label->name))
    {
      g_cp = label_queue->label_node_queue[i];
      return;
    }

    i--;
  }

  if(i < 0)
  {
    parse_error("label is not exist", label->name);
    g_cp = NULL;
  }
}

void node_process(Node node)
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

    jump_to_label(g_cp, p);

    /*  */
    int stack_push_code = get_op_code("PUSH");
    push_code(stack_push_code);
    /*  */
    value label_index;
    label_index.i = get_label_code_index(p->name);
    push_data(find_type_by_id(TYPE_INTEGER), &label_index);
    /*  */
    int jump_code = get_op_code("JUMP");
    push_code(jump_code);
  }
  break;
  case COND:
  {
    node_process(node->kids[0]);

    switch(node->kids[0]->type->type_id)
    {
    case TYPE_INTEGER:
    {
      /*  */
      int stack_push_code = get_op_code("PUSH");
      push_code(stack_push_code);
      /*  */
      value cond;

      if((node->kids[0]->val.i == 0 && node->u.cond.true_or_false == false) ||
      (node->kids[0]->val.i != 0 && node->u.cond.true_or_false == true))
      {
        jump_to_label(g_cp, node->u.cond.label);

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
    case TYPE_BOOLEAN:
    {
      /*  */
      int stack_push_code = get_op_code("PUSH");
      push_code(stack_push_code);
      /*  */
      value cond;

      if((node->kids[0]->val.b == false && node->u.cond.true_or_false == false) ||
      (node->kids[0]->val.b == true && node->u.cond.true_or_false == true))
      {
        jump_to_label(g_cp, node->u.cond.label);

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

    /*  */
    value label_index;
    label_index.i = get_label_code_index(node->u.cond.label->name);
    push_data(find_type_by_id(TYPE_INTEGER), &label_index);
    /*  */
    int stack_push_code = get_op_code("PUSH");
    push_code(stack_push_code);
    /*  */
    int jump_code = get_op_code("JUMP");
    push_code(jump_code);
  }
  break;
  }

  /* 函数调用相关 */
  switch (generic(node->op))
  {
  case SYS:
  {
    /*  */
    node_process(node->kids[0]);

    /* 有参数 */
    switch (node->u.sys_id)
    {
      case pREAD:
      {
        read(node);
      }
      break;
      case pWRITELN:
      {
        write(node);
      }
      break;
    }
  }
  break;
  case CALL:
  {
    /* 记录返回地址 */
    push_return_position_stack(g_cp);

    /* 对应函数的DAG节点森林 */
    g_cp = find_routine_forest(node->symtab);

    if(g_cp)
    {
      /* 实参 */
      if (node->kids[0] != NULL)
      {
        node_process(node->kids[0]);
      }
      
      /* 符号表压栈 */
      push_symtab_stack(node->symtab);

      /* 返回值压栈 */
      push_return_val_stack(find_symbol(node->symtab, node->symtab->name));

      /* 本地变量压栈 */
      push_local_stack(node->symtab);

      /* 实参压栈 */
      push_args_stack(node->symtab);

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
            assign_arg(tmpNode, p, NULL);
            break;
          }
        }
      }
    }
    else
    {
      pop_return_position_stack();
    }
  }
  break;
  case RIGHT:
  {
    /* 计算表达式AST节点对应的值 */
    if(node->kids[0] != NULL)
    {
      node_process(node->kids[0]);
    }

    node->val = node->kids[0]->val;

    /* 计算其余参数的值 */
    if(node->kids[1] != NULL)
    {
      node_process(node->kids[1]);
    }
  }
  break;
  case ARG:
  {
    /* 计算参数的值 */
    if(node->kids[0] != NULL)
    {
      node_process(node->kids[0]);
    }

    /* 参数赋值 */
    node->val = node->kids[0]->val;

    /* 计算其余参数的值 */
    if(node->kids[1] != NULL)
    {
      node_process(node->kids[1]);
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
      int code = get_op_code("PUSH");
      /*  */
      push_code(code);
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
      node_process(node->kids[0]);

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
        node_process(node->kids[0]);
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
        }
        /* 参数局部类型，从栈取值 */
        else if((q != NULL && (q->defn == DEF_VALPARA || q->defn == DEF_VARPARA)) || 
          p->defn == DEF_VALPARA || p->defn == DEF_VARPARA)
        {
          load_arg(node, p, q);
        }
        else {
          /* 普通局部变量，从栈取值 */
          load_local(node, p, q);
        }
      }

      /*  */
      int code = get_op_code("PUSH");
      /*  */
      push_code(code);
      /*  */
      push_data(p->type, &(node->val));
    }
    break;
    case ASGN:
    {
      Symbol p;
      Symbol q = NULL;

      if(node->kids[0])
      {
        /* 地址节点 */
        node_process(node->kids[0]);
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
      node_process(node->kids[1]);

      if(top_symtab_stack()->level == 0)
      {
        /*  */
        assign_global(node->kids[1], p, q);
      }
      else
      {
        if(p->defn == DEF_VALPARA || p->defn == DEF_VARPARA)
        {
          /* 参数赋值 */
          assign_arg(node->kids[1], p, q);
        }
        else if(p->defn == DEF_FUNCT) {
          /* 函数返回值赋值 */
          assign_return_val(node->kids[1], p);
        }
        else if(p->defn == DEF_PROC)
        {
          parse_error("proc can not have return val", p->name);
          g_cp = NULL;
        }
        else
        {
          /* 局部变量赋值 */
          assign_local(node->kids[1], p, q);
        }
      }
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
        node_process(node->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(node->kids[1] != NULL)
      {
        node_process(node->kids[1]);
      }

      arithmetical_operate(node);

      /*  */
      char *code_name = get_op_name(generic(node->op));
      /*  */
      int code = get_op_code(code_name);
      /*  */
      push_code(code);
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
      node_process(node->kids[0]);

      arithmetical_operate(node);

      /*  */
      char *code_name = get_op_name(generic(node->op));
      /*  */
      int code = get_op_code(code_name);
      /*  */
      push_code(code);
    }
    case INCR:
    case DECR:
    {
      Symbol p;

      /*  */
      node_process(node->kids[0]);

      /*  */
      Node addr = node->kids[0];
      p = addr->syms[0];
      if(top_symtab_stack()->level == 0)
      {
        load_global(addr, p, NULL);
      }
      else
      {
        /* 参数局部类型，从栈取值 */
        if(p->defn == DEF_VALPARA || p->defn == DEF_VARPARA)
        {
          load_arg(addr, p, NULL);
        }
        else {
          /* 普通局部变量，从栈取值 */
          load_local(addr, p, NULL);
        }
      }

      /*  */
      arithmetical_operate(node);

      /*  */
      if(top_symtab_stack()->level == 0)
      {
        assign_global(node, p, NULL);
      }
      else
      {
        assign_local(node, p, NULL);
      }
    }
    break;
  }

  /* 代码块标记 */
  switch (generic(node->op))
  {
    case HEADER: /* 表示过程以及函数定义的开始 */  
    {
      
    }
    break;
    case TAIL: /* 表示过程以及函数定义的结束 */
    {
      /*  */
      Symbol sp = pop_symtab_stack();

      /*  */
      g_cp = pop_return_position_stack();

      /*  */
      pop_local_stack(sp);

      /*  */
      pop_args_stack(sp);
    }
    break;
    case BLOCKBEG:
    case BLOCKEND:
        break;
  }
}