#include  <stdio.h>
#include  "../common.h"
#include  "../ast/symtab.h"
#include  "../parser/error.h"
#include  "../parser/rule.h"

Symtab ptab;
Symbol p;
Symbol q;

List cp;

static int label_node_index = 0;
static List label_node_queue[256];

void interpret(List dag)
{
    ptab = Global_symtab;
    Node n;
    
    /*  */
    for(cp = dag->link; cp != NULL; cp = cp->link)
    {
      n = (Node)(cp->x);
      if(generic(n->op) == LABEL)
      {
        label_node_queue[label_node_index++] = cp;
      }
    }

    /*  */
    for(cp = dag->link; cp != NULL; cp = cp->link)
    {
      node_process((Node)(cp->x));
      if(cp == NULL)
      {
        printf("*********************ERROR*********************");
        break;
      }
    }
}

void jump_to_label(Symbol label)
{
  /*  */
  int i = label_node_index - 1;
  while(i >= 0)
  {
    Node label_node = (Node)(label_node_queue[i]->x);
    if(!strcmp(label_node->syms[0]->name, label->name))
    {
      cp = label_node_queue[i];
      return;
    }

    i--;
  }

  if(cp == NULL)
  {
    printf("label is not exist %s", label->name);
  }
}

void node_process(Node node)
{
  if(node->compute == true)
  {
    printf("get node computed op: %s, result: %d\n", node->op_name, node->val.i);
    // return;
  }

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
    jump_to_label(node->syms[0]);
  }
  break;
  case COND:
  {
    node_process(node->kids[0]);

    if((node->kids[0]->val.i == 0 && node->u.cond.true_or_false == false) || 
      (node->kids[0]->val.i != 0 && node->u.cond.true_or_false == true))
    {
      jump_to_label(node->u.cond.label);
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
          /* 参数对应的符号 */
          p = node->kids[0]->syms[0];

          /*  */
          printf("result: %d\n", p->v.i);
        }
        break;
      }
    }
  }
  break;
  case CALL:
  {
    /*  */
  }
  break;
  }

  switch (generic(node->op))
  {
  case RIGHT:
  {
    printf("\nRIGHT, ");

    /* 计算表达式AST节点对应的值 */
    if(node->kids[0]->kids[0] != NULL || node->kids[0]->kids[1] != NULL)
    {
      node_process(node->kids[0]);
    }

    /* 参数对应的符号 */
    p = node->syms[0];

    /* 参数赋值 */
    p->v.i = node->kids[0]->val.i;

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

    /* 参数对应的符号 */
    p = node->syms[0];

    /* 参数赋值 */
    p->v.i = node->kids[0]->val.i;

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
      /**/
      node->syms[0] = node->syms[1];  
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
          node->syms[0] = p;
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
        node_process(node->kids[0]);
        node->syms[0] = node->kids[0]->syms[0];
        node->val.i = node->kids[0]->syms[0]->v.i;
      }
      else
      {
        node->val.i = node->syms[0]->v.i;
      }
    }
    break;
    case ASGN:
    {
      /*  */
      if(node->kids[0])
      {
        node_process(node->kids[0]);
      }

      /* 计算表达式AST节点对应的值 */
      if(node->kids[1])
      {
        node_process(node->kids[1]);
      }
      
      /* 对应的符号 */
      p = node->kids[0]->syms[0];

      /* 变量赋值 */
      p->v.i = node->kids[1]->val.i;
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

      /*  */
      node->compute = true;
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

      /*  */
      node->compute = true;
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

      /*  */
      node->compute = true;
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

      /*  */
      node->compute = true;
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

      /*  */
      node->compute = true;
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

      /*  */
      node->compute = true;
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

      /*  */
      node->compute = true;
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

      /*  */
      node->compute = true;
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

      /*  */
      node->compute = true;
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

      /*  */
      node->compute = true;
    }
    break;
  }

  switch (generic(node->op))
  {
    case HEADER: /* 表示过程以及函数定义的开始 */  
    case TAIL: /* 表示过程以及函数定义的结束 */
      break;
    case BLOCKBEG:
    case BLOCKEND:
        break;
  }
}