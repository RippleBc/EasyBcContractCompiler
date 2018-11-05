#include "../common.h"

#define ASSIGN_VAL(np, p, q) if(top_symtab_stack()->level == 0) \
      { \
        assign_global(np, p, q); \
      } \
      else \
      { \
        if(p->defn == DEF_VALPARA || p->defn == DEF_VARPARA) \
        { \
          assign_arg(np, p, q); \
        } \
        else \
        { \
          assign_local(np, p, q); \
        } \
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
  Symbol p = NULL, q = NULL;
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

  printf("pread name %s, offset %d\n", p->name, p->offset);

  switch(np->type->type_id)
  {
  case TYPE_INTEGER:
  {
    np->val.i = atoi(str);
    ASSIGN_VAL(np, p, q);
  }
  break;
  case TYPE_CHAR:
  {
    np->val.c = str[0];
    ASSIGN_VAL(np, p, q);
  }
  break;
  case TYPE_BOOLEAN:
  {
    np->val.b = atoi(str);
    ASSIGN_VAL(np, p, q);
  }
  break;
  case TYPE_REAL:
  {
    np->val.f = atof(str);
    ASSIGN_VAL(np, p, q);
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

	for(np = node->kids[0]; np != NULL; np = np->kids[1])
  {
    switch(np->type->type_id)
    {
    case TYPE_INTEGER:
    {
      printf("result: %d\n", np->kids[0]->val.i);
    }
    break;
    case TYPE_CHAR:
    {
      printf("result: %c\n", np->kids[0]->val.c);
    }
    break;
    case TYPE_BOOLEAN:
    {
      printf("result: %d\n", np->kids[0]->val.i);
    }
    break;
    case TYPE_REAL:
    {
      printf("result: %f\n", np->kids[0]->val.f);
    }
    break;
    case TYPE_STRING:
    {
      printf("result: %s\n", np->kids[0]->val.s);
    }
    break;
    default:
    {
      parse_error("wrong type", "");
    }
    }
  }
}