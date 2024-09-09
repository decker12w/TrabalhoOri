#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include "Postagem.h"

typedef struct No *ArvAVL;

ArvAVL *criaArvAVL();
int insereArvAVL(ArvAVL *, Postagem);
int consultaArvAVL(ArvAVL *, Postagem);
void iteratorArvAVL(ArvAVL *, struct iterator **);
void liberaArvAVL(ArvAVL *);

#endif // ARVOREAVL_H