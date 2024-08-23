#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Postagem
{
    char palavra[100];
    int RRN[100];
    int quantPalavras;
    struct Postagem *esq, *dir;
} Postagem;

typedef Postagem *ArvoreAux;

ArvoreAux *criaArvore()
{
    ArvoreAux *raiz = (ArvoreAux *)malloc(sizeof(ArvoreAux));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

Postagem *criaPostagem(char palavra[], int RRN)
{
    Postagem *post = (Postagem *)malloc(sizeof(Postagem));
    if (post == NULL)
        return NULL;
    post->quantPalavras = 0;
    strcpy(post->palavra, palavra);
    post->esq = NULL;
    post->dir = NULL;
    post->RRN[post->quantPalavras] = RRN;

    return post;
}

void liberaNo(Postagem *no)
{
    if (no == NULL)
        return;
    liberaNo(no->esq);
    liberaNo(no->dir);
    free(no);
    no = NULL;
}

void liberaArvore(ArvoreAux *raiz)
{
    if (raiz == NULL)
        return;
    liberaNo(*raiz);
    free(raiz);
}

void insere_arvore(ArvoreAux *raiz, char palavra[], int RRN)
{
    if (raiz == NULL)
    {
        return;
    }

    if (*raiz == NULL)
    {
        *raiz = criaPostagem(palavra, RRN);
        return;
    }
    else
    {
        if (strcmp(palavra, (*raiz)->palavra) < 0)
        {
            insere_arvore(&((*raiz)->esq), palavra, RRN);
        }
        else if (strcmp(palavra, (*raiz)->palavra) > 0)
        {
            insere_arvore(&((*raiz)->dir), palavra, RRN);
        }
        else
        {
            (*raiz)->quantPalavras++;
            (*raiz)->RRN[(*raiz)->quantPalavras] = RRN;
        }
    }
}

int busca_arvore(ArvoreAux *raiz, int **RRN, char palavra[])
{
    if (raiz == NULL)
        return -1;
    if (*raiz == NULL)
    {
        return -1;
    }

    if (strcmp(palavra, (*raiz)->palavra) < 0)
    {
        return busca_arvore(&((*raiz)->esq), RRN, palavra);
    }
    else if (strcmp(palavra, (*raiz)->palavra) > 0)
    {
        return busca_arvore(&((*raiz)->dir), RRN, palavra);
    }
    else if (strcmp(palavra, (*raiz)->palavra) == 0)
    {
        *RRN = (*raiz)->RRN;
        return 1;
    }
    else
    {
        return -1;
    }
}
