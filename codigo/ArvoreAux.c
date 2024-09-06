#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAux.h"
#include <string.h>

struct No
{
    Palavra info;
    int altura;
    struct No *esq;
    struct No *dir;
};

ArvAux *criaArvAux()
{
    ArvAux *raiz = (ArvAux *)malloc(sizeof(ArvAux));
    if (raiz != NULL)
    {
        *raiz = NULL;
    }

    return raiz;
}

void liberaNoAVLAUX(struct No *no)
{
    if (no == NULL)
    {
        return;
    }

    liberaNoAVLAUX(no->esq);
    liberaNoAVLAUX(no->dir);
    free(no);
    no = NULL;
}

void liberaArvAux(ArvAux *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    liberaNoAVLAUX(*raiz);
    free(raiz);
}

int alturaNoAUX(struct No *no)
{
    if (no == NULL)
    {
        return -1;
    }

    return no->altura;
}

int fatorBalanceamentoNoAUX(struct No *no)
{
    return labs(alturaNoAUX(no->esq) - alturaNoAUX(no->dir));
}

int maiorAUX(int x, int y)
{
    if (x > y)
    {
        return x;
    }

    return y;
}

int busca_arvore(ArvAux *raiz, Palavra *palavra, char *palavraBusca)
{
    if (raiz == NULL || *raiz == NULL)
        return -1;

    if (strcmp(palavraBusca, (*raiz)->info.valor) < 0)
    {
        return busca_arvore(&((*raiz)->esq), palavra, palavraBusca);
    }
    else if (strcmp(palavraBusca, (*raiz)->info.valor) > 0)
    {
        return busca_arvore(&((*raiz)->dir), palavra, palavraBusca);
    }
    else
    {
        *palavra = (*raiz)->info;
        return 0;
    }
}

void rotacaoLLAUX(ArvAux *A)
{
    struct No *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maiorAUX(alturaNoAUX((*A)->esq), alturaNoAUX((*A)->dir)) + 1;
    B->altura = maiorAUX(alturaNoAUX(B->esq), (*A)->altura) + 1;
    *A = B;
}

void rotacaoRRAUX(ArvAux *A)
{
    struct No *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maiorAUX(alturaNoAUX((*A)->esq), alturaNoAUX((*A)->dir)) + 1;
    B->altura = maiorAUX(alturaNoAUX(B->dir), (*A)->altura) + 1;
    (*A) = B;
}

void rotacaoLRAUX(ArvAux *A)
{
    rotacaoRRAUX(&(*A)->esq);
    rotacaoLLAUX(A);
}

void rotacaoRLAUX(ArvAux *A)
{
    rotacaoLLAUX(&(*A)->dir);
    rotacaoRRAUX(A);
}

int insereArvAux(ArvAux *raiz, Palavra valor, Postagem post)
{
    if (*raiz == NULL)
    {
        // Se a árvore estiver vazia, cria um novo nó com a palavra e o set
        struct No *novo = (struct No *)malloc(sizeof(struct No));
        if (novo == NULL)
        {
            return 0; // Falha ao alocar memória
        }

        // Inicializa a palavra e o set
        novo->info = valor;
        novo->info.postagens = criaSet();      // Cria um novo set para as postagens
        insereSet(novo->info.postagens, post); // Adiciona a postagem ao set

        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;

        return 1;
    }

    struct No *atual = *raiz;
    if (strcmp(valor.valor, atual->info.valor) < 0)
    {
        if (insereArvAux(&(atual->esq), valor, post))
        {
            if (fatorBalanceamentoNoAUX(atual) >= 2)
            {
                if (strcmp(valor.valor, (*raiz)->esq->info.valor) < 0)
                {
                    rotacaoLLAUX(raiz);
                }
                else
                {
                    rotacaoLRAUX(raiz);
                }
            }
        }
    }
    else if (strcmp(valor.valor, atual->info.valor) > 0)
    {
        if (insereArvAux(&(atual->dir), valor, post))
        {
            if (fatorBalanceamentoNoAUX(atual) >= 2)
            {
                if (strcmp(valor.valor, (*raiz)->dir->info.valor) > 0)
                {
                    rotacaoRRAUX(raiz);
                }
                else
                {
                    rotacaoRLAUX(raiz);
                }
            }
        }
    }
    else
    {

        insereSet(atual->info.postagens, post);
    }

    atual->altura = maiorAUX(alturaNoAUX(atual->esq), alturaNoAUX(atual->dir)) + 1;
    return 1;
}

struct No *procuraMenorAUX(struct No *atual)
{
    struct No *no1 = atual;
    struct No *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }

    return no1;
}
