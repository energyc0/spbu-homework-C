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

    static char buf[BINARY_NUMBER_STR_SIZE] = {};
    fprintf(stream, "%s", binaryNumberToStr(num, buf));
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
    return memcmp(a->data, b->data, BINARY_NUMBER_SIZE);
}

char* binaryNumberToStr(const BinaryNumber* num, char* buf)
{
    if (buf == NULL)
        return buf;

    int idx = 0;
    for (int bit = 0; bit < (int)BINARY_NUMBER_SIZE; bit++) {
        if (bit % 8 == 0 && bit > 0)
            buf[idx++] = ' ';
        buf[idx++] = (num->data[bit] == 0 ? '0' : '1');
    }
    buf[idx] = '\0';

    return buf;
}

#ifdef DEBUG

void fprintDebug(int line, FILE* stream, const char* msg)
{
    fprintf(stream, "[Line: %d] %s\n", line, msg);
}

void eprintDebug(int line, int* returnCode, const char* msg)
{
    *returnCode = 1;
    fprintDebug(line, stderr, msg);
}

void expectBinary(int line, int* returnCode, const BinaryNumber* binNum, const char* expectBin, int expectDec)
{
    static char binBuf[BINARY_NUMBER_STR_SIZE] = {};
    char msgBuf[256] = {};
    binaryNumberToStr(binNum, binBuf);
    if (memcmp(binBuf, expectBin, BINARY_NUMBER_STR_SIZE) != 0) {
        sprintf(msgBuf, "Unexpected binary number,\n"
                        "\texpected: %.*s,\n\tfound %.*s.",
            (int)BINARY_NUMBER_STR_SIZE, expectBin,
            (int)BINARY_NUMBER_STR_SIZE, binBuf);
        eprintDebug(line, returnCode, msgBuf);
    }

    int decimal = binaryNumberToDecimal(binNum);
    if (decimal != expectDec) {
        sprintf(msgBuf, "Unexpected binary to decimal conversion,\n"
                        "\texpected: %d,\n\tfound: %d.",
            expectDec, decimal);
        eprintDebug(line, returnCode, msgBuf);
    }
}

typedef struct {
    int a;
    int b;
    const char* binStrA;
    const char* binStrB;
    const char* binStrRes;
} BinaryCheckAdditionArgs;

void binaryCheckAddition(int line, const BinaryCheckAdditionArgs* args, int* returnCode)
{
    BinaryNumber* binA = binaryNumberCreate(args->a);
    BinaryNumber* binB = binaryNumberCreate(args->b);

    expectBinary(line, returnCode, binA, args->binStrA, args->a);
    expectBinary(line, returnCode, binB, args->binStrB, args->b);

    BinaryNumber* result = NULL;
    if ((result = binaryNumberAdd(binA, binB, result)) != NULL) {
        expectBinary(line, returnCode, result,
            args->binStrRes, args->a + args->b);
    } else {
        eprintDebug(line, returnCode, "Failed to perform addition!\n");
    }
}

int binaryNumberRunTests()
{
    int returnCode = 0;

    BinaryCheckAdditionArgs args = {
        .a = 6,
        .b = 17,
        .binStrA = "00000000 00000000 00000000 00000110",
        .binStrB = "00000000 00000000 00000000 00010001",
        .binStrRes = "00000000 00000000 00000000 00010111"
    };
    binaryCheckAddition(__LINE__, &args, &returnCode);

    if (returnCode == 0)
        printf("Passed tests.\n");
    else
        fprintf(stderr, "Failed tests.\n");

    return returnCode;
}
#endif
