#include <stdio.h>
#include <stdlib.h>

int ProductWithout(int *arr, size_t n);
void PrintArr(int *arr, size_t n);

int main()
{
    int arr[] = {-5, -6, 1, 1};
    int n = sizeof(arr) / sizeof(*arr);
    int res = 0;
    res = ProductWithout(arr, n);
    if (res == 0)
    {
        PrintArr(arr, n);
    }
    return (0);
}

int ProductWithout(int *arr, size_t n)
{
    int result = 1;
    int *arr_before = (int *)malloc(sizeof(int) * n);
    int *arr_after = (int *)malloc(sizeof(int) * n);

    if ((arr_before != NULL) && ((arr_after != NULL)))
    {
        size_t i = 0;
        arr_before[0] = 1;
        arr_after[n - 1] = 1;

        for (i = 1; i < n; ++i)
        {
            arr_before[i] = arr[i - 1] * arr_before[i - 1];
            arr_after[n - i - 1] = arr[n - i] * arr_after[n - i];
        }

        for (i = 0; i < n; ++i)
        {
            arr[i] = arr_before[i] * arr_after[i];
        }
        result = 0;
    }
    free(arr_before);
    arr_before = NULL;
    free(arr_after);
    arr_after = NULL;

    return (result);
}

void PrintArr(int *arr, size_t n)
{
    size_t idx = 0;

    for (idx = 0; idx < n; ++idx)
    {
        printf("idx %lu: %d\n", idx, arr[idx]);
    }
}