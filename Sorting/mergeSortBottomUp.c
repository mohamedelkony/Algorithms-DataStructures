
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
