#include "../common.h"

void assign_with_byte_unit(int type, unsigned char *array, Value v)
{
  int j = 0;
  unsigned char *p = NULL;

  if(type == TYPE_INTEGER || type == TYPE_BOOLEAN)
  {
    if(type = TYPE_BOOLEAN)
    {
      v->i = v->b;
    }

    int i_tmp = v->i;
    p = &i_tmp;

    if(TYPE_BYTE_DEBUG)
    {
      printf("origin host integer value is %d, byte sequence is ", i_tmp);
      for(int i = 0; i < sizeof(int); i++)
      {
        printf("%x ", *(p + i));
      }
      printf("\n");
    }

    /* negative */
    if(v->i < 0)
    {
      /* complement to abs */
      i_tmp = ~(i_tmp - 1);
      
      if(g_is_big_endian)
      {
        /* 01111111 */
        p[sizeof(int) - 1] &= 0x7f;
      }
      else
      {
        /* 01111111 */
        p[0] &= 0x7f;
      }
    }

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

    /* negative */
    if(v->i < 0)
    {
      int carry_mark = 1;
      /* abs to complement(without sign bit) */
      for(int i = IR->intmetric.size - 1; i >= 0; i--)
      {
        /* reverse */
        array[i] ^= 0xff;

        /* carry */
        if(carry_mark == 1)
        {
          
          if(array[i] == 0xff)
          {
            carry_mark = 1;
          }
          else
          {
            carry_mark = 0;
          }

          array[i] += 1;
        }
      }
      /* assign sign bit */
      array[0] |= 0x80;  
    }

    if(TYPE_BYTE_DEBUG)
    {
      printf("target vm integer byte sequence is ");
      for(int i = 0; i < IR->intmetric.size; i++)
      {
        printf("%x ", array[i]);
      }
      printf("\n");
    }
  }
  else
  {
    switch(type)
    {
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
      {
        array[0] = v->c;
      }
      break;
      case TYPE_UCHAR:
      {
        array[0] = v->uc;
      }
      break;
      case TYPE_REAL:
      {     
        p = &(v->f);

        if(g_is_big_endian)
        {
          for(j = 0; j < IR->intmetric.size && j < sizeof(float); j++)
          {
            array[IR->intmetric.size - 1 - j] = *(p + j);
          }
        }
        else
        {
          for(j = 0; j < IR->intmetric.size && j < sizeof(float); j++)
          {
            array[IR->intmetric.size - 1 - j] = *(p + sizeof(float) - 1 - j);
          }
        }
      }
      default:
      {
        printf("assign_with_byte_unit type unsupport\n");
      }
    }
  }
}


void load_with_byte_unit(int type, unsigned char *array, Value v)
{
  int j = 0;
  unsigned char *p = NULL;

  if(type == TYPE_INTEGER || type == TYPE_BOOLEAN)
  {
    if(TYPE_BYTE_DEBUG)
    {
      printf("origin vm integer byte sequence is ");
      for(int i = 0; i < IR->intmetric.size; i++)
      {
        printf("%x ", array[i]);
      }
      printf("\n");
    }

    unsigned char uc_tmp[IR->intmetric.size];

    /* negative */
    if(array[0] & 0x80 > 0)
    {
      /* dup */
      for(int i = 0; i < IR->intmetric.size; i++)
      {
        uc_tmp[i] = array[i];
      }

      /* complement to abs */
      int carry_mark = 1;
      for(int i = IR->intmetric.size - 1; i >= 0; i--)
      {
        /* carry */
        if(carry_mark)
        {
          if(uc_tmp[i] == 0x00)
          {
            carry_mark = 1;
          }
          else
          {
            carry_mark = 0;
          }

          uc_tmp[i] -= 1;
        }

        /* reverse */
        uc_tmp[i] ^= uc_tmp[i];
      }

      /* sign bit */
      uc_tmp[0] &= 0x7f;
    }

    /*  */
    if(type == TYPE_BOOLEAN)
    {
      v->i = v->b;
    }
    
    p = &(v->i);

    if(g_is_big_endian)
    {
      for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
      {
        *(p + sizeof(int) - 1 - j) = array[j];
      }
    }
    else
    {
      for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
      {
        *(p + j) = array[j];
      }
    }

    /* negative */
    if(array[0] & 0x80 > 0)
    {
      if(g_is_big_endian)
      {
        *(p + sizeof(int) - 1) |= 0x80;
      }
      else
      {
        *p |= 0x80;
      }
    }

    if(TYPE_BYTE_DEBUG)
    {
      printf("target host integer value is %d, byte sequence is ", v->i);
      for(int i = 0; i < sizeof(int); i++)
      {
        printf("%x ", *(p + i));
      }
      printf("\n");
    }
  }
  else
  {
    switch(type)
    {
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
      {
        v->c = array[0];
      }
      break;
      case TYPE_UCHAR:
      {
        v->uc = array[0];
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
            *(p + sizeof(float) - 1 - j) = array[IR->intmetric.size - 1 - j];
          }
        }
      }
    }
  }
}