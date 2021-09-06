
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
