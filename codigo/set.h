#ifndef SET_H
#define SET_H

#include "ArvoreAVL.h" // Inclui a definição de Postagem e outras funções necessárias

typedef struct set Set;

Set *criaSet();
void liberaSet(Set *s);
int insereSet(Set *s, Postagem postagem);
int removeSet(Set *s, Postagem postagem);
int tamanhoSet(Set *s);
int consultaSet(Set *s, Postagem postagem);
void imprimeSet(Set *s);
void beginSet(Set *s);
int endSet(Set *s);
void nextSet(Set *s);
void getItemSet(Set *s, Postagem *postagem);
Set *uniaoSet(Set *A, Set *B);
Set *interseccaoSet(Set *A, Set *B);
Set *NOTInterseccaoSet(Set *A, Set *B);

#endif // SET_H
