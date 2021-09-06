
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