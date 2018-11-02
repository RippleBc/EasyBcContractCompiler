#include "../common.h"

#define ASSIGN_VAL if(top_symtab_stack()->level == 0) \
      { \
        assign_global(node, p, q); \
      } \
      else \
      { \
        if(p->defn == DEF_VALPARA || p->defn == DEF_VARPARA) \
        { \
          assign_arg(node, p, q); \
        } \
        else \
        { \
          assign_local(node, p, q); \
        } \
      } \

void read(Node node)
{
	Node np = node->kids[0];
  char str[NAME_LEN];
  char c;
  int i;

  while(np)
  {
  	/*  */
    i = 0;
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

    /*  */
    Symbol p, q;
    if(generic(np->op) == ARRAY || generic(np->op) == FIELD)
    {
      /* syms[0]表示数组或者记录，syms[1]表示数组成员或者属性，node->kids[0]表示ARRAY或者FIELD节点 */
      p = node->syms[1];
      q = node->syms[0];
    }
    else
    {
      p = node->syms[0];
    }

    switch(np->type->type_id)
    {
    case TYPE_INTEGER:
    {
      node->val.i = atoi(str);
      ASSIGN_VAL;
    }
    break;
    case TYPE_CHAR:
    {
      node->val.c = str[0];
      ASSIGN_VAL;
    }
    break;
    case TYPE_BOOLEAN:
    {
      node->val.b = atoi(str);
      ASSIGN_VAL;
    }
    break;
    case TYPE_REAL:
    {
      node->val.f = atof(str);
      ASSIGN_VAL;
    }
    break;
    case TYPE_ARRAY:
    {
      if(node->type->last->type->type_id == TYPE_CHAR)
      {
        ASSIGN_VAL;
      }
      else
      {
        parse_error("wrong type", "");
      }
    }
    break;
    default:
    {
      parse_error("wrong type", "");
    }
    }

    np = np->kids[1];
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
      printf("result: %d\n", node->kids[0]->val.i);
    }
    break;
    case TYPE_CHAR:
    {
      printf("result: %c\n", node->kids[0]->val.c);
    }
    break;
    case TYPE_BOOLEAN:
    {
      printf("result: %d\n", node->kids[0]->val.i);
    }
    break;
    case TYPE_REAL:
    {
      printf("result: %f\n", node->kids[0]->val.f);
    }
    break;
    case TYPE_STRING:
    {
      printf("result: %s\n", node->kids[0]->val.s);
    }
    break;
    case TYPE_ARRAY:
    {
      if(node->type->last->type->type_id == TYPE_CHAR)
      {
        printf("result: %s\n", node->kids[0]->val.s);
      }
      else
      {
        parse_error("wrong type", "");
      }
    }
    break;
    default:
    {
      parse_error("wrong type", "");
    }
    }
  }
}