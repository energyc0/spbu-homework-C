#include "sorter.h"
#include <string.h>

/*
 * Merge two arrays into one using temporary space
 */
void merge(int* arr, int leftSize, int rightSize)
{
    const int size = leftSize + rightSize;
    int buf[size];
    memcpy(buf, arr, sizeof(buf));

    int l = 0;
    int r = leftSize;
    for (int i = 0; i < size; i++) {
        if (l < leftSize && r < size) {
            if (buf[l] < buf[r])
                arr[i] = buf[l++];
            else
                arr[i] = buf[r++];
        } else {
            if (l < leftSize)
                arr[i] = buf[l++];
            else
                arr[i] = buf[r++];
        }
    }
}

/*
 * mergeSort() implementation
 */
void mergeSortImpl(int* arr, int size)
{
    if (size <= 1)
        return;

    int mid = size / 2;
    mergeSortImpl(arr, mid);
    mergeSortImpl(arr + mid, size - mid);

    merge(arr, mid, size - mid);
}

/*
 * Sorts array 'arr' of integers of size 'size'
 */
void mergeSort(int* arr, int size)
{
    mergeSortImpl(arr, size);
}