#include <stdio.h>

/*
 * 1    - braces are closed
 * 0    - braces are not closed
 * -1   - undefined character or unknown brace
 */

int isClosedBraces(const char* str)
{
    char start;
    char end;
    switch (str[0]) {
    case '(':
        start = '(';
        end = ')';
        break;
    case '[':
        start = '[';
        end = ']';
        break;
    case '{':
        start = '{';
        end = '}';
        break;
    case '<':
        start = '<';
        end = '>';
        break;
    case ')':
    case ']':
    case '}':
    case '>':
        return 0;
    case '\0':
        return 1;
    default:
        return -1;
    }

    int k = 0;
    for (const char* p = str; *p != '\0'; p++) {
        if (*p == start) {
            k++;
        } else if (*p == end) {
            --k;
            if (k < 0)
                return -1;
        }
    }
    return k == 0;
}

void printOutput(const char* str)
{
    printf("isClosedBraces(\"%s\") = %d\n", str, isClosedBraces(str));
}

int main()
{
    printOutput("()()((()()))");
    printOutput("(0()))");
    printOutput("<><><");
    printOutput("][][");
    printOutput("[][[[]]]");
    printOutput("{}{{}}");
}