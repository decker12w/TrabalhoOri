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
    char *frase, *token;
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
        // Simulando a inserção na tabela hash
        printf("Linha lida: %s\n", linha);
        // Aqui você pode adicionar a lógica para inserir os dados da linha na tabela hash
        // usando as funções de inserção específicas da sua hash
    }

    // Fechar o arquivo após a leitura
    fclose(arquivo);

    // Continuar com o restante da lógica do programa
    char entrada[200];
    int *RRN = NULL;
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
        value = buscaHash(tab, entrada, RRN); // Passa a palavra 'entrada' e o ponteiro 'RRN'

        if (value != -1 && RRN != NULL)
        {
            for (int j = 0; j < value; j++)
            {
                printf("RRN[%d]: %d\n", j, RRN[j]);
            }
        }
        else
        {
            printf("Nenhum RRN encontrado.\n");
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

    return 0;
}
