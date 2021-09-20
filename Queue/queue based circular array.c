
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<assert.h>

#define linkedlist
#ifndef linkedlist
typedef struct _queue
{
	int front, rear, size;
	unsigned capacity;	
	int* data;
}queue;

queue* newQueue(unsigned capacity)
{
	queue* q = malloc(sizeof(queue));
	q->capacity = capacity;
	q->front = 0;
	q->size = 0;
	q->rear = q->capacity - 1;
	q->data = malloc(sizeof(int)*capacity);
	return q;
}
int isFull(queue* q)
{
	return q->size == q->capacity;
}
int isEmpty(queue* q)
{
	return q->size == 0;
}
void enqueue(queue* q,int item)
{
	assert(isFull(q) == 0);
	q->rear = (q->rear + 1) % q->capacity;
	q->data[q->rear] = item;
	q->size++;
}
int dequeue(queue *q)
{
	assert(isEmpty(q) == 0);
	int item = q->data[q->front];
	q->size--;
	q->front = (q->front + 1)% q->capacity;
	return item;
}
int front(queue* q)
{
	return q->data[q->front];
}
int rear(queue* q)
{
	return q->data[q->rear];
}
void printQueue(queue *q)
{
	for (int i = 0; i < q->size; i++)
	{
		printf("%d<<", q->data[(q->front + i) % q->capacity]);
	}
	printf("\n\nfront[%d]=%d ,rear[%d]=%d  ,size=%d  ,cap=%d  ,isfull=%d,  isempty=%d \n", q->front, q->data[q->front], q->rear, q->data[q->rear], q->size, q->capacity, isFull(q), isEmpty(q));
}
 int main()
{
	queue* s = newQueue(5);
	while (1)
	{
		printf("1>enqueue,2>dequeue,3>front,4>isfull,5>isempty,6->rear\n"); fflush(stdin);
		int command; scanf("%d", &command); int in1;
		switch (command)
		{
		case 1:
			printf("enter value\n"); fflush(stdin); scanf("%d", &in1);
			enqueue(s, in1);
			break;
		case 2:
			dequeue(s);
			//printf("dequeue of stack=%d\n", dequeue(s));
			break;
		case 3:
			printf("front of stack=%d\n", front(s));
			break;
		case 4:
			printf("is full =%d\n", isFull(s));
			break;
		case 5:
			printf("is empty =%d\n", isEmpty(s));
			break;
		case 6:printf("rear =%d\n", rear(s)); break;
		}
		printf("--------------------------\n\n");
		printQueue(s);
		printf("\n------------------------\n\n");
	}
	getch();
	return 0;
}
#endif
