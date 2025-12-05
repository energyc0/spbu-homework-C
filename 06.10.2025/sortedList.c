#include "sortedList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode* next;
} ListNode;

struct SortedList {
    struct ListNode* _head;
};

static ListNode* allocListNode(int value)
{
    ListNode* ptr = malloc(sizeof(struct ListNode));
    if (ptr == NULL)
        return ptr;

    ptr->value = value;
    ptr->next = NULL;
    return ptr;
}

SortedList* sortedListAlloc()
{
    SortedList* pList = malloc(sizeof(*pList));
    if (pList == NULL)
        return NULL;

    pList->_head = NULL;
    return pList;
}

void sortedListFree(SortedList** pList)
{
    if (pList == NULL || *pList == NULL)
        return;

    ListNode* ptr = (*pList)->_head;
    while (ptr != NULL) {
        ListNode* temp = ptr->next;
        free(ptr);
        ptr = temp;
    }

    free(*pList);
    *pList = NULL;
}

bool sortedListInsert(SortedList* pList, int value)
{
    if (pList == NULL)
        return false;

    ListNode* newNode = allocListNode(value);
    if (newNode == NULL)
        return false;

    if (pList->_head == NULL) {
        pList->_head = newNode;
        return true;
    }

    if (pList->_head->value >= value) {
        newNode->next = pList->_head;
        pList->_head = newNode;
        return true;
    }

    ListNode* ptr = pList->_head;
    while (ptr->next != NULL && ptr->next->value < value)
        ptr = ptr->next;

    newNode->next = ptr->next;
    ptr->next = newNode;

    return true;
}

bool sortedListRemoveIndex(SortedList* pList, int index)
{
    if (pList == NULL || pList->_head == NULL || index < 0)
        return false;

    if (index == 0) {
        ListNode* temp = pList->_head;
        pList->_head = temp->next;
        free(temp);
        return true;
    }

    int i = 1;
    ListNode* ptr = pList->_head;
    for (; ptr->next != NULL && i < index; i++, ptr = ptr->next)
        ;

    if (ptr->next != NULL) {
        ListNode* temp = ptr->next;
        ptr->next = temp->next;
        free(temp);
        return true;
    }

    return false;
}

bool sortedListRemoveValue(SortedList* pList, int value)
{
    if (pList == NULL || pList->_head == NULL) {
        return false;
    } else if (pList->_head->value == value) {
        ListNode* temp = pList->_head;
        pList->_head = pList->_head->next;
        free(temp);
        return true;
    }

    ListNode* ptr = pList->_head;
    for (; ptr->next != NULL && ptr->next->value < value; ptr = ptr->next)
        ;

    if (ptr->next != NULL && ptr->next->value == value) {
        ListNode* temp = ptr->next;
        ptr->next = ptr->next->next;
        free(temp);
        return true;
    }

    return false;
}

void sortedListPrint(const SortedList* pList)
{
    if (pList == NULL) {
        printf("[NULL]\n");
        return;
    }

    putchar('[');

    for (ListNode* ptr = pList->_head; ptr != NULL; ptr = ptr->next) {
        printf("%d", ptr->value);
        if (ptr->next != NULL)
            printf(", ");
    }

    printf("]\n");
}

bool sortedListGet(const SortedList* pList, int index, int* value)
{
    if (pList == NULL)
        return false;
    ListNode* ptr = pList->_head;
    for (int i = 0; i < index && ptr != NULL; i++, ptr = ptr->next)
        ;

    if (ptr != NULL) {
        *value = ptr->value;
        return true;
    }

    return false;
}

bool isSortedListEmpty(const SortedList* pList)
{
    return pList != NULL && pList->_head == NULL;
}