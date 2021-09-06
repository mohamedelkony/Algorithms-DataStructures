//return index of pivot as if it's in sorted array
//Lomuto partition scheme
//nice explaniatin https://www.khanacademy.org/computing/computer-science/algorithms/quick-sort/a/linear-time-partitioning
int lomuto_partition(int *arr, int start_index, int end_index)
{
	int pivot = arr[end_index];
	// current index of the element just before pivot if in a sorted array
	// current index of most right element in the group of smaller elements than pivot
	int barrier_index = start_index - 1;

	for (int i = start_index; i <= end_index - 1; i++)
	{
		if (arr[i] < pivot)
		{
			barrier_index++;
			swap_elements(arr, i, barrier_index);
		}
		comparsions++;
	}

	swap_elements(arr, barrier_index + 1, end_index);

	printArraywithInfo(arr, global_arr_count_to_show_megre_sort_info_in_recursion);

	return barrier_index + 1;
}

void _quick_lomto_sort_recursion(int *arr, int start_index, int end_index)
{
	if (start_index < end_index)
	{

		int border_index = lomuto_partition(arr, start_index, end_index);
		_quick_lomto_sort_recursion(arr, start_index, border_index - 1);
		_quick_lomto_sort_recursion(arr, border_index + 1, end_index);
	}
}
void _quick_lomto_sort_recursion(int *arr, int start_index, int end_index)
{
	if (start_index < end_index)
	{
		
		int border_index = lomuto_partition(arr, start_index, end_index);
		_quick_lomto_sort_recursion(arr, start_index, border_index - 1);
		_quick_lomto_sort_recursion(arr, border_index + 1, end_index);
	}
}
void quick_lomto_sort_recursion(int *arr, int count)
{
	_quick_lomto_sort_recursion(arr, 0, count - 1);
}