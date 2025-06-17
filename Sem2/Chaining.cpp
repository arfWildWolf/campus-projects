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
	student *next;
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
	data->next = NULL;
	student* curr = maps[hash_number];
	if(maps[hash_number]==NULL){
	maps[hash_number]=data;
	return;
	}
	
	else while(curr->next!=NULL){
		curr=curr->next;
		
	}
	curr->next=data;
	
}

void printTable(){
	for(int i=0; i<TABLE_SIZE; i++){
		student *curr = maps[i];
		if(maps[i]==NULL){
			printf("Map[%d] empty\n", i);
			continue;
		}
		printf("Map[%d]", i);
		while(curr!=NULL){
			printf(" -> key %s: %d", curr->key, curr->score);
			curr=curr->next;
		}
		puts("");
	}
}

student* get(char key[]){
	int hash_number = hash(key);
	student *curr = maps[hash_number];
	while(curr!= NULL){
		if(strcmp(curr->key, key)==0){
			return curr;
		}
		curr=curr->next;
	}
	
	return NULL;
	
}

void unset(char key[]){
	int hash_number = hash(key);
	student* curr = maps[hash_number];
	if(maps[hash_number]==NULL) return;
	student* toDel = maps[hash_number];
	if(strcmp(maps[hash_number]->key, key)==0){
		curr=curr->next;
		free(maps[hash_number]);
		maps[hash_number]=curr;
		return;
	}
	while(curr->next!=NULL){
		if(strcmp(curr->next->key, key)==0){
			student* toDel = curr->next;
			curr->next=curr->next->next;
			free(toDel);
			return;
		}
		curr=curr->next;
	}
	
	
}

int main(){
	
	set("budi", 10);
	set("bagas", 2);
	set("bajaj", 3);
	unset("budi");
	unset("bagas");
	
	student *result = get("bagas");
	if(result != NULL){
		printf("Score of %s is %d\n", result->key , result->score);
		
	}
	else{
		puts("Not found!");
	}
	
	printTable();
	
//	printf("%s %d\n", maps[hash("budi")]->key, maps[hash("budi")]->score);
//	printf("%s %d\n", maps[hash("bagas")]->key, maps[hash("bagas")]->score);
//	printf("%d", hash("Budi"));
}
