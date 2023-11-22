#include "llist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node node_t;

struct node {
    element_t val;
    node_t   *nxt;
};

struct list {
    node_t *start;
    node_t *end;
    int     size;
};

list_t *list_create() {
    list_t *list = malloc(sizeof(list_t));
    assert(list != NULL);
    list->start  = NULL;
    list->end    = NULL;
    list->size   = 0;
    return list;
}

node_t *node_create() {
    node_t *node = malloc(sizeof(node_t));
    node->val    = (element_t)0;
    node->nxt    = NULL;
    return node;
}

void node_delete(node_t *node) {
    assert(node != NULL);
    free(node);
}

void list_delete(list_t *list) {
    assert(list != NULL);
    node_t *node = list->start;
    while (node != NULL) {
        list->start = node->nxt;
        node_delete(node);
        node = list->start;
    }
    free(list);
}

void list_insert(list_t *list, element_t element) {
    assert(list != NULL);
    node_t *node = node_create();
    node->val = element;
    if (list->size == 0) list->start = node;
    else list->end->nxt = node;
    list->end = node;
    list->size++;
}

void list_remove(list_t *list, element_t element) {
    assert(list != NULL);
    if (!list_search(list, element)) return;
    node_t *node = list->start;
    node_t *prev = NULL;
    while (node != NULL) {
        if (node->val == element) {
            if (node == list->start) 
                list->start = node->nxt;
            else if (node == list->end) {
                list->end = prev;
                list->end->nxt = NULL;
            }
            else 
                prev->nxt = node->nxt;
            node_delete(node);
            list->size--;
            return;
        }
        else {
            prev = node;
            node = node->nxt;
        }
    }
}

int list_size(list_t *list) {
    assert(list != NULL);
    return list->size;
}

bool list_search(list_t *list, element_t element) {
    assert(list != NULL);
    node_t *node = list->start;
    while (node != NULL) {
        if (node->val == element) return true;
        node = node->nxt;
    }
    return false;
}

void list_print(list_t *list, char *format) {
    assert(list != NULL && format != NULL);
    node_t *node = list->start;
    while (node != NULL) {
        printf(format, node->val);
        node = node->nxt;
    }
    printf("\n");
}
