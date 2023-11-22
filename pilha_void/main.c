#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main() {

    stack_t *s = create();
    //printf("Push\n");
    for (int i = 0; i < 10; i++)
        push(s, (void *)&i);
    while (!is_empty(s)) {
        int *x = malloc(sizeof(int));
        pop(s, (void **)&x);
        printf("%d ", *x);
        //free(x);
    }
    printf("\n");
    //destroy(s);

    return 0;
}