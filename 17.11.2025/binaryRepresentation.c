#include "binaryNumbers.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool scanNum(int* num, const char* prompt)
{
    int res = 0;
    do {
        printf("%s\n", prompt);
        res = scanf("%d", num);
        if (res == 0)
            while (getchar() != '\n')
                ;

    } while (res == 0);

    return res == 1;
}

#ifdef DEBUG
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void printUsage(FILE* stream, const char* programName)
{
    const char* flags[] = { "--help", "--test" };
    const char* descriptions[] = { "Print help information.", "Launch tests." };
    fprintf(stream, "Usage: %s [flags]\n", programName);
    fprintf(stream, "FLAGS:\n");
    for (int i = 0; i < (int)ARRAY_SIZE(flags); i++)
        fprintf(stream, "  %-12s %s\n", flags[i], descriptions[i]);
}

#undef ARRAY_SIZE
#endif

int main(int argc, char** argv)
{
#ifdef DEBUG
    if (argc > 2) {
        printUsage(stderr, argv[0]);
        return 1;
    }

    if (argc == 2) {
        if (strcmp("--help", argv[1]) == 0) {
            printUsage(stdout, argv[0]);
            return 0;
        }
        if (strcmp("--test", argv[1]) == 0)
            return binaryNumberRunTests();
        printUsage(stderr, argv[0]);
        return 1;
    }
#else
    /*
     * Unused.
     */
    ((void)argc);
    ((void)argv);
#endif
    int num1 = 0;
    if (!scanNum(&num1, "Enter number 'A':"))
        return 1;
    int num2 = 0;
    if (!scanNum(&num2, "Enter number 'B':"))
        return 1;

    printf("Calculating...\n");
    BinaryNumber* binNum1 = binaryNumberCreate(num1);
    if (binNum1 == NULL)
        return 1;
    binaryNumberPrint(stdout, binNum1);
    printf("\n+\n");

    BinaryNumber* binNum2 = binaryNumberCreate(num2);
    if (binNum2 == NULL)
        return 1;
    binaryNumberPrint(stdout, binNum2);

    BinaryNumber* result = binaryNumberAdd(binNum1, binNum2, NULL);
    if (result == NULL)
        return 1;

    printf("\n=\n");
    binaryNumberPrint(stdout, result);
    printf("\nResult: %d\n", binaryNumberToDecimal(result));

    binaryNumberFree(&binNum1);
    binaryNumberFree(&binNum2);
    binaryNumberFree(&result);

    return 0;
}