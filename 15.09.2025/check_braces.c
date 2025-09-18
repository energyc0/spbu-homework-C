#include <stdbool.h>
#include <stdio.h>

bool isClosedBraces(const char* str)
{
    int k = 0;
    for (const char* p = str; *p != '\0'; p++) {
        if (*p == '(') {
            k++;
        } else if (*p == ')') {
            k--;
            if (k < 0)
                return false;
        }
    }
    return k == 0;
}

void printOutput(const char* str)
{
    printf("isClosedBraces(\"%s\") = %s\n",
        str,
        isClosedBraces(str) ? "true" : "false");
}

int main()
{
    printOutput("ab(cd)e)");
    printOutput("if () else ");
    printOutput("(1 + 2 * (3-1))");
    printOutput("(1 + 2");
}