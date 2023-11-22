#include <stdio.h>
#include "fila.h"

int main() {

    queue_t *q = create();
    for (int i = 0; i < 10; i++)
        enqueue(q, (element_t)i);
    while (!is_empty(q)) {
        element_t x = dequeue(q);
        printf("%d\n", x);
    }
    delete(q);

    return 0;
}