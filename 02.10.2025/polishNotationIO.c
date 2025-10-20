#include "polishNotationIO.h"
#include <ctype.h>
#include <stdio.h>

#define ARRAY_CAPACITY (BUFSIZ)

struct Array {
    char buf[ARRAY_CAPACITY];
    int idx;
} output;

int getInput(const char* buf, int* idx)
{

    for (; isspace(buf[*idx]); (*idx)++)
        ;

    return buf[*idx] == '\0' ? EOF : buf[(*idx)++];
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
