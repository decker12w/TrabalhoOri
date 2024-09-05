#include "TabelaHash.h"
#include "ArvoreAux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hash
{
    int TABLE_SIZE;
    ArvoreAux **ArvPosts;
};

// Função para criar uma tabela hash
Hash *criaHash(int TABLE_SIZE)
{
    Hash *ha = (Hash *)malloc(sizeof(Hash));
    if (ha != NULL)
    {
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->ArvPosts = (ArvoreAux **)malloc(TABLE_SIZE * sizeof(ArvoreAux *));
        if (ha->ArvPosts == NULL)
        {
            free(ha);
            return NULL;
        }

        // Inicializa todas as árvores nas entradas da tabela hash
        for (int i = 0; i < ha->TABLE_SIZE; i++)
            ha->ArvPosts[i] = criaArvore();
    }
    return ha;
}

// Função para liberar a tabela hash
void liberaHash(Hash *ha)
{
    if (ha != NULL)
    {
        for (int i = 0; i < ha->TABLE_SIZE; i++)
        {
            if (ha->ArvPosts[i] != NULL)
                liberaArvore(ha->ArvPosts[i]);
        }
        free(ha->ArvPosts);
        free(ha);
    }
}

// Função para inserir uma postagem na tabela hash
int insereHash(Hash *ha, Postagem *post)
{
    if (ha == NULL || post == NULL)
        return -1;
    // Calcula a posição na tabela hash com base na função hash
    int pos = funcaoHash(post->palavra) % ha->TABLE_SIZE;
    insere_arvore(ha->ArvPosts[pos], post->palavra, post->RRN[0]);
    return 0;
}

// Função para buscar uma postagem na tabela hash
int buscaHash(Hash *ha, char *palavra, int *RRN)
{
    if (ha == NULL)
        return -1;
    int pos = funcaoHash(palavra) % ha->TABLE_SIZE;
    return busca_arvore(ha->ArvPosts[pos], &RRN, palavra); // Passa o endereço de RRN (int **)
}

// Função de hash baseada no algoritmo de DJB2
unsigned long funcaoHash(char *str)
{
    unsigned long hash = 5381;
    int c;

    // Aplica a função hash caracter a caracter
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

/* // Exemplo de teste
int main()
{
    int RRN1, RRN2;

    // Cria a tabela hash com tamanho 10
    Hash *hash = criaHash(10);
    char palavra[20];

    // Insere 10 postagens de teste
    for (int i = 0; i < 10; i++)
    {
        sprintf(palavra, "teste%d", i);
        Postagem *post = criaPostagem(palavra, i);
        insereHash(hash, post);
    }

    // Testa a busca de uma palavra presente
    if (buscaHash(hash, "teste0", &RRN1) > 0)
        printf("Encontrou vetor de RRN %d\n", RRN1);
    else
        printf("Não encontrou\n");

    // Testa a busca de uma palavra ausente
    if (buscaHash(hash, "erro", &RRN2) > 0)
        printf("Encontrou vetor de RRN %d\n", RRN2);
    else
        printf("Não encontrou\n");

    // Libera a memória
    liberaHash(hash);
}
 */
