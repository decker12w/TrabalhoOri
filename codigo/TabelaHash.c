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

// Função para buscar na hash
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
    if (busca_arvore(ha->ArvPalavras[pos], &palavra, palavraBusca) == 0) // busca_arvore retorna 0 no sucesso
    {
        *ok = 1;
        return palavra.postagens;
    }

    // Se a busca falhar, 'ok' permanece 0 e NULL é retornado
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

/* // Função principal
int main()
{
    // Definir o tamanho da tabela hash
    int tamanhoHash = 10;
    Hash *hash = criaHash(tamanhoHash);

    // Verificar se a tabela hash foi criada com sucesso
    if (hash == NULL)
    {
        printf("Erro ao criar a tabela hash.\n");
        return -1;
    }

    // Criar algumas postagens e palavras para inserir na hash
    Postagem post1 = {1, 10}; // Exemplo de postagem 1
    Postagem post2 = {2, 15}; // Exemplo de postagem 2
    Postagem post3 = {3, 20}; // Exemplo de postagem 3

    // Inserir as postagens na hash
    insereHash(hash, "palavra1", post1);
    insereHash(hash, "palavra2", post2);
    insereHash(hash, "palavra3", post3);
    insereHash(hash, "palavra1", post3); // Inserindo novamente para testar busca

    // Buscar pela palavra "palavra1"
    int ok;
    Set *resultado = buscaHash(hash, "palavra1", &ok);

    if (ok == 0)
    {
        printf("Palavra não encontrada.\n");
    }
    else
    {
        printf("Resultados para a palavra 'palavra1':\n");
        for (beginSet(resultado); !endSet(resultado); nextSet(resultado))
        {
            Postagem postagem;
            getItemSet(resultado, &postagem);
            printf("Postagem { rrn: %d, tamanhoLinha: %d }\n", postagem.rrn, postagem.tamanhoLinha);
        }
    }

    // Liberar a tabela hash
    liberaHash(hash);

    return 0;
}
 */