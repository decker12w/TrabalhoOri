#ifndef ARVORE_AUX_H
#define ARVORE_AUX_H

#include "Postagem.h"

typedef Postagem *ArvoreAux;

ArvoreAux *criaArvore();

void liberaNo(Postagem *no);
void liberaArvore(ArvoreAux *raiz);
void insere_arvore(ArvoreAux *raiz, char palavra[], int RRN);
int busca_arvore(ArvoreAux *raiz, int **RRN, char palavra[]);
void imprimeArvore(ArvoreAux *raiz);

#endif
