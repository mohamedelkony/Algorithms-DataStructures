#include<stdio.h>
#include"stack.h"


int main()
{
	stack* s = newStack();


#if defined ARRAY_STACK
	printf("ARRAY\n");
#elif  defined LINKED_STACK
	printf("LINKED LIST\n");
#endif

	
	while (1)
	{
		printf("1>push,2>pop,3>peek,4>isfull,5>isempty\n"); fflush(stdin);
		int command; scanf("%d", &command); data_type in1;
		switch (command)
		{
		case 1:
			printf("enter value\n"); fflush(stdin); scanf("%f", &in1);
			push(s, in1);
			break;
		case 2:
			printf("pop of stack=%f\n", pop(s));
			break;
		case 3:
			printf("peak of stack=%f\n", peak(s));
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

