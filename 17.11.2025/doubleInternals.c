#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define MANTISSA_MASK (((uint64_t)1 << 52) - 1)
#define EXPONENT_MASK ((((uint64_t)1 << 11) - 1) << 52)
#define SIGN_MASK ((uint64_t)1 << 63)

#define EXTRACT_MANTISSA(bits) ((bits) & MANTISSA_MASK)
#define EXTRACT_EXPONENT(bits) (((bits) & EXPONENT_MASK) >> 52)
#define EXTRACT_SIGN(bits) (((bits) & SIGN_MASK) ? '-' : '+')

typedef union FloatingNumber {
    double number;
    uint64_t bits;
} FloatingNumber;

bool scanNumber(double* num, const char* prompt)
{
    int res = 0;
    do {
        printf("%s\n", prompt);
        res = scanf("%lf", num);
        if (res == 0)
            while (getchar() != '\n')
                ;
    } while (res == 0);

    return res == 1;
}

int main(int argc, char** argv)
{
    FloatingNumber num = { .number = 0.0 };
    if (!scanNumber(&num.number, "Please, enter a number:"))
        return 1;

    printf("You've entered %lf\n", num.number);

    char sign = EXTRACT_SIGN(num.bits);
    uint32_t exponent = EXTRACT_EXPONENT(num.bits);
    double mantissa = EXTRACT_MANTISSA(num.bits);

    /*
     * Formula to extract floating number is
     * sign * (1 + mantissa / 2^52) * 2^(exponent - 1023)
     */
    printf("It can be represented as %c%.20g*2^%d\n",
        sign, (1 + mantissa / ((uint64_t)1 << 52)), exponent - 1023);

    return 0;
}
