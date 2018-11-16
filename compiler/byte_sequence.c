#include "./common.h"

void assign_with_byte_unit(int type, unsigned char *array, Value v)
{
  int j = 0;
  unsigned char *p = NULL;

  switch(type)
  {
    case TYPE_INTEGER:
    case TYPE_BOOLEAN:
    {
      int i_tmp = v->i;

      /* neg int */
      if(v->i < 0)
      {
        /* complement to abs*/
        i_tmp = ~(v->i - 1);
      }
     
      p = &i_tmp;

      if(g_is_big_endian)
      {
        for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
        {
         array[IR->intmetric.size - 1 - j] = *(p + j);
        }
      }
      else
      {
        for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
        {
          array[IR->intmetric.size - 1 - j] = *(p + sizeof(int) - 1 - j);
        }
      }

      /* neg int */
      if(v->i < 0)
      {
        /* true to complement */
        int *i_tmp = array;
        *i_tmp = (~(*i_tmp) + 1);

        /*  */
        unsigned char c_tmp = 0x80;

        array[0] = array[0] | c_tmp;
      }
    }
    break;
    case TYPE_UINTEGER:
    {
      p = &(v->ui);

      if(g_is_big_endian)
      {
        for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
        {
         array[IR->intmetric.size - 1 - j] = *(p + j);
        }
      }
      else
      {
        for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
        {
          array[IR->intmetric.size - 1 - j] = *(p + sizeof(int) - 1 - j);
        }
      }
    }
    break;
    case TYPE_CHAR:
    case TYPE_UCHAR:
    {
      p = &(v->c);

      array[0] = p[0];
    }
    break;
    case TYPE_REAL:
    {
      p = &(v->f);

      if(g_is_big_endian)
      {
        for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
        {
          array[IR->intmetric.size - 1 - j] = *(p + j);
        }
      }
      else
      {
        for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
        {
          array[IR->intmetric.size - 1 - j] = *(p + sizeof(int) - 1 - j);
        }
      }
    }
    default:
    {
      printf("assign_with_byte_unit type unsupport\n");
    }
  }
}


void load_with_byte_unit(int type, unsigned char *array, Value v)
{
  int j = 0;
  unsigned char *p = NULL;

  switch(type)
  {
    case TYPE_INTEGER:
    case TYPE_BOOLEAN:
    {
      p = &(v->i);

      if(g_is_big_endian)
      {
        for(j = 0; j < IR->intmetric.size; j++)
        {
          *(p + j) = array[IR->intmetric.size - 1 - j];
        }
      }
      else
      {
        for(j = 0; j < IR->intmetric.size; j++)
        {
          *(p + sizeof(int) - 1 - j) = array[IR->intmetric.size - 1 - j];
        }
      }
    }
    break;
    case TYPE_UINTEGER:
    {
      p = &(v->ui);

      if(g_is_big_endian)
      {
        for(j = 0; j < IR->intmetric.size; j++)
        {
          *(p + j) = array[IR->intmetric.size - 1 - j];
        }
      }
      else
      {
        for(j = 0; j < IR->intmetric.size; j++)
        {
          *(p + sizeof(int) - 1 - j) = array[IR->intmetric.size - 1 - j];
        }
      }
    }
    break;
    case TYPE_CHAR:
    case TYPE_UCHAR:
    {
      p = &(v->c);

      p[0] = array[0];
    }
    break;
    case TYPE_REAL:
    {
      p = &(v->f);

      if(g_is_big_endian)
      {
        for(j = 0; j < IR->intmetric.size; j++)
        {
          *(p + j) = array[IR->intmetric.size - 1 - j];
        }
      }
      else
      {
        for(j = 0; j < IR->intmetric.size; j++)
        {
          *(p + sizeof(int) - 1 - j) = array[IR->intmetric.size - 1 - j];
        }
      }
    }
  }
}