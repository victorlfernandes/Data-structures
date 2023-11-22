#include "bank.h"
#include <stdio.h>

int main() {

    bank_t *bank = bank_create();

    for (int i = 0; i < 10; i++) 
        bank_push(bank, i);
    
    bank_print(bank, "%d ");
    bank_remove(bank);
    bank_print(bank, "%d ");

    bank_delete(bank);

    return 0;
}