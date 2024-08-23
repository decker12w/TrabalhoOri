#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabelaHash.h"
struct hash
{
    int qtd, TABLE_SIZE;
    struct ArvPostagem **posts;
};

Hash *criaHash(int TABLE_SIZE)
{
    Hash *ha = (Hash *)malloc(sizeof(Hash));
    if (ha != NULL)
    {
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->posts = (struct aluno **)malloc(TABLE_SIZE * sizeof(struct aluno *));
        if (ha->posts == NULL)
        {
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for (i = 0; i < ha->TABLE_SIZE; i++)
            ha->posts[i] = NULL;
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
            if (ha->posts[i] != NULL)
                free(ha->posts[i]);
        }
        free(ha->posts);
        free(ha);
    }
}
