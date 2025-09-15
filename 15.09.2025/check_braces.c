#include <stdio.h>

/*
 * 1    - braces are closed
 * 0    - braces are not closed
 * -1   - undefined character
 */

int isClosedBraces(const char* str)
{
    int k = 0;
    for (const char* p = str; *p != '\0'; p++) {
        if (*p == '(') {
            k++;
        } else if (*p == ')') {
            if (--k < 0)
                return -1;
        }
    }
    return k == 0;
}

void printOutput(const char* str)
{
    printf("isClosedBraces(%s) = %d\n", str, isClosedBraces(str));
}

int main() 
{
    printOutput("()()((()()))");
    printOutput("(0()))");
    printOutput("()(");
}