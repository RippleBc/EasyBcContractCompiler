#include "../common.h"

void check_format_str(Tree args)
{
	/* check arg */
	if(args->kids[0]->result_type->type_id != TYPE_STRING)
	{
		parse_error("type mismatch", "");
	}
  
  /*  */
  char *format_str = args->kids[0]->u.generic.sym->v.s;
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
          	if(args->kids[0]->result_type->type_id != TYPE_INTEGER && args->kids[0]->result_type->type_id != TYPE_BOOLEAN)
          	{
          		parse_error("format type mismatch, should be integer", "");
          		exit(1);
          	}

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
            if(args->kids[0]->result_type->type_id != TYPE_CHAR)
          	{
          		parse_error("format type mismatch, should be char", "");
          		exit(1);
          	}

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
            if(args->kids[0]->result_type->type_id != TYPE_REAL)
          	{
          		parse_error("format type mismatch, should be real", "");
          		exit(1);
          	}

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
            if(args->kids[0]->result_type->type_id != TYPE_UINTEGER)
          	{
          		parse_error("format type mismatch, should be unsigned integer", "");
          		exit(1);
          	}

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
            if(args->kids[0]->result_type->type_id != TYPE_UCHAR)
          	{
          		parse_error("format type mismatch, should be unsigned char", "");
          		exit(1);
          	}

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
            if(args->kids[0]->result_type->type_id != TYPE_STRING)
          	{
          		parse_error("format type mismatch, should be string", "");
          		exit(1);
          	}

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
      }
    }
  }
}