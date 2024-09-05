#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

// Definição do tipo de nó e da árvore AVL
#include "Postagem.h"
struct iterator
{
    Postagem valor;
    struct iterator *prox;
};

typedef struct NO *ArvAVL;

// Funções da árvore AVL
ArvAVL *cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, Postagem valor);
int remove_ArvAVL(ArvAVL *raiz, Postagem valor);
void iterator_ArvAVL(ArvAVL *raiz, struct iterator **iter);
int estaVazia_ArvAVL(ArvAVL *raiz);

#endif // ARVORE_AVL_H
