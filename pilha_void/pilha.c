#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct stack {
    int top;
    void **items;
};

stack_t *create() {

    stack_t *s = malloc(sizeof(stack_t));
    assert(s != NULL);

    s->items = malloc(STACK_SIZE * sizeof(void **));
    assert(s->items != NULL);
    for (int i = 0; i < STACK_SIZE; i++) {
        s->items[i] = malloc(sizeof(void *));
        assert(s->items[i] != NULL);
    }
  
    s->top = -1; //empty
  
    return s;
}

void destroy(stack_t *s) {
    while (s->top >= 0) {
        if (s->items[s->top] != NULL) {
            free(s->items[s->top]);
        }
        s->top--;
    }
    if (s->items != NULL) 
        free(s->items);
    if (s != NULL)
        free(s);
}

int is_full(stack_t *s) {
    assert(s != NULL);
    if (s->top == STACK_SIZE - 1)
        return 1;
    else    
        return 0;
}

int is_empty(stack_t *s) {
    assert(s != NULL);
    if (s->top < 0)
        return 1;
    else
        return 0;
}

void push(stack_t *s, void *x) {
    //printf("%d\n", *x)
    if (!is_full(s)) {
        s->top++;
        assert(s->items[s->top] != NULL);
        s->items[s->top] = x;
    }
}

void *pop(stack_t *s, void **x) {
    if (!is_empty(s)) {
        *x = s->items[s->top];
        //memcpy(x, s->items[s->top], s->element_size);
        //free(s->items[s->top]);
        s->top--;
    }
}

/*
void *top(stack_t *s) {
    void *x;
    if (!is_empty(s)) {
        memcpy(x, s->items[s->top], s->element_size);
    }
    return x;
}
*/
