// ArvoreAux.c content
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreAux.h"

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
    post->quantPalavras = 1;                // Start with 1 RRN
    post->RRN = (int *)malloc(sizeof(int)); // Allocate space for 1 RRN
    if (post->RRN == NULL)
    {
        free(post);
        return NULL;
    }
    strcpy(post->palavra, palavra);
    post->esq = NULL;
    post->dir = NULL;
    post->RRN[0] = RRN; // Set the first RRN

    return post;
}

void liberaNo(Postagem *no)
{
    if (no == NULL)
        return;
    liberaNo(no->esq);
    liberaNo(no->dir);
    free(no->RRN); // Free the RRN array
    free(no);
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
            (*raiz)->RRN = realloc((*raiz)->RRN, (++(*raiz)->quantPalavras) * sizeof(int));
            (*raiz)->RRN[(*raiz)->quantPalavras - 1] = RRN;
        }
    }
}

int busca_arvore(ArvoreAux *raiz, int **RRN, char palavra[])
{
    if (raiz == NULL || *raiz == NULL)
        return -1;

    if (strcmp(palavra, (*raiz)->palavra) < 0)
    {
        return busca_arvore(&((*raiz)->esq), RRN, palavra);
    }
    else if (strcmp(palavra, (*raiz)->palavra) > 0)
    {
        return busca_arvore(&((*raiz)->dir), RRN, palavra);
    }
    else
    {
        *RRN = (*raiz)->RRN;
        return (*raiz)->quantPalavras;
    }
}

void imprimeArvore(ArvoreAux *raiz)
{
    if (raiz == NULL || *raiz == NULL)
        return;
    imprimeArvore(&((*raiz)->esq));
    printf("%s\n", (*raiz)->palavra);
    imprimeArvore(&((*raiz)->dir));
}

// Teste de funcionamento da árvore
int main()
{
    int *RRN1 = NULL, *RRN2 = NULL;

    ArvoreAux *raiz = criaArvore();
    insere_arvore(raiz, "teste", 1);
    insere_arvore(raiz, "teste", 2);
    insere_arvore(raiz, "teste", 3);
    insere_arvore(raiz, "teste2", 3);

    // Teste de funcionar
    if (busca_arvore(raiz, &RRN1, "teste") > 0)
        printf("Encontrou vetor de rrn %d\n", RRN1[1]);
    else
        printf("Não encontrou\n");

    // Teste deve falhar
    if (busca_arvore(raiz, &RRN2, "erro") > 0)
        printf("Encontrou vetor de rrn %d\n", RRN2[0]);
    else
        printf("Não encontrou\n");

    imprimeArvore(raiz);
    liberaArvore(raiz);
}