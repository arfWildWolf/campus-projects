#include <stdio.h>
#include <stdlib.h>

struct BST{
	
	int num;

	BST *left, *right;	
	
};

void insert(BST **curr, int num){
	if(*curr==NULL){
		*curr = (BST*) malloc(sizeof(BST));
		(*curr)->num = num;
		(*curr)->left = (*curr)->right = NULL;
		return;
	}
	if(num>(*curr)->num){
		insert(&(*curr)->right, num);
		return;
	}
	if(num<(*curr)->num){
		insert(&(*curr)->left, num);
		return;
	}

}

void preOrder(BST *curr){
	if(curr!=NULL){
		printf("%d ", curr->num);
		preOrder(curr->left );
		preOrder(curr->right );
	}
}

void inOrder(BST *curr){
	if(curr!=NULL){
		
		inOrder(curr->left );
		printf("%d ", curr->num);
		inOrder(curr->right );
	}
}

void postOrder(BST *curr){
	if(curr!=NULL){
		
		postOrder(curr->left );
		postOrder(curr->right );
		printf("%d ", curr->num);
	}
}

BST* findNum(BST *curr, int find){
	if(curr==NULL||curr->num==find){
		return curr;
	}
	if(find>curr->num){
//		curr =  curr->right;
		return findNum(curr->right, find);
	}
	else{
//		curr=curr->left;
		return findNum(curr->left, find);
	}
	
}
BST* findRightMost(BST *curr){//predecessor
	while(curr->right!=NULL){
		curr=curr->right;
	}
	return curr;
}

void pop(BST **curr, int num){
	if(*curr==NULL){
		return;
	}	
	if(num < (*curr)->num){
		pop(&(*curr)->left, num);
		return;
	}
	if(num>(*curr)->num){
		pop(&(*curr)->right, num);
		return;
	}
	
	//case 1, no child // is a leaf
	if((*curr)->left==NULL&&(*curr)->right==NULL){
		free(*curr);
		*curr=NULL;
		return;
	}
	if((*curr)->right==NULL){
		
		(*curr)->num= (*curr)->left->num;
		pop(&(*curr)->left, (*curr)->num);
		return;
	}
	if((*curr)->left==NULL){
		
		(*curr)->num= (*curr)->right->num;
		pop(&(*curr)->right, (*curr)->num);
		return;
	}
	else{
		BST *predecessor = findRightMost((*curr)->left );
		(*curr)->num= predecessor->num;
		pop(&(*curr)->left, predecessor->num);
	}
}


int main(){
	BST *root = NULL;
	insert(&root, 10);
	insert(&root, 5);
	insert(&root, 20);
	insert(&root, 7);
	insert(&root, 17);
	
	pop(&root, 10);
	
	BST *result=findNum(root, 7);
	if(result==NULL){
		puts("NOT FOUND");
	}
	else printf("result %d\n", result->num);
	
	printf("Preorder : ");
	preOrder(root);
	puts("");
	
	printf("Pnorder : ");
	inOrder(root);
	puts("");
	
	printf("Postorder : ");
	postOrder(root);
	puts("");
//	
	return 0;
}
