#include "TabelaHash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash
{
    int TABLE_SIZE;
    ArvoreAux **ArvPosts;
};

Hash *criaHash(int TABLE_SIZE)
{
    Hash *ha = (Hash *)malloc(sizeof(Hash));
    if (ha != NULL)
    {
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->ArvPosts = (ArvoreAux **)malloc(TABLE_SIZE * sizeof(ArvoreAux *));
        if (ha->ArvPosts == NULL)
        {
            free(ha);
            return NULL;
        }

        for (i = 0; i < ha->TABLE_SIZE; i++)
            ha->ArvPosts[i] = criaArvore();
    }
    return ha;
}

void liberaHash(Hash *ha)
{
    if (ha != NULL)
    {
        int i;
        for (i = 0; i < ha->TABLE_SIZE; i++)
        {
            if (ha->ArvPosts[i] != NULL)
                liberaArvore(ha->ArvPosts[i]);
        }
        free(ha->ArvPosts);
        free(ha);
    }
}

int insereHash(Hash *ha, Postagem *post)
{
    if (ha == NULL || post == NULL)
        return -1;
    int pos = funcaoHash(post->palavra) % ha->TABLE_SIZE;
    insere_arvore(ha->ArvPosts[pos], post->palavra, post->RRN[0]);
    return 0;
}

int buscaHash(Hash *ha, int **RRN, char *palavra)
{
    if (ha == NULL)
        return -1;
    int pos = funcaoHash(palavra) % ha->TABLE_SIZE;
    return busca_arvore(ha->ArvPosts[pos], RRN, palavra);
}

unsigned long funcaoHash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

// Teste de funcionamento da árvore
int main()
{
    int *RRN1, *RRN2;

    Hash *hash = criaHash(10);
    char palavra[20];

    for (int i = 0; i < 10; i++)
    {
        sprintf(palavra, "teste%d", i);
        Postagem *post = criaPostagem(palavra, i);
        insereHash(hash, post);
    }

    // Teste de funcionar
    if (buscaHash(hash, &RRN1, "teste0") > 0)
        printf("Encontrou vetor de rrn %d\n", RRN1[0]);
    else
        printf("Não encontrou\n");

    // Teste deve falhar
    if (buscaHash(hash, &RRN2, "erro") > 0)
        printf("Encontrou vetor de rrn %d\n", RRN2[0]);
    else
        printf("Não encontrou\n");

    liberaHash(hash);
}
