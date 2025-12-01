#include <stdio.h>
#include <stdbool.h>

unsigned int binaryCompare(unsigned int a, unsigned int b)
{
    const int totalBits = sizeof(a)*8;
    for (int bit = 0; bit < totalBits; bit++) {
        bool hasBitA = (a & (1<<bit));
        bool hasBitB = (b & (1<<bit));
        /* Find the difference */
        if (hasBitA != hasBitB) {
            return hasBitA ? a : b;
        }
    }
    /* Return a or b, because they are equal. */
    return a;
}

int main(int argc, char** argv)
{
    printf("%u\n", binaryCompare(11, 8));
    return 0;
}