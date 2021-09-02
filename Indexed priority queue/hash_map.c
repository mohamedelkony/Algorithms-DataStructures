
#include <stdlib.h>
#include <string.h>
#include"hash_map.h"

struct _item
{
	key_type key;
	value_type value;
	struct _item* next;
};

struct _hash_map
{
	int size;
	item** data;
};

hash_map* new_hash_map(int size)
{
	hash_map* t = malloc(sizeof(hash_map));
	t->size = size;
	t->data = malloc(size * sizeof(item*));
	for (int i = 0; i<size; i++)
	{
		t->data[i] = NULL;
	}
	return t;
}
void h_map_insert(hash_map* t, key_type key, value_type value)
{
	item* m = malloc(sizeof(item));
	m->value = value; m->key = key; m->next = NULL;

	unsigned index = hash_generic(t, key);

	item* list = t->data[index];
	comparsions++;//for time analysis
	if (list == NULL)
	{
		t->data[index] = m;
	}
	else
	{
		while (list->next != NULL)
		{
			list = list->next;
			 comparsions++;//for time analysis
		}
		list->next = m;
	}

}

static int is_equal_generic(key_type k1, key_type k2)
{
	int ans;

#ifdef  string_key_type
	ans = (strcmp(k1, k2) == 0);
#elif defined int_key_type
	ans = (k1 == k2);
#else
	ans = (k1 == k2);
#endif

	return ans;
}
static unsigned hash_generic(hash_map*t, key_type key)
{
	int index;

#ifdef  string_key_type
	index = hash_string(t, key);
#elif defined int_key_type
	index = hash_int(t, key);
#else
	index = hash_float(t, key);
#endif

	return index;
}
static unsigned hash_string(hash_map* t, char* key)
{
	int v = 0;
	while (*key != '\0')
	{
		v += *key;
		key++;
	}
	return v % (t->size);
}
static unsigned xor_hash_string(hash_map* t, char* key)
{
	int v = 0;
	while (*key != '\0')
	{
		v ^= *key;
		key++;
	}
	return v % (t->size);
}
static unsigned hash_int(hash_map* t, int value)
{
	return value % (t->size);
}
static unsigned hash_float(hash_map* t, float value)
{
	return (int)value % (t->size);
}

value_type h_map_get_value(hash_map* t, key_type key)
{
	unsigned index = hash_generic(t, key);
	item* m = t->data[index];
	
	while (m != NULL)
	{
		comparsions++;//for time analysis
		if (is_equal_generic(key, m->key))
			return m->value;
		m = m->next;
	}
	return NULL;
}

int h_map_contains(hash_map* t, key_type key)
{
	unsigned index = hash_generic(t, key);
	item* m = t->data[index];
	comparsions++;//for time analysis

	if (m == NULL)return 0;

	while (m != NULL)
	{
		comparsions++;//for time analysis
		if (is_equal_generic(m->key, key))
			return 1;
		m = m->next;
	}
	return 0;
}

void h_map_erase(hash_map* t, key_type key)
{
	unsigned index = hash_generic(t, key);
	item* m = t->data[index];
	item* prev = NULL;
	comparsions++;//for time analysis
	if (m == NULL)return;

	while (m != NULL)
	{
		if (is_equal_generic(m->key, key))
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
		comparsions++;//for time analysis
	}
}

void h_map_print(hash_map* t)
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
			printf("%d  ---> key:%4d ,value: %d", i, m->key, m->value);
			while (m->next != NULL)
			{
				m = m->next;
				printf("\n   ---> key:%4d ,val: %d", m->key, m->value);
			}
			printf("\n-------------------------\n");
		}
	}
}