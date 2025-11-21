#pragma once

#include <stdio.h>

typedef struct BinaryNumber BinaryNumber;

BinaryNumber* binaryNumberAlloc();

BinaryNumber* binaryNumberAssign(BinaryNumber* binNum, int decNum);

BinaryNumber* binaryNumberCreate(int decNum);

BinaryNumber* binaryNumberAdd(const BinaryNumber* a, const BinaryNumber* b, BinaryNumber* result);

int binaryNumberToDecimal(const BinaryNumber* binNum);

void binaryNumberPrint(FILE* stream, const BinaryNumber* binNum);

void binaryNumberFree(BinaryNumber** binNum);
