#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "handler.h"
#include "set.h"
#include "TabelaHash.h"

#define MAXTAM_DADOS 100

int main()
{
    FILE *arquivo;
    char linha[256];
    char *token;
    Hash *tab = criaHash(11); // Cria a tabela hash

    // Abrir o arquivo para leitura
    arquivo = fopen("corpus.csv", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    // Leitura linha por linha e inserção na tabela hash
    while (fgets(linha, sizeof(linha), arquivo))
    {
        // Suponha que os dados da linha estejam no formato "palavra,RRN,tamanhoLinha"
        // Exemplo de linha: "palavra,5,30"
        token = strtok(linha, ",");
        char *palavra = strdup(token); // Copiar a palavra

        token = strtok(NULL, ",");
        int RRN = atoi(token); // Converter o RRN para int

        token = strtok(NULL, ",");
        int tamanhoLinha = atoi(token); // Converter o tamanho da linha para int

        // Criar uma nova postagem usando a função criaPostagem
        Postagem *post = criaPostagem(palavra, RRN, tamanhoLinha);

        // Inserir a nova postagem na tabela hash
        insereHash(tab, post); // Função `insereHash` deve estar definida no seu `TabelaHash.c`

        // Liberação de memória para a palavra (que foi duplicada)
        free(palavra);
    }

    // Fechar o arquivo após a leitura
    fclose(arquivo);

    // Continuar com o restante da lógica do programa
    char entrada[200];
    int *RRN = (int *)malloc(MAXTAM_DADOS * sizeof(int));
    int numComponentes = 0, value;

    // Leitura da frase de entrada
    printf("Digite a frase a ser buscada (com operadores lógicos AND, OR, NOT): ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0'; // Remove o newline no final da string

    // Limpar a string removendo caracteres especiais
    limparString(entrada);
    printf("Frase limpa: %s\n", entrada);

    // Separar a frase em componentes
    char **componentes = separarBuscaEmComponentes(entrada, &numComponentes);
    if (componentes == NULL)
    {
        printf("Erro ao separar a frase em componentes.\n");
        liberaHash(tab);
        free(RRN);
        return 1;
    }

    // Exibir os componentes separados
    printf("Componentes da frase:\n");
    for (int i = 0; i < numComponentes; i++)
    {
        printf("%s\n", componentes[i]);
    }

    // Converter a expressão para a notação pós-fixada
    int tamanhoPostfix;
    char **postfix = converterComponentesParaPostfix(componentes, numComponentes, &tamanhoPostfix);
    if (postfix == NULL)
    {
        printf("Erro ao converter para postfix.\n");
        liberaHash(tab);
        free(RRN);
        return 1;
    }

    // Exibir a expressão em pós-fixado
    printf("Expressão Pós-fixada:\n");
    for (int i = 0; i < tamanhoPostfix; i++)
    {
        printf("%s ", postfix[i]);
    }
    printf("\n");

    // Avaliar a expressão pós-fixada e buscar resultados na hash
    Set *resultado = avaliarPostfix(tab, postfix, tamanhoPostfix);
    if (resultado != NULL)
    {
        printf("Resultado: Conjunto encontrado.\n");

        // Laço para percorrer os termos (palavras) e buscar seus RRNs
        for (int i = 0; i < tamanhoPostfix; i++)
        {
            if (!isOperator(postfix[i])) // Se não for um operador, buscamos a palavra
            {
                value = buscaHash(tab, RRN, postfix[i]); // Função buscaHash busca o RRN associado à palavra
                if (value != -1 && RRN != NULL)
                {
                    printf("Palavra: %s - RRNs: ", postfix[i]);
                    for (int j = 0; j < value; j++)
                    {
                        printf("%d ", RRN[j]); // Exibir os RRNs encontrados
                    }
                    printf("\n");
                }
                else
                {
                    printf("Nenhum RRN encontrado para a palavra '%s'.\n", postfix[i]);
                }
            }
        }
    }
    else
    {
        printf("Resultado: Nenhuma postagem foi encontrada.\n");
    }

    // Liberar memória alocada
    for (int i = 0; i < numComponentes; i++)
    {
        free(componentes[i]);
    }
    free(componentes);
    liberaHash(tab);
    free(RRN);

    return 0;
}
