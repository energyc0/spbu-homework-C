#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

typedef struct Queue {
    ListNode* headRoot;
    ListNode* tailRoot;
} Queue;

void freeList(ListNode* root)
{
    while (root != NULL) {
        ListNode* p = root->next;
        free(root);
        root = p;
    }
}

ListNode* makeListNode(int data)
{
    ListNode* p = malloc(sizeof(*p));
    if (p == NULL)
        return p;

    p->data = data;
    p->next = NULL;
    return p;
}

Queue* makeQueue()
{
    Queue* p = malloc(sizeof(*p));
    if (p == NULL)
        return p;

    p->headRoot = NULL;
    p->tailRoot = NULL;
    return p;
}

void freeQueue(Queue** q)
{
    if (q == NULL || *q == NULL)
        return;

    freeList((*q)->headRoot);
    freeList((*q)->tailRoot);
    free(*q);
    *q = NULL;
}

bool enqueue(Queue* q, int n)
{
    if (q == NULL)
        return false;

    ListNode* node = makeListNode(n);
    if (node == NULL)
        return false;

    node->next = q->headRoot;
    q->headRoot = node;

    return true;
}

ListNode* reverseList(ListNode* root)
{
    if (root == NULL)
        return root;
    ListNode* newRoot = root;
    ListNode* p = root->next;

    if (p == NULL)
        return newRoot;
    ListNode* next = p->next;

    while (next != NULL) {
        p->next = newRoot;
        newRoot = p;
        p = next;

        next = next->next;
    }

    /* Destroy recursion. */
    root->next = NULL;
    p->next = newRoot;
    newRoot = p;
    for (ListNode* pp = newRoot; pp != NULL; pp = pp->next)
        printf("%d ", pp->data);
    return newRoot;
}

bool dequeue(Queue* q, int* n)
{
    if (q == NULL || n == NULL)
        return false;

    /*
     * Nodes to pop are empty.
     * Try to get nodes from head.
     */
    if (q->tailRoot == NULL) {
        /* The queue is empty */
        if (q->headRoot == NULL)
            return false;

        q->tailRoot = reverseList(q->headRoot);
        q->headRoot = NULL;
    }

    *n = q->tailRoot->data;
    ListNode* p = q->tailRoot;
    q->tailRoot = q->tailRoot->next;
    free(p);

    return true;
}