// Postagem.h
#ifndef POSTAGEM_H
#define POSTAGEM_H

typedef struct Postagem
{
    char *palavra;
    int *RRN;
    int quantPalavras;
    int tamanhoLinha;

    struct Postagem *esq, *dir;
} Postagem;

Postagem *criaPostagem(char *palavra, int RRN, int tamanhoLinha);
#endif
