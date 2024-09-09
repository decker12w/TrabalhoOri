#include "TabelaHash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreAux.h"

// Estrutura da tabela hash
struct hash
{
    int TABLE_SIZE;
    ArvAux **ArvPalavras;
};

// Função para inserir na hash
int insereHash(Hash *ha, char *palavraInserir, Postagem post)
{
    if (ha == NULL || ha->ArvPalavras == NULL)
        return -1;

    // Calcula a chave da palavra a ser inserida e a posição na hash
    int chave = valorString(palavraInserir);
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);

    // Cria uma palavra para inserir e copia o valor da palavra a ser inserida
    Palavra palavra;
    palavra.valor = (char *)malloc((strlen(palavraInserir) + 1) * sizeof(char));
    if (palavra.valor == NULL)
        return -1;
    strcpy(palavra.valor, palavraInserir);

        insereArvAux(ha->ArvPalavras[pos], palavra, post);
    return 0;
}

// Função para buscar na hash
Set *buscaHash(Hash *ha, char *palavraBusca, int *ok)
{
    *ok = -1; // Inicialmente, assume-se que a busca falhou
    if (ha == NULL || ha->ArvPalavras == NULL)
    {
        return NULL;
    }

    // Calcula a chave da palavra a ser inserida e a posição na hash
    int chave = valorString(palavraBusca);
    int pos = chaveDivisao(chave, ha->TABLE_SIZE);
    Palavra palavra;

    // Se a busca na árvore retornar sucesso, então ajusta 'ok' para 1
    if (busca_arvore(ha->ArvPalavras[pos], &palavra, palavraBusca) == 0) // busca_arvore retorna 0 no sucesso
    {
        // retorna o set de postagens da palavra buscada
        *ok = 1;
        return palavra.postagens;
    }

    // Se a busca falhar, 'ok' permanece -1 e NULL é retornado
    return NULL;
}

// Função para calcular o valor da chave de uma string
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

// Função de divisão para calcular a posição na hash
int chaveDivisao(int chave, int tamanhoHash)
{
    return (chave & 0x7FFFFFFF) % tamanhoHash;
}

// Função para criar a hash
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

        // Inicializa cada posição da hash com uma árvore AUX (AVL)
        for (i = 0; i < ha->TABLE_SIZE; i++)
            ha->ArvPalavras[i] = criaArvAux();
    }
    return ha;
}

// Função para liberar a memória da hash
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
