#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _node
{
	int data;
	struct _node* next;
}node;

typedef struct _queue
{
	node* front;
	node* rear;
}queue;

queue* newQueue()
{
	queue* q = malloc(sizeof(queue));
	q->front = NULL; q->rear = NULL;
	return q;
}

void enqueue(queue* q, int data)
{
	node* n = malloc(sizeof(node));
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
int dequeue(queue* q)
{
	assert(q->front != NULL);
	int data = q->front->data;
	node* formerFront = q->front;
	if (formerFront->next == NULL)
		q->rear = NULL;
	q->front = formerFront->next;
	free(formerFront);
	return data;
}
int front(queue* q)
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
	node* n = q->front;
	while (n != NULL)
	{
		printf("%d<<", n->data);
		n = n->next;
	}

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