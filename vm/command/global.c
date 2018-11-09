#include "../common.h"

#define GLOBAL_LENGTH 256

/*  */
unsigned char global_queue[GLOBAL_LENGTH];

void assign_global(int index, unsigned char val)
{
  global_queue[index] = val;
}

unsigned char load_global(int index)
{
  return global_queue[index];
}