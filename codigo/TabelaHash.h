#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "Postagem.h"
#include "ArvoreAux.h"

typedef struct hash Hash;

Hash *criaHash(int TABLE_SIZE);
void liberaHash(Hash *ha);
unsigned long funcaoHash(char *str);
int insereHash(Hash *ha, Postagem *post);
int buscaHash(Hash *ha, int **RRN, char *palavra);

// Add declarations for valorString and chaveDivisao
int valorString(char *str);
int chaveDivisao(int chave, int tamanhoHash);

#endif