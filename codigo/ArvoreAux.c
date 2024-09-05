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

void insere_arvore(ArvoreAux *raiz, char *palavra, int RRN, int tamanhoLinha)
{
    if (raiz == NULL)
    {
        return;
    }

    if (*raiz == NULL)
    {
        *raiz = criaPostagem(palavra, RRN, tamanhoLinha);
    }
    else
    {
        if (strcmp(palavra, (*raiz)->palavra) < 0)
        {
            insere_arvore(&((*raiz)->esq), palavra, RRN, tamanhoLinha);
        }
        else if (strcmp(palavra, (*raiz)->palavra) > 0)
        {
            insere_arvore(&((*raiz)->dir), palavra, RRN, tamanhoLinha);
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

/* // Teste de funcionamento da árvore
int main()
{
    int *RRN1, *RRN2;

    ArvoreAux *raiz = criaArvore();
    insere_arvore(raiz, "teste", 1, 1);
    insere_arvore(raiz, "teste", 2, 1);
    insere_arvore(raiz, "teste", 3, 1);
    insere_arvore(raiz, "teste2", 3, 1);

    // Teste de funcionar
    if (busca_arvore(raiz, &RRN1, "teste") > 0)
        for (int i = 0; i < 3; i++)
            printf("Encontrou vetor de rrn %d\n", RRN1[i]);
    else
        printf("Não encontrou\n");

    // Teste deve falhar
    if (busca_arvore(raiz, &RRN2, "erro") > 0)
        printf("Encontrou vetor de rrn %d\n", RRN2[0]);
    else
        printf("Não encontrou\n");

    imprimeArvore(raiz);
    liberaArvore(raiz);
} */