#include "stack.h"
#include <stdio.h>

typedef struct StackNode {
    int val;
    struct StackNode* prev;
} StackNode;

static StackNode* stackNodeAlloc(int val)
{
    StackNode* ptr = (StackNode*)malloc(sizeof(struct StackNode));
    if (ptr == NULL)
        return ptr;

    ptr->val = val;
    ptr->prev = NULL;
    return ptr;
}

void stackFree(Stack* st)
{
    StackNode* ptr = st->_data;
    while (ptr != NULL) {
        StackNode* temp = ptr->prev;
        free(ptr);
        ptr = temp;
    }
}

void stackInit(Stack* st)
{
    st->_data = NULL;
}

int stackPeek(const Stack* st)
{
    return st->_data->val;
}

bool stackPush(Stack* st, int val)
{
    StackNode* ptr = stackNodeAlloc(val);
    if (ptr == NULL)
        return false;

    ptr->prev = st->_data;
    st->_data = ptr;

    return true;
}

int stackPop(Stack* st)
{
    int data = st->_data->val;
    StackNode* ptr = st->_data;
    st->_data = st->_data->prev;
    free(ptr);

    return data;
}

bool isStackEmpty(const Stack* st)
{
    return st->_data == NULL;
}