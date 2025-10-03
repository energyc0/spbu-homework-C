#include "stack.h"
#include <stdio.h>
#include <ctype.h>

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

static int _putback = '\0';
static char _outputBuf[BUFSIZ];
static int _outputBufSize = 0;
/*
 * Skip white spaces and tabs and return character from the input.
 */
int getInput()
{
    int ch;
    if (_putback) {
        ch = _putback;
        _putback = '\0';
        return ch;
    }
    for (ch = getchar(); isblank(ch); ch = getchar());
    return ch;
}

bool putOutput(int ch)
{
    if (_outputBufSize >= (int)(sizeof(_outputBuf) - 2))
        return false;

    _outputBuf[_outputBufSize++] = ch;
    _outputBuf[_outputBufSize++] = ' ';

    return true;
}

void printOutput()
{
    _outputBuf[_outputBufSize] = '\0';
    printf("%s\n", _outputBuf);
}

/*
 * Puts character back into the stream.
 */
void putback(int ch) 
{
    _putback = ch;
}

bool isEOF(int ch)
{
    return ch == EOF || ch == '\n';
}

/*
 * Get operation precedence in expression.
 * Return -1 if it is unknown operation.
 */
int getOpPrec(int op)
{
    switch (op) {
        case '-': case '+':
            return 1;
        case '/': case '*':
            return 2;
        default:
            return -1;
    }
}

/*
 * Pops all the operations from 'opStack' until '('.
 * Return false and print error message if '(' is not found.
 */
bool processClosedBrace(Stack* opStack)
{
    while (!stackEmpty(opStack) && stackPeek(opStack) != '(')
        putOutput(stackPop(opStack));

    if (stackEmpty(opStack)) {
        eprintf ("Missing '('\n");
        return false;
    }

    stackPop(opStack);
    return true;
}

/*
 * Gets arithmetic operation.
 * Return true if parsed successfully.
 * Return false if either EOF, '\n' or error found.
 * Prints error messages.
 * Pops and prints all the operation with lower precedence.
*/
bool processOp(Stack* opStack, int* exit_code)
{
    int op = getInput();
    int prec = getOpPrec(op);
    if (prec == -1) {
        if (isEOF(op))
            return false;
        if (op == ')')
            return processClosedBrace(opStack) && processOp(opStack, exit_code);
        eprintf("Unexpected operation: %c\n", op);
        return false;
    }

    while (!stackEmpty(opStack)) {
        int temp = stackPeek(opStack);
        if (getOpPrec(temp) >= prec)
            putOutput(stackPop(opStack));
        else
            break;
    }

    stackPush(opStack, op);
    return true;
}

/*
 * Return false when either error encountered, EOF or '\n'
 */
bool processPrimaryExpr(Stack* opStack, int* exit_code)
{
    int ch = getInput();
    if (isdigit(ch)) {
        putOutput(ch);
        ch = getInput();
        if (ch == ')') {
            if (!processClosedBrace(opStack))
                return false;
        } else {
            putback(ch);
        }
        return true;
    } else if (ch == '(') {
        stackPush(opStack, ch);
        return processPrimaryExpr(opStack, exit_code);
    } else if (isEOF(ch)) {
        eprintf("Expected primary expression\n");
        return false;
    }

    eprintf("Unexpected primary expression: %c\n", ch);
    return false;
}

/*
 * Return false when either error encountered, EOF or '\n'
 */
bool processExpr(Stack* opStack, int* exit_code)
{
    if (!processPrimaryExpr(opStack, exit_code))
        return false;

    if (!processOp(opStack, exit_code))
        return false;

    return true;
}

int clearOpStack(Stack* opStack)
{
    while (!stackEmpty(opStack)) {
        int ch = stackPop(opStack);
        if (ch == '(') {
            eprintf("Missing ')'\n");
            return 1;
        }

        putOutput(ch);
    }
    return 0;
}

int translateToPolishNotation()
{
    Stack opStack;
    stackInit(&opStack);
    int exit_code = 0;
    while (processExpr(&opStack, &exit_code));

    if (exit_code == 0)
        exit_code = clearOpStack(&opStack);

    if (exit_code == 0)
        printOutput();

    stackFree(&opStack);
    return exit_code;
}

int main(void)
{
    printf("Enter expression\n"
        "(single digits, '+', '-', '*', '/', '(', ')' are allowed):\n");
    return translateToPolishNotation();
}