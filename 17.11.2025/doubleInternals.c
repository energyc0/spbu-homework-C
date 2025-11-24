#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

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

/*
 * Prints 'number' in 'buf' in exponential form.
 * sm*2^p, where
 * s - sign,
 * m - mantissa,
 * p - power.
 * 'buf' must have enough space to store data.
 */
char* doubleToExpForm(double number, char* buf)
{
    FloatingNumber num = { .number = number };

    char sign = EXTRACT_SIGN(num.bits);
    uint32_t exponent = EXTRACT_EXPONENT(num.bits);
    double mantissa = EXTRACT_MANTISSA(num.bits);

    /*
     * Formula to extract floating number is
     * sign * (1 + mantissa / 2^52) * 2^(exponent - 1023)
     */
    sprintf(buf, "%c%.20g*2^%d",
    sign, (1 + mantissa / ((uint64_t)1 << 52)), exponent - 1023);

    return buf;
}

#ifdef DEBUG
int launchTests()
{
    int returnCode = 0;
    return returnCode;
}

void printUsage(FILE* stream, const char* programName)
{
    const char* flags[] = {"--help", "--test"};
    const char* description[] = {"Show help info.", "Launch tests."};

    fprintf(stream, "Usage: %s [flags]\n", programName);
    fprintf(stream, "FLAGS:\n");
    for (int i = 0; i < (int)ARRAY_SIZE(flags); i++)
        fprintf(stream, "  %-15s %s\n", flags[i], description[i]);
}
#endif

int main(int argc, char** argv)
{
    #ifdef DEBUG
    if (argc > 2) {
        printUsage(stderr, argv[0]);
        return 1;
    } else if (argc == 2) {
        if (strcmp(argv[1], "--test") == 0)
            return launchTests();
        if (strcmp(argv[1], "--help") == 0) {
            printUsage(stdout, argv[0]);
            return 0;
        }
        printUsage(stderr, argv[0]);
        return 1;
    }
    #else
    /* Unused. */
    ((void)argc);
    ((void)argv);
    #endif

    double num = 0.0;
    if (!scanNumber(&num, "Please, enter a number:"))
        return 1;

    char buf[128] = {0};
    printf("You've entered %lf\n", num);
    printf("It can be represented as %s\n", doubleToExpForm(num, buf));

    return 0;
}
