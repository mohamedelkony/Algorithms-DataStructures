#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef struct _stacknode
{
	int data;
	struct _stacknode* next;
}stackNode;
	
void lpush(stackNode** root, int data)
{
	stackNode* sn = malloc(sizeof(stackNode));
	sn->data = data;
	sn->next = *root;
	*root = sn;
}
int lpop(stackNode **root)
{
	int popped = (*root)->data;
	stackNode* temp = *root;
	*root = (*root)->next;
	free(temp);
	return popped;
}
int lpeak(stackNode* root){ return root->data; }
int lisEmpty(stackNode* root){ return root == NULL; }
int lisFull(stackNode* root){ return 0; }
static int maintest()
{
	stackNode* root = malloc(sizeof(stackNode));
	root->data = 5;
	while (1)
	{
		printf("1>push,2>pop,3>peek,4>isfull,5>isempty\n"); fflush(stdin);
		int command; scanf("%d", &command); int in1;
		switch (command)
		{
		case 1:
			printf("enter value\n"); fflush(stdin); scanf("%d", &in1);
			lpush(&root, in1);
			break;
		case 2:
			printf("pop of stack=%d\n", lpop(&root));
			break;
		case 3:
			printf("peek of stacck=%d\n", lpeak(root));
			break;
		case 4:
			printf("is full =%d\n", lisFull(root));
			break;
		case 5:
			printf("is empty =%d\n", lisEmpty(root));
			break;
		}
	}
	getch();
	return 0;
}