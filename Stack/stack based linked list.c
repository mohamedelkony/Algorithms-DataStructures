#include"stack.h"
#ifdef LINKEDLIST_STACK
#include<stdlib.h>
#include<assert.h>


typedef struct _stacknode
{
	data_type data;
	struct _stacknode* next;
}stackNode;

struct _stack
{
	stackNode *linked_list;

};

//typedef struct _stack stack;

stack* newStack()
{
	stack* thisStack = malloc(sizeof(stack));
	thisStack->linked_list = NULL;
	return thisStack;
}

void push(stack* s,const data_type data)
{
	stackNode* sn = malloc(sizeof(stackNode));
	sn->data = data;
	sn->next = s->linked_list;
	s->linked_list = sn;
}
data_type pop(stack* s)
{
	assert(isEmpty(s) == 0);
	data_type popped = s->linked_list->data;
	stackNode* temp = s->linked_list;
	s->linked_list = (s->linked_list)->next;
	free(temp);
	return popped;
}
data_type peak(const stack* s){ return s->linked_list->data; }
int isEmpty(const stack* s){ return s->linked_list == NULL; }
int isFull(const stack* s){ return 0; }
#endif
