#include <stdio.h>
#include <string.h>

int countSubStrs(const char* s, const char* s1)
{
    int k = 0;
    const int len = strlen(s);
    const int subLen = strlen(s1);

    for (int i = 0; i < len - subLen + 1; i++) {
        if (memcmp(s + i, s1, subLen) == 0)
            k++;
    }

    return k;
}

int main(void)
{
    printf("%d\n", countSubStrs("abcabcaaaabccc", "abc"));
    printf("%d\n", countSubStrs("aaa", "a"));
    printf("%d\n", countSubStrs("aaaa", "aa"));
    return 0;
}