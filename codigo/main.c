#include <stdio.h>
#include <stdlib.h>
#include "LeitorArquivo.h"
#include "TabelaHash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Estrutura para armazenar precedências
typedef struct
{
    int notPrecedence;
    int andPrecedence;
    int orPrecedence;
} Precedence;

// Função para definir precedência com base na configuração
int precedence(char c, Precedence prec)
{
    if (c == 'N') // NOT
        return prec.notPrecedence;
    if (c == 'A') // AND
        return prec.andPrecedence;
    if (c == 'O') // OR
        return prec.orPrecedence;
    return 0;
}

// Função para verificar se um caractere é um operador
int isOperator(char c)
{
    return (c == 'AND' || c == 'NOT' || c == 'OR');
}

// Função para converter infixo para pós-fixo respeitando precedência e parênteses
void infixToPostfix(char *exp, char *output, Precedence prec)
{
    char stack[MAX];
    int top = -1, k = 0;

    for (int i = 0; exp[i]; i++)
    {
        if (isalnum(exp[i]) || exp[i] == '\"' || exp[i] == '\'')
        { // Se for um operando
            if (exp[i] == '\"' || exp[i] == '\'')
            {
                char quote = exp[i++];
                output[k++] = quote;
                while (exp[i] != quote)
                {
                    output[k++] = exp[i++];
                }
                output[k++] = quote;
                output[k++] = ' ';
            }
            else
            {
                while (isalnum(exp[i]) || exp[i] == ' ')
                {
                    output[k++] = exp[i++];
                }
                output[k++] = ' ';
                i--;
            }
        }
        else if (exp[i] == '(')
        {
            stack[++top] = exp[i];
        }
        else if (exp[i] == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                output[k++] = stack[top--];
                output[k++] = ' ';
            }
            top--; // Remove o '(' do stack
        }
        else if (isOperator(exp[i]))
        {
            while (top != -1 && precedence(stack[top], prec) >= precedence(exp[i], prec))
            {
                output[k++] = stack[top--];
                output[k++] = ' ';
            }
            stack[++top] = exp[i];
        }
    }

    while (top != -1)
    {
        output[k++] = stack[top--];
        output[k++] = ' ';
    }

    output[k - 1] = '\0'; // Termina a string output
}

// Função para calcular a interseção (AND) de dois conjuntos
void ANDOperation(char *result[], char *set1[], int size1, char *set2[], int size2, int *resultSize)
{
    *resultSize = 0;
    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < size2; j++)
        {
            if (strcmp(set1[i], set2[j]) == 0)
            {
                result[(*resultSize)++] = set1[i];
            }
        }
    }
}

