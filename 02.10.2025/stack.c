#include "stack.h"
#include <stdio.h>

typedef struct StackNode {
    int val;
    struct StackNode* prev;
} StackNode;

typedef struct Stack {
    struct StackNode* data;
} Stack;

static StackNode* stackNodeAlloc(int val)
{
    StackNode* ptr = (StackNode*)malloc(sizeof(*ptr));
    if (ptr == NULL)
        return ptr;

    ptr->val = val;
    ptr->prev = NULL;
    return ptr;
}

void stackFree(Stack** st)
{
    StackNode* ptr = (*st)->data;
    while (ptr != NULL) {
        StackNode* temp = ptr->prev;
        free(ptr);
        ptr = temp;
    }

    free(*st);
    *st = NULL;
}

Stack* stackAlloc()
{
    Stack* ptr = malloc(sizeof(*ptr));
    if (ptr == NULL)
        return ptr;
    ptr->data = NULL;
    return ptr;
}

int stackPeek(const Stack* st)
{
    return st->data->val;
}

bool stackPush(Stack* st, int val)
{
    StackNode* ptr = stackNodeAlloc(val);
    if (ptr == NULL)
        return false;

    ptr->prev = st->data;
    st->data = ptr;

    return true;
}

int stackPop(Stack* st)
{
    int data = st->data->val;
    StackNode* ptr = st->data;
    st->data = st->data->prev;
    free(ptr);

    return data;
}

bool isStackEmpty(const Stack* st)
{
    return st->data == NULL;
}