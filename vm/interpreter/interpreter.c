#define MAX_CODE_NUM 10 * 1024

int byte_sequence_index = 0;
unsigned char byte_sequence[MAX_CODE_NUM];

void interpret()
{
	int index = 0;
  while(index < byte_sequence_index)
  {
      printf("%x ", byte_sequence[index++]);
  }
}