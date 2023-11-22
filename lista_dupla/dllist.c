#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node node_t;

struct node {
    element_t val;
    node_t   *nxt;
    node_t   *prev;
};

struct list {
    node_t *start;
    node_t *end;
    int     size;
};

list_t *list_create() {
    list_t *list = malloc(sizeof(list_t));
    assert(list != NULL);
    list->start = NULL;
    list->end   = NULL;
    list->size  = 0;
    return list;
}

node_t *node_create() {
    node_t *node = malloc(sizeof(node_t));
    node->val    = (element_t)0;
    node->nxt    = NULL;
    node->prev   = NULL;
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

node_t *node_search(list_t *list, element_t element) {
    assert(list != NULL);
    node_t *node = list->start;
    while (node != NULL) {
        if (node->val == element) return node;
        node = node->nxt;
    }
    return NULL;
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

void list_insert_sorted(list_t *list, element_t element) {

    assert(list != NULL);
    
    if (list->size == 0) {
        list_push(list, element);
        return;
    }

    node_t *prev_node = list->start;
    while (prev_node != NULL && prev_node->val > element)
        prev_node = prev_node->next;
    
    if (prev_node == list->start) {
        list_push(list, element);
        return;
    }
    
    if (prev_node == NULL) {
        list_append(list, element);
        return;
    }
    
    node_t *new_node = node_create();
    new_node->val = element;

    new_node->prev = prev_node;
    new_node->next = prev_node->next;

    prev_node->next->prev = new_node;
    prev_node->next = new_node;

    list->size++;
}

void list_insert_after(list_t *list, element_t element, element_t after) {
    assert(list != NULL);
    node_t *prev_node = node_search(list, after);
    assert(prev_node != NULL);

    if (prev_node->nxt == NULL) {
        list_append(list, element);
        return;
    }
   
    node_t *node = node_create();
    node->val = element;

    node->prev = prev_node;
    node->nxt = prev_node->nxt;

    prev_node->nxt->prev = node;
    prev_node->nxt = node;

    list->size++;
}

void list_insert_before(list_t *list, element_t element, element_t before) {
    assert(list != NULL);
    node_t *nxt_node = node_search(list, before);
    assert(nxt_node != NULL);

    if (nxt_node->prev == NULL) {
        list_push(list, element);
        return;
    }

    node_t *node = node_create();
    node->val = element;

    node->nxt = nxt_node;
    node->prev = nxt_node->prev;

    nxt_node->prev->nxt = node;
    nxt_node->prev = node;

    list->size++;
}

void list_push(list_t *list, element_t element) {
    assert(list != NULL);
    node_t *node = node_create();
    node->val = element;
    if (list->size == 0) {
        list->start = node;
        list->end   = node;
        list->start->prev = NULL;
        list->start->nxt  = NULL;
    }
    else {
        node->prev = NULL;
        node->nxt  = list->start;
        list->start->prev = node;
        list->start = node;
    }
    list->size++;
}

void list_append(list_t *list, element_t element) {
    assert(list != NULL);
    node_t *node = node_create();
    node->val = element;
    if (list->size == 0) {
        list->start = node;
        list->end   = node;
        list->start->prev = NULL;
        list->start->nxt  = NULL;
    }
    else {
        node->nxt = NULL;
        node->prev = list->end;
        list->end->nxt = node;
        list->end = node;
    }   
    list->size++;
}

void list_remove(list_t *list, element_t element) {
    assert(list != NULL);
    if (!list_search(list, element)) return;
    node_t *node = list->start;
    while (node != NULL) {
        if (node->val == element) {
            if (node == list->start) {
                list->start = node->nxt;
                list->start->prev = NULL;
            }
            else if (node == list->end) {
                list->end = node->prev;
                list->end->nxt = NULL;
            }
            else {
                node->prev->nxt = node->nxt;
                node->nxt->prev = node->prev;
            }
            node_delete(node);
            list->size--;
            return;
        }
        else 
            node = node->nxt;
    }
}

int list_size(list_t *list) {
    assert(list != NULL);
    return list->size;
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

void node_print(list_t *list, char *format, int index) {
    assert(list != NULL);
    node_t *node = list->start;
    int index_counter = 0;
    bool finished = false;
    while (node != NULL && !finished) {
        if (index_counter == index) {
            printf(format, node->val);
            finished = true;
        }            
        node = node->nxt;
        index_counter++;
    }
}

void list_rprint(list_t *list, char *format) {
    assert(list != NULL && format != NULL);
    node_t *node = list->end;
    while (node != NULL) {
        printf(format, node->val);
        node = node->prev;
    }
    printf("\n");
}

void list_rotate(list_t *list) {
    assert(list != NULL);
    node_t *node = node_create();
    node->val = list->end->val;
    node->prev = NULL;
    node->nxt = list->start;
    list->start->prev = node;
    list->start = node;
    list->end = list->end->prev;
    node_delete(list->end->nxt);
    list->end->nxt = NULL;
}

void swap(list_t *list, node_t *n1, node_t *n2) {

    if (n1 == NULL || n2 == NULL || n1 == n2)
        return;

    if (n1->prev != NULL) {
        if (n1->prev->next != n2)
            n1->prev->next = n2;
        else
            n1->prev->next = n2->next;
    }

    if (n1->next != NULL) {
        if (n1->next->prev != n2)
            n1->next->prev = n2;
        else 
            n1->next->prev = n2->prev;
    }
            
    if (n1 == list->start)
        list->start = n2;
    else if (n1 == list->end) 
        list->end = n2;

    if (n2->prev != NULL) {
        if (n2->prev->next != n1)
            n2->prev->next = n1;
        else
            n2->prev->next = n1->next;
    }

    if (n2->next != NULL) {
        if (n2->next->prev != n1)
            n2->next->prev = n1;
        else
            n2->next->prev = n1->prev;
    }

    if (n2 == list->start)
        list->start = n1;
    else if (n2 == list->end)
        list->end = n1;

    node_t *aux_node = n1->next;
    n1->next = n2->next;
    n2->next = aux_node;

    aux_node = n1->prev;
    n1->prev = n2->prev;
    n2->prev = aux_node;
}
