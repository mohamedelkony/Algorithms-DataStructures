//returns index of most right element in the left group
int haore_partition(int *arr, int left_index, int right_index)
{
	int pivot = arr[left_index + (right_index - left_index) / 2];
	int left_arrow = left_index - 1;
	int right_arrow = right_index + 1;
	while (1)
	{
		do
		{
			left_arrow++;
			comparsions++;
		} while (arr[left_arrow] < pivot);

		do
		{
			right_arrow--;
			comparsions++;
		} while (arr[right_arrow] > pivot);

		if (left_arrow >= right_arrow)
		{

			printArraywithInfo(arr, global_arr_count_to_show_megre_sort_info_in_recursion);
			return right_arrow; //will be index of most right element in the left group
		}

		swap_elements(arr, left_arrow, right_arrow);
	}
}
void _quick_hoare_sort_recursion(int *arr, int left_index, int right_index)
{
	if (left_index < right_index)
	{
		int barrier_index = haore_partition(arr, left_index, right_index);
		_quick_hoare_sort_recursion(arr, left_index, barrier_index);
		_quick_hoare_sort_recursion(arr, barrier_index + 1, right_index);
	}
}
void quick_hoare_sort_recursion(int *arr, int count)
{
	_quick_hoare_sort_recursion(arr, 0, count - 1);
}
