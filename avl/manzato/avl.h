typedef int elem;

typedef struct no no_t;

typedef struct arvore {
	no_t *raiz;
} arvore_t;

arvore_t *criar();
int esta_vazia(arvore_t *a);
void finalizar(no_t *raiz);
void imprimir(no_t *raiz);
int altura(no_t *raiz);
void pre_ordem(no_t *raiz);
void em_ordem(no_t *raiz);
void pos_ordem(no_t *raiz);
no_t *busca(no_t *raiz, elem x);
void inserir(arvore_t *a, elem x);
void remover(arvore_t *a, elem x);
