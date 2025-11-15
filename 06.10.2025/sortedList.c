#include "sortedList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode* next;
} ListNode;

static ListNode* allocListNode(int value);

ListNode* allocListNode(int value)
{
    ListNode* ptr = malloc(sizeof(struct ListNode));
    if (ptr == NULL)
        return ptr;

    ptr->value = value;
    ptr->next = NULL;
    return ptr;
}

void sortedListInit(SortedList* pList)
{
    pList->_head = NULL;
}

void sortedListFree(SortedList* pList)
{
    ListNode* ptr = pList->_head;
    while (ptr != NULL) {
        ListNode* temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
}

bool sortedListInsert(SortedList* pList, int value)
{
    ListNode* newNode = allocListNode(value);
    if (newNode == NULL)
        return false;

    if (pList->_head == NULL) {
        pList->_head = newNode;
        return true;
    } else if (pList->_head->value >= value) {
        newNode->next = pList->_head;
        pList->_head = newNode;
        return true;
    }

    ListNode* ptr = pList->_head;
    for (; ptr->next && ptr->next->value < value; ptr = ptr->next)
        ;

    newNode->next = ptr->next;
    ptr->next = newNode;

    return true;
}

bool sortedListRemoveIndex(SortedList* pList, int index)
{
    if (pList->_head == NULL || index < 0)
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
    if (pList->_head == NULL) {
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
    return pList->_head == NULL;
}