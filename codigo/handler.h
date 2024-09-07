#include "TabelaHash.h"

int palavraComposta(char *valor, int i, int tamanho);
void limparString(char *valor);
char **Componente(char *busca, int *numComponentes);
char **converterParaPostfix(char **componentes, int tamanho, int *tamanhoPostfix);
Set *avaliarPostfix(Hash *hash, char **postfix, int quantidade, int *tipoErro);
