#pragma once
#include "Palavra.h"

typedef struct No *ArvAux;

ArvAux *criaArvAux();
int insereArvAux(ArvAux *raiz, Palavra valor, Postagem post);
int busca_arvore(ArvAux *raiz, Palavra *palavra, char *palavraBusca);
void liberaArvAux(ArvAux *);
