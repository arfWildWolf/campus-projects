#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
	int mem;
	int *x=&mem;;
	
	scanf("%x", *x);
	
	printf("%d", mem);
	
	return 0;
	
	
	}
