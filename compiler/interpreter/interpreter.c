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
  printf("\n********************\nbegin compiler to code bytes\n********************\n");

  /*  */
  for(g_cp = dag->link; g_cp != NULL; g_cp = g_cp->link)
  {
    node_process((Node)(g_cp->x));

    if(g_cp == NULL)
    {
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
    
  }
  break;
  case JUMP:
  {
    Symbol p = node->syms[0];

    jump_to_label(g_cp, p);
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
    case TYPE_UINTEGER:
    {
      if((node->kids[0]->val.ui == 0 && node->u.cond.true_or_false == false) ||
      (node->kids[0]->val.ui != 0 && node->u.cond.true_or_false == true))
      {
        jump_to_label(g_cp, node->u.cond.label);
      }
    }
    break;
    case TYPE_CHAR:
    case TYPE_UCHAR:
    {
      parse_error("COND expression can not be char", "");
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
      parse_error("COND expression can not be real", "");
    }
    break;
    case TYPE_STRING:
    {
      parse_error("COND expression can not be string", "");
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
    /*  */
    node_process(node->kids[0]);

    /* 有参数 */
    switch (node->u.sys_id)
    {
      case pREADLN:
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

      /* 本地变量压栈 */
      push_function_call_stack(node->symtab);

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

      int startIndex = node->syms[0]->type->first->v.i;

      if(index < startIndex || index > startIndex + node->syms[0]->type->num_ele - 1)
      {
        parse_error("array index out of bound", "");
        return;
      }

      p = node->syms[0]->type->last;
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
        p = clone_symbol(node->syms[0]->type->last);
        p->offset = (index - startIndex) * get_symbol_align_size(p);
        /*  */
        snprintf(p->name, NAME_LEN, "%s_%d", node->syms[0]->name, index);

        p->next = node->syms[0]->type->last;
        node->syms[0]->type->last = p;
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

      /*  */
      if(p->defn == DEF_ENUM_ELEMENT)
      {
        node->val = p->v;
      }
      else
      {
        if(q)
        {
          /* record or array */
          push_symtab_stack(q->tab);
        }
        else
        {
          push_symtab_stack(p->tab);
        }

        /* 全局变量 */
        if(top_symtab_stack()->level == 0)
        {
          load_global(node, p, q);
        }
        else
        {
          /* 参数局部类型，从栈取值 */
          if((q != NULL && (q->defn == DEF_VALPARA || q->defn == DEF_VARPARA)) || 
            p->defn == DEF_VALPARA || p->defn == DEF_VARPARA)
          {
            load_function_call_stack_val(node, p, q);
          }
          else {
            /* 普通局部变量，从栈取值 */
            load_function_call_stack_val(node, p, q);
          }
        }

        /*  */
        pop_symtab_stack();
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

      /*  */
      if(q)
      {
        /* record or array */
        push_symtab_stack(q->tab);
      }
      else
      {
        push_symtab_stack(p->tab);
      }

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
          assign_function_call_stack_val(node->kids[1], p, q);
        }
      }

      /*  */
      pop_symtab_stack();
    }
    break;
  }

  /*  */
  switch (generic(node->op))
  {
    /*  */
    case CVF:
    {
      node_process(node->kids[0]);

      switch(node->kids[0]->type->type_id)
      {
        case TYPE_INTEGER:
        {
          node->val.f = (float)node->kids[0]->val.i;
        }
        break;
        case TYPE_UINTEGER:
        {
          node->val.f = (float)node->kids[0]->val.ui;
        }
        break;
        case TYPE_REAL:
        {
          
        }
        case TYPE_BOOLEAN:
        {
          node->val.f = (float)node->kids[0]->val.b;
        }
        break;
        default:
        {
          printf("CVF convert type error\n");
        }
      }
    }
    break;
    case CVI:
    {
      node_process(node->kids[0]);

      switch(node->kids[0]->type->type_id)
      {
        case TYPE_INTEGER:
        {
          
        }
        break;
        case TYPE_REAL:
        {
          node->val.i = (int)node->kids[0]->val.f;
        }
        break;
        case TYPE_CHAR:
        {
          node->val.i = (int)node->kids[0]->val.c;
        }
        break;
        case TYPE_UCHAR:
        {
          node->val.i = (int)node->kids[0]->val.uc;
        }
        break;
        case TYPE_BOOLEAN:
        {

        }
        break;
        default:
        {
          printf("CVI convert type error\n");
        }
      }
    }
    break;
    case CVB:
    {
      node_process(node->kids[0]);
      
      switch(node->kids[0]->type->type_id)
      {
        case TYPE_INTEGER:
        {
          node->val.b = node->kids[0]->val.i == 0 ? false : true;
        }
        break;
        case TYPE_UINTEGER:
        {
          node->val.b = node->kids[0]->val.ui == 0 ? false : true;
        }
        break;
        case TYPE_REAL:
        {
          node->val.b = node->kids[0]->val.f == 0 ? false : true;
        }
        break;
        case TYPE_CHAR:
        {
          node->val.b = (unsigned char)(node->kids[0]->val.c) == 0 ? false : true;
        }
        break;
        case TYPE_UCHAR:
        {
          node->val.b = (unsigned char)(node->kids[0]->val.uc) == 0 ? false : true;
        }
        case TYPE_BOOLEAN:
        {

        }
        break;
        default:
        {
          printf("CVB convert type error\n");
        }
      }
    }
    break;
    case CVUI:
    {
      node_process(node->kids[0]);

      switch(node->kids[0]->type->type_id)
      {
        case TYPE_INTEGER:
        {
          node->val.ui = (unsigned int)node->kids[0]->val.i;
        }
        break;
        case TYPE_UINTEGER:
        {
          
        }
        break;
        case TYPE_CHAR:
        {
          node->val.ui = (unsigned int)node->kids[0]->val.c;
        }
        break;
        case TYPE_UCHAR:
        {
          node->val.ui = (unsigned int)node->kids[0]->val.uc;
        }
        break;
        default:
        {
          printf("CVUI convert type error\n");
        }
      }
    }
    break;
    case CVC:
    {
      node_process(node->kids[0]);

      switch(node->kids[0]->type->type_id)
      {
        case TYPE_INTEGER:
        {
          node->val.c = (char)(node->kids[0]->val.i);
        }
        break;
        case TYPE_UINTEGER:
        {
          node->val.c = (char)(node->kids[0]->val.ui);
        }
        break;
        case TYPE_CHAR:
        {
          
        }
        break;
        case TYPE_UCHAR:
        {
          node->val.c = (char)node->kids[0]->val.uc;
        }
        break;
        default:
        {
          printf("CVC convert type error\n");
        }
      }
    }
    break;
    case CVUC:
    {
      node_process(node->kids[0]);

      switch(node->kids[0]->type->type_id)
      {
        case TYPE_INTEGER:
        {
          node->val.uc = (unsigned char)(node->kids[0]->val.i);
        }
        break;
        case TYPE_UINTEGER:
        {
          node->val.uc = (unsigned char)(node->kids[0]->val.ui);
        }
        break;
        case TYPE_CHAR:
        {
          node->val.uc = (unsigned char)node->kids[0]->val.c;

        }
        break;
        case TYPE_UCHAR:
        {

        }
        break;
        default:
        {
          printf("CVUC convert type error\n");
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
    }
    break;
  }

  /* 一元数学元算 */
  switch (generic(node->op))
  {
    case BCOM:
    case NOT:
    case NEG:   
    {
      node_process(node->kids[0]);

      /*  */
      arithmetical_operate(node);
    }
    break;
    case INCR:
    case DECR:
    {
      Symbol p;

      /*  */
      node_process(node->kids[0]);

      /*  */
      Node addr = node->kids[0];
      p = addr->syms[0];

      /*  */
      push_symtab_stack(p->tab);

      /* add operation */
      if(top_symtab_stack()->level == 0)
      {
        load_global(addr, p, NULL);
      }
      else
      {
        /* 参数局部类型，从栈取值 */
        if(p->defn == DEF_VALPARA || p->defn == DEF_VARPARA)
        {
          load_function_call_stack_val(addr, p, NULL);
        }
        else {
          /* 普通局部变量，从栈取值 */
          load_function_call_stack_val(addr, p, NULL);
        }
      }

      /*  */
      arithmetical_operate(node);

      /* assign val */
      if(top_symtab_stack()->level == 0)
      {
        assign_global(node, p, NULL);
      }
      else
      {
        assign_function_call_stack_val(node, p, NULL);
      }

      /*  */
      pop_symtab_stack();
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
      Symtab ptab = pop_symtab_stack();

      /*  */
      g_cp = pop_return_position_stack();

      /*  */
      pop_function_call_stack(ptab);
    }
    break;
    case BLOCKBEG:
    case BLOCKEND:
        break;
  }
}