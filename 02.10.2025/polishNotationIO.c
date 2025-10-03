#include "polishNotationIO.h"
#include <ctype.h>
#include <stdio.h>

static int _putback = '\0';
static char _outputBuf[BUFSIZ];
static int _outputBufSize = 0;

int getInput()
{
    int ch;
    if (_putback) {
        ch = _putback;
        _putback = '\0';
        return ch;
    }
    for (ch = getchar(); isblank(ch); ch = getchar())
        ;
    return ch;
}

void putOutput(int ch)
{
    if (_outputBufSize < (int)(sizeof(_outputBuf) - 2)) {
        _outputBuf[_outputBufSize++] = ch;
        _outputBuf[_outputBufSize++] = ' ';
    }
}

void printOutput()
{
    _outputBuf[_outputBufSize] = '\0';
    printf("%s\n", _outputBuf);
}

void putback(int ch)
{
    _putback = ch;
}

bool isEOF(int ch)
{
    return ch == EOF || ch == '\n';
}
