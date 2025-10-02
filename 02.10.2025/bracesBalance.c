#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*
 * -1   - error occured.
 * 0    - braces are not balanced.
 * 1    - braces are balanced.
 */
int checkBraceBalance(const char* str)
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
            if (stackEmpty(&st) || stackPop(&st) != '(') {
                stackFree(&st);
                return 0;
            }
            break;
        case ']':
            if (stackEmpty(&st) || stackPop(&st) != '[') {
                stackFree(&st);
                return 0;
            }
            break;
        case '}':
            if (stackEmpty(&st) || stackPop(&st) != '{') {
                stackFree(&st);
                return 0;
            }
            break;
        default:
            fprintf(stderr, "Undefined character.\n");
            stackFree(&st);
            return -1;
        }
    }

    int res = stackEmpty(&st);
    stackFree(&st);
    return res;
}

int main(void)
{
    char buf[BUFSIZ];
    printf("Enter string of braces - (), [] or {}:\n");
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return 0;

    buf[strcspn(buf, "\n")] = '\0';
    int res = checkBraceBalance(buf);
    if (res == -1)
        return 1;
    else
        printf("String is %s\n", res ? "balanced" : "not balanced");
    return 0;
}