#ifndef ARVOREAUX_H
#define ARVOREAUX_H

#include "Palavra.h"

typedef struct No *ArvAux;

ArvAux *criaArvAux();
int insereArvAux(ArvAux *, Palavra, Postagem);
int busca_arvore(ArvAux *, Palavra *, char *);
void liberaArvAux(ArvAux *);

#endif