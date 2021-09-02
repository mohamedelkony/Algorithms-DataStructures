#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include <math.h> //for time analysis
#include<time.h>//for time analayize
#include"indexed_priority_queue.h"

/*
Priority queues are often implemented with heaps,but they are conceptually distinct from heaps.
A priority queue is a concept like "a list" or "a map";
just as a list can be implemented with a linked list or an array
a priority queue can be implemented with a heap or a variety of other methods such as an unordered array
*/

//for time analysis
typedef unsigned long long int big_int;
typedef enum _types{nlog_t,nsquared_t,n_t,of_one_t,logn_t}types;
typedef struct _big_o{ int val; types type; }big_o;

int comper(void* p1, void* p2)
{
	return ((big_o*)p1)->val - ((big_o*)p2)->val;
}
const char* big_o_tostr(big_o b){

	char* s=malloc(10);
	switch (b.type)
	{
	case nlog_t:
		s = "nlogn";
		break;
	case logn_t:
		s = "logn";
		break;
	case nsquared_t:
		s = "nsquare";
		break;
	case of_one_t:
		s = "1";
		break;
	case n_t:
		s = "n";
		break;
	}
	return s;
}
void analyize_time(big_int n, big_int compares_count)
{	
	/*float nsquared_cof = compares_count / (long double)(n*n);
	float nlogn_cof = compares_count / (n*log2(n));
	float n_cof = compares_count / (long double)n;
	float logn_cof = compares_count / (log2(n));
	*/
	//printf(">>>Time (%llu) complexity :%0.3f logn, %0.3f n ,%0.3f nlog2n ,%0.3f n^2\n",compares_count,logn_cof, n_cof, nlogn_cof, nsquared_cof);
	
	big_o o1 = { abs(compares_count - (n*n)), nsquared_t };
	big_o o2 = { abs(compares_count - (n*log2(n))), nlog_t };
	big_o o3 = { abs(compares_count - n), n_t };
	big_o o4 = { abs(compares_count - 1), of_one_t };
	big_o o5 = { abs(compares_count - (log2(n))), logn_t };
	
	big_o os[5]; os[0] = o1; os[1] = o2; os[2] = o3; os[3] = o4; os[4] = o5;
	qsort(os, 5, sizeof(big_o), comper);
	printf("%llu comparsions done for a queue of size %d\n",compares_count,n);
	printf("  >> its bestfit is O(%s),2nd bestfit is O(%s)\n\n", big_o_tostr(os[0]), big_o_tostr(os[1]));
}

void test1()
{
	while (1)
	{

	printf("enter items count");
	int n = 10e4;
	scanf("%d",&n);

	ipq* q = new_ipq(n);
	for (int i = 0; i<n-1;i++)
		ipq_insert(q,i, -i+1);
	
	ipq_insert(q, 25,-1050);
	printf("\n 1 item  insertion analysis into queue\n",n);
	analyize_time(n, comparsions);

	
	printf("ipq_decrease_key(q, 3, -1000);\n");
	ipq_decrease_key(q, 3, -1000);
	analyize_time(n, comparsions);
	
	
	//ipq_print(q);
	printf("get_min() =%d\n",ipq_get_min(q));
	analyize_time(n, comparsions);

	//ipq_print(q);
	printf("ipq_extract_min(); = %d\n", ipq_extract_min(q));
	analyize_time(n, comparsions);

	printf(" ipq_get_key_priority(3); = %d \n", ipq_get_key_priority(q, 3));
	analyize_time(n, comparsions);

	printf("ipq_contains_key(20); = %d \n", ipq_contains_key(q, 20));
	analyize_time(n, comparsions);

	printf("queue is being heap sorted\n");
	key_type* v = ipq_get_sorted_keys(q);
	analyize_time(n, comparsions);
	
	printf("print queue?"); int er;
	scanf("%d", &er);
	if (er)
		ipq_print(q);
	printf("print queue internal hash map?"); int er2;
	scanf("%d", &er2);
	if (er2)
		ipq_print_h_map(q);
	}
}
int main()
{
	test1();

	scanf_s("%d");
	return 0;
}