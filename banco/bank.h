#ifndef _BANK_H_
#define _BANK_H_

#include <stdbool.h>
#include <limits.h>

typedef int element_t;
typedef struct bank bank_t;

#define SIZE 100
#define INVALID INT_MIN

bank_t *bank_create();
void bank_delete(bank_t *bank);

void bank_push(bank_t *bank, element_t element);
void bank_remove(bank_t *bank);

bool bank_empty(bank_t *bank);
bool bank_full(bank_t *bank);
void bank_print(bank_t *bank, char *format);
void node_print(bank_t *bank, char *format, int index);

#endif
