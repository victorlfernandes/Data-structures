#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"

struct no {
	no_t *esq, *dir;
	int fb;
	elem info;
};

arvore_t *criar() {
	arvore_t *a = (arvore_t *)malloc(sizeof(arvore_t));
	a->raiz = NULL;
	return a;
}

int esta_vazia(arvore_t *a) {
	assert(a != NULL);
	if(a->raiz == NULL)
		return 1;
	return 0;
}

void finalizar(no_t *raiz) {
	if(raiz != NULL) {
		finalizar(raiz->esq);
		finalizar(raiz->dir);
		free(raiz);
	}
}

void imprimir(no_t *raiz) {
	if(raiz != NULL) {
		printf("%d(", raiz->info);
		imprimir(raiz->esq);
		printf(",");
		imprimir(raiz->dir);
		printf(")");
	} else {
		printf("null");
	}
}

int altura(no_t *raiz) {
	if(raiz == NULL) 
		return 0;
	
	int alt_esq = 1 + altura(raiz->esq);
	int alt_dir = 1 + altura(raiz->dir);
	
	if(alt_esq > alt_dir)
		return alt_esq;
	else
		return alt_dir;
}

void pre_ordem(no_t *raiz) {
	if(raiz != NULL) {
		printf("%d ", raiz->info);
		pre_ordem(raiz->esq);
		pre_ordem(raiz->dir);
	}
}

void em_ordem(no_t *raiz) {
	if(raiz != NULL) {		
		em_ordem(raiz->esq);
		printf("%d ", raiz->info);
		em_ordem(raiz->dir);
	}
}

void pos_ordem(no_t *raiz) {
	if(raiz != NULL) {		
		pos_ordem(raiz->esq);		
		pos_ordem(raiz->dir);
		printf("%d ", raiz->info);
	}
}

no_t *busca(no_t *raiz, elem x) {
	if(raiz == NULL) {
		return NULL;
	} else if(raiz->info == x) {
		return raiz;
	} else if(x < raiz->info) {
		return busca(raiz->esq, x);
	} else {
		return busca(raiz->dir, x);
	}
}

no_t *rotacao_EE(no_t *desb) {
	no_t *aux = desb->dir;
	desb->dir = aux->esq;
	aux->esq = desb;
	return aux;
}

no_t *rotacao_DD(no_t *desb) {
	no_t *aux = desb->esq;
	desb->esq = aux->dir;
	aux->dir = desb;
	return aux;
}

no_t *rotacao_ED(no_t *desb) {
	desb->esq = rotacao_EE(desb->esq);
	desb = rotacao_DD(desb);
	return desb;
}

no_t *rotacao_DE(no_t *desb) {
	desb->dir = rotacao_DD(desb->dir);
	desb = rotacao_EE(desb);
	return desb;
}

no_t *insere_avl(no_t *raiz, elem x, int *flag) {
	if(raiz != NULL) {
		if(x < raiz->info) {
			raiz->esq = insere_avl(raiz->esq, x, flag);
			if(*flag == 1) {
				switch(raiz->fb) {
					case -1:
						raiz->fb = 0;
						*flag = 0;
						break;
					case 0:
						raiz->fb = 1;
						*flag = 1;
						break;
					case 1:
						if(raiz->esq->fb == 1) { //sinais iguais
							raiz = rotacao_DD(raiz);
							raiz->dir->fb = 0;
							raiz->fb = 0;
						} else { //sinais diferentes
							raiz = rotacao_ED(raiz);
							if(raiz->fb == -1) {
								raiz->esq->fb = 1;
								raiz->dir->fb = 0;
								raiz->fb = 0;
							} else if(raiz->fb == 1) {
								raiz->esq->fb = 0;
								raiz->dir->fb = -1;
								raiz->fb = 0;
							} else { //raiz->fb == 0
								raiz->esq->fb = 0;
								raiz->dir->fb = 0;
								raiz->fb = 0;
							}
						}
						*flag = 0;
						break;
				}
			}
		} else if(x > raiz->info) {
			raiz->dir = insere_avl(raiz->dir, x, flag);			
			if(*flag == 1) {				
				switch(raiz->fb) {
					case 1:
						raiz->fb = 0;
						*flag = 0;
						break;
					case 0:
						raiz->fb = -1;
						*flag = 1;
						break;
					case -1:						
						if(raiz->dir->fb == -1) { //sinais iguais							
							raiz = rotacao_EE(raiz);
							raiz->esq->fb = 0;
							raiz->fb = 0;
						} else { //sinais diferentes
							raiz = rotacao_DE(raiz);
							if(raiz->fb == -1) {
								raiz->esq->fb = 1;
								raiz->dir->fb = 0;
								raiz->fb = 0;
							} else if(raiz->fb == 1) {
								raiz->esq->fb = 0;
								raiz->dir->fb = -1;
								raiz->fb = 0;
							} else { //raiz->fb == 0
								raiz->esq->fb = 0;
								raiz->dir->fb = 0;
								raiz->fb = 0;
							}
						}
						*flag = 0;
						break;
				}
			}
		} else {
			printf("Elemento ja existente!\n");
		}
	} else {
		raiz = (no_t *)malloc(sizeof(no_t));
		raiz->info = x;
		raiz->esq = NULL;
		raiz->dir = NULL;
		raiz->fb = 0;
		*flag = 1;
	}
	
	return raiz;
}

