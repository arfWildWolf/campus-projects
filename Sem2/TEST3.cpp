#include <stdio.h>
#include <stdlib.h>

struct LL{
	int ID;
	int HP;
	
	LL *NEXT, *PREV;
	
	
}*HEAD, *TAIL;

LL* createLL(int ID, int HP){
	LL* newLL = (LL*)malloc(sizeof(LL));
	newLL->ID = ID;
	newLL->HP = HP;
	
	newLL->NEXT = newLL->PREV = NULL;
	
	return newLL;
}

void pushHead(int ID, int HP){
	
	struct LL *curr=HEAD;
	struct LL *push= createLL(ID, HP);
	
	if(HEAD==NULL){
		
		HEAD=TAIL=push;
		puts("HEAD MADE!");
		
	}
	else{
		curr->PREV = push;
		push->NEXT = curr;
		HEAD=push;
	}
	
	
	
}

void pushMid(int ID, int HP){
	
	struct LL *curr=HEAD;
	struct LL *push= createLL(ID, HP);
	
	if(HEAD==NULL){
		
		HEAD=TAIL=push;
		puts("HEAD MADE!");
		
	}
	else{
		while(curr!=NULL){
//			printf("%d %d\n", push->ID, curr->ID);
			if(push->ID<curr->ID){
				curr->PREV->NEXT =push;
				push->PREV=curr->PREV;
				
				curr->PREV=push;
				push->NEXT=curr;
				return;
			}
			else{
				curr=curr->NEXT;
			}
		}
	}
	
	
	
}

void display(){
	struct LL *curr=HEAD;
	if(HEAD==NULL){
		puts("BONK! HEAD EMPTY!");
	}
	else{
		while(curr!=NULL){
			printf("%d %d\n", curr->ID, curr->HP);
			curr=curr->NEXT;
		}
	}
}

int main(){
	struct LL *curr;
	display();
	pushHead(40, 10);
	pushHead(10, 1);
	
	pushMid(20, 1);
	display();
	
	return 0;
}
