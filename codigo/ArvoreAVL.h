#pragma once
#include "Postagem.h"

struct iterator
{
    Postagem valor;
    struct iterator *prox;
};

typedef struct No *ArvAVL;

ArvAVL *criaArvAVL();
int insereArvAVL(ArvAVL *, Postagem);
int consultaArvAVL(ArvAVL *, Postagem);
void iteratorArvAVL(ArvAVL *, struct iterator **);
void liberaArvAVL(ArvAVL *);