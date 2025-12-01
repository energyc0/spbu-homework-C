#include "queue.h"
#include <stdio.h>

int main()
{
    Queue* q = makeQueue();

    for (int i = 0; i < 10; i++)
        enqueue(q, i);

    for (int i = 0; i < 10; i++) {
        int n = 0;
        dequeue(q, &n);
        printf("num: %d\n", n);
    }

    freeQueue(&q);
    return 0;
}