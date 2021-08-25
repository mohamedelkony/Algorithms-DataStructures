#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <stdio.h>
#include <string.h>
#include<limits.h>
#include <stdlib.h>
#include <assert.h>

#define Dqueue
#define COUNT 10


typedef struct _node
{
	int data; struct _node *left; struct _node *right;
}bstNode;

bstNode* newBstNode(int);
bstNode* serach_ref(bstNode*, int); int serach(bstNode*,int);
bstNode* findmin(bstNode*);
bstNode* getInorederSuccessor(bstNode*, int);
bstNode* newBstTreeUtil(int*,int,int);

int findHeight(bstNode*);
int findHeight(bstNode*);
int* inOrderTraversArrayUtil(bstNode*,int*,int*);
int nodesCount(bstNode*);

void balanceBST(bstNode**);

#ifdef Dqueue
typedef struct _qnode
{
	bstNode* data;
	struct _qnode* next;
}qnode;

typedef struct _queue
{
	qnode* front;
	qnode* rear;
}queue;

queue* newQueue()
{
	queue* q = malloc(sizeof(queue));
	q->front = NULL; q->rear = NULL;
	return q;
}

void enqueue(queue* q, bstNode* data)
{
	qnode* n = malloc(sizeof(qnode));
	n->data = data; n->next = NULL;
	if (q->front == NULL)
	{
		q->front = q->rear = n;
	}
	else
	{
		q->rear->next = n;
		q->rear = n;
	}
}
bstNode* dequeue(queue* q)
{
	assert(q->front != NULL);
	bstNode* data = q->front->data;
	qnode* formerFront = q->front;
	if (formerFront->next == NULL)
		q->rear = NULL;
	q->front = formerFront->next;
	free(formerFront);
	return data;
}
bstNode* getFront(queue* q)
{
	return q->front->data;
}
int rear(queue* q)
{
	return q->rear->data;
}
int isEmpty(queue* q)
{
	return q->front == NULL;
}
int isFull(queue* q)
{
	return 0;
}
void printQueue(queue* q)
{
	qnode* n = q->front;
	while (n != NULL)
	{
		printf("*(%x)=%d<<",n->data, n->data->data);
		n = n->next;
	}

}
#endif // DEBUG



bstNode* newBstNode(int data)
{
	bstNode* v = malloc(sizeof(bstNode));
	v->data = data;
	v->left = v->right = NULL;
	return v;
}

bstNode* findmin(bstNode* root)
{
	assert(root != NULL);
	if (root->left == NULL)return root;

	return findmin(root->left);
}
int findmax(bstNode* root)
{
	assert(root != NULL);
	if (root->right == NULL)return root->data;
	return findmax(root->right);
}
int findHeight(bstNode* root)
{
	if (root == NULL)return -1;
	int lefth = findHeight(root->left);
	int righth = findHeight(root->right);
	if (lefth > righth)
		return lefth+1;
	return righth+1;

}
int nodesCount(bstNode* root)
{
	if (root == NULL)return 0;
	return nodesCount(root->left) + nodesCount(root->right) + 1;
}
bstNode* getInorederSuccessor(bstNode* root, int data)
{
	//find node of data
	bstNode* nodeOfData = serach_ref(root, data);
	assert(nodeOfData != NULL);

	if (nodeOfData->right != NULL)
		{return findmin(nodeOfData->right);}

		

	bstNode* val =NULL;
	bstNode* crnt_val = root;
	while (crnt_val->data !=data)
	{
		if (data < crnt_val->data)
		{
			val = crnt_val;
			crnt_val = crnt_val->left;
		}
		else
		{
			crnt_val = crnt_val->right;
		}
	}
	return val;
}

int serach(bstNode* root, int data)
{
	if (root->data == data)
		return 1;

	if (data < root->data)
	{
		if (root->left == NULL)return 0;
		return serach(root->left, data);
	}
	else
	{
		if (root->right == NULL) return 0;
		return serach(root->right, data);
	}
}
bstNode* serach_ref(bstNode* root, int data)
{
	assert(root != NULL);

	if (root->data == data)	return root;

	if (data < root->data)
	{
		if (root->data == NULL)return NULL;
		return serach_ref(root->left, data);
	}
	else
	{
		if (root->right == NULL) return NULL;
		return serach_ref(root->right, data);
	}
}

void insert(bstNode** rootRef, int data)
{	
	bstNode *root = *rootRef;
	if (*rootRef == NULL)
	{
		*rootRef = newBstNode(data);
	}
	else if (data <= (*rootRef)->data)
	{
		insert(&(*rootRef)->left, data);
	}
	else
	{
		insert(&(*rootRef)->right, data);
	}
}
void delete(bstNode** rootPtr, int data)
{
	bstNode *root = *rootPtr;
	assert(root != NULL);
	if (data < root->data)delete(&(*rootPtr)->left, data);
	else if (data>root->data)delete(&(*rootPtr)->right, data);
	else
	{
		if (root->left == NULL && root->right == NULL)
		{
			bstNode* temp = root;
			*rootPtr = NULL;
			free(temp);
		}
		else if (root ->left ==NULL)
		{
			bstNode* temp = *rootPtr;
			*rootPtr = root->right;
			free(temp);
		}
		else if (root->right == NULL)
		{
			bstNode *temp = *rootPtr;
			*rootPtr = root->left;
			free(temp);
		}
		else
		{
			bstNode* minNode = findmin(root->right);
			(*rootPtr)->data = minNode->data;
			delete(&(*rootPtr)->right, minNode->data);
		}
	}
}

