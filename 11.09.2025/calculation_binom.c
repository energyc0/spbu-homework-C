#include <stdio.h>

int calculation_binom(int x)
{
    int xx = x * x;
    return (xx + x) * (xx + 1) + 1;
}

int main(void)
{
    int x;
    printf("Enter a number: ");
    if (scanf("%d", &x) != 1) {
        fprintf(stderr, "Expected a number\n");
        return 1;
    }
    printf("Result: %d\n", calculation_binom(x));
    return 0;
}