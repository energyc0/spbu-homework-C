#include "binaryNumbers.h"
#include <stdlib.h>
#include <string.h>

#define BINARY_NUMBER_SIZE 32
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct BinaryNumber {
    char data[BINARY_NUMBER_SIZE];
} BinaryNumber;

BinaryNumber* binaryNumberAlloc()
{
    BinaryNumber* ptr = malloc(sizeof(*ptr));
    if (ptr == NULL)
        return NULL;
    memset(ptr->data, '0', sizeof(ptr->data));
    return ptr;
}

BinaryNumber* binaryNumberAssign(BinaryNumber* binNum, int decNum)
{
    if (binNum == NULL)
        return NULL;

    const int decSize = sizeof(decNum) * 8;
    for (int bit = decSize-1; bit >= 0; bit--) {
        binNum->data[bit] = ((decNum & (1 << (decSize - bit-1))) ? '1' : '0');
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

}

int binaryNumberToDecimal(const BinaryNumber* num);

void binaryNumberPrint(FILE* stream, const BinaryNumber* num)
{
    for (int byte = 0; byte < BINARY_NUMBER_SIZE / 8; byte++)
        fprintf(stream, "%.*s ", 8,  num->data + byte * 8);
}

void binaryNumberFree(BinaryNumber** binNum)
{
    free(*binNum);
    *binNum = NULL;
}