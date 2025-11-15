#include "polishNotationIO.h"
#include "stack.h"
#include <ctype.h>
#include <stdio.h>

/*
 * Print error and assign *pExitCode = 1
 */
#define eprintf(pExitCode, ...)       \
    do {                              \
        fprintf(stderr, __VA_ARGS__); \
        *pExitCode = 1;               \
    } while (0)

/*
 * Get operation precedence in expression.
 * Return -1 if it is unknown operation.
 */
int getOpPrec(int op)
{
    switch (op) {
    case '-':
    case '+':
        return 1;
    case '/':
    case '*':
        return 2;
    default:
        return -1;
    }
}

/*
 * Pops all the operations from 'opStack' until '('.
 * Return false and print error message if '(' is not found.
 * pExitCode must be initialized.
 * *pExitCode = 1 on errors occured.
 */
bool processClosedBrace(Stack* opStack, int* pExitCode)
{
    while (!isStackEmpty(opStack) && stackPeek(opStack) != '(')
        putOutput(stackPop(opStack));

    if (isStackEmpty(opStack)) {
        eprintf(pExitCode, "Missing '('\n");
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
bool processOp(Stack* opStack, int* pExitCode, char* buf, int* idx)
{
    int op = getInput(buf, idx);
    int prec = getOpPrec(op);
    if (prec == -1) {
        if (op == EOF)
            return false;
        if (op == ')')
            return processClosedBrace(opStack, pExitCode) && processOp(opStack, pExitCode, buf, idx);
        eprintf(pExitCode, "Unexpected operation: %c\n", op);
        return false;
    }

    while (!isStackEmpty(opStack)) {
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
 * *pExitCode must be initialized.
 * *pExitCode = 1 on errors occured.
 */
bool processPrimaryExpr(Stack* opStack, int* pExitCode, char* buf, int* idx)
{
    int ch = getInput(buf, idx);
    if (isdigit(ch)) {
        putOutput(ch);

        ch = getInput(buf, idx);
        if (ch == ')') {
            if (!processClosedBrace(opStack, pExitCode))
                return false;
        } else {
            (*idx)--;
        }
        return true;
    } else if (ch == '(') {
        stackPush(opStack, ch);
        return processPrimaryExpr(opStack, pExitCode, buf, idx);
    }

    if (ch == EOF)
        eprintf(pExitCode, "Expected primary expression\n");
    else
        eprintf(pExitCode, "Unexpected primary expression: %c\n", ch);

    return false;
}

/*
 * Return false when either error encountered, EOF or '\n'
 * If error encountered *pExitCode = 1.
 * *pExitCode must be initialized.
 */
bool processExpr(Stack* opStack, int* pExitCode)
{
    char buf[BUFSIZ];
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return false;

    for (int i = 0; buf[i];) {
        if (!processPrimaryExpr(opStack, pExitCode, buf, &i))
            return false;

        if (!processOp(opStack, pExitCode, buf, &i))
            return false;
    }

    return true;
}

/*
 * Just pushes all the operations to the output.
 * It must be called after all the operations.
 * If error encountered *pExitCode = 1.
 * *pExitCode must be initialized.
 */
void clearOpStack(Stack* opStack, int* pExitCode)
{
    while (!isStackEmpty(opStack)) {
        int ch = stackPop(opStack);
        if (ch == '(') {
            eprintf(pExitCode, "Missing ')'\n");
            break;
        }

        putOutput(ch);
    }
}

int translateToPolishNotation()
{
    Stack* pOpStack = stackAlloc();
    int exitCode = 0;
    while (processExpr(pOpStack, &exitCode))
        ;

    if (exitCode == 0)
        clearOpStack(pOpStack, &exitCode);

    if (exitCode == 0)
        printOutput();

    stackFree(&pOpStack);
    return exitCode;
}

int main(void)
{
    printf("Enter expression\n"
           "(single digits, '+', '-', '*', '/', '(', ')' are allowed):\n");
    return translateToPolishNotation();
}