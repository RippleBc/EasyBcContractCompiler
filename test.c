#include <stdio.h>

int main()
{
	unsigned char *c;
	int a = 10;
	float b = 10;

	c = &a;
	printf("%x \n", *c);
	printf("%x \n", *(c + 1));
	printf("%x \n", *(c + 2));
	printf("%x \n", *(c + 3));

	c = &b;
	printf("%x \n", *c);
	printf("%x \n", *(c + 1));
	printf("%x \n", *(c + 2));
	printf("%x \n", *(c + 3));
}