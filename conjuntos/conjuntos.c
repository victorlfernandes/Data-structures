#include "conjuntos.h"

int *criar_conjunto() {
    int *conjunto = calloc(TAM_MAX, sizeof(int));
    return conjunto;
}

void liberar(int *conjunto) {
    free(conjunto);
}

void inserir(int termo, int *conjunto) {
    if (termo < TAM_MAX) {
        if (!conjunto[termo])
            conjunto[termo] = 1;
    }
}

int tamanho(int *conjunto) {
    int contador = 0;
    for (int i = 0; i < TAM_MAX; i++) {
        if (conjunto[i])
            contador++;
    }
    return contador;
}

void remover(int termo, int *conjunto) {
    if (termo < TAM_MAX) {
        if (conjunto[termo])
            conjunto[termo] = 0;
    }
}

int *uniao(int *conjunto1, int *conjunto2) {
    int *conjunto3 = criar_conjunto();
    for (int i = 0; i < TAM_MAX; i++){
        if (conjunto1[i] || conjunto2[i])
            inserir(i, conjunto3);
    }
    return conjunto3;
}

int *diferenca(int *conjunto1, int *conjunto2) {
    int *conjunto3 = criar_conjunto();
    for (int i = 0; i < TAM_MAX; i++){
        if (conjunto1[i] && !conjunto2[i])
            inserir(i, conjunto3);
    }
    return conjunto3;
}

int *intersecao(int *conjunto1, int *conjunto2) {
    int *conjunto3 = criar_conjunto();
    for (int i = 0; i < TAM_MAX; i++){
        if (conjunto1[i] && conjunto2[i])
            inserir(i, conjunto3);
    }
    return conjunto3;
}

int max(int *conjunto) {
    int aux;
    for (int i = 0; i < TAM_MAX; i++) {
        if (conjunto[i])
            aux = i;
    }
    return aux;
}

int min(int *conjunto) {
    int aux;
    for (int i = TAM_MAX - 1; i >= 0; i--) {
        if (conjunto[i])
            aux = i;
    }
    return aux;
}

bool membro(int termo, int *conjunto) {
    if (conjunto[termo])
        return true;
    else 
        return false;
}

bool igual(int *conjunto1, int *conjunto2) {
    for (int i = 0; i < TAM_MAX; i++) {
        if (conjunto1[i] != conjunto2[i])
            return false;
    }
    return true;
}

void copia(int *conjunto1, int *conjunto2) {
    for (int i = 0; i < TAM_MAX; i++) {
        if (conjunto1[i] && !conjunto2[i])
            conjunto2[i] = 1;
        if (!conjunto1[i] && conjunto2[i])
            conjunto2[i] = 0;
    }
}

void imprimir(int *conjunto) {
    for (int i = 0; i < TAM_MAX; i++) {
        if (conjunto[i])
            printf("%d ", i);
    }
    printf("\n");
}
