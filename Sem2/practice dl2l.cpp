#include <stdio.h>
#include <stdlib.h>

struct DLL{
	
	int num;
	
	DLL *next, *prev;
	
	
} *head, *tail;

struct DLL* createDLL(int num){
	
	struct DLL* newDLL = (DLL*)malloc(sizeof(DLL));
	newDLL->num=num;
	newDLL->next=newDLL->prev=NULL;
	
	return newDLL;
}

void pushHead(int num){
	DLL *temp = createDLL(num);
	DLL *curr = head;
	
	if(head==NULL){
		head=tail=temp;
		return;
	}
	while(curr->next!=NULL){
		curr=curr->next;
	}
	curr->next = temp;
	curr->next->prev = curr;
	
}

void printALL(){
	
	DLL *curr=head;
	
	if(head==NULL){
		puts("HEAD EMPTY!!");
		return;
	}
	
	while(curr!=NULL){
		printf("%d -> ", curr->num);
		curr=curr->next;
	}
	
	puts("");
	return;
}



int main(){
	printALL();
	
	pushHead(1);
//	printf("%d -> ", head->num);
	printALL();
	pushHead(2);
//	printf("%d -> ", head->num);
	printALL();
	pushHead(3);
//	printf("%d -> ", head->num);
	printALL();
	pushHead(4);
//	printf("%d -> ", head->num);
	
	printALL();
	return 0;
}