// Função para calcular a união (OR) de dois conjuntos
void OROperation(char *result[], char *set1[], int size1, char *set2[], int size2, int *resultSize)
{
    *resultSize = 0;
    for (int i = 0; i < size1; i++)
    {
        result[(*resultSize)++] = set1[i];
    }
    for (int j = 0; j < size2; j++)
    {
        int found = 0;
        for (int i = 0; i < size1; i++)
        {
            if (strcmp(set2[j], set1[i]) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            result[(*resultSize)++] = set2[j];
        }
    }
}

// Função para calcular a diferença (NOT) entre dois conjuntos
void NOTOperation(char *result[], char *set1[], int size1, char *set2[], int size2, int *resultSize)
{
    *resultSize = 0;
    for (int i = 0; i < size1; i++)
    {
        int found = 0;
        for (int j = 0; j < size2; j++)
        {
            if (strcmp(set1[i], set2[j]) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            result[(*resultSize)++] = set1[i];
        }
    }
}

// Função para avaliar a expressão pós-fixada
void evaluatePostfix(char *postfix, char *result[], int *resultSize)
{
    char *stack[MAX][MAX];
    int stackSizes[MAX] = {0};
    int top = -1;

    char *token = strtok(postfix, " ");
    while (token != NULL)
    {
        if (isalpha(token[0]) || isdigit(token[0]) || token[0] == '\"' || token[0] == '\'')
        { // Se for uma palavra ou frase
            top++;
            stack[top][0] = token;
            stackSizes[top] = 1;
        }
        else if (strcmp(token, "A") == 0)
        { // AND
            char *temp[MAX];
            int tempSize;
            ANDOperation(temp, stack[top - 1], stackSizes[top - 1], stack[top], stackSizes[top], &tempSize);
            top--;
            stackSizes[top] = tempSize;
            memcpy(stack[top], temp, sizeof(char *) * tempSize);
        }
        else if (strcmp(token, "O") == 0)
        { // OR
            char *temp[MAX];
            int tempSize;
            OROperation(temp, stack[top - 1], stackSizes[top - 1], stack[top], stackSizes[top], &tempSize);
            top--;
            stackSizes[top] = tempSize;
            memcpy(stack[top], temp, sizeof(char *) * tempSize);
        }
        else if (strcmp(token, "N") == 0)
        { // NOT
            char *temp[MAX];
            int tempSize;
            NOTOperation(temp, stack[top], stackSizes[top], stack[top - 1], stackSizes[top - 1], &tempSize);
            stackSizes[top] = tempSize;
            memcpy(stack[top], temp, sizeof(char *) * tempSize);
        }
        token = strtok(NULL, " ");
    }

    *resultSize = stackSizes[top];
    memcpy(result, stack[top], sizeof(char *) * (*resultSize));
}

int main()
{
    Precedence prec;

    // Configuração de precedência (NOT tem maior precedência, AND tem precedência média, OR tem menor precedência)
    prec.notPrecedence = 3;
    prec.andPrecedence = 2;
    prec.orPrecedence = 1;

    char expression[] = "(usa OR \"palavra chave\") AND NOT (tentativa)";
    char postfix[MAX] = "";

    // Converte a expressão para pós-fixa respeitando parênteses e precedência
    infixToPostfix(expression, postfix, prec);

    printf("Expressão pós-fixa: %s\n", postfix);

    // Avalia a expressão pós-fixada
    char *result[MAX];
    int resultSize;
    evaluatePostfix(postfix, result, &resultSize);

    // Exibindo as palavras resultantes após aplicar as operações
    printf("Resultado após as operações:\n");
    for (int i = 0; i < resultSize; i++)
    {
        printf("%s\n", result[i]);
    }

    return 0;
}
/*

int main()
{
    Hash *tab = criaHash(11);
    if (lerArquivo("corpus.csv", tab) == -1)
        printf("Erro ao ler arquivo\n");

    int *RRN = NULL;
    int value;
    char frase[200];
    char *tokens[50];
    int i = 0;

    printf("Digite a palavra ou frase a ser buscada: ");
    scanf("%s", frase); // Corrigido para usar aspas duplas

    // Variável temporária para reconstruir a string com espaços ao redor dos parênteses
    char novaFrase[100] = "";
    int k = 0;

    // Adicionar espaços antes e depois de parênteses
    for (int j = 0; j < strlen(frase); j++)
    {
        if (frase[j] == '(' || frase[j] == ')')
        {
            novaFrase[k++] = ' ';
            novaFrase[k++] = frase[j];
            novaFrase[k++] = ' ';
        }
        else
        {
            novaFrase[k++] = frase[j];
        }
    }
    novaFrase[k] = '\0'; // Finalizar a nova string

    // Definir os delimitadores como espaço e nova linha
    const char delimitadores[] = " \n";

    // Quebrar a string usando strtok
    char *token = strtok(novaFrase, delimitadores);

    // Iterar sobre as partes separadas e armazenar no vetor de strings
    while (token != NULL)
    {
        tokens[i] = token;
        i++;
        token = strtok(NULL, delimitadores);
    }

    // Imprimir as palavras separadas
    printf("Palavras:\n");
    for (int j = 0; j < i; j++)
    {
        printf("%s\n", tokens[j]);
    }

    return 0;

    value = buscaHash(tab, &RRN, frase); // Captura o valor de retorno de buscaHash
    if (value != -1 && RRN != NULL)      // Verifica se encontrou e se RRN não é NULL
        printf("Encontrou vetor de rrn %d\n", RRN[0]);
    else
        printf("Não encontrou\n");

    // Lembre-se de liberar a memória alocada, se necessário.
    liberaHash(tab);
    return 0;
}
*/