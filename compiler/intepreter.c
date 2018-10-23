#include  <stdio.h>
#include  "common.h"
#include  "symtab.h"
#include  "error.h"
#include  _YTAB_H_

Symtab ptab;
Symbol p;
Symbol q;

int ast_process(List asts)
{
    ptab = Global_symtab;

    List cp = asts->link;
    int ret = 0;

    for (; cp; cp = cp->link)
    {
        /* 解析执行AST */
        if ((ret = intepret((Tree)(cp->x))) < 0)
        {
            parse_error("Error generating code.", "");
            return ret;
        }
    }
    return ret;
}

int intepret(Tree ast)
{
  Tree ptree;

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
      intepret(ast->kids[0]);
      /* 有参数 */
      switch (ast->u.sys.sys_id)
      {
        case pWRITELN:
        {
          /* 参数对应的符号 */
          p = ast->kids[0]->u.generic.sym;

          /*  */
          printf("\n%d\n", p->v.i);
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
  		intepret(ast->kids[0]);
  	}

    /* 参数对应的符号 */
    p = ast->u.generic.sym;

    /* 参数赋值 */
    p->v.i = ast->kids[0]->u.generic.val.i;

  	/* 计算其余参数的值 */
  	if(ast->kids[1] != NULL)
  	{
  		intepret(ast->kids[1]);
  	}
	}
	break;
	case ARG:
	{
    printf("\nARG, ");

		/* 计算参数的值 */
  	if(ast->kids[0] != NULL)
  	{
  		intepret(ast->kids[0]);
  	}

    /* 参数对应的符号 */
    p = ast->u.generic.sym;

  	/* 参数赋值 */
  	p->v.i = ast->kids[0]->u.generic.val.i;

  	/* 计算其余参数的值 */
  	if(ast->kids[1] != NULL)
  	{
  		intepret(ast->kids[1]);
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
      /* */
      for(p = ast->u.generic.sym->type_link->first; p != NULL; p = p->next)
      {
        intepret(ast->kids[0]);

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
        return 0;
      }
    }
    break;
    case ADDRG:
    {
      /*  */
      if(ast->kids[0])
      {
        intepret(ast->kids[0]);
        ast->u.generic.sym = ast->kids[0]->u.generic.sym;
      }
    }
    break;
    case LOAD:
    {
      /*  */
      if(ast->kids[0])
      {
        intepret(ast->kids[0]);
        ast->u.generic.sym = ast->kids[0]->u.generic.sym;
        ast->u.generic.val.i = ast->kids[0]->u.generic.sym->v.i;
      }
      else
      {
        ast->u.generic.val.i = ast->u.generic.sym->v.i;
      }

      printf("load %s\n", ast->u.generic.sym->name);
    }
    break;
    case ASGN:
    {
      /*  */
      if(ast->kids[0])
      {
        intepret(ast->kids[0]);
      }

      /* 计算表达式AST节点对应的值 */
      if(ast->kids[1])
      {
        intepret(ast->kids[1]);
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
        intepret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1])
      {
        intepret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i + ast->kids[1]->u.generic.val.i;
    }
    break;
    case SUB:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        intepret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        intepret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i - ast->kids[1]->u.generic.val.i;
    }
    break;
    case MUL:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        intepret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        intepret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i * ast->kids[1]->u.generic.val.i;
    }
    break;
    case DIV:
    {
      /* 计算左表达式AST节点对应的值 */
      if(ast->kids[0] != NULL)
      {
        intepret(ast->kids[0]);
      }

      /* 计算右表达式AST节点对应的值 */
      if(ast->kids[1] != NULL)
      {
        intepret(ast->kids[1]);
      }

      ast->u.generic.val.i = ast->kids[0]->u.generic.val.i / ast->kids[1]->u.generic.val.i;
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
    default:
        return 0;
  }

  return 1;
}


void astCompute()
{

}