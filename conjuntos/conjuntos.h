#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_MAX 100

int *criar_conjunto();

void liberar(int *conjunto);

void inserir(int termo, int *conjunto);

int tamanho(int *conjunto);

void remover(int termo, int *conjunto);

int *uniao(int *conjunto1, int *conjunto2);

int *intersecao(int *conjunto1, int *conjunto2);

int *diferenca(int *conjunto1, int *conjunto2);

int max(int *conjunto);

int min(int *conjunto);

bool membro(int termo, int *conjunto);

bool igual(int *conjunto1, int *conjunto2);

void copia(int *conjunto1, int *conjunto2);

void imprimir(int *conjunto);
