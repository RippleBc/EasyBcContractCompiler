#include "../common.h"

#define GLOBAL_LENGTH 256

/*  */
unsigned char global_queue[GLOBAL_LENGTH];

void ASSIGN_GLOBAL(int index, unsigned char val)
{
	for(int i = 0; i < 4; i++)
	{
		global_queue[index] = val;
	}
  
}

unsigned char LOAD_GLOBAL(int index)
{
  return &global_queue[index];
}