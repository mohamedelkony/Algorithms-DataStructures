#include <stdio.h>
#include <stdlib.h>
#include"hash.h"


int main(){

	system("COLOR 4A");
	int num;
	scanf("%d\n", &num);
	table *t = createTable(num * 2);
	while (num)
	{
		int id; char* name = malloc(27);
		scanf("%d %s", &id, name);
		add(t, id, name);
		num--;
	}

	printT(t);

	while (1)
	{
		char* s = malloc(25);
		scanf("%s", s);
		printf("\n----------****--------\n %d \n-------\n", contains(t, s));

		erase(t, s);
		printT(t);
	}

}