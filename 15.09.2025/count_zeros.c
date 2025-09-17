#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int countZeros(const int* arr, int size)
{
    if (arr == NULL)
        return 0;

    int k = 0;
    for (int i = 0; i < size; i++)
        if (arr[i] == 0)
            k++;

    return k;
}

int main(void)
{
    int a[] = { 1, 2, 0, 4, 5, 0 };
    int b[] = { 8, 13, -1, 4, 0 };
    int c[] = { 4, 3, 1 };

    printf("%d\n", countZeros(a, ARRAY_SIZE(a)));
    printf("%d\n", countZeros(b, ARRAY_SIZE(b)));
    printf("%d\n", countZeros(c, ARRAY_SIZE(c)));
    return 0;
}