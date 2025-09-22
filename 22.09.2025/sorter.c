#include "sorter.h"
#include <string.h>

void _merge(int* arr, int left_size, int right_size)
{
    const int size = left_size + right_size;
    int buf[size];
    memcpy(buf, arr, sizeof(buf));

    int l = 0;
    int r = left_size;
    for(int i = 0; i < size; i++) {
        if (l < left_size && r < size) {
            if (buf[l] < buf[r])
                arr[i] = buf[l++];
            else
                arr[i] = buf[r++];
        } else {
            if (l < left_size) 
                arr[i] = buf[l++];
            else
                arr[i] = buf[r++];
        }
    }
}

void _mergeSortImpl(int* arr, int size)
{
    if (size <= 1)
        return;

    int mid = size / 2;
    _mergeSortImpl(arr, mid);
    _mergeSortImpl(arr + mid, size - mid);
    
    _merge(arr, mid, size - mid);
}

void mergeSort(int* arr, int size)
{
    _mergeSortImpl(arr, size);
    
}