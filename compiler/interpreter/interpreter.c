#include  <stdio.h>
#include  "../common.h"
#include  "../ast/symtab.h"
#include  "../parser/error.h"
#include  "../parser/rule.h"

Symbol p;
Symbol q;

List cp;
List routine_forest;

static int traverse_deep;

/*  */
void interpret(List _routine_forest, List dag)
{
  routine_forest = _routine_forest;

  push_symtab_stack(Global_symtab);

  Node n;

  LabelQueue label_queue;

  /*  */
  NEW(label_queue, PERM);
  label_queue->label_node_index = 0;

  for(cp = dag->link; cp != NULL; cp = cp->link)
  {
    n = (Node)(cp->x);
    /*  */
    cp->label_queue = label_queue;
    /*  */
    if(generic(n->op) == LABEL)
    {
      label_queue->label_node_queue[label_queue->label_node_index++] = cp;
    }
  }

  List cpTmp;
  for(cp = routine_forest->link; cp != NULL; cp = cp->link)
  {
    NEW(label_queue, PERM);
    label_queue->label_node_index = 0;
    /*  */
    for(cpTmp = (List)(cp->x); cpTmp != NULL; cpTmp = cpTmp->link)
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
  for(cp = dag->link; cp != NULL; cp = cp->link)
  {
    traverse_deep = 0;

    node_process((Node)(cp->x));

    if(cp == NULL)
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
  for(cpTmp1 = routine_forest->link; cpTmp1 != NULL; cpTmp1 = cpTmp1->link)
  {
    for(cpTmp2 = (List)(cpTmp1->x); cpTmp2 != NULL; cpTmp2 = cpTmp2->link)
    {
      n = (Node)(cpTmp2->x);
      /*  */
      if(n->symtab == ptab)
      {
        printf("found routine %s\n", n->symtab->name);

        return cpTmp2;
      }
    }
  }

  if(cpTmp2 == NULL)
  {
    printf("routine not exist %s\n", ptab->name);

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
      cp = label_queue->label_node_queue[i];
      return;
    }

    i--;
  }

  if(i < 0)
  {
    printf("label is not exist %s\n", label->name);
    cp = NULL;
  }
}

void node_process(Node node)
{
  traverse_deep++;

  switch (generic(node->op))
  {
    case INCR:
    {
      /* */
      node_process(node->kids[0]);
      /* */
      node->kids[0]->syms[0]->v.i++;
    }
    break;
    case DECR:
    {
      /*  */
      node_process(node->kids[0]);
      /*  */
      node->kids[0]->syms[0]->v.i--;
    }
    break;
  }

  switch (generic(node->op))
  {
  case LABEL:
  {
    
  }
  break;
  case JUMP:
  {
    jump_to_label(cp, node->syms[0]);
  }
  break;
  case COND:
  {
    node_process(node->kids[0]);

    if((node->kids[0]->val.i == 0 && node->u.cond.true_or_false == false) || 
      (node->kids[0]->val.i != 0 && node->u.cond.true_or_false == true))
    {
      jump_to_label(cp, node->u.cond.label);
    }
  }
  break;
  }

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
    List originCp = cp;
    cp = find_routine_forest(node->symtab);

    if(cp)
    {
      /*  */
      push_symtab_stack(node->symtab);

      /*  */
      push_return_position_stack(originCp);

      /*  */
      push_return_val_stack(find_symbol(node->symtab, node->symtab->name));

      /*  */
      push_local_stack(node->symtab);

      /*  */
      push_args_stack(node->symtab);

      if (node->kids[0] != NULL)
      {
        node_process(node->kids[0]);
      }
      
      /*  */
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
            assign_arg(sym, tmpNode->val.i);
            break;
          }
        }
      }
    }
  }
  break;
  case RIGHT:
  {
    printf("RIGHT\n");

    /* 计算表达式AST节点对应的值 */
    if(node->kids[0] != NULL)
    {
      node_process(node->kids[0]);
    }

    /* 参数赋值 */
    node->val.i = node->kids[0]->val.i;

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
    node->val.i = node->kids[0]->val.i;

    /* 计算其余参数的值 */
    if(node->kids[1] != NULL)
    {
      node_process(node->kids[1]);
    }
  }
  break;
  }

  switch (generic(node->op))
  {
    case FIELD:
    {
      
    }
    break;
    case ARRAY:
    {
      char ele_name[NAME_LEN];
      /*  */
      for(p = node->syms[0]->type_link->first; p != NULL; p = p->next)
      {
        node_process(node->kids[0]);

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
    }
    break;
    case ADDRG:
    {

    }
    break;
    case LOAD:
    {
      if(node->kids[0])
      {
        /* array or field */
        node_process(node->kids[0]);
        p = node->kids[0]->syms[1];
      }
      else
      {
        p = node->syms[0];
      }

      if(top_symtab_stack()->level == 0)
      {
        /*  */
        node->val.i = p->v.i;
      }
      else
      {
        /*  */
        if(p->defn == DEF_VALPARA || p->defn == DEF_VARPARA)
        {
          node->val.i = load_arg(p);
        }
        else {
          node->val.i = load_local(p);
        }
      }
    }
    break;
    case ASGN:
    {
      /*  */
      if(generic(node->kids[0]->op) == ARRAY || generic(node->kids[0]->op) == FIELD)
      {
        /* array or filed */
        node_process(node->kids[0]);
        p = node->kids[0]->syms[1];
      }
      else
      {
        p = node->kids[0]->syms[0];
      }
      /* 计算表达式AST节点对应的值 */
      if(node->kids[1])
      {
        node_process(node->kids[1]);
      }

      if(top_symtab_stack()->level == 0)
      {
        if(generic(node->kids[1]->op) == CALL)
        {
          /*  */
          q = find_symbol(node->kids[1]->symtab, node->kids[1]->symtab->name);
          /*  */
          p->v.i = load_return_val(q);
          /*  */
          pop_return_val_stack();
        }
        else
        {
          /* 变量赋值 */
          p->v.i = node->kids[1]->val.i;
        }
      }
      else
      {
        printf("*********************************assign %s\n", p->name);
        int expression_val;
        if(generic(node->kids[1]->op) == CALL)
        {
          /*  */
          q = find_symbol(node->kids[1]->symtab, node->kids[1]->symtab->name);
          /*  */
          expression_val = load_return_val(q);
          /*  */
          pop_return_val_stack();
        }
        else
        {
          /* 变量赋值 */
          expression_val = node->kids[1]->val.i;
        }

        /*  */
        if(p->defn == DEF_VALPARA || p->defn == DEF_VARPARA)
        {
          assign_arg(p, expression_val);
        }
        else if(p->defn == DEF_FUNCT) {
          assign_return_val(p, expression_val);
        }
        else if(p->defn == DEF_PROC)
        {

        }
        else
        {
          assign_local(p, expression_val);
        }
      }
    }
    break;
    case CNST:
    {
      node->val.i = node->syms[0]->v.i;
    }
    break;
  }

  switch (generic(node->op))
  {
    case ADD:
    {
      /* 计算左表达式AST节点对应的值 */
      if(node->kids[0])
      {
        node_process(node->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(node->kids[1])
      {
        node_process(node->kids[1]);
      }

      node->val.i = node->kids[0]->val.i + node->kids[1]->val.i;
    }
    break;
    case SUB:
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

      node->val.i = node->kids[0]->val.i - node->kids[1]->val.i;
    }
    break;
    case MUL:
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

      node->val.i = node->kids[0]->val.i * node->kids[1]->val.i;
    }
    break;
    case DIV:
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

      node->val.i = node->kids[0]->val.i / node->kids[1]->val.i;
    }
    break;
    case EQ:
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

      node->val.i = node->kids[0]->val.i == node->kids[1]->val.i;
    }
    break;
    case NE:
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

      node->val.i = node->kids[0]->val.i != node->kids[1]->val.i;
    }
    break;
    case GE:
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

      node->val.i = node->kids[0]->val.i >= node->kids[1]->val.i;
    }
    break;
    case GT:
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

      node->val.i = node->kids[0]->val.i > node->kids[1]->val.i;
    }
    break;
    case LE:
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

      node->val.i = node->kids[0]->val.i <= node->kids[1]->val.i;
    }
    break;
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

      node->val.i = node->kids[0]->val.i < node->kids[1]->val.i;
    }
    break;
  }

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
      cp = pop_return_position_stack();

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