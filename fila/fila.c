#include "fila.h"

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

struct queue {
    int front;
    int rear;
    int size;
    element_t array[QUEUE_SIZE];
};

queue_t *create() {
    queue_t *q = malloc(sizeof(queue_t));
    assert(q != NULL);
    q->front = 0; 
    q->rear  = 0;
    q->size  = 0;
    return q;
}

void delete(queue_t *q) {
    if (q != NULL)
        free(q);
}

bool is_full(queue_t *q) {
    assert(q != NULL);
    return (q->size == QUEUE_SIZE) ? true : false;
}

bool is_empty(queue_t *q) {
    assert(q != NULL);
    return (q->size == 0) ? true : false;
}

void enqueue(queue_t *q, element_t x) {
    if (!is_full(q)) {
        q->array[q->rear] = x;
        q->rear = (q->rear + 1) % QUEUE_SIZE;
        q->size++;
    }
}

element_t dequeue(queue_t *q) {
    if (is_empty(q)) return (element_t)INT_MIN;
    element_t x = q->array[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->size--;
    return x;
}

element_t front(queue_t *q) {
    if (is_empty(q)) return (element_t)INT_MIN;
    return q->array[q->front];
}

element_t rear(queue_t *q) {
    if (is_empty(q)) return (element_t)INT_MIN;
    return q->array[q->rear];
}