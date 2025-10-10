#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
 * false    - braces are not balanced.
 * true     - braces are balanced.
 */
bool checkBraceBalance(const char* str)
{
    Stack st;
    stackInit(&st);

    for (const char* ptr = str; *ptr != '\0'; ptr++) {
        switch (*ptr) {
        case '(':
        case '{':
        case '[':
            stackPush(&st, *ptr);
            break;
        case ')':
            if (isStackEmpty(&st) || stackPop(&st) != '(') {
                stackFree(&st);
                return false;
            }
            break;
        case ']':
            if (isStackEmpty(&st) || stackPop(&st) != '[') {
                stackFree(&st);
                return false;
            }
            break;
        case '}':
            if (isStackEmpty(&st) || stackPop(&st) != '{') {
                stackFree(&st);
                return false;
            }
            break;
        }
    }

    bool res = isStackEmpty(&st);
    stackFree(&st);
    return res;
}

int main(void)
{
    char buf[BUFSIZ];
    printf("Enter string of braces - (), [] or {}:\n");
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return 0;

    int res = checkBraceBalance(buf);
    printf("String is %s\n", res ? "balanced" : "not balanced");

    return res;
}