#include  <stdio.h>
#include  "../common.h"
#include  "../ast/symtab.h"
#include  "../parser/error.h"
#include  "../parser/rule.h"

List g_cp;
List g_routine_forest;

/*  */
void interpret(List routine_forest, List dag)
{
  g_routine_forest = routine_forest;

  Node n;

  LabelQueue label_queue;

  /*  */
  push_symtab_stack(Global_symtab);

  /*  */
  NEW(label_queue, PERM);
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
    NEW(label_queue, PERM);
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
      printf("*********************ERROR*********************");
      break;
    }
  }
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
      if(n->symtab == ptab)
      {
        return cpTmp2;
      }
    }
  }

  if(cpTmp2 == NULL)
  {
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
    printf("label is not exist %s\n", label->name);
    g_cp = NULL;
  }
}

void node_process(Node node)
{

  printf("node process %s\n", get_op_name(generic(node->op)));

  /* 流程控制相关 */
  switch (generic(node->op))
  {
  case LABEL:
  {
    
  }
  break;
  case JUMP:
  {
    jump_to_label(g_cp, node->syms[0]);
  }
  break;
  case COND:
  {
    node_process(node->kids[0]);

    switch(node->kids[0]->type->type_id)
    {
    case TYPE_INTEGER:
    {
      if((node->kids[0]->val.i == 0 && node->u.cond.true_or_false == false) ||
      (node->kids[0]->val.i != 0 && node->u.cond.true_or_false == true))
      {
        jump_to_label(g_cp, node->u.cond.label);
      }
    }
    break;
    case TYPE_CHAR:
    {
      printf("COND expression can not be char\n");
    }
    break;
    case TYPE_BOOLEAN:
    {
      if((node->kids[0]->val.b == false && node->u.cond.true_or_false == false) ||
      (node->kids[0]->val.b == true && node->u.cond.true_or_false == true))
      {
        jump_to_label(g_cp, node->u.cond.label);
      }
    }
    break;
    case TYPE_REAL:
    {
      printf("COND expression can not be real\n");
    }
    break;
    case TYPE_STRING:
    {
      printf("COND expression can not be string\n");
    }
    break;
    }
  }
  break;
  }

  /* 函数调用相关 */
  switch (generic(node->op))
  {
  case SYS:
  {
    if (node->kids[0] == NULL)
    {
      /* 没有参数 */
    }
    else {
      /*  */
      node_process(node->kids[0]);

      /* 有参数 */
      switch (node->u.sys_id)
      {
        case pWRITELN:
        {
          /*  */

          printf("result: %d\n", node->kids[0]->val.i);
        }
        break;
      }
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
      Symbol sym;
      Node tmpNode;
      int i = 0, j = 0;;
      for(sym = node->symtab->args; sym != NULL; sym = sym->next)
      {
        i++;
        j = 0;
        for(tmpNode = node->kids[0]; tmpNode != NULL; tmpNode = tmpNode->kids[1])
        {
          j++;
          if(i == j)
          {
            assign_arg(tmpNode, sym, NULL);
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
      printf("CNST begin\n");
      node->val = node->syms[0]->v;
      printf("CNST end\n");
    }
    break;
    case FIELD:
    {
      
    }
    break;
    case ARRAY:
    {
      printf("ARRAY begin\n");
      Symbol p;

      char ele_name[NAME_LEN];

      /* 遍历数组元素 */
      for(p = node->syms[0]->type_link->first; p != NULL; p = p->next)
      {
        /* 数组下标 */
        node_process(node->kids[0]);

        /* 对应下标的元素 */
        snprintf(ele_name, sizeof(ele_name), "%d", node->kids[0]->val.i);
        if(is_symbol(p, ele_name))
        {
          node->syms[1] = p;
          break;
        }
      }
      if(p == NULL)
      {
        parse_error("array index out of bound", "");
        return;
      }
      printf("ARRAY end\n");
    }
    break;
    case ADDRG:
    {
      Symbol p = node->syms[0];
      if(top_symtab_stack()->level == 0)
      {
        load_global(node, p, NULL);
      }
      else
      {
        /* 参数局部类型，从栈取值 */
        if(p->defn == DEF_VALPARA || p->defn == DEF_VARPARA)
        {
          load_arg(node, p, NULL);
        }
        else {
          /* 普通局部变量，从栈取值 */
          load_local(node, p, NULL);
        }
      }
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
        load_global(node, p, q);
      }
      else
      {
        if(p->defn == DEF_ENUM_ELEMENT)
        {
          node->val = p->v;
        }
        /* 参数局部类型，从栈取值 */
        else if(p->defn == DEF_VALPARA || p->defn == DEF_VARPARA)
        {
          load_arg(node, p, q);
        }
        else {
          /* 普通局部变量，从栈取值 */
          load_local(node, p, q);
        }
      }
    }
    break;
    case ASGN:
    {
      printf("ASGN begin\n");
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
          printf("proc can not have return val\n", p->name);
          g_cp = NULL;
        }
        else
        {
          /* 局部变量赋值 */
          assign_local(node->kids[1], p, q);
        }
      }
      printf("ASGN end\n");
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
    case AND:
    case OR:
    case EQ:
    case NE:
    case GE:
    case GT:
    case LE:
    case LT:
    case MOD:
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
    }
    case INCR:
    case DECR:
    {
      Symbol p;

      /*  */
      node_process(node->kids[0]);

      arithmetical_operate(node);

      p = node->kids[0]->syms[0];

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
      pop_symtab_stack();

      /*  */
      g_cp = pop_return_position_stack();

      /*  */
      pop_local_stack();

      /*  */
      pop_args_stack();
    }
    break;
    case BLOCKBEG:
    case BLOCKEND:
        break;
  }
}