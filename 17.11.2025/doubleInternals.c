#include <stdbool.h>
#include <stdio.h>

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
    double number = 0.0;
    if (!scanNumber(&number, "Please, enter a number:"))
        return 1;

    printf("You entered %lf\n", number);

    return 0;
}
