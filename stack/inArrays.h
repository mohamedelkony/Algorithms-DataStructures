struct _stack
{
	int top;
	unsigned capacity;
	int *data;
};
typedef struct _stack stack;
stack* newStack(unsigned );

int peak(stack* );

int pop(stack* );

int push(stack*, int);

int isEmpty(stack*);
int isFull(stack*);