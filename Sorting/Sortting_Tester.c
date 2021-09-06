
#include <math.h> //for time analayize
#include <stdio.h>
#include <time.h> //for time analayize
#include <stdlib.h>
#include <assert.h>

#include "insertionSort.c"
#include "selectionSort.c"
#include "bubbleSort.c"
#include "merge_sort_recursionTopDown.c"
#include "mergeSortBottomUp.c"
#include "lomto_sort_recursion.c"
#include "_quick_lumoto_sort_iterative.c"
#include "quick_hoare_sort_recursion.c"
#include "lomto_sort_recursion.c"
#include "top_down_merge_sort_halves_wiki_implement.c"
#include "top_down_merge_sort_halves.c"
#include "util.c"

int main()
{
	CLRSCR;
	while (1)
	{
		comparsions = 0;
		int *arr;
		unsigned int n = 10;
		algorithms algo = insertion;
		int arr_elments_type = 0;
		int quickmethod = 0;
		int quick_partition_type = 0;
		int mergemethod = 0;
		printf("enter array count");
		scanf("%u", &n);
		global_arr_count_to_show_megre_sort_info_in_recursion = n;
		//		static_assert(0);

		fflush(stdin);
		CLRLINE;

		printf("enter arlgrithm 0-> insertion , 1->selection ,2->bubble ,3->merge,4 quick ");
		scanf("%d", &algo);
		CLRLINE;
		if (algo == 4)
		{
			printf("enter qucik sort method 0-> recursion,1-> iterative");
			scanf("%d", &quickmethod);
			CLRLINE;

			printf("enter partition scheme 0-> Lomuto,1-> Hoare ");
			scanf("%d", &quick_partition_type);
			CLRLINE;

			if (quickmethod == 0 && quick_partition_type == 0)
				algo = qucik_recuresion_Lomuto;
			else if (quickmethod == 0 && quick_partition_type == 1)
				algo = quick_recursion_hoare;
			else if (quickmethod == 1 && quick_partition_type == 0)
				algo = quick_iterative_lomuto;
			else if (quickmethod == 1 && quick_partition_type == 1)
				algo = quick_iteraative_haore;
		}
		else if (algo == 3)
		{
			printf("enter merge sort method 0-> TOPDOWN,1-> BOTTOMUP");
			scanf("%d", &mergemethod);
			CLRLINE;
			if (mergemethod == 0)
				algo = merge_TopDown;
			else if (mergemethod == 1)
				algo = mergeBottomUp;
		}
		printf("enter show style");
		scanf("%d", &this_showstyle);
		CLRLINE;

		printf("enter elemnets type 0->descending , 1->random ,2-> nearly sorted,3->already sorted");
		scanf("%d", &arr_elments_type);
		CLRLINE;
		if (arr_elments_type == 1)
		{
			printf("enter max random number");
			scanf("%d", &random_array_max);
			CLRLINE;
		}
		if (arr_elments_type == 0)
			arr = get_desecending_array(n);
		else if (arr_elments_type == 1)
			arr = get_random_array(n);
		else if (arr_elments_type == 2)
			arr = get_nearly_sorted_array(n);
		else
			arr = get_ascending_array(n);

		if (arr == NULL)
		{
			printf("NOT enuogh memory avaiable to allocate array of %u elments\nyou need at least %d MB availabe in your ram\n", n, (n * sizeof(int)) / (1024 * 1024));
			continue;
		}
		int x = 3;

		clock_t begin = clock();
		sort_array(arr, n, algo);
		clock_t stop = clock();

		float elapsed = (double)(stop - begin) / CLOCKS_PER_SEC;

		if (this_showstyle == dont_show)
		{
			this_showstyle = 1;
			printArraywithInfo(arr, n);
		}

		else if (this_showstyle == justinfo)
		{
			bigint nsquared = (bigint)n * (bigint)n;
			long double n2per = (long double)comparsions / (long double)nsquared;
			float nlogn = comparsions / (n * log2(n));
			printf(" ,%-0.4f n^2,%-4.1f nlogn, %.1f comparsions/n\n", n2per, nlogn, comparsions / (float)n);
		}

		printf("\n>> Time =%d ms ,%u %s elements ,%s sort \n", (int)(elapsed * 1000.0), n, arr_elments_type == 0 ? "Descending" : (arr_elments_type == 1 ? "Random" : (arr_elments_type == 1 ? "Random" : (arr_elments_type == 2 ? "nearly sorted" : "already sorted"))), get_algo_string(algo));

		printf(">>> press q to exit or anykey to repeat\n");

		fflush(stdin);
		char c = getch();
		if (c == 'q')
		{
			return;
		}
		else if (c != ' ')
		{
			CLRSCR;
		}
		else
		{
			printf("--------------------------------------------------------------------------\n");
		}
		free(arr);
	}
	return 0;
}
