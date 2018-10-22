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
  case HEADER: /* 表示过程以及函数定义的开始 */  
  case TAIL: /* 表示过程以及函数定义的结束 */
  	break;
	case SYS:
	{
    printf("\nSYS\n");
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
					p = ast->kids[0]->u.arg.sym;

          /*  */
        	printf("%d", p->v.i);
        }
        break;
      }
		}
	}
	break;
	case RIGHT:
	{
    printf("\nRIGHT\n");

		/* 计算表达式AST节点对应的值 */
  	if(ast->kids[0]->kids[0] != NULL || ast->kids[0]->kids[1] != NULL)
  	{
  		intepret(ast->kids[0]);
  	}

    /* 参数对应的符号 */
    p = ast->u.arg.sym;

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
    printf("\nARG\n");

		/* 计算参数的值 */
  	if(ast->kids[0] != NULL)
  	{
  		intepret(ast->kids[0]);
  	}

    /* 参数对应的符号 */
    p = ast->u.arg.sym;

  	/* 参数赋值 */
  	p->v.i = ast->kids[0]->u.generic.val.i;

  	/* 计算其余参数的值 */
  	if(ast->kids[1] != NULL)
  	{
  		intepret(ast->kids[1]);
  	}
	}
	break;
  case LOAD:
  {
    printf("\nLOAD\n");

    ast->u.generic.val.i = ast->u.generic.sym->v.i;

    printf("\nload result: %d\n", ast->u.generic.val.i);
  }
  break;
  case ASGN:
  {
    printf("\nASGN\n");

  	/* 对应的符号 */
  	p = ast->kids[0]->u.generic.sym;

  	/* 计算表达式AST节点对应的值 */
  	if(ast->kids[1])
  	{
  		intepret(ast->kids[1]);
  	}
  	
  	/* 变量赋值 */
  	p->v.i = ast->kids[1]->u.generic.val.i;

    printf("\nasign result %d\n", p->v.i);
  }
  break;
  case CNST:
  {
    printf("\nCONST\n");

    ast->u.generic.val.i = ast->u.generic.sym->v.i;

    printf("\nconst result: %d\n", ast->u.generic.val.i);

  }
  break;
  case ADD:
  {
    printf("\nADD\n");

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

    printf("\nadd result %d\n", ast->u.generic.val.i);
  }
  break;
  case SUB:
  {
    printf("\nSUB\n");

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
    printf("\nMUL\n");

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

    printf("\nmul result %d\n", ast->u.generic.val.i);
  }
  break;
  case DIV:
  {
    printf("\nDIV\n");

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

    printf("\ndiv result %d\n", ast->u.generic.val.i);
  }
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