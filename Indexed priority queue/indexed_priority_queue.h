#ifndef IPQ
#define IPQ
#include"hash_map.h"

//typedef int key_t;

typedef int priority_t;

//incomplete data type
typedef struct ipq_s ipq;

typedef struct node_s node;
ipq* new_ipq(int capacity);

//O(log(n))
void ipq_insert(ipq*, key_type, priority_t);

//O(log(n))
key_type ipq_extract_min(ipq* h);

//O(1)
key_type ipq_get_min(ipq*);

//O[1)
int ipq_contains_key(ipq*, key_type);

//O(1)
value_type ipq_get_key_priority(ipq* , key_type );

//valid only for min heap
//new_val is assumed to be lower thaan original value
//Time complexity O(log(n))
void ipq_decrease_key(ipq* h, key_type key, priority_t updated_priority);

void ipq_print_h_map(ipq*);
void ipq_print(ipq*);

//O(nlog(n))
key_type* ipq_get_sorted_keys(ipq* q);

//private:

static void sift_down(ipq* h, int startingIndex);
static void update_position_map(key_type k1, key_type k2,value_type k1_new_value,value_type k2_new_value);
static void sift_up(ipq* h, int index);
static void swap(node* arr, int i, int j);

unsigned long long  comparsions;//for time analysis;

#endif