#include "../common.h"

#define MAX_CODE_NUM 10 * 1024
#define MAX_FORMAT_STR_SIZE 128
#define MAX_STR_SIZE 128

#define GLOBAL_AREA_MARK 1
#define FUNCTION_CALL_STACK_MARK 2

int byte_sequence_size = 0;
unsigned char byte_sequence[MAX_CODE_NUM];

int byte_sequence_index = 0;

void interpret()
{
  /*  */
	struct _op_code_ *code_detail;

  /*  */
  unsigned char* cp;

  while(byte_sequence_index < byte_sequence_size)
  {
  	code_detail = get_detail_by_op_code(byte_sequence[byte_sequence_index]);
    if(code_detail == NULL)
    {
      printf("*************get_detail_by_op_code error*************\n");
      exit(1);
    }

  	if(!strcmp(code_detail->name, "PUSH4"))
  	{
  		push_vm_stack_from_byte_sequence(4);
  	}
  	else if(!strcmp(code_detail->name, "PUSH8"))
  	{
  		push_vm_stack_from_byte_sequence(8);
  	}
    else if(!strcmp(code_detail->name, "COND"))
    {
      int position = get_int_from_vm_stack();
      boolean cond = get_boolean_from_vm_stack();
      boolean expression = get_boolean_from_vm_stack();
      
      if(cond == expression)
      {
        /* jump */
        byte_sequence_index = position;
      }
      else
      {
        /* execute the next op code */
        byte_sequence_index++;
      }
    }
    else if(!strcmp(code_detail->name, "JUMP"))
    {
      int position = get_int_from_vm_stack();
      byte_sequence_index = position;
    }
    else
    {
      /*  */
      if(!strcmp(code_detail->name, "ILSH"))
      {
        value result;
        result.i = get_int_from_vm_stack() <<  get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IRSH %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_INTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "IRSH"))
      {
        value result;
        result.i = get_int_from_vm_stack() >>  get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IRSH %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_INTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "UILSH"))
      {
        value result;
        result.ui = get_uint_from_vm_stack() <<  get_uint_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("UILSH %d result %d\n", result.ui);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "UIRSH"))
      {
        value result;
        result.ui = get_uint_from_vm_stack() >>  get_uint_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("UIRSH %d result %d\n", result.ui);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }

      /* basic arithmatical */
      if(!strcmp(code_detail->name, "IADD"))
      {
        value result;
        result.i = get_int_from_vm_stack() + get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IADD %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "ISUB"))
      {
        value result;
        result.i = get_int_from_vm_stack() - get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("ISUB %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      if(!strcmp(code_detail->name, "IMUL"))
      {
        value result;
        result.i = get_int_from_vm_stack() * get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IMUL %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "IDIV"))
      {
        value result;
        result.i = get_int_from_vm_stack() / get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IDIV %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      if(!strcmp(code_detail->name, "RADD"))
      {
        value result;
        result.f = get_real_from_vm_stack() + get_real_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IADD %d result %d\n", result.f);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "RSUB"))
      {
        value result;
        result.f = get_real_from_vm_stack() - get_real_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("ISUB %d result %d\n", result.f);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      if(!strcmp(code_detail->name, "RMUL"))
      {
        value result;
        result.f = get_real_from_vm_stack() * get_real_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IMUL %d result %d\n", result.f);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "RDIV"))
      {
        value result;
        result.f = get_real_from_vm_stack() / get_real_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IDIV %d result %d\n", result.f);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "MOD"))
      {
        value result;
        result.i = get_int_from_vm_stack() / get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("MOD %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_UINTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "IINCR"))
      {
        value result;
        result.i = get_int_from_vm_stack() + 1;

        if(TYPE_BYTE_DEBUG)
        {
          printf("IINCR %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_INTEGER, &result);
      }
      else if(!strcmp(code_detail->name, "IDECR"))
      {
        value result;
        result.i = get_int_from_vm_stack() - 1;

        if(TYPE_BYTE_DEBUG)
        {
          printf("IDECR %d result %d\n", result.i);
        }

        push_vm_stack_from_compute(TYPE_INTEGER, &result);
      }
      
      /* judge */
      if(!strcmp(code_detail->name, "IEQ"))
      {
        value result;
        result.b = get_int_from_vm_stack() == get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IEQ %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      else if(!strcmp(code_detail->name, "INE"))
      {
        value result;
        result.b = get_int_from_vm_stack() != get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("INE %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      else if(!strcmp(code_detail->name, "IGE"))
      {
        value result;
        result.b = get_int_from_vm_stack() >= get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IGE %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      else if(!strcmp(code_detail->name, "IGT"))
      {
        value result;
        result.b = get_int_from_vm_stack() > get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("IGT %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      else if(!strcmp(code_detail->name, "ILE"))
      {
        value result;
        result.b = get_int_from_vm_stack() <= get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("ILE %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      else if(!strcmp(code_detail->name, "ILT"))
      {
        value result;
        result.b = get_int_from_vm_stack() < get_int_from_vm_stack();

        if(TYPE_BYTE_DEBUG)
        {
          printf("ILT %d result %d\n", result.b);
        }

        push_vm_stack_from_compute(TYPE_BOOLEAN, &result);
      }
      

      /* global stack */
      if(!strcmp(code_detail->name, "ASSIGN_GLOBAL4"))
      {
        assign_global(4);
      }
      else if(!strcmp(code_detail->name, "LOAD_GLOBAL4"))
      {
        load_global(4);
      }
      else if(!strcmp(code_detail->name, "ASSIGN_GLOBAL8"))
      {
        assign_global(8);
      }
      else if(!strcmp(code_detail->name, "LOAD_GLOBAL8"))
      {
        load_global(8);
      }

      /* function stack */
      if(!strcmp(code_detail->name, "ASSIGN_CALL4"))
      {
        assign_call(4);
      }
      else if(!strcmp(code_detail->name, "LOAD_CALL4"))
      {
        load_call(4);
      }
      else if(!strcmp(code_detail->name, "ASSIGN_CALL8"))
      {
        assign_call(8);
      }
      else if(!strcmp(code_detail->name, "LOAD_CALL8"))
      {
        load_call(8);
      }
      else if(!strcmp(code_detail->name, "TOP_CALL"))
      {
        top_call();
      }
      else if(!strcmp(code_detail->name, "PUSH_CALL"))
      {
        push_call();
      }
      else if(!strcmp(code_detail->name, "POP_CALL"))
      {
        pop_call();
      }

      if(!strcmp(code_detail->name, "READLN"))
      {
        char format_str[MAX_FORMAT_STR_SIZE];

        /*  */
        int format_str_size = get_int_from_vm_stack();
        if(format_str_size > MAX_FORMAT_STR_SIZE)
        {
          printf("*************format string is too long , max size is %d*************\n", MAX_FORMAT_STR_SIZE);
          exit(1);
        }

        /*  */
        int format_str_index = 0;
        while(format_str_index < format_str_size)
        {
          format_str[format_str_index++] = get_char_from_vm_stack();
        }
        format_str[format_str_index] = '\0';
        
        /*  */
        int i;
        int j;
        char c;
        char str[NAME_LEN];
        for(i = 0; i < format_str_index - 1; i++)
        {
          if(format_str[i] == '%')
          {
            if(i == 0 || format_str[i-1] != '\\')
            {
              /*  */
              j = 0;
              while(1)
              {
                while((c = getchar()) != '\n')
                {
                  str[j++] = c;
                }
                str[j] = '\0';
                if(j == 0)
                {
                  printf("please input valid val\n");
                  continue;
                }
                break;
              }

              /*  */
              int memory_mark = get_int_from_vm_stack();

              /*  */
              int size = get_int_from_vm_stack();

              /*  */
              int address = get_int_from_vm_stack();

              
              switch(format_str[i + 1])
              {
                case 'd':
                {
                  /* data */
                  value result;
                  result.i = atoi(str);
                  push_vm_stack_from_compute(TYPE_INTEGER, &result);
                }
                break;
                case 'c':
                {
                  /* data */
                  value result;
                  result.c = (char)str[0];
                  push_vm_stack_from_compute(TYPE_CHAR, &result);
                }
                break;
                case 'f':
                {
                  /* data */
                  value result;
                  result.f = atof(str);
                  push_vm_stack_from_compute(TYPE_REAL, &result);
                }
                break;
                case 'u':
                {
                  /* data */
                  value result;
                  result.ui = (unsigned int)atoi(str);
                  push_vm_stack_from_compute(TYPE_UINTEGER, &result);
                }
                break;
                case 'y':
                {
                  /* data */
                  value result;
                  result.uc = (unsigned char)str[0];
                  push_vm_stack_from_compute(TYPE_UCHAR, &result);
                }
                break;
                default:
                {
                  printf("*************unsupported format type*************\n", format_str[i + 1]);
                  exit(1);
                }
              }

              /* address */
              value result;
              result.i = address;
              push_vm_stack_from_compute(TYPE_INTEGER, &result);

              /* */
              if(memory_mark == GLOBAL_AREA_MARK)
              {
                assign_global(size);
              }
              else
              {
                assign_call(size);
              }

              i++;
            }
          }
        }
      }
      else if(!strcmp(code_detail->name, "WRITELN"))
      {
        char format_str[MAX_FORMAT_STR_SIZE];

        /*  */
        int format_str_size = get_int_from_vm_stack();
        if(format_str_size > MAX_FORMAT_STR_SIZE)
        {
          printf("*************format string is too long , max size is %d*************\n", MAX_FORMAT_STR_SIZE);
          exit(1);
        }

        /*  */
        int format_str_index = 0;
        while(format_str_index < format_str_size)
        {
          format_str[format_str_index++] = get_char_from_vm_stack();
        }
        format_str[format_str_index] = '\0';
        
        /*  */
        int i;
        for(i = 0; i < format_str_index - 1; i++)
        {
          if(format_str[i] == '%')
          {
            if(i == 0 || format_str[i-1] != '\\')
            {
              switch(format_str[i + 1])
              {
                case 'd':
                {
                  printf("%d", get_int_from_vm_stack());
                }
                break;
                case 'c':
                {
                  printf("%c", get_char_from_vm_stack());
                }
                break;
                case 'f':
                {
                  printf("%f", get_real_from_vm_stack());
                }
                break;
                case 'u':
                {
                  printf("%u", get_uint_from_vm_stack());
                }
                break;
                case 'y':
                {
                  printf("%u", get_uchar_from_vm_stack());
                }
                break;
                case 's':
                {
                  char str[MAX_STR_SIZE];

                  /* str size */
                  int str_size = get_int_from_vm_stack();
                  if(str_size > MAX_STR_SIZE)
                  {
                    printf("*************string is too long , max size is %d*************\n", MAX_STR_SIZE);
                    exit(1);
                  }

                  /* str data */
                  int str_index = 0;
                  while(str_index < str_size)
                  {
                    str[str_index++] = get_char_from_vm_stack();
                  }
                  str[str_index] = '\0';

                  printf("%s", str);
                }
                break;
                default:
                {
                  printf("*************unsupported format type*************\n", format_str[i + 1]);
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

      byte_sequence_index++;
    }
  }
}