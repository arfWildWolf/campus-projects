#include <stdio.h>
#include <stdlib.h>

struct avl{
	int x;
	struct avl* left;
	struct avl* right;
	
	int h;//height
};



struct avl* createAvl(int x){
	struct avl* newavl=(avl*)malloc(sizeof(avl));
	newavl->x=x;
	newavl->h=1;
	newavl->left=newavl->right=NULL;
	return newavl;
}

void LLRot(struct avl* root){
	root->left->right=root;
	root->left=NULL;
}

void RRRot(struct avl* root){
	root->right->left=root;
	root->right=NULL;
}

void LRRot(struct avl* root){
	root->left->right->right=root;
	root->left->right->left=root->left;
	root->left=NULL;
}

void RLRot(struct avl* root){
	root->right->left->left=root;
	root->right->left->right=root->right;
	root->right=NULL;
}


int max(int x, int y){
	if(x>y) return x;
	else return y;
}



int weightl(struct avl* p) {
	if(p==NULL) return 0;
	int height = p->left->h - p->right->h;
//	printf("%d->", p->x);
return height;	
}

int getheight(struct avl* p){
	if(p==NULL) return 0;
	return p->h;
}

struct avl* insert(struct avl* p, int x){
	if(p==NULL) {
	
	
	return createAvl(x);	
	}
	else if(x>p->x) p->right=insert(p->right, x);
	else if(x<p->x) p->left=insert(p->left, x);
	else return p;
	
	

	p->h=max(getheight(p->left), getheight(p->right))+1;
	
	int weight=weightl(p);
	
	
	
	if(weight>1){
		if(weightl(p->left)>0) LLRot(p);
		else if(weightl(p->left<0))LRRot(p);
		else puts("wtf happened");

	}
	else if(weight<1){
	if(weightl(p->right)>0) RLRot(p);
		else if(weightl(p->right<0))RRRot(p);
		else puts("wtf happened");
	}
	
}

void printAll(struct avl* p){
	if(p==NULL) return;
	printAll(p->left );
	printf("%d->", p->x);
	printAll(p->right );
}

int main(){
	struct avl* root=NULL;
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 3);
//printf("%d->", root->x);
//	root->x=1;
	printAll(root);
	return 0;
}
