#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void swapInt(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Sort array in increasing order.
 */
void gnomeSort(int* array, int size)
{
    for (int i = 1, j = 2; i < size;) {
        if (array[i - 1] < array[i]) {
            i = j;
            j++;
        } else {
            swapInt(&array[i - 1], &array[i]);
            if (--i == 0) {
                i = j;
                j++;
            }
        }
    }
}

/*
 * Just prints array elements divided by spaces.
 * Insert '\n' at the end.
 */
void printArray(const int* array, int size)
{
    putchar('[');
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("]\n");
}

/*
 * Print array before sorting and after.
 */
void printTestCase(int* array, int size)
{
    printf("Before: ");
    printArray(array, size);
    gnomeSort(array, size);
    printf("After: ");
    printArray(array, size);
}

int main(void)
{
    int a[] = { 2, 3, 5, -1, 4, 2, 1, -2 };
    int b[] = { 1, 2, 3 };
    int c[] = { 1 };

    printTestCase(a, ARRAY_SIZE(a));
    printTestCase(b, ARRAY_SIZE(b));
    printTestCase(c, ARRAY_SIZE(c));
    return 0;
}