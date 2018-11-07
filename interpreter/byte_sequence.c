#include "../common.h"

void assign_with_byte_unit(int type, unsigned char *array, Value v)
{
  int j = 0;
  unsigned char *p = NULL;

  switch(type)
  {
    case TYPE_INTEGER:
    {
      p = &(v->i);

      if(g_is_big_endian)
      {
        for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
        {
         array[IR->intmetric.size - 1 - j] = *(p + sizeof(int) - 1 - j);
         // printf("big endian %d %d", IR->intmetric.size -1 - j, array[IR->intmetric.size -1 - j]);
        }
      }
      else
      {
        for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
        {
          array[IR->intmetric.size -1 - j] = *(p + j);
          // printf("little endian %d %d", IR->intmetric.size -1 - j, array[IR->intmetric.size -1 - j]);
        }
      }
    }
    break;
    case TYPE_CHAR:
    case TYPE_BOOLEAN:
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
          array[IR->intmetric.size - 1 - j] = *(p + sizeof(int) - 1 - j);
        }
      }
      else
      {
        for(j = 0; j < IR->intmetric.size && j < sizeof(int); j++)
        {
          array[IR->intmetric.size -1 - j] = *(p + j);
        }
      }
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
    {
      p = &(v->i);

      if(g_is_big_endian)
      {
        for(j = 0; j < IR->intmetric.size; j++)
        {
          *(p + sizeof(int) - 1 - j) = array[IR->intmetric.size - 1 - j];
        }
      }
      else
      {
        for(j = 0; j < IR->intmetric.size; j++)
        {
          *(p + j) = array[IR->intmetric.size -1 - j];
        }
      }
    }
    break;
    case TYPE_CHAR:
    case TYPE_BOOLEAN:
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
          *(p + sizeof(int) - 1 - j) = array[IR->intmetric.size - 1 - j];
        }
      }
      else
      {
        for(j = 0; j < IR->intmetric.size; j++)
        {
          *(p + j) = array[IR->intmetric.size -1 - j];
        }
      }
    }
  }
}