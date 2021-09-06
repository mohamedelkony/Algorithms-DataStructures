
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