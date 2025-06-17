#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define TABLE_SIZE 10

struct student{
	char key[100];
	int score;
};

student* maps[TABLE_SIZE];

int hash(char key[]){
	
	char first_char = key[0];
	int hash_number= first_char-'A';
	
	return hash_number%TABLE_SIZE;
}

void set(char key[], int score){
	
	int hash_number = hash(key);
	student* data = (student*)malloc(sizeof(student));
	data->score = score;
	strcpy(data->key, key);
	
	int idx = hash_number;
	do{
		if(maps[idx]==NULL){
			maps[idx]=data;
			return;
		}
		idx=(idx+1)%TABLE_SIZE;
	}
	while(idx!=hash_number);
	
}

void printTable(){
	for(int i=0; i<TABLE_SIZE; i++){
		if(maps[i]==NULL){
			printf("Map[%d] empty\n", i);
			continue;
		}
		printf("Map[%d] key %s: %d\n", i, maps[i]->key, maps[i]->score);
	}
}

student* get(char key[]){
	int hash_number = hash(key);
	int idx = hash_number;
	do{
		if(maps[idx]!=NULL&&strcmp(maps[idx]->key , key)==0){
			return maps[idx];
		}
		idx=(idx+1)%TABLE_SIZE;
	}
	while(idx!=hash_number);
	
	return NULL;
	
}

void unset(char key[]){
	int hash_number = hash(key);
	int idx = hash_number;
	do{
		if(maps[idx]!=NULL&&strcmp(maps[idx]->key , key)==0){
			free(maps[idx]);
			maps[idx]=NULL;
			return;
		}
		idx=(idx+1)%TABLE_SIZE;
	}while(idx!=hash_number);
}

int main(){
	
	set("budi", 10);
	set("bagas", 2);
	
	unset("bagas");
	
	student *result = get("bagas");
	if(result != NULL){
		printf("Score of %s is %d\n", result->key , result->score);
		
	}
	else{
		puts("Not found!");
	}
	
//	printTable();
	
//	printf("%s %d\n", maps[hash("budi")]->key, maps[hash("budi")]->score);
//	printf("%s %d\n", maps[hash("bagas")]->key, maps[hash("bagas")]->score);
//	printf("%d", hash("Budi"));
}
