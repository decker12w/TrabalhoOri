#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "handler.h"

#define MAX_COMPONENTES 100
#define MAX_PILHA 100

// Função que separa a string de busca em componentes (palavras e operadores)
char **Componente(char *busca, int *numComponentes)
{
    *numComponentes = 0;
    char **componentes = (char **)malloc(MAX_COMPONENTES * sizeof(char *));
    if (componentes == NULL)
    {
        return NULL;
    }

    char *componente;
    int i = 0;

    // Loop para processar cada componente da string de busca
    while (*busca != '\0')
    {
        while (isspace(*busca)) // Ignora espaços em branco
        {
            busca++;
        }

        if (*busca == '\0')
        {
            break;
        }

        // Verifica operadores simples ou caracteres especiais
        if (*busca == '(' || *busca == ')' || !isalnum(*busca))
        {
            componentes[i] = malloc(2 * sizeof(char));
            componentes[i][0] = *busca;
            componentes[i][1] = '\0';
            i++;
            busca++;
        }
        else // Captura palavras
        {
            componente = busca;
            while (*busca != '\0' && isalnum(*busca))
            {
                busca++;
            }
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

// Define a precedência dos operadores lógicos
int precedencia(char *operacao)
{
    if (strcmp(operacao, "NOT") == 0)
    {
        return 3;
    }
    if (strcmp(operacao, "AND") == 0)
    {
        return 2;
    }
    if (strcmp(operacao, "OR") == 0)
    {
        return 1;
    }
    return 0;
}

// Converte a expressão infix para postfix (notação polonesa reversa)
char **converterParaPostfix(char **componentes, int tamanho, int *tamanhoPostfix)
{
    char **resultado = (char **)malloc(MAX_PILHA * sizeof(char *));
    if (resultado == NULL)
    {
        return NULL;
    }

    char *pilha[MAX_PILHA];
    int topo = -1;
    int indice = 0;

    // Percorre cada componente da expressão
    for (int i = 0; i < tamanho; i++)
    {
        char *componente = componentes[i];

        // Verifica se o componente é uma palavra
        if (strcmp(componente, "NOT") != 0 && strcmp(componente, "AND") != 0 && strcmp(componente, "OR") != 0 && strcmp(componente, "(") != 0 && strcmp(componente, ")") != 0)
        {
            for (int i = 0; componente[i] != '\0'; i++) // Converte para minúsculas
            {
                componente[i] = tolower(componente[i]);
            }
            resultado[indice] = componente;
            indice++;
        }
        else if (strcmp(componente, "(") == 0) // Trata parênteses de abertura
        {
            topo++;
            pilha[topo] = componente;
        }
        else if (strcmp(componente, ")") == 0) // Trata parênteses de fechamento
        {
            while (topo != -1 && strcmp(pilha[topo], "(") != 0)
            {
                resultado[indice] = pilha[topo];
                indice++;
                topo--;
            }
            topo--; // Remove o parêntese de abertura
        }
        else // Operadores lógicos
        {
            while (topo != -1 && precedencia(pilha[topo]) >= precedencia(componente))
            {
                resultado[indice] = pilha[topo];
                indice++;
                topo--;
            }
            topo++;
            pilha[topo] = componente;
        }
    }

    // Adiciona os operadores restantes à saída postfix
    while (topo != -1)
    {
        resultado[indice] = pilha[topo];
        indice++;
        topo--;
    }

    *tamanhoPostfix = indice;
    return resultado;
}

// Avalia a expressão postfix e retorna o conjunto de resultados
Set *avaliarPostfix(Hash *hash, char **postfix, int quantidade, int *tipoErro)
{
    Set *pilha[MAX_PILHA];
    int topo = -1;
    int operadorNot = 0; // Indica uso do operador NOT
    int elementoNegado = -1;

    // Percorre cada componente da expressão postfix
    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(postfix[i], "NOT") == 0)
        {
            if (quantidade == 2 || elementoNegado != -1)
            {
                *tipoErro = 2;
                return NULL;
            }

            operadorNot = 1;
            elementoNegado = topo;
        }
        else if (strcmp(postfix[i], "AND") == 0)
        {
            if (topo < 1)
            {
                *tipoErro = 1;
                return NULL;
            }

            Set *set1 = pilha[topo];
            topo--;
            Set *set2 = pilha[topo];

            // Aplica operador AND considerando se há negação
            if (operadorNot)
            {
                if (elementoNegado == 0)
                {
                    pilha[topo] = intNegadoSet(set1, set2);
                }
                else
                {
                    pilha[topo] = intNegadoSet(set2, set1);
                }
            }
            else
            {
                pilha[topo] = interseccaoSet(set1, set2);
            }
            operadorNot = 0;
            elementoNegado = -1;
        }
        else if (strcmp(postfix[i], "OR") == 0)
        {
            if (topo < 1)
            {
                *tipoErro = 1;
                return NULL;
            }

            if (operadorNot)
            {
                *tipoErro = 2;
                return NULL;
            }

            Set *set1 = pilha[topo];
            topo--;
            Set *set2 = pilha[topo];

            pilha[topo] = uniaoSet(set1, set2);
            operadorNot = 0;
        }
        else // Palavras-chave
        {
            int deuCerto;
            Set *conjunto = buscaHash(hash, postfix[i], &deuCerto);
            topo++;
            if (deuCerto)
            {
                pilha[topo] = conjunto;
            }
            else
            {
                pilha[topo] = criaSet();
            }
        }
    }

    // Verifica se a avaliação terminou corretamente
    if (topo != 0 || tamanhoSet(pilha[topo]) == 0)
    {
        *tipoErro = 3;
        return NULL;
    }

    return pilha[topo];
}
