#include <stdio.h>
#include <stdlib.h>

#define errQuit(msg) do { \
        fprintf(stderr, msg);\
        putc('\n', stderr); \
        exit(EXIT_FAILURE);\
    } while (0) 

int calculateDivision(int a, int b)
{
    if (b == 0)
        errQuit("Division by zero");
    int sign = (((a > 0) ^ (b > 0)) ? -1 : 1);
    a = abs(a);
    b = abs(b);
    int res = 0;
    while (a >= b) {
        a -= b;
        res++;
    }
    return res * sign + (a > 0 && sign == -1 ? -1 : 0);
}

int getNum() 
{
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) 
        errQuit("Expected a number");
    return num;
}

int main(void)
{
    int a = getNum();
    int b = getNum();
    printf("Result: %d\n", calculateDivision(a,b));

    return 0;
}