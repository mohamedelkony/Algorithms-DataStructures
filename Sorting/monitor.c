
unsigned int global_arr_count_to_show_megre_sort_info_in_recursion = 0;
void printArraywithInfo(int arr[], int n)
{
	if (this_showstyle == linearshow || this_showstyle == list_show)
	{
		if (this_showstyle == linearshow)
			CLRSCR; // CLRLASTLINE(1);

		int i;

		for (i = 0; i < n; i++)
		{
			printf("%d ", arr[i]);
		}
		bigint nsquared = (bigint)n * (bigint)n;
		long double n2per = (long double)comparsions / (long double)nsquared;
		float nlogn = comparsions / (n * log2(n));
		printf(" ,%0.4f n^2,%4.1f nlogn , %lli comparsions\n", n2per, nlogn, comparsions);
		delay(WAITTIME);
	}
}