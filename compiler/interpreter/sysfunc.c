#include "../common.h"

#define ASSIGN_VAL if(top_symtab_stack()->level == 0) \
      { \
        assign_global(var, p, q); \
      } \
      else \
      { \
        assign_function_call_stack_val(var, p, q); \
      } \

void read(Node node)
{
  Node arg = node->kids[0]->kids[1];
  Node var;
	/*  */
  int i;
  char c;
  char str[NAME_LEN];

  /*  */
  Symbol p, q;

  while(arg)
  {
    var = arg->kids[0];

    /*  */
    i = 0;
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
    q = NULL;
    if(generic(var->op) == ARRAY || generic(var->op) == FIELD)
    {
      /* syms[0]表示数组或者记录，syms[1]表示数组成员或者属性，var->kids[0]表示ARRAY或者FIELD节点 */
      p = var->syms[1];
      q = var->syms[0];
    }
    else
    {
      p = var->syms[0];
    } 

    switch(p->type->type_id)
    {
      case TYPE_INTEGER:
      {
        var->val.i = atoi(str);
        ASSIGN_VAL;
      }
      break;
      case TYPE_UINTEGER:
      {
        var->val.ui = (unsigned int)atoi(str);
        ASSIGN_VAL;
      }
      break;
      case TYPE_CHAR:
      {
        var->val.c = (char)str[0];
        ASSIGN_VAL;
      }
      break;
      case TYPE_UCHAR:
      {
        var->val.uc = str[0];
        ASSIGN_VAL;
      }
      break;
      case TYPE_BOOLEAN:
      {
        var->val.b = atoi(str);
        ASSIGN_VAL;
      }
      break;
      case TYPE_REAL:
      {
        var->val.f = atof(str);
        ASSIGN_VAL;
      }
      break;
      default:
      {
        printf("read wrong type");
        exit(1);
      }
    }

    arg = arg->kids[1];
  }
}

void write(Node node)
{
  Node arg = node->kids[0];

  /*  */
  char *format_str = arg->kids[0]->syms[0]->v.s;
  arg = arg->kids[1];

  /* check format */
  int i;
  int format_str_size = strlen(format_str);
  for(i = 0; i < format_str_size - 1; i++)
  {
    if(format_str[i] == '%')
    {
      if(i == 0 || format_str[i-1] != '\\')
      {
        switch(format_str[i + 1])
        {
          case 'd':
          {
            printf("%d", arg->val.i);

            /*  */
            if(!arg)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            arg = arg->kids[1];
          }
          break;
          case 'c':
          {
            printf("%c", arg->val.c);

            /*  */
            if(!arg)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            arg = arg->kids[1];
          }
          break;
          case 'f':
          {
            printf("%f", arg->val.f);

            /*  */
            if(!arg)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            arg = arg->kids[1];
          }
          break;
          case 'u':
          {
            printf("%u", arg->val.i);

            /*  */
            if(!arg)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            arg = arg->kids[1];
          }
          break;
          case 'y':
          {
            printf("%u", arg->val.uc);

            /*  */
            if(!arg)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            arg = arg->kids[1];
          }
          break;
          case 's':
          {
            printf("%s", arg->val.s);

            /*  */
            if(!arg)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            arg = arg->kids[1];
          }
          break;
          default:
          {
            parse_error("unsupported format type", "");
            exit(1);
          }
        }

        i++;
        continue;
      }
    }
    else if((i == 0 && format_str[i] == '\\') || 
        (i > 0 && format_str[i - 1] != '\\' && format_str[i] == '\\'))
    {
      if(format_str[i + 1] == 'n')
      {
        printf("\n");

        i++;
        continue;
      }
    }
    else
    {
      printf("%c", format_str[i]);
    }
  }

  printf("%c", format_str[i]);
}