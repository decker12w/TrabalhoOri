#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "handler.h"
#include "set.h"
#include "TabelaHash.h"

#define MAXTAM_DADOS 100
#define MAXTAM_PILHA 100

// Função para verificar se um caractere está dentro de uma palavra composta
int palavraComposta(char *valor, int i, int tamanho)
{
    return (i > 0 && i < tamanho - 1 && isalpha(valor[i - 1]) && isalpha(valor[i + 1]));
}

// Função para limpar a string removendo caracteres especiais e convertendo para minúsculas
void limparString(char *valor)
{
    int tamanho = strlen(valor);
    char stringLimpa[tamanho + 1];
    int quantidadeCaracteresValidos = 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (isalpha(valor[i]) || isdigit(valor[i]))
        {
            stringLimpa[quantidadeCaracteresValidos++] = tolower(valor[i]);
        }
        else if ((valor[i] == '-' || valor[i] == '\'') && palavraComposta(valor, i, tamanho))
        {
            stringLimpa[quantidadeCaracteresValidos++] = valor[i];
        }
        else if (quantidadeCaracteresValidos > 0 && stringLimpa[quantidadeCaracteresValidos - 1] != ' ')
        {
            stringLimpa[quantidadeCaracteresValidos++] = ' ';
        }
    }

    if (quantidadeCaracteresValidos > 0 && stringLimpa[quantidadeCaracteresValidos - 1] == ' ')
    {
        quantidadeCaracteresValidos--;
    }

    stringLimpa[quantidadeCaracteresValidos] = '\0';
    strcpy(valor, stringLimpa);
}

// Função para separar a busca em componentes
char **separarBuscaEmComponentes(char *busca, int *numComponentes)
{
    char **componentes = (char **)malloc(MAXTAM_DADOS * sizeof(char *));
    int i = 0;

    if (componentes == NULL)
    {
        return NULL;
    }

    while (*busca != '\0')
    {
        while (isspace(*busca))
            busca++;

        if (*busca == '\0')
            break;

        // Operadores e parênteses
        if (*busca == '(' || *busca == ')' || !isalnum(*busca))
        {
            componentes[i] = malloc(2 * sizeof(char));
            componentes[i][0] = *busca;
            componentes[i][1] = '\0';
            i++;
            busca++;
        }
        else
        {
            char *componente = busca;
            while (*busca != '\0' && isalnum(*busca))
                busca++;
            int tamanho = busca - componente;
            componentes[i] = malloc((tamanho + 1) * sizeof(char));
            strncpy(componentes[i], componente, tamanho);
            componentes[i][tamanho] = '\0';
            i++;
        }
    }

    *numComponentes = i;
    return componentes;
}

// Função para retornar a precedência dos operadores
int precedencia(char *operacao)
{
    if (strcmp(operacao, "NOT") == 0)
        return 3;
    if (strcmp(operacao, "AND") == 0)
        return 2;
    if (strcmp(operacao, "OR") == 0)
        return 1;
    return 0;
}

char **converterComponentesParaPostfix(char **componentes, int tamanho, int *tamanhoPostfix)
{
    char **resultado = (char **)malloc(MAX_PILHA * sizeof(char *));
    if (resultado == NULL)
    {
        return NULL;
    }

    char *pilha[MAX_PILHA];
    int topo = -1;
    int indice = 0;

    for (int i = 0; i < tamanho; i++)
    {
        char *componente = componentes[i];

        // Se não for operador, adiciona diretamente à saída
        if (!isOperator(componente) && strcmp(componente, "(") != 0 && strcmp(componente, ")") != 0)
        {
            resultado[indice] = (char *)malloc((strlen(componente) + 1) * sizeof(char));
            strcpy(resultado[indice], componente);
            indice++;
        }
        // Se for um parêntese de abertura, empilha
        else if (strcmp(componente, "(") == 0)
        {
            pilha[++topo] = componente;
        }
        // Se for um parêntese de fechamento, desempilha até o parêntese de abertura
        else if (strcmp(componente, ")") == 0)
        {
            while (topo != -1 && strcmp(pilha[topo], "(") != 0)
            {
                resultado[indice] = (char *)malloc((strlen(pilha[topo]) + 1) * sizeof(char));
                strcpy(resultado[indice++], pilha[topo--]);
            }
            topo--; // Remove o parêntese de abertura
        }
        else
        {
            // Operador encontrado: garante a precedência correta
            while (topo != -1 && precedencia(pilha[topo]) >= precedencia(componente))
            {
                resultado[indice] = (char *)malloc((strlen(pilha[topo]) + 1) * sizeof(char));
                strcpy(resultado[indice++], pilha[topo--]);
            }
            pilha[++topo] = componente;
        }
    }

    // Esvaziar a pilha de operadores restantes
    while (topo != -1)
    {
        resultado[indice] = (char *)malloc((strlen(pilha[topo]) + 1) * sizeof(char));
        strcpy(resultado[indice++], pilha[topo--]);
    }

    *tamanhoPostfix = indice;

    return resultado;
}

