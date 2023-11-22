#include "skipl.h"
#include "str.h"
#include <stdlib.h>
#include <time.h>

int main() {

    srand(time(NULL));
    skipl_t *sl = create_sl();
    for (int i = 0; i < 20; i++)
        insert_sl(sl, i * 3);

    print_sl(sl);

    printf("\n");

    delete_sl(sl);

    return 0;
}