#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include <math.h> //for time analysis

#define CLRSCR system("@cls||clear")
#define CLRLINE 	printf("\033[A\33[2K\r", 27)
typedef unsigned long long int bigint;//for time analysis

typedef struct _maxheap maxHeap;
typedef struct _s node;

maxHeap* newMaxHeap(int);
maxHeap* newHeapFromArray(node*, int);
void insert(maxHeap*, node);
char* extractMax(maxHeap*);

static void siftUp(maxHeap*, int);
static void siftDown(maxHeap*);
static void swap(node*, int, int);

int isEmpty(maxHeap*);



int comparsions;//for time analysis

 struct _s
{
	char* val;
	int priority;
};

struct _maxheap
{
	int capacity;
	node* arr;
	int size;
};

maxHeap* newMaxHeap(int capacity)
{
	maxHeap *t = malloc(sizeof(maxHeap));
	t->capacity = capacity;
	t->arr = malloc(sizeof(node)*capacity);
	t->size = 0;
	return t;
}
//Time complexity : O(n),don't free arr pointer after calling 
maxHeap* newHeapFromArray(node*	arr, int count)
{
	maxHeap* h = newMaxHeap(count);
	h->arr = arr;
	h->size = count;

	comparsions = 0;
	//index of last non leaf node in a complete tree =N/2-1
	for (int i = count / 2 - 1; i >= 0; i--)
	{
		siftDown(h, i);
	}
	return h;
}
void insert(maxHeap* h, node data)
{
	assert(h != NULL);
	if (h->size == h->capacity)
	{
		h->arr = realloc(h->arr, h->capacity * 2 * sizeof(node));
		h->capacity *= 2;
	}
	h->size++;
	h->arr[h->size - 1] = data;
	siftUp(h, h->size - 1);
}
static void siftUp(maxHeap* h, int index)
{
	if (index == 0)return;
	int parent = (index - 1) / 2;
	if ((h->arr[index]).priority > (h->arr[parent]).priority)
	{
		swap(h->arr, index, parent);
		siftUp(h, parent);
	}
}
static void swap(node* arr, int i, int j)
{
	node v = arr[i];
	arr[i] = arr[j];
	arr[j] = v;
}

char* extractMax(maxHeap*h)
{
	assert(h->size > 0);
	char* v = h->arr[0].val;
	swap(h->arr, h->size - 1, 0);
	h->size--;
	siftDown(h, 0);
	return v;
}
void siftDown(maxHeap*h, int startingIndex)
{
	int parent = startingIndex;
	int l = parent * 2 + 1;
	while (l < h->size)
	{
		int right = l + 1;
		int maxChildIndex = l;
		if (right < h->size)
		{
			if (h->arr[l].priority < h->arr[right].priority)
				maxChildIndex = l + 1;
		}

		comparsions++;

		if (h->arr[maxChildIndex].priority>h->arr[parent].priority)
		{
			swap(h->arr, parent, maxChildIndex);
			parent = maxChildIndex;
			l = parent * 2 + 1;


		}
		else
		{
			break;
		}
	}
}
int isEmpty(maxHeap* h)
{
	return h->size == 0;
}

void heapSort(int* arr, int count)
{
	maxHeap *h = newHeapFromArray(arr, count);
	while (h->size > 0)
	{
		swap(h->arr, 0, h->size - 1);
		h->size--;
		siftDown(h, 0);
	}
	return h->arr;
}
node* newNode(char* tag, int priority)
{
	node* n = malloc(sizeof(node));
	n->priority = priority;
	n->val = tag;
	return n;
}
void print2DUtil(maxHeap* h, int root, int space)
{
	// Base case 
	if (root == -1)
		return;
	if (root >= h->size)return;

	// Increase distance between levels 
	space += 10;

	int right = root * 2 + 2;
	int left = root * 2 + 1;

	// Process right child first 
	print2DUtil(h, right, space);

	// Print current node after space 
	// count 
	printf("\n");
	for (int i = 10; i < space; i++)
		printf(" ");
	printf("%s:%d\n", h->arr[root].val,h->arr[root].priority);

	// Process left child 
	print2DUtil(h, left, space);
}

void print2D(maxHeap* h)
{
	// Pass initial space count as 0 
	print2DUtil(h, 0, 0);
}




int main()
{
	CLRSCR;
	comparsions = 0;
	maxHeap *h = newMaxHeap(10);
	while (1)
	{
		comparsions = 0;
		printf("1>insert,2>extractMax,3->print,4->isEmpty,5->fromArray,6->heapsort\n"); fflush(stdin);
		int command; scanf("%d", &command); int in1=0; char* tag=malloc(10);
		switch (command)
		{
		case 1:
			printf("enter string\n"); fflush(stdin); scanf("%s", tag);
			printf("\nenter priority\n"); fflush(stdin); scanf("%d", &in1);
			insert(h, *newNode(tag,in1));
			break;
		case 2:
			printf("MAX was %s", extractMax(h));
			break;
		case 3:
			print2D(h);
			break;
		case 4:
			printf("is empty = %d", isEmpty(h)); break;

		}
		if (command == 5)
		{
			printf("enter array count\n"); fflush(stdin); scanf("%d", &in1); CLRLINE;
			node* arr = malloc(in1*sizeof(node));
			for (int i = 0; i< in1; i++)
			{
				arr[i].priority = in1 - i;
				char* v = malloc(4);
				v[3] = '\0';
				v[1]=v[2]=v[0] = i%27+'A';
				arr[i].val = v;
			}
			h = newHeapFromArray(arr, in1);
			printf("\n");
			print2D(h);
			bigint nsquared = (bigint)in1*(bigint)in1;
			long double n2per = (long double)comparsions / (long double)nsquared;
			float nlogn = comparsions / (in1*log2(in1));
			printf(">>>Time complexity : %0.3f n ,%0.3f nlog2n ,%0.3f n^2", comparsions / (float)in1, nlogn, n2per);
		}
	
		printf("\n------------------------\n");
	}
	getch();
	return 0;
}