#include "stack.h"
#include <stdio.h>

typedef struct StackNode {
    int val;
    struct StackNode* prev;
} StackNode;

static StackNode* _stackNodeAlloc(int val)
{
    StackNode* ptr = (StackNode*)malloc(sizeof(struct StackNode));
    if (ptr == NULL)
        return ptr;

    ptr->val = val;
    ptr->prev = NULL;
    return ptr;
}

static void _stackNodeFree(StackNode* node)
{
    free(node);
}

Stack* stackAlloc()
{
    Stack* ptr = (Stack*)malloc(sizeof(struct Stack));
    if (ptr == NULL)
        return ptr;

    stackInit(ptr);
    return ptr;
}

void stackFree(Stack* st)
{
    StackNode* ptr = st->_data;
    while (ptr != NULL) {
        StackNode* temp = ptr->prev;
        _stackNodeFree(ptr);
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
    StackNode* ptr = _stackNodeAlloc(val);
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
    _stackNodeFree(ptr);

    return data;
}

bool stackEmpty(const Stack* st)
{
    return st->_data == NULL;
}