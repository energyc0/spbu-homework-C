#pragma once

#include <stdbool.h>

/*
 * Function wrapper for convenient recursive list.
 */

typedef struct RecursiveList {
    struct ListNode* _head;
    int _size;
} RecursiveList;

/*
 * Construct recursive list of length 'size' containing values from 'values'.
 */
RecursiveList makeRecursiveList(const int* values, int size);

/*
 * Frees the content of the list, do not free pList pointer.
 */
void freeRecursiveList(RecursiveList* pList);

/*
 * Erase element from the recursive list.
 * Index may be greater than size of the list, but not less than 0.
 * Return true if successfull.
 */
bool eraseRecursiveList(RecursiveList* pList, int idx);

/*
 * Just prints the list elements starting from head.
 */
void printRecursiveList(const RecursiveList* pList);

/*
 * Print the list elements in reverse order.
 */
void printRecursiveListReverse(const RecursiveList* pList);

/*
 * Get element of the given index of pList and write it to val.
 * Return true if success.
 * Return false if failed (pList may be empty).
 */
bool getRecursiveList(const RecursiveList* pList, int idx, int* val);

/*
 * Remove every 'm'th element from the list.
 * After this function list consist of one element.
 * isVerbose = true to print list every element deletion.
 */
void removeSequenceRecursiveList(RecursiveList* pList, int m, bool isVerbose);

/*
 * Get size of the list.
 */
int getSizeRecursiveList(const RecursiveList* pList);
