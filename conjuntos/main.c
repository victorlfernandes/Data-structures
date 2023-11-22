#include "conjuntos.h"
#include <time.h>

int main() {
    srand(time(NULL));

    int TAM_CONJUNTO = rand() % TAM_MAX;

    int *conjunto1 = criar_conjunto();
    for (int i = 0; i < TAM_CONJUNTO; i++) {
        inserir(rand() % (TAM_MAX - 1), conjunto1);
    }
    printf("Conjunto 1: ");
    imprimir(conjunto1);
    printf("Tamanho: %d\n", tamanho(conjunto1));
    int rm[TAM_CONJUNTO];
    bool removi_algo = false;
    for (int i = 0; i < TAM_CONJUNTO; i++) {
        rm[i] = rand() % (TAM_MAX - 1); 
        if (membro(rm[i], conjunto1)) {
            remover(rm[i], conjunto1);
            removi_algo = true;
        }
    }
    if (removi_algo) {
        printf("Conjunto 1 após remoções: ");
        imprimir(conjunto1);
        printf("Tamanho: %d\n", tamanho(conjunto1));
    }
    printf("\n");

    int *conjunto2 = criar_conjunto();
    for (int i = 0; i < TAM_CONJUNTO; i++) {
        inserir(rand() % (TAM_MAX - 1), conjunto2);
    }
    printf("Conjunto 2: ");
    imprimir(conjunto2);
    printf("Tamanho: %d\n", tamanho(conjunto2));
    removi_algo = false;
    for (int i = 0; i < TAM_CONJUNTO; i++) {
        rm[i] = rand() % (TAM_MAX - 1); 
        if (membro(rm[i], conjunto2)) {
            remover(rm[i], conjunto2);
            removi_algo = true;
        }
    }
    if (removi_algo) {
        printf("Conjunto 2 após remoções: ");
        imprimir(conjunto2);
        printf("Tamanho: %d\n", tamanho(conjunto2));
    }
    printf("\n");

    int *un = uniao(conjunto1, conjunto2);
    printf("Uniao: ");
    imprimir(un);

    int *it = intersecao(conjunto1, conjunto2);
    printf("Intersecao: ");
    imprimir(it);

    int *dif = diferenca(conjunto2, conjunto1);
    printf("Diferenca entre 2 e 1: ");
    imprimir(dif);

    printf("\n");
    printf("Maximo 1: ");
    printf("%d\n", max(conjunto1));    

    printf("Minimo 2: ");
    printf("%d\n", min(conjunto2));   

    printf("\n");
    int var = rand() % (TAM_MAX - 1);
    printf("%d pertence ao conjunto 1? %s\n", var, membro(var, conjunto1) ? "sim" : "nao");   
    printf("%d pertence ao conjunto 2? %s\n", var, membro(var, conjunto2) ? "sim" : "nao");   

    printf("\n");
    printf("Os conjuntos são iguais? %s\n", igual(conjunto1, conjunto2) ? "sim" : "nao");
    printf("Copiando o conjunto 2 pro conjunto 1\n");
    copia(conjunto2, conjunto1);
    printf("Os conjuntos são iguais? %s\n", igual(conjunto1, conjunto2) ? "sim" : "nao");

    liberar(conjunto1);
    liberar(conjunto2);
    liberar(un);
    liberar(it);
    liberar(dif);

    return 0;
}