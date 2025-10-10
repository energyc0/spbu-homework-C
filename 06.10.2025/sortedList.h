#pragma once

#include <stdbool.h>

typedef struct SortedList {
    struct ListNode* _head;
} SortedList;

/*
 * Initialize SortedList structure.
 */
void sortedListInit(SortedList* pList);

/*
 * Free SortedList internals.
 * Do not frees SortedList pointer.
 */
void sortedListFree(SortedList* pList);

/*
 * Insert value to the sortedList in sorted order.
 * Return true if inserted successfully, false otherwise.
 */
bool sortedListInsert(SortedList* pList, int value);

/*
 * Remove element from the given index.
 * Return true if removed successfullly.
 */
bool sortedListRemoveIndex(SortedList* pList, int index);

/*
 * Remove element that equals the given value.
 * Return true if removed successfullly.
 */
bool sortedListRemoveValue(SortedList* pList, int value);

/*
 * Print SortedList value divided by spaces in one line.
 */
void sortedListPrint(const SortedList* pList);

/*
 * Get SortedList's value from the given index.
 * Writes data to value and return true if successful.
 * Do not write and return false otherwise.
 */
bool sortedListGet(const SortedList* pList, int index, int* value);

/*
 * Check whether the SortedList is empty.
 */
bool isSortedListEmpty(const SortedList* pList);