Set *avaliarPostfix(Hash *hash, char **postfix, int quantidade)
{
    Set *pilha[MAX_PILHA];
    int topo = -1;
    int operadorNot = 0;
    int elementoNegado = -1;

    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(postfix[i], "NOT") == 0)
        {
            if (elementoNegado != -1)
            {
                printf("Busca inválida.\n");
                return NULL;
            }
            operadorNot = 1;
            elementoNegado = topo;
        }
        else if (strcmp(postfix[i], "AND") == 0)
        {
            if (topo < 1)
            {
                printf("Busca inválida.\n");
                return NULL;
            }

            Set *set1 = pilha[topo];
            topo--;
            Set *set2 = pilha[topo];
            topo--;

            if (operadorNot)
            {
                if (elementoNegado == 0)
                {
                    pilha[++topo] = interseccaoSetComNot(set1, set2);
                }
                else
                {
                    pilha[++topo] = interseccaoSetComNot(set2, set1);
                }
            }
            else
            {
                pilha[++topo] = interseccaoSet(set1, set2);
            }
            operadorNot = 0;
            elementoNegado = -1;
        }
        else if (strcmp(postfix[i], "OR") == 0)
        {
            if (topo < 1)
            {
                printf("Busca inválida.\n");
                return NULL;
            }

            Set *set1 = pilha[topo];
            topo--;
            Set *set2 = pilha[topo];
            topo--;

            if (operadorNot)
            {
                printf("Busca inválida.\n");
                return NULL;
            }
            else
            {
                pilha[++topo] = uniaoSet(set1, set2);
            }
            operadorNot = 0;
        }
        else
        {
            // int deuCerto;
            // Set *conjunto = buscaHash(hash, postfix[i], &deuCerto);
            // if (deuCerto)
            // {
            //     pilha[++topo] = conjunto;
            // }
            // else
            // {
            //     pilha[++topo] = criaSet();
            // }
        }
    }

    if (topo != 0 || tamanhoSet(pilha[topo]) == 0)
    {
        printf("Nenhuma postagem foi encontrada.\n");
        return NULL;
    }

    return pilha[topo];
}

int isOperator(char *token)
{
    return strcmp(token, "NOT") == 0 || strcmp(token, "AND") == 0 || strcmp(token, "OR") == 0;
}

// int main()
// {
//     char frase[] = "(usa AND NOT palavra) OR (tentativa AND mouse)";
//     printf("Expressão lógica: %s\n", frase);

//     // Limpar a string e separar os componentes
//     limparString(frase);
//     printf("Frase limpa: %s\n", frase);

//     int numComponentes;
//     char **componentes = separarBuscaEmComponentes(frase, &numComponentes);
//     if (componentes == NULL)
//     {
//         printf("Erro ao separar a busca em componentes.\n");
//         return 1;
//     }

//     printf("Componentes da busca:\n");
//     for (int i = 0; i < numComponentes; i++)
//     {
//         printf("%s\n", componentes[i]);
//     }

//     // Converter para postfix
//     int tamanhoPostfix;
//     char **postfix = converterComponentesParaPostfix(componentes, numComponentes, &tamanhoPostfix);
//     if (postfix == NULL)
//     {
//         printf("Erro ao converter para postfix.\n");
//         return 1;
//     }

//     printf("Expressão Pós-fixada:\n");
//     for (int i = 0; i < tamanhoPostfix; i++)
//     {
//         printf("%s ", postfix[i]);
//     }
//     printf("\n");

//     // Criar uma hash fictícia (precisa ser implementada no projeto real)
//     Hash *hash = NULL;

//     // Avaliar a expressão postfix
//     Set *resultado = avaliarPostfix(hash, postfix, tamanhoPostfix);
//     if (resultado != NULL)
//     {
//         printf("Resultado: Conjunto encontrado.\n");
//     }
//     else
//     {
//         printf("Resultado: Nenhuma postagem foi encontrada.\n");
//     }

//     // Liberar memória alocada
//     for (int i = 0; i < numComponentes; i++)
//     {
//         free(componentes[i]);
//     }
//     free(componentes);

//     return 0;
// }
