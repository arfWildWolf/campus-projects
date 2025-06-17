#include <stdio.h>

int main{
	
	int number=10;
	int *ptr=&number;
	
	*ptr=20;
	printf("Number Value: %d\n", *ptr)
	
	
	return 0;
}
