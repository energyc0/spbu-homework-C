#include "polishNotationIO.h"
#include <ctype.h>
#include <stdio.h>

#define ARRAY_CAPACITY (BUFSIZ)

typedef struct Array {
    char buf[ARRAY_CAPACITY];
    int idx;
} Array;

static Array input = {.buf = {0}, .idx = 0};
static Array output = {.buf = {0}, .idx = 0};

void skipSpaces(const char* buf, int* idx)
{
    for (; isspace(buf[*idx]); (*idx)++)
        ;

}

int getInput(const char* buf, int* idx)
{

    for (; isspace(buf[*idx]); (*idx)++)
        ;

    return buf[*idx] == '\0' ? EOF : buf[(*idx)++];
    /*
    if (input.buf[input.idx] == '\0' && input.idx == 0)
        if (fgets(input.buf, sizeof(input.buf), stdin) == NULL)
            return EOF;


    for (; isspace(input.buf[input.idx]); input.idx++)
        ;

    if (input.buf[input.idx] == '\0')
        return EOF;

    return input.buf[input.idx++];
    */
}

void putOutput(int ch)
{
    if (output.idx < (int)(sizeof(output.buf) - 2)) {
        output.buf[output.idx++] = ch;
        output.buf[output.idx++] = ' ';
    }
}

void printOutput()
{
    output.buf[output.idx] = '\0';
    printf("%s\n", output.buf);
}

void putback()
{
    if (input.idx > 0)
        input.idx--;
}
