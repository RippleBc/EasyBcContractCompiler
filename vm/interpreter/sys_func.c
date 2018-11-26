 #include "../common.h"

#define MAX_FORMAT_STR_SIZE 128
#define MAX_STR_SIZE 128

#define GLOBAL_AREA_MARK 1
#define FUNCTION_CALL_STACK_MARK 2

void sys_func(struct _op_code_ *code_detail) 
{
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
}
