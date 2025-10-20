#include "recursiveList.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * Ask user to enter a number,
 * return true if successfully,
 * return false if EOF found.
 */
static bool getNum(const char* prompt, int* num)
{
    puts(prompt);
    int res = 0;

    char buf[BUFSIZ];
    while (fgets(buf, sizeof(buf) - 1, stdin) != NULL
        && (res = sscanf(buf, "%d", num)) < 1) {
        if (res == -1)
            break;
        printf("Invalid number, try again:\n");
    }

    return res == 1;
}

/*
 * In our case, 'n' warriors are involved and every 'm'th is killed.
 * It is required to determine the number 'k' of the initial position of the warrior,
 * who will have to remain last.
 */
static int countingGame(int n, int m)
{
    int values[n];
    for (int i = 0; i < n; i++)
        values[i] = i + 1;
    RecursiveList list = makeRecursiveList(values, n);
    removeSequenceRecursiveList(&list, m, true);

    int result = -1;
    if (!getRecursiveList(&list, 0, &result)) {
        fprintf(stderr, "Something wrong occured to get element :(\n");
    }
    freeRecursiveList(&list);
    return result;
}

int main(void)
{
    printf("%d\n", -1 % 10);
    int n;
    if (!getNum("Enter n:", &n))
        return 1;

    int m;
    if (!getNum("Enter m:", &m))
        return 1;

    int k = countingGame(n, m);
    if (k > 0)
        printf("k = %d\n", k);

    return 0;
}