void levelOrderTraversal(bstNode* root)
{
	assert(root != NULL);
	queue *q = newQueue();
	enqueue(q, root);
	while (!isEmpty(q))
	{
		bstNode* front = getFront(q);
		if (front->left != NULL)enqueue(q, front->left);
		if (front->right != NULL)enqueue(q, front->right);
		printf("%d >>", front->data);
		dequeue(q);
	}
}
void preOrderTraversal(bstNode* root)
{
	if (root == NULL){return;}
	printf("%d ", root->data);
	preOrderTraversal(root->left);	
	preOrderTraversal(root->right);
}
void inOrederTraversal(bstNode* root)
{
	if (root == NULL){ return; }
	inOrederTraversal(root->left);
	printf("%d ", root->data);
	inOrederTraversal(root->right);
}

int* inOrderTraversArrayUtil(bstNode* root,int *arr,int *i)
{
	if (root == NULL){ return; }
	inOrderTraversArrayUtil(root->left, arr, i);
	arr[*i]= root->data;
	(*i)++;
	inOrderTraversArrayUtil(root->right, arr, i);
}

int* inOrderTraversArray(bstNode* root,int* arrayCount)
{
	*arrayCount = nodesCount(root);
	int *arr = malloc(sizeof(int)*(*arrayCount));
	int i = 0;
	inOrderTraversArrayUtil(root, arr, &i);
	return	arr;
}
void postOrederTraversal(bstNode* root)
{
	if (root == NULL)return;
	postOrederTraversal(root->left);
	postOrederTraversal(root->right);
	printf("%d ", root->data);
}

int isBSTutil(bstNode* root, int minValue, int maxValue)
{
	if (root == NULL)return 1;
	if (root->data >= minValue &&root->data <= maxValue
		&& isBSTutil(root->left, minValue, root->data)
		&& isBSTutil(root->right, root->data, maxValue))
		return 1;
	return 0;
}
int isBinarySerachTree(bstNode* root)
{
	return isBSTutil(root, INT_MIN, INT_MAX);
}

void print2DUtil(bstNode *root, int space)
{
	// Base case 
	if (root == NULL)
		return;

	// Increase distance between levels 
	space += COUNT;

	// Process right child first 
	print2DUtil(root->right, space);

	// Print current node after space 
	// count 
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", root->data);

	// Process left child 
	print2DUtil(root->left, space);
}


bstNode* BstTreeOfArrayUtil(int arr[], int leftIndex, int rightIndex)
{
	if (leftIndex > rightIndex)
		return NULL;
	int mid = leftIndex + (rightIndex - leftIndex) / 2;
	bstNode* root = newBstNode(arr[mid]);
	root->left = BstTreeOfArrayUtil(arr, leftIndex, mid - 1);
	root->right = BstTreeOfArrayUtil(arr, mid + 1, rightIndex);
	return root;
}
bstNode* BstTreeOfArray(int arr[], int count)
{
	return BstTreeOfArrayUtil(arr, 0, count - 1);
}

void balanceBST(bstNode** root)
{
	int count = 0;
	int* arr = inOrderTraversArray(*root, &count);
	*root = BstTreeOfArray(arr,count);
	free(arr);
}
// Wrapper over print2DUtil() 
void print2D(struct Node *root)
{
	// Pass initial space count as 0 
	print2DUtil(root, 0);
}

int main()
{
	bstNode *x = NULL;

	insert(&x, 100); insert(&x, 50); insert(&x, 25);
	insert(&x, 75); insert(&x, 150); insert(&x, 125); insert(&x, 200);
	while (1)
	{
		printf("1>insert,2>serarch,3>print,4->min,5->max,6->height,7->level order,8PreT,9inT\n10postT,11->isBST?,12->delete,13->inOrderS,14->from array,15->#ofnodes,16->balance\n"); fflush(stdin);
		int command; scanf("%d", &command); int in1;
		switch (command)
		{
		case 1:
			printf("enter value\n"); fflush(stdin); scanf("%d", &in1);
			insert(&x, in1);
			break;
		case 2:
			fflush(stdin); scanf("%d", &in1);
			printf("%d = %d\n", in1,serach(x,in1));
			break;
		case 3:
			print2D(x);
			break;
		case 4:
			printf("%d", findmin(x)->data);
			break;
		case 5:
			printf("%d", findmax(x));
			break;
		case 6:printf("%d", findHeight(x)); break;
		case 7:levelOrderTraversal(x); break;
		case 8:preOrderTraversal(x); break;
		case 9:inOrederTraversal(x); break;
		case 10:postOrederTraversal(x); break;
		case 11:printf("%d", isBinarySerachTree(x)); break;
		case 12:
			fflush(stdin); scanf("%d", &in1);delete(&x, in1);	
			break;
		case 13:
			fflush(stdin); scanf("%d", &in1); printf("%d",getInorederSuccessor(x,in1)->data);
			break;
		case 15:
			printf("%d", nodesCount(x));
			break;
		case 16:
			balanceBST(&x);
			break;
		}
		if (command == 20)
		{
			int count = 0;
			int *arr =inOrderTraversArray(x, &count);
			for (int i = 0; i < count; i++)
			{
				printf("%d > ", arr[i]);
			}
			free(arr);
		}
		else if (command == 14)
		{
			fflush(stdin); scanf("%d", &in1);
			int* arr = malloc(in1*sizeof(int));
			for (int i=0; i< in1; i++)
			{
				fflush(stdin);
				scanf("%d",arr+i);
			}
			x = BstTreeOfArray(arr, in1);
			free(arr);
		}
		printf("\n------------------------\n");
	}
	getch();
	return 0;
}