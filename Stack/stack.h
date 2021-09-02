#ifndef STACK_H
#define LINKEDLIST_STACK

//#define ARRAY_STACK
#define STACK_H

typedef	float data_type;
typedef int(*comparator)(const void*, const void*);

/**********************************
* incomplete data type
* struct _stack implementation depends on .c file used
**********************************/
typedef struct _stack stack;

stack* newStack();


data_type peak(const stack*);
data_type pop(stack*);
void push(stack*,const data_type);
int isEmpty(const stack*);
int isFull(const stack*);


#endif