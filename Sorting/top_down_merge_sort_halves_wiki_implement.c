
void top_down_merge_sort_halves_wiki_implement(int *arr, int left_start_index, int right_end_index, int *temp_sorted_arr)
{

	int mid_index = (right_end_index + left_start_index) / 2;
	int current_left_index = left_start_index;
	int current_right_index = mid_index + 1;

	// While there are elements in the left or right runs...
	for (int current_sorted_index = left_start_index; current_sorted_index <= right_end_index; current_sorted_index++)
	{
		// If left run head exists and is <= existing right run head.
		if (current_left_index <= mid_index && (current_right_index > right_end_index || arr[current_left_index] <= arr[current_right_index]))
		{
			temp_sorted_arr[current_sorted_index] = arr[current_left_index];
			current_left_index++;
		}
		else
		{
			temp_sorted_arr[current_sorted_index] = arr[current_right_index];
			current_right_index++;
		}
		comparsions++;
	}
	//copy temp arr_sorted to orginal arr
	for (int i = left_start_index; i <= right_end_index; i++)
	{
		*(arr + i) = *(temp_sorted_arr + i);
	}
	printArraywithInfo(arr, global_arr_count_to_show_megre_sort_info_in_recursion);
}