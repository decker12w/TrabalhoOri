#ifndef SET_H
#define SET_H

#include "ArvoreAvl.h"

typedef struct set Set;

Set *criaSet();
void liberaSet(Set *);
int insereSet(Set *, Postagem);
int tamanhoSet(Set *);
int consultaSet(Set *, Postagem);
Set *uniaoSet(Set *, Set *);
Set *interseccaoSet(Set *, Set *);
Set *interseccaoSetComNot(Set *, Set *);
void beginSet(Set *);
int endSet(Set *);
void nextSet(Set *);
void getItemSet(Set *, Postagem *);

#endif