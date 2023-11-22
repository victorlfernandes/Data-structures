#ifndef _LLIST_H_
#define _LLIST_H_

#include <stdbool.h>

typedef int element_t;
typedef struct list list_t;

#define INVALID -19203

list_t *list_create();
void list_delete(list_t *list);

void list_insert(list_t *list, element_t element);
void list_remove(list_t *list, element_t element);

int list_size(list_t *list);
bool list_search(list_t *list, element_t element);
void list_print(list_t *list, char *format);

#endif
