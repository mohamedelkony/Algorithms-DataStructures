#include<stdlib.h>
#include<assert.h>
#include"indexed_priority_queue.h"
#include"hash_map.h"

 struct node_s
{
	key_type key;
	priority_t priority;
};

typedef struct ipq_s
{
	int capacity;
	node* arr;
	int size;
	hash_map* map;
};

ipq* new_ipq(int capacity)
{
	ipq* t = malloc(sizeof(ipq));
	t->capacity = capacity;
	t->arr = malloc(sizeof(node)*capacity);
	t->size = 0;
	t->map = new_hash_map(capacity*5);
	return t;
}

void ipq_insert(ipq* h, key_type key,priority_t p)
{
	assert(h != NULL); 
	comparsions = 0;//for time analysis
	node n;
	n.priority = p;
	n.key = key;

	if (h->size == h->capacity)
	{
		h->arr = realloc(h->arr, h->capacity * 2 * sizeof(node));
		h->capacity *= 2;
	}
	h->size++;
	h->arr[h->size - 1] = n;
	h_map_insert(h->map, n.key, h->size - 1);
	sift_up(h, h->size - 1);
}
static int _time_anlayise_flag = 0;

key_type* ipq_get_sorted_keys(ipq* q)
{
	comparsions = 0; _time_anlayise_flag = 1;
	key_type* v = malloc(q->size*sizeof(key_type));
	int i = 0;
	for (int i = 0;q->size>0;i++)
	{
		v[i]=ipq_extract_min(q);
	}
	_time_anlayise_flag = 0;
	return v;
}
static void sift_up(ipq* h, int index)
{
	if (index == 0)return;
	int parent = (index - 1) / 2;
	if ((h->arr[index]).priority < (h->arr[parent]).priority)
	{
		update_position_map(h, h->arr[index].key, h->arr[parent].key, parent, index);
		swap(h->arr, index, parent);
		sift_up(h, parent);
		comparsions++;//for time analysis
	}
}

key_type ipq_extract_min(ipq* h)
{
	assert(h->size > 0);

	if (!_time_anlayise_flag)
	{
		comparsions = 0;//for time analysis
	}

	key_type v = h->arr[0].key;
	swap(h->arr, h->size - 1, 0);
	h->size--;

	h_map_erase(h->map, v);
	h_map_erase(h->map, h->arr[0].key);
	h_map_insert(h->map, h->arr[0].key, 0);

	sift_down(h, 0);
	return v;
}
void sift_down(ipq* h, int startingIndex)
{
	int parent = startingIndex;
	int l = parent * 2 + 1;
	while (l < h->size)
	{
		int right = l + 1;
		int min_childIndex = l;
		if (right < h->size)
		{
			if (h->arr[l].priority > h->arr[right].priority)
				min_childIndex = l + 1;
		}

		

		if (h->arr[min_childIndex].priority<h->arr[parent].priority)
		{
			update_position_map(h, h->arr[parent].key, h->arr[min_childIndex].key, min_childIndex, parent);		
			swap(h->arr, parent, min_childIndex);
			parent = min_childIndex;
			l = parent * 2 + 1;


		}
		else
		{
			break;
		}
		comparsions++;//for time analysis
	}
}
static void swap(node* arr, int i, int j)
{
	node v = arr[i];
	arr[i] = arr[j];
	arr[j] = v;
}
static void update_position_map(ipq* v,key_type k1, key_type k2, value_type k1_new_value, value_type k2_new_value)
{
	h_map_erase(v->map, k1); 
	h_map_erase(v->map, k2);
	h_map_insert(v->map, k1, k1_new_value);
	h_map_insert(v->map, k2, k2_new_value);
}
int ipq_contains_key(ipq* h, key_type key)
{
	comparsions = 0;//for time analysis
	return h_map_contains(h->map, key);
}
key_type ipq_get_min(ipq* q)
{
	comparsions = 0;//for time analysis
	return q->arr[0].key;
}
value_type ipq_get_key_priority(ipq* me, key_type key)
{
	assert(h_map_contains(me->map, key));
	comparsions = 0;//for time analysis
	int i = h_map_get_value(me->map, key);
	return me->arr[i].priority;
}

//valid only for min heap
//new_val is assumed to be lower thaan original value
//Time complexity O(log(n))
 void ipq_decrease_key(ipq* me, key_type key, priority_t updated_priority)
{
	 int index = h_map_get_value(me->map, key);
	 assert(updated_priority <= me->arr[index].priority);
	 comparsions = 0;//for time analysis

	 me->arr[index].priority = updated_priority;
	
	int parent = (index - 1) / 2;
	while (index != 0 && me->arr[parent].priority > me->arr[index].priority)
	{
		
		update_position_map(me, me->arr[parent].key, me->arr[index].key, index, parent);
		swap(me->arr, index, parent);
		index = parent;
		parent = (index - 1) / 2;
		comparsions++;
	}
}
 void ipq_print_h_map(ipq* i)
 {
	 h_map_print(i->map);
 }

 static void print2DUtil(ipq* h, int root, int space)
 {
	 // Base case 
	 if (root == -1)
		 return;
	 if (root >= h->size)return;

	 // Increase distance between levels 
	 space +=20;

	 int right = root * 2 + 2;
	 int left = root * 2 + 1;

	 // Process right child first 
	 print2DUtil(h, right, space);

	 // Print current node after space 
	 // count 
	 printf("\n");
	 for (int i = 10; i < space; i++)
		 printf(" ");
	 printf("{p:%d,k:%d,ki:%d}\n\n"
		 ,h->arr[root].priority
		 , h->arr[root].key
		 ,h_map_get_value(h->map,h->arr[root].key));

	 // Process left child 
	 print2DUtil(h, left, space);
 }

 void ipq_print(ipq* q)
 {
	 // Pass initial space count as 0 
	 print2DUtil(q, 0,0);
	 printf("------------------------------------------------------------------\n");
 }