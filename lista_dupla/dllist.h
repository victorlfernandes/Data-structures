#ifndef _DLLIST_H_
#define _DLLIST_H_

#include <stdbool.h>
#include <limits.h>

typedef int element_t;
typedef struct list list_t;

#define INVALID INT_MIN

list_t *list_create();
void list_delete(list_t *list);

void list_push(list_t *list, element_t element);
void list_append(list_t *list, element_t element);
void list_insert_after(list_t *list, element_t element, element_t after);
void list_insert_before(list_t *list, element_t element, element_t before);
void list_remove(list_t *list, element_t element);

int list_size(list_t *list);
bool list_search(list_t *list, element_t element);
void list_print(list_t *list, char *format);
void list_rprint(list_t *list, char *format);
void node_print(list_t *list, char *format, int index);
void list_rotate(list_t *list);

#endif
