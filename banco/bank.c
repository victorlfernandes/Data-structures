#include "bank.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node node_t;

struct node {
    element_t val;
    int nxt;
};

struct bank {
    node_t array[SIZE];
    int start;
    int end;
    int empty_p;
};

bank_t *bank_create() {
    
    bank_t *bank = malloc(sizeof(bank_t));
    assert(bank != NULL);
    
    // creating the logic relation between all elements
    for (int i = 0; i < SIZE - 1; i++) 
        bank->array[i].nxt = i + 1;
    
    // setting up the indexes
    bank->start   = -1;
    bank->end     = -1;
    bank->empty_p =  0;

    return bank;
}

void bank_delete(bank_t *bank) {
    assert(bank != NULL);
    free(bank);
}

int find_empty(bank_t *bank) {
    
    if (bank_full(bank))
        // there arent empty spaces to fill
        return INVALID;

    // getting the first empty space
    int empty_pos = bank->empty_p;
    
    // changing the first empty space to the next one
    bank->empty_p = bank->array[empty_pos].nxt;
    
    // the empty space obtained is gonna be filled with the last element of the
    // bank, so the next position of it must be -1, the terminating index
    bank->array[empty_pos].nxt = -1;

    return empty_pos;
}

void bank_push(bank_t *bank, element_t element) {
    
    // getting the position that the element must be inserted
    int insertion_pos = find_empty(bank);
    if (insertion_pos == INVALID)
        return;

    // assigning the element
    bank->array[insertion_pos].val = element;

    // checking if this is the first element of the bank
    if (bank->start == -1)
        bank->start = insertion_pos;
    else
        bank->array[bank->end].nxt = insertion_pos; 
    
    // updating the last element as this one
    bank->end = insertion_pos;
}

void node_delete(bank_t *bank, int pos) {

    // checking the validity of the position
    assert(pos >= 0 && pos < SIZE);

    // adding the position passed to the beggining of the empty list 
    bank->array[pos].nxt = bank->empty_p;
    bank->empty_p = pos;
}

void bank_remove(bank_t *bank) {

    if (bank_empty(bank))
        // there isnt an element to remove
        return;

    int aux = bank->start;

    // turning second bank element into first
    bank->start = bank->array[aux].nxt;

    // deleting the first element of the bank
    node_delete(bank, aux);
}

bool bank_empty(bank_t *bank) {
    assert(bank != NULL);
    return (bank->start == -1) ? true : false;
}

bool bank_full(bank_t *bank) {
    assert(bank != NULL);
    return (bank->empty_p == -1) ? true : false;
}

void bank_print(bank_t *bank, char *format) {
    
    assert(bank != NULL && format != NULL);
    
    int i = bank->start;
    while (i != -1) {
        printf(format, bank->array[i].val);
        i = bank->array[i].nxt;
    }
    
    printf("\n");
}

void node_print(bank_t *bank, char *format, int index) {
    assert(bank != NULL);
    printf(format, bank->array[index].val);
}
