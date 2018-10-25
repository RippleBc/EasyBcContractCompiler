#include  <stdio.h>
#include  "../common.h"
#include  "../ast/symtab.h"
#include  "../parser/error.h"
#include  "../parser/rule.h"

Symtab ptab;
Symbol p;
Symbol q;

List cp;

static int label_tree_index = 0;
static List label_tree_queue[256];

void interpret(List dag)
{
    ptab = Global_symtab;
    Tree t;
    
    /*  */
    for(cp = dag->link; cp != NULL; cp = cp->link)
    {
      t = (Tree)(cp->x);
      if(generic(t->op) == LABEL)
      {
        label_tree_queue[label_tree_index++] = cp;
      }
    }

    /*  */
    for(cp = dag->link; cp != NULL; cp = cp->link)
    {
      node_process((Tree)(cp->x));
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
  int i = label_tree_index - 1;
  while(i >= 0)
  {
    Tree label_tree = (Tree)(label_tree_queue[i]->x);
    if(!strcmp(label_tree->u.generic.sym->name, label->name))
    {
      cp = label_tree_queue[i];
      return;
    }

    i--;
  }

  if(cp == NULL)
  {
    printf("label is not exist %s", label->name);
  }
}

void node_process(Tree node)
{
  switch (generic(node->op))
  {
    case INCR:
    {
      /* */
      node_process(node->kids[0]);
      /* */
      node->kids[0]->u.generic.sym->v.i++;
    }
    break;
    case DECR:
    {
      /*  */
      node_process(node->kids[0]);
      /*  */
      node->kids[0]->u.generic.sym->v.i--;
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
    jump_to_label(node->u.generic.sym);
  }
  break;
  case COND:
  {
    node_process(node->kids[0]);

    if((node->kids[0]->u.generic.val.i == 0 && node->u.cond_jump.true_or_false == false) || 
      (node->kids[0]->u.generic.val.i != 0 && node->u.cond_jump.true_or_false == true))
    {
      jump_to_label(node->u.cond_jump.label);
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
      switch (node->u.sys.sys_id)
      {
        case pWRITELN:
        {
          /* 参数对应的符号 */
          p = node->kids[0]->u.generic.sym;

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
    p = node->u.generic.sym;

    /* 参数赋值 */
    p->v.i = node->kids[0]->u.generic.val.i;

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
    p = node->u.generic.sym;

  	/* 参数赋值 */
  	p->v.i = node->kids[0]->u.generic.val.i;

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
      
      node->u.generic.sym = node->u.field.field;
    }
    break;
    case ARRAY:
    {
      char ele_name[NAME_LEN];
      /*  */
      for(p = node->u.generic.sym->type_link->first; p != NULL; p = p->next)
      {
        node_process(node->kids[0]);

        snprintf(ele_name, sizeof(ele_name), "%d", node->kids[0]->u.generic.val.i);
        if(is_symbol(p, ele_name))
        {
          node->u.generic.sym = p;
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
        node->u.generic.sym = node->kids[0]->u.generic.sym;
        node->u.generic.val.i = node->kids[0]->u.generic.sym->v.i;
      }
      else
      {
        node->u.generic.val.i = node->u.generic.sym->v.i;
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
      p = node->kids[0]->u.generic.sym;

      /* 变量赋值 */
      p->v.i = node->kids[1]->u.generic.val.i;
    }
    break;
    case CNST:
    {
      node->u.generic.val.i = node->u.generic.sym->v.i;
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

      node->u.generic.val.i = node->kids[0]->u.generic.val.i + node->kids[1]->u.generic.val.i;
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

      node->u.generic.val.i = node->kids[0]->u.generic.val.i - node->kids[1]->u.generic.val.i;
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

      node->u.generic.val.i = node->kids[0]->u.generic.val.i * node->kids[1]->u.generic.val.i;
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

      node->u.generic.val.i = node->kids[0]->u.generic.val.i / node->kids[1]->u.generic.val.i;
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

      node->u.generic.val.i = node->kids[0]->u.generic.val.i == node->kids[1]->u.generic.val.i;
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

      node->u.generic.val.i = node->kids[0]->u.generic.val.i != node->kids[1]->u.generic.val.i;
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

      node->u.generic.val.i = node->kids[0]->u.generic.val.i >= node->kids[1]->u.generic.val.i;
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

      node->u.generic.val.i = node->kids[0]->u.generic.val.i > node->kids[1]->u.generic.val.i;
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

      node->u.generic.val.i = node->kids[0]->u.generic.val.i <= node->kids[1]->u.generic.val.i;
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

      node->u.generic.val.i = node->kids[0]->u.generic.val.i < node->kids[1]->u.generic.val.i;
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