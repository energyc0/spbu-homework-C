#include "binaryNumbers.h"
#include <stdbool.h>

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

int main(void)
{
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