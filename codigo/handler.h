#include "TabelaHash.h"

char **Componente(char *busca, int *numComponentes);
char **converterParaPostfix(char **componentes, int tamanho, int *tamanhoPostfix);
Set *avaliarPostfix(Hash *hash, char **postfix, int quantidade, int *tipoErro);
