#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define TEST1 "abcdcba"
#define TEST2 "was it a cat i saw"
#define TEST3 "sit on a potato pan otis"
#define TEST4 "abc"
#define TEST5 "abc aba"

bool isPalindrome(const char* s)
{
    const char* start = s;
    const char* end = start + strlen(s) - 1;

    for (; start < end; start++, end--) {
        for (; start < end && isspace(*start); start++)
            ;
        for (; start < end && isspace(*end); end--)
            ;

        if (*start != *end)
            return false;
    }

    return true;
}

void printIsPalindrome(const char* s)
{
    printf("'%s' is %s\n", s, isPalindrome(s) ? "palindrome" : "not palindrome");
}

int main(void)
{
    printIsPalindrome(TEST1);
    printIsPalindrome(TEST2);
    printIsPalindrome(TEST3);
    printIsPalindrome(TEST4);
    printIsPalindrome(TEST5);
    return 0;
}