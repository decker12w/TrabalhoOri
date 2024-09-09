#ifndef POSTAGEM_H
#define POSTAGEM_H

typedef struct
{
    int RRN;
    int tamanhoLinha;
} Postagem;

struct iterator
{
    Postagem valor;
    struct iterator *prox;
};

#endif