/*	First divides the list into the smallest unit (1 element), 
	then compare each element with the adjacent list to sort and merge the two adjacent lists.
	Finally all the elements are sorted and merged
*/
void merge_sort_recursionTopDown(int *arr, int left_start_index, int right_end_index, int *temp_arr)
{

	if (left_start_index >= right_end_index)
	{

		return;
	}

	int mid_index = left_start_index + (right_end_index - left_start_index) / 2;

	merge_sort_recursionTopDown(arr, left_start_index, mid_index, temp_arr);
	merge_sort_recursionTopDown(arr, mid_index + 1, right_end_index, temp_arr);

	top_down_merge_sort_halves_wiki_implement(arr, left_start_index, right_end_index, temp_arr);
}

void merge_sortTopDown(int *arr, int count)
{
	int *temp_arr = (int *)malloc(count * sizeof(int));
	merge_sort_recursionTopDown(arr, 0, count - 1, temp_arr);
}
