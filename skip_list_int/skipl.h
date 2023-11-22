#ifndef _SKIPL_H_
#define _SKIPL_H_

#include "str.h"
#include <stdbool.h>

typedef int element_t;
typedef struct skip_list skipl_t;

#define MAX_LEVEL 20

skipl_t *create_sl();
void delete_sl(skipl_t *sl);

void insert_sl(skipl_t *sl, element_t element);
void remove_sl(skipl_t *sl, element_t key);
bool search_sl(skipl_t *sl, element_t key);

void print_sl(skipl_t *sl);
void print_error(int code, char ch);

#endif
