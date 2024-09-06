#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "Postagem.h"
#include "ArvoreAux.h"

typedef struct hash Hash;

Hash *criaHash(int TABLE_SIZE);
void liberaHash(Hash *ha);
Set *buscaHash(Hash *ha, char *palavra, int *deuCerto);
int insereHash(Hash *hash, char *novaPalavra, Postagem novaPostagem);
int valorString(char *str);
int chaveDivisao(int chave, int tamanhoHash);

#endif