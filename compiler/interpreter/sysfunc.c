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
  Node args = node->kids[0]->kids[1];

	/*  */
  int i;
  char c;
  char str[NAME_LEN];

  /*  */
  Symbol p, q = NULL;

  while(args)
  {
    Node np = args->kids[0];

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
        printf("read wrong type");
        exit(1);
      }
    }

    args = args->kids[1];
  }
}

void write(Node node)
{
  Node args = node->kids[0];

  /*  */
  char *format_str = args->kids[0]->syms[0]->v.s;
  args = args->kids[1];

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
            printf("%d", args->val.i);

            /*  */
            if(!args)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            args = args->kids[1];
          }
          break;
          case 'c':
          {
            printf("%c", args->val.c);

            /*  */
            if(!args)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            args = args->kids[1];
          }
          break;
          case 'f':
          {
            printf("%f", args->val.f);

            /*  */
            if(!args)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            args = args->kids[1];
          }
          break;
          case 'u':
          {
            printf("%u", args->val.i);

            /*  */
            if(!args)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            args = args->kids[1];
          }
          break;
          case 'y':
          {
            printf("%u", args->val.uc);

            /*  */
            if(!args)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            args = args->kids[1];
          }
          break;
          case 's':
          {
            printf("%s", args->val.s);

            /*  */
            if(!args)
            {
              parse_error("format type mismatch", "");
              exit(1);
            }
            args = args->kids[1];
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