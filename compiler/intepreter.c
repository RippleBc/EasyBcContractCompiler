#include "common.h"
#include "symtab.h"

Symtab ptab = Global_symtab;
Symbol p;
Symbol q;

int ast_process(List asts)
{
    List cp = asts->link;
    int ret = 0;

    for (; cp; cp = cp->link)
    {
        /* 解析执行AST */
        if ((ret = intepret((Node)(cp->x))) < 0)
        {
            parse_error("Error generating code.", "");
            return ret;
        }
    }
    return ret;
}

static int intepret(List ast)
{
  int ret = 0;
  Tree ptree;

  gen_level++;

  switch (generic(rootnode->op))
  {
  case HEADER: /* 表示过程以及函数定义的开始 */  
  case TAIL: /* 表示过程以及函数定义的结束 */
  	break;
	case SYS:
	{
		if (rootnode->kids[0] == NULL)
		{
			/* 没有参数 */
		}
		else {
			/* 有参数 */
			switch (rootnode->u.sys_id)
      {
        case pWRITELN:
        {
        	/* 参数对应的符号 */
					p = find_symbol(ptab, ast->kids[0]->u.arg.sym->name);
        	printf("%d", p->v.i);
        }
        break;
		}
	}
	break;
	case RIGHT:
	{
		/* 参数对应的符号 */
		p = find_symbol(ptab, ast->kids[0]->u.arg.sym->name);

		/* 计算表达式AST节点对应的值 */
  	if(ast->kids[0]->kids[0] != NULL || ast->kids[0]->kids[1] != NULL)
  	{
  		intepret(ast->kids[0]);
  	}

  	/* 参数赋值 */
  	p->v.i = ast->kids[0]->u.generic.val->i;

  	/* 计算其余参数的值 */
  	if(ast->kids[1] != NULL)
  	{
  		intepret(ast->kids[1]);
  	}
	}
	break;
	case ARG:
	{
		/* 参数对应的符号 */
		p = find_symbol(ptab, ast->kids[0]->u.arg.sym->name);

		/* 计算表达式AST节点对应的值 */
  	if(ast->kids[0]->kids[0] != NULL || ast->kids[0]->kids[1] != NULL)
  	{
  		intepret(ast->kids[0]);
  	}

  	/* 参数赋值 */
  	p->v.i = ast->kids[0]->u.generic.val->i;

  	/* 计算其余参数的值 */
  	if(ast->kids[1] != NULL)
  	{
  		intepret(ast->kids[1]);
  	}
	}
	break;
  case ASGN:
  {
  	/* 对应的符号 */
  	Symbol p = find_symbol(ptab, ast->kids[0]->u.generic.sym->name);

  	/* 计算表达式AST节点对应的值 */
  	if(ast->kids[1]->kids[0] != NULL || ast->kids[1]->kids[1] != NULL)
  	{
  		intepret(ast->kids[1]);
  	}
  	
  	/* 变量赋值 */
  	p->v.i = ast->kids[1]->u.generic.val->i;
  }
  break;
  case ADD:
  {
  	/* 计算左表达式AST节点对应的值 */
  	if(ast->kids[0]->kids[0] != NULL || ast->kids[0]->kids[1] != NULL)
  	{
  		intepret(ast->kids[0]);
  	}

  	/* 计算右表达式AST节点对应的值 */
  	if(ast->kids[1]->kids[0] != NULL || ast->kids[1]->kids[1] != NULL)
  	{
  		intepret(ast->kids[1]);
  	}

  	ast->u.generic.val->i = ast->kids[0]->u.generic.val->i + ast->kids[1]->u.generic.val->i;
  }
  break;
  case SUB:
  {
  	/* 计算左表达式AST节点对应的值 */
  	if(ast->kids[0]->kids[0] != NULL || ast->kids[0]->kids[1] != NULL)
  	{
  		intepret(ast->kids[0]);
  	}

  	/* 计算右表达式AST节点对应的值 */
  	if(ast->kids[1]->kids[0] != NULL || ast->kids[1]->kids[1] != NULL)
  	{
  		intepret(ast->kids[1]);
  	}

  	ast->u.generic.val->i = ast->kids[0]->u.generic.val->i - ast->kids[1]->u.generic.val->i;
  }
  break;
  case BLOCKBEG:
  case BLOCKEND:
      break;
  default:
      assert(0);
      break;
  }
}