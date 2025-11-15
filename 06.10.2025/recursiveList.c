#include "recursiveList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

typedef struct RecursiveList {
    struct ListNode* head;
    int size;
} RecursiveList;

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
    if (pList->head == NULL)
        return NULL;
    if (node == pList->head) {
        if (node->next == node)
            pList->head = NULL;
        else
            pList->head = pList->head->next;
    }

    ListNode* prev = node->prev;
    ListNode* next = node->next;
    prev->next = next;
    next->prev = prev;

    pList->size--;
    free(node);
    return pList->head == NULL ? NULL : next;
}

/*
 * Get node of the given index
 */
static ListNode* getNodeRecursiveList(const RecursiveList* pList, int idx)
{
    if (pList->head == NULL)
        return NULL;

    ListNode* node = pList->head;
    for (int i = 0; i < idx; i++)
        node = node->next;

    return node;
}

RecursiveList* allocRecursiveList(const int* values, int size)
{
    RecursiveList* pList = calloc(1, sizeof(*pList));
    if (pList == NULL)
        return NULL;

    ListNode* tail = NULL;

    if (size > 0) {
        pList->head = allocListNode(values[0], NULL, NULL);
        if (pList->head == NULL) {
            freeRecursiveList(&pList);
            return NULL;
        }
        pList->head->prev = pList->head;
        pList->head->next = tail = pList->head;
        pList->size = size;
    }

    for (int i = 1; i < size; i++) {
        tail->next = allocListNode(values[i], pList->head, tail);
        if (tail->next == NULL) {
            freeRecursiveList(&pList);
            return NULL;
        }
        pList->head->prev = tail->next;
        tail = tail->next;
    }

    return pList;
}

void freeRecursiveList(RecursiveList** pList)
{
    if (pList == NULL || *pList == NULL)
        return;

    ListNode* head = (*pList)->head;
    free(*pList);
    *pList = NULL;
    if (head == NULL)
        return;

    for (ListNode* p = head;;) {
        ListNode* temp = p->next;
        free(p);
        if (temp == head)
            break;
        p = temp;
    }
}

bool eraseRecursiveList(RecursiveList* pList, int idx)
{
    if (pList->head == NULL)
        return false;

    idx = roundIndex(idx, pList->size);
    ListNode* node = getNodeRecursiveList(pList, idx);
    deleteNodeRecursiveList(pList, node);

    return true;
}

void printRecursiveList(const RecursiveList* pList)
{
    putchar('[');
    if (pList->head != NULL) {
        for (ListNode* p = pList->head;; p = p->next) {
            printf("%d", p->data);
            if (p->next != pList->head)
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
    if (pList->head != NULL) {
        for (ListNode* p = pList->head->prev;; p = p->prev) {
            printf("%d", p->data);
            if (p->prev != pList->head)
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
    if (pList->head == NULL)
        return;

    m = roundIndex(m, pList->size);
    printRecursiveList(pList);

    ListNode* p = pList->head;
    while (pList->head->next != pList->head) {
        for (int i = 1; i < m; i++, p = p->next)
            ;
        p = deleteNodeRecursiveList(pList, p);
        if (isVerbose)
            printRecursiveList(pList);
    }
}

int getSizeRecursiveList(const RecursiveList* pList)
{
    return pList->size;
}
