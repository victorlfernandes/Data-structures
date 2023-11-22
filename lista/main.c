#include "llist.h"
#include <stdio.h>

int main() {

    list_t *list = list_create();

    for (int i = 0; i < 10; i++) 
        list_insert(list, i);
    
    list_print(list, "%d ");

    list_remove(list, 0);
    list_print(list, "%d ");

    list_remove(list, 9);
    list_print(list, "%d ");

    list_remove(list, 5);
    list_print(list, "%d ");

    list_delete(list);

    return 0;
}