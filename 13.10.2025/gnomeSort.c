#include <stdio.h>

void swapInt(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void gnomeSort(int* array, int size)
{
    for (int i = 1, j = 2; i < size;) {
        if (array[i-1] < array[i]) {
            i = j;
            j++;
        } else {
            swapInt(&array[i-1], &array[i]);
            if (--i == 0) {
                i = j;
                j++;
            }
        }
    }
}

void printArray(const int* array, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    putchar('\n');
}

int main(void)
{
    int a[] = {2, 3, 5, -1, 4, 2, 1, -2};
    printArray(a, sizeof(a) / sizeof(int));
    gnomeSort(a, sizeof(a) / sizeof(int));
    printArray(a, sizeof(a) / sizeof(int));
    return 0;
}