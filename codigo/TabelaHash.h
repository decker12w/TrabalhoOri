#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "Postagem.h"
#include "ArvoreAux.h"

typedef struct hash Hash;

Hash *criaHash(int);
void liberaHash(Hash *);
Set *buscaHash(Hash *, char *, int *);
int insereHash(Hash *, char *, Postagem);
int valorString(char *);
int chaveDivisao(int, int);
// SET_H
#endif