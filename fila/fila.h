#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

#define QUEUE_SIZE 100

typedef int element_t;
typedef struct queue queue_t;

queue_t *create();

void delete(queue_t *q);

bool is_full(queue_t *q);

bool is_empty(queue_t *q);

void enqueue(queue_t *q, element_t x);

element_t dequeue(queue_t *q);

element_t front(queue_t *q);

element_t rear(queue_t *q);

#endif