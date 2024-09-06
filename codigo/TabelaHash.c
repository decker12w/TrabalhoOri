#include "TabelaHash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreAux.h"

struct hash
{
    int TABLE_SIZE;
    ArvAux **ArvPalavras;
};

int insereHash(Hash *ha, char *palavraInserir, Postagem post)
{
    if (ha == NULL || ha->ArvPalavras == NULL)
        return -1;

    int chave = valorString(palavraInserir);
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);

    Palavra palavra;
    palavra.valor = (char *)malloc((strlen(palavraInserir) + 1) * sizeof(char));
    if (palavra.valor == NULL)
        return -1;
    strcpy(palavra.valor, palavraInserir);

    insereArvAux(ha->ArvPalavras[pos], palavra, post);
    return 0;
}

Set *buscaHash(Hash *ha, char *palavraBusca, int *ok)
{
    *ok = 0; // Inicialmente, assume-se que a busca falhou
    if (ha == NULL || ha->ArvPalavras == NULL)
    {
        return NULL;
    }

    int chave = valorString(palavraBusca);
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    Palavra palavra;

    // Se a busca na árvore retornar sucesso, então ajusta 'ok' para 1
    if (busca_arvore(ha->ArvPalavras[pos], &palavra, palavraBusca))
    {
        *ok = 1;
        return palavra.postagens;
    }

    // Se a busca falhar, 'ok' permanece 0 e NULL é retornado
    return NULL;
}

int valorString(char *str)
{
    int i, valor = 7;
    int tam = strlen(str);

    for (i = 0; i < tam; i++)
    {
        valor = 31 * valor + (int)str[i];
    }

    return (valor & 0x7FFFFFFF);
}

int chaveDivisao(int chave, int tamanhoHash)
{
    return (chave & 0x7FFFFFFF) % tamanhoHash;
}

Hash *criaHash(int TABLE_SIZE)
{
    Hash *ha = (Hash *)malloc(sizeof(Hash));
    if (ha != NULL)
    {
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->ArvPalavras = (ArvAux **)malloc(TABLE_SIZE * sizeof(ArvAux *));
        if (ha->ArvPalavras == NULL)
        {
            free(ha);
            return NULL;
        }

        for (i = 0; i < ha->TABLE_SIZE; i++)
            ha->ArvPalavras[i] = criaArvAux();
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
            if (ha->ArvPalavras[i] != NULL)
                liberaArvAux(ha->ArvPalavras[i]);
        }
        free(ha->ArvPalavras);
        free(ha);
    }
}
