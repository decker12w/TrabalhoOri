#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Postagem.h"

Postagem *criaPostagem(char *palavra, int RRN, int tamanhoLinha)
{
    Postagem *post = (Postagem *)malloc(sizeof(Postagem));
    if (post == NULL)
    {
        perror("Erro ao alocar memória para Postagem");
        return NULL;
    }
    post->tamanhoLinha = tamanhoLinha;
    post->quantPalavras = 1;
    post->RRN = (int *)malloc(sizeof(int));
    if (post->RRN == NULL)
    {
        free(post);
        perror("Erro ao alocar memória para RRN");
        return NULL;
    }

    // Aloca memória dinamicamente para armazenar a string palavra
    post->palavra = (char *)malloc(strlen(palavra) + 1);
    if (post->palavra == NULL)
    {
        free(post->RRN);
        free(post);
        perror("Erro ao alocar memória para palavra");
        return NULL;
    }
    strcpy(post->palavra, palavra); // Copia a string para a memória alocada

    post->esq = NULL;
    post->dir = NULL;
    post->RRN[0] = RRN;

    return post;
}
