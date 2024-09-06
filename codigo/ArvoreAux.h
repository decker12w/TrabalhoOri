#ifndef ARVORE_AUX_H
#define ARVORE_AUX_H

#include "Postagem.h"

typedef Postagem *ArvoreAux;

ArvoreAux *criaArvore();

void liberaNo(Postagem *no);
void liberaArvore(ArvoreAux *raiz);
int busca_arvore(ArvoreAux *raiz, int **RRN, char palavra[]);
void imprimeArvore(ArvoreAux *raiz);
int insere_arvore(ArvoreAux *raiz, char *palavra, int RRN, int tamanhoLinha);
int maior(int a, int b);
int altura_Post(struct Postagem *post);
int fator_balanco(Postagem *Post);
void RotacaoLL(ArvoreAux *raiz);
void RotacaoRR(ArvoreAux *raiz);
void RotacaoLR(ArvoreAux *raiz);
void RotacaoRL(ArvoreAux *raiz);

#endif
