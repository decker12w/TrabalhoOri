// Postagem.h
#ifndef POSTAGEM_H
#define POSTAGEM_H

typedef struct Postagem
{
    char palavra[100];
    int *RRN;
    int quantPalavras;
    struct Postagem *esq, *dir;
} Postagem;

#endif
