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

// Função para retornar o maior valor entre dois inteiros
int maior(int a, int b)
{
    return (a > b) ? a : b;
}

// Função para calcular a altura de uma postagem
int altura_Post(struct Postagem *post)
{
    if (post == NULL)
        return -1;
    else
        return post->altura;
}

// Função para calcular o fator de balanço de um nó
int fator_balanco(Postagem *Post)
{
    if (Post == NULL)
    {
        return 0;
    }
    return altura_Post(Post->esq) - altura_Post(Post->dir);
}

// Funções de rotação para balanceamento da árvore
void RotacaoLL(ArvoreAux *A)
{
    Postagem *B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_Post((*A)->esq), altura_Post((*A)->dir)) + 1;
    B->altura = maior(altura_Post(B->esq), (*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvoreAux *A)
{
    Postagem *B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;
    (*A)->altura = maior(altura_Post((*A)->esq), altura_Post((*A)->dir)) + 1;
    B->altura = maior(altura_Post(B->dir), (*A)->altura) + 1;
    *A = B;
}

void RotacaoLR(ArvoreAux *A)
{
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvoreAux *A)
{
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_arvore(ArvoreAux *raiz, char *palavra, int RRN, int tamanhoLinha)
{
    if (raiz == NULL)
    {
        return 0;
    }

    if (*raiz == NULL)
    {
        *raiz = criaPostagem(palavra, RRN, tamanhoLinha);
        return 1;
    }

    Postagem *atual = *raiz;

    if (strcmp(palavra, atual->palavra) < 0)
    {
        insere_arvore(&(atual->esq), palavra, RRN, tamanhoLinha);

        // Verificar se precisa balancear a árvore
        if (fator_balanco(atual) >= 2)
        {
            if (strcmp(palavra, atual->esq->palavra) < 0)
            {
                RotacaoLL(raiz); // Rotação simples à direita
            }
            else
            {
                RotacaoLR(raiz); // Rotação esquerda-direita
            }
        }
    }
    else if (strcmp(palavra, atual->palavra) > 0)
    {
        insere_arvore(&(atual->dir), palavra, RRN, tamanhoLinha);

        // Verificar se precisa balancear a árvore
        if (fator_balanco(atual) <= -2)
        {
            if (strcmp(palavra, atual->dir->palavra) > 0)
            {
                RotacaoRR(raiz); // Rotação simples à esquerda
            }
            else
            {
                RotacaoRL(raiz); // Rotação direita-esquerda
            }
        }
    }
    else
    {
        // Palavra já existe, adiciona o RRN ao vetor
        atual->RRN = realloc(atual->RRN, (++atual->quantPalavras) * sizeof(int));
        atual->RRN[atual->quantPalavras - 1] = RRN;
        return 0;
    }

    // Atualizar a altura do nó após a inserção
    atual->altura = maior(altura_Post(atual->esq), altura_Post(atual->dir)) + 1;

    return 1;
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
} */