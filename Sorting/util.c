#ifndef util
#define util

#include <math.h> //for time analayize
#include <stdio.h>
#include <time.h> //for time analayize
#include <stdlib.h>
#include <assert.h>

#include "insertionSort.c"
#include "selectionSort.c"
#include "bubbleSort.c"
#include "merge_sort_recursionTopDown.c"
#include "mergeSortBottomUp.c"
#include "lomto_sort_recursion.c"
#include "_quick_lumoto_sort_iterative.c"
#include "quick_hoare_sort_recursion.c"
#include "lomto_sort_recursion.c"
#include "top_down_merge_sort_halves_wiki_implement.c"
#include "top_down_merge_sort_halves.c"

#define CLRSCR system("@cls||clear")
#define CLRLINE printf("\033[A\33[2K\r", 27)
#define WAITTIME 300

typedef unsigned long long int bigint;

enum showstyle
{
    dont_show,
    list_show,
    linearshow,
    justinfo = -1,
    innersteps
} this_showstyle;

typedef enum _algorithms
{
    insertion,
    selection,
    bubble,
    merge_TopDown,
    mergeBottomUp,
    quick_iterative_lomuto,
    qucik_recuresion_Lomuto,
    quick_iteraative_haore,
    quick_recursion_hoare
} algorithms;
char *get_algo_string(algorithms algo)
{
    char *x = "";
    switch (algo)
    {
    case insertion:
        x = "insertion";
        break;
    case selection:
        x = "selection";
        break;
    case bubble:
        x = "bubble";
        break;
    case mergeBottomUp:
        x = "merge Bottom Up";
        break;
    case merge_TopDown:
        x = "Merge Top Down";
        break;
    case quick_iteraative_haore:
        x = "quick_iteraative_haore";
        break;
    case quick_recursion_hoare:
        x = "quick_recursion_hoare ";
        break;
    case qucik_recuresion_Lomuto:
        x = "qucik_recuresion_Lomuto";
        break;
    case quick_iterative_lomuto:
        x = "quick_iterative_lomuto";
        break;
    }
    return x;
}

bigint comparsions = 0;

void CLRLASTLINE(int clearnewline)
{
    if (clearnewline)
    {
        //delete current line
        printf("%c[2K", 27);
        //move same colmon to up line
        printf("\033[A");
    }
    printf("%c[2K", 27);
    printf("\r");
}

void delay(int number_of_milliseconds)
{
    // Converting time into milli_seconds
    int milli_seconds = number_of_milliseconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}

void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

unsigned int global_arr_count_to_show_megre_sort_info_in_recursion = 0;
void printArraywithInfo(int arr[], int n)
{
    if (this_showstyle == linearshow || this_showstyle == list_show)
    {
        if (this_showstyle == linearshow)
            CLRSCR; // CLRLASTLINE(1);

        int i;

        for (i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        bigint nsquared = (bigint)n * (bigint)n;
        long double n2per = (long double)comparsions / (long double)nsquared;
        float nlogn = comparsions / (n * log2(n));
        printf(" ,%0.4f n^2,%4.1f nlogn , %lli comparsions\n", n2per, nlogn, comparsions);
        delay(WAITTIME);
    }
}

void swap_elements(int *arr, int i, int x)
{
    if (i == x)
        return;
    int temp = *(arr + i);
    *(arr + i) = *(arr + x);
    *(arr + x) = temp;
}

void sortarry(int arr[], int count, void (*sorting_algorithm)(int *, int))
{
    sorting_algorithm(arr, count);
}

void sort_array(int *arr, int count, algorithms algo)
{
    switch (algo)
    {
    case insertion:
        sortarry(arr, count, insertionSort);
        break;
    case selection:
        sortarry(arr, count, selectionSort);
        break;
    case bubble:
        sortarry(arr, count, bubbleSort);
        break;
    case mergeBottomUp:
        sortarry(arr, count, mergeSortBottomUp);
        break;
    case merge_TopDown:
        sortarry(arr, count, merge_sortTopDown);
        break;
    case quick_iteraative_haore:

        break;
    case quick_recursion_hoare:
        sortarry(arr, count, quick_hoare_sort_recursion);
        break;
    case qucik_recuresion_Lomuto:
        sortarry(arr, count, quick_lomto_sort_recursion);
        break;
    case quick_iterative_lomuto:
        sortarry(arr, count, quick_lumoto_sort_iterative);
        break;
    }
}

int *get_ascending_array(unsigned int count)
{
    int *arr = (int *)malloc(count * sizeof(int));
    if (arr == NULL)
        return NULL;
    for (int i = 0; i < count; i++)
    {
        arr[i] = i;
    }
    return arr;
}
int *get_desecending_array(unsigned int count)
{
    int *arr = (int *)malloc(count * sizeof(int));
    if (arr == NULL)
        return NULL;
    for (int i = 0; i < count; i++)
    {
        arr[i] = count - i;
    }
    return arr;
}
int random_array_max = 50;
int *get_random_array(unsigned int count)
{
    srand(time(0));
    int *arr = (int *)malloc(count * sizeof(int));
    if (arr == NULL)
        return NULL;
    for (int i = 0; i < count; i++)
    {
        arr[i] = rand() % random_array_max;
    }
    return arr;
}
int *get_nearly_sorted_array(unsigned int count)
{
    srand(time(0));
    int *arr = (int *)malloc(count * sizeof(int));
    if (arr == NULL)
        return NULL;
    for (int i = 0; i < count; i++)
    {
        int percent = (i / (float)count) * 100.0;

        if (percent % 25 < 4)
        {
            arr[i] = rand() % count;
        }
        else
        {
            arr[i] = i;
        }
    }
    return arr;
}
#endif