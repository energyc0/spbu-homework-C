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
    for (int bit = 0; bit < totalBits; bit++) {
        bool hasBitA = (a & (1<<bit));
        bool hasBitB = (b & (1<<bit));
        /* Found the difference */
        if (hasBitA != hasBitB) {
            return hasBitA ? 1 : -1;
        }
    }
    return 0;
}



int launchTests()
{
    struct {
        unsigned int a;
        unsigned int b;
        int expected;
    } testcases[] = {
        {11, 12, -1},
        {INT_MAX, INT_MAX, 0},
        {INT_MIN, INT_MIN, 0},
        {INT_MIN, INT_MAX, -1},
        {INT_MAX, INT_MIN, 1},
        {1, 0, 0}
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

int main(int argc, char** argv)
{
    launchTests();
    return 0;
}