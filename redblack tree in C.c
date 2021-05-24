#include<stdio.h>
#include<stdlib.h>

struct node{
	struct node* left;
	struct node* right;
	struct node* p;
	int data;
	char x;

};

struct node* NewNode(int data){
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->left = NULL;
	temp->right = NULL;
	temp->p = NULL;
	temp->data = data;
	temp->x = 'R';
	
	return temp;

}

struct node* CHANGECOLOR(struct node* temp){
	if(temp->x == 'B')temp->x = 'R';
	else temp->x = 'B';
	return temp;

}
void RIGHTROTATE(struct node* temp){
	struct node* x = temp->left;
	struct node* y = x->right;
	x->right=temp;
	temp->left = y;
	x->p = temp->p;
	if(y != NULL)y->p = temp;
	temp->p = x;
	if(x->p != NULL && x->p->left == temp)x->p->left = x;
	else if(x->p != NULL)x->p->right =x;
	
	
}

void LEFTROTATE(struct node* temp){
	struct node* x = temp->right;
	struct node* y = x->left;
	x->left = temp;
	temp->right = y;
	x->p = temp->p;
	if(y!= NULL)y->p = temp;
	temp->p = x;
	if(x->p != NULL && x->p->left == temp)x->p->left = x;
	else if(x->p != NULL)x->p->right =x;
	
}

void PRINTTREE(struct node* A){
	if(A == NULL){
		printf("( )");
		return;
	}
	printf("(");
	printf(" %d %c ",A->data,A->x);
	PRINTTREE(A->left);
	printf(" ");
	PRINTTREE(A->right);
	printf(" )");
}
struct node* REDCHANGE(struct node* head,struct node* z){
	while(z->p != NULL && z->p->x == 'R'){
		if(z->p == z->p->p->left){
			struct node* y = z->p->p->right;
			if(y == NULL || (y !=NULL && y->x == 'B')){
				if(z == z->p->right){
					z = z->p;
					LEFTROTATE(z);
				}
				z->p = CHANGECOLOR(z->p);
				z->p->p = CHANGECOLOR(z->p->p);
				if(z->p->p == head)head = z->p;
				RIGHTROTATE(z->p->p);
			}
			else if(y->x == 'R'){
				y->x = 'B';
				z->p->x = 'B';
				if(z->p->p != head ){
				z->p->p->x = 'R';
				}
				z=z->p->p;
			}
			
		}
		else{
			struct node* y = z->p->p->left;
			if(y == NULL || (y !=NULL && y->x == 'B')){
				if(z == z->p->left){
					z = z->p;
					RIGHTROTATE(z);
				}
				z->p = CHANGECOLOR(z->p);
				z->p->p = CHANGECOLOR(z->p->p);
				if(z->p->p == head)head = z->p;
				LEFTROTATE(z->p->p);
			}
			else if(y->x == 'R'){
				y->x = 'B';
				z->p->x = 'B';
				if(z->p->p != head ){
				z->p->p->x = 'R';
				}
				z=z->p->p;
			}
		
		
		
		}
	
	
	}
	return head;
	
}
struct node* INSERTREDBLACK(struct node* head,int key){
	if(head == NULL){
		head = NewNode(key);
		head->x = 'B';
		PRINTTREE(head);
		return head;
	}
	struct node* z = NewNode(key);
	struct node* ptr = head;
	struct node* temp = head;
	while(ptr != NULL){
		temp = ptr;
		if(temp->data > key ){
			ptr = ptr->left;
		}
		else ptr = ptr->right;
	}
	if(temp->data > key){temp->left = z;
		z->p = temp;
	}else {temp->right = z;
		z->p = temp;
	}
	
	if(temp->x == 'B'){
		PRINTTREE(head);
		return head;	
	}
	else if(temp->x == 'R'){
		head = REDCHANGE(head,z);
		PRINTTREE(head);
		return head;
	
	}
	
	
	
	
}



void main(){
	struct node* head = NULL;
	int k;
	while(1){
		if(scanf("%d",&k)!=1)break;
		if(k<=0)break;
		head = INSERTREDBLACK(head,k);
		printf("\n");
	}
	
	
	
	
	
	
	
	

}