void inserir(arvore_t *a, elem x) {
	int flag = 0;
	a->raiz = insere_avl(a->raiz, x, &flag);
}

no_t *balanceamento_esquerdo(no_t *p, int *h) {
	printf("Balanceamento para o lado esquerdo\n");
	
	switch(p->fb) {
		case 1: //altura foi alterada
			p->fb = 0;
			break;
		case 0: //altura nao foi alterada
			p->fb = -1;
			*h = 0;
			break;
		case -1: //altura foi alterada e desbalanceou
			if(p->dir->fb <= 0) {
				p = rotacao_EE(p);
				if(p->fb == 0) {
					p->esq->fb = -1;
					p->fb = 1;
					*h = 0; //altura nao muda apos a rotacao
				} else {
					p->esq->fb = 0;
					p->fb = 0;
				}
			} else {
				printf("oi\n");
				p = rotacao_DE(p);
				if(p->fb == 1) {
					p->esq->fb = 0;
					p->dir->fb = -1;
				} else if(p->fb == -1) {
					p->esq->fb = 1;
					p->dir->fb = 0;
				} else { //p->fb == 0
					p->esq->fb = 0;
					p->dir->fb = 0;
				}
				p->fb = 0;
			}
	}
	return p;
}

no_t *balanceamento_direito(no_t *p, int *h) {
	printf("Balanceamento para o lado direito\n");	
	
	switch(p->fb) {
		case -1: //altura foi alterada
			p->fb = 0;
			break;
		case 0: //altura nao foi alterada
			p->fb = 1;
			*h = 0;
			break;
		case 1: //altura foi alterada e desbalanceou
			if(p->esq->fb >= 0) {
				p = rotacao_DD(p);
				if(p->fb == 0) {
					p->dir->fb = 1;
					p->fb = -1;
					*h = 0; //altura nao muda apos a rotacao
				} else {
					p->dir->fb = 0;
					p->fb = 0;
				}
			} else {
				p = rotacao_ED(p);
				if(p->fb == 1) {
					p->esq->fb = 0;
					p->dir->fb = -1;
				} else if(p->fb == -1) {
					p->esq->fb = 1;
					p->dir->fb = 0;
				} else { //p->fb == 0
					p->esq->fb = 0;
					p->dir->fb = 0;
				}
				p->fb = 0;
			}
	}
	return p;
}

no_t *busca_remove(no_t *p, no_t *no_chave, int *h) {
	no_t *aux;

	if(p->dir != NULL) {
		p->dir = busca_remove(p->dir, no_chave, h);
		if(*h == 1)
			p = balanceamento_direito(p, h);
	} else {
		no_chave->info = p->info;
		aux = p;
		p = p->esq;
		free(aux);
		*h = 1;
	}
	
	return p;
}

no_t *remove_avl(no_t *raiz, elem x, int *h) {
	no_t *aux;
	
	if(raiz == NULL) {
		printf("Chave nao foi encontrada!");
		*h = 0;
	} else if(x < raiz->info) {
		raiz->esq = remove_avl(raiz->esq, x, h);
		if(*h == 1) {
			raiz = balanceamento_esquerdo(raiz, h);
		}
	} else if(x > raiz->info) {
		raiz->dir = remove_avl(raiz->dir, x, h);
		if(*h == 1) {
			raiz = balanceamento_direito(raiz, h);
		}
	} else { //encontrou o elemento
		if(raiz->dir == NULL) {
			aux = raiz;
			raiz = raiz->esq;
			free(aux);
			*h = 1;
		} else if(raiz->esq == NULL) {
			aux = raiz;
			raiz = raiz->dir;
			*h = 1;
		} else {
			raiz->esq = busca_remove(raiz->esq, raiz, h);
			if(*h == 1) 
				raiz = balanceamento_esquerdo(raiz, h);
		}
	}
	
	return raiz;
}

void remover(arvore_t *a, elem x) {
	int flag = 0;
	a->raiz = remove_avl(a->raiz, x, &flag);
}






