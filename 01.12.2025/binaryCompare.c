#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/* 
 * Compare two unsigned numbers.
 * Return 0, if a == b,
 * Return 1, if a > b,
 * Return -1, if a < b.
 */
int binaryCompare(unsigned int a, unsigned int b)
{
    const int totalBits = sizeof(a)*8;
    /* Start compate from the biggest byte. */
    for (int bit = totalBits-1; bit >= 0; bit--) {
        bool hasBitA = (a & (1<<bit));
        bool hasBitB = (b & (1<<bit));
        /* Found the difference */
        if (hasBitA != hasBitB) {
            return hasBitA ? 1 : -1;
        }
    }
    return 0;
}

/*
 * Launch tests for binaryCompare().
 * Return 0, if successful,
 * Return 1, if failed.
 */
int launchTests()
{
    struct {
        unsigned int a;
        unsigned int b;
        int expected;
    } testcases[] = {
        {11, 12, -1},
        {UINT_MAX, UINT_MAX, 0},
        {0, 0, 0},
        {0, UINT_MAX, -1},
        {UINT_MAX, 0, 1},
        {65, 63, 1},
        {125, 127, -1},
        {25,25,0}
    };
    int returnCode = 0;

    for (int i = 0; i < ARRAY_SIZE(testcases); i++) {
        int res = binaryCompare(testcases[i].a, testcases[i].b);
        if (res != testcases[i].expected) {
            fprintf(stderr, "binaryCompare(%u, %u) - failed,\n"
            "expected %d, found %d.\n",
            testcases[i].a, testcases[i].b, testcases[i].expected, res);
            returnCode = 1;
        }
    }

    printf("Tests %s\n", returnCode == 0 ? "passed" : "failed");
    return returnCode;
}

int main(void)
{
    return launchTests();
}