#include "dllist.h"
#include <stdio.h>

int main() {

    list_t *list = list_create();

    for (int i = 0; i < 10; i++) 
        list_push(list, i);
    
    list_print(list, "%d ");

    list_insert_before(list, 90, 9);
    list_insert_before(list, 90, 5);
    list_print(list, "%d ");

    list_delete(list);

    return 0;
}