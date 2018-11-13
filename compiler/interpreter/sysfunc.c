#include "../common.h"

#define ASSIGN_VAL if(top_symtab_stack()->level == 0) \
      { \
        assign_global(np, p, q); \
      } \
      else \
      { \
        assign_function_call_stack_val(np, p, q); \
      } \

void read(Node node)
{
  Node np = node->kids[0];

	/*  */
  int i = 0;
  char c;
  char str[NAME_LEN];

  /*  */
  while(1)
  {
    while((c = getchar()) != '\n')
    {
      str[i++] = c;
    }
    str[i] = '\0';
    if(i == 0)
    {
      printf("please input valid val\n");
      continue;
    }
    break;
  }

  /*  */
  Symbol p, q = NULL;
  if(generic(np->op) == ARRAY || generic(np->op) == FIELD)
  {
    /* syms[0]表示数组或者记录，syms[1]表示数组成员或者属性，np->kids[0]表示ARRAY或者FIELD节点 */
    p = np->syms[1];
    q = np->syms[0];
  }
  else
  {
    p = np->syms[0];
  }

  switch(p->type->type_id)
  {
  case TYPE_INTEGER:
  {
    np->val.i = atoi(str);
    ASSIGN_VAL;
  }
  break;
  case TYPE_UINTEGER:
  {
    np->val.ui = (unsigned int)atoi(str);
    ASSIGN_VAL;
  }
  break;
  case TYPE_CHAR:
  {
    np->val.c = str[0];
    ASSIGN_VAL;
  }
  break;
  case TYPE_UCHAR:
  {
    np->val.uc = str[0];
    ASSIGN_VAL;
  }
  break;
  case TYPE_BOOLEAN:
  {
    np->val.b = atoi(str);
    ASSIGN_VAL;
  }
  break;
  case TYPE_REAL:
  {
    np->val.f = atof(str);
    ASSIGN_VAL;
  }
  break;
  default:
  {
    parse_error("wrong type", "");
  }
  }
}

void write(Node node)
{
	Node np;
  Node exp;
  int type_id;

	for(np = node->kids[0]; np != NULL; np = np->kids[1])
  {    
    exp = np->kids[0];

    if(generic(exp->op) == LOAD)
    {
      if(exp->kids[0])
      {
        /*  */
        type_id = exp->kids[0]->syms[1]->type->type_id;
      }
      else
      {
        type_id = exp->syms[0]->type->type_id;
      }
    }
    else
    {
      type_id = exp->type->type_id;
    }


    switch(type_id)
    {
    case TYPE_INTEGER:
    {
      printf("%d\n", np->val.i);
    }
    break;
    case TYPE_CHAR:
    {
      printf("%c\n", np->val.c);
    }
    break;
    case TYPE_BOOLEAN:
    {
      printf("%d\n", np->val.i);
    }
    break;
    case TYPE_REAL:
    {
      printf("%f\n", np->val.f);
    }
    break;
    case TYPE_STRING:
    {
      printf("%s\n", np->val.s);
    }
    break;
    default:
    {
      parse_error("wrong type", "");
    }
    }
  }
}