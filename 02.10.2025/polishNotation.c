#include "stack.h"
#include <stdio.h>
#include <ctype.h>

int getInput(FILE* fp)
{
    int ch;
    for (ch = getc(fp); isblank(ch); ch = getc(fp));
    return ch;
}

bool isBinOp(int ch) 
{
    return ch == '+' || ch == '-' || ch == '/' || ch == '*';
}

bool isToken(int ch)
{
    return isdigit(ch) || ch == '(' || ch == ')' || isBinOp(ch);
}

int getOpPrec(int op)
{
    if (op == '-' || op == '+')
        return 1;
    else if (op == '/' || op == '*')
        return 2;
    else 
        return -1;
}

bool processOp(Stack* opStack, int op)
{
    int prec = getOpPrec(op);
    if (prec == -1)
        return false;

    while (!stackEmpty(opStack)) {
        int temp = stackPeek(opStack);
        if (getOpPrec(temp) >= prec)
            printf("%c ", stackPop(opStack));
        else
            break;
    }

    stackPush(opStack, op);
    return true;
}

bool processClosedBrace(Stack* opStack)
{
    while (!stackEmpty(opStack) && stackPeek(opStack) != '(')
        printf("%c ", stackPop(opStack));

    if (stackEmpty(opStack))
        return false;

    stackPop(opStack);
    return true;
}

int translateToPolishNotation(FILE* fp)
{
#define errorQuit(...) do { \
    fprintf(stderr, __VA_ARGS__); \
    return 1; \
} while(0) 

    Stack opStack;
    stackInit(&opStack);

    int ch;
    for (ch = getInput(fp); isToken(ch); ch = getInput(fp)) {
        if (isdigit(ch)) {
            printf("%c ", ch);
        } else if (ch == '(') {
            stackPush(&opStack, ch);
        } else if (ch == ')') {
            if (!processClosedBrace(&opStack))
                errorQuit("Missing '('\n");
        } else if (isBinOp(ch)) {
            processOp(&opStack, ch);
        } else {
            break;
        }
    }

    if (ch != EOF && ch != '\n')
        errorQuit("Undefined character: '%c'\n", ch);

    while (!stackEmpty(&opStack)) {
        ch = stackPop(&opStack);
        if (ch == '(')
            errorQuit("Missing ')'\n");

        printf("%c ", ch);
    }
    putchar('\n');

    return 0;

    #undef errorQuit
}

int main(void)
{
    printf("Enter expression:\n");
    return translateToPolishNotation(stdin);
}