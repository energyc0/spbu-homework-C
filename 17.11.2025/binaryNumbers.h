#pragma once

/*
 * Binary numbers library, implemented for 'int' type.
 */

#include <stdio.h>

typedef struct BinaryNumber BinaryNumber;

/*
 * Allocate newly created binary number initialized with decNum,
 * must call binaryNumberFree() to free memory.
 */
BinaryNumber* binaryNumberCreate(int decNum);

/*
 * Assign decNum to binNum.
 */
BinaryNumber* binaryNumberAssign(BinaryNumber* binNum, int decNum);

/*
 * Add values 'a' and 'b' and store them in 'result'.
 * If 'a' or 'b' equals NULL, function returns NULL.
 * If 'result' equals NULL, function allocate new BinaryNumber
 * and store the result there.
 * Addition may lead to overflow!
 */
BinaryNumber* binaryNumberAdd(const BinaryNumber* a, const BinaryNumber* b, BinaryNumber* result);

/*
 * Convert binary number to decimal.
 * Returns zero if binNum equals NULL.
 */
int binaryNumberToDecimal(const BinaryNumber* binNum);

/*
 * Prints binNum if it is a non-NULL pointer to the given stream.
 */
void binaryNumberPrint(FILE* stream, const BinaryNumber* binNum);

/*
 * Frees memory for *binNum and set *binNum pointer to NULL
 */
void binaryNumberFree(BinaryNumber** binNum);

#ifdef DEBUG
/*
 * Run tests and return exit code.
 * 0 - success, 1 - failed.
 */
int binaryNumberRunTests();
#endif
