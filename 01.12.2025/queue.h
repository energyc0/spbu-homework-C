#pragma once

typedef struct Queue Queue;

/* 
 * Allocate empty queue on the heap.
 */
Queue* makeQueue();

/*
 * Free queue data and set 'q' pointer to NULL.
 */
void freeQueue(Queue** q);

/*
 * Put element into the queue.
 * Return true, if successful,
 * Return false, if failed.
 */
bool enqueue(Queue* q, int n);

/*
 * Pop element from the queue.
 * Return true and write data to 'n' pointer, if successful,
 * Return false and do not write data to 'n' pointer, if failed.
 */
bool dequeue(Queue* q, int* n);
