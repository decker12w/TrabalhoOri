#pragma once
typedef struct
{
    int rrn;
    int tamanhoLinha;
} Postagem;

struct iterator
{
    Postagem valor;
    struct iterator *prox;
};
