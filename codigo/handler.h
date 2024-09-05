#ifndef MIDDLE_H
#define MIDDLE_H
#include "TabelaHash.h"
#include "set.h"

// Definições de constantes
#define MAX_COMPONENTES 100
#define MAX_PILHA 100

// Funções utilitárias
int palavraComposta(char *valor, int i, int tamanho);
void limparString(char *valor);
Set *buscaPalavra(Hash *hash, char *palavra, int *sucesso);
// Funções para manipulação de componentes
char **separarBuscaEmComponentes(char *busca, int *numComponentes);
int precedencia(char *operacao);
char **converterComponentesParaPostfix(char **componentes, int tamanho, int *tamanhoPostfix);

// Função para avaliar a expressão pós-fixada
Set *avaliarPostfix(Hash *hash, char **postfix, int quantidade);

// Função auxiliar para verificar se um token é um operador
int isOperator(char *token);

#endif // MIDDLE_H
