#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct stack {
    int top;
    element items[STACK_SIZE];
};

stack_t *create() {
    stack_t *s = malloc(sizeof(stack_t));
    assert(s != NULL);
    s->top = -1; //empty
    return s;
}

void destroy(stack_t *s) {
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
    if (s->top == -1)
        return 1;
    else
        return 0;
}

void push(stack_t *s, element x) {
    if (!is_full(s)) {
        s->top++;
        s->items[s->top] = x;
    }
}

element pop(stack_t *s) {
    element x;
    if (!is_empty(s)) {
        x = s->items[s->top];
        s->top--;
    }
    return x;
}

element top(stack_t *s) {
    element x;
    if (!is_empty(s)) {
        x = s->items[s->top];
    }
    return x;
}