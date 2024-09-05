#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ArvoreAVL.h" //inclui os protótipos

struct NO
{
    Postagem info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

// Funções de criação e liberação da árvore
ArvAVL *cria_ArvAVL()
{
    ArvAVL *raiz = (ArvAVL *)malloc(sizeof(ArvAVL));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO *no)
{
    if (no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
}

void libera_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return;
    libera_NO(*raiz); // libera cada nó
    free(raiz);       // libera a raiz
}

// Funções auxiliares de altura e balanceamento
int altura_NO(struct NO *no)
{
    if (no == NULL)
        return -1;
    return no->altura;
}

int fatorBalanceamento_NO(struct NO *no)
{
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y)
{
    return (x > y) ? x : y;
}

int estaVazia_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL || *raiz == NULL)
        return 1;
    return 0;
}

// Funções de rotação
void RotacaoLL(ArvAVL *A)
{
    struct NO *B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq), (*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A)
{
    struct NO *B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir), (*A)->altura) + 1;
    *A = B;
}

void RotacaoLR(ArvAVL *A)
{
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A)
{
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

// Função de inserção na árvore AVL
int insere_ArvAVL(ArvAVL *raiz, Postagem valor)
{
    if (*raiz == NULL)
    {
        struct NO *novo = (struct NO *)malloc(sizeof(struct NO));
        if (novo == NULL)
            return 0;

        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    int res;

    if (valor.rrn < atual->info.rrn)
    {
        if ((res = insere_ArvAVL(&(atual->esq), valor)) == 1)
        {
            if (fatorBalanceamento_NO(atual) >= 2)
            {
                if (valor.rrn < (*raiz)->esq->info.rrn)
                {
                    RotacaoLL(raiz);
                }
                else
                {
                    RotacaoLR(raiz);
                }
            }
        }
    }
    else if (valor.rrn > atual->info.rrn)
    {
        if ((res = insere_ArvAVL(&(atual->dir), valor)) == 1)
        {
            if (fatorBalanceamento_NO(atual) >= 2)
            {
                if ((*raiz)->dir->info.rrn < valor.rrn)
                {
                    RotacaoRR(raiz);
                }
                else
                {
                    RotacaoRL(raiz);
                }
            }
        }
    }
    else
    {
        // Valor duplicado
        return 0;
    }

    atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;
    return res;
}

// Função de consulta na árvore AVL
int consulta_ArvAVL(ArvAVL *raiz, Postagem postagem)
{
    if (raiz == NULL || *raiz == NULL)
        return 0; // Árvore vazia ou nó não encontrado

    struct NO *atual = *raiz;

    if (postagem.rrn == atual->info.rrn)
        return 1; // Postagem encontrada
    else if (postagem.rrn < atual->info.rrn)
        return consulta_ArvAVL(&(atual->esq), postagem); // Busca na subárvore esquerda
    else
        return consulta_ArvAVL(&(atual->dir), postagem); // Busca na subárvore direita
}

// Função para imprimir a árvore AVL em ordem
void emOrdem_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL || *raiz == NULL)
        return;

    struct NO *atual = *raiz;

    // Percorre a subárvore esquerda
    emOrdem_ArvAVL(&(atual->esq));

    // Imprime a postagem atual
    printf("RRN: %d, Tamanho: %d\n", atual->info.rrn, atual->info.tamanhoLinha);

    // Percorre a subárvore direita
    emOrdem_ArvAVL(&(atual->dir));
}

struct NO *procuraMenor(struct NO *atual)
{
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

// Função para remover um nó da árvore AVL
int remove_ArvAVL(ArvAVL *raiz, Postagem valor)
{
    if (*raiz == NULL)
        return 0;

    int res;

    if (valor.rrn < (*raiz)->info.rrn)
    {
        if ((res = remove_ArvAVL(&(*raiz)->esq, valor)) == 1)
        {
            if (fatorBalanceamento_NO(*raiz) >= 2)
            {
                if (altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
        }
    }
    else if (valor.rrn > (*raiz)->info.rrn)
    {
        if ((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1)
        {
            if (fatorBalanceamento_NO(*raiz) >= 2)
            {
                if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    }
    else
    {
        if (((*raiz)->esq == NULL) || ((*raiz)->dir == NULL))
        {
            struct NO *oldNode = *raiz;
            if ((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(oldNode);
        }
        else
        {
            struct NO *temp = procuraMenor((*raiz)->dir);
            (*raiz)->info = temp->info;
            remove_ArvAVL(&(*raiz)->dir, temp->info);
            if (fatorBalanceamento_NO(*raiz) >= 2)
            {
                if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
        if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
        return 1;
    }

    (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    return res;
}

void iterator_ArvAVL(ArvAVL *raiz, struct iterator **iter)
{
    if (raiz == NULL)
        return;
    if (*raiz != NULL)
    {
        iterator_ArvAVL(&((*raiz)->esq), iter);

        struct iterator *no = (struct iterator *)malloc(sizeof(struct iterator));
        no->valor = (*raiz)->info;
        no->prox = *iter;
        *iter = no;

        iterator_ArvAVL(&((*raiz)->dir), iter);
    }
}
