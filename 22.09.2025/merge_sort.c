#include "sorter.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_CAPACITY (100)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/*
 * Reads integers until newline in array 'arr'
 * of size 'capacity', returns the number of integers
 */
int scanNumbers(int* arr, int capacity)
{
    char buf[BUFSIZ];
    printf("Enter numbers:\n");
    fgets(buf, sizeof(buf), stdin);

    int num = 0;
    int offset = 0;
    int number_offset = 0;
    int size = 0;
    while (size < capacity && sscanf(buf + offset, "%d%n", &num, &number_offset) == 1) {
        arr[size++] = num;
        offset += number_offset;
    }

    return size;
}

/*
 * Sorts given array and prints the result,
 * outputs count of the replaced elements
 */
int printSortedArray(const int* arr, int size)
{
    int temp_buf[size];
    memcpy(temp_buf, arr, size * sizeof(int));
    mergeSort(temp_buf, size);

    int pos_changes = 0;
    for (int i = 0; i < size; i++) {
        if (temp_buf[i] != arr[i])
            pos_changes++;
        printf("%d ", temp_buf[i]);
    }

    putchar('\n');
    return pos_changes;
}

int main(void)
{
    int buf[BUFFER_CAPACITY];
    int size = scanNumbers(buf, BUFFER_CAPACITY);

    return printSortedArray(buf, size);
}