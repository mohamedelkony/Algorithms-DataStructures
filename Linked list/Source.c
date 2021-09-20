#include <math.h> 
#include <stdio.h> 
#include<time.h>
#include <stdlib.h>
#include<assert.h>
#include<string.h>

#define CLRSCR system("@cls||clear")
#define CLRLINE 	printf("\033[A\33[2K\r")
#define WAITTIME 300

void delay(int number_of_milliseconds)
{
	// Converting time into milli_seconds 
	int milli_seconds = number_of_milliseconds;

	// Stroing start time 
	clock_t start_time = clock();

	// looping till required time is not acheived 
	while (clock() < start_time + milli_seconds)
		;
}

typedef struct _node
{
	int data; 
	char* tag; 
  struct _node* next;
}node;

node* createNode(const int _id,const char* _tag)
{
	node* newNode = (node*)malloc(sizeof(node));
	assert(newNode != NULL);
	newNode->data = _id;
	newNode->tag = _tag;
	newNode->next = NULL;
	return newNode;
}
node* createNodeEmpty()
{
	return createNode(0, NULL);
}

node* getLastNode(node* head)
{
	node* value = head;
	while (value->next != NULL)
		value = value->next;
	return value;
}

node* getPerviousNode(const node* head,const node* target)
{
	node* prev = head;
	while (prev->next!=target)
	{
		prev = prev->next;
		if (prev == NULL)return NULL;
	}
	return prev;
}

//in case of even list returns the latter mid point 
node* getMiddleNode(node* head,node** prev)
{
	if (head == NULL)
	{
		return NULL;
	}
	else if (head->next == NULL)
	{
		return head;
	}

	node* slow = head;
	node* fast = head;
	*prev = slow;
	while (fast!=NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			fast = fast->next;
			*prev = slow;
			slow = slow->next;
		}
	}
	
	return slow;
}

node* findNodebyId(node* head, int data)
{
	while (head->data!=data)
	{
		if (head->next == NULL)
			return NULL;
		head = head->next;
	}
	return head;
}

void printNode(node* _node)
{
	printf("%-5d |%-15s |%x |%x\n", _node->data, _node->tag,_node, _node->next);
}
void printLinkedList(node* head)
{
	printf("%-5s |%-15s |%-6s |%-6s\n","data", "tag","curent", "next");
	while (head!=NULL)
	{
		printNode(head);
		head = head->next;
	}
}

//insert node in fornt of the list
void push(node** head,node* _node)
{
	 assert(_node != NULL);
	// (head) address of local function pointer ,usless
	// (*head) address of pointer to head node
	// (**head) address of head node
	_node->next=*head;
	*head = _node;
}

void insertAfter(node* source, node* _node)
{	
	assert(source != NULL); assert(_node != NULL);
	_node->next = source->next;
	source->next = _node;
}

void add(node** head, node* _node)
{
	 assert(_node != NULL);
	if (*head == NULL)
	{
		*head = _node; return;
	}
	node* last = getLastNode(*head);
	last->next = _node;
	_node->next = NULL;
}

void deleteNode(node** head, node* target)
{
	if (*head == target)
	{
		node* temp = *head;
		*head = (*head)->next;
		free(temp);
		return;
	}
	node* perviousNode = getPerviousNode(*head, target);
	assert(perviousNode != NULL);

	perviousNode->next = target->next;
	free(target);
}

void swapNodes(node** head, node* a, node* b)
{
	assert(a != NULL); assert(b != NULL);

	node* pA = getPerviousNode(*head, a);
	node* pB = getPerviousNode(*head, b);

	if (pA != NULL)
	{
		pA->next = b;
	}
	else{ *head = b; }

	if (pB != NULL)
	{
		pB->next = a;
	}
	else{ *head = a; }

	node* temp = a->next;
	a->next = b->next;
	b->next = temp;
	
}
node* mergeLindekList(node* a, node* b)
{
	node* head=NULL;
	
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	

	if (a->data <= b->data)
	{
		head = a;
		head->next=mergeLindekList(a->next, b);
	}
	else
	{
		head = b;
		head->next=mergeLindekList(a, b->next);
	}
	return head;
}
void mergeSortLinkedList(node **head)
{
	
	
	if (*head == NULL)
	{
		return ;
	}
	else if ((*head)->next == NULL){ return; }

	node* prevMiddleNode=NULL;
	node* middleNode = getMiddleNode(*head, &prevMiddleNode);
	prevMiddleNode->next = NULL;

	mergeSortLinkedList(head);
	mergeSortLinkedList(&middleNode);

	*head=mergeLindekList(*head, middleNode);
}

int main()
{
	CLRSCR;
	node* head = NULL;
	add(&head, createNode(4, "4th"));
	add(&head, createNode(6, "6th"));
	add(&head, createNode(5, "5th"));
	add(&head, createNode(2, "second"));	
	add(&head, createNode(1, "First"));	
	add(&head, createNode(3, "Third"));
	
	while (1)
	{
		printf("1:PUSH,2:InsertAfter,3:ADD,4:PRINT,5:GETLAST,6:delete,7:swap,8:QuickSort,9:MergeSort,10:Invert,11:GETmiddle");fflush(stdin);int c; scanf("%d",&c);
		CLRLINE;
		int data ,id2,id3 = 0; char* tag = (char*)malloc(15);

		if (c == 1 || c==2|| c == 3)
		{
			printf("enter data"); scanf("%d", &data); CLRLINE;fflush(stdin);
			
			printf("enter tag");fflush(stdin); gets(tag); CLRLINE;
		}

			

		
		if (c == 1)
		{
			push(&head,createNode(data, tag));
		}
		else if (c == 2)
		{
			printf("enter data of node to insert after"); scanf("%d", &id2); CLRLINE;
			insertAfter(findNodebyId(head, id2), createNode(data, tag));
		}
		else if (c == 3)
		{
			add(&head, createNode(data, tag));

		}
		else if (c == 4)
		{
			printLinkedList(head);
		}
		else if (c == 5)
		{
			printNode(getLastNode(head));
		}
		else if (c == 6)
		{
			printf("enter data of node to be deleted"); scanf("%d", &id2); CLRLINE;
			deleteNode(&head, findNodebyId(head, id2));
			printLinkedList(head);
		}
		else if (c == 7)
		{
			printf("enter data of first node"); scanf("%d", &id2); CLRLINE;
			printf("enter data of second node"); scanf("%d", &id3); CLRLINE;
			swapNodes(&head, findNodebyId(head, id2), findNodebyId(head, id3));
			printLinkedList(head);
		}
		else if (c == 11)
		{
			node* prev = NULL; node* mid = getMiddleNode(head, &prev);
			printNode(prev);printNode(mid);
		}
		else if (c == 9)
		{
			mergeSortLinkedList(&head);
			printLinkedList(head);
		}
		printf("----------------------------------------------------------\n");
	}

	return 0;
}