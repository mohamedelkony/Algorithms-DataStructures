
#include<stdlib.h>
#include<assert.h>

struct _stack
{
	int top;
	unsigned capacity;
	int *data;
};
typedef struct _stack stack;

stack* newStack(unsigned capacity)
{
	stack* thisStack = malloc(sizeof(stack));
	thisStack->capacity = capacity;
	thisStack->top = -1;
	thisStack->data = malloc(capacity*sizeof(int));
	assert(thisStack->data != NULL);
	return thisStack;
}
int peak(stack* s)
{
	return s->data[s->top];
}
int pop(stack* _stack)
{
	assert(!_stack->top< 0);
	return _stack->data[_stack->top--];
}
int push(stack* s, int num)
{
	assert(s->top+1 < s->capacity);
	s->data[++s->top] = num;
}
int isEmpty(stack* s){ return s->top == -1; }
int isFull(stack* s){ return s->top == s->capacity - 1; }

/*
static int maintest()
{
	stack* s = newStack(10);
	while (1)
	{
		printf("1>push,2>pop,3>peek,4>isfull,5>isempty\n"); fflush(stdin);
		int command; scanf("%d", &command); int in1;
		switch (command)
		{
		case 1:
			printf("enter value\n"); fflush(stdin);scanf("%d", &in1);
			push(s, in1);
			break;
		case 2:
			printf("pop of stack=%d\n", pop(s));
			break;
		case 3:
			printf("peak of stack=%d\n", peak(s));
			break;
		case 4:
			printf("is full =%d\n", isFull(s));
			break;
		case 5:
			printf("is empty =%d\n", isEmpty(s));
			break;
		}
	}
	getch();
	return 0;
}
*/