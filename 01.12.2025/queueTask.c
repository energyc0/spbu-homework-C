#include "queue.h"
#include <stdio.h>

/*
 * Return 1 on fail,
 * Return 0 on success.
 */
int launchTests()
{
    Queue* q = makeQueue();
    int vals[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for (int i = 0; i < 10; i++)
        if (!enqueue(q, i))
            return 1;

    for (int i = 0; i < 10; i++) {
        int n = 0;
        if (!dequeue(q, &n))
            return 1;
        if (vals[i] != n)
            return 1;
    }

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    int n = 0;
    if (!dequeue(q, &n) || n != 10)
        return 1;

    enqueue(q, 11);
    enqueue(q, 12);
    enqueue(q, 13);
    if (!dequeue(q, &n) || n != 20)
        return 1;
    if (!dequeue(q, &n) || n != 30)
        return 1;
    if (!dequeue(q, &n) || n != 11)
        return 1;
    if (!dequeue(q, &n) || n != 12)
        return 1;
    if (!dequeue(q, &n) || n != 13)
        return 1;
    if (dequeue(q, &n))
        return 1;

    freeQueue(&q);
    if (q != NULL)
        return 1;

    return 0;
}

int main()
{
    int returnCode = launchTests();
    printf("Tests %s\n", returnCode == 0 ? "passed" : "failed");
    return returnCode;
}