
#include <stdlib.h>
#include <string.h>
#include"hash.h"

struct _item
{
	char* name;
	int id;
	struct _item* next;
};

struct _table
{
	int size;
	item** data;
};

table* createTable(int size)
{
	table* t = malloc(sizeof(table));
	t->size = size;
	t->data = malloc(size * sizeof(item*));
	for (int i = 0; i<size; i++)
	{
		t->data[i] = NULL;
	}
	return t;
}
void add(table* t, int id, char* name)
{
	item* m = malloc(sizeof(item));
	m->id = id; m->name = name; m->next = NULL;

	int index = hash(t, name);

	item* list = t->data[index];
	if (list == NULL)
	{
		t->data[index] = m;
	}
	else
	{
		while (list->next != NULL)
			list = list->next;
		list->next = m;
	}

}
static unsigned hash(table* t, char* name)
{
	int v = 0;
	while (*name != '\0')
	{
		v += *name;
		name++;
	}
	return v % (t->size);
}
static unsigned xorHash(table* t, char* name)
{
	int v = 0;
	while (*name != '\0')
	{
		v ^= *name;
		name++;
	}
	return v % (t->size);
}
static unsigned hash2(table* t, int id)
{
	return id % (t->size);
}
char* getName(table* t, int id)
{
	int index = hash2(t, id);
	item* m = t->data[index];

	while (m != NULL)
	{
		if (m->id == id)
			return m->name;
		m = m->next;
	}
	return NULL;
}
int contains(table* t, char* name)
{
	int index = hash(t, name);
	item* m = t->data[index];
	if (m == NULL)return 0;

	while (m != NULL)
	{
		if (strcmp(m->name, name) == 0)
			return 1;
		m = m->next;
	}
	return 0;
}

void erase(table* t, char* name)
{
	int index = hash(t, name);
	item* m = t->data[index];
	item* prev = NULL;
	if (m == NULL)return;

	while (m != NULL)
	{
		if (strcmp(m->name, name) == 0)
		{
			if (prev != NULL)
			{
				prev->next = m->next;
				free(m);
				return;
			}
			else
			{
				t->data[index] = m->next;
				free(m);
				return;
			}
		}
		prev = m;
		m = m->next;
	}
}
void printT(table* t)
{
	for (int i = 0; i<t->size; i++)
	{
		item* m = t->data[i];
		if (m == NULL)
		{
			printf("%d >> NULL\n-------------------\n", i);
		}
		else
		{
			printf("%d  ---> id:%4d ,name: %s", i, m->id, m->name);
			while (m->next != NULL)
			{
				m = m->next;
				printf("\n   ---> id:%4d ,name: %s", m->id, m->name);
			}
			printf("\n-------------------------\n");
		}
	}
}