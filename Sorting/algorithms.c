
/*
Time Complexity : O(n * 2)
Auxiliary Space : O(1)
Uses: Insertion sort is used when number of elements is small.
	  It can also be useful when input array is almost sorted
	 , only few elements are misplaced in complete big array.
*/
void insertionSort(int arr[], int count)
{

	int j, key;
	for (int i = 0; i < count; i++)
	{
		j = i - 1;
		key = arr[i];

		/* Move elements of arr[0..i-1], that are3
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
			comparsions++;
		}
		arr[j + 1] = key;

		printArraywithInfo(arr, count);
	}
}

/*
Time Complexity : O(n * 2)
Auxiliary Space : O(1)
*/
void selectionSort(int arr[], int count)
{
	for (int i = 0; i < count - 1; i++)
	{
		int min_element_index = i;
		for (int j = i + 1; j < count; j++)
		{
			if (arr[j] < arr[min_element_index])
			{
				min_element_index = j;
			}
			comparsions++;
		}
		swap_elements(arr, min_element_index, i);

		printArraywithInfo(arr, count);
	}
}

void bubbleSort(int *arr, int count)
{

	short int sorted = 0;
	int last_sorted_index = count - 1;
	while (!sorted)
	{
		sorted = 1;
		for (int i = 0; i < last_sorted_index; i++)
		{
			if (arr[i + 1] < arr[i])
			{
				swap_elements(arr, i, i + 1);
				sorted = 0;
			}
			comparsions++;
		}

		last_sorted_index--;
		if (sorted)
			break;

		printArraywithInfo(arr, count);
	}
}

void top_down_merge_sort_halves(int *arr, int left_start_index, int right_end_index, int *temp_sorted_arr)
{

	int mid_index = (right_end_index + left_start_index) / 2;
	int current_left_index = left_start_index;
	int current_right_index = mid_index + 1;
	int current_sorted_index = left_start_index;

	//sort 2 halves into temp sorted arr
	while (current_left_index <= mid_index && current_right_index <= right_end_index)
	{
		if (arr[current_left_index] > arr[current_right_index])
		{
			temp_sorted_arr[current_sorted_index] = arr[current_right_index];
			current_right_index++;
		}
		else
		{
			temp_sorted_arr[current_sorted_index] = arr[current_left_index];
			current_left_index++;
		}
		current_sorted_index++;
		comparsions++;
	}

	//copy already sorted reminder elements in right half
	while (current_right_index <= right_end_index)
	{
		temp_sorted_arr[current_sorted_index] = arr[current_right_index];
		current_sorted_index++;
		current_right_index++;
	}

	//copy already sorted reminder elements in left half
	while (current_left_index <= mid_index)
	{
		temp_sorted_arr[current_sorted_index] = arr[current_left_index];
		current_sorted_index++;
		current_left_index++;
	}

	//copy temp arr_sorted to orginal arr
	for (int i = left_start_index; i <= right_end_index; i++)
	{
		*(arr + i) = *(temp_sorted_arr + i);
	}

	printArraywithInfo(arr, global_arr_count_to_show_megre_sort_info_in_recursion);
}

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

void mergeSortBottomUpHalves(int *arr, const int leftStartIndex, const int rightStartIndex, const int rightEndIndex, int *tempSortedArr)
{
	int currentLeftIndex = leftStartIndex;
	int currentRightIndex = rightStartIndex;

	for (int currentSortedIndex = leftStartIndex; currentSortedIndex <= rightEndIndex; currentSortedIndex++)
	{
		//place element in current left index in sorted arrat and increase it
		//  if
		//    left index still in its region [left  start index,right index-1]
		// and
		//    its value less than the value at current right or current right exceed its region [right start index, right end index]
		if (currentLeftIndex < rightStartIndex && (currentRightIndex > rightEndIndex || arr[currentLeftIndex] < arr[currentRightIndex]))
		{
			tempSortedArr[currentSortedIndex] = arr[currentLeftIndex];
			currentLeftIndex++;
		}
		else
		{
			tempSortedArr[currentSortedIndex] = arr[currentRightIndex];
			currentRightIndex++;
		}
		comparsions++;
	}
}
void mergeSortBottomUp(int *arr, int count)
{
	int *tempArr = (int *)malloc(count * sizeof(int));

	for (int width = 1; width < count; width = width * 2)
	{
		for (int leftStartIndex = 0; leftStartIndex < count; leftStartIndex = leftStartIndex + width * 2)
		{
			int rightStartIndex = min(leftStartIndex + width, count - 1);
			int rightEndIndex = min(leftStartIndex + width * 2 - 1, count - 1);
			mergeSortBottomUpHalves(arr, leftStartIndex, rightStartIndex, rightEndIndex, tempArr);
		}
		//copy tempArr to original array
		for (int i = 0; i < count; i++)
		{
			arr[i] = tempArr[i];
		}
		printArraywithInfo(arr, global_arr_count_to_show_megre_sort_info_in_recursion);
	}
}

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

void _quick_lumoto_sort_iterative(int arr[], int l, int h)
{
	// Create an auxiliary stack
	int *stack = malloc((h - l + 1) * sizeof(int));

	// initialize top of stack
	int top = -1;

	// push initial values of l and h to stack
	*(stack + (++top)) = l;
	stack[++top] = h;

	// Keep popping from stack while is not empty
	while (top >= 0)
	{
		// Pop h and l
		h = stack[top--];
		l = stack[top--];

		// Set pivot element at its correct position
		// in sorted array
		int p = lomuto_partition(arr, l, h);

		// If there are elements on left side of pivot,
		// then push left side to stack
		if (p - 1 > l)
		{
			stack[++top] = l;
			stack[++top] = p - 1;
		}

		// If there are elements on right side of pivot,
		// then push right side to stack
		if (p + 1 < h)
		{
			stack[++top] = p + 1;
			stack[++top] = h;
		}
	}
	free(stack);
}

void quick_lumoto_sort_iterative(int *arr, int count)
{

	_quick_lumoto_sort_iterative(arr, 0, count - 1);
}
void quick_lomto_sort_recursion(int *arr, int count)
{
	_quick_lomto_sort_recursion(arr, 0, count - 1);
}
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
