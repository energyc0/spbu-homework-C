#include "recursiveList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

/*
 * Get the actual index of element.
 */
static int roundIndex(int idx, int listSize)
{
    idx = idx % listSize;
    if (idx < 0)
        idx = listSize + idx;
    return idx;
}

static ListNode* allocListNode(int data, ListNode* next, ListNode* prev)
{
    ListNode* ptr = malloc(sizeof(struct ListNode));
    if (ptr == NULL)
        return ptr;

    ptr->data = data;
    ptr->next = next;
    ptr->prev = prev;
    return ptr;
}

/*
 * Return the next node of deleted node.
 * Node must be a node of pList.
 */
static ListNode* deleteNodeRecursiveList(RecursiveList* pList, ListNode* node)
{
    if (pList->_head == NULL)
        return NULL;
    if (node == pList->_head) {
        if (node->next == node)
            pList->_head = NULL;
        else
            pList->_head = pList->_head->next;
    }

    ListNode* prev = node->prev;
    ListNode* next = node->next;
    prev->next = next;
    next->prev = prev;

    pList->_size--;
    free(node);
    return pList->_head == NULL ? NULL : next;
}

/*
 * Get node of the given index
 */
static ListNode* getNodeRecursiveList(const RecursiveList* pList, int idx)
{
    if (pList->_head == NULL)
        return NULL;

    ListNode* node = pList->_head;
    for (int i = 0; i < idx; i++, node = node->next)
        ;

    return node;
}

RecursiveList makeRecursiveList(const int* values, int size)
{
    RecursiveList list = { ._head = NULL, ._size = 0 };
    ListNode* tail = NULL;

    if (size > 0) {
        list._head = allocListNode(values[0], NULL, NULL);
        if (list._head == NULL)
            return list;
        list._head->prev = list._head->next = tail = list._head;
        list._size = size;
    }

    for (int i = 1; i < size; i++) {
        tail->next = allocListNode(values[i], list._head, tail);
        list._head->prev = tail->next;
        tail = tail->next;
    }

    return list;
}

void freeRecursiveList(RecursiveList* pList)
{
    if (pList->_head == NULL)
        return;

    for (ListNode* p = pList->_head;;) {
        ListNode* temp = p->next;
        free(p);
        if (temp == pList->_head)
            break;
        p = temp;
    }
    pList->_head = NULL;
    pList->_size = 0;
}

bool eraseRecursiveList(RecursiveList* pList, int idx)
{
    if (pList->_head == NULL)
        return false;

    idx = roundIndex(idx, pList->_size);
    ListNode* node = getNodeRecursiveList(pList, idx);
    deleteNodeRecursiveList(pList, node);

    return true;
}

void printRecursiveList(const RecursiveList* pList)
{
    putchar('[');
    if (pList->_head != NULL) {
        for (ListNode* p = pList->_head;; p = p->next) {
            printf("%d", p->data);
            if (p->next != pList->_head)
                printf(", ");
            else
                break;
        }
    }
    printf("]\n");
}

void printRecursiveListReverse(const RecursiveList* pList)
{
    putchar('[');
    if (pList->_head != NULL) {
        for (ListNode* p = pList->_head->prev;; p = p->prev) {
            printf("%d", p->data);
            if (p->prev != pList->_head)
                printf(", ");
            else
                break;
        }
    }
    printf("]\n");
}

bool getRecursiveList(const RecursiveList* pList, int idx, int* val)
{
    ListNode* p = getNodeRecursiveList(pList, idx);
    if (p == NULL)
        return false;

    *val = p->data;
    return true;
}

void removeSequenceRecursiveList(RecursiveList* pList, int m, bool isVerbose)
{
    if (pList->_head == NULL)
        return;

    m = roundIndex(m, pList->_size);
    printRecursiveList(pList);

    ListNode* p = pList->_head;
    while (pList->_head->next != pList->_head) {
        for (int i = 1; i < m; i++, p = p->next)
            ;
        p = deleteNodeRecursiveList(pList, p);
        if (isVerbose)
            printRecursiveList(pList);
    }
}

int getSizeRecursiveList(const RecursiveList* pList)
{
    return pList->_size;
}
