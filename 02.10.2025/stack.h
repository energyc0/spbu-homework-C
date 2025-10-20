#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct Stack Stack;

/*
 * Free stack internals and pointer.
 * Pointer = NULL after call.
 */
void stackFree(Stack** st);

/*
 * Allocate stack structure.
 */
Stack* stackAlloc();

/*
 * Push value on the stack.
 */
bool stackPush(Stack* st, int val);

/*
 * Return top value from the stack.
 * User must check if stack is empty to prevent undefined behavior.
 */
int stackPeek(const Stack* st);

/*
 * Pop value from the stack and return it.
 * User must check if stack is empty to prevent undefined behavior.
 */
int stackPop(Stack* st);

/*
 * Return true if stack is empty.
 */
bool isStackEmpty(const Stack* st);