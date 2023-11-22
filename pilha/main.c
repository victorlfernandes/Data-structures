#include <stdio.h>
#include "pilha.h"

int main() {

    stack_t *s = create();
    for (int i = 0; i < 10; i++)
        push(s, (element)i);
    while (!is_empty(s)) {
        element x = pop(s);
        printf("%d ", x);
    }
    printf("\n");
    destroy(s);

    return 0;
}