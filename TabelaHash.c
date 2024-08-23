#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabelaHash.h"
#include "ArvoreAux.h"
struct hash
{
    int TABLE_SIZE;
    struct ArvoreAux **ArvPosts;
};

Hash *criaHash(int TABLE_SIZE)
{
    Hash *ha = (Hash *)malloc(sizeof(Hash));
    if (ha != NULL)
    {
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->ArvPosts = (struct ArvoreAux **)malloc(TABLE_SIZE * sizeof(struct ArvoreAux *));
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

/* void liberaHash(Hash *ha)
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
} */
