#include <stdio.h>

#define LIMIT_FIB 1000000

/*
 * Counts the sum of the even fibonacci numbers <= limit.
 */
long long unsigned evenFibNumbersCount(const long long unsigned limit)
{
    long long unsigned result = 0;
    long long unsigned prev = 0;
    long long unsigned cur = 1;

    for (int idx = 1; cur <= limit; idx++) {
        if (idx % 2 == 0)
            result += cur;

        long long unsigned temp = cur + prev;
        prev = cur;
        cur = temp;
    }

    return result;
}

int main(void)
{
    printf("%llu\n", evenFibNumbersCount(LIMIT_FIB));
    return 0;
}