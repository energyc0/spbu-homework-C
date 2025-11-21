#include "binaryNumbers.h"
#include <stdbool.h>

bool scanNum(int *num, const char* prompt)
{
    int res = 0;
    do {
        printf("%s\n", prompt);
        res = scanf("%d", num);
        if (res == 0)
            while(getchar() != '\n');

    } while (res == 0);

    return res == 1;
}

int main()
{
    int num1 = 0;
    if (!scanNum(&num1, "Enter number 'A':"))
        return 1;
    int num2 = 0;
    if(!scanNum(&num2, "Enter number 'B':"))
        return 1;

    printf("Calculating...\n"); 
    BinaryNumber* binNum1 = binaryNumberCreate(num1);
    binaryNumberPrint(stdout, binNum1);
    putchar('\n');

    printf("+\n");

    BinaryNumber* binNum2 = binaryNumberCreate(num2);
    binaryNumberPrint(stdout, binNum2);
    putchar('\n');

    /*BinaryNumber* result  = binaryNumberAdd(binNum1, binNum2, NULL);

    printf("=\n");
    binaryNumberPrint(stdout, result);
    putchar('\n');
    printf("Result: %d\n", binaryNumberToDecimal(result));
*/
    binaryNumberFree(&binNum1);
    binaryNumberFree(&binNum2);
    //binaryNumberFree(&result);
    return 0;
}