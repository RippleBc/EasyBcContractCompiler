#include  <stdio.h>
#include  "common.h"
#include  "symtab.h"
#include  "error.h"
#include  "./parser/rule.h"

Symtab ptab;
Symbol p;
Symbol q;

List cp;

static int label_tree_index = 0;
static List label_tree_queue[256];

void ast_process(List asts)
{
    ptab = Global_symtab;
    Tree t;
    
    /*  */
    for(cp = asts->link; cp != NULL; cp = cp->link)
    {
      t = (Tree)(cp->x);
      if(generic(t->op) == LABEL)
      {
        label_tree_queue[label_tree_index++] = cp;
      }
    }

    /*  */
    for(cp = asts->link; cp != NULL; cp = cp->link)
    {
      interpret((Tree)(cp->x));
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

void interpret(Tree ast)
{
  switch (generic(ast->op))
  {
    case INCR:
    {
      /* */
      interpret(ast->kids[0]);
      /* */
      ast->kids[0]->u.generic.sym->v.i++;
    }
    break;
    case DECR:
    {
      /*  */
      interpret(ast->kids[0]);
      /*  */
      ast->kids[0]->u.generic.sym->v.i--;
    }
    break;
  }

  switch (generic(ast->op))
  {
  case LABEL:
  {
    
  }
  break;
  case JUMP:
  {
    jump_to_label(ast->u.generic.sym);
  }
  break;
  case COND:
  {
    interpret(ast->kids[0]);

    if((ast->kids[0]->u.generic.val.i == 0 && ast->u.cond_jump.true_or_false == false) || 
      (ast->kids[0]->u.generic.val.i != 0 && ast->u.cond_jump.true_or_false == true))
    {
      jump_to_label(ast->u.cond_jump.label);
    }
  }
  break;
  }

  switch (generic(ast->op))
  {
  case SYS:
  {
    if (ast->kids[0] == NULL)
    {
      /* 没有参数 */
    }
    else {
      /*  */
      interpret(ast->kids[0]);
      /* 有参数 */
      switch (ast->u.sys.sys_id)
      {
        case pWRITELN:
        {
          /* 参数对应的符号 */
          p = ast->kids[0]->u.generic.sym;

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

  switch (generic(ast->op))
  {
	case RIGHT:
	{
    printf("\nRIGHT, ");

		/* 计算表达式AST节点对应的值 */
  	if(ast->kids[0]->kids[0] != NULL || ast->kids[0]->kids[1] != NULL)
  	{
  		interpret(ast->kids[0]);
  	}

    /* 参数对应的符号 */
    p = ast->u.generic.sym;

    /* 参数赋值 */
    p->v.i = ast->kids[0]->u.generic.val.i;

  	/* 计算其余参数的值 */
  	if(ast->kids[1] != NULL)
  	{
  		interpret(ast->kids[1]);
  	}
	}
	break;
	case ARG:
	{
		/* 计算参数的值 */
  	if(ast->kids[0] != NULL)
  	{
  		interpret(ast->kids[0]);
  	}

    /* 参数对应的符号 */
    p = ast->u.generic.sym;

  	/* 参数赋值 */
  	p->v.i = ast->kids[0]->u.generic.val.i;

  	/* 计算其余参数的值 */
  	if(ast->kids[1] != NULL)
  	{
  		interpret(ast->kids[1]);
  	}
	}
	break;
  }

  switch (generic(ast->op))
  {
    case CNST:
    {
      ast->u.generic.val.i = ast->u.generic.sym->v.i;
    }
    break;
  }

  switch (generic(ast->op))
  {
    case FIELD:
    {
      
      ast->u.generic.sym = ast->u.field.field;
    }
    break;
    case ARRAY:
    {
      char ele_name[NAME_LEN];
      /*  */
      for(p = ast->u.generic.sym->type_link->first; p != NULL; p = p->next)
      {
        interpret(ast->kids[0]);

        snprintf(ele_name, sizeof(ele_name), "%d", ast->kids[0]->u.generic.val.i);
        if(is_symbol(p, ele_name))
        {
          ast->u.generic.sym = p;
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
      /*  */
      if(ast->kids[0])
      {
        interpret(ast->kids[0]);
        ast->u.generic.sym = ast->kids[0]->u.generic.sym;
      }
    }
    break;
    case LOAD:
    {
      /*  */
      if(ast->kids[0])
      {
        interpret(ast->kids[0]);
        ast->u.generic.sym = ast->kids[0]->u.generic.sym;
        ast->u.generic.val.i = ast->kids[0]->u.generic.sym->v.i;
      }
      else
      {
        ast->u.generic.val.i = ast->u.generic.sym->v.i;
      }
    }
    break;
    case ASGN:
    {
      /*  */
      if(ast->kids[0])
      {
        interpret(ast->kids[0]);
      }

      /* 计算表达式AST节点对应的值 */
      if(ast->kids[1])
      {
        interpret(ast->kids[1]);
      }
      
      /* 对应的符号 */
      p = ast->kids[0]->u.generic.sym;

      /* 变量赋值 */
      p->v.i = ast->kids[1]->u.generic.val.i;
    }
    break;
  }

  switch (generic(ast->op))
  {
    case ADD:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0])
      {
        interpret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1])
      {
        interpret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i + ast->kids[1]->u.generic.val.i;
    }
    break;
    case SUB:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        interpret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        interpret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i - ast->kids[1]->u.generic.val.i;
    }
    break;
    case MUL:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        interpret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        interpret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i * ast->kids[1]->u.generic.val.i;
    }
    break;
    case DIV:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        interpret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        interpret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i / ast->kids[1]->u.generic.val.i;
    }
    break;
    case EQ:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        interpret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        interpret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i == ast->kids[1]->u.generic.val.i;
    }
    break;
    case NE:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        interpret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        interpret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i != ast->kids[1]->u.generic.val.i;
    }
    break;
    case GE:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        interpret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        interpret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i >= ast->kids[1]->u.generic.val.i;
    }
    break;
    case GT:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        interpret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        interpret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i > ast->kids[1]->u.generic.val.i;
    }
    break;
    case LE:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        interpret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        interpret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i <= ast->kids[1]->u.generic.val.i;
    }
    break;
    case LT:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        interpret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        interpret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i < ast->kids[1]->u.generic.val.i;
    }
    break;
  }

  switch (generic(ast->op))
  {
    case HEADER: /* 表示过程以及函数定义的开始 */  
    case TAIL: /* 表示过程以及函数定义的结束 */
      break;
    case BLOCKBEG:
    case BLOCKEND:
        break;
  }
}