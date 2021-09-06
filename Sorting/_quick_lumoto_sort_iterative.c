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