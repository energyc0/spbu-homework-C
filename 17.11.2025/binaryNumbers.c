#include "binaryNumbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Binary numbers library, implemented for 'int' type.
 */

#define BINARY_NUMBER_SIZE (sizeof(int) * 8)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct BinaryNumber {
    char data[BINARY_NUMBER_SIZE];
} BinaryNumber;

/*
 * Allocate new binary number and initialize it with zero.
 */
static BinaryNumber* binaryNumberAlloc()
{
    BinaryNumber* ptr = malloc(sizeof(*ptr));
    if (ptr == NULL) {
        fprintf(stderr, "Failed to allocate BinaryNumber!\n");
        return NULL;
    }
    memset(ptr->data, 0, sizeof(ptr->data));
    return ptr;
}

BinaryNumber* binaryNumberAssign(BinaryNumber* binNum, int decNum)
{
    if (binNum == NULL)
        return NULL;

    if (decNum == 0) {
        memset(binNum->data, 0, sizeof(binNum->data));
        return binNum;
    }
    for (int bit = BINARY_NUMBER_SIZE - 1; bit >= 0; bit--) {
        binNum->data[bit] = ((decNum & (1 << (BINARY_NUMBER_SIZE - bit - 1))) ? 1 : 0);
    }

    return binNum;
}

BinaryNumber* binaryNumberCreate(int decNum)
{
    BinaryNumber* ptr = binaryNumberAlloc();
    return binaryNumberAssign(ptr, decNum);
}

BinaryNumber* binaryNumberAdd(const BinaryNumber* a, const BinaryNumber* b, BinaryNumber* result)
{
    if (a == NULL || b == NULL)
        return NULL;

    if (result == NULL) {
        result = binaryNumberAlloc();
        if (result == NULL)
            return NULL;
    }

    int carry = 0;
    for (int bit = BINARY_NUMBER_SIZE - 1; bit >= 0; bit--) {
        int res = a->data[bit] + b->data[bit] + carry;
        result->data[bit] = res % 2;
        carry = res / 2;
    }
    return result;
}

int binaryNumberToDecimal(const BinaryNumber* num)
{
    int result = 0;
    for (int bit = BINARY_NUMBER_SIZE - 1; bit >= 0; bit--)
        result += (num->data[bit] << (BINARY_NUMBER_SIZE - 1 - bit));
    return result;
}

void binaryNumberPrint(FILE* stream, const BinaryNumber* num)
{
    if (num == NULL)
        return;

    for (int bit = 0; bit < (int)BINARY_NUMBER_SIZE; bit++) {
        if (bit % 8 == 0 && bit > 0)
            putc(' ', stream);
        putc(num->data[bit] == 0 ? '0' : '1', stream);
    }
}

void binaryNumberFree(BinaryNumber** binNum)
{
    if (binNum != NULL && *binNum != NULL) {
        free(*binNum);
        *binNum = NULL;
    }
}

int binaryNumberCompare(const BinaryNumber* a, const BinaryNumber* b)
{
    if (a == NULL || b == NULL)
        return 0;
    return strncmp(a->data, b->data, BINARY_NUMBER_SIZE);
}

#ifdef DEBUG
int binaryNumberRunTests()
{
    int returnCode = 0;

    int a = 6;
    int b = 17;

    printf("Tests %s.\n", returnCode == 0 ? "succeded" : "failed");
    return returnCode;
}
#endif
