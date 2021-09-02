#include"stack.h"
#ifdef ARRAY_STACK
#include<stdlib.h>
#include<assert.h>
#include<limits.h>

#define INITIAL_SIZE 32
#define ARRAY_STACK_MAX_SIZE INT_MAX*2

struct _stack
{
	int top;
	unsigned capacity;
	data_type* data;
};

//typedef struct _stack stack;

stack* newStack()
{
	stack* thisStack = malloc(sizeof(stack));
	thisStack->capacity = INITIAL_SIZE;
	thisStack->top = -1;
	thisStack->data = malloc(thisStack->capacity*sizeof(data_type));
	assert(thisStack->data != NULL);
	return thisStack;
}
data_type peak(stack* s)
{
	return s->data[s->top];
}
data_type pop(stack* s)
{
	assert(!isEmpty(s));
	return s->data[s->top--];
}
void push(stack* s,const data_type num)
{
	if (s->top == s->capacity - 1)
	{
		s->capacity *= 2;
		s->data = (data_type*)realloc(s->data,s->capacity*sizeof(*(s->data)));
	}
	s->data[++s->top] = num;
}
int isEmpty(const stack* s){ return s->top == -1; }
int isFull(const stack* s){ return s->top == s->capacity - 1; }
#endif