#include <stdio.h>
#include <string.h>


struct student{
	
	char name[100];
	int score;
	
	
} andi;


int main(){
	
	strcpy(andi.name , "Andi");
	printf("%s\n", andi.name );
	
	return 0;
}
