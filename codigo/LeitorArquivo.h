#ifndef LEITOR_ARQUIVO
#define LEITOR_ARQUIVO

#include "TabelaHash.h"

void removePontuacao(char *text);
void removeEspaco(char *text);
char *tratadorTexto(char *text);
int lerArquivo(char *nomeArquivo, Hash *hash);

#endif
